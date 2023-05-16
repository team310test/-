#include "all.h"

// OBJ2D
bool objToul::FadeOut(OBJ2D* obj, const float& fadeOutSpeed)
{
    // color_.wを直接参照
    float& colorW = obj->renderer_->color_.w;

    // colorW + fadeOutSpeedが0.0fより大きければ代入、小さければ0.0fを代入
    colorW = std::max(0.0f, colorW + fadeOutSpeed);


    // 透明(0.0f)になったらtrue
    if (colorW == 0.0f) return true;

    // そうでなければfalse
    return false;
}

bool objToul::FadeIn(OBJ2D* obj, const float& fadeInSpeed)
{
    // color_.wを直接参照
    float& colorW = obj->renderer_->color_.w;

    // colorW + fadeOutSpeedが1.0f未満なら代入、それ以上なら0.0fを代入
    colorW = std::min(1.0f, colorW + fadeInSpeed);


    // 不透明(1.0f)になったらtrue
    if (colorW == 1.0f) return true;

    // そうでなければfalse
    return false;
}

//bool objToul::Shrink(OBJ2D* obj, const VECTOR2& target, const float& fadeSpeed)
//{
//    // 既にターゲットより小さい場合、今のサイズのまま返す
//    if (obj->renderer_->drawScale_.x < target.x)
//        target.x = obj->renderer_->drawScale_.x;
//    if (obj->renderer_->drawScale_.y < target.y)
//        target.y = obj->renderer_->drawScale_.y;
//
//    // Y軸
//    if (obj->renderer_->drawScale_.y >= target.y)
//    {
//        obj->renderer_->drawScale_.y -= fadeSpeed;
//        // 超過修正
//        if (obj->renderer_->drawScale_.y < target.y)
//            obj->renderer_->drawScale_.y = target.y;
//    }
//
//    // X軸
//    if (obj->renderer_->drawScale_.x >= target.x)
//    {
//        obj->renderer_->drawScale_.x -= fadeSpeed;
//        // 超過修正
//        if (obj->renderer_->drawScale_.x < target.y)
//            obj->renderer_->drawScale_.x = target.y;
//    }
//
//    // 両方ともscaleが1.0fになったらtrueえお返す
//    if (
//        (obj->renderer_->drawScale_.y == target.y)
//        && (obj->renderer_->drawScale_.x == target.y)
//        )
//    {
//        return true;
//    }
//
//    return false;
//}


// 拡大
bool objToul::Enlarge(OBJ2D* obj, const VECTOR2& targetScale, const float& enlargeSpeed)
{
    // drawScale_を直接参照
    VECTOR2& drawScale = obj->renderer_->drawScale_;

    // 目標スケール未満ならdrawScale.x(y) + enlargeSpeedを代入
    // それ以上ならtargetScale.x(y)を代入
    drawScale.x = std::min(targetScale.x, drawScale.x + enlargeSpeed);
    drawScale.y = std::min(targetScale.y, drawScale.y + enlargeSpeed);

    // 目標に達したらtrue
    if (drawScale == targetScale) return true;

    // 目標に達していなければfalse
    return false;
}

bool objToul::ContactPos(OBJ2D* obj, const VECTOR2& targetPos, const float& contactSpeed)
{
    Transform* t = obj->transform_;

    // 目標と位置が同じならtrueを返す
    if (t->position_ == targetPos) return true;

    const VECTOR2 d  = { targetPos - t->position_ };        // objから目標へ向かうベクトル
    const float dist = sqrtf((d.x * d.x) + (d.y * d.y));    // objから目標までの距離

    // 速度計算
    t->velocity_ = {
        (d.x / dist) * contactSpeed,
        (d.y / dist) * contactSpeed,
    };
    // 位置に速度を加算
    t->position_ += t->velocity_;

    // 目標の位置範囲内に収まったらtrueを返す
    if (t->position_.x >= targetPos.x - 10.0f && 
        t->position_.x <= targetPos.x + 10.0f &&          
        t->position_.y >= targetPos.y - 10.0f && 
        t->position_.y <= targetPos.y + 10.0f)
    {
        t->position_ = targetPos;
        t->velocity_ = {};
        return true;
    }

    return false;
}

// OBJ2DManager
bool objToul::isObjType(OBJ2DManager* obj2dManager, const OBJ_TYPE& objType)
{
    for (auto& obj : *obj2dManager->getList())
    {
        if (obj->behavior_->getType() == objType) return true;
    }
    return false;
}

// <その他>

// 指定したフレームが経過するとtrueを返す
bool wait(const int& waitTime)
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