#include "all.h"
#include <sstream>
#include <iomanip>

float   UI::meterAlphaColor_;              // �v��̕s�����x
bool    UI::isInAreaMeter_;                // OBJ���v��͈͓̔��ɓ����Ă��邩
int     UI::meterShrinkCount_;             // �v���C���[�k���J�E���g�ɍ��킹�ĕϓ�����J�E���g
int     UI::dispMeterShrinkCountMaxTimer_; // �ő�k���J�E���g���������̊Ԍ�����^�C�}�[
float   UI::meterFrameAngle_;              // �v��̘g�̊p�x
float   UI::meterNeedleAngle_;             // �v��̐j�̊p�x
float   UI::subMeterNeedleAngle_;          // �v��̐j�̊p�x�����Z
VECTOR2 UI::meterPos_;

float   UI::plPartsCountAlphaColor_;     // �J�E���g�̕s�����x
bool    UI::isInAreaPlPartsCount_;       // OBJ���J�E���g�`��͈͓̔��ɓ����Ă��邩
VECTOR2 UI::plPartsCountPos_;


float UI::letterBox_multiplySizeY_;      // �f��̍��т̏c��(����)


// �����ݒ�
void UI::init()
{
    meterAlphaColor_                = 1.0f;
    isInAreaMeter_                  = false;
    meterShrinkCount_               = 0;
    dispMeterShrinkCountMaxTimer_   = 0;
    meterFrameAngle_                = 0.0f;
    meterNeedleAngle_               = 0.0f;
    subMeterNeedleAngle_            = 0.0f;

    meterPos_ = { -850,850 };

    plPartsCountAlphaColor_       = 1.0f;
    isInAreaPlPartsCount_         = false;

    plPartsCountPos_ = { -850,-850 };

    letterBox_multiplySizeY_        = 1.0f;
}


void UI::update()
{
    // UI�͈͓̔���OBJ���N�����Ă��Ȃ����false�����f�����
    isInAreaMeter_        = false;
    isInAreaPlPartsCount_ = false;

    // UI�͈͓̔���OBJ���N�����Ă�����UI�𓧂���
    for (auto& p : *Game::instance()->obj2dManager()->getList())
    {
        if (p->behavior_ == nullptr) continue;

        Transform* t = p->transform_;

        // �v���C���[�p�[�c�J�E���g�͈̔̓`�F�b�N
        if (t->position_.x >= 0 && t->position_.x <= 300 &&
            t->position_.y >= 0 && t->position_.y <= 175)
        {
            isInAreaPlPartsCount_ = true;
        }

        // ���[�^�[�͈̔̓`�F�b�N
        if (t->position_.x >= 0  && t->position_.x <= 500 &&
            t->position_.y >= 575 && t->position_.y <= 1100)
        {
            isInAreaMeter_ = true;
        }

    }
}


