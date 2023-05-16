#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include "Core/SceneManager.hpp"
#include "app.hpp"
#include "Scenes/TestScene.hpp"

extern sf::RenderWindow* window = nullptr;
extern lua_State* L = nullptr;
extern sf::Event* event = nullptr;

int App::Run()
{

    Init();

    while (window->isOpen())
    {
        TimerStart();
        UpdateWindow();
        Update();
        UpdateFixed();
        UpdatePast();
        Render();
    }

    Cleanup();

    return 0;
}

void App::Cleanup()
{
    if (window != nullptr)
    {
        delete window;
        window = nullptr;
    }
}

void App::Init()
{
    resolution = sf::Vector2u(1280, 720);
    view.setSize(resolution.x, resolution.y);
    view.setCenter(resolution.x / 2.f, resolution.y / 2.f);

    window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), "sfg", sf::Style::Default);
    window->setView(view);
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
    ImDemoShow = false;
    ImControll = false;

    SceneMgr::push(new TestScene);
}

void App::UpdateWindow()
{
    while (window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(*window, event);
        switch (event.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::Resized:
            resolution = window->getSize();
            view.setCenter(resolution.x / 2.0f, resolution.y / 2.0f);
            view.setSize(resolution.x, resolution.y);
            window->setView(view);
            break;

        case sf::Event::KeyPressed:
            break;
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::F8)
            {
                ImControll = !ImControll;
            }
            break;
        default:
            break;
        }

        SceneMgr::top()->UpdateEvents();

    }

    SceneMgr::top()->UpdateInput();

    ImGui::SFML::Update(*window, imClock.restart());
}

void App::Update()
{
    SceneMgr::top()->Update(eleapsed.asSeconds());
}

void App::TimerStart()
{
    current = clock.getElapsedTime();
    eleapsed = current - previous;
    previous = current;
    lag += eleapsed;
}

void App::UpdateFixed()
{
    while (lag >= MS_PER_UPDATE)
    {
        SceneMgr::top()->UpdateFixed();
        lag -= MS_PER_UPDATE;
    }
}

void App::Debug()
{
    if (ImControll)
    {
        ImGui::Begin("App controll", &ImControll);
        {
            ImGui::Checkbox("ImGui Demo", &ImDemoShow);
            ImGui::Checkbox("App debug", &ImDebugShow);
        }
        ImGui::End();
    }

    if (ImDemoShow)
        ImGui::ShowDemoWindow(&ImDemoShow);

    if (ImDebugShow)
    {
        ImGui::Begin("App Debug", &ImDebugShow);
        {
            ImGui::Text("Timeup : %.2f", current.asSeconds());
            ImGui::Separator();

            if (ImGui::CollapsingHeader("APP"))
            {
                if (ImGui::CollapsingHeader("Timings"))
                {
                    ImGui::Text("Eleapsed Time:\n\ts: %.2f\n\tms: %d\n\tmcs: %d", eleapsed.asSeconds(), eleapsed.asMilliseconds(), eleapsed.asMicroseconds());
                    ImGui::Text("Current Time:\n\ts: %.2f\n\tms: %d\n\tmcs: %d", current.asSeconds(), current.asMilliseconds(), current.asMicroseconds());
                    ImGui::Text("Previous Time:\n\ts: %.2f\n\tms: %d\n\tmcs: %d", previous.asSeconds(), previous.asMilliseconds(), previous.asMicroseconds());
                    ImGui::Text("Lag Time:\n\ts: %.2f\n\tms: %d\n\tmcs: %d", lag.asSeconds(), lag.asMilliseconds(), lag.asMicroseconds());
                    ImGui::Text("MS_PER_UPDATE(CONST) Time:\n\ts: %.2f\n\tms: %d\n\tmcs: %d", MS_PER_UPDATE.asSeconds(), MS_PER_UPDATE.asMilliseconds(), MS_PER_UPDATE.asMicroseconds());
                }

                if (ImGui::CollapsingHeader("Window"))
                {
                    ImGui::Text("Window: width = %d, height = %d\nResolution: width = %d, height = %d", window->getSize().x, window->getSize().y, resolution.x, resolution.y);
                    ImGui::Text("View: width = %.1f, height = %.1f", window->getView().getSize().x, window->getView().getSize().y);
                    ImGui::Text("View center: x = %.1f, y = %.1f", window->getView().getCenter().x, window->getView().getCenter().y);
                }
                if (ImGui::CollapsingHeader("Scene Manager"))
                {
                    ImGui::Text("max size: %d\nsize: %d", SceneMgr::sizeMax(), SceneMgr::size());
                }
                if (ImGui::CollapsingHeader("Window background fill collor"))
                {
                    if (ImGui::ColorEdit4("Background fill color", color))
                    {
                        WindowCollor.r = static_cast<sf::Uint8>(color[0] * 255.f);
                        WindowCollor.g = static_cast<sf::Uint8>(color[1] * 255.f);
                        WindowCollor.b = static_cast<sf::Uint8>(color[2] * 255.f);
                        WindowCollor.a = static_cast<sf::Uint8>(color[3] * 255.f);
                    }

                    if (ImGui::Button("default color"))
                    {
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

                if (ImGui::CollapsingHeader("Mouse info"))
                {
                    ImGui::Text("Global Position:\nx = %d\ny = %d", sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                    ImGui::Text("Local Position:\nx = %d\ny = %d", sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
                }
            }
            ImGui::Separator();
            if (ImGui::CollapsingHeader("SceneDebug"))
            {
                ImGui::BeginChild("SceneDebug", ImVec2(440, 0), true);
                SceneMgr::top()->Debug(eleapsed.asSeconds());
                ImGui::EndChild();
            }
        }
        ImGui::End();
    }
}

void App::UpdatePast()
{
    SceneMgr::top()->UpdatePast(eleapsed.asSeconds());

    Debug();
}

void App::Render()
{
    window->setView(view);
    window->clear(WindowCollor);
    SceneMgr::top()->Render();
    ImGui::SFML::Render(*window);
    window->display();
}
