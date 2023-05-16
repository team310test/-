#include "all.h"

namespace
{
    // �^���b�g01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // �^���b�g01(���])
    GameLib::AnimeData animeTurret01Flip[] = {
        { &sprPartsTurret01Flip, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // �^���b�g02
    GameLib::AnimeData animeTurret02[] = {
        { &sprPartsTurret02, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // �^���b�g02(���])
    GameLib::AnimeData animeTurret02Flip[] = {
        { &sprPartsTurret02Flip, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // �V�[���h01
    GameLib::AnimeData animeShield01[] = {
    { &sprPartsShield01, 10 },
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
    //  �S�~02
    GameLib::AnimeData animeTrash02[] = {
        { &sprPartsTrash02, 10 },
        { nullptr, -1 },// �I���t���O
    };    
    //  �S�~03
    GameLib::AnimeData animeTrash03[] = {
        { &sprPartsTrash03, 10 },
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
    const VECTOR2* pos = &obj->transform_->position_;
    const VECTOR2* size = &obj->collider_->size_;

    const float leftLimit = size->x;
    const float rightLimit = BG::WINDOW_W + size->x;
    const float topLimit = size->y;
    const float bottomLimit = BG::WINDOW_H + size->y;

    if (pos->x < leftLimit || pos->x > rightLimit ||
        pos->y < topLimit || pos->y > bottomLimit)
    {
        obj->behavior_ = nullptr; // ��ʊO�ɍs���������
        return;
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
    param_.ANIME_WAIT    = animeTurret01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerTurret01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_TURRET01_NEXT_HP;
}

// Turret01(���])
DropTurret01FlipBehavior::DropTurret01FlipBehavior()
{
    param_.ANIME_WAIT = animeTurret01Flip;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerTurret01FlipBehavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = DROP_TURRET01_NEXT_HP;
}

// Turret02(CurveShot)
DropTurret02Behavior::DropTurret02Behavior()
{
    param_.ANIME_WAIT = animeTurret02;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerTurret02Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = DROP_TURRET03_NEXT_HP;
}

DropTurret02FlipBehavior::DropTurret02FlipBehavior()
{
    param_.ANIME_WAIT = animeTurret02Flip;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerTurret02FlipBehavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = DROP_TURRET03_NEXT_HP;
}

//******************************************************************************
// 
//      Shield(�h��p�[�c)
// 
//******************************************************************************
DropShield01Behavior::DropShield01Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animeShield01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.25f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.25f,  PARTS_OBJ_SIZE * 0.5f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerShield01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_SHIELD01_NEXT_HP;
}


//******************************************************************************
// 
//      Buff(�o�t�p�[�c)
// 
//******************************************************************************

// Buff01
DropBuff01Behavior::DropBuff01Behavior()
{
    param_.ANIME_WAIT    = animeBuff01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerBuff01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_BUFF01_NEXT_HP;
}


//******************************************************************************
// 
//      Trash(�S�~�p�[�c)
// 
//******************************************************************************

// Trash01
DropTrash01Behavior::DropTrash01Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animeTrash01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerTrash01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_TRASH01_NEXT_HP;
}

// Trash02
DropTrash02Behavior::DropTrash02Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animeTrash02;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerTrash02Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_TRASH02_NEXT_HP;
}

// Trash03
DropTrash03Behavior::DropTrash03Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animeTrash03;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerTrash03Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_TRASH03_NEXT_HP;
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
    param_.ANIME_WAIT    = animeCommon01;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]    = {
        -COMMON_HITBOX_64, -COMMON_HITBOX_18,
         COMMON_HITBOX_64,  COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_COMMON01_NEXT_HP;
}

// Common01_2(90�x��])
DropCommon01_2Behavior::DropCommon01_2Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animeCommon01;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18,-COMMON_HITBOX_64,
          COMMON_HITBOX_18, COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon01_2Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_COMMON04_NEXT_HP;
}

// Common02
DropCommon02Behavior::DropCommon02Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animeCommon02;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]    = {
        -COMMON_HITBOX_64, -COMMON_HITBOX_18,
         COMMON_HITBOX_64,  COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon02Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_COMMON02_NEXT_HP;
}

// Common02_2(90�x��])
DropCommon02_2Behavior::DropCommon02_2Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animeCommon02;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18,-COMMON_HITBOX_64,
          COMMON_HITBOX_18, COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon02_2Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_COMMON05_NEXT_HP;
}

// Common03
DropCommon03Behavior::DropCommon03Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animeCommon03;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]    = {
        -COMMON_HITBOX_64, -COMMON_HITBOX_18,
         COMMON_HITBOX_64,  COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon03Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_COMMON03_NEXT_HP;
}

// Common03_2(90�x��])
DropCommon03_2Behavior::DropCommon03_2Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animeCommon03;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18,-COMMON_HITBOX_64,
          COMMON_HITBOX_18, COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����behavior�Eeraser�i�v���C���[�j
    param_.NEXT_BEHAVIOR = &playerCommon03_2Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP       = DROP_COMMON06_NEXT_HP;
}

//******************************************************************************
// 
//      erase(����)
// 
//******************************************************************************
void EraseDropParts::erase(OBJ2D* obj) const
{
    // behavior���Ȃ����return
    if (!obj->behavior_) return; 

    ActorComponent* a = obj->actorComponent_;


    //if (obj->transform_->scale_.x <= UPDATE_OBJ_SCALE_MIN_LIMIT) // �X�P�[����0�ȉ��ɂȂ�����
    if (obj->transform_->scale_.x < 1.0f && !obj->collider_->isShrink_) // 1��ł��k�����������
    {
        // �����G�t�F�N�g�ǉ�
        AddObj::addEffect(obj, &efcBombBehavior);

        // ���SSE���Đ�
        Audio::play(SE_DEATH, false);

        obj->behavior_ = nullptr; // ����
        return;
    }


    if (a->parent_) // �e����ɓ��ꂽ��v���C���[�̃p�[�c�ɂȂ�
    {
        // ���̃G�t�F�N�g�ǉ�
        AddObj::addEffect(obj, &efcCombineBehavior);

        // ����SE�Đ�
        Audio::play(SE_COMBINE, false);

        obj->behavior_ = obj->nextBehavior_;    // ����behavior����
        obj->eraser_   = obj->nextEraser_;      // ����eraser����

        if (obj->behavior_ == nullptr) return;
        obj->update_ = PLAYER_PATRS_UPDATE;     // update��ύX
        
        a->hp_ = a->nextHp_;                    // ����HP����
        a->attackTimer_ = 0;                    // �U���N�[���^�C�������Z�b�g
        a->damageTimer_ = COMBINE_DMG_TIME;    // ������������͂��΂炭���G��Ԃɂ���

        obj->isBlink_ = false;                  // ���ŏI��
       
        ++BasePlayerBehavior::plShrinkCount_;   // �k���܂ł̃J�E���g�����Z

        ++BasePlayerBehavior::plPartsCurrentCount_;

        return;
    }

}

//******************************************************************************
//      �p�[�c��update
//******************************************************************************
void DROP_PARTS_UPDATE(OBJ2D* obj)
{
    Transform* t = obj->transform_;
    
    t->velocity_.x = DROP_PARTS_SPEED_X;
    t->velocity_.y = 0;
    t->position_ += t->velocity_;
}