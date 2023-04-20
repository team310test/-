#include "all.h"

//bool isDebugDraw;

BG::BG()
    :player_(nullptr)
    , bgSprNo_(0)
{
    for (auto& bg : bg_)
    {
        bg = std::unique_ptr<OBJ2D>(
                new OBJ2D(
                    new Renderer,
                    new Collider,
                    this,
                    nullptr,
                    nullptr,
                    nullptr)
            );
    }
}


void BG::init(OBJ2D* player)
{
    player_ = player;

    // BG�p�f�[�^�̃N���A
    clear();

    //isDebugDraw = false;
}


void BG::clear()
{
    bg_[0]->transform_->scale_ = bg_[1]->transform_->scale_ = { 1, 1 };
    //bg_[2]->transform_->scale_ = bg_[3]->transform_->scale_ = { 2, 2 };

    bg_[0]->bg_->bgSprNo_ = BACK01;
    bg_[1]->bg_->bgSprNo_ = BACK01;
    //bg_[2]->bg_->bgSprNo_ = BACK01;
    //bg_[3]->bg_->bgSprNo_ = BACK01;


    int num = 1;

    for (auto& bg : bg_)
    {
        bg->collider_->size_        = { 3840, 1080 };
        bg->transform_->position_.x = (num % 2 == 0) // 2�Ŋ��ꂽ��
                                    ? 3840.0f + bg->collider_->size_.x * 0.5f // �ʒu���E���ɂ���
                                    : 0.0f    + bg->collider_->size_.x * 0.5f;
        bg->transform_->position_.y = bg->bg_->WINDOW_H * 0.5f;
        bg->collider_->targetScale_ = bg->transform_->scale_;
        bg->renderer_->color_       = { 1, 1, 1, 0.1f };

        bg->transform_->velocity_.x = -5.0f;

        ++num;
    }



}


void BG::update()
{
    moveBack();
}


// �w�i�X�V����(private)
static constexpr float subScaleValue = -0.0025f; // scale�̏k�����x
void BG::moveBack() const
{
    for (auto& bg : bg_)
    {
        Transform* t = bg->transform_;
        Collider*  c = bg->collider_;

        if (t->scale_.x <= 0.0f) continue; // scale��0�ȉ��Ȃ�continue

        // �ʒu�ɑ��x�𑫂�
        t->position_.x += (t->velocity_.x * t->scale_.x); // scale�̑傫���ŃX�N���[�����x�𒲐�

        // position�X�V
        if (t->position_.x + (c->size_.x * 0.5f) < 0.0f)
        {
            t->position_.x += (c->size_.x * 2.0f); // �摜�T�C�Y2���E�Ɉړ�
        }

        // scale�X�V
        if (t->scale_.x > c->targetScale_.x)
        {
            // scale����
            t->scale_ += (subScaleValue * t->scale_); // scale�̑傫���ŏk�����x�𒲐�

            if (t->scale_.x < c->targetScale_.x)
            {
                // �ڕW��菬�����Ȃ�����C��
                t->scale_ = c->targetScale_;
            }        
        }
    }

}


void BG::drawBack()
{
    // �w�i�`�悷��
    for (auto& bg : bg_)
    {
        if (bg->transform_->scale_.x <= 0.0f) continue;
        //if (bg->transform_->scale_.x >= 2.0f) continue;

        GameLib::texture::begin(bg->bg_->bgSprNo_);
        GameLib::texture::draw(
            bg->bg_->bgSprNo_,
            bg->transform_->position_, bg->transform_->scale_,
            { 0,0 }, bg->collider_->size_,
            {bg->collider_->size_.x * 0.5f, bg->collider_->size_.y * 0.5f, }, 
            0,
            bg->renderer_->color_
        );
        GameLib::texture::end(bg->bg_->bgSprNo_);
    }

}

void BG::setBGTargetScale()
{
    for (auto& bg : bg_)
    {
        if (bg->transform_->scale_.x <= 0) continue;

        // scale�̔�����ڕW�l�ɐݒ�
        bg->collider_->targetScale_ = bg->transform_->scale_ * 0.5f;
    }
}