#include "all.h"

void BaseWeaponBehavior::move(OBJ2D* obj) const
{
    switch (obj->state_)
    {
    case 0:
        //////// �����ݒ� ////////
        obj->renderer_->data_ = getParam()->SPR_WEAPON;

        //obj->transform_->scale_ = getParam()->SCALE;
        obj->transform_->scale_ = obj->weaponComponent_->parent_->transform_->scale_;

        obj->eraser_ = getParam()->ERASER;
        obj->collider_->judgeFlag_ = true;      // �����蔻����s��
        obj->collider_->isDrawAttackRect_ = true;  // �����蔻��̗̈��`�悷��i�f�o�b�O�p�j

        // ���E�̌����A���x��ݒ�i�v���C���[�ɂ�xFlip_�̐ݒ肪�K�v�j
        obj->weaponComponent_->xFlip_ = obj->weaponComponent_->parent_->renderer_->drawXFlip_;    // ����̎������xFlip_�𕐊�ɐݒ肷��
        obj->transform_->velocity_.x = obj->weaponComponent_->xFlip_ ? -getParam()->SPEED_X : getParam()->SPEED_X;
        obj->transform_->velocity_.y = 0.0f;    // �O�̂���

        obj->state_++;
        /*fallthrough*/

    case 1:
        //////// �ʏ펞 ////////
        update(obj);    // ����̈ʒu�X�V
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
    // �ʒu�ɑ��x�𑫂�
    obj->transform_->position_ += obj->transform_->velocity_;
}

void NormalShotBehavior::calcAttackBox(OBJ2D* obj) const
{
    // �U������̌v�Z
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