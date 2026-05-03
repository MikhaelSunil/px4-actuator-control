#ifndef PX4_MSGS_ALL_MESSAGES_HPP
#define PX4_MSGS_ALL_MESSAGES_HPP

// Auto-generated header including all PX4 message types
#include <px4_msgs/msg/action_request.hpp>
#include <px4_msgs/msg/actuator_armed.hpp>
#include <px4_msgs/msg/actuator_controls_status.hpp>
#include <px4_msgs/msg/actuator_motors.hpp>
#include <px4_msgs/msg/actuator_outputs.hpp>
#include <px4_msgs/msg/actuator_servos.hpp>
#include <px4_msgs/msg/actuator_servos_trim.hpp>
#include <px4_msgs/msg/actuator_test.hpp>
#include <px4_msgs/msg/adc_report.hpp>
#include <px4_msgs/msg/airspeed.hpp>
#include <px4_msgs/msg/airspeed_validated.hpp>
#include <px4_msgs/msg/airspeed_wind.hpp>
#include <px4_msgs/msg/arming_check_reply.hpp>
#include <px4_msgs/msg/arming_check_request.hpp>
#include <px4_msgs/msg/autotune_attitude_control_status.hpp>
#include <px4_msgs/msg/aux_global_position.hpp>
#include <px4_msgs/msg/battery_info.hpp>
#include <px4_msgs/msg/battery_status.hpp>
#include <px4_msgs/msg/button_event.hpp>
#include <px4_msgs/msg/camera_capture.hpp>
#include <px4_msgs/msg/camera_status.hpp>
#include <px4_msgs/msg/camera_trigger.hpp>
#include <px4_msgs/msg/can_interface_status.hpp>
#include <px4_msgs/msg/cellular_status.hpp>
#include <px4_msgs/msg/collision_constraints.hpp>
#include <px4_msgs/msg/config_overrides.hpp>
#include <px4_msgs/msg/control_allocator_status.hpp>
#include <px4_msgs/msg/cpuload.hpp>
#include <px4_msgs/msg/dataman_request.hpp>
#include <px4_msgs/msg/dataman_response.hpp>
#include <px4_msgs/msg/debug_array.hpp>
#include <px4_msgs/msg/debug_key_value.hpp>
#include <px4_msgs/msg/debug_value.hpp>
#include <px4_msgs/msg/debug_vect.hpp>
#include <px4_msgs/msg/device_information.hpp>
#include <px4_msgs/msg/differential_pressure.hpp>
#include <px4_msgs/msg/distance_sensor.hpp>
#include <px4_msgs/msg/distance_sensor_mode_change_request.hpp>
#include <px4_msgs/msg/dronecan_node_status.hpp>
#include <px4_msgs/msg/ekf2_timestamps.hpp>
#include <px4_msgs/msg/esc_eeprom_read.hpp>
#include <px4_msgs/msg/esc_eeprom_write.hpp>
#include <px4_msgs/msg/esc_report.hpp>
#include <px4_msgs/msg/esc_status.hpp>
#include <px4_msgs/msg/estimator_aid_source1d.hpp>
#include <px4_msgs/msg/estimator_aid_source2d.hpp>
#include <px4_msgs/msg/estimator_aid_source3d.hpp>
#include <px4_msgs/msg/estimator_bias.hpp>
#include <px4_msgs/msg/estimator_bias3d.hpp>
#include <px4_msgs/msg/estimator_event_flags.hpp>
#include <px4_msgs/msg/estimator_fusion_control.hpp>
#include <px4_msgs/msg/estimator_gps_status.hpp>
#include <px4_msgs/msg/estimator_innovations.hpp>
#include <px4_msgs/msg/estimator_selector_status.hpp>
#include <px4_msgs/msg/estimator_sensor_bias.hpp>
#include <px4_msgs/msg/estimator_states.hpp>
#include <px4_msgs/msg/estimator_status.hpp>
#include <px4_msgs/msg/estimator_status_flags.hpp>
#include <px4_msgs/msg/event.hpp>
#include <px4_msgs/msg/failsafe_flags.hpp>
#include <px4_msgs/msg/failure_detector_status.hpp>
#include <px4_msgs/msg/figure_eight_status.hpp>
#include <px4_msgs/msg/fixed_wing_lateral_guidance_status.hpp>
#include <px4_msgs/msg/fixed_wing_lateral_setpoint.hpp>
#include <px4_msgs/msg/fixed_wing_lateral_status.hpp>
#include <px4_msgs/msg/fixed_wing_longitudinal_setpoint.hpp>
#include <px4_msgs/msg/fixed_wing_runway_control.hpp>
#include <px4_msgs/msg/flight_phase_estimation.hpp>
#include <px4_msgs/msg/follow_target.hpp>
#include <px4_msgs/msg/follow_target_estimator.hpp>
#include <px4_msgs/msg/follow_target_status.hpp>
#include <px4_msgs/msg/fuel_tank_status.hpp>
#include <px4_msgs/msg/gain_compression.hpp>
#include <px4_msgs/msg/generator_status.hpp>
#include <px4_msgs/msg/geofence_result.hpp>
#include <px4_msgs/msg/geofence_status.hpp>
#include <px4_msgs/msg/gimbal_controls.hpp>
#include <px4_msgs/msg/gimbal_device_attitude_status.hpp>
#include <px4_msgs/msg/gimbal_device_information.hpp>
#include <px4_msgs/msg/gimbal_device_set_attitude.hpp>
#include <px4_msgs/msg/gimbal_manager_information.hpp>
#include <px4_msgs/msg/gimbal_manager_set_attitude.hpp>
#include <px4_msgs/msg/gimbal_manager_set_manual_control.hpp>
#include <px4_msgs/msg/gimbal_manager_status.hpp>
#include <px4_msgs/msg/goto_setpoint.hpp>
#include <px4_msgs/msg/gpio_config.hpp>
#include <px4_msgs/msg/gpio_in.hpp>
#include <px4_msgs/msg/gpio_out.hpp>
#include <px4_msgs/msg/gpio_request.hpp>
#include <px4_msgs/msg/gps_dump.hpp>
#include <px4_msgs/msg/gps_inject_data.hpp>
#include <px4_msgs/msg/gripper.hpp>
#include <px4_msgs/msg/health_report.hpp>
#include <px4_msgs/msg/heater_status.hpp>
#include <px4_msgs/msg/home_position.hpp>
#include <px4_msgs/msg/hover_thrust_estimate.hpp>
#include <px4_msgs/msg/input_rc.hpp>
#include <px4_msgs/msg/internal_combustion_engine_control.hpp>
#include <px4_msgs/msg/internal_combustion_engine_status.hpp>
#include <px4_msgs/msg/iridiumsbd_status.hpp>
#include <px4_msgs/msg/irlock_report.hpp>
#include <px4_msgs/msg/landing_gear.hpp>
#include <px4_msgs/msg/landing_gear_wheel.hpp>
#include <px4_msgs/msg/landing_target_innovations.hpp>
#include <px4_msgs/msg/landing_target_pose.hpp>
#include <px4_msgs/msg/lateral_control_configuration.hpp>
#include <px4_msgs/msg/launch_detection_status.hpp>
#include <px4_msgs/msg/led_control.hpp>
#include <px4_msgs/msg/log_message.hpp>
#include <px4_msgs/msg/logger_status.hpp>
#include <px4_msgs/msg/longitudinal_control_configuration.hpp>
#include <px4_msgs/msg/mag_worker_data.hpp>
#include <px4_msgs/msg/magnetometer_bias_estimate.hpp>
#include <px4_msgs/msg/manual_control_setpoint.hpp>
#include <px4_msgs/msg/manual_control_switches.hpp>
#include <px4_msgs/msg/mavlink_log.hpp>
#include <px4_msgs/msg/mavlink_tunnel.hpp>
#include <px4_msgs/msg/message_format_request.hpp>
#include <px4_msgs/msg/message_format_response.hpp>
#include <px4_msgs/msg/mission.hpp>
#include <px4_msgs/msg/mission_result.hpp>
#include <px4_msgs/msg/mode_completed.hpp>
#include <px4_msgs/msg/mount_orientation.hpp>
#include <px4_msgs/msg/navigator_mission_item.hpp>
#include <px4_msgs/msg/navigator_status.hpp>
#include <px4_msgs/msg/neural_control.hpp>
#include <px4_msgs/msg/normalized_unsigned_setpoint.hpp>
#include <px4_msgs/msg/obstacle_distance.hpp>
#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/onboard_computer_status.hpp>
#include <px4_msgs/msg/open_drone_id_arm_status.hpp>
#include <px4_msgs/msg/open_drone_id_operator_id.hpp>
#include <px4_msgs/msg/open_drone_id_self_id.hpp>
#include <px4_msgs/msg/open_drone_id_system.hpp>
#include <px4_msgs/msg/orb_test.hpp>
#include <px4_msgs/msg/orb_test_large.hpp>
#include <px4_msgs/msg/orb_test_medium.hpp>
#include <px4_msgs/msg/orbit_status.hpp>
#include <px4_msgs/msg/parameter_reset_request.hpp>
#include <px4_msgs/msg/parameter_set_used_request.hpp>
#include <px4_msgs/msg/parameter_set_value_request.hpp>
#include <px4_msgs/msg/parameter_set_value_response.hpp>
#include <px4_msgs/msg/parameter_update.hpp>
#include <px4_msgs/msg/ping.hpp>
#include <px4_msgs/msg/position_controller_landing_status.hpp>
#include <px4_msgs/msg/position_controller_status.hpp>
#include <px4_msgs/msg/position_setpoint.hpp>
#include <px4_msgs/msg/position_setpoint_triplet.hpp>
#include <px4_msgs/msg/power_button_state.hpp>
#include <px4_msgs/msg/power_monitor.hpp>
#include <px4_msgs/msg/pps_capture.hpp>
#include <px4_msgs/msg/pure_pursuit_status.hpp>
#include <px4_msgs/msg/pwm_input.hpp>
#include <px4_msgs/msg/px4io_status.hpp>
#include <px4_msgs/msg/qshell_req.hpp>
#include <px4_msgs/msg/qshell_retval.hpp>
#include <px4_msgs/msg/radio_status.hpp>
#include <px4_msgs/msg/ranging_beacon.hpp>
#include <px4_msgs/msg/raptor_input.hpp>
#include <px4_msgs/msg/raptor_status.hpp>
#include <px4_msgs/msg/rate_ctrl_status.hpp>
#include <px4_msgs/msg/rc_channels.hpp>
#include <px4_msgs/msg/rc_parameter_map.hpp>
#include <px4_msgs/msg/register_ext_component_reply.hpp>
#include <px4_msgs/msg/register_ext_component_request.hpp>
#include <px4_msgs/msg/rover_attitude_setpoint.hpp>
#include <px4_msgs/msg/rover_attitude_status.hpp>
#include <px4_msgs/msg/rover_position_setpoint.hpp>
#include <px4_msgs/msg/rover_rate_setpoint.hpp>
#include <px4_msgs/msg/rover_rate_status.hpp>
#include <px4_msgs/msg/rover_speed_setpoint.hpp>
#include <px4_msgs/msg/rover_speed_status.hpp>
#include <px4_msgs/msg/rover_steering_setpoint.hpp>
#include <px4_msgs/msg/rover_throttle_setpoint.hpp>
#include <px4_msgs/msg/rpm.hpp>
#include <px4_msgs/msg/rtl_status.hpp>
#include <px4_msgs/msg/rtl_time_estimate.hpp>
#include <px4_msgs/msg/satellite_info.hpp>
#include <px4_msgs/msg/sensor_accel.hpp>
#include <px4_msgs/msg/sensor_accel_fifo.hpp>
#include <px4_msgs/msg/sensor_airflow.hpp>
#include <px4_msgs/msg/sensor_baro.hpp>
#include <px4_msgs/msg/sensor_combined.hpp>
#include <px4_msgs/msg/sensor_correction.hpp>
#include <px4_msgs/msg/sensor_gnss_relative.hpp>
#include <px4_msgs/msg/sensor_gnss_status.hpp>
#include <px4_msgs/msg/sensor_gps.hpp>
#include <px4_msgs/msg/sensor_gyro.hpp>
#include <px4_msgs/msg/sensor_gyro_fft.hpp>
#include <px4_msgs/msg/sensor_gyro_fifo.hpp>
#include <px4_msgs/msg/sensor_hygrometer.hpp>
#include <px4_msgs/msg/sensor_mag.hpp>
#include <px4_msgs/msg/sensor_optical_flow.hpp>
#include <px4_msgs/msg/sensor_preflight_mag.hpp>
#include <px4_msgs/msg/sensor_selection.hpp>
#include <px4_msgs/msg/sensor_temp.hpp>
#include <px4_msgs/msg/sensor_uwb.hpp>
#include <px4_msgs/msg/sensors_status.hpp>
#include <px4_msgs/msg/sensors_status_imu.hpp>
#include <px4_msgs/msg/system_power.hpp>
#include <px4_msgs/msg/takeoff_status.hpp>
#include <px4_msgs/msg/task_stack_info.hpp>
#include <px4_msgs/msg/tecs_status.hpp>
#include <px4_msgs/msg/telemetry_status.hpp>
#include <px4_msgs/msg/tiltrotor_extra_controls.hpp>
#include <px4_msgs/msg/timesync_status.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>
#include <px4_msgs/msg/trajectory_setpoint6dof.hpp>
#include <px4_msgs/msg/transponder_report.hpp>
#include <px4_msgs/msg/tune_control.hpp>
#include <px4_msgs/msg/uavcan_parameter_request.hpp>
#include <px4_msgs/msg/uavcan_parameter_value.hpp>
#include <px4_msgs/msg/ulog_stream.hpp>
#include <px4_msgs/msg/ulog_stream_ack.hpp>
#include <px4_msgs/msg/unregister_ext_component.hpp>
#include <px4_msgs/msg/vehicle_acceleration.hpp>
#include <px4_msgs/msg/vehicle_air_data.hpp>
#include <px4_msgs/msg/vehicle_angular_acceleration_setpoint.hpp>
#include <px4_msgs/msg/vehicle_angular_velocity.hpp>
#include <px4_msgs/msg/vehicle_attitude.hpp>
#include <px4_msgs/msg/vehicle_attitude_setpoint.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/vehicle_command_ack.hpp>
#include <px4_msgs/msg/vehicle_constraints.hpp>
#include <px4_msgs/msg/vehicle_control_mode.hpp>
#include <px4_msgs/msg/vehicle_global_position.hpp>
#include <px4_msgs/msg/vehicle_imu.hpp>
#include <px4_msgs/msg/vehicle_imu_status.hpp>
#include <px4_msgs/msg/vehicle_land_detected.hpp>
#include <px4_msgs/msg/vehicle_local_position.hpp>
#include <px4_msgs/msg/vehicle_local_position_setpoint.hpp>
#include <px4_msgs/msg/vehicle_magnetometer.hpp>
#include <px4_msgs/msg/vehicle_odometry.hpp>
#include <px4_msgs/msg/vehicle_optical_flow.hpp>
#include <px4_msgs/msg/vehicle_optical_flow_vel.hpp>
#include <px4_msgs/msg/vehicle_rates_setpoint.hpp>
#include <px4_msgs/msg/vehicle_roi.hpp>
#include <px4_msgs/msg/vehicle_status.hpp>
#include <px4_msgs/msg/vehicle_thrust_setpoint.hpp>
#include <px4_msgs/msg/vehicle_torque_setpoint.hpp>
#include <px4_msgs/msg/velocity_limits.hpp>
#include <px4_msgs/msg/vtol_vehicle_status.hpp>
#include <px4_msgs/msg/vtx.hpp>
#include <px4_msgs/msg/wheel_encoders.hpp>
#include <px4_msgs/msg/wind.hpp>
#include <px4_msgs/msg/yaw_estimator_status.hpp>

