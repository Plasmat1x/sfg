find_package(SFML COMPONENTS graphics system window CONFIG REQUIRED)
find_package(Lua REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    app.cpp
    imgui/imgui.cpp
    imgui/imgui-SFML.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_demo.cpp
    Core/SceneManager.cpp
    Scenes/TestScene.cpp
    Core/Utils.cpp
    Game/Player.cpp
    Core/Animation/Animation.cpp
    Core/Animation/AnimationSF.cpp
    Core/Animation/Animator.cpp
    Core/Animation/Flipbook.cpp
)

find_path(LUABRIDGE_INCLUDE_DIRS "LuaBridge/List.h")
target_include_directories(${PROJECT_NAME} PRIVATE ${LUABRIDGE_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
    opengl32
    sfml-system
    sfml-window
    sfml-graphics
    ${LUA_LIBRARIES}
)