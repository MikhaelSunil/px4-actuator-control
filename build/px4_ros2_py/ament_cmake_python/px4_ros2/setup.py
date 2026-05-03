from setuptools import find_packages
from setuptools import setup

setup(
    name='px4_ros2',
    version='0.0.1',
    packages=find_packages(
        include=('px4_ros2', 'px4_ros2.*')),
)
