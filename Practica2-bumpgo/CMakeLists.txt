cmake_minimum_required(VERSION 2.8.3)
project(practica2-bumpgo)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslint
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs kobuki_msgs sensor_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(bumpgo src/nodo_bumpgo.cpp)

target_link_libraries(bumpgo ${catkin_LIBRARIES})

roslint_cpp(
 src/nodo_bumpgo.cpp
)
