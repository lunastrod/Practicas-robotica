cmake_minimum_required(VERSION 2.8.3)
project(stop-bumper)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES stop-bumper
#  CATKIN_DEPENDS geometry_msgs ros.cpp
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(nodoPrueba src/nodoPrueba.cpp)
target_link_libraries(nodoPrueba ${catkin_LIBRARIES})
