#include "all.h"

FADE FADE::instance_;
FADE FADE::instance2_;

bool FADE::fadeOut(float add)
{
    alpha += add;
    if (alpha >= 1.0f)
    {
        alpha = 1.0f;
        return true;
    }
    return false;
}

bool FADE::fadeIn(float min)
{
    alpha -= min;
    if (alpha <= 0.0f) 
    {
        alpha = 0.0f;
        return true;
    }
    return false;
}

//  指定した値までフェードアウトする
bool FADE::fadeOutPoint(float add, float max)
{
    alpha += add;
    if (alpha >= max)
    {
        alpha = max;
        return true;
    }
    return false;
}

//  描画
void FADE::draw()
{
    VECTOR2 pos = { 0.0f,0.0f };
    VECTOR2 size = { BG::WINDOW_W, BG::WINDOW_H };
    VECTOR2 texpos = { 0.0f,0.0f };
    VECTOR4 coler[] = { {0.0f,0.0f,0.0f,alpha},{1.0f,1.0f,1.0f,alpha} };

    GameLib::primitive::rect(pos, size, texpos, 0, coler[colerNum]);
}

// 初期化
void FADE::clear()
{
    instance_.SetAlpha(0.0f);
    instance_.SetColerNum(COLER::BLACK);
    instance2_.SetAlpha(0.0f);
    instance2_.SetColerNum(COLER::BLACK);
}
