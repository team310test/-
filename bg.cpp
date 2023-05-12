#include "all.h"

float BG::bgSubScale_           = 0.0f; // �X�P�[���̏k�����x
int   BG::bgSprTableIndex_      = 0;    // �w�i�e�[�u���z��̌��݂̗v�f��
int   BG::isAddbgSprTableIndex_ = 1;    // bgSprTableIndex_�����Z���邩���߂�


// �w�i�z��
const int bgSprites[] = {
    GAME_TEXNO::BG01,
    GAME_TEXNO::BG02,
    GAME_TEXNO::BG03,
    GAME_TEXNO::BG04,
    GAME_TEXNO::BG05,
    GAME_TEXNO::BG06,
    GAME_TEXNO::BG07,
    GAME_TEXNO::BG08,
    GAME_TEXNO::BG09,
    GAME_TEXNO::BG_END,
};

BG::BG()
    :bg_()
{
}


BG::~BG()
{
    for (OBJ2D*& bg : bg_) safe_delete(bg);
}


void BG::init()
{
    //new char[1]; // ���������[�N�m�F
    for (OBJ2D*& bg : bg_)
    {
        bg = new OBJ2D(
            new Renderer,
            new Collider,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr
        );
    }
    //new char[2]; // ���������[�N�m�F

    bgSubScale_           = BG_SHRINK_SPEED;
    bgSprTableIndex_      = 0;
    isAddbgSprTableIndex_ = 1;

    // BG�p�f�[�^�̃N���A
    clear();

}


void BG::clear()
{
    // �X�P�[���ƃX�v���C�g�摜�̐ݒ�
    bg_[0]->transform_->scale_   = bg_[1]->transform_->scale_   = { 1, 1 };
    bg_[2]->transform_->scale_   = bg_[3]->transform_->scale_   = { 5, 5 };
    bg_[4]->transform_->scale_   = bg_[5]->transform_->scale_   = { 10, 10 };
    bg_[6]->transform_->scale_   = bg_[7]->transform_->scale_   = { 50, 50 };
    bg_[8]->transform_->scale_   = bg_[9]->transform_->scale_   = { 100, 100 };
    bg_[10]->transform_->scale_  = bg_[11]->transform_->scale_  = { 500, 500 };

    bg_[0]->bgSprNo_   = bg_[1]->bgSprNo_   = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;
    bg_[2]->bgSprNo_   = bg_[3]->bgSprNo_   = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;
    bg_[4]->bgSprNo_   = bg_[5]->bgSprNo_   = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;
    bg_[6]->bgSprNo_   = bg_[7]->bgSprNo_   = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;
    bg_[8]->bgSprNo_   = bg_[9]->bgSprNo_   = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;
    bg_[10]->bgSprNo_  = bg_[11]->bgSprNo_  = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;


    int bgSetPosXNum = 1; // �X�N���[���̉E���z�u�ݒ�p

    // �����ݒ�
    for (OBJ2D*& bg : bg_)
    {
        Transform* t = bg->transform_;
        Collider*  c = bg->collider_;
        Renderer*  r = bg->renderer_;

        c->targetScale_ = t->scale_;         // �X�P�[��
        c->size_        = { 3840, 1080 + 256 };    // �摜�T�C�Y

        t->position_.x  = (bgSetPosXNum % 2 == 0) ? c->size_.x : 0.0f; // 2�Ŋ��ꂽ��X�N���[���̉E���S���ɂ���
        t->position_.y  = bg->bg_->WINDOW_H * 0.5f;             // y�����^�񒆂ɐݒ�i���h���j

        t->velocity_.x  = BG_SCROLL_SPEED;                      // �X�N���[�����x

        r->color_       = { 1, 1, 1, 1 };                       // �J���[
        r->color_.w     = (t->scale_.x < DISP_BG_SCALE_MAX)     // �s�����x
                        ? DEFAULT_ALPHA_COLOR : 0.0f; 
        r->targetColor_ = r->color_;                            // �ڕW�J���[

        ++bgSetPosXNum;
    }

}


void BG::update()
{
    moveBack();
}


