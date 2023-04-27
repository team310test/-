#include "all.h"

void ActorBehavior::move(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = nullptr;
    switch (obj->state_)
    {
    case 0:
        //////// 初期設定 ////////
        // アニメの初期設定
        obj->renderer_->animeData_  = getParam()->ANIME_WAIT;
        obj->transform_->scale_     = getParam()->SCALE;
        obj->renderer_->drawScale_  = getParam()->SCALE;
        obj->collider_->size_ = {
            getParam()->SIZE.x * getParam()->SCALE.x, 
            getParam()->SIZE.y * getParam()->SCALE.y
        };
        obj->actorComponent_->hp_     = getParam()->HP;
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
        if (obj->nextEraser_   != getParam()->NEXT_ERASER)   obj->nextEraser_   = getParam()->NEXT_ERASER;


        startAllShrink(obj);    // 縮小開始
        shrink(obj);            // 画像縮小


        if (obj->collider_->isShrink_) break; // 縮小中なら飛ばす
        // objがプレイヤーの場合
        if (obj == Game::instance()->player_) { if (Behavior::isObjShrink()) break; }// すべてのobjが縮小終了していなければ飛ばす


        // PGによるアニメーション(objAnimeTemporary_を優先的に行う)
        if (obj->actorComponent_->objAnimeTemporary_)
        {
            if (obj->actorComponent_->objAnimeTemporary_(obj))
                obj->actorComponent_->objAnimeTemporary_ = nullptr; // アニメが終わるとobjAnimeTemporaryをnullptrにする
        }
        else if (obj->actorComponent_->objAnimeAlways_) obj->actorComponent_->objAnimeAlways_(obj);

        damageProc(obj);

        // updateがあるならupdateを使用する
        if (obj->update_) obj->update_(obj);

        areaCheck(obj);

        obj->transform_->position_ += obj->transform_->velocity_;   // 速度を位置に加算

        if (obj->transform_->scale_.x > UPDATE_OBJ_SCALE_MIN_LIMIT)
        {
            attack(obj); // スケールがスケール更新最低値より大きければ攻撃処理を行う
        }

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


// すべてのobjのShrinkを開始させる関数
void Behavior::startAllShrink(OBJ2D* obj) const
{
    if (!Collider::isAllShrink_)        return; // Shrinkが開始されていなければreturn
    if (obj->collider_->isShrink_)      return; // objがすでにshrink中ならreturn
    if (obj->transform_->scale_.x <= 0) return; // scaleが0以下ならreturn

    VECTOR2* currentScale = &obj->transform_->scale_;       // 現在のscale
    VECTOR2* targetScale  = &obj->collider_->targetScale_;  // 最終的に目指すscale 
    *targetScale = (*currentScale) * SHRINK_DIVIDE_VALUE;           // 現在のscaleの?分の?を最終目標に設定

    obj->collider_->judgeFlag_ = false;
    obj->collider_->isShrink_ = true; // objのshrinkを開始
}

// 縮小関数
float Behavior::shrinkVelocity_ = SHRINK_SPEED; // 縮小する速度
void Behavior::shrink(OBJ2D* obj) const
{
    Transform* t = obj->transform_;
    Collider*  c = obj->collider_;

    // オリジナル自機でscaleが0.5f以下ならshrinkを強制終了
    if (obj->behavior_ == &playerCoreBehavior && t->scale_.x <= 0.5f)
    {
        c->isShrink_ = false;
        return; 
    }

    if (c->isShrink_ == false) return; // Shrinkしていなければreturn



    // Shrink中の場合
    if (t->scale_.x > c->targetScale_.x) // 現在のscaleが最終目標より大きければ
    {
        t->scale_ += {                // 縮小
            shrinkVelocity_ * t->scale_.x, 
            shrinkVelocity_ * t->scale_.y
        };  
        if (t->scale_.x < c->targetScale_.x)  t->scale_ = c->targetScale_; // 最終目標より小さくなったら値を修正
    }

    // scaleAnimeが設定されていなければ描画用と判定用のscaleのサイズを合わせる
/*    if (obj->actorComponent_)
    {
        if (obj->actorComponent_->objAnimeAlways_ != &scaleAnime)
            obj->renderer_->drawScale_ = t->scale_;
    }
    else */obj->renderer_->drawScale_ = t->scale_;


    // 目標を達成した場合
    if (t->scale_.x == c->targetScale_.x)
    {
        obj->collider_->judgeFlag_ = true;
        c->isShrink_ = false;   // Shrink終了
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