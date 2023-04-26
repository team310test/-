#include "all.h"

void ActorBehavior::move(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = nullptr;
    switch (obj->state_)
    {
    case 0:
        //////// 初期設定 ////////
        // アニメの初期設定
        obj->renderer_->animeData_ = getParam()->ANIME_WAIT;
        obj->transform_->scale_ = getParam()->SCALE;
        obj->renderer_->drawScale_ = getParam()->SCALE;
        obj->collider_->size_ = {
            getParam()->SIZE.x * getParam()->SCALE.x, 
            getParam()->SIZE.y * getParam()->SCALE.y
        };
        obj->actorComponent_->hp_ = getParam()->HP;
        obj->actorComponent_->nextHp_ = getParam()->NEXT_HP;

        obj->nextBehavior_ = getParam()->NEXT_BEHAVIOR;
        obj->nextEraser_   = getParam()->NEXT_ERASER;

        // アニメ用パラメータ
        obj->actorComponent_->objAnimeAlways_ = getParam()->OBJ_ANIME;
        obj->actorComponent_->rotSpeed_ = getParam()->ROT_SPEED;

        init(obj);

        obj->state_++;
        break;

    case 1:
        //////// 通常時 ////////

        // 現在のbehavior・eraserがparamと違う場合、paramの方を代入
        if (obj->nextBehavior_ != getParam()->NEXT_BEHAVIOR) obj->nextBehavior_ = getParam()->NEXT_BEHAVIOR;
        if (obj->nextEraser_ != getParam()->NEXT_ERASER) obj->nextEraser_ = getParam()->NEXT_ERASER;

        damageProc(obj);

        startAllShrink(obj); //縮小開始
        shrink(obj);    // 画像縮小

        // PGによるアニメーション(objAnimeTemporary_を優先的に行う)
        if (obj->actorComponent_->objAnimeTemporary_)
        {
            if (obj->actorComponent_->objAnimeTemporary_(obj))
                obj->actorComponent_->objAnimeTemporary_ = nullptr; // アニメが終わるとobjAnimeTemporaryをnullptrにする
        }
        else if (obj->actorComponent_->objAnimeAlways_) obj->actorComponent_->objAnimeAlways_(obj);

        // updateがあるならupdateを使用する(仮)
        if (obj->update_)
        {
            obj->update_(obj);
        }

        areaCheck(obj);


        if (obj->transform_->scale_.x >= 0) attack(obj); // scaleが0より大きければ攻撃処理を行う


        break;
    }

    for (int i = 0; i < Collider::boxMax; ++i)
        obj->collider_->calcHitBox(getParam()->HIT_BOX[i], i);

    for (int i = 0; i < Collider::boxMax; ++i)
        obj->collider_->calcAttackBox(getParam()->ATTACK_BOX[i], i);

    // アニメーション更新
    obj->renderer_->animeData_ = getParam()->ANIME_WAIT;

    if (obj->renderer_->animeData_) 
        obj->renderer_->animeUpdate();
}


static const float divideValue = 0.5f;     // scaleを割る値(最終的なscaleの大きさに影響)
// すべてのobjのShrinkを開始させる関数
void Behavior::startAllShrink(OBJ2D* obj) const
{
    if (!Collider::isAllShrink_)        return; // Shrinkが開始されていなければreturn
    if (obj->collider_->isShrink_)      return; // objがすでにshrink中ならreturn
    if (obj->transform_->scale_.x <= 0) return; // scaleが0以下ならreturn

    VECTOR2* currentScale = &obj->transform_->scale_;       // 現在のscale
    VECTOR2* targetScale = &obj->collider_->targetScale_;  // 最終的に目指すscale 
    *targetScale = (*currentScale) * divideValue;           // 現在のscaleの?分の?を最終目標に設定

    obj->collider_->isShrink_ = true; // objのshrinkを開始
}

static const float shrinkVelocity = -0.0025f; // 縮小する速度(縮小の速さに影響)
// 縮小関数
void Behavior::shrink(OBJ2D* obj) const
{
    bool* isShrink = &obj->collider_->isShrink_; // 縮小しているかどうか

    // オリジナル自機でscaleが0.5f以下ならshrinkを強制終了
    if (obj->behavior_ == &corePlayerBehavior &&
        obj->transform_->scale_.x <= 0.5f)
    {
        *isShrink = false;
        return; 
    }

    if (*isShrink == false) return; // Shrinkしていなければreturn


    VECTOR2* currentScale = &obj->transform_->scale_;      // 現在のscale
    VECTOR2* targetScale  = &obj->collider_->targetScale_; // 最終的に目指すscale 

    // Shrink中の場合
    if (currentScale->x > targetScale->x) // 最終目標より現在のscaleが大きければ
    {
        *currentScale += {                // 縮小
            shrinkVelocity * obj->transform_->scale_.x, 
            shrinkVelocity * obj->transform_->scale_.y
        };  
        if (currentScale->x < targetScale->x)  *currentScale = *targetScale; // 最終目標より小さくなったら値を修正
    }

    // scaleAnimeが設定されていなら描画用と判定用のscaleのサイズを合わせる
    if (obj->actorComponent_->objAnimeAlways_ != &scaleAnime)
        obj->renderer_->drawScale_ = obj->transform_->scale_;

    // 目標を達成した場合
    if (currentScale->x == targetScale->x)
    {
        *isShrink = false;           // Shrink終了

        //obj->actorComponent_->padTrg_ = GameLib::input::TRG(0);
        //obj->actorComponent_->padState_ = GameLib::input::STATE(0);
    }

}

// shrinkしているobjがいるか調べる関数（shrinkしているobjがいたらtrue, いなければfalse）
bool Behavior::isObjShrink()
{
    for (auto& list : *Game::instance()->obj2dManager()->getList())
    {
        if (!list->behavior_) continue;              // objが存在していなければcontinue
        if (list->collider_->isShrink_) return true; // shrinkが終わっていないobjがあればtrue
    }

    return false; // すべてshrinkが終わっていればfalse
}