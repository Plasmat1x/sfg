cmake_minimum_required(VERSION 3.20)
project(SceneManager VERSION 0.1 LANGUAGES CXX)

add_library(SceneManager STATIC 
    src/SceneManager.cpp
    include/SceneManager.hpp 
    include/IScene.hpp
)

target_include_directories(SceneManager PRIVATE ./src)
target_include_directories(SceneManager PUBLIC ./include)



