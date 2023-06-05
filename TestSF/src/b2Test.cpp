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

struct Obstacle {
    sf::Vector2f position;
    sf::Vector2f size;

    b2BodyDef bodyDef;
    b2Body* body;
    b2PolygonShape shape;

    sf::RectangleShape drawShape;

    Obstacle(const sf::Vector2f& pos, const sf::Vector2f& siz, b2World& world) {
        position = pos;
        size = siz;

        bodyDef.position.Set(position.x, position.y);
        body = world.CreateBody(&bodyDef);

        shape.SetAsBox(size.x * .5f, size.y * .5f);
        body->CreateFixture(&shape, 0.0f);

        drawShape.setFillColor(sf::Color(255, 0, 0, 255 * 0.7f));
        drawShape.setOutlineColor(sf::Color::Red);
        drawShape.setOutlineThickness(1.f);
        drawShape.setSize(size);
        drawShape.setOrigin(size * 0.5f);
        drawShape.setPosition(position);
    }

    void update() {
        position.x = body->GetPosition().x;
        position.y = body->GetPosition().y;

        drawShape.setPosition(position.x, position.y);
    }

    void draw(sf::RenderTarget& target) const {
        target.draw(drawShape);
    }
};

struct Dyno {
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape drawShape;

    b2BodyDef bodyDef;
    b2Body* body;
    b2PolygonShape shape;
    b2FixtureDef fixtureDef;

    Dyno(const sf::Vector2f& pos, const sf::Vector2f& siz, b2World& world) {
        position = pos;
        size = siz;

        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);
        body = world.CreateBody(&bodyDef);

        shape.SetAsBox(size.x * .5f, size.y * .5f);

        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        body->CreateFixture(&fixtureDef);

        drawShape.setFillColor(sf::Color(0, 0, 255, 255 * 0.7f));
        drawShape.setOutlineColor(sf::Color::Blue);
        drawShape.setOutlineThickness(1.f);
        drawShape.setSize(size);
        drawShape.setOrigin(size * 0.5f);
        drawShape.setPosition(position);
    }
    void update() {
        position.x = body->GetPosition().x;
        position.y = body->GetPosition().y;

        drawShape.setPosition(position.x, position.y);
    }
    void draw(sf::RenderTarget& target) const {
        target.draw(drawShape);
    }
};

int TestB2SFML() {
    //inits
#pragma region 
    sf::Vector2f scr(800.f, 600.f);
    sf::RenderWindow window(sf::VideoMode(scr.x, scr.y), "Test", sf::Style::Default);

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

    b2Vec2 gravity(0.f, 1.f);
    b2World world(gravity);

    Obstacle ground(sf::Vector2f(scr.x * 0.5f, scr.y * 0.90f), sf::Vector2f(scr.x * .8f, 50.f), world);
    Dyno player(sf::Vector2f(scr * 0.5f), sf::Vector2f(20.f, 80.f), world);



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

            case sf::Event::KeyPressed:
                if (e.key.code == sf::Keyboard::A) player.body->SetLinearVelocity(b2Vec2(-5.f, 0.f));
                if (e.key.code == sf::Keyboard::D) player.body->SetLinearVelocity(b2Vec2(5.f, 0.f));
                break;
            default:
                break;
            }
        }

        world.Step(1.f / 60.f, 1, 1);
        player.update();
        //render
#pragma region 
        window.clear(sf::Color::Cyan);
        window.setView(view);
        {
            ground.draw(window);
            player.draw(window);
        }
        window.setView(viewHUD);
        {

        }
        window.display();
#pragma endregion
    }

    return 0;
}