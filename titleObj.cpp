#include "all.h"

// �A�j���f�[�^
namespace
{
    // �^�C�g���p��player
    GameLib::AnimeData animeTitlePlayerCore[] = {
        { &sprTitlePlayerCore, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // �R�A(�n�[�g�̂�)
    GameLib::AnimeData animeTitleCoreHeart[] =
    {
        {&sprTitleCoreHeart,10},
        {nullptr,-1},// �I���t���O
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
        obj->renderer_->data_ = getParam()->SPR_DATA;

        init(obj);

        obj->state_++;
        break;

    case 1:
        //////// �ʏ펞 ////////
        update(obj);

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
TitleStartObjBehavior::TitleStartObjBehavior()
{
    param_.SPR_DATA = &sprTitleCoreFrame;
    param_.SIZE = {100,100};
    param_.SCALE = {2.0f,2.0f};
    //param_.ATTACK_BOX[0] = { -33, 0,19,53 };
    param_.ATTACK_BOX[0] = { -13, 20,-1,33 };
}

void TitleStartObjBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    static bool wait = false;

    // �摜���؂�ւ��O��player��frame�Əd�Ȃ�ʒu�ɕύX����
    VECTOR2 pos = src->transform_->position_;
    dst->transform_->position_ = { pos.x - 7.0f,pos.y + 28 };

    src->performComponent_->isTrigger = true;

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

// �X�V
void TitleStartObjBehavior::update(OBJ2D* obj) const
{
    if (!Title::instance()->player()) return;

    const OBJ2D*  pl    = Title::instance()->player();
    const VECTOR2 plPos = pl->transform_->position_;
    const VECTOR2 pos   = obj->transform_->position_;
    Renderer* r = obj->renderer_;

    // �v���C���[���v���C���[�t���[���ɋ߂Â����瑾�点��
    if (plPos.x >= pos.x - 250 && plPos.x <= pos.x + 250 &&
        plPos.y >= pos.y - 250 && plPos.y <= pos.y + 250 )
    {
        r->drawScale_ = { 2.25f,2.25f };

        // Start�e�L�X�g�\��(�v���C���[��update���Ȃ��Ȃ��Ă���Δ�\��)
        if (pl->update_) Title::instance()->isDispTextStart_ = true;
        else             Title::instance()->isDispTextStart_ = false;
    }
    else
    {
        r->drawScale_ = { 2.0f,2.0f };

        // Start�e�L�X�g��\��
        Title::instance()->isDispTextStart_ = false;
    }
}


// �G���h
TitleEndObjBehavior::TitleEndObjBehavior()
{
    param_.SPR_DATA = &sprTitleTrashBox01;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.SCALE = { 2.0f, 2.0f };

    param_.ATTACK_BOX[0] = { -30, -30,30,30 };
    //param_.ATTACK_BOX[0] = { -47, 20,18,85 };
}

void TitleEndObjBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    // �R�A�̂���ʒu�Ɏ��@�̍��W��ύX
    //dst->transform_->position_ = src->transform_->position_;

    src->performComponent_->isTrigger = true;
    src->collider_->judgeFlag_ = false;

    // ���@�𑀍�ł��Ȃ�����
    dst->transform_->velocity_ = { 0.0f,0.0f };
    dst->update_ = nullptr;
}

// �X�V
void TitleEndObjBehavior::update(OBJ2D* obj) const
{
    if (!Title::instance()->player()) return;

    const VECTOR2 plPos = Title::instance()->player()->transform_->position_;
    const VECTOR2 pos   = obj->transform_->position_;
    Renderer* r = obj->renderer_;

    // �v���C���[���S�~���ɋ߂Â�����ς��ς�������
    if (plPos.x >= pos.x - 250 && plPos.x <= pos.x + 250 &&
        plPos.y >= pos.y - 250 && plPos.y <= pos.y + 250 )
    {
        r->data_      = &sprTitleTrashBox02;
        r->drawScale_ = { 2.25f,2.25f };

        // Exit�e�L�X�g�\��
        Title::instance()->isDispTextExit_ = true;
    }
    else 
    {
        r->data_      = &sprTitleTrashBox01;
        r->drawScale_ = { 2.0f,2.0f };

        // Exit�e�L�X�g��\��
        Title::instance()->isDispTextExit_ = false;
    }
}


// �^�C�g�����S
TitleLogoObjBehavior::TitleLogoObjBehavior()
{
    param_.SPR_DATA = &sprTitleLogo;
    param_.SIZE = { 1024, 512 };
}

void TitleLogoObjBehavior::init(OBJ2D* obj) const
{
    // �`��ȊO�̔�����s��Ȃ�
    obj->collider_->judgeFlag_ = false;
    obj->collider_->isDrawHitRect_ = false;
    obj->collider_->isDrawAttackRect_ = false;
}

void TitleLogoObjBehavior::update(OBJ2D* obj) const
{
    if (!Title::instance()->player()) return;
    if (!Title::instance()->player()->performComponent_->isTrigger) return;
    if (!Title::instance()->player()->update_) return;


    const Transform* t = obj->transform_;
    const Collider*  c = obj->collider_;
    Renderer* r = obj->renderer_;

    const VECTOR2& plPos = Title::instance()->player()->transform_->position_;

    const float logoLeft  = t->position_.x - (c->size_.x * 0.5f);
    const float logoRight = t->position_.x + (c->size_.x * 0.5f);
    const float logoUp    = t->position_.y - (c->size_.y * 0.5f);
    const float logoDown  = t->position_.y + (c->size_.y * 0.5f);

    if (plPos.x > logoLeft && plPos.x < logoRight &&
        plPos.y > logoUp   && plPos.y < logoDown)
    {
        r->color_.w += (-0.025f);

        if (r->color_.w < 0.5f) r->color_.w = 0.5f;
    }
    else
    {
        r->color_.w += 0.025f;

        if (r->color_.w > 1.0f) r->color_.w = 1.0f;
    }

}

// �������[�ړ�]
TitleHintMoveObjBehavior::TitleHintMoveObjBehavior()
{
    param_.SPR_DATA = &sprTitleUserMove;
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
    param_.SPR_DATA = &sprTitleUserSpace;
    param_.SCALE    = { 0.75f, 0.75f };
}

void TitleHintShotObjBehavior::init(OBJ2D* obj) const
{
    // �`��ȊO�̔�����s��Ȃ�
    obj->collider_->judgeFlag_ = false;
    obj->collider_->isDrawHitRect_ = false;
    obj->collider_->isDrawAttackRect_ = false;
}


//******************************************************************************
// 
//      TitlePlayer�i�^�C�g���p�̎��@)
// 
//******************************************************************************
OBJ2D* setTitlePlayer(OBJ2DManager* obj2dManager, BG* bg)
{
    const VECTOR2 pos = { BG::WINDOW_W * 0.5f - 215.0f,-250.0f };

    OBJ2D* player = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr,
        new PerformComponent
    );

    player->zOrder_ = 3;
    player->actorComponent_->parent_ = player;

    player->actorComponent_->No = ActorComponent::playerNum;
    player->update_ = TITLE_PLAYER_UPDATE;

    return obj2dManager->add(player, &titlePlayerHeartBehavior, pos);
}

// �n�[�g�̂�
TitlePlayerCoreHeartBehavior::TitlePlayerCoreHeartBehavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeTitleCoreHeart;

    param_.SIZE = VECTOR2(42.0f, 37.0f);
    param_.SCALE = { 2.0f,2.0f };
    param_.HIT_BOX[0] = { -20, -20, 20, 20 };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];
}

