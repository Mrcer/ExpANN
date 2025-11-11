cmake_minimum_required(VERSION 3.24.0)

project(expann
    VERSION 1.0.0
    DESCRIPTION "An experimental project to implement FusionANNS"
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(expann)
add_subdirectory(demos)
add_subdirectory(tests)