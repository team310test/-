#include "all.h"
#include <sstream>
#include <iomanip>

float UI::meterAlphaColor_;              // 計器の不透明度
bool  UI::isInAreaMeter_;                // OBJが計器の範囲内に入っているか
int   UI::meterShrinkCount_;             // プレイヤー縮小カウントに合わせて変動するカウント
int   UI::dispMeterShrinkCountMaxTimer_; // 最大縮小カウント数を少しの間見せるタイマー
float UI::meterFrameAngle_;              // 計器の枠の角度
float UI::meterNeedleAngle_;             // 計器の針の角度
float UI::subMeterNeedleAngle_;          // 計器の針の角度を減算
float UI::letterBox_multiplySizeY_;      // 映画の黒帯の縦幅(特殊)


// 初期設定
void UI::init()
{
    meterAlphaColor_                = 1.0f;
    isInAreaMeter_                  = false;
    meterShrinkCount_               = 0;
    dispMeterShrinkCountMaxTimer_   = 0;
    meterFrameAngle_                = 0.0f;
    meterNeedleAngle_               = 0.0f;
    subMeterNeedleAngle_            = 0.0f;
    letterBox_multiplySizeY_        = 1.0f;
}


// 縮小カウントの計器描画
void UI::drawShrinkValueMeter()
{
    using namespace GameLib;

    // 使いまわし変数
    int     sprNo   = 0;
    VECTOR2 pos     = {};
    VECTOR2 scale   = {};
    VECTOR2 texPos  = {};
    VECTOR2 size    = {};
    VECTOR2 center  = {};
    float   angle   = 0.0f;
    VECTOR4 color   = {};


    // メーターの範囲内にOBJが侵入していなければこのfalseが反映される
    isInAreaMeter_ = false; 

    // メーターの範囲内にOBJが侵入していたら計器を透かす
    for (auto& p : *Game::instance()->obj2dManager()->getList())
    {
        if (p->behavior_ == nullptr) continue;

        Transform* t = p->transform_;

        // 範囲チェック
        if (t->position_.x >= 50  && t->position_.x <= 500 &&
            t->position_.y >= 575 && t->position_.y <= 1100)
        {
            isInAreaMeter_ = true;
            break;
        }
    }

    if (isInAreaMeter_) meterAlphaColor_ += (-0.05f); // 侵入していたら透かす
    else                meterAlphaColor_ +=   0.05f;  // でなければ戻す

    // 不透明度超過チェック
    if (meterAlphaColor_ < METER_ALPHA_COLOR_MIN) meterAlphaColor_ = 0.2f;
    if (meterAlphaColor_ > METER_ALPHA_COLOR_MAX) meterAlphaColor_ = 1.0f;


    // 縮小カウントの数字
    {
        if (dispMeterShrinkCountMaxTimer_ > 0)  // timerに値が入っている場合
        {
            --dispMeterShrinkCountMaxTimer_;    // カウントダウン

             // タイマーセットループ回避のためにカウントを1減らす
            if (dispMeterShrinkCountMaxTimer_ <= 0) --meterShrinkCount_;
        }
        else if (meterShrinkCount_ == BasePlayerBehavior::plShrinkCountMax_) // カウントが縮小必要数と同じ場合
        {
            // タイマーセット
            dispMeterShrinkCountMaxTimer_ = DISP_METER_SHRINK_COUNT_MAX_TIME; 
        }
        else // カウントを滑らかに変動させる
        {
            if (meterShrinkCount_ < BasePlayerBehavior::plShrinkCount_) ++meterShrinkCount_;
            if (meterShrinkCount_ > BasePlayerBehavior::plShrinkCount_) --meterShrinkCount_;
        }

        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << meterShrinkCount_;

        // 使いまわし変数セット
        {
            sprNo   = 0;
            pos     = { 135, 990 };
            scale   = { 3.75f, 3.75f };
            texPos  = {};
            size    = {};
            center  = {};
            angle   = 0;
            color   = { 0, 0, 0, 0.2f };
        }

        // 数字描画
        font::textOut(6, ss.str(), pos, scale, color, TEXT_ALIGN::MIDDLE);
    }


    // 計器の枠
    {
        // 回転
        meterFrameAngle_ += DirectX::XMConvertToRadians(1.0f);

        if (meterFrameAngle_ > DirectX::XMConvertToRadians(360.0f))
        {
            //360度回ったら角度リセット
            meterFrameAngle_ = 0.0f; 
        }


        // 使いまわし変数セット
        {
            sprNo   = UI_METER_FRAME;
            pos     = { 100, 1000 };
            scale   = { 3, 3 };
            texPos  = {};
            size    = { 250, 250 };
            center  = { 125, 125 };
            angle   = meterFrameAngle_;
            color   = { 1, 1, 1, meterAlphaColor_ };
        }

        // 枠描画
        texture::begin(sprNo);
        texture::draw(sprNo, pos, scale, texPos, size, center, angle, color);
        texture::end(sprNo);
    }


    // 計器の目盛り(不使用)    
    {
        //sprNo   = UI_METER_READ;
        //pos     = { 100, 1000 };
        //scale   = { 3, 3 };
        //texPos  = {};
        //size    = { 250, 250 };
        //center  = { 125, 125 };
        //angle   = {};
        //color   = { 1, 1, 1, meterAlphaColor_ - 0.1f };
    
        //// 枠描画
        //texture::begin(sprNo);
        //texture::draw(sprNo, pos, scale, texPos, size, center, angle, color);
        //texture::end(sprNo);
    }


    // 計器の針
    {
        // 縮小カウントと縮小必要数をfloatにキャスト
        // （floatにキャストする前にint同士で割ると値が0になって針が動かなくなるので注意）
        const float count    = static_cast<float>(BasePlayerBehavior::plShrinkCount_);
        const float countMax = static_cast<float>(BasePlayerBehavior::plShrinkCountMax_);

        // 現在の縮小カウントを最大縮小カウント（10）で割り、その値を最高角度に掛け算したものを現在の角度にする
        // （縮小カウントが0なら （ 0 / 10 = ）  0倍で（90 *   0 = ） 0度、）
        // （縮小カウントが5なら （ 5 / 10 = ）0.5倍で（90 * 0.5 = ）45度、）
        // （縮小カウントが10なら（10 / 10 = ） 等倍で（90 *   1 = ）90度  ）
        const float currentAngle = DirectX::XMConvertToRadians(
            METER_NEEDLE_ANGLE_MAX * (count / countMax)
        );

        // 針の動きを滑らかにする処理
        if (meterNeedleAngle_ < currentAngle) // angleが現在の角度より小さい場合
        {
            subMeterNeedleAngle_ = 0.0f;
            meterNeedleAngle_    += ADD_NEEDLE_ANGLE;       // 加算
            if (meterNeedleAngle_ > currentAngle) meterNeedleAngle_ = currentAngle; // 超過修正
        }
        if (meterNeedleAngle_ > currentAngle) // angleが現在の角度より大きい場合
        {
            subMeterNeedleAngle_ += SUB_NEEDLE_ANGLE;
            meterNeedleAngle_    += subMeterNeedleAngle_;   // 減算
        //    if (meterNeedleAngle_ < currentAngle) meterNeedleAngle_ = currentAngle; // 超過修正
        }

        // 使いまわし変数セット
        {
            sprNo   = UI_METER_NEEDLE;
            pos     = { 100, 1000 };
            scale   = { 1.225f, 1.225f };
            texPos  = {};
            size    = { 250, 250 };
            center  = { 125, 125 };
            angle   = meterNeedleAngle_ + DirectX::XMConvertToRadians(-35);
            color   = { 1, 1, 1, meterAlphaColor_ };
        }

        // 針描画
        texture::begin(sprNo);
        texture::draw(sprNo, pos, scale, texPos, size, center, angle, color);
        texture::end(sprNo);
    }

}


// 映画の黒帯描画(マスク処理で行っている)
void UI::drawLetterBox()
{
    // 使いまわし変数
    VECTOR2 pos     = {};
    VECTOR2 size    = {};
    VECTOR2 center  = {};
    float   angle   = 0;
    VECTOR4 color   = {};

    // マスクで消す方  
    {
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        // 使いまわし変数セット
        pos     = { BG::WINDOW_W * 0.5f, BG::WINDOW_H * 0.5f };
        size    = { BG::WINDOW_W, BG::WINDOW_H * letterBox_multiplySizeY_ };
        center  = size * 0.5f;
        angle   = 0;
        color   = {};

        GameLib::primitive::rect(pos, size, center);
    }
    
    // マスクで消される方
    {
        DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);

        // 使いまわし変数セット
        pos     = {};
        size    = { BG::WINDOW_W, BG::WINDOW_H };
        center  = {};
        angle   = 0;
        color   = { 0, 0, 0, 0.7f };

        GameLib::primitive::rect(pos, size, center, angle, color);
    }

    // ステンシルをリセット
    DepthStencil::instance().clear();
    DepthStencil::instance().set(DepthStencil::MODE::NONE);
}
