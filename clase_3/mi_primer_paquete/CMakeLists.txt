cmake_minimum_required(VERSION 3.0.2)
project(mi_primer_paquete)


find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES mi_primer_paquete
#  CATKIN_DEPENDS geometry_msgs roscpp
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(publicador_cpp src/publicador.cpp)
add_executable(publicador_corregido_cpp src/publicador_corregido.cpp)
add_executable(publicador_loop_cpp src/publicador_loop.cpp)
add_executable(test_cpp src/hola_mundo.cpp)

target_link_libraries(publicador_cpp ${catkin_LIBRARIES})
target_link_libraries(publicador_corregido_cpp ${catkin_LIBRARIES})
target_link_libraries(publicador_loop_cpp ${catkin_LIBRARIES})





