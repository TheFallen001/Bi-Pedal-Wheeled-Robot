import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

from launch_ros.actions import Node

def generate_launch_description():
    package_name="bpwr"

    # rsp = IncludeLaunchDescription(
    #     PythonLaunchDescriptionSource([os.path.join(
    #         get_package_share_directory(package_name), 'launch', 'rsp.launch.py'
    #         )]), launch_arguments={'use_sim_time': 'true'}.items()
    # )

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [os.path.join(get_package_share_directory('gazebo_ros'), 'launch', 'gazebo.launch.py')]
        )
    )

    spawn_entity = Node(package='gazebo_ros', executable='spawn_entity.py', 
                 arguments=['-topic', 'robot_description', '-entity', 'bpwr'],
                 output='screen')
    
    ros2_control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[
            PathJoinSubstitution([
               FindPackageShare(package_name),
                "config",
                "controllers.yaml"
            ])
        ],
        output="screen"
    )
    
    

    return LaunchDescription([
        gazebo, ros2_control_node, spawn_entity
    ])