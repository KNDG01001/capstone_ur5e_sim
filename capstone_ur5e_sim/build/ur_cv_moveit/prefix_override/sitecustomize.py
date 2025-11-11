import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/sunbi/ros/capstone_ur5e_sim/install/ur_cv_moveit'
