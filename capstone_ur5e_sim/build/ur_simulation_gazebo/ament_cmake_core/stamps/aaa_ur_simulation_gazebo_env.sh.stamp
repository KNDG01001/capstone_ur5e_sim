pkg_share="/home/sunbi/ros/install/ur_simulation_gazebo/share/ur_simulation_gazebo"

# Materials and world assets live inside the package but (unlike real Gazebo models)
# they do not provide a model.config file. Only append those folders to the resource
# search path so Gazebo can discover textures and worlds without treating every
# subdirectory as a model.
export GAZEBO_RESOURCE_PATH="${pkg_share}/materials/scripts:\
${pkg_share}/materials/textures:\
${pkg_share}/materials:\
${pkg_share}/worlds:${GAZEBO_RESOURCE_PATH}"

# The package does not ship Gazebo models, so avoid polluting GAZEBO_MODEL_PATH
# with directories that are missing model.config. (Leaving the existing path
# untouched keeps default models available.)
export GAZEBO_MODEL_PATH="${GAZEBO_MODEL_PATH}"

export GAZEBO_PLUGIN_PATH="/home/sunbi/ros/install/ur_simulation_gazebo/lib:${GAZEBO_PLUGIN_PATH}"
