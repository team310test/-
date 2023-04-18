#include "all.h"

namespace
{
    // �^���b�g01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// �I���t���O
    };
}

void BaseDropPartsBehavior::init(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = getParam()->ANIME_WAIT;

    obj->collider_->judgeFlag_        = true; // �����蔻����s��
    obj->collider_->isDrawHitRect_    = true;
    obj->collider_->isDrawAttackRect_ = false;

    obj->eraser_ = &eraseDropParts;
}

void BaseDropPartsBehavior::moveX(OBJ2D* obj) const
{
    // �����ړ�(��)
    obj->transform_->velocity_.x -= getParam()->ACCEL_X;

    ActorBehavior::moveX(obj);
}

void BaseDropPartsBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    if (!dst->actorComponent_->parent_) return; // �������肪�e�������Ă��Ȃ����return

    src->actorComponent_->parent_ = dst;        // �e��ۑ�
}

bool BaseDropPartsBehavior::isAlive(OBJ2D* obj) const
{
    return true;
}

void BaseDropPartsBehavior::areaCheck(OBJ2D* obj) const
{
    if (obj->transform_->position_.x < 0) // ��ʉE�ɍs������
    {
        obj->behavior_ = nullptr; // ����
    }
}


//******************************************************************************
// 
//      Turret(�U���p�[�c)
// 
//******************************************************************************

// Turret01
DropTurret01Behavior::DropTurret01Behavior()
{
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -80, 48, 125, 95 };   // �������`
    param_.HIT_BOX[1] = { -125,-95,10,50 };      // �l�W

    param_.ATTACK_BOX[0] = { -80, 48, 125, 95 };   // �������`
    param_.ATTACK_BOX[1] = { -125,-95,10,50 };      // �l�W

    param_.ACCEL_X = 2.0f;
    param_.ACCEL_Y = 2.0f;
    param_.SPEED_X_MAX = 2.0f;
    param_.SPEED_Y_MAX = 2.0f;

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerTurret01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;
}


//******************************************************************************
// 
//      Buff(�o�t�p�[�c)
// 
//******************************************************************************

// Buff01
DropBuff01Behavior::DropBuff01Behavior()
{
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = { player_size, player_size };
    param_.HIT_BOX[0] = {
        -player_hitBox, -player_hitBox,
         player_hitBox,  player_hitBox,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ACCEL_X = 2.0f;
    param_.ACCEL_Y = 2.0f;
    param_.SPEED_X_MAX = 2.0f;
    param_.SPEED_Y_MAX = 2.0f;

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerBuff01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;
}


//******************************************************************************
// 
//      erase(����)
// 
//******************************************************************************
void EraseDropParts::erase(OBJ2D* obj) const
{
    if (obj->transform_->scale_.x <= 0) // �X�P�[����0�ȉ��ɂȂ�����
    {
        obj->behavior_ = nullptr; // ����
        return;
    }

    if (obj->actorComponent_->parent_) // �e����ɓ��ꂽ��v���C���[�̃p�[�c�ɂȂ�
    {
        obj->behavior_ = obj->nextBehavior_; // ����behavior����
        obj->eraser_   = obj->nextEraser_;   // ����eraser����
        
        ++BasePlayerBehavior::plShrinkCount_; // �k���܂ł̃J�E���g�����Z
        return;
    }
}