cmake_minimum_required(VERSION 3.0.2)
project(parameter_server)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
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

add_executable(servidor_servicio_1_cpp src/servidor_servicio.cpp)
target_link_libraries(servidor_servicio_1_cpp ${catkin_LIBRARIES})