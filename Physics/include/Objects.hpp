#include<box2d/box2d.h>
#include<box2d/b2_math.h>
#include<box2d/b2_world.h>

#include <vector>

namespace phy {
    class Obstacle {
    public:
        b2BodyDef bodyDef;
        b2Body* body;
        b2PolygonShape shape;
    public:
        Obstacle();
        Obstacle(const b2vec2& pos, const b2vec2& siz, b2World& world);
        Obstacle(const b2Vec2& pos, const std::vector<b2Vec2>& points, b2World& world);
        ~Obstacle();
    };

    class Dyno {
    public:
        b2BodyDef bodyDef;
        b2Body* body;
        b2PolygonShape shape;
        b2FixtureDef fixtureDef;
    public:
        Dyno();
        Dyno(const b2vec2& pos, const b2vec2& siz, b2World& world);
        ~Dyno();
    };
}