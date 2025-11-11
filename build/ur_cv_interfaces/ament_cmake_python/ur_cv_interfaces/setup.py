from setuptools import find_packages
from setuptools import setup

setup(
    name='ur_cv_interfaces',
    version='0.0.1',
    packages=find_packages(
        include=('ur_cv_interfaces', 'ur_cv_interfaces.*')),
)
