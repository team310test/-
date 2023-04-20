#include "all.h"

void ActorBehavior::moveY(OBJ2D* obj) const
{
    // 最大速度チェックを行う
    obj->transform_->velocity_.y = clamp(obj->transform_->velocity_.y, -getParam()->SPEED_Y_MAX, getParam()->SPEED_Y_MAX);

    // 位置更新
    float oldY = obj->transform_->position_.y;           // 移動前の位置を保持
    obj->transform_->position_.y += obj->transform_->velocity_.y;
    float deltaY = obj->transform_->position_.y - oldY;  // 移動後の位置から移動前の位置を引く
}

void ActorBehavior::moveX(OBJ2D* obj) const
{
    // 最大速度チェック
    if (obj->transform_->velocity_.x > getParam()->SPEED_X_MAX) obj->transform_->velocity_.x = getParam()->SPEED_X_MAX;
    if (obj->transform_->velocity_.x < -getParam()->SPEED_X_MAX) obj->transform_->velocity_.x = -getParam()->SPEED_X_MAX;

    // X方向移動
    float oldX = obj->transform_->position_.x;
    obj->transform_->position_.x += obj->transform_->velocity_.x;
    float deltaX = obj->transform_->position_.x - oldX;
}

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
        obj->renderer_->scale_ = getParam()->SCALE;
        obj->collider_->size_ = {
            getParam()->SIZE.x * getParam()->SCALE.x, 
            getParam()->SIZE.y * getParam()->SCALE.y
        };
        obj->actorComponent_->hp_ = getParam()->HP;

        obj->actorComponent_->nextBehavior_ = getParam()->NEXT_BEHAVIOR;
        obj->actorComponent_->nextEraser_ = getParam()->NEXT_ERASER;

        // アニメ用パラメータ
        obj->actorComponent_->objAnime_ = getParam()->obj_ANIME;
        obj->actorComponent_->rotSpeed_ = getParam()->ROT_SPEED;


        init(obj);

        obj->state_++;
        break;

    case 1:
        //////// 通常時 ////////

        damageProc(obj);

        startAllShrink(obj); //縮小開始
        shrink(obj);    // 画像縮小

        // アニメーション
        if(obj->actorComponent_->objAnime_) obj->actorComponent_->objAnime_(obj);

        moveY(obj);
        moveX(obj);
        areaCheck(obj);
        attack(obj);
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

//// <回転アニメーション>
//void ActorBehavior::rotateAnime(OBJ2D* obj) const
//{
//    if (getParam()->ROT_SPEED == 0.0f) return;  // 回転速度が0なら return
//
//    obj->transform_->rotation_ += getParam()->ROT_SPEED;
//}
//
//// <X軸のスケール変動アニメーション>
//void ActorBehavior::XscaleAnime(OBJ2D* obj) const
//{
//    // 画面の縮小中なら return
//    if (obj->collider_->isShrink_) return;
//
//    VECTOR2 orgScale = obj->transform_->scale_;
//    float shrinkScale = orgScale.x * 0.05;
//    static bool isShrink;
//}


static const float divideValue = 0.5f;     // scaleを割る値(最終的なscaleの大きさに影響)

// すべてのobjのShrinkを開始させる関数
void Behavior::startAllShrink(OBJ2D* obj) const
{
    if (!Collider::isAllShrink_)   return; // Shrinkが開始されていなければreturn
    if (obj->collider_->isShrink_) return; // objがすでにshrink中ならreturn;

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
    if (obj->behavior_ == &normalPlayerBehavior &&
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
            shrinkVelocity * obj->transform_->scale_.y,
        };  
        if (currentScale->x < targetScale->x)  *currentScale = *targetScale; // 最終目標より小さくなったら値を修正
    }
    
    // 描画用と判定用のscaleのサイズを合わせる
    obj->renderer_->scale_ = obj->transform_->scale_;


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