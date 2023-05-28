#pragma once

#include<SFML/Graphics.hpp>
#include<queue>

class Background;

class InfScroller : public sf::Drawable {
private:
    std::queue<Background*> queue;
public:
    InfScroller();
    InfScroller(Background* bg, sf::View* v);
    ~InfScroller();

    void init(Background* bg, sf::View* v);
    void cleanup();

    void update(sf::View* view);

    virtual void draw(sf::RenderTarget& tg, sf::RenderStates st) const;
};