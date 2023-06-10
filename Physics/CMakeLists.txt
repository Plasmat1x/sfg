cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

project(physics_sfg VERSION 0.1 LANGUAGES CXX)

find_package(box2d CONFIG REQUIRED)
find_package(SFML COMPONENTS graphics system window CONFIG REQUIRED)

set(physics_src
    src/PhysicsUtils.cpp
    src/DebugDraw.cpp
)

add_library(physics_sfg STATIC ${physics_src})

target_link_libraries(physics_sfg 
    PUBLIC box2d::box2d
    PRIVATE sfml-graphics sfml-system sfml-window
)

target_include_directories(physics_sfg PRIVATE ./src)
target_include_directories(physics_sfg PUBLIC ./include)