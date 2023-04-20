#include "all.h"

// �A�j���f�[�^
namespace
{   
    //  �R�A01
    GameLib::AnimeData animeCore01[] = {
        { &sprPartsCore01, 10 },
        { nullptr, -1 },// �I���t���O
    };

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


OBJ2D* setMainEnemy(OBJ2DManager* obj2dManager, BG* bg, BaseEnemyBehavior* behavior, VECTOR2 pos, int zOrder = 3)
{
    OBJ2D* enemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    enemy->zOrder_ = 3;
    enemy->actorComponent_->parent_ = enemy;

    return obj2dManager->add(enemy, &enemyCore01Behavior, pos);
}
void setSubEnemy(OBJ2DManager* obj2dManager, BG* bg, BaseEnemyBehavior* behavior, OBJ2D* parent, VECTOR2 pos, int zOrder = 3)
{
    VECTOR2 POS = parent->transform_->position_ + pos;

    OBJ2D* subEnemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    subEnemy->zOrder_ = zOrder;
    // �e��ݒ�
    subEnemy->actorComponent_->parent_ = parent;

    obj2dManager->add(subEnemy, behavior, POS);
}

void setEnemy01(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos)
{
    OBJ2D* Parent = setMainEnemy(obj2dManager, bg, &enemyCore01Behavior, pos);
    setSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, Parent, { -64,96 });
}
void setEnemy02(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos)
{
    OBJ2D* Parent = setMainEnemy(obj2dManager, bg, &enemyCore01Behavior, pos);
    setSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, Parent, { -128,0 });
}

void setEnemyT(OBJ2DManager* obj2dManager, BG* bg,VECTOR2 pos)
{
    OBJ2D* Parent = setMainEnemy(obj2dManager, bg, &enemyCore01Behavior, pos);
    setSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, Parent, { 0,-429 });
    setSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, Parent, { 0,-229 });
    setSubEnemy(obj2dManager, bg, &enemyBuff01Behavior, Parent, { 0,229 });
    setSubEnemy(obj2dManager, bg, &enemyBuff01Behavior, Parent, { 0,429 });
}

void addEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    OBJ2D* Parent = setMainEnemy(obj2dManager, bg, &enemyCore01Behavior, getCursorPoint2());
    // �T�u�p�[�c
    setSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, Parent, { 0,-229 });
    setSubEnemy(obj2dManager, bg, &enemyBuff01Behavior, Parent, { 0,229 });
}
#if 0
// Turret
void setSubEnemy(OBJ2DManager* obj2dManager, BG* bg, OBJ2D* parent, VECTOR2 pos)
{
    OBJ2D* subEnemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    subEnemy->zOrder_ = 3;
    // �e��ݒ�
    subEnemy->actorComponent_->parent_ = parent;

    obj2dManager->add(subEnemy, &enemyTurret01Behavior, pos);
}
// Buff
void setSubEnemy2(OBJ2DManager* obj2dManager, BG* bg, OBJ2D* parent, VECTOR2 pos)
{
    OBJ2D* subEnemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    subEnemy->zOrder_ = 3;
    // �e��ݒ�
    subEnemy->actorComponent_->parent_ = parent;

    obj2dManager->add(subEnemy, &enemyBuff01Behavior, pos);
}

void setEnemy01(OBJ2DManager* obj2dManager, BG* bg)
{
    const VECTOR2 pos = { 100,500 };

    OBJ2D* enemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    enemy->zOrder_ = 3;
    enemy->actorComponent_->parent_ = enemy;

    obj2dManager->add(enemy, &enemyCore01Behavior, pos);

    // �T�u�p�[�c
    setSubEnemy(obj2dManager, bg, enemy, { pos.x, pos.y - 429 });
    setSubEnemy(obj2dManager, bg, enemy, { pos.x, pos.y - 229 });
    setSubEnemy2(obj2dManager, bg, enemy, { pos.x, pos.y + 229 });
    setSubEnemy2(obj2dManager, bg, enemy, { pos.x, pos.y + 429 });
}

void addEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    const VECTOR2 pos = getCursorPoint2();

    OBJ2D* enemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    enemy->zOrder_ = 3;
    enemy->actorComponent_->parent_ = enemy;

    obj2dManager->add(enemy, &enemyCore01Behavior, pos);

    // �T�u�p�[�c
    setSubEnemy(obj2dManager, bg, enemy, { pos.x, pos.y - 229 });
    setSubEnemy(obj2dManager, bg, enemy, { pos.x, pos.y + 229 });
}
#endif




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

    obj->renderer_->flip(); // ���]������
}

void BaseEnemyBehavior::moveX(OBJ2D* obj) const
{
    // �����ړ�(��)
    obj->transform_->velocity_.x -= getParam()->ACCEL_X;
    
    ActorBehavior::moveX(obj);
}

void BaseEnemyBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
{
    // �v���C���[��HP�����炷
    dst->actorComponent_->hp_ -= getParam()->ATTACK_POWER;
}

