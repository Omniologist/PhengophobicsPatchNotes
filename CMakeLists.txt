cmake_minimum_required(VERSION 4.1)
project(untitled)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled main.cpp)
find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(main PRIVATE SDL3::SDL3)