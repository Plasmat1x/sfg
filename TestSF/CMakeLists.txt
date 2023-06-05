cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

project(TestSF VERSION 0.1 LANGUAGES CXX)

find_package(SFML COMPONENTS graphics system window CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

set(SRC 
    src/main.cpp
    src/DebugDraw.cpp
    include/PhysicsUtils.hpp
)

add_executable(TestSF ${SRC})

target_link_libraries(TestSF 
    PRIVATE sfml-window sfml-graphics sfml-system
    PRIVATE box2d::box2d
)

target_include_directories(TestSF PUBLIC ./include)

set_target_properties(TestSF PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin)
set_target_properties(TestSF PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin)
set_target_properties(TestSF PROPERTIES EXCLUDE_FROM_ALL TRUE)
set_target_properties(TestSF PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD TRUE)