bool BaseEnemyBehavior::isAlive(OBJ2D* obj) const
{
    return obj->actorComponent_->hp_ > 0;
}

void BaseEnemyBehavior::damageProc(OBJ2D* /*obj*/) const
{
    // �_���[�W����
    //obj->actorComponent_->damaged();

    // ���G����
    //obj->actorComponent_->muteki();
}

void BaseEnemyBehavior::areaCheck(OBJ2D* obj) const
{
#if 1
    // ���[�ɐi�ނƉE�[����o�Ă���(��)
    if (obj->transform_->position_.x < -obj->collider_->size_.x)
    {
        obj->transform_->position_.x = obj->collider_->size_.x + BG::WINDOW_W;
    }

#else
    if (obj->transform_->position_.x < 0) // ��ʉE�ɍs������
    {
        obj->behavior_ = nullptr; // ����
    }
#endif
}


//******************************************************************************
//
//      EnemyCore01
//
//******************************************************************************
EnemyCore01Behavior::EnemyCore01Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeCore01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -125,-125,125,125 };

    param_.ATTACK_BOX[0] = { -125, -125, 125, 125 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 4.0f;
    param_.ACCEL_Y = 4.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;

    // ����Behavior�Ȃ�
    param_.NEXT_BEHAVIOR = nullptr;
    param_.NEXT_ERASER   = nullptr;

    // �A�j���[�V�����̃p�����[�^
    param_.obj_ANIME = &rotateAnime;
    param_.ROT_SPEED = -0.05f;
}


//******************************************************************************
//
//      Turret
//
//******************************************************************************

// Turret01
EnemyTurret01Behavior::EnemyTurret01Behavior()
{
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = { player_size, player_size };
    param_.HIT_BOX[0] = { -125, 48, 80, 95 };   // �������`
    param_.HIT_BOX[1] = { -10,-95,125,50 };      // �l�W

    param_.ATTACK_BOX[0] = { -125, 48, 80, 95 };   // �������`
    param_.ATTACK_BOX[1] = { -10,-95,125,50 };      // �l�W

    param_.ACCEL_X = 4.0f;
    param_.ACCEL_Y = 4.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    //param_.JUMP_POWER_Y = -12.0f;

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

    // ��X(inline)�֐���������
    {
        const VECTOR2 pos = obj->transform_->position_/* + VECTOR2(0, -120)*/;

        OBJ2D* shot = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg_,
                nullptr,
                nullptr,
                new WeaponComponent
            ),
            &enemyNormalShotBehavior,
            pos
        );
        shot->zOrder_ = 2;
        shot->weaponComponent_->parent_ = obj;
    }

    obj->actorComponent_->attackTimer_ = 120;
}


//******************************************************************************
//
//      Buff
//
//******************************************************************************

// Buff01
EnemyBuff01Behavior::EnemyBuff01Behavior()
{
    param_.ANIME_WAIT = animeBuff01;

    param_.SIZE = { player_size, player_size };
    param_.HIT_BOX[0] = {
        -player_hitBox, -player_hitBox,
         player_hitBox,  player_hitBox,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];


    param_.ACCEL_X = 4.0f;
    param_.ACCEL_Y = 4.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    //param_.JUMP_POWER_Y = -12.0f;

    // ����Behavior�EEraser�i�h���b�v�A�C�e���j
    param_.NEXT_BEHAVIOR = &dropBuff01Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}

//******************************************************************************
//
//      erase�i�����j
//
//******************************************************************************
void EraseEnemy::erase(OBJ2D* obj) const
{
    // �X�P�[����0�ȉ��ɂȂ��������
    if (obj->transform_->scale_.x <= 0)
    {
        obj->behavior_ = nullptr;
        return;
    }

    //OBJ2D* parent = obj->actorComponent_->parent_->actorComponent_->parent_; // �����̂ŏȗ�
    OBJ2D* parent = obj->actorComponent_->parent_; // �����̂ŏȗ�

    // �e�����ł���ƃA�C�e��������
    if (parent && parent->behavior_ == nullptr) // �e�����Ă��̐e�����łɎ���ł���ꍇ
    {
        obj->actorComponent_->parent_ = nullptr; // �e���Z�b�g

        // ����behavior�Eeraser�i�h���b�v�A�C�e���j����
        obj->behavior_ = obj->nextBehavior_;
        obj->eraser_ = obj->nextEraser_;

        obj->renderer_->flip(); // ���]������

        return;
    }

    // HP��0�ȉ��ɂȂ��
    if (!obj->actorComponent_->isAlive())
    {
            // �R�A�łȂ��Ȃ�S�~�A�C�e��������
        if (obj != parent)
        {
            obj->actorComponent_->parent_ = nullptr; // �e���Z�b�g

            // ����behavior�Eeraser�i�h���b�v�A�C�e���j����
            obj->behavior_ = &doropTrash01Behavior;
            obj->eraser_ = &eraseDropParts;;
            return;
        }

        // �R�A�Ȃ���ł���
        obj->behavior_ = nullptr;
        return;
    }
}