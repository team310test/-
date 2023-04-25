#include "all.h"

namespace
{
    // �^���b�g01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// �I���t���O
    };

    //  �o�t01
    GameLib::AnimeData animeBuff01[] = {
        { &sprPartsBuff01, 10 },
        { nullptr, -1 },// �I���t���O
    };

    //  �S�~01
    GameLib::AnimeData animeTrash01[] = {
        { &sprPartsTrash01, 10 },
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

void BaseDropPartsBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    if (!dst->actorComponent_->parent_) return; // �������肪�e�������Ă��Ȃ����return

    src->actorComponent_->parent_ = dst;        // �e��ۑ�
}

bool BaseDropPartsBehavior::isAlive(OBJ2D* /*obj*/) const
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

    // �摜�T�C�Y(128*64�̔���)
    param_.HIT_BOX[0] = { -64, -32, 64, 32 };    // �������`
    //param_.HIT_BOX[1] = { -125,-95,10,50 };    // �l�W

    param_.ATTACK_BOX[0] = param_.HIT_BOX[0]; // �������`
    //param_.ATTACK_BOX[1] = param_.HIT_BOX[1];   // �l�W

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
    param_.ANIME_WAIT = animeBuff01;

    param_.SIZE = { player_size, player_size };
    param_.HIT_BOX[0] = {
        -player_hitBox, -player_hitBox,
         player_hitBox,  player_hitBox,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerBuff01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;
}


//******************************************************************************
// 
//      Trash(�S�~�p�[�c)
// 
//******************************************************************************
DropTrash01Behavior::DropTrash01Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeTrash01;

    param_.SIZE = { player_size, player_size };
    param_.HIT_BOX[0] = {
        -player_hitBox, -player_hitBox,
         player_hitBox,  player_hitBox,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerTrash01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP = 3;
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

        if (obj->behavior_ == nullptr) return;
        obj->behavior_->update = PATRS_PLAYER_UPDATE;  // update��ύX

        obj->actorComponent_->hp_ = obj->actorComponent_->nextHp_;  // ����HP����
        
        ++BasePlayerBehavior::plShrinkCount_; // �k���܂ł̃J�E���g�����Z
        return;
    }
}

//******************************************************************************
//      �p�[�c��update
//******************************************************************************
#define ITEM_SUPEED -2.0f
void PARTS_UPDATE(OBJ2D* obj)
{
    Transform* t = obj->transform_;
    
    t->velocity_.x = ITEM_SUPEED;
    t->position_ += t->velocity_;
}