
#include "all.h"

//--------------------------------------------------------------
//  �펞�A�j���[�V���� 
//--------------------------------------------------------------
// ��]�A�j���[�V����
void rotateAnime(OBJ2D* obj)
{
    obj->transform_->rotation_ += obj->actorComponent_->rotSpeed_;
}

//  �g��E�k���A�j���[�V����
void scaleAnime(OBJ2D* obj)
{
    float shrinkVelocity = obj->collider_->isShrink_ ?
        -0.005f : -0.002; // �k�����鑬�x(�k���̑����ɉe��)
    
    // �ڕW�̃X�P�[��
    VECTOR2 targetScale = { obj->transform_->scale_.x * 1.2f, obj->transform_->scale_.x * 1.2f };


    // �k��
    if (obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->drawScale_ +=
        {
            obj->renderer_->drawScale_.x* shrinkVelocity,
            obj->renderer_->drawScale_.y* shrinkVelocity
        };
    }
    // �g��
    if (!obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->drawScale_ -=
        {
            obj->renderer_->drawScale_.x* shrinkVelocity,
                obj->renderer_->drawScale_.y* shrinkVelocity
        };
    }

    // �ڕW�X�P�[���𒴂����isRenderShrink��true�ɂ���
    if ((obj->renderer_->drawScale_.x > targetScale.x || obj->renderer_->drawScale_.y > targetScale.y) && !obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->isDrawShrink_ = true;
        if (obj->renderer_->drawScale_ != targetScale)obj->renderer_->drawScale_ = targetScale;

    }
    // ����p�̃X�P�[�������ɂȂ��isRenderShrink��false�ɂ���
    if ((obj->renderer_->drawScale_.x < obj->transform_->scale_.x || obj->renderer_->drawScale_.y < obj->transform_->scale_.y) && obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->isDrawShrink_ = false;
        if (obj->renderer_->drawScale_ != obj->transform_->scale_)obj->renderer_->drawScale_ = obj->transform_->scale_;
    }
}

//--------------------------------------------------------------
//  �ꎞ�I�A�j���[�V���� 
//--------------------------------------------------------------
//  X���g��E�k���A�j���[�V����
bool xAxisSclaeAnime(OBJ2D* obj)
{
    float shrinkVelocity = obj->collider_->isShrink_ ?
        -0.08f : -0.07; // �k�����鑬�x(�k���̑����ɉe��)
    float magnificationVelocity = obj->collider_->isShrink_ ?
        -0.12f : -0.09; // �k�����鑬�x(�k���̑����ɉe��)

    // �ڕW�̃X�P�[��
    VECTOR2 targetScale = { obj->transform_->scale_.x * 1.4f, obj->transform_->scale_.y };


    // �k��
    if (obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->drawScale_ +=
        {
            obj->renderer_->drawScale_.x* shrinkVelocity,
                0
        };
    }
    // �g��
    if (!obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->drawScale_ -=
        {
            obj->renderer_->drawScale_.x* magnificationVelocity,
                0
        };
    }

    // �ڕW�X�P�[���𒴂����isRenderShrink��true�ɂ���
    if ((obj->renderer_->drawScale_.x > targetScale.x || obj->renderer_->drawScale_.y > targetScale.y) && !obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->isDrawShrink_ = true;
        if (obj->renderer_->drawScale_ != targetScale)obj->renderer_->drawScale_ = targetScale;

    }
    // ����p�̃X�P�[�������ɂȂ�� true��Ԃ�
    if ((obj->renderer_->drawScale_.x < obj->transform_->scale_.x || obj->renderer_->drawScale_.y < obj->transform_->scale_.y) && obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->drawScale_.x = obj->transform_->scale_.x;
        obj->renderer_->isDrawShrink_ = false;
        return true;
    }

    return false;
}
void setXAxisSclaeAnime(OBJ2D* obj)
{
    obj->renderer_->isDrawShrink_ = false;
    obj->renderer_->drawScale_ = obj->transform_->scale_;
    obj->actorComponent_->objAnimeTemporary_ = xAxisSclaeAnime;
}