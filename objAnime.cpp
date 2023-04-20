//******************************************************************************
//
//
//      objPerform
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//--------------------------------------------------------------
//  回転アニメーション
//--------------------------------------------------------------
void rotateAnime(OBJ2D* obj)
{
    obj->transform_->rotation_ += obj->actorComponent_->rotSpeed_;
}

//--------------------------------------------------------------
//  拡大・縮小アニメーション
//--------------------------------------------------------------
void scaleAnime(OBJ2D* obj)
{
    float shrinkVelocity = obj->collider_->isShrink_ ?
        -0.004f : -0.002; // 縮小する速度(縮小の速さに影響)
    
    // 目標のスケール
    VECTOR2 targetScale = { obj->transform_->scale_.x * 1.2f, obj->transform_->scale_.x * 1.2f };


    // 縮小
    if (obj->renderer_->isRenderShrink)
    {
        obj->renderer_->scale_ +=
        {
            obj->renderer_->scale_.x* shrinkVelocity,
            obj->renderer_->scale_.y* shrinkVelocity
        };
    }
    // 拡大
    if (!obj->renderer_->isRenderShrink)
    {
        obj->renderer_->scale_ -=
        {
            obj->renderer_->scale_.x* shrinkVelocity,
                obj->renderer_->scale_.y* shrinkVelocity
        };
    }

    // 目標スケールを超えるとisRenderShrinkをtrueにする
    if ((obj->renderer_->scale_.x > targetScale.x || obj->renderer_->scale_.y > targetScale.y) && !obj->renderer_->isRenderShrink)
    {
        obj->renderer_->isRenderShrink = true;
        if (obj->renderer_->scale_ != targetScale)obj->renderer_->scale_ = targetScale;

    }
    // 判定用のスケール未満になるとisRenderShrinkをfalseにする
    if ((obj->renderer_->scale_.x < obj->transform_->scale_.x || obj->renderer_->scale_.y < obj->transform_->scale_.y) && obj->renderer_->isRenderShrink)
    {
        obj->renderer_->isRenderShrink = false;
        if (obj->renderer_->scale_ != obj->transform_->scale_)obj->renderer_->scale_ = obj->transform_->scale_;
    }
}