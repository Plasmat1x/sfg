#include "Objects.hpp"

namespace phy {
    Obstacle::Obstacle() {

    }
    Obstacle::Obstacle(const b2vec2& pos, const b2vec2& siz, b2World& world) {
        bodyDef.position.Set(pos.x, pos.y);
        body = world.CreateBody(&bodyDef);

        shape.SetAsBox(siz.x * .5f, siz.y * .5f);
        body->CreateFixture(&shape, 0.0f);
    }

    Obstacle::Obstacle(const b2Vec2& pos, const std::vector<b2Vec2>& points, b2World& world) {
        bodyDef.position.Set(pos.x, pos.y);
        body = world.CreateBody(&bodyDef);

        shape.Set(points.data(), points.size());
        body->CreateFixture(&shape, 0.0f);
    }

    Dyno::Dyno() {

    }
    Dyno::Dyno(const b2vec2& pos, const b2vec2& siz, b2World& world) {
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);
        body = world.CreateBody(&bodyDef);

        shape.SetAsBox(siz.x * .5f, siz.y * .5f);

        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        body->CreateFixture(&fixtureDef);
    }
}



