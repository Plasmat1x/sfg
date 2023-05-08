template<typename T> T* Animator::GetAnimation()
{
    return reinterpret_cast<T*>(currentAnimation);
}

template<typename T> T* Animator::GetAnimation(std::string name)
{
    return reinterpret_cast<T*>(animations.at(name));
}