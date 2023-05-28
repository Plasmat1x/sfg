#include <iostream>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SceneManager.hpp>
#include "app.hpp"

extern sf::RenderWindow* window = nullptr;
extern sf::Event* event = nullptr;

int App::run() {

    while (window->isOpen()) {
        timerStart();
        updateWindow();
        update();
        updateFixed();
        updatePast();
        render();
    }

    cleanup();

    return 0;
}

void App::cleanup() {
    if (window != nullptr) {
        delete window;
        window = nullptr;
    }
}

void App::init() {
    resolution = sf::Vector2u(1280, 720);

    window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), "sfg", sf::Style::Default);
    window->setFramerateLimit(144);
    color[0] = .5f;
    color[1] = .5f;
    color[2] = .5f;
    color[3] = 1.f;
    WindowCollor.r = static_cast<sf::Uint8>(color[0] * 255.f);
    WindowCollor.g = static_cast<sf::Uint8>(color[1] * 255.f);
    WindowCollor.b = static_cast<sf::Uint8>(color[2] * 255.f);
    WindowCollor.a = static_cast<sf::Uint8>(color[3] * 255.f);

    ::event = &this->event;

    previous = clock.getElapsedTime();
    lag = sf::Time::Zero;

    ImGui::SFML::Init(*window);
    ImDebugShow = true;
    ImControll = false;


}

void App::updateWindow() {
    while (window->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(*window, event);
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::Resized:
            break;

        case sf::Event::KeyPressed:
            break;
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::F8) {
                ImControll = !ImControll;
            }
            break;
        default:
            break;
        }

        SceneManager::top()->updateEvents();

    }

    SceneManager::top()->updateInput();

    ImGui::SFML::Update(*window, imClock.restart());
}

void App::update() {
    SceneManager::top()->update(eleapsed.asSeconds());
}

void App::timerStart() {
    current = clock.getElapsedTime();
    eleapsed = current - previous;
    previous = current;
    lag += eleapsed;
}

void App::updateFixed() {
    while (lag >= MS_PER_UPDATE) {
        SceneManager::top()->updateFixed();
        lag -= MS_PER_UPDATE;
    }
}

void App::debug() {
    if (ImControll) {
        ImGui::Begin("App controll", &ImControll);
        {
            ImGui::Checkbox("App debug", &ImDebugShow);
        }
        ImGui::End();
    }

    if (ImDebugShow) {
        ImGui::Begin("App Debug", &ImDebugShow);
        {
            ImGui::Text("Timeup : %.2f", current.asSeconds());
            ImGui::Separator();

            if (ImGui::CollapsingHeader("APP"))
            {
                if (ImGui::CollapsingHeader("Timings")) {
                    ImGui::Text("Eleapsed Time:\n\ts: %.2f\n\tms: %d\n\tmcs: %d", eleapsed.asSeconds(), eleapsed.asMilliseconds(), eleapsed.asMicroseconds());
                    ImGui::Text("Current Time:\n\ts: %.2f\n\tms: %d\n\tmcs: %d", current.asSeconds(), current.asMilliseconds(), current.asMicroseconds());
                    ImGui::Text("Previous Time:\n\ts: %.2f\n\tms: %d\n\tmcs: %d", previous.asSeconds(), previous.asMilliseconds(), previous.asMicroseconds());
                    ImGui::Text("Lag Time:\n\ts: %.2f\n\tms: %d\n\tmcs: %d", lag.asSeconds(), lag.asMilliseconds(), lag.asMicroseconds());
                    ImGui::Text("MS_PER_UPDATE(CONST) Time:\n\ts: %.2f\n\tms: %d\n\tmcs: %d", MS_PER_UPDATE.asSeconds(), MS_PER_UPDATE.asMilliseconds(), MS_PER_UPDATE.asMicroseconds());
                }

                if (ImGui::CollapsingHeader("Window")) {
                    ImGui::Text("Window: width = %d, height = %d\nResolution: width = %d, height = %d", window->getSize().x, window->getSize().y, resolution.x, resolution.y);
                    ImGui::Text("View: width = %.1f, height = %.1f", window->getView().getSize().x, window->getView().getSize().y);
                    ImGui::Text("View center: x = %.1f, y = %.1f", window->getView().getCenter().x, window->getView().getCenter().y);
                }
                if (ImGui::CollapsingHeader("Scene Manager")) {
                    ImGui::Text("max size: %d\nsize: %d", SceneManager::sizeMax(), SceneManager::size());
                }
                if (ImGui::CollapsingHeader("Window background fill collor")) {
                    if (ImGui::ColorEdit4("Background fill color", color)) {
                        WindowCollor.r = static_cast<sf::Uint8>(color[0] * 255.f);
                        WindowCollor.g = static_cast<sf::Uint8>(color[1] * 255.f);
                        WindowCollor.b = static_cast<sf::Uint8>(color[2] * 255.f);
                        WindowCollor.a = static_cast<sf::Uint8>(color[3] * 255.f);
                    }

                    if (ImGui::Button("default color")) {
                        color[0] = .5f;
                        color[1] = .5f;
                        color[2] = .5f;
                        color[3] = 1.f;

                        WindowCollor.r = static_cast<sf::Uint8>(color[0] * 255.f);
                        WindowCollor.g = static_cast<sf::Uint8>(color[1] * 255.f);
                        WindowCollor.b = static_cast<sf::Uint8>(color[2] * 255.f);
                        WindowCollor.a = static_cast<sf::Uint8>(color[3] * 255.f);
                    }
                }

                if (ImGui::CollapsingHeader("Mouse info")) {
                    ImGui::Text("Global Position:\nx = %d\ny = %d", sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                    ImGui::Text("Local Position:\nx = %d\ny = %d", sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
                }
            }
        }
        ImGui::End();

        SceneManager::top()->debug(eleapsed.asSeconds());
    }
}

void App::updatePast() {
    SceneManager::top()->updatePast(eleapsed.asSeconds());

    debug();
}

void App::render() {
    window->clear(WindowCollor);
    SceneManager::top()->render();
    ImGui::SFML::Render(*window);
    window->display();
}