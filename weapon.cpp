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
        obj->weaponComponent_->xFlip_ = obj->weaponComponent_->parent_->actorComponent_->xFlip_;    // 武器の持ち主のxFlip_を武器に設定する
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

ShurikenBehavior::ShurikenBehavior()
{
    param_.SPR_WEAPON = &sprWeapon_Shuriken;
    param_.ERASER = &shurikenEraser;
    param_.SPEED_X = 20.0f;
    param_.ROT_SPEED = ToRadian(24);
    param_.ATTACK_POWER = 1;
    param_.SCALE = { 0.5f, 0.5f };
    param_.ATTACK_BOX = { -24, -24, 24, 24 };
}

void ShurikenBehavior::update(OBJ2D* obj) const
{
    // 位置に速度を足す
    bool xFlip = false;
    obj->transform_->velocity_ = { xFlip ? -getParam()->SPEED_X : getParam()->SPEED_X, 0 };
    obj->transform_->position_ += obj->transform_->velocity_;

    // 回転を加える
    //obj->transform_->rotation_ += xFlip ? -getParam()->ROT_SPEED : getParam()->ROT_SPEED;
}

void ShurikenBehavior::calcAttackBox(OBJ2D* obj) const
{
    // 攻撃判定の計算
    obj->collider_->calcAttackBox(getParam()->ATTACK_BOX,1);
}

void ShurikenBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    dst->actorComponent_->hp_ = std::max(dst->actorComponent_->hp_ - getParam()->ATTACK_POWER, 0);

    src->remove();
}

void ShurikenEraser::erase(OBJ2D* obj) const
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

SwordBehavior::SwordBehavior()
{
    param_.SPR_WEAPON = &sprWeapon_Sword;
    param_.ERASER = &swordEraser;
    param_.ATTACK_POWER = 2;
    param_.SCALE = { 1,1 };
    param_.ATTACK_BOX = { -32,-32,32,32 };
}

void SwordBehavior::update(OBJ2D* obj) const
{
    OBJ2D* parent = obj->weaponComponent_->parent_;

    // 角度
    bool xFlip = parent->actorComponent_->xFlip_;
    float angle = 0.0f;
    if (xFlip)
    {
        angle = 30.0f + obj->timer_ * -15.0f;
        angle = std::max(angle, -105.0f);
    }
    else
    {
        angle = -30.0f + obj->timer_ * 15.0f;
        angle = std::min(angle, 105.0f);
    }
    obj->transform_->rotation_ = ToRadian(angle);

    // 位置
    VECTOR2 pos = parent->transform_->position_ + VECTOR2(0, -48);
    obj->transform_->position_ = pos;

    obj->timer_++;
}

void SwordBehavior::calcAttackBox(OBJ2D* obj) const
{
    float angle = obj->transform_->rotation_;
    VECTOR2 pos = { sinf(angle) * 96, -cosf(angle) * 96 };
    obj->collider_->calcAttackBox(
        {
            pos.x + getParam()->ATTACK_BOX.left,
            pos.y + getParam()->ATTACK_BOX.top,
            pos.x + getParam()->ATTACK_BOX.right,
            pos.y + getParam()->ATTACK_BOX.bottom
        },1
    );
}

void SwordBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    if (!src || !dst ||
        !dst->actorComponent_) return;

    dst->actorComponent_->hp_ = (std::max)(dst->actorComponent_->hp_ - getParam()->ATTACK_POWER, 0);
    src->collider_->judgeFlag_ = false;
}

void SwordEraser::erase(OBJ2D* obj) const
{
    if (obj->timer_ > 15)
        obj->remove();
}
