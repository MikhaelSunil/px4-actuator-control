# PX4 Quadrotor Control — Actuator-Level COntrol & RL  Hover Training

**Author:** Mikhael Sunil  
**Platform:** PX4 X500 Quadrotor · Gazebo Harmonic · ROS 2 Jazzy  
**Repo:** [MikhaelSunil/px4-actuator-control](https://github.com/MikhaelSunil/px4-actuator-control)

---

## Overview

This repository covers two quadrotor control tasks implemented in PX4 SITL:

- **Task A** — Actuator-level control via direct motor commands, no PX4 internal controllers
- **Task B** — Learning-based hover policy using an online Actor-Critic RL agent

Both run over ROS 2 using `px4_msgs` and Micro XRCE-DDS as the PX4 ↔ ROS 2 bridge.

---

## Task A: Actuator-Level Control

### What It Does

A cascaded controller publishes motor throttle commands directly to `/fmu/in/actuator_motors`, bypassing PX4's built-in attitude and position controllers entirely. It executes a four-phase mission:

1. **Takeoff** — climb to 3 m with proportional vertical velocity control
2. **Hover** — hold position with XY damping
3. **Forward motion** — translate 3 m in the heading direction via tilt-based velocity control
4. **Landing** — constant descent at −0.15 m/s with body-frame XY damping, auto-disarm on touchdown

### Control Architecture

```
Position error → Velocity setpoint (outer loop)
Velocity error → Acceleration setpoint (PD)
Acceleration direction → Desired tilt (roll, pitch)
Angular velocity → Rate damping torques (inner loop)
[T, τ_x, τ_y, τ_z] → Motor commands via pseudo-inverse mixer
```

**Motor mixer** uses the X500 actuator effectiveness matrix B (arm length = 0.25 m, torque-to-thrust ratio = 0.05). Motor commands are solved with the Moore-Penrose pseudo-inverse and clipped to [0, 1].

### State Machine

| State | Action | Exit Condition |
|-------|--------|----------------|
| WARMUP | Publish idle motors at 50 Hz for 1.5 s | Elapsed cycles |
| OFFBOARD | Send `DO_SET_MODE` every 10 cycles | `nav_state == OFFBOARD` |
| ARMING | Send ARM command, retry every 10 cycles | `arming_state == ARMED` |
| climb | Vertical velocity control to z = 3 m | `|err_z| < 0.3 m` |
| hover | XY position lock | `vel_xy < 0.1 m/s`, `pos_err < 0.3 m` for 2 s |
| waypoint | Tilt-based forward navigation | `dist < 0.3 m`, `vel_xy < 0.1 m/s` |
| land | Fixed descent, XY damping, auto-disarm | `height < 0.08 m`, `|vel_z| < 0.1 m/s` |

### Coordinate Frames

PX4 outputs odometry in NED. All controller logic runs in ENU. Conversion happens once per odometry callback:

```python
pos_enu = [pos_ned[1],  pos_ned[0], -pos_ned[2]]
vel_enu = [vel_ned[1],  vel_ned[0], -vel_ned[2]]
yaw_enu = π/2 - yaw_ned
```

### Setup and Launch

```bash
colcon build --symlink-install
source install/setup.bash
ros2 launch px4_actuator_ctrl offboard.launch.py
```

### Results
<img width="1893" height="491" alt="Screenshot from 2026-05-03 17-11-49" src="https://github.com/user-attachments/assets/e92e966c-4d2a-4acc-b8cd-a6849db0ab1c" />

<img width="1213" height="836" alt="Screenshot from 2026-05-03 15-53-08" src="https://github.com/user-attachments/assets/47a9d6d3-14b5-435a-bd35-62cb11522461" />

- Takeoff reached 3 m smoothly with no oscillations
- Hover held within ~0.3 m of the takeoff point
- Forward motion covered ~3 m in the heading direction
- Landing descended at −0.15 m/s and touched down without spiraling

**Known limitations:** The waypoint phase overshoots slightly before settling — the braking radius (0.2 m) is narrow relative to cruise speed. The phase transition from hover to forward motion causes a brief tilt spike that the EMA filter reduces but does not eliminate. Both are tuning issues, not structural ones.

---

## Task B: Learning-Based Hover Policy

### What It Does

An online Actor-Critic RL agent runs inside a ROS 2 node and learns to hover at a fixed target position (x=0, y=0, z=−2 m in NED). It outputs velocity setpoints to `/fmu/in/trajectory_setpoint`, blended with a decaying PD baseline for safe initial exploration.

### Neural Network

Shared-backbone Actor-Critic with two 128-unit hidden layers:

| Layer | Type | In → Out |
|-------|------|----------|
| Shared FC 1 | Linear + ReLU | 12 → 128 |
| Shared FC 2 | Linear + ReLU | 128 → 128 |
| Actor Mean | Linear | 128 → 4 |
| Actor Log Std | Learnable parameter | — → 4 |
| Critic | Linear | 128 → 1 |

**State (12-dim):** position (÷5.0), velocity (÷3.0), orientation quaternion q[0], angular velocity  
**Action (4-dim):** velocity commands [vx, vy, vz] and yaw rate

### PD-RL Blended Control

The RL output is blended with a proportional baseline using a decaying weight:

```python
decay = max(0.3, 0.9 - step / 80000)
v_cmd = decay * PD_output + (1 - decay) * RL_output
```

PD influence starts at 0.9 and decays to a floor of 0.3, guaranteeing a minimum level of stability throughout training.

### Reward Function

```
R = -‖pos − target‖ − 0.3·‖vel‖ − 5.0·|z + 2| + exp(−3·‖pos − target‖)
```

| Term | Weight | Purpose |
|------|--------|---------|
| −‖pos − target‖ | 1.0 | Position accuracy |
| −0.3·‖vel‖ | 0.3 | Velocity damping |
| −5.0·\|z + 2\| | 5.0 | Altitude tracking (strong penalty) |
| exp(−3·pos_error) | 1.0 | Dense proximity bonus |

### Training Configuration

| Hyperparameter | Value |
|----------------|-------|
| Algorithm | Online Actor-Critic (A2C-style) |
| Optimizer | Adam, lr = 3e-4 |
| Discount factor | 0.99 |
| Entropy coefficient | 0.01 |
| Max steps | 50,000 |
| Advantage clipping | [−5, 5] |
| Log std clipping | [0.1, 1.0] |
| Warmup steps | 200 |

### Training Results

At ~2,500 steps:

- **Reward** climbed from −10/−11 to ~−2.5 (steps 500–1800), then dropped as PD influence decayed and RL authority increased before convergence
- **Position error** improved from ~1.8 m to ~0.5 m at best, then rose again past step 1800
- **Control influence** shows PD near 0.9 throughout — expected, since 2,500 of 50,000 steps have elapsed

The agent is not yet converged. Longer training is needed for the RL policy to stabilize independently of the PD baseline.

![Training curves](<img width="1898" height="503" alt="Screenshot from 2026-05-03 22-33-28" src="https://github.com/user-attachments/assets/3515354f-ddde-4412-a9dc-835ecba67055" />

*Figure: Reward (top), Position Error (middle), PD vs RL Control Influence (bottom)*

### Sim-to-Sim Transfer

The current policy trains in PX4 SITL (Gazebo Harmonic backend). Candidate transfer targets:

- **Isaac Lab** — GPU-accelerated, ROS 2 bridge, good for parallel training
- **Webots** — open-source, ROS 2 native, quadrotor models available
- **AirSim** — photorealistic, PX4 SITL compatible

The velocity-setpoint action space (no actuator dynamics) aids transferability. State normalization constants may need recalibration per simulator.

### Run

```bash
# From the ROS 2 workspace
python3 rl_hover_node.py
```

The node arms the drone automatically after 20 odometry callbacks and plots reward, error, and control influence in real time.

---

## Limitations and Future Work

**Task A**
- Widen the braking zone and lower cruise speed to reduce waypoint overshoot
- Replace the fixed landing descent rate with an altitude-scaled velocity profile for a cleaner touchdown
- Add PID auto-tuning (Ziegler–Nichols or optimization-based) to replace manual gain selection
- Consider Model Predictive Control for smooth deceleration without overshoot

**Task B**
- Switch to SAC (Soft Actor-Critic) for off-policy learning with lower variance
- Add episode reset logic (land + re-arm) so the agent trains across proper episodes
- Use the full quaternion or Euler angles in the state vector — currently only q[0] is used
- Add domain randomization to improve policy robustness
- Log to TensorBoard or Weights & Biases for richer training diagnostics

---

## Repository Structure

```
px4-actuator-control/
├── px4_actuator_ctrl/
│   ├── actuator_ctrl_node.py   # Task A: cascaded motor-level controller
│   └── px4_visualizer.py       
├── launch/
│   └── offboard.launch.py
├── rl_hover_pkg/
│   ├── rl_hover_node.py  # Task B: Actor-Critic hover policy
├── training_plot.png
└── README.md
```

---

## Dependencies

- PX4-Autopilot (SITL)
- ROS 2 Jazzy
- Micro XRCE-DDS Agent
- `px4_msgs`
- PyTorch
- Gazebo Harmonic
