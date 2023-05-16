#include "all.h"

// �A�j���f�[�^
namespace
{   
    //  �R�A01
    GameLib::AnimeData animeCore01[] = {
        { &sprEnemyCore01, 10 },
        { nullptr, -1 },// �I���t���O
    };

    //  �R�A02(�{�X)
    GameLib::AnimeData animeCore02[] = {
        { &sprEnemyCore02, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // �^���b�g01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
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


// �J�[�\���̍��W�擾
VECTOR2 getCursorPoint2()
{
    static POINT point_;

    GetCursorPos(&point_);
    ScreenToClient(GetActiveWindow(), &point_);

    VECTOR2 pos = { static_cast<float>(point_.x), static_cast<float>(point_.y) };
    return pos;
}

// �N���b�N�œG�o��������(�폜�\��)
OBJ2D* TsetMainEnemy(OBJ2DManager* obj2dManager, BG* bg, BaseEnemyBehavior* behavior, VECTOR2 pos,OBJ_DATA update,float accelX,int zOrder = 3)
{
    OBJ2D* enemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr,
        nullptr
    );

    enemy->zOrder_ = zOrder;
    enemy->actorComponent_->parent_ = enemy;
    enemy->actorComponent_->orgParent_ = enemy;
    enemy->update_ = update;
    enemy->actorComponent_->accel_.x = accelX;

    return obj2dManager->add(enemy, behavior, pos);
}
OBJ2D* TsetSubEnemy(OBJ2DManager* obj2dManager, BG* bg, BaseEnemyBehavior* behavior, OBJ2D* parent,OBJ2D* orgParent, VECTOR2 pos, OBJ_DATA update, int zOrder = 3)
{
    OBJ2D* subEnemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr,
        nullptr
    );

    subEnemy->zOrder_ = zOrder;
    // �e��ݒ�
    subEnemy->actorComponent_->parent_ = parent;
    subEnemy->actorComponent_->orgParent_ = orgParent;
    subEnemy->update_ = update;

    return obj2dManager->add(subEnemy, behavior, pos);
}
void addEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    OBJ2D* Parent = TsetMainEnemy(obj2dManager, bg, &enemyCore01Behavior, getCursorPoint2(),ENEMY_LINE, 5.0f);
    VECTOR2 pos = Parent->transform_->position_;
    // �T�u�p�[�c
    TsetSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, Parent, Parent,{ pos.x,pos.y - 229 }, ENEMY_PARTS);
    TsetSubEnemy(obj2dManager, bg, &enemyBuff01Behavior, Parent, Parent,{ pos.x,pos.y + 229 }, ENEMY_PARTS);
}

//******************************************************************************
//
//      BaseEnemyBehavior
//
//******************************************************************************
void BaseEnemyBehavior::init(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = getParam()->ANIME_WAIT;

    obj->collider_->judgeFlag_ = true;
    obj->collider_->isDrawHitRect_ = true;
    obj->collider_->isDrawAttackRect_ = true;

    obj->eraser_ = &eraseEnemy;

    obj->renderer_->Xflip(); // ���]������
}

void BaseEnemyBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
{
    ActorComponent* dstA = dst->actorComponent_;

    // �v���C���[��HP�����炷
    dstA->hp_ = std::max(dstA->hp_ - getParam()->ATTACK_POWER, 0);

    // ��eSE���Đ�
    Audio::play(SE_DMG, false);

    // ���肪�܂������Ă���ꍇ
    if (dstA->hp_ > 0)
    {
        // �����h�炷
        dst->isQuake_ = true;
        // �����_�ł����閳�G����
        dstA->damageTimer_ = DMG_TIME;

        // �v���C���[�R�A�Ȃ��p��eSE���Đ�
        if (dst == Game::instance()->player_)
        {
            Audio::play(SE_PL_CORE_ALERT, false);
        }
    }
}

bool BaseEnemyBehavior::isAlive(OBJ2D* obj) const
{
    return obj->actorComponent_->hp_ > 0;
}

void BaseEnemyBehavior::damageProc(OBJ2D* obj) const
{
    ActorComponent* a = obj->actorComponent_;

    // �_���[�W����
    //obj->actorComponent_->damaged();

    // ���G����
    //obj->actorComponent_->muteki();

    // �_�ł�����
    if (a->damageTimer_ > 0)
    {
        VECTOR4 color = obj->renderer_->color_;
        color.w = a->damageTimer_ & OBJ_DAMAGED_BLINK ? 1.0f : 0.2f;
        obj->renderer_->color_ = color;

        --a->damageTimer_;

        // �_���[�W�^�C�}�[��0�ȉ��ɂȂ邩�A�k�����Ȃ�color��߂�
        if (a->damageTimer_ <= 0 || obj->collider_->isShrink_)
        {
            obj->renderer_->color_ = { 1,1,1,1 };
        }
    }


    if (!obj->isQuake_) return;

    // �h�炷
    static Quake quake;
    quake.quakeDamage(obj);
}

