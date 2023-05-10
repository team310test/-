#include "all.h"

// OBJ2D
bool objToul::FadeOut(OBJ2D* obj, float fadeSpeed)
{
    // �����x0�����̏ꍇ
    if (obj->renderer_->color_.w < 0.0f)
    {
        obj->renderer_->color_.w = 0.0f;
        return true;
    }

    // �����x0.0�𒴂��Ă���Ȃ猸��
    if (obj->renderer_->color_.w >= 0)
    {
        obj->renderer_->color_.w -= fadeSpeed;
        // ���ߏC��
        if (obj->renderer_->color_.w < 0)
            obj->renderer_->color_.w = 0.0f;
    }

    // �S�ē����ɂȂ�����treu��Ԃ�
    if (obj->renderer_->color_.w == 0)
    {
        return true;
    }

    return false;
}

bool objToul::FadeIn(OBJ2D* obj, float fadeSpeed)
{
    // �����x��1.0�𒴂���ꍇ
    if (obj->renderer_->color_.w > 1.0f)
    {
        obj->renderer_->color_.w = 1.0f;
        return true;
    }

    // �����x1.0�����Ȃ瑝��
    if (obj->renderer_->color_.w <= 1.0f)
    {
        obj->renderer_->color_.w += fadeSpeed;
        // ���ߏC��
        if (obj->renderer_->color_.w > 1.0f)
            obj->renderer_->color_.w = 1.0f;
    }

    // �����x1.0�ɂȂ�����true��Ԃ�
    if (obj->renderer_->color_.w == 1.0f)
    {
        return true;
    }

    return false;
}

bool objToul::Shrink(OBJ2D* obj, VECTOR2 target, float fadeSpeed)
{
    // ���Ƀ^�[�Q�b�g��菬�����ꍇ�A���̃T�C�Y�̂܂ܕԂ�
    if (obj->renderer_->drawScale_.x < target.x)
        target.x = obj->renderer_->drawScale_.x;
    if (obj->renderer_->drawScale_.y < target.y)
        target.y = obj->renderer_->drawScale_.y;

    // Y��
    if (obj->renderer_->drawScale_.y >= target.y)
    {
        obj->renderer_->drawScale_.y -= fadeSpeed;
        // ���ߏC��
        if (obj->renderer_->drawScale_.y < target.y)
            obj->renderer_->drawScale_.y = target.y;
    }

    // X��
    if (obj->renderer_->drawScale_.x >= target.x)
    {
        obj->renderer_->drawScale_.x -= fadeSpeed;
        // ���ߏC��
        if (obj->renderer_->drawScale_.x < target.y)
            obj->renderer_->drawScale_.x = target.y;
    }

    // �����Ƃ�scale��1.0f�ɂȂ�����true�����Ԃ�
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
    // ���Ƀ^�[�Q�b�g��菬�����ꍇ�A���̃T�C�Y�̂܂ܕԂ�
    if (obj->renderer_->drawScale_.x > target.x)
        target.x = obj->renderer_->drawScale_.x;
    if (obj->renderer_->drawScale_.y > target.y)
        target.y = obj->renderer_->drawScale_.y;

    // Y��
    if (obj->renderer_->drawScale_.y <= target.y)
    {
        obj->renderer_->drawScale_.y += fadeSpeed;
        // ���ߏC��
        if (obj->renderer_->drawScale_.y > target.y)
            obj->renderer_->drawScale_.y = target.y;
    }

    // X��
    if (obj->renderer_->drawScale_.x <= target.x)
    {
        obj->renderer_->drawScale_.x += fadeSpeed;
        // ���ߏC��
        if (obj->renderer_->drawScale_.x > target.y)
            obj->renderer_->drawScale_.x = target.y;
    }

    // �����Ƃ�scale��1.0f�ɂȂ�����true�����Ԃ�
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
    const VECTOR2 objPos = obj->transform_->position_;      // obj�̈ʒu

    if (objPos == target) return true;

    const VECTOR2 d = { target - objPos };                  // obj���玩�@�{�̂֌������x�N�g��
    const float dist = sqrtf((d.x * d.x) + (d.y * d.y));    // obj���玩�@�{�̂܂ł̋���

    float addVelocity = 0.0f;                               // obj��velocity�ɑ������x
    float num = 0.0f;                                       // for����i�݂����Ȗ���
    const float copyDist = dist >= 0 ? dist : dist * (-1);

    while (true)
    {
        if (num > 999) // �O�̂��߂ɏI�_��ݒu
        {
            addVelocity = Velocity * num;
            break;
        }

        // obj���玩�@�{�̂܂ł̋����������Ȃ邽�ё��x���㏸������
        // (���������������obj�����@�{�̂ɒǂ����Ȃ�����)
        if ((copyDist >= (50.0f * num) && copyDist <= 50.0f * (num + 1.0f)))  // �}0����}50�A�}50����}100�A�}100����}150...
        {
            addVelocity = (num != 0.0f) ? (Velocity * num) : Velocity; // �}0����}50�܂ł̋�����num��0�Ȃ̂Ńf�t�H���g�̒l����

            break; // ��������̂�break;
        }

        ++num; // num�����Z���Ă���
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

// <���̑�>

// �w�肵���t���[�����o�߂����true��Ԃ�
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