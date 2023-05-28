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

sf::RectangleShape r1;
sf::RectangleShape r2;

Player p;
Level* l = nullptr;

std::queue<sf::RectangleShape*> q;

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

    r1.setSize(sf::Vector2f(100.0f, 80.0f));
    r1.setPosition(0.0f, 0.0f);
    r1.setOutlineColor(sf::Color::Red);
    r1.setOutlineThickness(1.f);

    r2.setSize(sf::Vector2f(100.0f, 80.0f));
    r2.setPosition(r1.getSize().x, 0);
    r2.setOutlineColor(sf::Color::Red);
    r2.setOutlineThickness(1.f);

    q.push(&r1);
    q.push(&r2);
}

void TestScene::updateEvents() {

}

void TestScene::updateInput() {
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
    l->update();
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

    ImGui::End();
}

void TestScene::render()
{
    window->setView(view);
    window->draw(dot);
    window->draw(vline);
    window->draw(hline);

    window->draw(*l);

    window->setView(view);
    window->draw(*q.front());
    window->draw(*q.back());
    window->draw(p);


    window->setView(viewUI);
    window->draw(vline);
    window->draw(hline);

}

void TestScene::cleanup() {
    if (l) delete l;
}