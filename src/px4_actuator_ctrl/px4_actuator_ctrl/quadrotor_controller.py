
############################################################################
# Custom PX4 SITL Quadrotor Controller
# Author: Mikhael Sunil (adapted from PX4 example)
############################################################################

# Publishes directly to /fmu/in/actuator_motors for actuator-level offboard control.
# All positions/velocities are in ENU (x=East, y=North, z=Up).
# PX4 outputs NED,the odom callback converts everything before it reaches the controller.
# Mission: takeoff -> hover at A -> fly 3m forward -> land at B


#!/usr/bin/env python3

import math
import numpy as np
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy
import csv

from px4_msgs.msg import (
    VehicleOdometry,
    VehicleStatus,
    VehicleCommand,
    OffboardControlMode,
    ActuatorMotors,
)


#  Quaternion   (scalar-first: [w, x, y, z])# for 3D rotation representation without gimbal lock


# QUATERNION to DCM(direct cosine matrix) (Rotation Matrix)
# Converts quaternion into a 3×3 rotation matrix
# Used to transform vectors between body and world frames
def quat_to_dcm(q):
    w,x,y,z = q / (np.linalg.norm(q) + 1e-12)  # normalize quaternion to ensure valid rotation (unit quaternion)
    return np.array([
        [1-2*(y*y+z*z),   2*(x*y-z*w),   2*(x*z+y*w)],#world X axis in body frame
        [  2*(x*y+z*w), 1-2*(x*x+z*z),   2*(y*z-x*w)],#world Y axis
        [  2*(x*z-y*w),   2*(y*z+x*w), 1-2*(x*x+y*y)],#world Z axis
    ])    # formula comes from quaternion to rotation matrix conversion:
    # R(q) = function of (w, x, y, z)
    # used in:
    # v_world = R * v_body



# YAW EXTRACTION FROM QUATERNION
# Converts quaternion → heading angle
def yaw_from_quat(q):
    w,x,y,z = q
    return math.atan2(2.0*(w*z + x*y), 1.0 - 2.0*(y*y + z*z))
    # formula:
    # yaw = atan2(2(wz + xy), 1 - 2(y² + z²))
    # derived from rotation matrix.gives heading around Z axis (important for navigation)


ARM = 0.25    # arm length [m]
CQ  = 0.05   # yaw torque-to-thrust ratio

# B matrix maps [roll, pitch, yaw, thrust] to individual motor commands.
# Thrust row uses 0.25 (not 1.0) so B_pinv gives one motor its proportional share directly.
# Yaw row uses CQ=0.05 .the torque-to-thrust ratio measured for this airframe.
B = np.array([

    [ -ARM,      +ARM,        +ARM,       -ARM ],  # roll  
    [ -ARM,      +ARM,        -ARM,       +ARM ],  # pitch 
    [ +CQ,       +CQ,         -CQ,        -CQ  ],  # yaw   
    [  0.25,      0.25,         0.25,       0.25],  # thrust
])
B_pinv = np.linalg.pinv(B)# Compute pseudo-inverse of the mixer matrix B
# Converts desired [roll, pitch, yaw, thrust] to motor outputs [m1, m2, m3, m4]
# Used because B is not directly invertible; pinv() gives the best least-squares solution



def mix_motors(thrust, torque):
    # Combine control inputs into a single vector:
    # u = [roll, pitch, yaw, thrust]
    # This represents the desired total forces/torques on the drone
    u = np.array([
        torque[0],   # roll
        torque[1],   # pitch
        torque[2],   # yaw
        thrust
    ])
    # Convert desired forces/torques to individual motor outputs
    # Using pseudo-inverse of mixer matrix:
    # motors = B⁺ * u
    # This solves how each motor should contribute
    motors = B_pinv @ u

    # normalize. Find highest and lowest motor command
    hi = np.max(motors)
    lo = np.min(motors)
    # If any motor exceeds max limit (1.0),
    # shift all motors down equally to keep ratios same
    if hi > 1.0:
        motors -= (hi - 1.0)
    # If any motor goes below 0,
    # shift all motors up equally
    if lo < 0.0:
        motors -= lo

    return np.clip(motors, 0.0, 1.0)# Ensure all motor outputs stay within valid range [0, 1]


