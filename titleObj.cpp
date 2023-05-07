#include "all.h"

// �A�j���f�[�^
namespace
{
    // �ҋ@(player)
    GameLib::AnimeData animePlayerCore01[] = {
        { &sprPlayerCore01, 10 },
        { nullptr, -1 },// �I���t���O
    };
}

//******************************************************************************
//
//      BaseTitleObjBehavior
//
//******************************************************************************
void BaseTitleObjBehavior::move(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = nullptr;
    switch (obj->state_)
    {
    case 0:
        //////// �����ݒ� ////////
        // �A�j���̏����ݒ�
        obj->transform_->scale_ = getParam()->SCALE;
        obj->renderer_->drawScale_ = getParam()->SCALE;
        obj->collider_->size_ = {
            getParam()->SIZE.x,
            getParam()->SIZE.y
        };
        obj->renderer_->color_ = getParam()->COLOR;
        obj->renderer_->data_ = getParam()->SPR_DETA;

        init(obj);

        obj->state_++;
        break;

    case 1:
        //////// �ʏ펞 ////////

        break;
    }

    for (int i = 0; i < Collider::boxMax; ++i)
        obj->collider_->calcHitBox(getParam()->HIT_BOX[i], i);

    for (int i = 0; i < Collider::boxMax; ++i)
        obj->collider_->calcAttackBox(getParam()->ATTACK_BOX[i], i);
}

void BaseTitleObjBehavior::init(OBJ2D* obj) const
{
    obj->collider_->judgeFlag_ = true;
    obj->collider_->isDrawHitRect_ = true;
    obj->collider_->isDrawAttackRect_ = true;
}

//******************************************************************************
//
//      BaseTitleObjBehavior
//
//******************************************************************************
// �X�^�[�g
TitleStateObjBehavior::TitleStateObjBehavior()
{
    param_.SPR_DETA = &sprTitleCore;
    param_.SIZE = {100,100};
    param_.SCALE = {2.0f,2.0f};
    //param_.ATTACK_BOX[0] = { -33, 0,19,53 };
    param_.ATTACK_BOX[0] = { -13, 20,-1,33 };
}

void TitleStateObjBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    static bool wait = false;

    // �摜���؂�ւ��O��player��frame�Əd�Ȃ�ʒu�ɕύX����
    VECTOR2 pos = src->transform_->position_;
    dst->transform_->position_ = { pos.x - 7.0f,pos.y + 28 };

    src->titleComponent_->isTrigger = true;

    // 1�t���[��������x�点��
    if (wait)
    {
        // �摜���؂�ւ����player��frame�̍������ʒu�ɕύX����
        dst->transform_->position_ = src->transform_->position_;
        src->collider_->judgeFlag_ = false; // ��������Ȃ��悤�ɂ���
        src->renderer_->color_.w = 0.0f;    // �����ɂ���
        src->zOrder_ = 4;                   // �����̏��Ԃ�ύX
        wait = false;                       // �ϐ�������

        return;
    }

    wait = true;
    dst->update_ = nullptr;                 // ���@��ύX�@����ł��Ȃ�����
    dst->behavior_ = &titlePlayerCoreBehavior;   // �摜(Behavior)�ύX
    dst->transform_->velocity_ = { 0.0f,0.0f };
}

// �G���h
TitleEndObjBehavior::TitleEndObjBehavior()
{
    param_.SPR_DETA = &sprTitleTrash;
    param_.SIZE = { 128,128 };
    param_.ATTACK_BOX[0] = { -30, -30,30,30 };
    //param_.ATTACK_BOX[0] = { -47, 20,18,85 };
}

void TitleEndObjBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    // �R�A�̂���ʒu�Ɏ��@�̍��W��ύX
    //dst->transform_->position_ = src->transform_->position_;

    src->titleComponent_->isTrigger = true;
    src->collider_->judgeFlag_ = false;

    // ���@�𑀍�ł��Ȃ�����
    dst->transform_->velocity_ = { 0.0f,0.0f };
    dst->update_ = nullptr;
}

// �^�C�g�����S
TitleLogoObjBehavior::TitleLogoObjBehavior()
{
    param_.SPR_DETA = &sprTitleLogo;
}

void TitleLogoObjBehavior::init(OBJ2D* obj) const
{
    // �`��ȊO�̔�����s��Ȃ�
    obj->collider_->judgeFlag_ = false;
    obj->collider_->isDrawHitRect_ = false;
    obj->collider_->isDrawAttackRect_ = false;
}
// �������[�ړ�]
TitleHintMoveObjBehavior::TitleHintMoveObjBehavior()
{
    param_.SPR_DETA = &sprTitleUser01;
}

void TitleHintMoveObjBehavior::init(OBJ2D* obj) const
{
    // �`��ȊO�̔�����s��Ȃ�
    obj->collider_->judgeFlag_ = false;
    obj->collider_->isDrawHitRect_ = false;
    obj->collider_->isDrawAttackRect_ = false;
}
// �������[�U��]
TitleHintShotObjBehavior::TitleHintShotObjBehavior()
{
    param_.SPR_DETA = &sprTitleUser02;
}

void TitleHintShotObjBehavior::init(OBJ2D* obj) const
{
    // �`��ȊO�̔�����s��Ȃ�
    obj->collider_->judgeFlag_ = false;
    obj->collider_->isDrawHitRect_ = false;
    obj->collider_->isDrawAttackRect_ = false;
}
