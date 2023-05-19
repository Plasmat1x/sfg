cmake_minimum_required(VERSION 3.20)
project(Animator VERSION 0.1 LANGUAGES CXX)

set(A_HEADERS
    include/Animation.hpp
    include/Animator.hpp
    include/Flipbook.hpp
    include/Frame.hpp
)

set(A_SRC
    src/Frame.cpp
    src/Flipbook.cpp
    src/Animation.cpp
    src/Animator.cpp
)

add_library(Animator STATIC 
    ${A_SRC}
    ${A_HEADERS}
)

target_include_directories(Animator PRIVATE ./src)
target_include_directories(Animator PUBLIC ./include)