# PX4 navigation state IDs
NAV_STATE_OFFBOARD = 14   # VehicleStatus.NAVIGATION_STATE_OFFBOARD
ARMING_STATE_ARMED = 2    # VehicleStatus.ARMING_STATE_ARMED

# Startup phase constants
PHASE_WARMUP   = 0   # publishing heartbeat and idle motors, no arm yet
PHASE_OFFBOARD = 1   # sent OFFBOARD command, waiting for ack
PHASE_ARMING   = 2   # sent ARM command, waiting for armed state
PHASE_FLYING   = 3   # armed and in OFFBOARD for running controller


class Offboardcontroller(Node):

    HOVER_THRUST  = 0.75 
    #  Loop rate 
    CTRL_HZ = 50.0     # 50 Hz controller  (PX4 offboard needs ≥ 2 Hz)
    WARMUP_CYCLES   = int(CTRL_HZ * 1.5)  
    OFFBOARD_CYCLES = int(CTRL_HZ * 0.5)   

    def __init__(self):
        super().__init__('offboard_controller')

        px4_qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.TRANSIENT_LOCAL,
            history=HistoryPolicy.KEEP_LAST,
            depth=1,
        )
        sensor_qos = QoSProfile(
        reliability=ReliabilityPolicy.BEST_EFFORT,
        durability=DurabilityPolicy.VOLATILE,        
        history=HistoryPolicy.KEEP_LAST,
        depth=1,
        )

        self._hover_start_time = None
        self._at_final_point = False
        self._log_file = open("flight_log.csv", "w", newline="")
        self._logger_csv = csv.writer(self._log_file)
        self._final_hover_start = None
        self.pos = np.zeros(3)
        self.vel = np.zeros(3)
        self.pos_sp = None #Postiton of setipoint
        self.yaw = 0.0
        self.vel_sp_smooth = np.zeros(2)



        self._logger_csv.writerow([
            "time",
            "px","py","pz",
            "spx","spy","spz",
            "vx","vy","vz",
            "err_x","err_y","err_z",
            "pitch_tilt","roll_tilt","thrust",
            "rx","ry","rz",
            "m1","m2","m3","m4"
        ])

        #  Subscribers 
        self.create_subscription(VehicleOdometry,
            '/fmu/out/vehicle_odometry', self._odom_cb, sensor_qos)
        self.create_subscription(VehicleStatus,
            '/fmu/out/vehicle_status', self._status_cb, px4_qos)

        # ── Publishers 
        self._offboard_pub = self.create_publisher(
            OffboardControlMode, '/fmu/in/offboard_control_mode', px4_qos)
        self._cmd_pub      = self.create_publisher(
            VehicleCommand, '/fmu/in/vehicle_command', px4_qos)
        self._motors_pub   = self.create_publisher(
            ActuatorMotors, '/fmu/in/actuator_motors', px4_qos)

        #  Vehicle state 

        self.q_ned      = np.array([1., 0., 0., 0.])
        self.rates_body = np.zeros(3)
        self.arming_state = 0
        self.nav_state    = 0
        self._hover_xy_lock = None
   

        #  Mission state 
        self._mission_phase = 'climb'   # climb → waypoint → land
        self.pos_sp_ned : np.ndarray | None = None
        self.yaw_sp     = 0.0
        self._takeoff_xy = np.zeros(2)

        #  Startup state machine 
        self._phase  = PHASE_WARMUP
        self._cycles = 0          # cycles elapsed in current phase
        self._last_t : float | None = None
        self._timer = self.create_timer(1.0 / self.CTRL_HZ, self._loop)
        self.get_logger().info('Controller ready . waiting for odometry …')


    #  Callbacks
    def _odom_cb(self, msg: VehicleOdometry):
        # Raw PX4 data (NED frame)
        pos_ned = np.array(msg.position[:3])
        vel_raw = np.array(msg.velocity[:3])
        # Convert POSITION → ENU
        self.pos = np.array([
            pos_ned[1],     # east → x
            pos_ned[0],     # north → y
            -pos_ned[2]     # up
        ])
        # Converting VELOCITY to ENU
        if msg.velocity_frame == VehicleOdometry.VELOCITY_FRAME_NED:
            vel_ned = vel_raw
        else:
            # body frame to NED first
            vel_ned = quat_to_dcm(np.array(msg.q)) @ vel_raw

        self.vel = np.array([
            vel_ned[1],
            vel_ned[0],
            -vel_ned[2]
        ])
        self.q_ned = np.array(msg.q)
        self.yaw   = yaw_from_quat(self.q_ned)
        # Angular velocity (body frame)
        rates = np.array(msg.angular_velocity[:3])
        if np.all(np.isfinite(rates)):
            self.rates_body = rates
        # Setpoint initialization (ONLY ONCE)
        if self.pos_sp is None:

            self._takeoff_xy = self.pos[:2].copy()

            self.pos_sp = self.pos.copy()
            self.pos_sp[2] += 3.0   # take off UP 3m 

            self.yaw_sp = self.yaw

            self.traj_pos = self.pos[:2].copy()
            self.traj_vel = np.zeros(2)

            self.get_logger().info(
                f'Setpoint latched (ENU): '
                f'[{self.pos_sp[0]:.2f}, {self.pos_sp[1]:.2f}, {self.pos_sp[2]:.2f}]'
            )

    def _status_cb(self, msg: VehicleStatus):
        self.arming_state = msg.arming_state
        self.nav_state    = msg.nav_state

    #  PX4 pffboard mode

    def _ts(self) -> int:
        """Timestamp in microseconds from ROS clock (to be consistent with PX4 bridge)"""
        return self.get_clock().now().nanoseconds // 1000

    def _pub_offboard_mode(self):
        msg = OffboardControlMode()
        msg.timestamp       = self._ts()
        msg.position        = False
        msg.velocity        = False
        msg.acceleration    = False
        msg.attitude        = False
        msg.direct_actuator = True  
        self._offboard_pub.publish(msg)

    def _pub_idle_motors(self):
        msg = ActuatorMotors()
        msg.timestamp        = self._ts()
        msg.timestamp_sample = self._ts()
        msg.reversible_flags = 0
        for i in range(12):
            msg.control[i] = 0.0  
        self._motors_pub.publish(msg)
    def world_to_body(self, v_enu):
            # Converting ENU to NED first
            v_ned = np.array([
                v_enu[1],   # N = y
                v_enu[0],   # E = x
                -v_enu[2]   # D = -z
            ])
            R = quat_to_dcm(self.q_ned)
            return R.T @ v_ned
    def _send_cmd(self, command, p1=0., p2=0., p7=0.):
        msg = VehicleCommand()
        msg.timestamp        = self._ts()
        msg.command          = command
        msg.param1           = float(p1)
        msg.param2           = float(p2)
        msg.param7           = float(p7)
        msg.target_system    = 1
        msg.target_component = 1
        msg.source_system    = 1
        msg.source_component = 1
        msg.from_external    = True
        self._cmd_pub.publish(msg)

