#include "all.h"

void BaseWeaponBehavior::move(OBJ2D* obj) const
{
    switch (obj->state_)
    {
    case 0:
        //////// 初期設定 ////////
        obj->renderer_->data_ = getParam()->SPR_WEAPON;

        //obj->transform_->scale_ = getParam()->SCALE;
        obj->transform_->scale_ = obj->weaponComponent_->parent_->transform_->scale_;

        obj->eraser_ = getParam()->ERASER;
        obj->collider_->judgeFlag_ = true;      // あたり判定を行う
        obj->collider_->isDrawAttackRect_ = true;  // あたり判定の領域を描画する（デバッグ用）

        // 左右の向き、速度を設定（プレイヤーにもxFlip_の設定が必要）
        obj->weaponComponent_->xFlip_ = obj->weaponComponent_->parent_->renderer_->drawXFlip_;    // 武器の持ち主のxFlip_を武器に設定する
        obj->transform_->velocity_.x = obj->weaponComponent_->xFlip_ ? -getParam()->SPEED_X : getParam()->SPEED_X;
        obj->transform_->velocity_.y = 0.0f;    // 念のため

        obj->state_++;
        /*fallthrough*/

    case 1:
        //////// 通常時 ////////
        update(obj);    // 武器の位置更新
        calcAttackBox(obj);
        break;
    }
}

NormalShotBehavior::NormalShotBehavior()
{
    param_.SPR_WEAPON = &sprWeapon_Shuriken;
    param_.ERASER = &normalShotEraser;
    param_.SPEED_X = 20.0f;
    param_.ATTACK_POWER = 1;
    param_.SCALE = { 0.5f, 0.5f };
    param_.ATTACK_BOX = { -24, -24, 24, 24 };
}

void NormalShotBehavior::update(OBJ2D* obj) const
{
    // 位置に速度を足す
    obj->transform_->position_ += obj->transform_->velocity_;
}

void NormalShotBehavior::calcAttackBox(OBJ2D* obj) const
{
    // 攻撃判定の計算
    obj->collider_->calcAttackBox(getParam()->ATTACK_BOX,1);
}

void NormalShotBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    dst->actorComponent_->hp_ = std::max(dst->actorComponent_->hp_ - getParam()->ATTACK_POWER, 0);

    src->remove();
}

void NormalShotEraser::erase(OBJ2D* obj) const
{
    const VECTOR2* size = &obj->collider_->size_;
    const VECTOR2* pos = &obj->transform_->position_;

    const float leftLimit = size->x;
    const float rightLimit = BG::WINDOW_W + size->x;
    const float topLimit = size->y;
    const float bottomLimit = BG::WINDOW_H + size->y;

    if (pos->x < leftLimit ||
        pos->x > rightLimit ||
        pos->y < topLimit ||
        pos->y > bottomLimit)
    {
        obj->remove();
    }
}