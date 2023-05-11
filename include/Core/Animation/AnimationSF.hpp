#pragma once

#include <SFML/Graphics.hpp>
#include <Core/Animation/Animation.hpp>
#include <Core/Animation/Frame.hpp>

class AnimationSF : public Animation
{
public:

    sf::Sprite* sprite;

    AnimationSF();
    AnimationSF(const int& x, const int& y,
                const int& w, const int& h,
                const int& c, const float& s, sf::Sprite* t);

    void Init(const int& x, const int& y,
              const int& w, const int& h,
              const int& c, const float& s, sf::Sprite* t);

    ~AnimationSF();

    bool Play(const float& dt);
    bool PlayReverse(const float& dt);
    void Update();

    bool Next();
    bool Prev();

    void Debug();

private:
    bool textureInspector = false;
};