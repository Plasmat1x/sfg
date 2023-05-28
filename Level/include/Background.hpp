#pragma once

#include <SFML/Graphics.hpp>

class MapParser;
class InfScroller;

class Background : public sf::Drawable {
private:
    float opacity;
    float offsetx;
    float offsety;
    float parallaxx;
    float parallaxy;
    bool repeatx;
    bool repeaty;
    int texturewidth;
    int textureheight;
    sf::Color tintcolor;
    sf::Texture* texture;
    sf::Sprite sprite;

public:
    Background();
    Background(int width, int height, float opacity, float offsetx, float offsety, float parallaxx, float parallaxy, bool repeatx, bool repeaty, sf::Color tintcolor, std::string tex);
    ~Background();

    Background(const Background& right);
    Background& operator=(const Background& right);

    void init(int width, int height, float opacity, float offsetx, float offsety, float parallaxx, float parallaxy, bool repeatx, bool repeaty, sf::Color tintcolor, std::string tex);
    void cleanup();

    void setPosition(float x, float y);
    void move(float x, float y);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    friend class MapParser;
    friend class InfScroller;
};