#include "all.h"

void ActorBehavior::moveY(OBJ2D* obj) const
{
    // �ő呬�x�`�F�b�N���s��
    obj->transform_->velocity_.y = clamp(obj->transform_->velocity_.y, -getParam()->SPEED_Y_MAX, getParam()->SPEED_Y_MAX);

    // �ʒu�X�V
    float oldY = obj->transform_->position_.y;           // �ړ��O�̈ʒu��ێ�
    obj->transform_->position_.y += obj->transform_->velocity_.y;
    float deltaY = obj->transform_->position_.y - oldY;  // �ړ���̈ʒu����ړ��O�̈ʒu������
}

void ActorBehavior::moveX(OBJ2D* obj) const
{
    // �ő呬�x�`�F�b�N
    if (obj->transform_->velocity_.x > getParam()->SPEED_X_MAX) obj->transform_->velocity_.x = getParam()->SPEED_X_MAX;
    if (obj->transform_->velocity_.x < -getParam()->SPEED_X_MAX) obj->transform_->velocity_.x = -getParam()->SPEED_X_MAX;

    // X�����ړ�
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
        //////// �����ݒ� ////////
        // �A�j���̏����ݒ�
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
        //////// �ʏ펞 ////////
        damageProc(obj);
        moveY(obj);
        moveX(obj);
        areaCheck(obj);
        attack(obj);
        break;
    }

    obj->collider_->calcHitBox(getParam()->HIT_BOX);
    obj->collider_->calcAttackBox(getParam()->ATTACK_BOX);

    // �A�j���[�V�����X�V
    if (obj->renderer_->animeData_) obj->renderer_->animeUpdate();
}