# Holds position after takeoff and after waypoint arrival.
# Two-layer: position error -->velocity setpoint, then velocity error --?tilt.
# The xy_lock freezes the target point on first entry so drift doesn't change the goal.
# Velocity damping runs even inside the deadband ,otherwise residual speed causes slow spiral.
    def _hover_control(self, err_z):

        thrust = self.HOVER_THRUST + (0.5 * err_z) - (0.3 * self.vel[2])
        # XY position  LOCK LOGIC 
        if self._hover_xy_lock is None:
            self._hover_xy_lock = self.pos[:2].copy()

        err_xy = self._hover_xy_lock - self.pos[:2]
        dist   = np.linalg.norm(err_xy)

        # small threshold
        deadband = 0.05

        # Direct velocity damping  always active
        vel_body = self.world_to_body(np.array([self.vel[0], self.vel[1], 0.0]))
        vel_damp_pitch = float(np.clip(-vel_body[0] * 0.06, -0.020, 0.020))
        vel_damp_roll  = float(np.clip(-vel_body[1] * 0.06, -0.020, 0.020))

        if dist < deadband:
            # inside threshold -> no correction
            pitch_tilt = vel_damp_pitch
            roll_tilt  = vel_damp_roll
        else:
            # small correction only
            Kp = 0.15   
            vel_sp = Kp * err_xy #Velocity to setpoint
            vel_sp = np.clip(vel_sp, -0.3, 0.3)

            vel_err = vel_sp - self.vel[:2]
