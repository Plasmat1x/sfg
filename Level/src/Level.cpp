#include "Level.hpp"
#include "MapParser.hpp"

Level::Level() {
    texture = nullptr;
}

Level::Level(std::string FILE, sf::View* view) {
    init(FILE, view);
}

Level::~Level() {
    cleanup();
}

void Level::init(std::string FILE, sf::View* view) {
    this->view = view;
    MapParser pars;
    pars.level = this;
    pars.init(FILE);
}

void Level::cleanup() {
    if (texture) delete texture;

    for (auto BG : backgrounds) {
        delete BG;
    }
}

void Level::draw(sf::RenderTarget& tg, sf::RenderStates state) const {
    for (auto B : backgrounds) {
        B->draw(tg, *view);
    }

    for (TileLayer L : layers) {
        for (sf::Sprite T : L.tiles) {
            tg.setView(*view);
            tg.draw(T);
        }
    }

    for (ObjectsLayer L : objects) {
        if (L.visible) {
            for (sf::ConvexShape O : L.shapes) {
                tg.draw(O);
            }
        }
    }
}


void Level::setView(sf::View* view) {
    this->view = view;
}

void Level::update() {

}

//TODO: need logger