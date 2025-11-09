from setuptools import setup
from glob import glob
import os

package_name = 'ur_cv_moveit'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
         ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),

        # ✅ launch 디렉토리 전체 install (여기 수정)
        ('share/' + package_name + '/launch', glob(os.path.join('launch', '*.launch.py'))),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='you',
    maintainer_email='you@example.com',
    description='Detect a button with CV and use MoveIt to move the UR5e.',
    license='BSD-3-Clause',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'button_detection_node = ur_cv_moveit.button_detection_node:main',
            'button_press_action_node = ur_cv_moveit.button_press_action_node:main',
            'camera_capture_node = ur_cv_moveit.camera_capture_node:main',
        ],
    },
)
