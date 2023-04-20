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
    float shrinkVelocity = obj->collider_->isShrink_ ?
        -0.004f : -0.002; // �k�����鑬�x(�k���̑����ɉe��)
    
    // �ڕW�̃X�P�[��
    VECTOR2 targetScale = { obj->transform_->scale_.x * 1.2f, obj->transform_->scale_.x * 1.2f };


    // �k��
    if (obj->renderer_->isRenderShrink)
    {
        obj->renderer_->scale_ +=
        {
            obj->renderer_->scale_.x* shrinkVelocity,
            obj->renderer_->scale_.y* shrinkVelocity
        };
    }
    // �g��
    if (!obj->renderer_->isRenderShrink)
    {
        obj->renderer_->scale_ -=
        {
            obj->renderer_->scale_.x* shrinkVelocity,
                obj->renderer_->scale_.y* shrinkVelocity
        };
    }

    // �ڕW�X�P�[���𒴂����isRenderShrink��true�ɂ���
    if ((obj->renderer_->scale_.x > targetScale.x || obj->renderer_->scale_.y > targetScale.y) && !obj->renderer_->isRenderShrink)
    {
        obj->renderer_->isRenderShrink = true;
        if (obj->renderer_->scale_ != targetScale)obj->renderer_->scale_ = targetScale;

    }
    // ����p�̃X�P�[�������ɂȂ��isRenderShrink��false�ɂ���
    if ((obj->renderer_->scale_.x < obj->transform_->scale_.x || obj->renderer_->scale_.y < obj->transform_->scale_.y) && obj->renderer_->isRenderShrink)
    {
        obj->renderer_->isRenderShrink = false;
        if (obj->renderer_->scale_ != obj->transform_->scale_)obj->renderer_->scale_ = obj->transform_->scale_;
    }
}