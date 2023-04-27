#include "all.h"


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
            nullptr
        );
    }
    //new char[2]; // ���������[�N�m�F

    // BG�p�f�[�^�̃N���A
    clear();

}


void BG::clear()
{
    // �X�P�[���ƃX�v���C�g�摜�̐ݒ�
    bg_[0]->transform_->scale_ = bg_[1]->transform_->scale_ = { 1, 1 };
    bg_[2]->transform_->scale_ = bg_[3]->transform_->scale_ = { 2, 2 };
    bg_[4]->transform_->scale_ = bg_[5]->transform_->scale_ = { 4, 4 };
    bg_[6]->transform_->scale_ = bg_[7]->transform_->scale_ = { 8, 8 };
    bg_[8]->transform_->scale_ = bg_[9]->transform_->scale_ = { 16, 16 };

    bg_[0]->bgSprNo_ = bg_[1]->bgSprNo_ = BACK01;
    bg_[2]->bgSprNo_ = bg_[3]->bgSprNo_ = BACK02;
    bg_[4]->bgSprNo_ = bg_[5]->bgSprNo_ = BACK01;
    bg_[6]->bgSprNo_ = bg_[7]->bgSprNo_ = BACK02;
    bg_[8]->bgSprNo_ = bg_[9]->bgSprNo_ = BACK01;


    int bgNum = 1; // �X�N���[���̉E���z�u�ݒ�p

    // �����ݒ�
    for (OBJ2D*& bg : bg_)
    {
        Transform* t = bg->transform_;
        Collider*  c = bg->collider_;
        Renderer*  r = bg->renderer_;

        c->targetScale_ = t->scale_;         // �X�P�[��
        c->size_        = { 3840, 1080 };    // �摜�T�C�Y

        t->position_.x  = (bgNum % 2 == 0) ? c->size_.x : 0.0f; // 2�Ŋ��ꂽ��X�N���[���̉E���S���ɂ���
        t->position_.y  = bg->bg_->WINDOW_H * 0.5f;             // y�����^�񒆂ɐݒ�i���h���j

        t->velocity_.x  = -5.0f;             // �X�N���[�����x

        r->color_   = { 1, 1, 1, 1 };        // �J���[
        r->color_.w = (t->scale_.x < DISP_BG_SCALE_MAX) // �s�����x
                    ? DEFAULT_ALPHA_COLOR : 0.0f; 
        r->targetColor_ = r->color_;         // �ڕW�J���[

        ++bgNum;
    }

}


void BG::update()
{
    moveBack();
}


// �w�i�X�V����(private)
float BG::subScale = -0.0035f;    // scale�̏k�����x
static constexpr float ADD_ALPHA_COLOR     =  0.001f;  // �s�����x�̑������x
static constexpr float SUBJECT_ALPHA_COLOR = -0.0025f; // �s�����x�̌������x
void BG::moveBack()
{
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

        if (t->scale_.x < DISP_BG_SCALE_MIN) continue;  // scale���ŏ��\����菬�������continue


/////////////// �X�P�[���X�V //////////////////////////
        if (t->scale_.x > c->targetScale_.x)
        {
            // scale����
            t->scale_ += (subScale * t->scale_); // scale�̑傫���ŏk�����x�𒲐��X�V

            // �ڕW��菬�����Ȃ�����C��
            if (t->scale_.x < c->targetScale_.x) t->scale_ = c->targetScale_;
        }


/////////////// �J���[�s�����x�X�V /////////////////////
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


/////////////// �ʒu�X�V /////////////////////////////
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

        if (t->scale_.x < DISP_BG_SCALE_MIN) continue; // scale���ŏ��\����菬�������continue
        if (t->scale_.x > DISP_BG_SCALE_MAX) continue; // scale���ő�\�����傫�����continue


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

        if (t->scale_.x < DISP_BG_SCALE_MIN) continue; // scale���ŏ��\����菬�������continue

        t->velocity_ *= 1.25f;

        // scale�̔�����ڕW�l�ɐݒ�
        c->targetScale_ = t->scale_ * 0.5f;

        // �s�����x�̓f�t�H���g��scale�̒l��1.0f�ȉ��Ȃ猸�炵�A�ő�\����菬������Α��₷
        if (t->scale_.x <= 1.0f) r->targetColor_.w = r->color_.w * 0.75f;
        else if (t->scale_.x <= DISP_BG_SCALE_MAX) r->targetColor_.w = DEFAULT_ALPHA_COLOR;
    }

}