void BaseEnemyBehavior::areaCheck(OBJ2D* obj) const
{
    const VECTOR2* size     = &obj->collider_->size_;
    const VECTOR2* pos      = &obj->transform_->position_;
    const float    margin   = 600.0f;

    const float leftLimit   = size->x - margin;
    const float rightLimit  = BG::WINDOW_W + size->x + margin;
    const float topLimit    = size->y - margin;
    const float bottomLimit = BG::WINDOW_H + size->y + margin;

    if (pos->x < leftLimit  ||
        pos->x > rightLimit ||
        pos->y < topLimit   ||
        pos->y > bottomLimit)
    {
        //obj->actorComponent_->hp_ = 0;              // ��ʊO�ɍs���������(�̗͂�0�ɂ���)
        obj->actorComponent_->parent_ = nullptr;    

        // hp��0�ɂȂ����Ƃ��Ɏ��SSE�����Ă��܂��̂�behavior�̕�������
        obj->behavior_ = nullptr;
        return;
    }

}



//******************************************************************************
//
//      EnemyCore01
//
//******************************************************************************
EnemyCore01Behavior::EnemyCore01Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animeCore01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = { 
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f, 
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f 
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = ENM_CORE01_HP;
    param_.ATTACK_POWER  = ENM_CORE01_ATK;

    // ����Behavior�Ȃ�
    param_.NEXT_BEHAVIOR = nullptr;
    param_.NEXT_ERASER   = nullptr;

    // �A�j���[�V�����̃p�����[�^
    param_.OBJ_ANIME     = &rotateAnime;
    param_.ROT_SPEED     = ENM_CORE01_ROT_SPEED;
}


//******************************************************************************
//
//      EnemyCore02(�{�X)
//
//******************************************************************************
EnemyCore02Behavior::EnemyCore02Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeCore02;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.SCALE = { 2.0f,2.0f };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP = ENM_CORE02_HP;
    param_.ATTACK_POWER = ENM_CORE02_ATK;

    // ����Behavior�Ȃ�
    param_.NEXT_BEHAVIOR = nullptr;
    param_.NEXT_ERASER = nullptr;

    // �A�j���[�V�����̃p�����[�^
    param_.OBJ_ANIME = &scaleAnime;
}


//******************************************************************************
// 
//      BaseEnemyPartsBehavior�i�G�l�~�[�̃p�[�c�̃x�[�X�j
// 
//******************************************************************************

void BaseEnemyPartsBehavior::shrink(OBJ2D* obj) const
{
    Behavior::shrink(obj);

    if (!obj->actorComponent_->orgParent_) return;
    if (!obj->actorComponent_->orgParent_->behavior_) return;

    contactToEnmCore(obj, obj->actorComponent_->orgParent_);
}


