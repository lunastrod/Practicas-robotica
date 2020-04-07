cmake_minimum_required(VERSION 2.8.3)
project(practica7-behavior)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  behaviortree_cpp_v3
  roslint
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs behaviortree_cpp_v3
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(btreetest
  src/btreetest.cpp
  src/behavior_trees/go.cpp
  src/behavior_trees/turn.cpp
)
target_link_libraries(btreetest ${catkin_LIBRARIES})
