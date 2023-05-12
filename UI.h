#pragma once

class UI
{
public:
    static void init();                 // 初期設定

    static void drawShrinkValueMeter(); // 縮小カウントの計器描画
    static void drawLetterBox();        // 映画の黒帯描画(マスク処理で行っている)

private:
    static constexpr float METER_ALPHA_COLOR_MIN = 0.2f;            // 計器の最低不透明度
    static constexpr float METER_ALPHA_COLOR_MAX = 1.0f;            // 計器の最大不透明度
    static const     int   DISP_METER_SHRINK_COUNT_MAX_TIME = 180;  // 最大縮小カウントを表示する時間
    static constexpr float METER_NEEDLE_ANGLE_MAX = 160.0f;         // 針が傾く最大角度
    static constexpr float ADD_NEEDLE_ANGLE = DirectX::XMConvertToRadians(1.5f);   // 針を加算
    static constexpr float SUB_NEEDLE_ANGLE = DirectX::XMConvertToRadians(-0.02f); // 針を減算

private:
    static float meterAlphaColor_;              // 計器の不透明度
    static bool  isInAreaMeter_;                // OBJが計器の範囲内に入っているか
    static int   meterShrinkCount_;             // プレイヤー縮小カウントに合わせて変動するカウント
    static int   dispMeterShrinkCountMaxTimer_; // 最大縮小カウント数を少しの間見せるタイマー
    static float meterFrameAngle_;              // 計器の枠の角度
    static float meterNeedleAngle_;             // 計器の針の角度
    static float subMeterNeedleAngle_;          // 計器の針の角度を減算

public:
    static VECTOR2 meterPos_;                   // 計器の位置
    static float letterBox_multiplySizeY_;      // 映画の黒帯の縦幅(特殊)

};

