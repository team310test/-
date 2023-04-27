#pragma once

class UI
{
public:
    static void init();

    static void drawShrinkValueMeter(); // k¬ƒJƒEƒ“ƒg‚ÌŒvŠí•`‰æ
    static void drawLetterBox();        // ‰f‰æ‚Ì•‘Ñ•`‰æ

private:
    static constexpr float NEEDLE_ANGLE_MAX = 160;   // j‚ªŒX‚­Å‘åŠp“x
    static constexpr float ADD_NEEDLE_ANGLE = DirectX::XMConvertToRadians(1.5f);   // ‰ÁZ
    //static constexpr float SUB_NEEDLE_ANGLE = DirectX::XMConvertToRadians(-0.65f); // Œ¸Z
    static constexpr float SUB_NEEDLE_ANGLE = DirectX::XMConvertToRadians(-0.02f); // Œ¸Z

public:
    static float needleAngle_;              // ŒvŠí‚Ìj‚ÌŠp“x
    static float letterBox_multiplySizeY_;  // ‰f‰æ‚Ì•‘Ñ‚Ìc•

};

