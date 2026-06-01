cmake_minimum_required(VERSION 3.0.2)
project(nodos_cpp)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES nodos_cpp
#  CATKIN_DEPENDS geometry_msgs roscpp
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(suscriptor_cpp src/suscriptor.cpp)
target_link_libraries(suscriptor_cpp ${catkin_LIBRARIES})


add_executable(pub_sub_cpp src/pub_sub.cpp)
target_link_libraries(pub_sub_cpp ${catkin_LIBRARIES})