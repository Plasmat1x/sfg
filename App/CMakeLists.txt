cmake_minimum_required(VERSION 3.20)

project(sfg_app VERSION 0.1 LANGUAGES CXX)

find_package(SFML COMPONENTS graphics system window CONFIG REQUIRED)

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
    sfml-window sfml-graphics sfml-system
    ImGui-SFML::ImGui-SFML    
)

target_include_directories(sfg_app PUBLIC ./include)
target_include_directories(sfg_app PRIVATE ./src)

set_target_properties(sfg_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ROOT_DIR}/debug)
set_target_properties(sfg_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ROOT_DIR}/bin)