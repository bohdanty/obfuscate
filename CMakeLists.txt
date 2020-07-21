cmake_minimum_required(VERSION 3.10)

project(obfuscate CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(rot13 STATIC rot13.h rot13.cpp)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE rot13)

set(SAPI_ROOT "" CACHE PATH "Path to the Sandboxed API source tree")

set(SAPI_ENABLE_EXAMPLES OFF CACHE BOOL "")
set(SAPI_ENABLE_TESTS OFF CACHE BOOL "")
add_subdirectory("${SAPI_ROOT}"
                 "${CMAKE_BINARY_DIR}/sandboxed-api-build"
                 EXCLUDE_FROM_ALL)

add_sapi_library(rot13_sapi
  FUNCTIONS obfuscate  # List of functions that we want to include in the
                       # generated sandboxed API class
  INPUTS rot13.h       # Header files or .cc files that should be parsed
  LIBRARY rot13        # Library dependency from the add_library() above
  LIBRARY_NAME Rot13   # Name prefix for the generated header. Will be
                       # suffixed with "Api" and "Sandbox" as needed.
  NAMESPACE ""         # Optional C++ namespace to wrap the generated code
)

target_include_directories(rot13_sapi INTERFACE
  "${PROJECT_BINARY_DIR}"  # To find the generated SAPI header
)

add_executable(rot13_sandboxed
    main_sandboxed.cpp
)

target_link_libraries(rot13_sandboxed PRIVATE
    rot13_sapi
    sapi::sapi
)