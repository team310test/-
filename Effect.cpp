#include "all.h"

namespace 
{
    // 鼓動アニメ
    GameLib::AnimeData animeEfcBeat[] = {
        { &sprTitlePlayerCore, 10 },
        { nullptr,             -1 },
    };

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
        { nullptr,               -1  },    // 終了フラグ
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
        r->animeData_ = getParam()->ANIME;

        c->judgeFlag_ = false;    // あたり判定を行わない
        c->isDrawAttackRect_ = false;    // あたり判定の領域を描画しない

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
    const float addColor = -0.04f;
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
//      EffectBeatBehavior（鼓動エフェクト）
//******************************************************************************
EffectBeatBehavior::EffectBeatBehavior()
{
    param_.ANIME = animeEfcBeat;
}

void EffectBeatBehavior::update(OBJ2D* obj) const
{
    Transform* t = obj->transform_;
    Renderer*  r = obj->renderer_;

    t->scale_       += { 0.06f, 0.06f };
    r->drawScale_    = t->scale_;
    r->color_.w     += -0.05f;
    r->targetColor_  = r->color_;

    if (r->color_.w <= 0)
    {
        obj->behavior_ = nullptr;
        return;
    }

    if (r->animeData_) r->animeUpdate();
}

//******************************************************************************
//      EffectBombBehavior（爆発エフェクト）
//******************************************************************************
EffectBombBehavior::EffectBombBehavior()
{
    param_.ANIME = animeEfcBomb;
}

//******************************************************************************
//      EffectCombineBehavior（合体エフェクト）
//******************************************************************************
EffectCombineBehavior::EffectCombineBehavior()
{
    param_.ANIME = animeEfcCombine;
}

void EffectCombineBehavior::update(OBJ2D* obj) const
{
    if (!Game::instance()->player_)            return;
    if (!Game::instance()->player_->behavior_) return;

    Transform* t       = obj->transform_;
    Transform* plCoreT = Game::instance()->player_->transform_;

    // プレイヤーパーツと同じ処理でエフェクトを追従させる  
    // プレイヤーコアの速度を代入
    t->velocity_ = plCoreT->velocity_;
    // 縮小中でなければ位置に速度を足す
    if (!Behavior::isObjShrink()) t->position_ += plCoreT->velocity_;

    // アニメーション更新
    BaseEffectBehavior::update(obj);
}


// objの周囲にエフェクトを連鎖的に発生させる関数
bool ChainEffect(OBJ2D* obj)
{
    // 連鎖的にエフェクトを流すためのデータ
    ChainEffectData chainEffectData[] =
    {
        {  0, &efcBombBehavior, {    0.0f,    0.0f } },
        { 20, &efcBombBehavior, { -100.0f, -100.0f } },
        { 40, &efcBombBehavior, {  100.0f, -100.0f } },
        { 60, &efcBombBehavior, { -100.0f,  100.0f } },
        { 80, &efcBombBehavior, {  100.0f,  100.0f } },
                                                    
        { 0, nullptr, { 0.0f,0.0f } },
    };

    static int timer = 0;
    static ChainEffectData* data = nullptr;
    if (!data) data = chainEffectData;


    while (data->behavior_ && data->time_ == timer)
    {
        AddObj::addEffect(obj, data->behavior_, data->add_);
        ++data;
    }
    ++timer;

    // behaviorがnullptrなら
    if (!data->behavior_)
    {
        timer = 0;
        data = nullptr;
        return true;
    }
    return false;
}
