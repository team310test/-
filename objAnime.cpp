//******************************************************************************
//
//
//      objPerform
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//--------------------------------------------------------------
//  ��]�A�j���[�V����
//--------------------------------------------------------------
void rotateAnime(OBJ2D* obj)
{
    obj->transform_->rotation_ += obj->actorComponent_->rotSpeed_;
}

//--------------------------------------------------------------
//  �g��E�k���A�j���[�V����
//--------------------------------------------------------------
void scaleAnime(OBJ2D* obj)
{
    static const float shrinkVelocity = -0.002f; // �k�����鑬�x(�k���̑����ɉe��)
    static int timer = 50;
    VECTOR2 targetScale = { obj->transform_->scale_.x * 1.2f, obj->transform_->scale_.x * 1.2f };

    if (obj->actorComponent_->isDrawShrink)
    {
        obj->renderer_->scale_ +=
        {
            obj->renderer_->scale_.x* shrinkVelocity,
            obj->renderer_->scale_.y* shrinkVelocity
        };
    }
    else
    {
        obj->renderer_->scale_ -=
        {
            obj->renderer_->scale_.x* shrinkVelocity,
                obj->renderer_->scale_.y* shrinkVelocity
        };
    }

    if ((obj->renderer_->scale_.x > targetScale.x || obj->renderer_->scale_.y > targetScale.y) && !obj->actorComponent_->isDrawShrink)
    {
        obj->actorComponent_->isDrawShrink = true;
        if (obj->renderer_->scale_ != targetScale)obj->renderer_->scale_ = targetScale;

    }
    if ((obj->renderer_->scale_.x < obj->transform_->scale_.x || obj->renderer_->scale_.y < obj->transform_->scale_.y) && obj->actorComponent_->isDrawShrink)
    {
        obj->actorComponent_->isDrawShrink = false;
        if (obj->renderer_->scale_ != obj->transform_->scale_)obj->renderer_->scale_ = obj->transform_->scale_;
    }
}