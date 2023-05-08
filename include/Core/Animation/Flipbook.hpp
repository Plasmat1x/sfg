#pragma once

class Frame;

class Flipbook
{
public:
    int count;
    Frame* frames;

    Flipbook();
    Flipbook(
        const int& x, const int& y,
        const int& w, const int& h,
        const int& c);

    ~Flipbook();

    void Init(const int& x, const int& y,
              const int& w, const int& h,
              const int& c);

};