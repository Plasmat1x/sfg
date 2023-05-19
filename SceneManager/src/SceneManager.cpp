#include "SceneManager.hpp"

IScene* SceneManager::scenes[3]{ nullptr, nullptr, nullptr };
size_t SceneManager::m_size = 3;
size_t SceneManager::c_size = 0;
bool SceneManager::changeScene = false;

SceneManager* SceneManager::_instance = nullptr;
ScnMgrDstr SceneManager::destroyer;


SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
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

void SceneManager::push(IScene* scene)
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

void SceneManager::popFromBegin()
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

void SceneManager::pop()
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

void SceneManager::replace(IScene* scene) // exception (try call methods deleted Scene object)
{
    if (c_size > 0)
    {
        pop();
        push(scene);
    }
    changeScene = true;
}

void SceneManager::swap()
{
}

void SceneManager::shift()
{
    IScene* tmp = scenes[c_size - 1];
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

IScene& SceneManager::begin()
{
    return *scenes[0];
}

IScene& SceneManager::end()
{
    return *scenes[c_size - 1];
}

IScene* SceneManager::top()
{
    return &end();
}

void SceneManager::clear()
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

size_t SceneManager::sizeMax()
{
    return m_size;
}

size_t SceneManager::size()
{
    return c_size;
}

bool SceneManager::isChange()
{
    if (changeScene)
    {
        changeScene = false;
        return true;
    }
    return false;
}

ScnMgrDstr::~ScnMgrDstr() { delete p_instance; }

void ScnMgrDstr::init(SceneManager* p)
{
    p_instance = p;
}

SceneManager& SceneManager::getInstance()
{
    if (!_instance)
    {
        _instance = new SceneManager();
        destroyer.init(_instance);
    }

    return *_instance;
}