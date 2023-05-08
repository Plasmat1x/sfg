#pragma once

#include "Core/Interfaces/IScene.hpp"

class SceneMgr
{
public:
    static void push(IScene *scene);
    static void pop();
    static void popFromBegin();
    static void replace(IScene *scene);
    static void swap();
    static void shift();

    static IScene &begin();
    static IScene &end();

    static IScene *top();

    static void clear();

    static size_t sizeMax();
    static size_t size();

    static bool isChange();

private:
    static IScene *scenes[];
    static size_t m_size;
    static size_t c_size;
    static bool changeScene;

    SceneMgr();
    ~SceneMgr();
};