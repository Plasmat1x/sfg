#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

class MapParser;
class PairBG;

//TODO: storage of all bg layers, get max size of texture, calculate optimal size of texture rect
/*
{
    tsize = texture.size.x
    vsize = view.size.x

    t_res = vsize
    while(tres % tsize || vsize)
        tres += tsize;

    texure.rect.x = tres;
}
*/

class Background {
private:
    float opacity;
    float offsetx;
    float offsety;
    float parallaxx;
    float parallaxy;
    bool repeatx;
    bool repeaty;
    int width;
    int height;
    sf::IntRect textureRect;
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

    void setSize(int width, int height);
    void setPosition(float x, float y);
    void move(float x, float y);

    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;

    void update(const sf::View& view);
    void draw(sf::RenderTarget& target, const sf::View& view);

    friend class MapParser;
    friend class PairBG;
};

class PairBG {
private:
    Background* s1;
    Background* s2;

    Background* cur;
    Background* chn;

    bool repeat;

public:

    PairBG(Background bg);
    ~PairBG();

    void init(Background bg);
    void cleanup();

    void update(const sf::View& view);
    void draw(sf::RenderTarget& target, const sf::View& view);
};