#pragma once

class IObject
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Cleanup() = 0;
};