# rotates the error from world frame (North/East) into the drone's own frame. 
# Matters because the drone might be facing sideways like "move East" means different motors depending on which way it's pointed.
            vel_err_body = self.world_to_body(np.array([vel_err[0], vel_err[1], 0.0]))

            pitch_tilt = float(np.clip(vel_err_body[0] * 0.04 + vel_damp_pitch, -0.025, 0.025))
            roll_tilt  = float(np.clip(vel_err_body[1] * 0.04 + vel_damp_roll,  -0.025, 0.025))

        return thrust, pitch_tilt, roll_tilt

# Moves toward pos_sp[:2] at up to 0.5 m/s, slowing inside 0.2m.
# Tilt comes from velocity error, not position error directly — this gives natural braking.
# The smoothed vel_sp (alpha=0.2) prevents sharp tilt changes on setpoint transitions.
# Thrust uses the gravity-compensated acc_sp[2] rather than a fixed offset.
    def _waypoint_control(self, err_z):

        #  Position error 
        err = self.pos_sp - self.pos
        # error = desired position − current position
        err_xy = err[:2]# taking only horizontal components (X, Y)
        dist = np.linalg.norm(err_xy)  # Euclidean distance: ||e|| = sqrt(x² + y²), used to scale speed based on distance

        #  Velocity setpoint with braking 
        max_speed = 0.50# max allowed horizontal velocity (m/s)
        slow_radius = 0.2 #slow down radius near the target

        if dist > slow_radius:
            vel_sp_xy = max_speed * (err_xy / (dist + 1e-6))  #v=vmax​⋅*(d/r)
        # direction = err_xy / ||err_xy||  → unit vector
        # velocity = max_speed * direction
        # constant motion toward target
        else:
            vel_sp_xy = max_speed * (dist / slow_radius) * (err_xy / (dist + 1e-6))  
        # linear scaling: v ∝ distance
        # v = vmax * (d / slow_radius)
        # ensures velocity reduces to 0 as setpoint approaches for smooth stop
     
# 1e-6 guards against division by zero when dist=0 (drone exactly on target); 
# err_xy is also ~0 there so the result stays small.

        alpha = 0.2  # smoothing factor (Exponential Moving Average(EMA) filter)  # smoothing factor (0 = smooth, 1 = raw)

        if not hasattr(self, "vel_sp_prev"):# initialize previous velocity
            self.vel_sp_prev = np.zeros(3)

        # Exponential Moving Average (EMA):y[n]=αx[n]+(1−α)y[n−1]
        # v_new = α * v_current + (1-α) * v_prev
        # reduces sudden jumps → avoids jerks
        vel_sp = alpha * np.array([vel_sp_xy[0], vel_sp_xy[1], err_z * 0.8]) + \
                (1 - alpha) * self.vel_sp_prev
        self.vel_sp_prev = vel_sp

        # velocity error
        vel_err = vel_sp - self.vel  # velocity error = desired − actual

        #acceleration to  setpoint (Velocity to  Acceleration)
        # PD control:
        # acceleration ≈ Kp * velocity_error − Kd * velocity
        # used from:
        # a = dv/dt for controlling acceleration stabilizes velocity
        # - 1.0 * vel_err [drives toward target velocity]
        # - 0.7 * vel [damping term (prevents oscillations)]
        kp=1.0
        kd=0.7
        acc_sp = kp * vel_err - kd * self.vel

        acc_sp = np.clip(acc_sp, -2.0, 2.0)    # limit acceleration for safety and stability
                                                 # prevents aggressive tilt commands

        #  Added gravity 
        acc_sp[2] += 9.81 # added gravity to Z-axis because drone must counter gravity to hover
        #  Thrust direction 
        zb = acc_sp / (np.linalg.norm(acc_sp) + 1e-6)
            # zb = desired body Z axis direction
            # normalize acceleration vector to unit vector.We normalize acc_sp to get only its direction, 
            # so the drone tilts correctly regardless of how large the acceleration is

        zb_body = self.world_to_body(zb) # convert from world frame → body frame
        pitch_tilt = zb_body[0]
        roll_tilt  = zb_body[1]
        # tilt = lateral acceleration / gravity
        #  Clamp tilt 
        pitch_tilt = float(np.clip(pitch_tilt, -0.08, 0.08))
        roll_tilt  = float(np.clip(roll_tilt,  -0.08, 0.08))
        # limiting tilt angle
        #  Thrust 
        thrust = self.HOVER_THRUST * (acc_sp[2] / 9.81)
        #  thrust = hover_thrust * (desired_acc / g)
        # referred from PX4 multicopter position control
        thrust = float(np.clip(thrust, 0.5, 0.8))
        # limiting thrust range
        return thrust, pitch_tilt, roll_tilt
    

