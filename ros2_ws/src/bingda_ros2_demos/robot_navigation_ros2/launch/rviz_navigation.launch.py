import os
import xacro

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

BASE_TYPE = os.environ['BASE_TYPE']

def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time', default='false')

    # 获取rviz配置文件
    rviz_config_dir = os.path.join(
        get_package_share_directory('robot_navigation_ros2'),
        'rviz',
        'navigation.rviz'
    )

    # 处理xacro生成robot_description
    xacro_file = os.path.join(
    get_package_share_directory('cpp06_urdf'),
    'urdf', 'urdf', 'robot_description.urdf.xacro'
    )
    doc = xacro.process_file(xacro_file)
    robot_description_config = doc.toxml()

    # 加 robot_state_publisher节点（发布TF和robot_description）
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[{
            'robot_description': robot_description_config,
            'use_sim_time': use_sim_time
        }]
    )

    # 加joint_state_publisher节点（发布joint_states）
    joint_state_publisher_node = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        name='joint_state_publisher',
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    # 启动rviz
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config_dir],
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='false',
            description='Use simulation (Gazebo) clock if true'
        ),
        joint_state_publisher_node,
        robot_state_publisher_node,
        rviz_node
    ])