// �I���W�i�����@�̕��Ɍ������Ĉړ�����֐�
//static const float toCoreVelocity = 0.085f; // ���ɂȂ鑬�x(�I���W�i�����@�֌����������ɉe��)
float BaseEnemyPartsBehavior::toCoreVelocity_ = TO_CORE_SPEED;
// �I���W�i�����@�֌��������x
void BaseEnemyPartsBehavior::contactToEnmCore(OBJ2D* obj, OBJ2D* coreEnm) const
{
    if (!obj->collider_->isShrink_) return; // �k�����Ă��Ȃ����return

    const VECTOR2 coreEnmPos = coreEnm->transform_->position_;  // ���@�{�̂̈ʒu
    const VECTOR2 objPos     = obj->transform_->position_;      // obj�̈ʒu

    const VECTOR2 d    = { coreEnmPos - objPos };               // obj���玩�@�{�̂֌������x�N�g��
    const float   dist = sqrtf((d.x * d.x) + (d.y * d.y));      // obj���玩�@�{�̂܂ł̋���

    float addVelocity = 0.0f;                                   // obj��velocity�ɑ������x
    float num         = 0.0f;                                   // for����i�݂����Ȗ���
    const float copyDist = (dist >= 0) ? dist : dist * (-1);

    while (true)
    {
        if (num > 999) // �O�̂��߂ɏI�_��ݒu
        {
            addVelocity = toCoreVelocity_ * num;
            break;
        }

        // obj���玩�@�{�̂܂ł̋����������Ȃ邽�ё��x���㏸������
        // (���������������obj�����@�{�̂ɒǂ����Ȃ�����)
        if ((copyDist >= (50.0f * num) && copyDist <= 50.0f * (num + 1.0f)))  // �}0����}50�A�}50����}100�A�}100����}150...
        {
            addVelocity = (num != 0.0f) ? (toCoreVelocity_ * num) : toCoreVelocity_; // �}0����}50�܂ł̋�����num��0�Ȃ̂Ńf�t�H���g�̒l����

            break; // ��������̂�break;
        }

        // obj���玩�@�{�̂܂ł̋����ɂ���đ��x���㏸������
        // (���������������obj�����@�{�̂ɒǂ����Ȃ�����)
        if ((copyDist >= (50.0f * num) && copyDist <= 50.0f * (num + 1.0f)))  // �}0����}50�A�}50����}100�A�}100����}150...
        {
            addVelocity = (num != 0) ? (toCoreVelocity_ * num) : toCoreVelocity_;   // �}0����}50�܂ł̋�����num��0�Ȃ̂�0.1f����

            break; // ��������̂�break;
        }
        ++num; // num�����Z���Ă���
    }

    obj->transform_->velocity_ = {
        (d.x / dist) * (addVelocity),
        (d.y / dist) * (addVelocity),
    };


    //// �ő呬�x�`�F�b�N���s��
    //obj->transform_->velocity_.y = clamp(
    //    obj->transform_->velocity_.y, -PL_SPEED_MAX, PL_SPEED_MAX
    //);
    //obj->transform_->velocity_.x = clamp(
    //    obj->transform_->velocity_.x, -PL_SPEED_MAX, PL_SPEED_MAX
    //);
    // �ʒu�X�V
    obj->transform_->position_ += obj->transform_->velocity_;
}



//******************************************************************************
//
//      Turret
//
//******************************************************************************