# Computes a new XY target in ENU by projecting 'distance' meters along the current yaw.
# NED yaw from PX4 is converted to ENU yaw before the trig. One-time call at hover->waypoint.
    def set_forward_setpoint(self, distance):

        #yaw = self.yaw (yaw angle from PX4 (in NED frame, radians))
        # Converting NED yaw to  ENU yaw
        yaw_enu = math.pi/2 - self.yaw
        # frame conversion:
        # NED (North-East-Down) → ENU (East-North-Up)
        # formula: yaw_enu = π/2 − yaw_ned
        # needed because trig (cos/sin) assumes ENU frame

        # computing forward displacement
        dx = distance * math.cos(yaw_enu)
        dy = distance * math.sin(yaw_enu)
        # basic 2D projection:
        # x = d * cos(θ)
        # y = d * sin(θ)
        #
        # converts forward motion into global XY coordinates

        #Set target setpoint
        sp_x = self.pos_sp[0]   # saving current Setpoint for reference
        sp_y = self.pos_sp[1]
        self.pos_sp[0] = sp_x + dx   # new target = current setpoint + forward offset
        self.pos_sp[1] = sp_y + dy

        self.get_logger().info(
            f"[SETPOINT] Forward {distance}m → "
            f"Target=({self.pos_sp[0]:.2f}, {self.pos_sp[1]:.2f})"
        )
        self.get_logger().info(f"Yaw: {math.degrees(self.yaw):.2f}")

        #  Publishing Motors 
    def _publish_motors(self, cmds: np.ndarray):

        msg = ActuatorMotors()
        msg.timestamp        = self._ts()
        msg.timestamp_sample = self._ts()
        msg.reversible_flags = 0

        # Initialize all channels to 0
        for i in range(12):
            msg.control[i] = 0.0

        # Set motor outputs (first 4 motors)
        for i in range(4):
            msg.control[i] = float(cmds[i])

        self._motors_pub.publish(msg)


    #  Main loop  

    def _loop(self):

        #  Always publishing  heartbeat 
        now = self.get_clock().now().nanoseconds * 1e-9
        self._pub_offboard_mode()# continuously send OFFBOARD heartbeat


        # FIRST check whether setpoint is initialised
        if self.pos_sp is None:
            return
         # don't run control until first odometry received
        # PHASE 1: WARMUP

        if self._phase == PHASE_WARMUP:

            self._pub_idle_motors()# sending zero thrust before arming
            self._cycles += 1  # counting control loop iterations

            if self._cycles >= self.WARMUP_CYCLES:
                self.get_logger().info('Warmup complete .Switchting to OFFBOARD mode')# commanding PX4 to switch to OFFBOARD mode
                self._send_cmd(VehicleCommand.VEHICLE_CMD_DO_SET_MODE, p1=1., p2=6.)
                self._phase = PHASE_OFFBOARD
                self._cycles = 0

            return

        # PHASE 2: OFFBOARD
        if self._phase == PHASE_OFFBOARD:

            self._pub_idle_motors()# still sending idle until mode confirmed
            self._cycles += 1

            if self._cycles % 10 == 0:
                self._send_cmd(VehicleCommand.VEHICLE_CMD_DO_SET_MODE, p1=1., p2=6.)# resending OFFBOARD command periodically

            if self.nav_state == NAV_STATE_OFFBOARD:
                self.get_logger().info('OFFBOARD active .Drone ARMING.........')
                self._send_cmd(VehicleCommand.VEHICLE_CMD_COMPONENT_ARM_DISARM, p1=1.)# arm the drone
                self._phase = PHASE_ARMING
                self._cycles = 0

            return

        #  PHASE 3: ARMING

        if self._phase == PHASE_ARMING:

            self._pub_idle_motors()
            self._cycles += 1

            if self._cycles % 10 == 0:
                self._send_cmd(VehicleCommand.VEHICLE_CMD_COMPONENT_ARM_DISARM, p1=1.) # retry arm command (in case it fails)

            if self.arming_state == ARMING_STATE_ARMED:
                self.get_logger().info('Armed succesfully . Flight control started')
                self._phase = PHASE_FLYING
                self._last_t = now  # storing time for dt calculation
            
            elif self._cycles > int(self.CTRL_HZ * 5):
                self.get_logger().warn('ARM timeout.retrying')
                self._phase = PHASE_OFFBOARD
                self._cycles = 0 # fallback if arming failed

            return

        # PHASE 4: FLYING

        #  Safety check 
        if not hasattr(self, '_control_loss_timer'):
            self._control_loss_timer = None

        if self.arming_state != ARMING_STATE_ARMED or self.nav_state != NAV_STATE_OFFBOARD:
            self.get_logger().warn("Offboard lost .Holding position")
            self._pub_idle_motors()   # keeping the publishing so PX4 doesn't kill offboard

            return
                
        else:
            self._control_loss_timer = None

        #  Time step 
        dt = now - self._last_t # dt = Δt = time difference between control cycles
        dt = max(1e-4, min(dt, 0.05))    # clamp dt:
           # avoid division by zero
            # prevent instability from large dt spikes
        self._last_t = now

        #  Run controller 
        motors = self._run_controller(dt) # compute motor outputs from control logic

        #  Publish motors 
        self._publish_motors(motors) # publish actuator commands
        if self._cycles % 10 == 0:
            self._log_file.flush() # flush log to file periodically (avoid data loss)


