cmake_minimum_required(VERSION 3.20)

project(sfg VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

#The package luabridge is header only and can be used from CMake via:
#find_path(LUABRIDGE_INCLUDE_DIRS "LuaBridge/List.h")
#target_include_directories(main PRIVATE ${LUABRIDGE_INCLUDE_DIRS})

#Use this package via the module FindLua that comes with CMake. To use in your CMakeLists.txt:
#find_package(Lua REQUIRED)
#target_include_directories(main PRIVATE ${LUA_INCLUDE_DIR})
#target_link_libraries(main PRIVATE ${LUA_LIBRARIES})

#find_package(EnTT CONFIG REQUIRED)
#target_link_libraries(main PRIVATE EnTT::EnTT)

#find_package(box2d CONFIG REQUIRED)
#target_link_libraries(main PRIVATE box2d::box2d)

include_directories(
    include
    include/imgui
    include/Core
    include/Core/Interfaces
    include/Scenes
    include/Game
    include/Interfaces
    include/Core/Animation
)

set(BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}/bin)
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

add_subdirectory(src)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/debug)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin)