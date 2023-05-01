#include "all.h"

//******************************************************************************
//
//      BaseEffectBehavior（エフェクトのベース）
//
//******************************************************************************
void BaseEffectBehavior::move(OBJ2D* obj) const
{
    switch (obj->state_)
    {
    case 0:
        obj->renderer_->animeData_   = getParam()->ANIME;
        obj->transform_->scale_ = obj->weaponComponent_->parent_->transform_->scale_;

        obj->collider_->judgeFlag_          = false;    // あたり判定を行わない
        obj->collider_->isDrawAttackRect_   = false;    // あたり判定の領域を描画しない

        ++obj->state_;
        /*fallthrough*/
    case 1:
        startAllShrink(obj);    // 縮小開始
        shrink(obj);            // 画像縮小

        if (obj->collider_->isShrink_) break; // 縮小中なら飛ばす

        // 位置更新
        update(obj);        

        // アニメーション更新
        if (obj->renderer_->animeData_) obj->renderer_->animeUpdate();

        break;
    }
}


//******************************************************************************
//      EffectBombBehavior（爆発エフェクト）
//******************************************************************************
EffectBombBehavior::EffectBombBehavior()
{
    //param_.ANIME = spr;
}

void EffectBombBehavior::update(OBJ2D* obj) const
{
    //EffectComponent* e = obj->effectComponent_;
}
