cmake_minimum_required(VERSION 2.8.3)
project(practica9-findmymates)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslint
  tf
  behaviortree_cpp_v3
  dialogflow_ros_msgs
  std_srvs
  sound_play
  actionlib
  actionlib_msgs
  gb_dialog
)

catkin_package(
    LIBRARIES
      gb_dialog
    CATKIN_DEPENDS
      roscpp
      std_msgs kobuki_msgs sensor_msgs
      tf tf2_geometry_msgs tf2 tf2_ros
      darknet_ros_msgs darknet_ros
      gb_dialog dialogflow_ros_msgs actionlib_msgs
      behaviortree_cpp_v3
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(findmymates
  src/findmymates.cpp
  src/behavior_trees/busca.cpp
  src/behavior_trees/dialogo.cpp
  src/behavior_trees/informacion.cpp
  src/behavior_trees/navegacion.cpp
  src/behavior_trees/saludo.cpp
  src/behavior_trees/vuelve.cpp
  src/ejemploDF.cpp
)

target_link_libraries(findmymates ${catkin_LIBRARIES})

roslint_cpp(
 src/gototf.cpp
)
