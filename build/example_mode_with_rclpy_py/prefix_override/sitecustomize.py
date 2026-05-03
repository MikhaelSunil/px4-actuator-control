import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/mikks/ros2_px4_ws/install/example_mode_with_rclpy_py'
