#include "PhysicsUtils.hpp"

namespace ut {
    //const float SCALE = 30.f;

    sf::Color b2_to_sf(const b2Color& color, int trans) {
        return sf::Color(color.r * 255, color.g * 255, color.b * 255, trans);
    }
    sf::Vector2f b2_to_sf(b2Vec2 vect, float scale) {
        return sf::Vector2f(vect.x * scale, vect.y * scale);
    }
    sf::Vector2f b2_to_sf(float x, float y, float scale) {
        return sf::Vector2f(x * scale, y * scale);
    }

    b2Color sf_to_b2(const sf::Color& color) {
        return b2Color(color.r / 255.f, color.g / 255.f, color.b / 255.f);
    }
    b2Vec2 sf_to_b2(const sf::Vector2f& vect, float scale) {
        return b2Vec2(vect.x / scale, vect.y / scale);
    }
    b2Vec2 sf_to_b2(float x, float y, float scale) {
        return b2Vec2(x / scale, y / scale);
    }

    float vectLength(sf::Vector2f vect) {
        return std::sqrtf(vect.x * vect.x + vect.y * vect.y);
    }
    float vectLength(b2Vec2 vect) {
        return std::sqrtf(vect.x * vect.x + vect.y * vect.y);
    }
    float distance(sf::Vector2f vect1, sf::Vector2f vect2) {
        return vectLength(vect2 - vect1);
    }
    float distance(b2Vec2 vect1, b2Vec2 vect2) {
        return vectLength(vect2 - vect1);
    }
    float toDegree(float radian) {
        return 180.f / 3.141592653589793238462643383f * radian;
    }
    float toRadian(float degree) {
        return 3.141592653589793238462643383f / 180 * degree;
    }
}