#  takeoff control
# Transitions to hover when altitude error drops below 0.3m.
# XY lock is set here so hover knows exactly where to hold.
    def _takeoff_control(self, err_z):
        now   = self.get_clock().now().nanoseconds * 1e-9 # current time (seconds) using  for timing transitions
        
        # POSITION error to  VELOCITY in Z axis
        kp=0.6
        vel_z_sp = np.clip(err_z * kp, -0.6, 0.6)
        # proportional control:
        # v_sp = Kp * error
        # limits vertical speed to safe range
        # prevents aggressive climb/descent

        err_vz   = vel_z_sp - self.vel[2] # VELOCITY ERROR (velocity error = desired vertical speed − current speed)
        # thrust =hover_thrust + Kp * velocity_error
        kp2=0.15
        thrust = np.clip(0.75 + err_vz * kp2, 0.5, 0.9)    # if climbing too slow → increase thrust
        # if climbing too fast ->reduce thrust
        # 0.75 = hover thrust baseline
        # 0.15 = velocity gain

        pitch_tilt = 0.0
        roll_tilt  = 0.0

        # transition condition
        if abs(err_z) < 0.3 and self._mission_phase == 'climb': # condition:if |position error| < 0.3m ->reached target altitude
            self._mission_phase = 'hover'# switching state machine to hover mode
            self._hover_xy_lock = self.pos[:2].copy()# stores current XY position.this becomes the hold position for hover
            self._hover_start_time = now # starting hover timer (used for stability check)

            self.get_logger().info("Transition → intial hover at point A ")
        return thrust, pitch_tilt, roll_tilt


