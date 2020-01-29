cmake_minimum_required(VERSION 2.8.3)
project(stop-bumper)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  std_msgs
  roscpp
  roslint
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES stop-bumper
  CATKIN_DEPENDS geometry_msgs roscpp
#  DEPENDS system_lib
  CATKIN_DEPENDS roscpp std_msgs
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable( stop-bumper src/stop-bumper-node.cpp)
target_link_libraries( stop-bumper ${catkin_LIBRARIES})
