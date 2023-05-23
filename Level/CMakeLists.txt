cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

project(level VERSION 0.1 LANGUAGES CXX)

find_package(tinyxml2 CONFIG REQUIRED)

set(level_hpp
    include/Level.hpp
)

set(level_cpp
    src/Level.cpp
)

add_library(level STATIC ${level_cpp} ${level_hpp})

target_link_libraries(level PRIVATE tinyxml2::tinyxml2)

target_include_directories(level PRIVATE ./src)
target_include_directories(level PUBLIC ./include)