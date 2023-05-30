#include "TestScene.hpp"
#include <SceneManager.hpp>

#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <Animator.hpp>
#include <thread>
#include <sstream>
#include <string>
#include <queue>

#include <Player.hpp>
#include <Level.hpp>
#include <Background.hpp>

extern sf::RenderWindow* window;
extern sf::Event* event;
sf::Texture texture;
sf::View view;
sf::View viewUI;
sf::RectangleShape vline;
sf::RectangleShape hline;
sf::CircleShape dot;

Player p;
Level* l = nullptr;

sf::Vector2f mousePos;

TestScene::TestScene() {
    init();
}

TestScene::~TestScene() {
    cleanup();
}

void TestScene::init() {
    view.setSize(1280, 720);
    view.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);
    viewUI.setSize(1280, 720);
    viewUI.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);

    texture.loadFromFile("../resources/image/elf/anim_wip.png");

    vline.setSize(sf::Vector2f(1.0f, window->getView().getSize().y));
    vline.setOrigin(sf::Vector2f(vline.getSize().x / 2.f, vline.getSize().y / 2.f));
    vline.setPosition(window->getView().getCenter());
    vline.setFillColor(sf::Color(0, 0, 0, 92));

    hline.setSize(sf::Vector2f(window->getView().getSize().x, 1.0f));
    hline.setOrigin(sf::Vector2f(hline.getSize().x / 2.f, hline.getSize().y / 2.f));
    hline.setPosition(window->getView().getCenter());
    hline.setFillColor(sf::Color(0, 0, 0, 92));

    dot.setPosition(0, 0);
    dot.setOrigin(5, 5);
    dot.setRadius(5);
    dot.setFillColor(sf::Color::Black);

    p.Init(sf::Vector2f(0, 0), sf::Vector2f(40, 180), texture);
    p.debug = true;

    view.zoom(1.0f);
    l = new Level();
    l->init("map1.tmx", &view);
}

void TestScene::updateEvents() {
    switch (event->type)
    {
    case sf::Event::Resized:

        view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
        viewUI.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
        break;

    case sf::Event::KeyReleased:
        if (event->key.code == sf::Keyboard::T) {
            p.position = mousePos;
        }
        break;
    default:
        break;
    }
}

void TestScene::updateInput() {
    mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window), view);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        p.Climb();
        p.position.y = p.position.y - 1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        p.direction = Player::Direction::LEFT;
        p.Move();
        p.position.x = p.position.x - 1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        p.Fall();
        p.position.y = p.position.y + 1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        p.direction = Player::Direction::RIGHT;
        p.Move();
        p.position.x = p.position.x + 1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        p.Jump();

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        p.Roll();
    }
    else {
        p.Idle();
    }
}

void TestScene::update(const float& dt) {
    p.Update(dt);
    p.UpdateAnimation(dt);
}

void TestScene::updatePast(const float& dt) {
    p.setCam(&view);
}

void TestScene::updateFixed() {

}

void TestScene::debug(const float& dt) {

    ImGui::Begin("viewport");

    ImGui::SeparatorText("Main view");
    ImGui::Text("View: width = %.1f, height = %.1f", view.getSize().x, view.getSize().y);
    ImGui::Text("View center: x = %.1f, y = %.1f", view.getCenter().x, view.getCenter().y);

    ImGui::SeparatorText("UI view");

    ImGui::Text("View: width = %.1f, height = %.1f", viewUI.getSize().x, viewUI.getSize().y);
    ImGui::Text("View center: x = %.1f, y = %.1f", viewUI.getCenter().x, viewUI.getCenter().y);

    ImGui::SeparatorText("window view");

    ImGui::Text("View: width = %.1f, height = %.1f", window->getView().getSize().x, window->getView().getSize().y);
    ImGui::Text("View center: x = %.1f, y = %.1f", window->getView().getCenter().x, window->getView().getCenter().y);

    if (ImGui::Button("+")) { view.zoom(0.5f); }
    ImGui::SameLine();
    if (ImGui::Button("-")) { view.zoom(2.0f); }



    ImGui::Text("mouse pos: %.1f x %.1f",
                mousePos.x,
                mousePos.y);

    ImGui::End();
}

void TestScene::render()
{

    window->setView(view);

    window->draw(vline);
    window->draw(hline);

    window->draw(*l);

    window->setView(view);
    window->draw(p);

    window->draw(dot);

    window->setView(viewUI);
    window->draw(vline);
    window->draw(hline);

}

void TestScene::cleanup() {
    if (l) delete l;
}


