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
    this->texture = right.texture;
    this->texturewidth = right.texturewidth;
    this->textureheight = right.textureheight;
    this->sprite = sf::Sprite(right.sprite);

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
    this->texture = new sf::Texture; texture->loadFromFile(tex);
    this->texturewidth = this->texture->getSize().x;
    this->textureheight = this->texture->getSize().y;

    sf::Color color(tintcolor.r, tintcolor.g, tintcolor.b, tintcolor.a * opacity);
    sf::IntRect rect(0, 0, texture->getSize().x, texture->getSize().y);

    if (repeatx || repeaty) {
        this->texture->setRepeated(true);
        if (repeatx) {
            rect.width = width;
        }
        if (repeaty) {
            rect.height = height;
        }

    }

    sprite.setTexture(*texture);
    sprite.setTextureRect(rect);
    sprite.setColor(color);
    sprite.setPosition(sf::Vector2f(offsetx, offsety));
}

void Background::cleanup() {
    if (texture) delete texture;
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::View v(target.getView());
    v.setCenter(target.getView().getCenter().x * parallaxx, target.getView().getCenter().y * parallaxy);
    target.setView(v);
    target.draw(sprite);
}

void Background::setPosition(float x, float y) {
    sprite.setPosition(sf::Vector2f(x + offsetx, y + offsety));
}

void Background::move(float x, float y) {
    sprite.move(x, y);
}