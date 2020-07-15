cmake_minimum_required(VERSION 3.10)

project(obfuscate)

set(CMAKE_CXX_STANDARD 17)

add_library(rot13 rot13.cpp rot13.h)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC rot13)