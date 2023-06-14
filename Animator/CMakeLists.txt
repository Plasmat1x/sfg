cmake_minimum_required(VERSION 3.20)
project(Animator VERSION 0.1 LANGUAGES CXX)

set(A_SRC
    src/Frame.cpp
    src/Flipbook.cpp
    src/Animation.cpp
    src/Animator.cpp
)

add_library(Animator STATIC 
    ${A_SRC}
)

target_include_directories(Animator PRIVATE ./src)
target_include_directories(Animator PUBLIC ./include)

