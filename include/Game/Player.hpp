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

    Player()
    {

    }

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
        state = State::IDLE;
        direction = Direction::RIGHT;

        texture = t;
        position = p;
        size = s;

        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Magenta);
        rect.setOutlineThickness(5.f);

        /*
        int w = 400;
        int h = 240;
        int cf = 6;
        float sp = 8.f;
        float scale = 1.f;

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, w, h));
        sprite.setScale(scale, scale);

        animator.AddAnimation("IDLE", new AnimationSF(0, 0, w, h, cf, sp, &sprite));
        animator.AddAnimation("MOVE", new AnimationSF(0, 1, w, h, cf, sp, &sprite));
        animator.AddAnimation("JUMP", new  AnimationSF(0, 2, w, h, cf - 2, sp, &sprite));
        animator.AddAnimation("FALL", new AnimationSF(0, 3, w, h, cf - 2, sp, &sprite));
        animator.AddAnimation("CLIMB", new AnimationSF(0, 4, w, h, cf, sp, &sprite));
        animator.AddAnimation("ROLL", new AnimationSF(0, 5, w, h, cf + 1, sp, &sprite));
        */
        Update(0.0f);
    }

    void Update(const float& dt)
    {
        rect.setSize(size);
        rect.setOrigin(size.x / 2.f, size.y);
        rect.setPosition(position);

        sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height);
        sprite.setPosition(position);

        updateStataeMachine();

        if (animator.currentAnimation)
            animator.GetAnimation<AnimationSF>()->Play(dt);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        //target.setView(view);
        target.draw(sprite);
        if (debug)
            target.draw(rect);
    }

    void Cleanup()
    {

    }

private:

    std::string astr;

    void adir()
    {
        if (direction == Direction::RIGHT)
        {
            animator.GetAnimation<AnimationSF>(astr)->hflip = false;
        }
        else if (direction == Direction::LEFT)
        {
            animator.GetAnimation<AnimationSF>(astr)->hflip = false;
        }
    }

    void mdir()
    {
        if (control == Control::A || control == Control::D)
        {
            if (control == Control::A)
            {
                direction = Direction::LEFT;
            }
            else if (control == Control::D)
            {
                direction = Direction::RIGHT;
            }
        }
    }

    void updateStataeMachine()
    {
        astr = "";

        switch (state)
        {

        case State::IDLE:
            astr = "IDLE";
            animator.SetAnimation(astr);
            adir();

            if (control == Control::A || control == Control::D)
                state = State::RUN;

            if (control == Control::SPACE)
                state = State::JUMP;

            if (control == Control::SHIFT)
                state = State::ROLL;

            break;

        case State::RUN:
            astr = "RUN";
            animator.SetAnimation(astr);
            adir();
            mdir();

            if (control == Control::A || control == Control::D)
                state = State::RUN;

            if (control == Control::SPACE)
                state = State::JUMP;

            if (control == Control::SHIFT)
                state = State::ROLL;

            break;

        case State::JUMP:
            astr = "JUMP";
            animator.SetAnimation(astr);
            adir();
            mdir();

            state = State::IDLE;
            break;

        case State::FALL:
            astr = "FALL";
            animator.SetAnimation(astr);
            adir();
            mdir();
            state = State::IDLE;
            break;

        case State::CLIMB:
            astr = "CLIMB";
            animator.SetAnimation(astr);
            adir();
            state = State::IDLE;
            break;

        case State::ROLL:
            astr = "ROLL";
            animator.SetAnimation(astr);
            adir();
            mdir();
            state = State::IDLE;
            break;

        default:
            break;
        }
    }

};