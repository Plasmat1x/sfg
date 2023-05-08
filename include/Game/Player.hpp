#pragma once

#include <SFML/Graphics.hpp>
#include <Core/Animation/AnimationSF.hpp>
#include <Core/Animation/Animator.hpp>

class Player : public sf::Drawable
{
public:

    Animator animator;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RectangleShape rect;

    sf::Vector2f position;
    sf::Vector2f size;

    sf::View view;

    bool debug;

    enum State
    {
        IDLE,
        RUN,
        JUMP,
        FALL,
        CLIMB,
        ROLL
    };

    enum Direction
    {
        RIGHT,
        LEFT
    };

    enum Control
    {
        NONE,
        W,
        A,
        S,
        D,
        SPACE,
        SHIFT
    };

    State state;
    Direction direction;
    Control control;

    Player(sf::Vector2f p, sf::Vector2f s, sf::Texture t)
    {
        state = State::IDLE;
        direction = Direction::RIGHT;
        Init(p, s, t);
    }

    ~Player()
    {

    }

    void Init(sf::Vector2f p, sf::Vector2f s, sf::Texture t)
    {
        texture = t;
        position = p;
        size = s;

        Update(0.0f);
    }

    void Update(const float& dt)
    {
        rect.setOrigin(size.x / 2.f, size.y);
        rect.setSize(size);
        rect.setPosition(position);

        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y);
        sprite.setPosition(position);

        updateStataeMachine();

        if (animator.currentAnimation)
            animator.GetAnimation<AnimationSF>()->Play(dt);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.setView(view);

        target.draw(sprite);
        if (debug)
            target.draw(rect);
    }

    void Cleanup()
    {

    }

private:

    void updateStataeMachine()
    {
        switch (state)
        {
        case State::IDLE:
            break;
        case State::RUN:
            break;
        case State::JUMP:
            break;
        case State::FALL:
            break;
        case State::CLIMB:
            break;
        case State::ROLL:
            break;

        default:
            break;
        }
    }

};