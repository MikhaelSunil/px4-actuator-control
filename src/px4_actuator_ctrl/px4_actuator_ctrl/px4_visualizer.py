#!/usr/bin/env python3
############################################################################
# PX4 RViz Visualizer (Fixed Version)
# Author: Mikhael Sunil (adapted from PX4 example)
############################################################################

import numpy as np
import math

import rclpy
from rclpy.node import Node
from rclpy.clock import Clock
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSHistoryPolicy

from px4_msgs.msg import VehicleAttitude
from px4_msgs.msg import VehicleLocalPosition
from px4_msgs.msg import TrajectorySetpoint
from px4_msgs.msg import VehicleOdometry
from geometry_msgs.msg import PoseStamped, Point
from nav_msgs.msg import Path
from visualization_msgs.msg import Marker
import tf2_ros
from geometry_msgs.msg import TransformStamped
from rclpy.qos import qos_profile_sensor_data
qos_profile = qos_profile_sensor_data
  
def vector2PoseMsg(frame_id, position, attitude):
    pose_msg = PoseStamped()
    pose_msg.header.frame_id = frame_id
    pose_msg.header.stamp = Clock().now().to_msg()   

    pose_msg.pose.orientation.w = attitude[0]
    pose_msg.pose.orientation.x = attitude[1]
    pose_msg.pose.orientation.y = attitude[2]
    pose_msg.pose.orientation.z = attitude[3]

    pose_msg.pose.position.x = position[0]
    pose_msg.pose.position.y = position[1]
    pose_msg.pose.position.z = position[2]

    return pose_msg      
# PX4 Visualizer Node

