#include "all.h"

float UI::needleAngle_ = 0.0f;              // 計器の針の角度
float UI::letterBox_multiplySizeY_ = 0.0f;  // 映画の黒帯の縦幅


// 初期設定
void UI::init()
{
    needleAngle_ = 0.0f;
    letterBox_multiplySizeY_ = 1.0f;
}

// 縮小カウントの計器描画
void UI::drawShrinkValueMeter()
{
    using namespace GameLib;

    int sprNo       = {};
    VECTOR2 pos     = {};
    VECTOR2 scale   = {};
    VECTOR2 texPos  = {};
    VECTOR2 size    = {};
    VECTOR2 center  = {};
    float   angle   = {};
    VECTOR4 color   = {};

    // 計器の枠
    {
        static float frameAngle = {};
        frameAngle += DirectX::XMConvertToRadians(1.0f);

        sprNo   = UI_METER_FRAME;
        pos     = { 100, 1000 };
        scale   = { 3, 3 };
        texPos  = {};
        size    = { 250, 250 };
        center  = { 125, 125 };
        angle   = frameAngle;
        color   = { 1, 1, 1, 1 };

        // 枠描画
        texture::begin(sprNo);
        texture::draw(sprNo, pos, scale, texPos, size, center, angle, color);
        texture::end(sprNo);
    }


    // 計器の針
    {
        // 縮小カウントと最大縮小カウントをfloatにキャスト
        // （floatにキャストする前にint同士で割ると値が0になって針が動かなくなるので注意）
        const float count    = static_cast<float>(BasePlayerBehavior::plShrinkCount_);
        const float countMax = static_cast<float>(BasePlayerBehavior::PL_SHRINK_COUNT_MAX);

        // 現在の縮小カウントを最大縮小カウント（10）で割り、その値を最高角度に掛け算したものを現在の角度にする
        // （縮小カウントが0なら （ 0 / 10 = ）  0倍で（90 *   0 = ） 0度、）
        // （縮小カウントが5なら （ 5 / 10 = ）0.5倍で（90 * 0.5 = ）45度、）
        // （縮小カウントが10なら（10 / 10 = ） 等倍で（90 *   1 = ）90度  ）
        const float currentAngle = DirectX::XMConvertToRadians(
            NEEDLE_ANGLE_MAX * (count / countMax)
        );

        static float subNeedleAngle = {};
        // 針の動きを滑らかにする処理
        if (needleAngle_ < currentAngle) // angleが現在の角度より小さい場合
        {
            subNeedleAngle = 0.0f;
            needleAngle_ += ADD_NEEDLE_ANGLE;    // 加算
            if (needleAngle_ > currentAngle) needleAngle_ = currentAngle; // 超過修正
        }
        if (needleAngle_ > currentAngle) // angleが現在の角度より大きい場合
        {

            subNeedleAngle += SUB_NEEDLE_ANGLE;
            needleAngle_ += subNeedleAngle;    // 減算
            if (needleAngle_ < currentAngle) needleAngle_ = currentAngle; // 超過修正
        }


        sprNo   = UI_METER_NEEDLE;
        pos     = { 100, 1000 };
        scale   = { 1, 1 };
        texPos  = {};
        size    = { 250, 250 };
        center  = { 125, 250 };
        angle   = needleAngle_ + DirectX::XMConvertToRadians(-35);
        color   = { 1, 1, 1, 1 };

        // 針描画
        texture::begin(sprNo);
        texture::draw(sprNo, pos, scale, texPos, size, center, angle, color);
        texture::end(sprNo);
    }

}


// 映画の黒帯描画
void UI::drawLetterBox()
{
    VECTOR2 pos     = {};
    VECTOR2 size    = {};
    VECTOR2 center  = {};
    float   angle   = {};
    VECTOR4 color   = {};

    // マスクで消す方  
    {
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        pos     = { BG::WINDOW_W * 0.5f, BG::WINDOW_H * 0.5f };
        size    = { BG::WINDOW_W, BG::WINDOW_H * letterBox_multiplySizeY_ };
        center  = size * 0.5f;
        angle   = {};
        color   = {};

        GameLib::primitive::rect(pos, size, center);
    }
    
    // マスクで消される方
    {
        DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);

        pos     = {};
        size    = { BG::WINDOW_W, BG::WINDOW_H };
        center  = {};
        angle   = {};
        color   = { 0, 0, 0, 0.7f };

        GameLib::primitive::rect(pos, size, center, angle, color);
    }

    // ステンシルをリセット
    DepthStencil::instance().clear();
    DepthStencil::instance().set(DepthStencil::MODE::NONE);
}
