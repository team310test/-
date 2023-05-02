#include "all.h"

namespace
{
    GameLib::AnimeData animeEfcBomb[] = {
        { &sprEfcBomb_anime0,  10 },
        { &sprEfcBomb_anime1,  10 },
        { &sprEfcBomb_anime2,  10 },
        { nullptr,      -1 },    // 終了フラグ
    };
}


//******************************************************************************
//
//      BaseEffectBehavior（エフェクトのベース）
//
//******************************************************************************
void BaseEffectBehavior::move(OBJ2D* obj) const
{
    Collider* c = obj->collider_;
    Renderer* r = obj->renderer_;

    switch (obj->state_)
    {
    case 0:
        r->animeData_ = getParam()->ANIME;

        c->judgeFlag_ = false;    // あたり判定を行わない
        c->isDrawAttackRect_ = false;    // あたり判定の領域を描画しない

        ++obj->state_;
        /*fallthrough*/
    case 1:
        startAllShrink(obj);    // 縮小開始
        shrink(obj);            // 画像縮小

        //if (c->isShrink_) break; // 縮小中なら飛ばす


        // 更新
        update(obj);

        r->animeData_ = param_.ANIME;
        // アニメーション更新(アニメーションが終了すると自身を削除する)
        if (r->animeData_) if (r->animeUpdate())obj->behavior_ = nullptr;

        break;
    }
}


//******************************************************************************
//      EffectBombBehavior（爆発エフェクト）
//******************************************************************************
EffectBombBehavior::EffectBombBehavior()
{
    param_.ANIME = animeEfcBomb;
}

void EffectBombBehavior::update(OBJ2D* obj) const
{
    //if (obj->renderer_->animeData_->data == nullptr)
    //{
    //    obj->behavior_ = nullptr;
    //}
}