cmake_minimum_required(VERSION 3.26)
project(hola_joints)

set(CMAKE_CXX_STANDARD 17)

add_executable(hola_joints main.cpp)

find_package(box2d CONFIG REQUIRED)
target_link_libraries(hola_joints PRIVATE box2d::box2d)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(hola_joints PRIVATE sfml-system sfml-network sfml-graphics sfml-window)