void TitlePlayerCoreHeartBehavior::areaCheck(OBJ2D* obj) const
{
    // �n�[�g�������鉉�o���̓G���A�`�F�b�N���΂�
    if (!Title::instance()->startPerform()) return;

    Transform* t = obj->transform_;
    //Collider*  c = obj->collider_;

    const float leftSize    = 42.0f;
    const float rightSize   = 42.0f;
    const float topSize     = 30.0f;
    const float bottomSize  = 44.0f;

    const float leftLimit   = leftSize;
    const float rightLimit  = BG::WINDOW_W - rightSize;
    const float topLimit    = topSize;
    const float bottomLimit = BG::WINDOW_H - bottomSize;

    if (t->position_.x >= rightLimit)
    {
        t->position_.x = rightLimit;
        if (t->velocity_.x > 0) t->velocity_.x = 0;
    }
    if (t->position_.x <= leftLimit)
    {
        t->position_.x = leftLimit;
        if (t->velocity_.x < 0) t->velocity_.x = 0;
    }
    if (t->position_.y >= bottomLimit)
    {
        t->position_.y = bottomLimit;
        if (t->velocity_.y > 0) t->velocity_.y = 0;
    }
    if (t->position_.y <= topLimit)
    {
        t->position_.y = topLimit;
        if (t->velocity_.y < 0) t->velocity_.y = 0;
    }
}

// �R�A
TitlePlayerCoreBehavior::TitlePlayerCoreBehavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeTitlePlayerCore;

    param_.SIZE = VECTOR2(PARTS_OBJ_SIZE, PARTS_OBJ_SIZE);
    param_.SCALE = { 2.0f,2.0f };
    param_.HIT_BOX[0] = { -10, -10, 10, 10 };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];
}