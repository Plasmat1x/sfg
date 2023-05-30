#include "Background.hpp"

Background::Background() {

}

Background::Background(int width, int height, float opacity, float offsetx, float offsety, float parallaxx, float parallaxy, bool repeatx, bool repeaty, sf::Color tintcolor, std::string tex) {
    init(width, height, opacity, offsetx, offsety, parallaxx, parallaxy, repeatx, repeaty, tintcolor, tex);
}

Background::~Background() {
    cleanup();
}

Background::Background(const Background& right) {
    *this = right;
}

Background& Background::operator=(const Background& right) {

    this->opacity = right.opacity;
    this->offsetx = right.offsetx;
    this->offsety = right.offsety;
    this->parallaxx = right.parallaxx;
    this->parallaxy = right.parallaxy;
    this->repeatx = right.repeatx;
    this->repeaty = right.repeaty;
    this->tintcolor = right.tintcolor;
    this->texture = new sf::Texture(*right.texture);
    this->textureRect = right.textureRect;
    this->sprite = sf::Sprite(right.sprite);
    this->sprite.setTexture(*texture);
    this->width = right.width;
    this->height = right.height;

    return *this;
}

void Background::init(int width, int height, float opacity, float offsetx, float offsety, float parallaxx, float parallaxy, bool repeatx, bool repeaty, sf::Color tintcolor, std::string tex) {

    this->opacity = opacity;
    this->offsetx = offsetx;
    this->offsety = offsety;
    this->parallaxx = parallaxx;
    this->parallaxy = parallaxy;
    this->repeatx = repeatx;
    this->repeaty = repeaty;
    this->tintcolor = tintcolor;
    this->texture = new sf::Texture;
    texture->loadFromFile(tex);

    sf::Color color(tintcolor.r, tintcolor.g, tintcolor.b, tintcolor.a * opacity);
    textureRect = sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y);

    if (repeatx || repeaty) {
        this->texture->setRepeated(true);
        if (repeatx) {
            textureRect.width = width;
        }
        if (repeaty) {
            textureRect.height = height;
        }
    }

    sprite.setTexture(*texture);
    sprite.setTextureRect(textureRect);
    sprite.setColor(color);
    sprite.setPosition(sf::Vector2f(offsetx, offsety));
}

void Background::cleanup() {
    if (texture) delete texture;
}

void Background::draw(sf::RenderTarget& target, const sf::View& view) {
    sf::View v(view);
    v.setCenter(view.getCenter().x * parallaxx, view.getCenter().y * parallaxy);
    target.setView(v);
    target.draw(sprite);
}

void Background::setPosition(float x, float y) {
    sprite.setPosition(sf::Vector2f(x + offsetx, y + offsety));
}

void Background::move(float x, float y) {
    sprite.move(x, y);
}

void Background::setSize(int width, int height) {
    this->textureRect.width = width;
    this->textureRect.height = height;
}

sf::FloatRect Background::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
sf::Vector2f Background::getSize() const {
    return sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}
sf::Vector2f Background::getPosition() const {
    return sprite.getPosition();
}


PairBG::PairBG(Background bg) {
    init(bg);
}

PairBG::~PairBG() {
    cleanup();
}

void PairBG::init(Background bg) {
    s1 = new Background(bg);
    repeat = s1->repeatx || s1->repeaty;
    s2 = new Background(bg);
    s2->move(bg.getSize().x, 0.0f);

    cur = s1;
    chn = s2;
}

void PairBG::cleanup() {
    if (s1) delete s1;
    if (s2) delete s2;
}

void PairBG::update(const sf::View& view) {
    if (
        view.getCenter().x * chn->parallaxx > ((chn->getPosition().x + chn->getSize().x * 0.5f)) &&
        view.getCenter().x * cur->parallaxx > ((cur->getPosition().x + cur->getSize().x * 0.5f))
        ) {
        chn->move(chn->getSize().x * 2, 0.0f);
    }
    else if (
        view.getCenter().x * chn->parallaxx < ((chn->getPosition().x + chn->getSize().x * 0.5f)) &&
        view.getCenter().x * cur->parallaxx < ((cur->getPosition().x + cur->getSize().x * 0.5f))
        ) {
        chn->move(-chn->getSize().x * 2, 0.0f);
    }

    if (!(
        view.getCenter().x * cur->parallaxx >= (cur->getPosition().x) &&
        view.getCenter().x * cur->parallaxx <= ((cur->getPosition().x + cur->getSize().x))
        )) {
        std::swap(cur, chn);
    }
}

void PairBG::draw(sf::RenderTarget& t, const sf::View& view) {
    if (repeat)
        update(view);

    s1->draw(t, view);
    if (repeat)
        s2->draw(t, view);
}
