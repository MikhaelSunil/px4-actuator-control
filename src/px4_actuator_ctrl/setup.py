from setuptools import setup

package_name = 'px4_actuator_ctrl'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    install_requires=['setuptools'],
    zip_safe=True,

    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name,
            ['package.xml']),
        ('share/' + package_name + '/launch',
            ['launch/offboard.launch.py']),
        ('share/' + package_name + '/rviz',
            ['rviz/px4.rviz']),
    ],

    entry_points={
        'console_scripts': [
            'quadrotor_controller = px4_actuator_ctrl.quadrotor_controller:main',
            'px4_visualizer = px4_actuator_ctrl.px4_visualizer:main',
        ],
    },)