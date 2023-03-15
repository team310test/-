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
        moveY(obj);
        moveX(obj);
        areaCheck(obj);
        attack(obj);
        break;
    }

    obj->collider_->calcHitBox(getParam()->HIT_BOX);
    obj->collider_->calcAttackBox(getParam()->ATTACK_BOX);

    // アニメーション更新
    if (obj->renderer_->animeData_) obj->renderer_->animeUpdate();
}
