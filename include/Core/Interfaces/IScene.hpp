#pragma once

class IScene
{
public:
    virtual void Init() = 0;
    virtual void UpdateEvents() = 0;
    virtual void UpdateInput() = 0;
    virtual void Update(const float& dt) = 0;
    virtual void UpdatePast(const float& dt) = 0;
    virtual void UpdateFixed() = 0;
    virtual void Render() = 0;
    virtual void Cleanup() = 0;
    virtual void Debug() = 0;

};
