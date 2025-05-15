import os
import xacro  # 加上这个依赖！
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time', default='false')

    # 定位到你的 xacro 文件
    xacro_file = '/home/bingda/ros2_ws/src/cpp06_urdf/urdf/urdf/robot_description.urdf.xacro'

    # 调用 xacro 处理成 urdf 内容
    doc = xacro.process_file(xacro_file)
    robot_description_config = doc.toxml()

    # 发布 robot_description
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[{
            'robot_description': robot_description_config,
            'use_sim_time': use_sim_time
        }]
    )
    joint_state_publisher_node = Node(
    package='joint_state_publisher',
    executable='joint_state_publisher',
    name='joint_state_publisher',
    parameters=[{'use_sim_time': use_sim_time}],
    output='screen'
    )

    # 启动 rviz
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=[],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='false',
            description='Use simulation (Gazebo) clock if true'
        ),
        robot_state_publisher_node,
        joint_state_publisher_node,
        rviz_node
    ])
