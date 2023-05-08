#include "Core/SceneManager.hpp"

IScene *SceneMgr::scenes[3]{nullptr, nullptr, nullptr};
size_t SceneMgr::m_size = 3;
size_t SceneMgr::c_size = 0;
bool SceneMgr::changeScene = false;

inline SceneMgr::SceneMgr()
{
}

SceneMgr::~SceneMgr()
{
    for (size_t i = 0; i < m_size; i++)
    {
        if (scenes[i])
        {
            delete scenes[i];
            scenes[i] = nullptr;
        }
    }
}

void SceneMgr::push(IScene *scene)
{
    if (c_size < m_size)
    {
        scenes[c_size++] = scene;
    }
    else
    {
        if (scenes[0])
        {
            delete scenes[0];
            scenes[0] = nullptr;
        }
        for (size_t i = 1; i < c_size; i++)
        {
            scenes[i - 1] = scenes[i];
        }
        scenes[c_size - 1] = scene;
    }

    changeScene = true;
}

void SceneMgr::popFromBegin()
{
    if (c_size > 0)
    {
        if (scenes[0])
        {
            delete scenes[0];
            scenes[0] = nullptr;
        }
        for (size_t i = 1; i < c_size; i++)
        {
            scenes[i - 1] = scenes[i];
        }
        c_size--;
    }
    changeScene = true;
}

void SceneMgr::pop()
{
    if (c_size > 0)
    {
        if (scenes[c_size - 1])
        {
            delete scenes[c_size - 1];
            scenes[c_size - 1] = nullptr;
        }
        c_size--;
    }
    changeScene = true;
}

void SceneMgr::replace(IScene *scene) // exception (try call methods deleted Scene object)
{
    if (c_size > 0)
    {
        pop();
        push(scene);
    }
    changeScene = true;
}

void SceneMgr::swap()
{
}

void SceneMgr::shift()
{
    IScene *tmp = scenes[c_size - 1];
    for (size_t i = 0; i < c_size; i++)
    {
        if (scenes[i])
        {
            delete scenes[i];
            scenes[i] = nullptr;
        }
        c_size = 0;
    }

    scenes[c_size++] = tmp;

    changeScene = true;
}

IScene &SceneMgr::begin()
{
    return *scenes[0];
}

IScene &SceneMgr::end()
{
    return *scenes[c_size - 1];
}

IScene *SceneMgr::top()
{
    return &end();
}

void SceneMgr::clear()
{
    for (size_t i = 0; i < c_size; i++)
    {
        if (scenes[i])
        {
            delete scenes[i];
            scenes[i] = nullptr;
            c_size--;
        }
    }
}

size_t SceneMgr::sizeMax()
{
    return m_size;
}

size_t SceneMgr::size()
{
    return c_size;
}

bool SceneMgr::isChange()
{
    if (changeScene)
    {
        changeScene = false;
        return true;
    }
    return false;
}