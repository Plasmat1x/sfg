#pragma once

class SceneManager;

class SceneManagerDestroyer
{
public:
    ~SceneManagerDestroyer();
    void init(SceneManager* p);
};