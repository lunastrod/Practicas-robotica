cmake_minimum_required(VERSION 2.8.3)
project(practica6-botella)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslint
  tf
  darknet_ros
  sensor_msgs
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs kobuki_msgs sensor_msgs tf darknet_ros_msgs darknet_ros
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(navp6 src/navp6.cpp)
add_executable(busquedap6 src/busquedap6.cpp)

target_link_libraries(navp6 ${catkin_LIBRARIES})
target_link_libraries(busquedap6 ${catkin_LIBRARIES})

roslint_cpp(
 src/gototf.cpp
)
