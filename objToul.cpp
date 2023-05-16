#include "all.h"

// OBJ2D
bool objToul::FadeOut(OBJ2D* obj, const float& fadeOutSpeed)
{
    // color_.w�𒼐ڎQ��
    float& colorW = obj->renderer_->color_.w;

    // colorW + fadeOutSpeed��0.0f���傫����Α���A���������0.0f����
    colorW = std::max(0.0f, colorW + fadeOutSpeed);


    // ����(0.0f)�ɂȂ�����true
    if (colorW == 0.0f) return true;

    // �����łȂ����false
    return false;
}

bool objToul::FadeIn(OBJ2D* obj, const float& fadeInSpeed)
{
    // color_.w�𒼐ڎQ��
    float& colorW = obj->renderer_->color_.w;

    // colorW + fadeOutSpeed��1.0f�����Ȃ����A����ȏ�Ȃ�0.0f����
    colorW = std::min(1.0f, colorW + fadeInSpeed);


    // �s����(1.0f)�ɂȂ�����true
    if (colorW == 1.0f) return true;

    // �����łȂ����false
    return false;
}

//bool objToul::Shrink(OBJ2D* obj, const VECTOR2& target, const float& fadeSpeed)
//{
//    // ���Ƀ^�[�Q�b�g��菬�����ꍇ�A���̃T�C�Y�̂܂ܕԂ�
//    if (obj->renderer_->drawScale_.x < target.x)
//        target.x = obj->renderer_->drawScale_.x;
//    if (obj->renderer_->drawScale_.y < target.y)
//        target.y = obj->renderer_->drawScale_.y;
//
//    // Y��
//    if (obj->renderer_->drawScale_.y >= target.y)
//    {
//        obj->renderer_->drawScale_.y -= fadeSpeed;
//        // ���ߏC��
//        if (obj->renderer_->drawScale_.y < target.y)
//            obj->renderer_->drawScale_.y = target.y;
//    }
//
//    // X��
//    if (obj->renderer_->drawScale_.x >= target.x)
//    {
//        obj->renderer_->drawScale_.x -= fadeSpeed;
//        // ���ߏC��
//        if (obj->renderer_->drawScale_.x < target.y)
//            obj->renderer_->drawScale_.x = target.y;
//    }
//
//    // �����Ƃ�scale��1.0f�ɂȂ�����true�����Ԃ�
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


// �g��
bool objToul::Enlarge(OBJ2D* obj, const VECTOR2& targetScale, const float& enlargeSpeed)
{
    // drawScale_�𒼐ڎQ��
    VECTOR2& drawScale = obj->renderer_->drawScale_;

    // �ڕW�X�P�[�������Ȃ�drawScale.x(y) + enlargeSpeed����
    // ����ȏ�Ȃ�targetScale.x(y)����
    drawScale.x = std::min(targetScale.x, drawScale.x + enlargeSpeed);
    drawScale.y = std::min(targetScale.y, drawScale.y + enlargeSpeed);

    // �ڕW�ɒB������true
    if (drawScale == targetScale) return true;

    // �ڕW�ɒB���Ă��Ȃ����false
    return false;
}

bool objToul::ContactPos(OBJ2D* obj, const VECTOR2& targetPos, const float& contactSpeed)
{
    Transform* t = obj->transform_;

    // �ڕW�ƈʒu�������Ȃ�true��Ԃ�
    if (t->position_ == targetPos) return true;

    const VECTOR2 d  = { targetPos - t->position_ };        // obj����ڕW�֌������x�N�g��
    const float dist = sqrtf((d.x * d.x) + (d.y * d.y));    // obj����ڕW�܂ł̋���

    // ���x�v�Z
    t->velocity_ = {
        (d.x / dist) * contactSpeed,
        (d.y / dist) * contactSpeed,
    };
    // �ʒu�ɑ��x�����Z
    t->position_ += t->velocity_;

    // �ڕW�̈ʒu�͈͓��Ɏ��܂�����true��Ԃ�
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

// <���̑�>

// �w�肵���t���[�����o�߂����true��Ԃ�
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