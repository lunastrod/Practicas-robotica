cmake_minimum_required(VERSION 2.8.3)
project(practica5-camara)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslint
  tf
  darknet_ros_msgs
  darknet_ros
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs kobuki_msgs sensor_msgs tf darknet_ros_msgs darknet_ros
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(gototf src/gototf.cpp)

target_link_libraries(gototf ${catkin_LIBRARIES})

roslint_cpp(
 src/gototf.cpp
)
