#include "all.h"

// OBJ2D
bool objToul::FadeOut(OBJ2D* obj, float fadeSpeed)
{
    // 透明度0未満の場合
    if (obj->renderer_->color_.w < 0.0f)
    {
        obj->renderer_->color_.w = 0.0f;
        return true;
    }

    // 透明度0.0を超えているなら減少
    if (obj->renderer_->color_.w >= 0)
    {
        obj->renderer_->color_.w -= fadeSpeed;
        // 超過修正
        if (obj->renderer_->color_.w < 0)
            obj->renderer_->color_.w = 0.0f;
    }

    // 全て透明になったらtreuを返す
    if (obj->renderer_->color_.w == 0)
    {
        return true;
    }

    return false;
}

bool objToul::FadeIn(OBJ2D* obj, float fadeSpeed)
{
    // 透明度が1.0を超える場合
    if (obj->renderer_->color_.w > 1.0f)
    {
        obj->renderer_->color_.w = 1.0f;
        return true;
    }

    // 透明度1.0未満なら増加
    if (obj->renderer_->color_.w <= 1.0f)
    {
        obj->renderer_->color_.w += fadeSpeed;
        // 超過修正
        if (obj->renderer_->color_.w > 1.0f)
            obj->renderer_->color_.w = 1.0f;
    }

    // 透明度1.0になったらtrueを返す
    if (obj->renderer_->color_.w == 1.0f)
    {
        return true;
    }

    return false;
}

bool objToul::Shrink(OBJ2D* obj, VECTOR2 target, float fadeSpeed)
{
    // 既にターゲットより小さい場合、今のサイズのまま返す
    if (obj->renderer_->drawScale_.x < target.x)
        target.x = obj->renderer_->drawScale_.x;
    if (obj->renderer_->drawScale_.y < target.y)
        target.y = obj->renderer_->drawScale_.y;

    // Y軸
    if (obj->renderer_->drawScale_.y >= target.y)
    {
        obj->renderer_->drawScale_.y -= fadeSpeed;
        // 超過修正
        if (obj->renderer_->drawScale_.y < target.y)
            obj->renderer_->drawScale_.y = target.y;
    }

    // X軸
    if (obj->renderer_->drawScale_.x >= target.x)
    {
        obj->renderer_->drawScale_.x -= fadeSpeed;
        // 超過修正
        if (obj->renderer_->drawScale_.x < target.y)
            obj->renderer_->drawScale_.x = target.y;
    }

    // 両方ともscaleが1.0fになったらtrueえお返す
    if (
        (obj->renderer_->drawScale_.y == target.y)
        && (obj->renderer_->drawScale_.x == target.y)
        )
    {
        return true;
    }

    return false;
}

bool objToul::Enlarge(OBJ2D* obj, VECTOR2 target, float fadeSpeed)
{
    // 既にターゲットより小さい場合、今のサイズのまま返す
    if (obj->renderer_->drawScale_.x > target.x)
        target.x = obj->renderer_->drawScale_.x;
    if (obj->renderer_->drawScale_.y > target.y)
        target.y = obj->renderer_->drawScale_.y;

    // Y軸
    if (obj->renderer_->drawScale_.y <= target.y)
    {
        obj->renderer_->drawScale_.y += fadeSpeed;
        // 超過修正
        if (obj->renderer_->drawScale_.y > target.y)
            obj->renderer_->drawScale_.y = target.y;
    }

    // X軸
    if (obj->renderer_->drawScale_.x <= target.x)
    {
        obj->renderer_->drawScale_.x += fadeSpeed;
        // 超過修正
        if (obj->renderer_->drawScale_.x > target.y)
            obj->renderer_->drawScale_.x = target.y;
    }

    // 両方ともscaleが1.0fになったらtrueえお返す
    if (
        (obj->renderer_->drawScale_.y == target.y)
        && (obj->renderer_->drawScale_.x == target.y)
        )
    {
        return true;
    }

    return false;
}

bool objToul::ContactPos(OBJ2D* obj, VECTOR2 target, float Velocity)
{
    const VECTOR2 objPos = obj->transform_->position_;      // objの位置

    if (objPos == target) return true;

    const VECTOR2 d = { target - objPos };                  // objから自機本体へ向かうベクトル
    const float dist = sqrtf((d.x * d.x) + (d.y * d.y));    // objから自機本体までの距離

    float addVelocity = 0.0f;                               // objのvelocityに足す速度
    float num = 0.0f;                                       // for分のiみたいな役割
    const float copyDist = dist >= 0 ? dist : dist * (-1);

    while (true)
    {
        if (num > 999) // 念のために終点を設置
        {
            addVelocity = Velocity * num;
            break;
        }

        // objから自機本体までの距離が遠くなるたび速度を上昇させる
        // (距離が遠すぎるとobjが自機本体に追いつけないため)
        if ((copyDist >= (50.0f * num) && copyDist <= 50.0f * (num + 1.0f)))  // ±0から±50、±50から±100、±100から±150...
        {
            addVelocity = (num != 0.0f) ? (Velocity * num) : Velocity; // ±0から±50までの距離はnumが0なのでデフォルトの値を代入

            break; // 代入したのでbreak;
        }

        ++num; // numを加算していく
    }

    obj->transform_->velocity_ = {
        (d.x / dist) * (addVelocity),
        (d.y / dist) * (addVelocity),
    };

    obj->transform_->position_ += obj->transform_->velocity_;

    VECTOR2& pos = obj->transform_->position_;
    if (
        ((pos.x <= target.x + 3.0f) && (pos.x >= target.x - 3.0f))
        && ((pos.y <= target.y + 3.0f) && (pos.y >= target.y - 3.0f))
        )
    {
        obj->transform_->position_ = target;
        obj->transform_->velocity_ = { 0.0f,0.0f };
        return true;
    }

    return false;
}

// OBJ2DManager
bool objToul::isObjType(OBJ2DManager* obj2dManager, OBJ_TYPE objType)
{
    {
        for (auto& obj : *obj2dManager->getList())
        {
            if (obj->behavior_->getType() == objType)
                return true;
        }
        return false;
    }
}

// <その他>

// 指定したフレームが経過するとtrueを返す
bool wait(int waitTime)
{
    static int timer = 0;
    ++timer;
    if (timer == waitTime)
    {
        timer = 0;
        return true;
    }
    return false;
}