// Turret01(AimShot)
EnemyTurret01Behavior::EnemyTurret01Behavior()
{
    param_.ANIME_WAIT    = animeTurret01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = { 
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f, 
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = ENM_TURRET01_HP;
    param_.ATTACK_POWER  = ENM_TURRET01_ATK;

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR = &dropTurret01Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}

void EnemyTurret01Behavior::attack(OBJ2D* obj) const
{
    // �U���N�[���^�C������
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �U���N�[���^�C�����I����Ă��Ȃ����return
    if (obj->actorComponent_->attackTimer_ > 0) return;

    // �e��ǉ�
    AddObj::addShot(obj, &enmAimShotBehavior, obj->transform_->position_);

    // �e����SE�Đ�
    Audio::play(SE_SHOT, false);

    // �U���N�[���^�C���ݒ�
    obj->actorComponent_->attackTimer_ = ENM_TURRET01_ATK_TIME;
}

// Turret01Flip
EnemyTurret01FlipBehavior::EnemyTurret01FlipBehavior()
{
    param_.ANIME_WAIT = animeTurret01Flip;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP = ENM_TURRET01_HP;
    param_.ATTACK_POWER = ENM_TURRET01_ATK;

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR = &dropTurret01FlipBehavior;
    param_.NEXT_ERASER = &eraseDropParts;
}

void EnemyTurret01FlipBehavior::attack(OBJ2D* obj) const
{
    // �U���N�[���^�C������
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �U���N�[���^�C�����I����Ă��Ȃ����return
    if (obj->actorComponent_->attackTimer_ > 0) return;

    // �e��ǉ�
    AddObj::addShot(obj, &enmAimShotBehavior, obj->transform_->position_);

    // �e����SE�Đ�
    Audio::play(SE_SHOT, false);

    // �U���N�[���^�C���ݒ�
    obj->actorComponent_->attackTimer_ = ENM_TURRET01_ATK_TIME;
}

// Turret02(CurveShot)
EnemyTurret02Behavior::EnemyTurret02Behavior()
{
    param_.ANIME_WAIT = animeTurret02;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    // �摜�T�C�Y(128*64�̔���)
    param_.HIT_BOX[0] = { -64, -32, 64, 32 };   // �������`    
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];   // �������`

    param_.ROTATION = ToRadian(ENM_TURRET02_ANGLE);

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR = &dropTurret02Behavior;
    param_.NEXT_ERASER = &eraseDropParts;
}

void EnemyTurret02Behavior::attack(OBJ2D* obj) const
{
    // �U���N�[���^�C������
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �U���N�[���^�C�����I����Ă��Ȃ����return
    if (obj->actorComponent_->attackTimer_ > 0) return;

    // �e��ǉ�
    const float radius = obj->collider_->size_.x * 0.5f;
    const float angle = obj->transform_->rotation_;
    VECTOR2 pos = obj->transform_->position_;
    pos.x -= cosf(angle) * radius;
    pos.y -= sinf(angle) * radius;

    AddObj::addShot(obj, &enmCurveShotBehavior, pos);

    obj->actorComponent_->attackTimer_ = 120;
}

// Turret02Flip
EnemyTurret02FlipBehavior::EnemyTurret02FlipBehavior()
{
    param_.ANIME_WAIT = animeTurret02Flip;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    // �摜�T�C�Y(128*64�̔���)
    param_.HIT_BOX[0] = { -64, -32, 64, 32 };   // �������`    
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];   // �������`

    param_.ROTATION = ToRadian(-ENM_TURRET02_ANGLE);

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR = &dropTurret02FlipBehavior;
    param_.NEXT_ERASER = &eraseDropParts;
}

void EnemyTurret02FlipBehavior::attack(OBJ2D* obj) const
{
    // �U���N�[���^�C������
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �U���N�[���^�C�����I����Ă��Ȃ����return
    if (obj->actorComponent_->attackTimer_ > 0) return;

    // �e��ǉ�
    const float radius = obj->collider_->size_.x * 0.5f;
    const float angle = obj->transform_->rotation_;
    VECTOR2 pos = obj->transform_->position_;
    pos.x -= cosf(angle) * radius;
    pos.y -= sinf(angle) * radius;

    AddObj::addShot(obj, &enmCurveShotFlipBehavior, pos);

    obj->actorComponent_->attackTimer_ = 120;
}


//******************************************************************************
//
//      Shield�i�h��p�[�c�j
//
//******************************************************************************

// Shield01
EnemyShield01Behavior::EnemyShield01Behavior()
{
    param_.ANIME_WAIT    = animeShield01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.25f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.25f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = ENM_SHIELD01_HP;
    param_.ATTACK_POWER  = ENM_SHIELD01_ATK;

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR = &dropShield01Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}


//******************************************************************************
//
//      Buff�i�o�t�p�[�c�j
//
//******************************************************************************


// Buff01
EnemyBuff01Behavior::EnemyBuff01Behavior()
{
    param_.ANIME_WAIT    = animeBuff01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP           = ENM_BUFF01_HP;
    param_.ATTACK_POWER = ENM_BUFF01_ATK;

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR = &dropBuff01Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}

// �U���^�C�v��ENEMY�Ȃ̂�dst�͖���(�G�l�~�[)�ɂȂ�(����ɑ̓�����_���[�W���^�����Ȃ�)
void EnemyBuff01Behavior::hit(OBJ2D*, OBJ2D* dst) const
{
    // �U���N�[���^�C���������i�e���㏸�j
    dst->actorComponent_->attackTimer_ -= BUFF_SUB_ATK_TIMER;
}


//******************************************************************************
// 
//      Common(���ʂȂ��p�[�c)
// 
//******************************************************************************

// Common01
EnemyCommon01Behavior::EnemyCommon01Behavior()
{
    param_.ANIME_WAIT       = animeCommon01;

    param_.SIZE             = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]       = {
        -COMMON_HITBOX_64, -COMMON_HITBOX_18,
         COMMON_HITBOX_64,  COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0]    = param_.HIT_BOX[0];

    param_.HP               = ENM_COMMON01_HP;
    param_.ATTACK_POWER     = ENM_COMMON01_ATK;

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR    = &dropCommon01Behavior;
    param_.NEXT_ERASER      = &eraseDropParts;
}

// Common01_2(90�x��])
// Common04([01]��90�x��])
EnemyCommon04Behavior::EnemyCommon04Behavior()
{
    param_.ANIME_WAIT       = animeCommon01;

    param_.SIZE             = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]       = {
         -COMMON_HITBOX_18, -COMMON_HITBOX_64,
          COMMON_HITBOX_18,  COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0]    = param_.HIT_BOX[0];
    param_.ROTATION         = ROT_90;

    param_.HP               = ENM_COMMON04_HP;
    param_.ATTACK_POWER     = ENM_COMMON04_ATK;

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR    = &dropCommon01_2Behavior;
    param_.NEXT_ERASER      = &eraseDropParts;
}

// Common02
EnemyCommon02Behavior::EnemyCommon02Behavior()
{
    param_.ANIME_WAIT    = animeCommon02;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
        -COMMON_HITBOX_64, -COMMON_HITBOX_18,
         COMMON_HITBOX_64,  COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = ENM_COMMON02_HP;
    param_.ATTACK_POWER  = ENM_COMMON02_ATK;

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR = &dropCommon02Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}

// Common02_2(90�x��])
// Common05([02]��90�x��])
EnemyCommon05Behavior::EnemyCommon05Behavior()
{
    param_.ANIME_WAIT    = animeCommon02;
                         
    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18, -COMMON_HITBOX_64,
          COMMON_HITBOX_18,  COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ROTATION      = ROT_90;

    param_.HP            = ENM_COMMON05_HP;
    param_.ATTACK_POWER  = ENM_COMMON05_ATK;

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR = &dropCommon02_2Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}

// Common03
EnemyCommon03Behavior::EnemyCommon03Behavior()
{
    param_.ANIME_WAIT    = animeCommon03;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]    = {
        -COMMON_HITBOX_64, -COMMON_HITBOX_18,
         COMMON_HITBOX_64,  COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = ENM_COMMON03_HP;
    param_.ATTACK_POWER  = ENM_COMMON03_ATK;

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR = &dropCommon03Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}

// Common03_2(90�x��])
// Common06([03]��90�x��])
EnemyCommon06Behavior::EnemyCommon06Behavior()
{
    param_.ANIME_WAIT     = animeCommon03;

    param_.SIZE           = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]     = {
         -COMMON_HITBOX_18, -COMMON_HITBOX_64,
          COMMON_HITBOX_18,  COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0]  = param_.HIT_BOX[0];
    param_.ROTATION       = ROT_90;

    param_.HP             = ENM_COMMON06_HP;
    param_.ATTACK_POWER   = ENM_COMMON06_ATK;

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR  = &dropCommon03_2Behavior;
    param_.NEXT_ERASER    = &eraseDropParts;
}

