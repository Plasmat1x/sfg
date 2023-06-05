#include "DebugDraw.hpp"    
DebugDraw::DebugDraw() {

}
DebugDraw::~DebugDraw() {
    window = nullptr;
}

void DebugDraw::setRenderWindow(sf::RenderWindow* renderWindow) {
    window = renderWindow;
}
void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 count, const b2Color& color) {
    sf::ConvexShape polygon;
    polygon.setOutlineThickness(thickness);
    polygon.setOutlineColor(ut::b2_to_sf(color));
    polygon.setFillColor(sf::Color::Transparent);

    polygon.setPointCount(count);
    for (int32 i{}; i < count; i++) {
        polygon.setPoint(i, ut::b2_to_sf(vertices[i], ut::SCALE));
    }

    window->draw(polygon);
}
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 count, const b2Color& color) {
    sf::ConvexShape polygon;
    polygon.setOutlineThickness(thickness);
    polygon.setOutlineColor(ut::b2_to_sf(color));
    polygon.setFillColor(ut::b2_to_sf(color, transparency));

    polygon.setPointCount(count);
    for (int32 i{}; i < count; i++) {
        polygon.setPoint(i, ut::b2_to_sf(vertices[i], ut::SCALE));
    }

    window->draw(polygon);
}
void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
    sf::CircleShape circle;
    circle.setOutlineThickness(thickness);
    circle.setOutlineColor(ut::b2_to_sf(color));
    circle.setFillColor(sf::Color::Transparent);

    float rad = radius * ut::SCALE;
    circle.setPosition(ut::b2_to_sf(center, ut::SCALE));
    circle.setRadius(rad);
    circle.setOrigin(sf::Vector2f(rad, rad));

    window->draw(circle);
}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
    sf::CircleShape circle;
    circle.setOutlineThickness(thickness);
    circle.setOutlineColor(ut::b2_to_sf(color));
    circle.setFillColor(ut::b2_to_sf(color, transparency));

    float rad = radius * ut::SCALE;
    circle.setPosition(ut::b2_to_sf(center, ut::SCALE));
    circle.setRadius(rad);
    circle.setOrigin(sf::Vector2f(rad, rad));

    window->draw(circle);
}
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    sf::RectangleShape line;
    float length = ut::distance(ut::b2_to_sf(p1, ut::SCALE), ut::b2_to_sf(p2, ut::SCALE));
    line.setSize(sf::Vector2f(length, thickness));
    line.setPosition(ut::b2_to_sf(p1, ut::SCALE));
    line.setFillColor(ut::b2_to_sf(color));
    line.setOrigin(sf::Vector2f(line.getOrigin().x, thickness / 2.f));

    float delta_x = p2.x - p1.x;
    float delta_y = p2.y - p1.y;
    float angle = atan2(delta_x, delta_y);
    line.setRotation(ut::toDegree(angle));

    window->draw(line);
}
void DebugDraw::DrawTransform(const b2Transform& xf) {
    const float k_axisScale = 0.4f;

    b2Vec2 p1, p2;
    p1 = xf.p;
    p2 = p1 + k_axisScale * xf.q.GetXAxis();
    DrawSegment(p1, p2, b2Color(1.0f, 0.0f, 0.0f));

    p2 = p1 + k_axisScale * xf.q.GetYAxis();
    DrawSegment(p1, p2, b2Color(0.0f, 1.0f, 0.0f));
}
void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color) {
    float s = size * 1.5f;
    sf::RectangleShape point;
    point.setFillColor(ut::b2_to_sf(color));
    point.setPosition(ut::b2_to_sf(p, ut::SCALE));
    point.setSize(sf::Vector2f(s, s));
    point.setOrigin(sf::Vector2f(s / 2.f, s / 2.f));

    window->draw(point);
}
void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color) {
    sf::ConvexShape aabb_shape;
    aabb_shape.setOutlineColor(ut::b2_to_sf(color));
    aabb_shape.setPointCount(4);

    aabb_shape.setPoint(0, ut::b2_to_sf(aabb->lowerBound, ut::SCALE));
    aabb_shape.setPoint(1, sf::Vector2f(aabb->upperBound.x * ut::SCALE, aabb->lowerBound.y * ut::SCALE));
    aabb_shape.setPoint(2, ut::b2_to_sf(aabb->upperBound, ut::SCALE));
    aabb_shape.setPoint(3, sf::Vector2f(aabb->lowerBound.x * ut::SCALE, aabb->upperBound.y * ut::SCALE));

    window->draw(aabb_shape);
}