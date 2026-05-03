#!/usr/bin/env python3

from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    pkg_path = get_package_share_directory('px4_actuator_ctrl')
    rviz_config = os.path.join(pkg_path, 'rviz', 'px4.rviz')

    # PX4 + MicroXRCE (terminal)

    microxrce = ExecuteProcess(
        cmd=[
            'gnome-terminal', '--tab', '--', 'bash', '-c',
            'MicroXRCEAgent udp4 -p 8888; exec bash'
        ],
        output='screen'
    )

    px4 = ExecuteProcess(
        cmd=[
            'gnome-terminal', '--tab', '--', 'bash', '-c',
            'cd ~/PX4-Autopilot && make px4_sitl gz_x500; exec bash'
        ],
        output='screen'
    )

    #  
    #  CONTROLLER NODE
    #  
    controller = Node(
        package='px4_actuator_ctrl',
        executable='quadrotor_controller',
        name='quadrotor_controller',
        output='screen'
    )

     
    # VISUALIZER NODE  
     
    visualizer = Node(
        package='px4_actuator_ctrl',
        executable='px4_visualizer',
        name='px4_visualizer',
        output='screen'
    )

     
    # RVIZ
    
    rviz =    Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', rviz_config],
            output='screen'
        )

    return LaunchDescription([
        microxrce,
        px4,
        controller,
        visualizer,
        rviz
    ])