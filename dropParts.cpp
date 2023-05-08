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

    // �R����01
    GameLib::AnimeData animeCommon01[] = {
    { &sprPartsCommon01, 10 },
    { nullptr, -1 },// �I���t���O
    };

    // �R����02
    GameLib::AnimeData animeCommon02[] = {
    { &sprPartsCommon02, 10 },
    { nullptr, -1 },// �I���t���O
    };

    // �R����03
    GameLib::AnimeData animeCommon03[] = {
    { &sprPartsCommon03, 10 },
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

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    // �摜�T�C�Y(128*64�̔���)
    param_.HIT_BOX[0]    = { -64, -32, 64, 32 };   // �������`
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];   // �������`

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

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0] = {
        -64, -64,
         64,  64,
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

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0] = {
        -64, -64,
         64,  64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerTrash01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP = 3;
}


//******************************************************************************
// 
//      Common(���ʂȂ��p�[�c)
// 
//******************************************************************************

// Common01
DropCommon01Behavior::DropCommon01Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeCommon01;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
        -64.0f, -18.0f,
         64.0f,  18.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon01Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

// Common01_2(90�x��])
DropCommon01_2Behavior::DropCommon01_2Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeCommon01;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
         -18.0f,-64.0f,
          18.0f, 64.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon01_2Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

// Common02
DropCommon02Behavior::DropCommon02Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeCommon02;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
        -64.0f, -18.0f,
         64.0f,  18.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon02Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

// Common02_2(90�x��])
DropCommon02_2Behavior::DropCommon02_2Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeCommon02;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
         -18.0f,-64.0f,
          18.0f, 64.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon02_2Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

// Common03
DropCommon03Behavior::DropCommon03Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeCommon03;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
        -64.0f, -18.0f,
         64.0f,  18.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon03Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

// Common03_2(90�x��])
DropCommon03_2Behavior::DropCommon03_2Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeCommon03;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
         -18.0f,-64.0f,
          18.0f, 64.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon03_2Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

//******************************************************************************
// 
//      erase(����)
// 
//******************************************************************************
void EraseDropParts::erase(OBJ2D* obj) const
{
    ActorComponent* a = obj->actorComponent_;


    if (obj->transform_->scale_.x <= UPDATE_OBJ_SCALE_MIN_LIMIT) // �X�P�[����0�ȉ��ɂȂ�����
    {
        // �����G�t�F�N�g�ǉ�
        AddObj::addEffect(obj, &efcBombBehavior);

        obj->behavior_ = nullptr; // ����
        return;
    }


    if (a->parent_) // �e����ɓ��ꂽ��v���C���[�̃p�[�c�ɂȂ�
    {
        // ���̃G�t�F�N�g�ǉ�
        AddObj::addEffect(obj, &efcCombineBehavior);

        obj->behavior_ = obj->nextBehavior_;    // ����behavior����
        obj->eraser_   = obj->nextEraser_;      // ����eraser����

        if (obj->behavior_ == nullptr) return;
        obj->update_ = PLAYER_PATRS_UPDATE;     // update��ύX
        
        a->hp_ = a->nextHp_;

        obj->isBlink_ = false;    // ���ŏI��
       
        ++BasePlayerBehavior::plShrinkCount_;   // �k���܂ł̃J�E���g�����Z

        return;
    }
}

//******************************************************************************
//      �p�[�c��update
//******************************************************************************
void DROP_PARTS_UPDATE(OBJ2D* obj)
{
    Transform* t = obj->transform_;
    
    t->velocity_.x = DROP_PARTS_SPEED;
    t->velocity_.y = 0;
    t->position_ += t->velocity_;
}