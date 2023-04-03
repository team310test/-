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
        obj->renderer_->animeData_ = getParam()->ANIME_RIGHT;
        obj->transform_->scale_ = getParam()->SCALE;
        obj->collider_->size_ = {
            getParam()->SIZE.x * getParam()->SCALE.x, 
            getParam()->SIZE.y * getParam()->SCALE.y
        };
        obj->actorComponent_->hp_ = getParam()->HP;

        init(obj);

        obj->state_++;
        break;

    case 1:
        //////// 通常時 ////////

        damageProc(obj);
        shrink(obj);    // 画像縮小

        moveY(obj);
        moveX(obj);
        areaCheck(obj);
        attack(obj);
        break;
    }

    obj->collider_->calcHitBox(getParam()->HIT_BOX);
    obj->collider_->calcAttackBox(getParam()->ATTACK_BOX);

    // アニメーション更新
    obj->renderer_->animeData_ = getParam()->ANIME_LEFT;

    if (obj->renderer_->animeData_) 
        obj->renderer_->animeUpdate();
}

// 縮小中かの判定
bool ShrinkJudge(OBJ2D* obj,VECTOR2 targetScale)
{
    //if (obj->collider_->targetScale_.x == 0 ||
    //    obj->collider_->targetScale_.y == 0)
    //    return false;

    //if (obj->transform_->scale_.x > targetScale.x)
    //    return true;
    //if (obj->transform_->scale_.x > targetScale.y)
    //    return true;

    return false;
}

// 縮小関数
static const float divideValue = 0.9f;                 // scaleを割る値
static const VECTOR2 shrinkValue = { -0.01f, -0.01f }; // 縮小する値

void Behavior::shrink(OBJ2D* obj) const
{
    if (obj->behavior_ != &normalPlayerBehavior &&
        obj->behavior_ != &itemPlayerBehavior) return;
    static VECTOR2 endScale{}; // 最終的なscaleの大きさ

    VECTOR2* currentScale = &obj->transform_->scale_;   // 現在のscale
    bool* isShrink        = &obj->collider_->isShrink_; // 縮小しているか判定


    if ((GameLib::input::TRG(0) & GameLib::input::PAD_TRG1) && // Zで縮小
        *isShrink == false)                                    // Shrinkしていなければ
    {
        endScale  = *currentScale * divideValue; // 現在のscaleの?分の?を最終目標に設定
        *isShrink = true;                        // Shrink開始
    }

    if (*isShrink == false) return; // Shrinkしていなければreturn
    
    //const VECTOR2 corePos = Game::instance()->getPlayer() ? 
    //                        Game::instance()->getPlayer()->transform_->position_ :
    //                        VECTOR2(0,0); // 本体の位置    
    VECTOR2* pos = &obj->transform_->position_;          // objの位置
    const VECTOR2 corePos = obj->actorComponent_->parent_ ?
                            obj->actorComponent_->parent_->transform_->position_:
        *pos;

    const VECTOR2 d  = { *pos - corePos };               // 本体の位置からobjの位置を引くことでobjから本体へ向かうベクトルができる
    const float dist = sqrtf(d.x * d.x * + d.y * d.y);    // 平方根を計算
    const VECTOR2 velocity = { d.x / dist * 0.1f, d.y / dist * 0.1f }; // 速度が完成

    *pos += velocity;

    // Shrink中の場合
    if (currentScale->x > endScale.x) // 最終目標より現在のscaleが大きければ
    {
        *currentScale += shrinkValue; // 縮小

        if (currentScale->x <= endScale.x) // 最終目標と同じか、それより小さくなったら
        {
            *currentScale = endScale; // 値を修正
            *isShrink     = false;     // Shrink終了
        }
    }
    

    //// [Z]で縮小
    //if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG1)
    //{ 
    //    obj->collider_->targetScale_.x = obj->transform_->scale_.x * 0.9f;
    //    obj->collider_->targetScale_.y = obj->transform_->scale_.y * 0.9f;
    //    obj->collider_->isShrink_ = true;
    //    obj->actorComponent_->padTrg_ = 0;
    //    obj->actorComponent_->padState_ = 0;
    //}
    //
    //if(ShrinkJudge(obj, obj->collider_->targetScale_))
    //{
    //    obj->transform_->scale_.x -= 0.01f * obj->transform_->scale_.x;
    //    obj->transform_->scale_.y -= 0.01f * obj->transform_->scale_.y;
    //}
    //else
    //{
    //    obj->collider_->isShrink_ = false;
    //    obj->actorComponent_->padTrg_ = GameLib::input::TRG(0);
    //    obj->actorComponent_->padState_ = GameLib::input::STATE(0);
    //}
}
