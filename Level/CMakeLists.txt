cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

project(level VERSION 0.1 LANGUAGES CXX)

find_package(tinyxml2 CONFIG REQUIRED)
find_package(SFML COMPONENTS graphics system window CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

set(level_cpp
    src/Level.cpp
    src/MapParser.cpp
    src/Background.cpp
    src/Utils.cpp
)

add_library(level STATIC ${level_cpp})

target_link_libraries(level PRIVATE tinyxml2::tinyxml2 
                            PUBLIC sfml-graphics
                            PUBLIC box2d::box2d
                            PUBLIC physics_sfg)

target_include_directories(level PRIVATE ./src)
target_include_directories(level PUBLIC ./include)