// �k���J�E���g�̌v��`��
void UI::drawShrinkValueMeter()
{
    using namespace GameLib;

    // �g���܂킵�ϐ�
    int     sprNo   = 0;
    VECTOR2 pos     = {};
    VECTOR2 scale   = {};
    VECTOR2 texPos  = {};
    VECTOR2 size    = {};
    VECTOR2 center  = {};
    float   angle   = 0.0f;
    VECTOR4 color   = {};


    if (isInAreaMeter_) meterAlphaColor_ += (-0.05f); // �N�����Ă����瓧����
    else                meterAlphaColor_ +=   0.05f;  // �łȂ���Ζ߂�

    // �s�����x���߃`�F�b�N
    if (meterAlphaColor_ < UI_ALPHA_COLOR_MIN) meterAlphaColor_ = UI_ALPHA_COLOR_MIN;
    if (meterAlphaColor_ > UI_ALPHA_COLOR_MAX) meterAlphaColor_ = UI_ALPHA_COLOR_MAX;


    // �k���J�E���g�̐���
    {
        if (dispMeterShrinkCountMaxTimer_ > 0)  // timer�ɒl�������Ă���ꍇ
        {
            --dispMeterShrinkCountMaxTimer_;    // �J�E���g�_�E��

             // �^�C�}�[�Z�b�g���[�v����̂��߂ɃJ�E���g��1���炷
            if (dispMeterShrinkCountMaxTimer_ <= 0) --meterShrinkCount_;
        }
        else if (meterShrinkCount_ == BasePlayerBehavior::plShrinkCountMax_) // �J�E���g���k���K�v���Ɠ����ꍇ
        {
            // �^�C�}�[�Z�b�g
            dispMeterShrinkCountMaxTimer_ = DISP_METER_SHRINK_COUNT_MAX_TIME; 
        }
        else // �J�E���g�����炩�ɕϓ�������
        {
            if (meterShrinkCount_ < BasePlayerBehavior::plShrinkCount_) ++meterShrinkCount_;
            if (meterShrinkCount_ > BasePlayerBehavior::plShrinkCount_) --meterShrinkCount_;
        }

        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << meterShrinkCount_;

        // �g���܂킵�ϐ��Z�b�g
        {
            sprNo   = 0;
            pos     = VECTOR2(135, 990) + meterPos_;
            scale   = { 3.75f, 3.75f };
            texPos  = {};
            size    = {};
            center  = {};
            angle   = 0;
            color   = { 0, 0, 0, 0.2f };
        }

        // �����`��
        font::textOut(6, ss.str(), pos, scale, color, TEXT_ALIGN::MIDDLE);
    }


    // �v��̘g
    {
        // ��]
        {
            // �ő�J�E���g�Ɠ����Ȃ�
            if (meterShrinkCount_ == BasePlayerBehavior::plShrinkCountMax_)
            {            
                // ������]
                meterFrameAngle_ += ToRadian(8.5f); 
            }
            else if (meterShrinkCount_ > 0) // 0���傫�����
            {
                // �J�E���g�ɔ�Ⴕ�ĉ�]�����オ��
                meterFrameAngle_ += ToRadian(0.5f * meterShrinkCount_);
            }
            else // 0�ȉ��Ȃ�
            {
                // ����������]����
                meterFrameAngle_ += ToRadian(0.25f);
            }
        }

        // 360�x�������p�x���Z�b�g
        if (meterFrameAngle_ > ToRadian(360.0f))
        {
            meterFrameAngle_ += ToRadian(-360.0f);
        }

        // �g���܂킵�ϐ��Z�b�g
        {
            sprNo   = UI_METER_FRAME;
            pos     = VECTOR2(100, 1000) + meterPos_;
            scale   = { 3, 3 };
            texPos  = {};
            size    = { 250, 250 };
            center  = { 125, 125 };
            angle   = meterFrameAngle_;
            color   = { 1, 1, 1, meterAlphaColor_ };
        }

        // �g�`��
        texture::begin(sprNo);
        texture::draw(sprNo, pos, scale, texPos, size, center, angle, color);
        texture::end(sprNo);
    }


    // �v��̐j
    {
        // �k���J�E���g�Ək���K�v����float�ɃL���X�g
        // �ifloat�ɃL���X�g����O��int���m�Ŋ���ƒl��0�ɂȂ��Đj�������Ȃ��Ȃ�̂Œ��Ӂj
        const float count    = static_cast<float>(BasePlayerBehavior::plShrinkCount_);
        const float countMax = static_cast<float>(BasePlayerBehavior::plShrinkCountMax_);

        // ���݂̏k���J�E���g���ő�k���J�E���g�i10�j�Ŋ���A���̒l���ō��p�x�Ɋ|���Z�������̂����݂̊p�x�ɂ���
        // �i�k���J�E���g��0�Ȃ� �i 0 / 10 = �j  0�{�Łi90 *   0 = �j 0�x�A�j
        // �i�k���J�E���g��5�Ȃ� �i 5 / 10 = �j0.5�{�Łi90 * 0.5 = �j45�x�A�j
        // �i�k���J�E���g��10�Ȃ�i10 / 10 = �j ���{�Łi90 *   1 = �j90�x  �j
        const float currentAngle = DirectX::XMConvertToRadians(
            METER_NEEDLE_ANGLE_MAX * (count / countMax)
        );

        // �j�̓��������炩�ɂ��鏈��
        if (meterNeedleAngle_ < currentAngle) // angle�����݂̊p�x��菬�����ꍇ
        {
            subMeterNeedleAngle_ = 0.0f;
            meterNeedleAngle_    += ADD_NEEDLE_ANGLE;       // ���Z
            if (meterNeedleAngle_ > currentAngle) meterNeedleAngle_ = currentAngle; // ���ߏC��
        }
        if (meterNeedleAngle_ > currentAngle) // angle�����݂̊p�x���傫���ꍇ
        {
            subMeterNeedleAngle_ += SUB_NEEDLE_ANGLE;
            meterNeedleAngle_    += subMeterNeedleAngle_;   // ���Z
        //    if (meterNeedleAngle_ < currentAngle) meterNeedleAngle_ = currentAngle; // ���ߏC��
        }

        // �g���܂킵�ϐ��Z�b�g
        {
            sprNo   = UI_METER_NEEDLE;
            pos     = VECTOR2(100, 1000) + meterPos_;
            scale   = { 1.225f, 1.225f };
            texPos  = {};
            size    = { 250, 250 };
            center  = { 125, 125 };
            angle   = meterNeedleAngle_ + DirectX::XMConvertToRadians(-35);
            color   = { 1, 1, 1, meterAlphaColor_ };
        }

        // �j�`��
        texture::begin(sprNo);
        texture::draw(sprNo, pos, scale, texPos, size, center, angle, color);
        texture::end(sprNo);
    }

}


