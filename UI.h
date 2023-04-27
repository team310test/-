#pragma once

class UI
{
public:
    static void init();

    static void drawShrinkValueMeter(); // �k���J�E���g�̌v��`��
    static void drawLetterBox();        // �f��̍��ѕ`��

private:
    static constexpr float NEEDLE_ANGLE_MAX = 160;   // �j���X���ő�p�x
    static constexpr float ADD_NEEDLE_ANGLE = DirectX::XMConvertToRadians(1.5f);   // ���Z
    //static constexpr float SUB_NEEDLE_ANGLE = DirectX::XMConvertToRadians(-0.65f); // ���Z
    static constexpr float SUB_NEEDLE_ANGLE = DirectX::XMConvertToRadians(-0.02f); // ���Z

public:
    static float needleAngle_;              // �v��̐j�̊p�x
    static float letterBox_multiplySizeY_;  // �f��̍��т̏c��

};

