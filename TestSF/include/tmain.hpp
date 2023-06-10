//sfml includes
#pragma region 
#include <SFML/Graphics.hpp>
#pragma endregion

//box2d includes
#pragma region 
#include<box2d/box2d.h>
#include<box2d/b2_math.h>
#include<box2d/b2_world.h>
#pragma endregion

//std includes
#pragma region 
#include<cmath>
#include<stdio.h>
#include<vector>
#pragma endregion

//custom
#pragma region 
#include "PhysicsUtils.hpp"
#include "DebugDraw.hpp"
#pragma endregion

struct Obstacle {
    b2BodyDef bodyDef;
    b2Body* body;
    b2PolygonShape shape;

    Obstacle(const b2Vec2& pos, const b2Vec2& siz, b2World& world) {
        bodyDef.position = pos;
        bodyDef.angle = 0.f;
        bodyDef.allowSleep = true;
        bodyDef.fixedRotation = false;
        bodyDef.gravityScale = 1.f;
        bodyDef.type = b2_dynamicBody;

        body = world.CreateBody(&bodyDef);

        shape.SetAsBox(siz.x * .5f, siz.y * .5f);
        body->CreateFixture(&shape, 0.0f);
    }

    Obstacle(const b2Vec2& pos, const std::vector<b2Vec2>& points, b2World& world) {
        bodyDef.position.Set(pos.x, pos.y);
        body = world.CreateBody(&bodyDef);

        shape.Set(points.data(), points.size());
        body->CreateFixture(&shape, 0.0f);
    }
};

struct Dyno {
    b2BodyDef bodyDef;
    b2Body* body;
    b2PolygonShape shape;
    b2FixtureDef fixtureDef;

    Dyno(const b2Vec2& pos, const b2Vec2& siz, b2World& world) {
        bodyDef.position = pos;
        bodyDef.angle = 0.f;
        bodyDef.allowSleep = true;
        bodyDef.fixedRotation = true;
        bodyDef.gravityScale = 1.f;
        bodyDef.type = b2_dynamicBody;

        body = world.CreateBody(&bodyDef);
        shape.SetAsBox(siz.x * .5f, siz.y * .5f);

        fixtureDef.shape = &shape;
        fixtureDef.isSensor = false;
        fixtureDef.density = 0.1f;
        fixtureDef.friction = 2.5f;
        fixtureDef.restitution = 0.01f;

        body->CreateFixture(&fixtureDef);
    }
};


int tmain() {
    //inits
#pragma region 
    sf::Vector2f scr(800.f, 600.f);
    sf::RenderWindow window(sf::VideoMode(scr.x, scr.y), "Test", sf::Style::Default);
    b2Vec2 gravity(0.f, 1.f);
    b2World world(gravity);
    DebugDraw dd;

    dd.setRenderWindow(&window);
    dd.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

    sf::View view;
    sf::View viewHUD;
    sf::Clock clock;
    sf::Time time;

    float prev;
    float cur;
    float dt;
#pragma endregion
    //setup var
#pragma region 
    view.setSize(scr);
    view.setCenter(scr * 0.5f);
    view.zoom(1.0f);

    viewHUD.setSize(scr);
    viewHUD.setCenter(scr * 0.5f);
    viewHUD.zoom(1.0f);
#pragma endregion


    world.SetDebugDraw(&dd);


    std::vector<b2Vec2> points{
        {0.0f, 0.0f},
        { -100.0f, 20.0f },
        { -30.0f, 40.0f },
        { 0.0f, 40.0f },
        { 100.0f, 20.0f },
        { 100.0f, 0.0f },
    };

    Obstacle c(b2Vec2(400.f, 5.f), b2Vec2(800.f, 10.f), world);
    Obstacle g(b2Vec2(400.f, 595.f), b2Vec2(800.f, 10.f), world);
    Obstacle r(b2Vec2(795.f, 300.f), b2Vec2(10.f, 575.f), world);
    Obstacle l(b2Vec2(5.f, 300.f), b2Vec2(10.f, 575.f), world);

    Obstacle s(b2Vec2(scr.x * 0.5f, scr.y * 0.77f), points, world);

    b2Vec2 psize(15.f, 45.f);
    Dyno player(b2Vec2(400.f, 300.f), psize, world);

    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile("../res/elf_single_frame_1x1.png");
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y);
    sprite.setPosition(400.f, 300.f);


    view.zoom(0.5f);

    //pre-loop setups
#pragma region 
    dt = 0.0f;
    prev = 0.0f;
#pragma endregion
    while (window.isOpen()) {
        sf::Event e;

        //time sync
#pragma region 
        time = clock.getElapsedTime();
        cur = time.asSeconds();
        dt = cur - prev;
        prev = cur;
#pragma endregion

        while (window.pollEvent(e)) {
            switch (e.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.body->SetLinearVelocity(b2Vec2(-5.f, player.body->GetLinearVelocity().y));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.body->SetLinearVelocity(b2Vec2(5.f, player.body->GetLinearVelocity().y));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) player.body->SetLinearVelocity(b2Vec2(player.body->GetLinearVelocity().x, -10.f));

        world.Step(1.f / 60.f, 16, 16);

        sprite.setPosition(ut::b2_to_sf(player.body->GetPosition()).x, ut::b2_to_sf(player.body->GetPosition()).y + psize.y * 0.5f);
        view.setCenter(sprite.getPosition());

        //render
#pragma region 
        window.clear(sf::Color::Black);
        window.setView(view);
        {
            window.draw(sprite);
            world.DebugDraw();
        }
        window.setView(viewHUD);
        {

        }
        window.display();
#pragma endregion
    }

    return 0;
}