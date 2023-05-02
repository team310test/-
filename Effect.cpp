#include "all.h"

namespace 
{
    GameLib::AnimeData animeEfcBomb[] = {
        { &sprEfcBomb_anime0,  2  },
        { &sprEfcBomb_anime1,  2  },
        { &sprEfcBomb_anime2,  2  },
        { &sprEfcBomb_anime3,  3  },
        { nullptr,            -1  },    // 終了フラグ
    };
}


//******************************************************************************
//
//      BaseEffectBehavior（エフェクトのベース）
//
//******************************************************************************
void BaseEffectBehavior::move(OBJ2D* obj) const
{
    Collider*  c = obj->collider_;
    Renderer*  r = obj->renderer_;

    switch (obj->state_)
    {
    case 0:
        r->animeData_   = getParam()->ANIME;

        c->judgeFlag_           = false;    // あたり判定を行わない
        c->isDrawAttackRect_    = false;    // あたり判定の領域を描画しない

        ++obj->state_;
        /*fallthrough*/
    case 1:
        update(obj);        

        break;
    }
}

void BaseEffectBehavior::update(OBJ2D* obj) const
{
    Renderer* r = obj->renderer_;

    // 徐々に薄くする
    //float addColor = -0.04f;
    //r->color_ = {
    //    r->color_.x + addColor, r->color_.y + addColor, 
    //    r->color_.z + addColor, r->color_.w + addColor
    //};
    //r->targetColor_ = r->color_;

    if (!r->animeData_) return; // アニメデータがなければreturn

    // アニメが回り切ったら消去
    if (r->animeUpdate()) obj->behavior_ = nullptr;

}


//******************************************************************************
//      EffectBombBehavior（爆発エフェクト）
//******************************************************************************
EffectBombBehavior::EffectBombBehavior()
{
    param_.ANIME = animeEfcBomb;
}
