cmake_minimum_required(VERSION 2.8.3)
project(practica8-dialogflow)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslint
  tf
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs kobuki_msgs sensor_msgs tf darknet_ros_msgs darknet_ros tf2_geometry_msgs tf2 tf2_ros gb_dialog
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

#add_executable(exampleDF src/exampleDF.cpp)

#target_link_libraries(exampleDF ${catkin_LIBRARIES})

roslint_cpp(
 src/gototf.cpp
)
