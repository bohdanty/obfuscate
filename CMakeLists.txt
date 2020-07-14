cmake_minimum_required(VERSION 3.10)

project(obfuscate )

set(CMAKE_CXX_STANDARD 17)

add_library(ret13 ret13.cpp ret13.h)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC ret13)