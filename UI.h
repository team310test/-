#pragma once

class UI
{
public:
    static void init();                 // �����ݒ�
    static void update();               // �X�V����

    static void drawShrinkValueMeter(); // �k���J�E���g�̌v��`��
    static void drawPlPartsCurrentCount(); // �v���C���[�p�[�c�̌��ݐ��`��
    static void drawLetterBox();        // �f��̍��ѕ`��(�}�X�N�����ōs���Ă���)

    static void drawResultJunks();
    static void drawResultTimes();

private:
    static const     int   DISP_METER_SHRINK_COUNT_MAX_TIME = 140;  // �ő�k���J�E���g��\�����鎞��
    static constexpr float METER_NEEDLE_ANGLE_MAX = 160.0f;         // �j���X���ő�p�x
    static constexpr float ADD_NEEDLE_ANGLE = DirectX::XMConvertToRadians(1.5f);   // �j�����Z
    static constexpr float SUB_NEEDLE_ANGLE = DirectX::XMConvertToRadians(-0.02f); // �j�����Z

public:
    static constexpr float UI_ALPHA_COLOR_MIN = 0.2f;            // UI�̍Œ�s�����x
    static constexpr float UI_ALPHA_COLOR_MAX = 1.0f;            // UI�̍ő�s�����x

private:
    static int   meterShrinkCount_;             // �v���C���[�k���J�E���g�ɍ��킹�ĕϓ�����J�E���g
    static int   dispMeterShrinkCountMaxTimer_; // �ő�k���J�E���g���������̊Ԍ�����^�C�}�[
    static float meterFrameAngle_;              // �v��̘g�̊p�x
    static float meterNeedleAngle_;             // �v��̐j�̊p�x
    static float subMeterNeedleAngle_;          // �v��̐j�̊p�x�����Z

    static float plPartsCountAlphaColor_;     // �v��̕s�����x
    static bool  isInAreaPlPartsCount_;       // OBJ���J�E���g�`��͈͓̔��ɓ����Ă��邩

public:
    static float meterAlphaColor_;              // �v��̕s�����x
    static bool  isInAreaMeter_;                // OBJ���v��͈͓̔��ɓ����Ă��邩

    static VECTOR2 meterPos_;                   // �v��̈ʒu
    static VECTOR2 plPartsCountPos_;

    static float letterBox_multiplySizeY_;      // �f��̍��т̏c��(����)

    static bool isSpawnResultJunks_;
    static bool isSpawnResultTimes_;
};

