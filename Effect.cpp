#include "all.h"

namespace 
{
    // 爆発アニメ
    GameLib::AnimeData animeEfcBomb[] = {
        { &sprEfcBomb_anime0,  2  },
        { &sprEfcBomb_anime1,  2  },
        { &sprEfcBomb_anime2,  2  },
        { &sprEfcBomb_anime3,  3  },
        { nullptr,            -1  },    // 終了フラグ
    };

    // 合体アニメ
    GameLib::AnimeData animeEfcCombine[] = {
    { &sprEfcCombine_anime0,  4  },
    { &sprEfcCombine_anime1,  4  },
    { &sprEfcCombine_anime2,  4  },
    { &sprEfcCombine_anime3,  4  },
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
    const float addColor = -0.035f;
    r->color_ = {
        r->color_.x + addColor, r->color_.y + addColor,
        r->color_.z + addColor, r->color_.w + addColor
    };
    r->targetColor_ = r->color_;

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

//******************************************************************************
//      EffectBombBehavior（爆発エフェクト）
//******************************************************************************
EffectCombineBehavior::EffectCombineBehavior()
{
    param_.ANIME = animeEfcCombine;
}

void EffectCombineBehavior::update(OBJ2D* obj) const
{
    Transform*  t = obj->transform_;

    //// 親がいれば親の位置を代入して親に追従する
    //// 読み取りアクセス違反のエラーが起きる
    //if (e->parent_ != nullptr)
    //{
    //    if (e->parent_->behavior_ != nullptr)
    //    {
    //        t->position_.x = e->parent_->transform_->position_.x;
    //        t->position_.y = e->parent_->transform_->position_.y;
    //    }
    //}

    // パーツと同じ処理でエフェクトを追従させる
    Transform* plCore = Game::instance()->player_->transform_;

    t->velocity_  = plCore->velocity_;
    t->position_ += plCore->velocity_;

    // アニメーション更新
    BaseEffectBehavior::update(obj);
}
