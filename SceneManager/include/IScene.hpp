#pragma once

class IScene {
public:
    virtual void init() = 0;
    virtual void updateEvents() = 0;
    virtual void updateInput() = 0;
    virtual void update(const float& dt) = 0;
    virtual void updatePast(const float& dt) = 0;
    virtual void updateFixed() = 0;
    virtual void render() = 0;
    virtual void cleanup() = 0;
    virtual void debug(const float& dt) = 0;
};
