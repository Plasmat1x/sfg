cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

project(physics VERSION 0.1 LANGUAGES CXX)

set(physics_hpp)
set(physics_cpp)

add_library(physics STATIC ${physics_cpp})

target_include_directories(physics PRIVATE ./src)
target_include_directories(physics PUBLIC ./include)