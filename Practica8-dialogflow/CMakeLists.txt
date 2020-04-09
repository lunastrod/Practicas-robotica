cmake_minimum_required(VERSION 2.8.3)
project(practica8-dialogflow)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslint
  tf
  behaviortree_cpp_v3
)

catkin_package(CATKIN_DEPENDS
    roscpp
    std_msgs kobuki_msgs sensor_msgs
    tf tf2_geometry_msgs tf2 tf2_ros
    darknet_ros_msgs darknet_ros
    gb_dialog
    behaviortree_cpp_v3
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(carryluggage
  src/carryluggage.cpp
  src/behavior_trees/saluda.cpp
  src/behavior_trees/eligebolsa.cpp
  src/behavior_trees/cogebolsa.cpp
  src/behavior_trees/siguepersona.cpp
  src/behavior_trees/vuelve.cpp

)

target_link_libraries(carryluggage ${catkin_LIBRARIES})

roslint_cpp(
 src/gototf.cpp
)
