#include <SFML/Graphics.hpp>

#define PI 3.14159265358979323846 

#include <math.h>
#include <stdlib.h>

inline float toDegree(float radian) {
    return 180.f / 3.141592653589793238462643383f * radian;
}
inline float toRadian(float degree) {
    return 3.141592653589793238462643383f / 180 * degree;
}

int rotation_main() {
    sf::Vector2f scr(800.f, 600.f);
    sf::RenderWindow window(sf::VideoMode(scr.x, scr.y), "Test", sf::Style::Default);

    sf::View view;
    sf::View viewHUD;
    sf::Clock clock;
    sf::Time time;

    float prev;
    float cur;
    float dt;

    view.setSize(scr);
    view.setCenter(scr * 0.5f);
    view.zoom(1.0f);

    viewHUD.setSize(scr);
    viewHUD.setCenter(scr * 0.5f);
    viewHUD.zoom(1.0f);

    dt = 0.0f;
    prev = 0.0f;

    float r = 30.f;

    sf::ConvexShape p;
    p.setPointCount(3);
    p.setPoint(0, sf::Vector2f(0.f, 0.f));
    p.setPoint(1, sf::Vector2f(-10.f, -10.f));
    p.setPoint(2, sf::Vector2f(-10.f, 10.f));
    p.setFillColor(sf::Color::Red);
    p.setPosition(scr * 0.5f);

    sf::ConvexShape o;
    o.setPointCount(3);
    o.setPoint(0, sf::Vector2f(0.f, 0.f));
    o.setPoint(1, sf::Vector2f(50.f, -10.f));
    o.setPoint(2, sf::Vector2f(50.f, 10.f));
    o.setFillColor(sf::Color::Yellow);
    o.setPosition(sf::Vector2f(
        p.getPosition().x + (r * cos(toRadian(p.getRotation()))),
        p.getPosition().y + (r * sin(toRadian(p.getRotation())))
    ));

    while (window.isOpen()) {
        sf::Event e;
        time = clock.getElapsedTime();
        cur = time.asSeconds();
        dt = cur - prev;
        prev = cur;

        while (window.pollEvent(e)) {
            switch (e.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (e.key.code == sf::Keyboard::Left) {
                    p.rotate(-45.f);
                    o.setRotation(p.getRotation());
                }
                if (e.key.code == sf::Keyboard::Right) {
                    p.rotate(45.f);
                    o.setRotation(p.getRotation());
                };

                o.setPosition(sf::Vector2f(
                    p.getPosition().x + (r * cosf(toRadian(p.getRotation()))),
                    p.getPosition().y + (r * sinf(toRadian(p.getRotation())))
                ));

                system("cls");
                printf("rad: %.1f\n", r);
                printf("\np:\n");
                printf("pad = %.1f, par = %.1f\n", p.getRotation(), toRadian(p.getRotation()));
                printf("px = %.1f, py = %.1f\n", p.getPosition().x, p.getPosition().y);

                printf("\no:\n");
                printf("oad = %.1f, oar = %.1f\n", o.getRotation(), toRadian(o.getRotation()));
                printf("ox = %.1f, oy = %.1f\n", o.getPosition().x, o.getPosition().y);

                break;
            default:
                break;
            }
        }

        window.clear(sf::Color::Black);
        window.setView(view);
        {
            window.draw(o);
            window.draw(p);
        }
        window.setView(viewHUD);
        {

        }
        window.display();
    }

    return 0;
}