cmake_minimum_required(VERSION 2.8.3)
project(practica3-yolo)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslint
  darknet_ros
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs kobuki_msgs sensor_msgs darknet_ros_msgs darknet_ros
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(yolo src/nodo_yolo.cpp)

target_link_libraries(yolo ${catkin_LIBRARIES})

roslint_cpp(
 src/nodo_yolo.cpp
)
