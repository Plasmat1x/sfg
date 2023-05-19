#pragma once

#include <SFML/Graphics.hpp>
#include <Core/Animation/Animator.hpp>

#include "imgui/imgui.h"
#include "imgui-SFML.h"

class Player : public sf::Drawable
{
public:

    Animation::Animator animator;
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
        MOVE,
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

    State state;
    Direction direction;


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

        w = 400;
        h = 240;
        cf = 6;
        sp = 8.3f;
        scale = 1.f;

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, w, h));
        sprite.setScale(scale, scale);

        animator.addAnimation("IDLE", new Animation::Animation(0, 0, w, h, cf, sp));
        animator.addAnimation("MOVE", new Animation::Animation(0, 1, w, h, cf, sp));
        animator.addAnimation("JUMP", new  Animation::Animation(0, 2, w, h, cf - 2, sp));
        animator.addAnimation("FALL", new Animation::Animation(0, 3, w, h, cf - 2, sp));
        animator.addAnimation("CLIMB", new Animation::Animation(0, 4, w, h, cf, sp));
        animator.addAnimation("ROLL", new Animation::Animation(0, 5, w, h, cf + 1, sp));
    }

    void Update(const float& dt)
    {
        _size = size;
        if (state == State::ROLL)
            _size.y = size.y * 0.5f;

        rect.setSize(_size);
        rect.setOrigin(_size.x * 0.5f, _size.y);
        rect.setPosition(position);

        sprite.setOrigin(animator.getFrame()->w / 2, animator.getFrame()->h);
        sprite.setPosition(position);

        if (animator.getAnimation() != nullptr)
        {

            if (direction == Direction::LEFT)
            {
                animator.getAnimation()->setFlipH(true);
            }
            else if (direction == Direction::RIGHT)
            {
                animator.getAnimation()->setFlipH(false);
            }

            animator.getAnimation()->playForward(dt);
        }
        sprite.setTextureRect(intrect(*animator.getFrame()));
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        //target.setView(view);
        target.draw(sprite);
        if (debug)
        {
            target.draw(rect);
            Debug();
        }
    }

    void Cleanup()
    {

    }

    void Move()
    {
        if (state != State::MOVE)
        {
            state = State::MOVE;
            animator.setAnimation("MOVE");
        }
    }

    void Jump()
    {
        if (state != State::JUMP)
        {
            state = State::JUMP;
            animator.setAnimation("JUMP");
        }
    }

    void Fall()
    {
        if (state != State::FALL)
        {
            state = State::FALL;
            animator.setAnimation("FALL");
        }
    }

    void Roll()
    {
        if (state != State::ROLL)
        {
            state = State::ROLL;
            animator.setAnimation("ROLL");
        }
    }

    void Climb()
    {
        if (state != State::CLIMB)
        {
            state = State::CLIMB;
            animator.setAnimation("CLIMB");
        }
    }

    void Idle()
    {
        if (state != State::IDLE)
        {
            state = State::IDLE;
            animator.setAnimation("IDLE");
        }
    }

    void Debug() const
    {
        ImGui::Begin("Player object");

        ImGui::SeparatorText("Sprite::Texture");
        ImGui::Text("x = %d\ny = %d\nwidth = %d\nheight = %d",
                    sprite.getTextureRect().left,
                    sprite.getTextureRect().top,
                    sprite.getTextureRect().width,
                    sprite.getTextureRect().height);

        ImGui::SeparatorText("Sprite::Rect");
        ImGui::Text("x = %.1f\ny = %.1f\nwidth = %.1f\nheight = %.1f",
                    sprite.getGlobalBounds().top,
                    sprite.getGlobalBounds().left,
                    sprite.getGlobalBounds().width,
                    sprite.getGlobalBounds().height
        );

        ImGui::SeparatorText("Sprite::Origin");
        ImGui::Text("x = %.1f\ny = %.1f",
                    sprite.getOrigin().x,
                    sprite.getOrigin().y
        );

        ImGui::SeparatorText("Sprite::Position");
        ImGui::Text("x = %.1f\ny = %.1f",
                    sprite.getPosition().x,
                    sprite.getPosition().y
        );

        ImGui::SeparatorText("Player::Rect");
        ImGui::Text("x = %.1f\ny = %.1f\nwidth = %.1f\nheight = %.1f",
                    rect.getGlobalBounds().top,
                    rect.getGlobalBounds().left,
                    rect.getGlobalBounds().width,
                    rect.getGlobalBounds().height
        );

        ImGui::End();
    }
private:

    int w = 400;
    int h = 240;
    int cf = 6;
    float sp = 8.3f;
    float scale = 1.f;

    sf::Vector2f _size;

    sf::IntRect intrect(Animation::Frame& frame)
    {
        return sf::IntRect(frame.x, frame.y, frame.w, frame.h);
    }
};