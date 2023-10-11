cmake_minimum_required(VERSION 3.26)
project(hola_poligonos)

set(CMAKE_CXX_STANDARD 17)

add_executable(hola_poligonos main.cpp)

find_package(box2d CONFIG REQUIRED)
target_link_libraries(hola_poligonos PRIVATE box2d::box2d)