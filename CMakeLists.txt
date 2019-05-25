cmake_minimum_required(VERSION 3.5)
project(cs133project)

set(CS133_PROJECT_VERSION_MAJOR 1)
set(CS133_PROJECT_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CS133_PROJECT_LIB ${PROJECT_NAME})
set(CS133_PROJECT_DEMO ${PROJECT_SOURCE_DIR}/demo.cpp)

add_library(${CS133_PROJECT_LIB})

add_executable(${CS133_PROJECT_DEMO})
