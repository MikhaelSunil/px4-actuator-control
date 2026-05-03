from setuptools import find_packages, setup

package_name = 'rl_hover_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='mikks',
    maintainer_email='mikhaelstark22@gmail.com',
    description='RL Hover Controller using Actor-Critic for PX4',
    license='Apache License 2.0',

    # ⭐ THIS IS THE IMPORTANT PART
    entry_points={
        'console_scripts': [
            'rl_hover_node = rl_hover_pkg.rl_hover_node:main',
        ],
    },
)
