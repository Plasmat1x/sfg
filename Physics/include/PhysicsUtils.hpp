#pragma once

#include <SFML/Graphics.hpp>

#include <box2d/box2d.h>
#include <box2d/b2_math.h>

#include <math.h>

namespace ut {
    //const float SCALE = 30.f;
    const float SCALE = 1.f;

    inline sf::Color b2_to_sf(const b2Color& color, int trans = 255);
    inline sf::Vector2f b2_to_sf(b2Vec2 vect, float scale = 1.f);
    inline sf::Vector2f b2_to_sf(float x, float y, float scale = 1.f);

    inline b2Color sf_to_b2(const sf::Color& color);
    inline b2Vec2 sf_to_b2(const sf::Vector2f& vect, float scale);
    inline b2Vec2 sf_to_b2(float x, float y, float scale = 1.f);

    inline float vectLength(sf::Vector2f vect);
    inline float vectLength(b2Vec2 vect);
    inline float distance(sf::Vector2f vect1, sf::Vector2f vect2);
    inline float distance(b2Vec2 vect1, b2Vec2 vect2);
    inline float toDegree(float radian);
    inline float toRadian(float degree);
}