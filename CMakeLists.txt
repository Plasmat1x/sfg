cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

project(sfgv2 VERSION 0.1 LANGUAGES CXX)

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(IMGUI_DIR ${CMAKE_CURRENT_LIST_DIR}/imgui-1.89.5)

add_subdirectory(imgui-sfml-2.5)
add_subdirectory(SceneManager)
add_subdirectory(Animator)
add_subdirectory(Level)
add_subdirectory(App)

add_subdirectory(TestSF)