# The land Three-zone descent fast above 1m, medium above 0.3m, gentle below that.
# Thrust is smoothed with a low-pass (alpha=0.25) to avoid motor surges near ground.
# Disarm triggers at height < 0.08m with near-zero vertical velocity.
    def _land_control(self, err_z):

        # Set desired altitude to ground level (ENU frame)
        self.pos_sp[2] = 0.0
        height = self.pos[2]# Current altitude (height above ground)

       # Fixed downward velocity → smooth and predictable landing
         # More negative → faster descent, less negative → slower
        vel_z_sp = -0.15 

        err_vz = vel_z_sp - self.vel[2]# Velocity error (desired - actual vertical velocity)

        # ── THRUST CONTROL ──
        # Adjust thrust based on vertical velocity error
        # If falling too fast , increases thrust
        # If falling too slow , decreases thrust
        thrust = self.HOVER_THRUST + 0.12 * err_vz

        # Damping term (reduces oscillations and bounce)
        # Acts like derivative control: D = -K * velocity
        thrust -= 0.08 * self.vel[2]
        # Clamp thrust to safe range
        # Prevents free fall (too low) and bounce (too high)
        thrust = float(np.clip(thrust, 0.5, 0.72))

        # smooth thurst down
        # Low-pass filter (EMA)
        # Reduces sudden thrust changes -> smoother descent
        if not hasattr(self, "thrust_prev"):
            self.thrust_prev = thrust

        thrust = 0.3 * thrust + 0.7 * self.thrust_prev
        self.thrust_prev = thrust

        #  XY DAMPING (ANTI-SPIRAL) 
        vel_err = -self.vel[:2]
        vel_err_body = self.world_to_body(np.array([vel_err[0], vel_err[1], 0.0]))      # Convert world velocity → body frame
                                                                        # Required because tilt commands are body-frame based
        pitch_tilt = float(np.clip(vel_err_body[0] * 0.08, -0.05, 0.05))
        roll_tilt  = float(np.clip(vel_err_body[1] * 0.08, -0.05, 0.05))

        #  TOUCHDOWN 
        # If very close to ground AND almost no vertical motion → landed
        if height < 0.08 and abs(self.vel[2]) < 0.1:
            self.get_logger().info("Landed → disarming")
            self._send_cmd(VehicleCommand.VEHICLE_CMD_COMPONENT_ARM_DISARM, p1=0.)

        return thrust, pitch_tilt, roll_tilt
    