//******************************************************************************
//
//      erase�i�����j
//
//******************************************************************************
Behavior* trashbahavior[] = {
    &dropTrash01Behavior,
    &dropTrash02Behavior,
    //&dropTrash03Behavior,
};

void EraseEnemy::erase(OBJ2D* obj) const
{
    // behavior���Ȃ����return
    if (!obj->behavior_) return;

    // parent���ȗ�����Ɛ���ɓ��삵�Ȃ��̂œP�p
    //OBJ2D* parent    = obj->actorComponent_->parent_;
    //OBJ2D* orgParent = obj->actorComponent_->orgParent_;

    ActorComponent* a = obj->actorComponent_;

    // TODO: �{�X������ł�����c���Ă���G�l�~�[������
    // �{�X������ł��Ď������{�X�łȂ����
    if (Game::instance()->isBossDied_ && obj->behavior_ != &enemyCore02Behavior)
    {
        // �����G�t�F�N�g
        AddObj::addEffect(obj, &efcBombBehavior);

        // ���SSE
        Audio::play(SE_DEATH, false);

        // ����
        a->parent_      =  nullptr;
        a->orgParent_   = nullptr;
        obj->behavior_  = nullptr;

        return;
    }
    // TODO: �{�X������ł��ă{�X�Ȃ�return�����s��
    else if (Game::instance()->isBossDied_ && obj->behavior_ == &enemyCore02Behavior)
    { 
        return; 
    } 


    // �X�P�[�������ȉ��ɂȂ��������
    //if (obj->transform_->scale_.x <= UPDATE_OBJ_SCALE_MIN_LIMIT)
    if (obj->transform_->scale_.x < 1.0f && !obj->collider_->isShrink_) // 1��ł��k�����������
    {
        // �����G�t�F�N�g
        AddObj::addEffect(obj, &efcBombBehavior);

        // ���SSE
        Audio::play(SE_DEATH, false);

        a->parent_      = nullptr; // �e�����Z�b�g
        a->orgParent_   = nullptr; // ���̐e�����Z�b�g
        obj->behavior_  = nullptr; // ����������

        return;
    }


    // HP��0�ȉ��ɂȂ��
    if (!a->isAlive())
    {
        // �����G�t�F�N�g
        AddObj::addEffect(obj, &efcBombBehavior);

        a->parent_ = nullptr; // �e�����Z�b�g

        // TODO: �{�X�����񂾂�{�X���S�t���O�𗧂�����
        // �������{�X�Ȃ�
        if (obj->behavior_ == &enemyCore02Behavior)
        {
            a->orgParent_ = nullptr;  // ���̐e�����Z�b�g

            // �{�X���S�t���O��true
            Game::instance()->isBossDied_ = true;

            return;
        }


        // �������R�A�łȂ��Ȃ�S�~�A�C�e��������
        if (obj != a->orgParent_)
        {
            // ���SSE
            Audio::play(SE_DEATH, false);

            a->orgParent_  = nullptr;           // ���̐e�����Z�b�g

            // ����behavior�Eeraser�i�h���b�v���݃A�C�e���j����
            obj->behavior_ = trashbahavior[rand() % 2];
            obj->eraser_   = &eraseDropParts;         
            obj->update_   = DROP_PARTS_UPDATE; // update��ύX

            a->hp_ = 0;                         // HP��0�ɂ���
            obj->renderer_->Xflip();            // ���]������i�}�X�N�����ɏd�v�j

            obj->isBlink_  = true;              // ���ł�����

            return;
        }

        // �G�l�~�[�R�A���SSE
        Audio::play(SE_ENM_CORE_DEATH, false);

        a->orgParent_  = nullptr;               // ���̐e�����Z�b�g

        obj->behavior_ = nullptr;               // ����(�R�A)������
        return;
    }

        
    // �e�����݂��Ȃ����
    if (!a->parent_)
    {
        ++a->deathDelayTimer_;   // ���S�f�B���C�^�C�}�[�����Z����
    }
    else // �e�����݂��Ă���
    {
        // �܂������Ă��ăG�l�~�[�p�[�c�ł����return
        if (a->parent_->behavior_)
        {
            if (a->parent_->behavior_->getType() == OBJ_TYPE::ENEMY) return;
        }

        // ����ł�����
        a->parent_    = nullptr; // �e�����Z�b�g
        a->orgParent_ = nullptr; // ���̐e�����Z�b�g
        return;
    }


    if (a->deathDelayTimer_ < PARTS_DEATH_DELAY_TIME) return;

    // ���S�f�B���C�^�C�}�[����莞�Ԃ�������h���b�v�p�[�c���������s��
    //�i�e�����񂾂Ƃ��̃p�[�c�̘A�����U�ɒx�������肾���j
    
    // �����G�t�F�N�g
    AddObj::addEffect(obj, &efcBombBehavior);

    // ���SSE
    Audio::play(SE_DEATH, false);

    // ����behavior�Eeraser�i�h���b�v�A�C�e���j����
    obj->behavior_ = obj->nextBehavior_;
    obj->eraser_   = obj->nextEraser_;


    if (obj->behavior_ == nullptr) return;  // ����Behavior���Ȃ����return


    obj->update_ = DROP_PARTS_UPDATE;       // update��ύX

    a->hp_ = 0;                             // HP��0�ɂ���
    obj->renderer_->Xflip();                // ���]������
    obj->transform_->rotation_ *= -1;       // �p�x���]

    obj->isBlink_ = true;                   // ���ł�����

    return;
    
    
}