struct TopicTypeSupport
{
  const char * topic_type_name;
  const rosidl_message_type_support_t * ts_handle;
};

static TopicTypeSupport all_px4_ros2_messages[] = {
  {"px4_msgs/msg/ActionRequest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ActionRequest>()},
  {"px4_msgs/msg/ActuatorArmed",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ActuatorArmed>()},
  {"px4_msgs/msg/ActuatorControlsStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ActuatorControlsStatus>()},
  {"px4_msgs/msg/ActuatorMotors",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ActuatorMotors>()},
  {"px4_msgs/msg/ActuatorOutputs",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ActuatorOutputs>()},
  {"px4_msgs/msg/ActuatorServos",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ActuatorServos>()},
  {"px4_msgs/msg/ActuatorServosTrim",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ActuatorServosTrim>()},
  {"px4_msgs/msg/ActuatorTest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ActuatorTest>()},
  {"px4_msgs/msg/AdcReport",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::AdcReport>()},
  {"px4_msgs/msg/Airspeed",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::Airspeed>()},
  {"px4_msgs/msg/AirspeedValidated",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::AirspeedValidated>()},
  {"px4_msgs/msg/AirspeedWind",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::AirspeedWind>()},
  {"px4_msgs/msg/ArmingCheckReply",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ArmingCheckReply>()},
  {"px4_msgs/msg/ArmingCheckRequest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ArmingCheckRequest>()},
  {"px4_msgs/msg/AutotuneAttitudeControlStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::AutotuneAttitudeControlStatus>()},
  {"px4_msgs/msg/AuxGlobalPosition",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::AuxGlobalPosition>()},
  {"px4_msgs/msg/BatteryInfo",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::BatteryInfo>()},
  {"px4_msgs/msg/BatteryStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::BatteryStatus>()},
  {"px4_msgs/msg/ButtonEvent",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ButtonEvent>()},
  {"px4_msgs/msg/CameraCapture",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::CameraCapture>()},
  {"px4_msgs/msg/CameraStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::CameraStatus>()},
  {"px4_msgs/msg/CameraTrigger",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::CameraTrigger>()},
  {"px4_msgs/msg/CanInterfaceStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::CanInterfaceStatus>()},
  {"px4_msgs/msg/CellularStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::CellularStatus>()},
  {"px4_msgs/msg/CollisionConstraints",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::CollisionConstraints>()},
  {"px4_msgs/msg/ConfigOverrides",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ConfigOverrides>()},
  {"px4_msgs/msg/ControlAllocatorStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ControlAllocatorStatus>()},
  {"px4_msgs/msg/Cpuload",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::Cpuload>()},
  {"px4_msgs/msg/DatamanRequest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::DatamanRequest>()},
  {"px4_msgs/msg/DatamanResponse",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::DatamanResponse>()},
  {"px4_msgs/msg/DebugArray",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::DebugArray>()},
  {"px4_msgs/msg/DebugKeyValue",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::DebugKeyValue>()},
  {"px4_msgs/msg/DebugValue",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::DebugValue>()},
  {"px4_msgs/msg/DebugVect",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::DebugVect>()},
  {"px4_msgs/msg/DeviceInformation",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::DeviceInformation>()},
  {"px4_msgs/msg/DifferentialPressure",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::DifferentialPressure>()},
  {"px4_msgs/msg/DistanceSensor",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::DistanceSensor>()},
  {"px4_msgs/msg/DistanceSensorModeChangeRequest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::DistanceSensorModeChangeRequest>()},
  {"px4_msgs/msg/DronecanNodeStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::DronecanNodeStatus>()},
  {"px4_msgs/msg/Ekf2Timestamps",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::Ekf2Timestamps>()},
  {"px4_msgs/msg/EscEepromRead",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EscEepromRead>()},
  {"px4_msgs/msg/EscEepromWrite",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EscEepromWrite>()},
  {"px4_msgs/msg/EscReport",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EscReport>()},
  {"px4_msgs/msg/EscStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EscStatus>()},
  {"px4_msgs/msg/EstimatorAidSource1d",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorAidSource1d>()},
  {"px4_msgs/msg/EstimatorAidSource2d",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorAidSource2d>()},
  {"px4_msgs/msg/EstimatorAidSource3d",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorAidSource3d>()},
  {"px4_msgs/msg/EstimatorBias",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorBias>()},
  {"px4_msgs/msg/EstimatorBias3d",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorBias3d>()},
  {"px4_msgs/msg/EstimatorEventFlags",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorEventFlags>()},
  {"px4_msgs/msg/EstimatorFusionControl",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorFusionControl>()},
  {"px4_msgs/msg/EstimatorGpsStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorGpsStatus>()},
  {"px4_msgs/msg/EstimatorInnovations",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorInnovations>()},
  {"px4_msgs/msg/EstimatorSelectorStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorSelectorStatus>()},
  {"px4_msgs/msg/EstimatorSensorBias",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorSensorBias>()},
  {"px4_msgs/msg/EstimatorStates",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorStates>()},
  {"px4_msgs/msg/EstimatorStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorStatus>()},
  {"px4_msgs/msg/EstimatorStatusFlags",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::EstimatorStatusFlags>()},
  {"px4_msgs/msg/Event",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::Event>()},
  {"px4_msgs/msg/FailsafeFlags",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FailsafeFlags>()},
  {"px4_msgs/msg/FailureDetectorStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FailureDetectorStatus>()},
  {"px4_msgs/msg/FigureEightStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FigureEightStatus>()},
  {"px4_msgs/msg/FixedWingLateralGuidanceStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FixedWingLateralGuidanceStatus>()},
  {"px4_msgs/msg/FixedWingLateralSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FixedWingLateralSetpoint>()},
  {"px4_msgs/msg/FixedWingLateralStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FixedWingLateralStatus>()},
  {"px4_msgs/msg/FixedWingLongitudinalSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FixedWingLongitudinalSetpoint>()},
  {"px4_msgs/msg/FixedWingRunwayControl",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FixedWingRunwayControl>()},
  {"px4_msgs/msg/FlightPhaseEstimation",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FlightPhaseEstimation>()},
  {"px4_msgs/msg/FollowTarget",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FollowTarget>()},
  {"px4_msgs/msg/FollowTargetEstimator",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FollowTargetEstimator>()},
  {"px4_msgs/msg/FollowTargetStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FollowTargetStatus>()},
  {"px4_msgs/msg/FuelTankStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::FuelTankStatus>()},
  {"px4_msgs/msg/GainCompression",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GainCompression>()},
  {"px4_msgs/msg/GeneratorStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GeneratorStatus>()},
  {"px4_msgs/msg/GeofenceResult",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GeofenceResult>()},
  {"px4_msgs/msg/GeofenceStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GeofenceStatus>()},
  {"px4_msgs/msg/GimbalControls",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GimbalControls>()},
  {"px4_msgs/msg/GimbalDeviceAttitudeStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GimbalDeviceAttitudeStatus>()},
  {"px4_msgs/msg/GimbalDeviceInformation",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GimbalDeviceInformation>()},
  {"px4_msgs/msg/GimbalDeviceSetAttitude",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GimbalDeviceSetAttitude>()},
  {"px4_msgs/msg/GimbalManagerInformation",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GimbalManagerInformation>()},
  {"px4_msgs/msg/GimbalManagerSetAttitude",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GimbalManagerSetAttitude>()},
  {"px4_msgs/msg/GimbalManagerSetManualControl",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GimbalManagerSetManualControl>()},
  {"px4_msgs/msg/GimbalManagerStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GimbalManagerStatus>()},
  {"px4_msgs/msg/GotoSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GotoSetpoint>()},
  {"px4_msgs/msg/GpioConfig",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GpioConfig>()},
  {"px4_msgs/msg/GpioIn",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GpioIn>()},
  {"px4_msgs/msg/GpioOut",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GpioOut>()},
  {"px4_msgs/msg/GpioRequest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GpioRequest>()},
  {"px4_msgs/msg/GpsDump",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GpsDump>()},
  {"px4_msgs/msg/GpsInjectData",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::GpsInjectData>()},
  {"px4_msgs/msg/Gripper",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::Gripper>()},
  {"px4_msgs/msg/HealthReport",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::HealthReport>()},
  {"px4_msgs/msg/HeaterStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::HeaterStatus>()},
  {"px4_msgs/msg/HomePosition",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::HomePosition>()},
  {"px4_msgs/msg/HoverThrustEstimate",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::HoverThrustEstimate>()},
  {"px4_msgs/msg/InputRc",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::InputRc>()},
  {"px4_msgs/msg/InternalCombustionEngineControl",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::InternalCombustionEngineControl>()},
  {"px4_msgs/msg/InternalCombustionEngineStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::InternalCombustionEngineStatus>()},
  {"px4_msgs/msg/IridiumsbdStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::IridiumsbdStatus>()},
  {"px4_msgs/msg/IrlockReport",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::IrlockReport>()},
  {"px4_msgs/msg/LandingGear",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::LandingGear>()},
  {"px4_msgs/msg/LandingGearWheel",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::LandingGearWheel>()},
  {"px4_msgs/msg/LandingTargetInnovations",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::LandingTargetInnovations>()},
  {"px4_msgs/msg/LandingTargetPose",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::LandingTargetPose>()},
  {"px4_msgs/msg/LateralControlConfiguration",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::LateralControlConfiguration>()},
  {"px4_msgs/msg/LaunchDetectionStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::LaunchDetectionStatus>()},
  {"px4_msgs/msg/LedControl",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::LedControl>()},
  {"px4_msgs/msg/LogMessage",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::LogMessage>()},
  {"px4_msgs/msg/LoggerStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::LoggerStatus>()},
  {"px4_msgs/msg/LongitudinalControlConfiguration",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::LongitudinalControlConfiguration>()},
  {"px4_msgs/msg/MagWorkerData",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::MagWorkerData>()},
  {"px4_msgs/msg/MagnetometerBiasEstimate",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::MagnetometerBiasEstimate>()},
  {"px4_msgs/msg/ManualControlSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ManualControlSetpoint>()},
  {"px4_msgs/msg/ManualControlSwitches",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ManualControlSwitches>()},
  {"px4_msgs/msg/MavlinkLog",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::MavlinkLog>()},
  {"px4_msgs/msg/MavlinkTunnel",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::MavlinkTunnel>()},
  {"px4_msgs/msg/MessageFormatRequest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::MessageFormatRequest>()},
  {"px4_msgs/msg/MessageFormatResponse",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::MessageFormatResponse>()},
  {"px4_msgs/msg/Mission",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::Mission>()},
  {"px4_msgs/msg/MissionResult",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::MissionResult>()},
  {"px4_msgs/msg/ModeCompleted",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ModeCompleted>()},
  {"px4_msgs/msg/MountOrientation",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::MountOrientation>()},
  {"px4_msgs/msg/NavigatorMissionItem",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::NavigatorMissionItem>()},
  {"px4_msgs/msg/NavigatorStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::NavigatorStatus>()},
  {"px4_msgs/msg/NeuralControl",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::NeuralControl>()},
  {"px4_msgs/msg/NormalizedUnsignedSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::NormalizedUnsignedSetpoint>()},
  {"px4_msgs/msg/ObstacleDistance",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ObstacleDistance>()},
  {"px4_msgs/msg/OffboardControlMode",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::OffboardControlMode>()},
  {"px4_msgs/msg/OnboardComputerStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::OnboardComputerStatus>()},
  {"px4_msgs/msg/OpenDroneIdArmStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::OpenDroneIdArmStatus>()},
  {"px4_msgs/msg/OpenDroneIdOperatorId",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::OpenDroneIdOperatorId>()},
  {"px4_msgs/msg/OpenDroneIdSelfId",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::OpenDroneIdSelfId>()},
  {"px4_msgs/msg/OpenDroneIdSystem",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::OpenDroneIdSystem>()},
  {"px4_msgs/msg/OrbTest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::OrbTest>()},
  {"px4_msgs/msg/OrbTestLarge",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::OrbTestLarge>()},
  {"px4_msgs/msg/OrbTestMedium",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::OrbTestMedium>()},
  {"px4_msgs/msg/OrbitStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::OrbitStatus>()},
  {"px4_msgs/msg/ParameterResetRequest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ParameterResetRequest>()},
  {"px4_msgs/msg/ParameterSetUsedRequest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ParameterSetUsedRequest>()},
  {"px4_msgs/msg/ParameterSetValueRequest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ParameterSetValueRequest>()},
  {"px4_msgs/msg/ParameterSetValueResponse",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ParameterSetValueResponse>()},
  {"px4_msgs/msg/ParameterUpdate",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::ParameterUpdate>()},
  {"px4_msgs/msg/Ping",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::Ping>()},
  {"px4_msgs/msg/PositionControllerLandingStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::PositionControllerLandingStatus>()},
  {"px4_msgs/msg/PositionControllerStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::PositionControllerStatus>()},
  {"px4_msgs/msg/PositionSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::PositionSetpoint>()},
  {"px4_msgs/msg/PositionSetpointTriplet",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::PositionSetpointTriplet>()},
  {"px4_msgs/msg/PowerButtonState",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::PowerButtonState>()},
  {"px4_msgs/msg/PowerMonitor",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::PowerMonitor>()},
  {"px4_msgs/msg/PpsCapture",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::PpsCapture>()},
  {"px4_msgs/msg/PurePursuitStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::PurePursuitStatus>()},
  {"px4_msgs/msg/PwmInput",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::PwmInput>()},
  {"px4_msgs/msg/Px4ioStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::Px4ioStatus>()},
  {"px4_msgs/msg/QshellReq",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::QshellReq>()},
  {"px4_msgs/msg/QshellRetval",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::QshellRetval>()},
  {"px4_msgs/msg/RadioStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RadioStatus>()},
  {"px4_msgs/msg/RangingBeacon",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RangingBeacon>()},
  {"px4_msgs/msg/RaptorInput",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RaptorInput>()},
  {"px4_msgs/msg/RaptorStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RaptorStatus>()},
  {"px4_msgs/msg/RateCtrlStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RateCtrlStatus>()},
  {"px4_msgs/msg/RcChannels",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RcChannels>()},
  {"px4_msgs/msg/RcParameterMap",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RcParameterMap>()},
  {"px4_msgs/msg/RegisterExtComponentReply",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RegisterExtComponentReply>()},
  {"px4_msgs/msg/RegisterExtComponentRequest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RegisterExtComponentRequest>()},
  {"px4_msgs/msg/RoverAttitudeSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RoverAttitudeSetpoint>()},
  {"px4_msgs/msg/RoverAttitudeStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RoverAttitudeStatus>()},
  {"px4_msgs/msg/RoverPositionSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RoverPositionSetpoint>()},
  {"px4_msgs/msg/RoverRateSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RoverRateSetpoint>()},
  {"px4_msgs/msg/RoverRateStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RoverRateStatus>()},
  {"px4_msgs/msg/RoverSpeedSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RoverSpeedSetpoint>()},
  {"px4_msgs/msg/RoverSpeedStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RoverSpeedStatus>()},
  {"px4_msgs/msg/RoverSteeringSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RoverSteeringSetpoint>()},
  {"px4_msgs/msg/RoverThrottleSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RoverThrottleSetpoint>()},
  {"px4_msgs/msg/Rpm",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::Rpm>()},
  {"px4_msgs/msg/RtlStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RtlStatus>()},
  {"px4_msgs/msg/RtlTimeEstimate",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::RtlTimeEstimate>()},
  {"px4_msgs/msg/SatelliteInfo",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SatelliteInfo>()},
  {"px4_msgs/msg/SensorAccel",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorAccel>()},
  {"px4_msgs/msg/SensorAccelFifo",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorAccelFifo>()},
  {"px4_msgs/msg/SensorAirflow",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorAirflow>()},
  {"px4_msgs/msg/SensorBaro",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorBaro>()},
  {"px4_msgs/msg/SensorCombined",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorCombined>()},
  {"px4_msgs/msg/SensorCorrection",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorCorrection>()},
  {"px4_msgs/msg/SensorGnssRelative",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorGnssRelative>()},
  {"px4_msgs/msg/SensorGnssStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorGnssStatus>()},
  {"px4_msgs/msg/SensorGps",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorGps>()},
  {"px4_msgs/msg/SensorGyro",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorGyro>()},
  {"px4_msgs/msg/SensorGyroFft",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorGyroFft>()},
  {"px4_msgs/msg/SensorGyroFifo",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorGyroFifo>()},
  {"px4_msgs/msg/SensorHygrometer",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorHygrometer>()},
  {"px4_msgs/msg/SensorMag",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorMag>()},
  {"px4_msgs/msg/SensorOpticalFlow",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorOpticalFlow>()},
  {"px4_msgs/msg/SensorPreflightMag",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorPreflightMag>()},
  {"px4_msgs/msg/SensorSelection",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorSelection>()},
  {"px4_msgs/msg/SensorTemp",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorTemp>()},
  {"px4_msgs/msg/SensorUwb",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorUwb>()},
  {"px4_msgs/msg/SensorsStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorsStatus>()},
  {"px4_msgs/msg/SensorsStatusImu",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SensorsStatusImu>()},
  {"px4_msgs/msg/SystemPower",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::SystemPower>()},
  {"px4_msgs/msg/TakeoffStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::TakeoffStatus>()},
  {"px4_msgs/msg/TaskStackInfo",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::TaskStackInfo>()},
  {"px4_msgs/msg/TecsStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::TecsStatus>()},
  {"px4_msgs/msg/TelemetryStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::TelemetryStatus>()},
  {"px4_msgs/msg/TiltrotorExtraControls",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::TiltrotorExtraControls>()},
  {"px4_msgs/msg/TimesyncStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::TimesyncStatus>()},
  {"px4_msgs/msg/TrajectorySetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::TrajectorySetpoint>()},
  {"px4_msgs/msg/TrajectorySetpoint6dof",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::TrajectorySetpoint6dof>()},
  {"px4_msgs/msg/TransponderReport",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::TransponderReport>()},
  {"px4_msgs/msg/TuneControl",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::TuneControl>()},
  {"px4_msgs/msg/UavcanParameterRequest",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::UavcanParameterRequest>()},
  {"px4_msgs/msg/UavcanParameterValue",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::UavcanParameterValue>()},
  {"px4_msgs/msg/UlogStream",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::UlogStream>()},
  {"px4_msgs/msg/UlogStreamAck",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::UlogStreamAck>()},
  {"px4_msgs/msg/UnregisterExtComponent",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::UnregisterExtComponent>()},
  {"px4_msgs/msg/VehicleAcceleration",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleAcceleration>()},
  {"px4_msgs/msg/VehicleAirData",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleAirData>()},
  {"px4_msgs/msg/VehicleAngularAccelerationSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleAngularAccelerationSetpoint>()},
  {"px4_msgs/msg/VehicleAngularVelocity",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleAngularVelocity>()},
  {"px4_msgs/msg/VehicleAttitude",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleAttitude>()},
  {"px4_msgs/msg/VehicleAttitudeSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleAttitudeSetpoint>()},
  {"px4_msgs/msg/VehicleCommand",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleCommand>()},
  {"px4_msgs/msg/VehicleCommandAck",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleCommandAck>()},
  {"px4_msgs/msg/VehicleConstraints",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleConstraints>()},
  {"px4_msgs/msg/VehicleControlMode",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleControlMode>()},
  {"px4_msgs/msg/VehicleGlobalPosition",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleGlobalPosition>()},
  {"px4_msgs/msg/VehicleImu",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleImu>()},
  {"px4_msgs/msg/VehicleImuStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleImuStatus>()},
  {"px4_msgs/msg/VehicleLandDetected",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleLandDetected>()},
  {"px4_msgs/msg/VehicleLocalPosition",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleLocalPosition>()},
  {"px4_msgs/msg/VehicleLocalPositionSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleLocalPositionSetpoint>()},
  {"px4_msgs/msg/VehicleMagnetometer",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleMagnetometer>()},
  {"px4_msgs/msg/VehicleOdometry",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleOdometry>()},
  {"px4_msgs/msg/VehicleOpticalFlow",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleOpticalFlow>()},
  {"px4_msgs/msg/VehicleOpticalFlowVel",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleOpticalFlowVel>()},
  {"px4_msgs/msg/VehicleRatesSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleRatesSetpoint>()},
  {"px4_msgs/msg/VehicleRoi",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleRoi>()},
  {"px4_msgs/msg/VehicleStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleStatus>()},
  {"px4_msgs/msg/VehicleThrustSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleThrustSetpoint>()},
  {"px4_msgs/msg/VehicleTorqueSetpoint",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VehicleTorqueSetpoint>()},
  {"px4_msgs/msg/VelocityLimits",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VelocityLimits>()},
  {"px4_msgs/msg/VtolVehicleStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::VtolVehicleStatus>()},
  {"px4_msgs/msg/Vtx",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::Vtx>()},
  {"px4_msgs/msg/WheelEncoders",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::WheelEncoders>()},
  {"px4_msgs/msg/Wind",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::Wind>()},
  {"px4_msgs/msg/YawEstimatorStatus",
    rosidl_typesupport_cpp::get_message_type_support_handle<px4_msgs::msg::YawEstimatorStatus>()},
};

const TopicTypeSupport* find_type_support(const std::string& type_name)
{
  for (const auto& entry : all_px4_ros2_messages) {
    if (type_name == entry.topic_type_name) {
      return &entry;
    }
  }
  return nullptr; // Not found
}


#endif // PX4_MSGS_ALL_MESSAGES_HPP
