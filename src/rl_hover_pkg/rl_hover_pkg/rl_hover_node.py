
#!/home/mikks/cf-venv/bin/python

import rclpy
from rclpy.node import Node
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
from rclpy.clock import Clock
from px4_msgs.msg import VehicleOdometry, TrajectorySetpoint
from px4_msgs.msg import OffboardControlMode
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
from px4_msgs.msg import VehicleCommand
from rclpy.clock import Clock
import matplotlib.pyplot as plt
 
# Actor-Critic Model
 
class ActorCritic(nn.Module):
    def __init__(self):
        super().__init__()

        self.net = nn.Sequential(
            nn.Linear(12, 128),
            nn.ReLU(),
            nn.Linear(128, 128),
            nn.ReLU()
        )

        self.actor_mean = nn.Linear(128, 4)
        self.actor_log_std = nn.Parameter(torch.zeros(4))
        self.critic = nn.Linear(128, 1)

    def forward(self, x):
        x = self.net(x)
        mean = self.actor_mean(x)
        std = torch.exp(self.actor_log_std)
        value = self.critic(x)
        return mean, std, value



 
# RL Node
 
class RLHoverNode(Node):

    def __init__(self):
        super().__init__('rl_hover_node')
        qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=10
        )


        # Subscriber
        self.sub = self.create_subscription(
            VehicleOdometry,
            '/fmu/out/vehicle_odometry',
            self.odom_callback,
            qos

        )

        # Publisher
        self.pub = self.create_publisher(
            TrajectorySetpoint,
            '/fmu/in/trajectory_setpoint',
            qos

        )
        self.offboard_pub = self.create_publisher(
        OffboardControlMode,
        '/fmu/in/offboard_control_mode',
        qos)
        self.cmd_pub = self.create_publisher(
            VehicleCommand,
            '/fmu/in/vehicle_command',
            qos
            )
        

        # Live plot setup
        plt.ion()  # interactive mode
        self.fig, self.ax = plt.subplots(3, 1)

        self.reward_line, = self.ax[0].plot([], [], label="Reward")
        self.error_line, = self.ax[1].plot([], [], label="Position Error")
        self.pd_line, = self.ax[2].plot([], [], label="PD Influence")
        self.rl_line, = self.ax[2].plot([], [], label="RL Influence")
        self.ax[0].set_title("Reward")
        self.ax[1].set_title("Position Error")
        self.ax[2].set_title("Control Influence")
        self.ax[2].legend()

        self.ax[0].legend()
        self.ax[1].legend()
        self.pd_log = []
        self.rl_log = []




        self.offboard_counter = 0
        # Model
        self.model = ActorCritic()
        self.optimizer = optim.Adam(self.model.parameters(), lr=3e-4)

        self.gamma = 0.99
        self.reward_log = []
        self.error_log = []
        self.prev_state = None
        self.prev_action = None
        self.prev_value = None

        self.training = True
        self.step_count = 0
        self.max_steps = 50000   # training iterations
        self.episode_step = 0
        self.max_episode_steps = 500
        self.episode = 0

        self.get_logger().info("RL Hover Node Started")
    def publish_vehicle_command(self, command, param1=0.0, param2=0.0):
        msg = VehicleCommand()
        msg.param1 = param1
        msg.param2 = param2
        msg.command = command
        msg.target_system = 1
        msg.target_component = 1
        msg.source_system = 1
        msg.source_component = 1
        msg.from_external = True
        msg.timestamp = int(Clock().now().nanoseconds / 1000)

        self.cmd_pub.publish(msg)

     
    # Odom Callback
     
    def odom_callback(self, msg):
        progress = self.step_count / self.max_steps * 100
        # ===== 1. Extract state =====
        raw_state = self.extract_state(msg)

        # ===== 2. Scaled state for NN =====
        state = np.array(raw_state)
        state[0:3] /= 5.0
        state[3:6] /= 3.0

        state_tensor = torch.tensor(state, dtype=torch.float32)

        # ===== 2. Forward + sample =====
        mean, std, value = self.model(state_tensor)

        dist = torch.distributions.Normal(mean, std)
        action = dist.sample()
        log_prob = dist.log_prob(action).sum()

        action_np = action.detach().numpy()

        # ===== Warmup =====
        if self.step_count < 200:
            self.prev_value = value.detach()
            self.step_count += 1
            return

        # ===== 3. Control =====
        target = np.array([0, 0, -2])
        pos = np.array(raw_state[0:3])
        error = target - pos
        decay = max(0.3, 0.9 - self.step_count / 80000)
        pd_influence = decay
        rl_influence = 1.0 - decay

        self.pd_log.append(pd_influence)
        self.rl_log.append(rl_influence)

        vx = decay * error[0] + (1 - decay) * action_np[0]
        vy = decay * error[1] + (1 - decay) * action_np[1]
        vz = decay * error[2] + (1 - decay) * action_np[2]

        vx = np.clip(vx, -0.3, 0.3)
        vy = np.clip(vy, -0.3, 0.3)
        vz = np.clip(vz, -0.35, -0.2)

        yaw_rate = 0.0

        # ===== 4. OFFBOARD MODE =====
        offboard_msg = OffboardControlMode()
        offboard_msg.timestamp = int(Clock().now().nanoseconds / 1000)
        offboard_msg.position = False
        offboard_msg.velocity = True
        offboard_msg.acceleration = False
        offboard_msg.attitude = False
        offboard_msg.body_rate = False
        self.offboard_pub.publish(offboard_msg)

        # ===== 5. TRAJECTORY =====
        traj_msg = TrajectorySetpoint()
        traj_msg.timestamp = int(Clock().now().nanoseconds / 1000)

        traj_msg.velocity[0] = vx
        traj_msg.velocity[1] = vy
        traj_msg.velocity[2] = vz

        traj_msg.position = [float('nan')] * 3
        traj_msg.acceleration = [float('nan')] * 3
        traj_msg.yaw = float('nan')
        traj_msg.yawspeed = yaw_rate

        self.pub.publish(traj_msg)

        # ===== ARM =====
        self.offboard_counter += 1
        if self.offboard_counter == 20:
            self.get_logger().info("Switching to OFFBOARD + ARM")

            self.publish_vehicle_command(
                VehicleCommand.VEHICLE_CMD_DO_SET_MODE, 1.0, 6.0
            )
            self.publish_vehicle_command(
                VehicleCommand.VEHICLE_CMD_COMPONENT_ARM_DISARM, 1.0
            )

        # ===== 6. Reward =====
        reward = self.compute_reward(raw_state)
        pos_error = np.linalg.norm(pos - target)
        if self.step_count % 10 == 0:
            self.get_logger().info(f"Reward: {reward:.3f}, Error: {pos_error:.3f}")
            self.get_logger().info(f"Progress: {progress:.1f}%")

        # ===== 7. Training =====
        if self.training and self.prev_value is not None:

            target_value = reward + self.gamma * value.detach()
            advantage = target_value - self.prev_value
            entropy = dist.entropy().mean()
            actor_loss = -(log_prob * advantage.detach() + 0.01 * entropy)
            critic_loss = (value - target_value).pow(2).mean()

            loss = actor_loss + critic_loss

            self.optimizer.zero_grad()
            loss.backward()
            self.optimizer.step()
            std = torch.clamp(std, 0.1, 1.0)
            advantage = torch.clamp(advantage, -5, 5)
      
            if self.step_count % 100 == 0:
                self.get_logger().info(f"Entropy: {entropy.item():.3f}")
        # ===== 8. Update =====
        self.prev_value = value.detach()
        self.step_count += 1

        # ===== 9. Stop =====
        if pos_error < 0.2:
            self.training = False
            self.get_logger().info("Stable hover achieved")
        self.reward_log.append(reward)
        self.error_log.append(pos_error)

        if self.step_count % 20 == 0:

            # Update reward plot
            self.reward_line.set_xdata(range(len(self.reward_log)))
            self.reward_line.set_ydata(self.reward_log)
            self.ax[0].relim()
            self.ax[0].autoscale_view()

            # Update error plot
            self.error_line.set_xdata(range(len(self.error_log)))
            self.error_line.set_ydata(self.error_log)
            self.ax[1].relim()
            self.ax[1].autoscale_view()

            # PD vs RL plot
            self.pd_line.set_xdata(range(len(self.pd_log)))
            self.pd_line.set_ydata(self.pd_log)

            self.rl_line.set_xdata(range(len(self.rl_log)))
            self.rl_line.set_ydata(self.rl_log)

            self.ax[2].relim()
            self.ax[2].autoscale_view()

            plt.draw()
            plt.pause(0.001)
     
    # Extract State
     
    def extract_state(self, msg):

        return [
            msg.position[0],
            msg.position[1],
            msg.position[2],
            msg.velocity[0],
            msg.velocity[1],
            msg.velocity[2],
            msg.q[0],
            msg.q[1],
            msg.q[2],
            msg.angular_velocity[0],
            msg.angular_velocity[1],
            msg.angular_velocity[2],
        ]

     
    # Reward Function
     
    def compute_reward(self, state):

        pos = np.array(state[0:3])
        vel = np.array(state[3:6])

        target = np.array([0, 0, -2])

        pos_error = np.linalg.norm(pos - target)
        vel_error = np.linalg.norm(vel)

        z_error = abs(pos[2] + 2)

        reward = -pos_error - 0.3 * vel_error
        reward -= 5.0 * z_error
        reward += np.exp(-3 * pos_error)

        return reward
     
    # Publish Setpoint
     
    def publish_setpoint(self, vx, vy, vz, yaw_rate):

        msg = TrajectorySetpoint()
        msg.velocity = [
            float(vx),
            float(vy),
            float(vz)
        ]

        msg.yawspeed = float(yaw_rate)

        self.pub.publish(msg)


 
# Main
 
def main(args=None):
    rclpy.init(args=args)

    node = RLHoverNode()
    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
