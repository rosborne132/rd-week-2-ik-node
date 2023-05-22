cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_NAME CustomNode)
project(${PROJECT_NAME})

include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)
include_directories(include)

# For fleet support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setup caching when building
set(CMAKE_CXX_COMPILER_LAUNCHER "ccache")

file(GLOB SOURCES "src/*.cpp")

set(SOURCE_FILES ${SOURCES})
set(LIBRARIES
    OpenMaya Foundation
)

build_plugin()