// �v���C���[�p�[�c�̌��ݐ��`��
void UI::drawPlPartsCurrentCount()
{
    using namespace GameLib;

    // �g���܂킵�ϐ�
    int     sprNo = 0;
    VECTOR2 pos = {};
    VECTOR2 scale = {};
    VECTOR2 texPos = {};
    VECTOR2 size = {};
    VECTOR2 center = {};
    float   angle = 0.0f;
    VECTOR4 color = {};

    if (isInAreaPlPartsCount_) plPartsCountAlphaColor_ += (-0.05f); // �N�����Ă����瓧����
    else                       plPartsCountAlphaColor_ +=   0.05f;  // �łȂ���Ζ߂�

    // �s�����x���߃`�F�b�N
    if (plPartsCountAlphaColor_ < UI_ALPHA_COLOR_MIN) plPartsCountAlphaColor_ = UI_ALPHA_COLOR_MIN;
    if (plPartsCountAlphaColor_ > UI_ALPHA_COLOR_MAX) plPartsCountAlphaColor_ = UI_ALPHA_COLOR_MAX;

    // ���ԕ`��
    {
        sprNo  = UI_METER_FRAME;
        pos    = VECTOR2(60, 60) + plPartsCountPos_;
        scale  = { 0.4f, 0.4f };
        size   = { 250,250 };
        center = size * 0.5f;
        color  = { 1,1,1, plPartsCountAlphaColor_ };

        // ���ԕ`��
        texture::begin(sprNo);
        texture::draw(sprNo, pos, scale, texPos, size, center, angle, color);
        texture::end(sprNo);
    }

    // �����`��
    {
        std::ostringstream ss;
        ss << "x" << BasePlayerBehavior::plPartsCurrentCount_;

        pos   = VECTOR2(125, 60) + plPartsCountPos_;
        scale = { 1.5f, 1.5f };
        color = { 0,0,0, plPartsCountAlphaColor_ };

        GameLib::font::textOut(
            6, ss.str(), pos, scale, color,
            GameLib::TEXT_ALIGN::MIDDLE_LEFT
        );
    }

}


// �f��̍��ѕ`��(�}�X�N�����ōs���Ă���)
void UI::drawLetterBox()
{
    // �g���܂킵�ϐ�
    VECTOR2 pos     = {};
    VECTOR2 size    = {};
    VECTOR2 center  = {};
    float   angle   = 0;
    VECTOR4 color   = {};

    // �}�X�N�ŏ�����  
    {
        DepthStencil::instance().set(DepthStencil::MODE::MASK);

        // �g���܂킵�ϐ��Z�b�g
        pos     = { BG::WINDOW_W * 0.5f, BG::WINDOW_H * 0.5f };
        size    = { BG::WINDOW_W, BG::WINDOW_H * letterBox_multiplySizeY_ };
        center  = size * 0.5f;
        angle   = 0;
        color   = {};

        GameLib::primitive::rect(pos, size, center);
    }
    
    // �}�X�N�ŏ�������
    {
        DepthStencil::instance().set(DepthStencil::MODE::EXCLUSIVE);

        // �g���܂킵�ϐ��Z�b�g
        pos     = {};
        size    = { BG::WINDOW_W, BG::WINDOW_H };
        center  = {};
        angle   = 0;
        color   = { 0, 0, 0, 0.8f };

        GameLib::primitive::rect(pos, size, center, angle, color);
    }

    // �X�e���V�������Z�b�g
    DepthStencil::instance().clear();
    DepthStencil::instance().set(DepthStencil::MODE::NONE);
}
