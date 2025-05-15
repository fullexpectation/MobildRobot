from setuptools import find_packages
from setuptools import setup

setup(
    name='object_information_msgs_ros2',
    version='0.0.0',
    packages=find_packages(
        include=('object_information_msgs_ros2', 'object_information_msgs_ros2.*')),
)
