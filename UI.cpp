#include "all.h"

float UI::needleAngle_ = 0.0f;              // �v��̐j�̊p�x
float UI::letterBox_multiplySizeY_ = 0.0f;  // �f��̍��т̏c��


// �����ݒ�
void UI::init()
{
    needleAngle_ = 0.0f;
    letterBox_multiplySizeY_ = 1.0f;
}

// �k���J�E���g�̌v��`��
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

    // �v��̘g
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

        // �g�`��
        texture::begin(sprNo);
        texture::draw(sprNo, pos, scale, texPos, size, center, angle, color);
        texture::end(sprNo);
    }


    // �v��̐j
    {
        // �k���J�E���g�ƍő�k���J�E���g��float�ɃL���X�g
        // �ifloat�ɃL���X�g����O��int���m�Ŋ���ƒl��0�ɂȂ��Đj�������Ȃ��Ȃ�̂Œ��Ӂj
        const float count    = static_cast<float>(BasePlayerBehavior::plShrinkCount_);
        const float countMax = static_cast<float>(BasePlayerBehavior::PL_SHRINK_COUNT_MAX);

        // ���݂̏k���J�E���g���ő�k���J�E���g�i10�j�Ŋ���A���̒l���ō��p�x�Ɋ|���Z�������̂����݂̊p�x�ɂ���
        // �i�k���J�E���g��0�Ȃ� �i 0 / 10 = �j  0�{�Łi90 *   0 = �j 0�x�A�j
        // �i�k���J�E���g��5�Ȃ� �i 5 / 10 = �j0.5�{�Łi90 * 0.5 = �j45�x�A�j
        // �i�k���J�E���g��10�Ȃ�i10 / 10 = �j ���{�Łi90 *   1 = �j90�x  �j
        const float currentAngle = DirectX::XMConvertToRadians(
            NEEDLE_ANGLE_MAX * (count / countMax)
        );

        static float subNeedleAngle = {};
        // �j�̓��������炩�ɂ��鏈��
        if (needleAngle_ < currentAngle) // angle�����݂̊p�x��菬�����ꍇ
        {
            subNeedleAngle = 0.0f;
            needleAngle_ += ADD_NEEDLE_ANGLE;    // ���Z
            if (needleAngle_ > currentAngle) needleAngle_ = currentAngle; // ���ߏC��
        }
        if (needleAngle_ > currentAngle) // angle�����݂̊p�x���傫���ꍇ
        {

            subNeedleAngle += SUB_NEEDLE_ANGLE;
            needleAngle_ += subNeedleAngle;    // ���Z
            if (needleAngle_ < currentAngle) needleAngle_ = currentAngle; // ���ߏC��
        }


        sprNo   = UI_METER_NEEDLE;
        pos     = { 100, 1000 };
        scale   = { 1, 1 };
        texPos  = {};
        size    = { 250, 250 };
        center  = { 125, 250 };
        angle   = needleAngle_ + DirectX::XMConvertToRadians(-35);
        color   = { 1, 1, 1, 1 };

        // �j�`��
        texture::begin(sprNo);
        texture::draw(sprNo, pos, scale, texPos, size, center, angle, color);
        texture::end(sprNo);
    }

}


// �f��̍��ѕ`��
void UI::drawLetterBox()
{
    VECTOR2 pos     = {};
    VECTOR2 size    = {};
    VECTOR2 center  = {};
    float   angle   = {};
    VECTOR4 color   = {};

    // �}�X�N�ŏ�����  
    {
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        pos     = { BG::WINDOW_W * 0.5f, BG::WINDOW_H * 0.5f };
        size    = { BG::WINDOW_W, BG::WINDOW_H * letterBox_multiplySizeY_ };
        center  = size * 0.5f;
        angle   = {};
        color   = {};

        GameLib::primitive::rect(pos, size, center);
    }
    
    // �}�X�N�ŏ�������
    {
        DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);

        pos     = {};
        size    = { BG::WINDOW_W, BG::WINDOW_H };
        center  = {};
        angle   = {};
        color   = { 0, 0, 0, 0.7f };

        GameLib::primitive::rect(pos, size, center, angle, color);
    }

    // �X�e���V�������Z�b�g
    DepthStencil::instance().clear();
    DepthStencil::instance().set(DepthStencil::MODE::NONE);
}
