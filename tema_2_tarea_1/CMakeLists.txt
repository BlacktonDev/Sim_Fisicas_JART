cmake_minimum_required(VERSION 3.26)
project(tema_2_tarea_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(tema_2_tarea_1 main.cpp)

find_package(box2d CONFIG REQUIRED)
target_link_libraries(tema_2_tarea_1 PRIVATE box2d::box2d)