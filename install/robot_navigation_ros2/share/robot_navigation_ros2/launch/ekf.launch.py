#!/usr/bin/env python3

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, Command
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # 参数配置
    use_sim_time = LaunchConfiguration('use_sim_time', default='false')
    resolution = LaunchConfiguration('resolution', default='0.05')
    publish_period_sec = LaunchConfiguration('publish_period_sec', default='1.0')

    # 包目录
    nav_pkg = get_package_share_directory('robot_navigation_ros2')
    urdf_pkg = get_package_share_directory('cpp06_urdf')  # 你的 URDF 包名

    # 文件路径
    urdf_path = os.path.join(urdf_pkg, 'urdf', 'urdf', 'robot_description.urdf.xacro')
    ekf_yaml = os.path.join(nav_pkg, 'config', 'ekf.yaml')
    carto_config_dir = os.path.join(nav_pkg, 'config')
    rviz_config = os.path.join(nav_pkg, 'bingda_cartographer.rviz')

    return LaunchDescription([
        # 声明参数
        DeclareLaunchArgument('use_sim_time', default_value='false'),
        DeclareLaunchArgument('resolution', default_value=resolution),
        DeclareLaunchArgument('publish_period_sec', default_value=publish_period_sec),


        # 🧠 EKF
        Node(
            package='robot_localization',
            executable='ekf_node',
            name='ekf_filter_node',
            output='screen',
            parameters=[ekf_yaml]
        ),

        # 🤖 发布 URDF TF
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            parameters=[{'robot_description': Command(['xacro ', urdf_path])}]
        ),

    ])
