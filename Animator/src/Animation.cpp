#include "Animation.hpp"

namespace anim {
    Animation::Animation() {
        isPlayed = false;
        looped = false;
        flip_h = false;
        flip_v = false;
        nCurrentFrame = -1;
        timer = 0.0f;
        speed = 0.0f;
        frequence = 0.0f;
        currentFrame = nullptr;
        flipbook = nullptr;
    }

    Animation::Animation(const int& x, const int& y,
                         const int& w, const int& h,
                         const int& count, const float& speed) {
        init(x, y, w, h, count, speed);
    }

    Animation::~Animation() {
        cleanup();
    }

    void Animation::init(const int& x, const int& y,
                         const int& w, const int& h,
                         const int& count, const float& speed) {
        this->looped = true;
        this->flip_h = false;
        this->flip_v = false;
        this->nCurrentFrame = 0;
        this->timer = 0.0f;
        this->speed = speed;
        this->frequence = 1.0f / speed;

        this->flipbook = new Flipbook(x, y, w, h, count);
        this->currentFrame = &flipbook->frames()[nCurrentFrame];
    }

    bool Animation::next() {
        isPlayed = true;
        //nCurrentFrame++;
        if (nCurrentFrame >= flipbook->size())
            if (!looped) {
                nCurrentFrame = flipbook->size() - 1;
                isPlayed = false;
                timer = 0.f;
                return isPlayed;
            }
            else {
                nCurrentFrame = 0;
            }

        currentFrame = &flipbook->frames()[nCurrentFrame];
        timer = 0.f;
        nCurrentFrame++;
        return isPlayed;
    }
    bool Animation::prev() {
        isPlayed = true;
        //nCurrentFrame--;
        if (nCurrentFrame < 0)
            if (!looped) {
                nCurrentFrame = 0;
                isPlayed = false;
                timer = 0.f;
                return isPlayed;
            }
            else {
                nCurrentFrame = flipbook->size() - 1;
            }

        currentFrame = &flipbook->frames()[nCurrentFrame];
        timer = 0.f;
        nCurrentFrame--;
        return isPlayed;
    }
    bool Animation::playForward(const float& dt) {
        if (!isPlayed) {
            nCurrentFrame = 0;
            isPlayed = true;
        }

        timer += dt;
        while (frequence < timer) {
            return next();
        }
        return isPlayed;
    }
    bool Animation::playBackward(const float& dt) {
        timer += dt;
        while (frequence < timer) {
            return prev();
        }
        return isPlayed;
    }
    Frame* Animation::getCurrentFrame() {
        return currentFrame;
    }
    bool Animation::isPlay() const {
        return isPlayed;
    }
    bool Animation::isLooped() const {
        return looped;
    }
    bool Animation::isFlipH() const {
        return flip_h;
    }
    bool Animation::isFlipV() const {
        return flip_v;
    }
    void Animation::setLoop(bool loop) {
        this->looped = loop;
    }
    void Animation::setSpeed(const float& speed) {
        this->speed = speed;
    }
    void Animation::setFlipH(bool flip_h) {
        this->flip_h = flip_h;
    }
    void Animation::setFlipV(bool flip_v) {
        this->flip_v = flip_v;
    }
    void Animation::cleanup() {
        delete flipbook;
    }
    void Animation::reset() {
        this->nCurrentFrame = 0;
        this->currentFrame = &flipbook->frames()[nCurrentFrame];
        this->timer = 0.0f;
    }

} // namespace Animation




