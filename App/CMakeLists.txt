cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

project(sfg_app VERSION 0.1 LANGUAGES CXX)

#find_package(box2d CONFIG REQUIRED)
#target_link_libraries(main PRIVATE box2d::box2d)
#find_package(EnTT CONFIG REQUIRED)
#target_link_libraries(main PRIVATE EnTT::EnTT)

find_package(SFML COMPONENTS graphics system window CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED) 

set(app_hpp
    include/App.hpp
    include/Player.hpp
    include/TestScene.hpp
)

set(app_cpp
    src/App.cpp
    src/main.cpp
    src/TestScene.cpp
)

add_executable(sfg_app ${app_cpp} ${app_hpp})

target_link_libraries(sfg_app PUBLIC 
    Animator 
    SceneManager
    level
    sfml-window sfml-graphics sfml-system
    ImGui-SFML::ImGui-SFML
    PRIVATE tinyxml2::tinyxml2
)

target_include_directories(sfg_app PUBLIC ./include)
target_include_directories(sfg_app PRIVATE ./src)

set_target_properties(sfg_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ROOT_DIR}/debug)
set_target_properties(sfg_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ROOT_DIR}/bin)