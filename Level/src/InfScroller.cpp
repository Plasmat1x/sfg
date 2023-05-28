#include "InfScroller.hpp"

#include "Background.hpp"

InfScroller::InfScroller() {

}

InfScroller::InfScroller(Background* bg, sf::View* v) {
    init(bg, v);
}

InfScroller::~InfScroller() {
    cleanup();
}

void InfScroller::init(Background* bg, sf::View* v) {
    queue.push(new Background(*bg));
    queue.push(new Background(*bg));
    queue.back()->move(v->getSize().x, 0.0f);
}

void InfScroller::cleanup() {
    while (!queue.empty()) {
        delete queue.front();
        queue.pop();
    }
}


void InfScroller::update(sf::View* view) {
    if (view->getCenter().x >= queue.front()->sprite.getPosition().x + view->getSize().x) {
        Background* _t = queue.front();
        _t->move(view->getSize().x * 2.0f, 0.0f);
        queue.pop();
        queue.push(_t);
    }
    else if (view->getCenter().x <= queue.front()->sprite.getPosition().x) {
        Background* _t = queue.front();
        _t->move(view->getSize().x * 2.0f, 0.0f);
        queue.pop();
        queue.push(_t);
    }
}

void InfScroller::draw(sf::RenderTarget& tg, sf::RenderStates st) const {
    tg.draw(*queue.front());
    tg.draw(*queue.back());
}