# Main dispatch. Picks the right controller for the current mission phase,
# then mixes roll/pitch/yaw_damp with the phase output.
# Rate damping (rx, ry, rz) resists unwanted rotation regardless of phase.
# Yaw damping is passed directly into mix_motors — the B matrix handles the rest.

    def _run_controller(self, dt: float) -> np.ndarray:

        # ── Common calculations ─────────────────────
        now = self.get_clock().now().nanoseconds * 1e-9  # current time (seconds)
        err = self.pos_sp - self.pos # position error: e = x_ref − x
        err_xy = err[:2]  # horizontal error
        dist = np.linalg.norm(err_xy)
        err_z = self.pos_sp[2] - self.pos[2] # vertical position error
        # Selects control mode based on mission phase and computes motor outputs
        if self._mission_phase == 'climb':
            thrust, pitch_tilt, roll_tilt = self._takeoff_control(err_z)

        elif self._mission_phase == 'hover':

            thrust, pitch_tilt, roll_tilt = self._hover_control(err_z) # takeoff controller handles vertical ascent

            now = self.get_clock().now().nanoseconds * 1e-9
            vel_xy = np.linalg.norm(self.vel[:2])# horizontal speed: ||v_xy||
            pos_err_xy = np.linalg.norm(self.pos_sp[:2] - self.pos[:2])# horizontal position error

            # Checking if stable hover 
            if vel_xy < 0.1 and pos_err_xy < 0.3: # condition:low velocity and small position error
                if self._hover_start_time is None:
                    self._hover_start_time = now

            #  Transition to waypoint 
            if (not self._at_final_point) and self._hover_start_time is not None and (now - self._hover_start_time > 2.0): # condition: stable hover for > 2 seconds
                self._mission_phase = 'waypoint' # switch to waypoint
                self.set_forward_setpoint(3.0)# set target 3 meters ahead
                self.get_logger().info("Transition to  waypoint mode")
                # check stable at B
            else:
                self._final_hover_start = None

        elif self._mission_phase == 'waypoint':

            thrust, pitch_tilt, roll_tilt = self._waypoint_control(err_z) # waypoint controller drives toward setpoint
            self._final_hover_start = None
            err_xy_dist = np.linalg.norm(self.pos_sp[:2] - self.pos[:2])  # distance to setpoint
            vel_xy      = np.linalg.norm(self.vel[:2]) # horizontal velocity     
    
            #  Checking if setpoint reached 
            if err_xy_dist < 0.3 and vel_xy < 0.1:# condition:if close to setpoint + almost stopped

                # reducing xy motion  
                self.vel_sp_prev = np.zeros(3)
                self.vel[:] = np.zeros(3)  # reducing residual velocity

                # locking XY so it doesn't drift during landing
                self.pos_sp[0] = self.pos[0]
                self.pos_sp[1] = self.pos[1]

                # switch to landing
                self._mission_phase = 'land'

                self.get_logger().info("Waypoint reached → LAND")
        elif self._mission_phase == 'land':
            thrust, pitch_tilt, roll_tilt = self._land_control(err_z)# landing controller handles descent

        else:# fallback 
            thrust, pitch_tilt, roll_tilt = 0.6, 0.0, 0.0

        # ── Motor mix ───────────────────────────────
         # RATE DAMPING (for stabilization)
        rx, ry, rz = self.rates_body# angular velocities (rad/s)
        roll_damp  = float(np.clip(-rx * 0.08, -0.20, 0.20))
        pitch_damp = float(np.clip(+ry * 0.08, -0.20, 0.20))
        yaw_damp   = float(np.clip(-rz * 0.06, -0.15, 0.15))
        # damping ≈ -K * angular_rate
        # reduces unwanted rotations
        # acts like derivative control
        roll_cmd  = roll_damp  + roll_tilt
        pitch_cmd = pitch_damp + pitch_tilt
         # combining feedforward tilt (from controller) and feedback damping (from rates)
        motors = mix_motors(
            thrust,
            np.array([roll_cmd, pitch_cmd, yaw_damp])
        )
        # mixer converts:
        # [roll, pitch, yaw, thrust] → individual motor outputs
        #
        # uses B matrix:
        # τ = B * motor_forces

        # compute position errors for logging
        err_x = self.pos_sp[0] - self.pos[0]
        err_y = self.pos_sp[1] - self.pos[1]
        
        # CSV LOGGING
        # log everything
        vel_sp = getattr(self, "vel_sp_prev", np.zeros(3))
        acc_sp = getattr(self, "acc_sp", np.zeros(3))

        self._logger_csv.writerow([
            self.get_clock().now().nanoseconds * 1e-9,

            *self.pos,
            *self.pos_sp,

            *self.vel,
            *vel_sp,

            err_x, err_y, err_z,

            *acc_sp,

            pitch_tilt, roll_tilt, thrust,

            *self.rates_body,

            *motors
        ])
        self._log_file.flush()
        # DEBUG LOG
        self.get_logger().info(
            f"[{self._mission_phase}] "
            f"pos=({self.pos[0]:.2f},{self.pos[1]:.2f}) "
           # f"err=({err_x:.2f},{err_y:.2f}) "
            f"vel=({self.vel[0]:.2f},{self.vel[1]:.2f}) "
            f"tilt=({pitch_tilt:.3f},{roll_tilt:.3f}) "
            f"yaw(deg)={math.degrees(self.yaw):.1f}"
            f"thr={thrust:.2f}",
            throttle_duration_sec=0.5
        )
        return np.clip(motors, 0.0, 1.0)# ensuring motor commands are within valid range

def main(args=None):
    rclpy.init(args=args)
    node = Offboardcontroller()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()
        node._log_file.close()


if __name__ == '__main__':
    main()







