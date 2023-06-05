#pragma once
#include <box2d/b2_draw.h>
#include <box2d/b2_collision.h>

#include <SFML/Graphics.hpp>

#include "PhysicsUtils.hpp"

class DebugDraw : public b2Draw {
private:
    sf::RenderWindow* window;
    float thickness = -2.f;
    int transparency = 50;

public:
    DebugDraw();
    ~DebugDraw();

    void setRenderWindow(sf::RenderWindow* renderWindow);
    void DrawPolygon(const b2Vec2* vertices, int32 count, const b2Color& color);
    void DrawSolidPolygon(const b2Vec2* vertices, int32 count, const b2Color& color);
    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);
    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    void DrawTransform(const b2Transform& xf);
    void DrawPoint(const b2Vec2& p, float size, const b2Color& color);
    void DrawAABB(b2AABB* aabb, const b2Color& color);
};