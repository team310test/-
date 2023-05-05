#pragma once

class FADE
{
public:
    enum COLER
    {
        BLACK = 0,
        WHITE,
    };
private:
    float alpha;        // ìßñæìx
    int colorNum;       // êFî‘çÜ

    static FADE instance_;
    static FADE instance2_;
public:
    FADE()
        :alpha(0.0f)
        , colorNum(COLER::BLACK){}
    bool fadeOut(float);
    bool fadeOutPoint(float, float);
    bool fadeIn(float);
    void SetColorNum(int color) { colorNum = color; }
    void SetAlpha(float a) { alpha = a; }
    void draw();
    static void clear();

    static FADE* getInstance() { return &instance_; }
    static FADE* getInstance2() { return &instance2_; }
};