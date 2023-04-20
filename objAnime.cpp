
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
        -0.005f : -0.002; // 縮小する速度(縮小の速さに影響)
    
    // 目標のスケール
    VECTOR2 targetScale = { obj->transform_->scale_.x * 1.2f, obj->transform_->scale_.x * 1.2f };


    // 縮小
    if (obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->drawScale_ +=
        {
            obj->renderer_->drawScale_.x* shrinkVelocity,
            obj->renderer_->drawScale_.y* shrinkVelocity
        };
    }
    // 拡大
    if (!obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->drawScale_ -=
        {
            obj->renderer_->drawScale_.x* shrinkVelocity,
                obj->renderer_->drawScale_.y* shrinkVelocity
        };
    }

    // 目標スケールを超えるとisRenderShrinkをtrueにする
    if ((obj->renderer_->drawScale_.x > targetScale.x || obj->renderer_->drawScale_.y > targetScale.y) && !obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->isDrawShrink_ = true;
        if (obj->renderer_->drawScale_ != targetScale)obj->renderer_->drawScale_ = targetScale;

    }
    // 判定用のスケール未満になるとisRenderShrinkをfalseにする
    if ((obj->renderer_->drawScale_.x < obj->transform_->scale_.x || obj->renderer_->drawScale_.y < obj->transform_->scale_.y) && obj->renderer_->isDrawShrink_)
    {
        obj->renderer_->isDrawShrink_ = false;
        if (obj->renderer_->drawScale_ != obj->transform_->scale_)obj->renderer_->drawScale_ = obj->transform_->scale_;
    }
}