//******************************************************************************
//
//      �G�l�~�[��update
//
//******************************************************************************
// �R�A�̒����ړ�
void ENEMY_LINE(OBJ2D* obj)
{
    Transform* t = obj->transform_;
    const float speedX = obj->actorComponent_->accel_.x;

    t->velocity_ = { -speedX, 0.0f };
}

// x���̖ڕW�n�_�ɒB����ƕʂ̕����ֈړ�����(��)
void ENEMY_TARGET_X(OBJ2D* obj)
{
    Transform* t = obj->transform_;
    ActorComponent* a = obj->actorComponent_;
    const float targetPosX = a->addition_.x;

    switch (obj->act_)
    {
    case 0:
        if (t->position_.x < targetPosX) obj->act_++;

        t->velocity_ = { -a->accel_.x, a->accel_.y };
        break;
    case 1:
        t->velocity_ = { -a->addition_.y,a->addition_.z };

        break;
    default:
        break;
    }
}
// �p�[�c�̃A�b�v�f�[�g
void ENEMY_PARTS(OBJ2D* obj)
{
    Transform*      t = obj->transform_;
    ActorComponent* a = obj->actorComponent_;

    if (!a->parent_)            return; // �e�����݂��Ȃ����return
    if (!a->parent_->behavior_) return;


    t->velocity_ = a->parent_->transform_->velocity_;
}