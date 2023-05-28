#include "App.hpp"

#include "TestScene.hpp"
#include <SceneManager.hpp>

int main() {
    App app;
    app.init();
    SceneManager::push(new TestScene);
    return app.run();
}