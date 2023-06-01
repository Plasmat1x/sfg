#pragma once

#include <SFML/Graphics.hpp>
#include <Animator.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

using namespace anim;

class Player;

class State {
protected:
    Player* player;

public:
    virtual ~State() {

    }

    void setPlayer(Player* p) {
        this->player = p;
    }

    virtual void Move() = 0;
    virtual void Jump() = 0;
    virtual void Roll() = 0;
    virtual void Fall() = 0;
    virtual void Idle() = 0;
    virtual void Climb() = 0;
};

class IdleState : public State {
public:
    void Idle() override;
    void Move() override;
    void Jump() override;
    void Fall() override;
    void Climb() override;
    void Roll() override;
};
class MoveState : public State {
public:
    void Idle() override;
    void Move() override;
    void Jump() override;
    void Fall() override;
    void Climb() override;
    void Roll() override;
};
class JumpState : public State {
public:
    void Idle() override;
    void Move() override;
    void Jump() override;
    void Fall() override;
    void Climb() override;
    void Roll() override;
};

class FallState : public State {
public:
    void Idle() override;
    void Move() override;
    void Jump() override;
    void Fall() override;
    void Climb() override;
    void Roll() override;
};
class ClimbState : public State {
public:

    void Idle() override;
    void Move() override;
    void Jump() override;
    void Fall() override;
    void Climb() override;
    void Roll() override;
};
class RollState : public State {
public:
    void Idle() override;
    void Move() override;
    void Jump() override;
    void Fall() override;
    void Climb() override;
    void Roll() override;

};

class Player : public sf::Drawable {
public:

    enum Dir {
        right,
        left
    };

    Animator animator;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RectangleShape rect;

    sf::Vector2f position;
    sf::Vector2f size;

    bool debug;

    State* state;

    Dir dir;

    Player() {

    }

    Player(sf::Vector2f p, sf::Vector2f s, sf::Texture t, State* state) {
        Init(p, s, t, state);
    }

    ~Player() {
        cleanup();
    }

    void Init(sf::Vector2f p, sf::Vector2f s, sf::Texture t, State* state) {

        dir = Dir::right;
        texture = t;
        position = p;
        size = s;

        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Magenta);
        rect.setOutlineThickness(1.f);

        w = 400;
        h = 240;
        cf = 6;
        sp = 8.3f;
        //scale = 1.f;
        scale = .25f;
        size.x = s.x * scale;
        size.y = s.y * scale;

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, w, h));
        sprite.setScale(scale, scale);

        animator.addAnimation("IDLE", new Animation(0, 0, w, h, cf, sp));
        animator.addAnimation("MOVE", new Animation(0, 1, w, h, cf, sp));
        animator.addAnimation("JUMP", new Animation(0, 2, w, h, cf - 2, sp));
        animator.addAnimation("FALL", new Animation(0, 3, w, h, cf - 2, sp));
        animator.addAnimation("CLIMB", new Animation(0, 4, w, h, cf, sp));
        animator.addAnimation("ROLL", new Animation(0, 5, w, h, cf + 1, sp));

        animator.getAnimation("ROLL")->setLoop(false);

        animator.setAnimation("IDLE");

        setState(state);
    }

    void Update(const float& dt) {
        rect.setSize(_size);
        rect.setOrigin(_size.x * 0.5f, _size.y);
        rect.setPosition(position);

        sprite.setOrigin(animator.getFrame()->w / 2, animator.getFrame()->h);
        sprite.setPosition(position);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        //target.setView(view);
        target.draw(sprite);
        if (debug)
        {
            target.draw(rect);
        }
    }

    void cleanup() {
        if (state) delete state;
    }

    void Move() {
        state->Move();
    }

    void Jump() {
        state->Jump();
    }

    void Fall() {
        state->Fall();
    }

    void Roll() {
        state->Roll();
    }

    void Climb() {
        state->Climb();
    }

    void Idle() {
        state->Idle();
    }

    void setState(State* state) {
        if (this->state) delete this->state;

        this->state = state;
        this->state->setPlayer(this);
    }

    void Debug() {
        ImGui::Begin("Player object");
        ImGui::Checkbox("Debug frame", &debug);

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

        if (ImGui::Button("Force IDLE state")) {
            setState(new IdleState);
        }

        ImGui::End();
    }

    void UpdateAnimation(const float& dt) {
        animator.getAnimation()->playForward(dt);

        if (dir == Dir::left) {
            sprite.setTextureRect(sf::IntRect(animator.getFrame()->x + animator.getFrame()->w, animator.getFrame()->y, -animator.getFrame()->w, animator.getFrame()->h));
        }
        else {
            sprite.setTextureRect(intrect(*animator.getFrame()));
        }
    }

    sf::Vector2f getCamPivot() {
        return sf::Vector2f(position.x, position.y - (size.y * 0.5f));
    }

    void setCam(sf::View* view) {
        view->setCenter(sf::Vector2f(position.x, position.y - (size.y * 0.5f)));
    }

private:

    int w = 400;
    int h = 240;
    int cf = 6;
    float sp = 8.3f;
    float scale = 1.f;

    sf::Vector2f _size;

    sf::IntRect intrect(anim::Frame& frame) {
        sf::IntRect _r(frame.x, frame.y, frame.w, frame.h);

        if (animator.getAnimation()->isFlipH()) {
            _r.left = frame.x + frame.w;
            _r.width = -frame.w;
        }
        if (animator.getAnimation()->isFlipV()) {
            _r.top = frame.y + frame.h;
            _r.height = -frame.h;
        }

        return _r;
    }
};



void IdleState::Idle() {
    if (player->animator.getAnimation() != nullptr) {
        player->animator.setAnimation("IDLE");
    }

}
void IdleState::Move() {
    player->setState(new MoveState);
}
void IdleState::Jump() {
    player->setState(new JumpState);
}
void IdleState::Fall() {

}
void IdleState::Climb() {

}
void IdleState::Roll() {
    player->setState(new RollState);
}


void MoveState::Idle() {
    player->setState(new IdleState);
}
void MoveState::Move() {
    player->animator.setAnimation("MOVE");
}
void MoveState::Jump() {
    player->setState(new JumpState);
}
void MoveState::Fall() {

}
void MoveState::Climb() {

}
void MoveState::Roll() {
    player->setState(new RollState);
}


void JumpState::Idle() {

}
void JumpState::Move() {

}
void JumpState::Jump() {
    player->animator.setAnimation("JUMP");
}
void JumpState::Fall() {
    player->setState(new FallState);
}
void JumpState::Climb() {

}
void JumpState::Roll() {

}

void FallState::Idle() {
    player->setState(new IdleState);
}
void FallState::Move() {

}
void FallState::Jump() {

}
void FallState::Fall() {
    player->animator.setAnimation("FALL");
}
void FallState::Climb() {

}
void FallState::Roll() {

}



void RollState::Idle() {
    if (!player->animator.getAnimation()->isPlay()) {
        player->setState(new IdleState);
    }
}
void RollState::Move() {
    if (!player->animator.getAnimation()->isPlay()) {
        player->setState(new IdleState);
    }
}
void RollState::Jump() {

}
void RollState::Fall() {

}
void RollState::Climb() {

}
void RollState::Roll() {
    player->animator.setAnimation("ROLL");

    if (!player->animator.getAnimation()->isPlay()) {
        player->setState(new IdleState);
    }
}