// �w�i�X�V����(private)
static constexpr float ADD_ALPHA_COLOR     =  0.001f;  // �s�����x�̑������x
static constexpr float SUBJECT_ALPHA_COLOR = -0.0025f; // �s�����x�̌������x
void BG::moveBack()
{
    // �ŏ��ƍŌ�̔w�i�̃X�P�[���m�F
    //GameLib::debug::setString("bg[0]Scale:%f", bg_[0]->transform_->scale_.x);
    //GameLib::debug::setString("bg[11]Scale:%f", bg_[11]->transform_->scale_.x);

    for (OBJ2D*& bg : bg_)
    {
        Transform* t = bg->transform_;
        Renderer*  r = bg->renderer_;
        Collider*  c = bg->collider_;

        // �l�m�F
        {
            //GameLib::debug::setString("position + size:%f", (t->position_.x + c->size_.x)); // �摜�̉E�[�̒l
            //GameLib::debug::setString("scale:%f", t->scale_.x); // �X�P�[��
            //GameLib::debug::setString("color.z:%f", r->color_.w); // �s�����x
        }

/////////////// �X�P�[���X�V //////////////////////////////////////////////

        if (t->scale_.x > c->targetScale_.x)
        {
            // scale����
            t->scale_ += (bgSubScale_ * t->scale_); // scale�̑傫���ŏk�����x�𒲐��X�V

            // �ڕW��菬�����Ȃ�����C��
            if (t->scale_.x < c->targetScale_.x) t->scale_ = c->targetScale_;
        }

/////////////// �J���[�s�����x�X�V /////////////////////////////////////////

        if (r->color_.w > r->targetColor_.w) // �ڕW�l���傫���ꍇ
        {
            // �s�����x����
            r->color_.w += (SUBJECT_ALPHA_COLOR * r->color_.w);

            // ���ߕ����C��
            if (r->color_.w < r->targetColor_.w) r->color_.w = r->targetColor_.w;
        }
        else if (r->color_.w < r->targetColor_.w) // �ڕW�l��菬�����ꍇ
        {
            // �s�����x����
            r->color_.w += ADD_ALPHA_COLOR;

            // ���ߕ����C��
            if (r->color_.w > r->targetColor_.w) r->color_.w = r->targetColor_.w;
        }


/////////////// �ʒu�X�V ///////////////////////////////////////////////////

        if (t->scale_.x > DISP_BG_SCALE_MAX) continue;  // scale���ő�\�����傫����Έʒu���X�V���Ȃ�
        
        // �ʒu�ɑ��x�𑫂�
        if (t->scale_.x == c->targetScale_.x) t->position_.x += (t->velocity_.x * t->scale_.x); // scale�̑傫���ŃX�N���[�����x�𒲐��i�������i�����j�قǂ������ɂȂ�j

        // �摜�̉E�[����ʍ��[�𒴂�����摜�T�C�Y2���E�Ɉړ�
        if ( (t->position_.x + c->size_.x) < 0) t->position_.x += (c->size_.x * 2.0f);  
        
    }

}


void BG::drawBack()
{
    // �w�i�`�悷��
    for (OBJ2D*& bg : bg_)
    {
        Transform* t = bg->transform_;
        Collider*  c = bg->collider_;
        Renderer*  r = bg->renderer_;

        GameLib::texture::begin(bg->bgSprNo_);
        GameLib::texture::draw(
            bg->bgSprNo_,
            t->position_, t->scale_,
            { 0, 0 }, c->size_,
            { 0.0f,  (c->size_.y * 0.5f) }, 
            0,
            r->color_
        );
        GameLib::texture::end(bg->bgSprNo_);
    }

}


void BG::setBGShrink()
{
    for (OBJ2D*& bg : bg_)
    {
        Transform* t = bg->transform_;
        Collider*  c = bg->collider_;
        Renderer*  r = bg->renderer_;

        // �摜�X�V(targetScale�����߂�K�v������̂ł����ŏ������s��)
        if( (t->scale_.x >= 0.01f && t->scale_.x <= 0.011f) || t->scale_.x == 0.05f)
        {
            // �w�i���Ō�̔w�i�Ȃ炻�̂܂܁A�����łȂ���Ύ��̔w�i�ɂ���
            bg->bgSprNo_ = (bgSprites[bgSprTableIndex_] < BG_END)
                         ? bgSprites[bgSprTableIndex_]
                         : bg->bgSprNo_;
            if (isAddbgSprTableIndex_ % 2 == 0) ++bgSprTableIndex_;
            ++isAddbgSprTableIndex_;

            if (t->scale_.x >= 0.01f && t->scale_.x <= 0.011f) t->scale_ = { 10,10 };
            if (t->scale_.x == 0.05f) t->scale_ = { 50, 50 };

            r->color_ = { 1,1,1,0 };
            r->targetColor_ = r->color_;
        }

        t->velocity_ *= 1.15f;

        // scale��?��ڕW�l�ɐݒ�
        c->targetScale_ = t->scale_ * 0.1f;

        bgSubScale_ = BG_SHRINK_SPEED; // �k�����x�����Z�b�g

        // �s�����x�̓f�t�H���g��scale�̒l��1.0f�ȉ��Ȃ猸�炵�A�ő�\����菬������Α��₷
        if (t->scale_.x <= 1.0f) r->targetColor_.w = r->color_.w * 0.25f;
        else if (t->scale_.x <= DISP_BG_SCALE_MAX) r->targetColor_.w = DEFAULT_ALPHA_COLOR;

    }

}