class PX4Visualizer(Node):

    def __init__(self):
        super().__init__('px4_visualizer')

        qos = QoSProfile(
            reliability=QoSReliabilityPolicy.BEST_EFFORT,
            history=QoSHistoryPolicy.KEEP_LAST,
            depth=1
        )

        qos_sens = qos_profile_sensor_data

        #  Subscribers     
        self.create_subscription(
            VehicleAttitude,
            '/fmu/out/vehicle_attitude',
            self.vehicle_attitude_callback,
            qos)
        self.tf_broadcaster = tf2_ros.TransformBroadcaster(self)
        self.create_subscription(
            VehicleLocalPosition,
            '/fmu/out/vehicle_local_position',
            self.vehicle_local_position_callback,
            qos_sens)
        self.odom_sub = self.create_subscription(
            VehicleOdometry,
            '/fmu/out/vehicle_odometry',
            self.vehicle_odometry_callback,
            qos_profile_sensor_data
        )
        self.create_subscription(
            TrajectorySetpoint,
            '/fmu/in/trajectory_setpoint',
            self.trajectory_setpoint_callback,
            qos)

        #  Publishers     
        self.vehicle_pose_pub = self.create_publisher(
            PoseStamped, '/px4_visualizer/vehicle_pose', 10)

        self.vehicle_vel_pub = self.create_publisher(
            Marker, '/px4_visualizer/vehicle_velocity', 10)

        self.vehicle_path_pub = self.create_publisher(
            Path, '/px4_visualizer/vehicle_path', 10)

        self.setpoint_path_pub = self.create_publisher(
            Path, '/px4_visualizer/setpoint_path', 10)

        #  State     
        self.vehicle_attitude = np.array([1., 0., 0., 0.])
        self.vehicle_local_position = np.zeros(3)
        self.vehicle_local_velocity = np.zeros(3)
        self.setpoint_position = np.zeros(3)

        self.vehicle_path_msg = Path()
        self.setpoint_path_msg = Path()

        # Timer loop
        self.timer = self.create_timer(0.05, self.cmdloop_callback)

        self.get_logger().info("PX4 Visualizer Started")

     
    # Callbacks
      
    def vehicle_attitude_callback(self, msg):
        # NED → ENU quaternion fix
        self.vehicle_attitude[0] = msg.q[0]
        self.vehicle_attitude[1] = msg.q[1]
        self.vehicle_attitude[2] = -msg.q[2]
        self.vehicle_attitude[3] = -msg.q[3]
    def publish_tf(self):
        t = TransformStamped()

        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = "map"
        t.child_frame_id = "base_link"

        # position
        t.transform.translation.x = float(self.vehicle_local_position[0])
        t.transform.translation.y = float(self.vehicle_local_position[1])
        t.transform.translation.z = float(self.vehicle_local_position[2])

        # orientation
        t.transform.rotation.w = float(self.vehicle_attitude[0])
        t.transform.rotation.x = float(self.vehicle_attitude[1])
        t.transform.rotation.y = float(self.vehicle_attitude[2])
        t.transform.rotation.z = float(self.vehicle_attitude[3])

        self.tf_broadcaster.sendTransform(t)
    def vehicle_odometry_callback(self, msg):
        # NED → ENU conversion (VERY IMPORTANT)
        self.vehicle_local_position[0] = msg.position[1]   # x = East
        self.vehicle_local_position[1] = msg.position[0]   # y = North
        self.vehicle_local_position[2] = -msg.position[2]  # z = Up

        self.vehicle_attitude[0] = msg.q[0]
        self.vehicle_attitude[1] = msg.q[1]
        self.vehicle_attitude[2] = msg.q[2]
        self.vehicle_attitude[3] = msg.q[3]

    def vehicle_local_position_callback(self, msg):
        # NED → ENU conversion
        self.vehicle_local_position[0] = msg.y
        self.vehicle_local_position[1] = msg.x
        self.vehicle_local_position[2] = -msg.z

        self.vehicle_local_velocity[0] = msg.vy
        self.vehicle_local_velocity[1] = msg.vx
        self.vehicle_local_velocity[2] = -msg.vz

    def trajectory_setpoint_callback(self, msg):
        # NED → ENU
        self.setpoint_position[0] = msg.position[1]
        self.setpoint_position[1] = msg.position[0]
        self.setpoint_position[2] = -msg.position[2]

          
    # Velocity arrow
      
    def create_arrow_marker(self, id, tail, vector):
        msg = Marker()
        msg.header.frame_id = 'map'
        msg.header.stamp = Clock().now().to_msg()  

        msg.ns = 'velocity'
        msg.id = id
        msg.type = Marker.ARROW
        msg.action = Marker.ADD

        msg.scale.x = 0.1
        msg.scale.y = 0.2

        msg.color.r = 1.0
        msg.color.g = 0.2
        msg.color.b = 0.0
        msg.color.a = 1.0

        dt = 0.3

        tail_point = Point()
        tail_point.x, tail_point.y, tail_point.z = tail

        head_point = Point()
        head_point.x = tail[0] + dt * vector[0]
        head_point.y = tail[1] + dt * vector[1]
        head_point.z = tail[2] + dt * vector[2]

        msg.points = [tail_point, head_point]
        return msg

         
    # Main loop
         
    def cmdloop_callback(self):
        self.publish_tf()
        # Pose
        pose_msg = vector2PoseMsg(
            'map',
            self.vehicle_local_position,
            self.vehicle_attitude
        )
        self.vehicle_pose_pub.publish(pose_msg)
        
        # Vehicle path
        self.vehicle_path_msg.header = pose_msg.header
        self.vehicle_path_msg.poses.append(pose_msg)
        self.vehicle_path_pub.publish(self.vehicle_path_msg)

        # Setpoint path
        sp_pose = vector2PoseMsg(
            'map',
            self.setpoint_position,
            self.vehicle_attitude
        )
        self.setpoint_path_msg.header = sp_pose.header
        self.setpoint_path_msg.poses.append(sp_pose)
        self.setpoint_path_pub.publish(self.setpoint_path_msg)

        # Velocity arrow
        vel_marker = self.create_arrow_marker(
            0,
            self.vehicle_local_position,
            self.vehicle_local_velocity
        )
        self.vehicle_vel_pub.publish(vel_marker)

      
# Main
      
def main(args=None):
    rclpy.init(args=args)

    node = PX4Visualizer()
    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()