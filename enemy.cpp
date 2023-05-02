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

    obj->renderer_->flip(); // ���]������
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
#if 0
    // ���[�ɐi�ނƉE�[����o�Ă���(��)
    if (obj->transform_->position_.x < -obj->collider_->size_.x)
    {
        //obj->behavior_ = nullptr; // ��ʊO�ɍs���������
    }

#else

    const VECTOR2* size = &obj->collider_->size_;
    const VECTOR2* pos = &obj->transform_->position_;
    const float margin = 600.0f;

    const float leftLimit = size->x - margin;
    const float rightLimit = BG::WINDOW_W + size->x + margin;
    const float topLimit = size->y - margin;
    const float bottomLimit = BG::WINDOW_H + size->y + margin;

    if (pos->x < leftLimit ||
        pos->x > rightLimit ||
        pos->y < topLimit ||
        pos->y > bottomLimit)
    {
        obj->actorComponent_->hp_ = 0;              // ��ʊO�ɍs���������(�̗͂�0�ɂ���)
        obj->actorComponent_->parent_ = nullptr;    
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

    // ����Behavior�Ȃ�
    param_.NEXT_BEHAVIOR = nullptr;
    param_.NEXT_ERASER   = nullptr;

    // �A�j���[�V�����̃p�����[�^
    param_.OBJ_ANIME = &rotateAnime;
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

    // �摜�T�C�Y(128*64�̔���)
    param_.HIT_BOX[0] = { -64, -32, 64, 32 };    // �������`    
    //param_.HIT_BOX[1] = { -10,-95,125,50 };      // �l�W

    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];   // �������`
    //param_.ATTACK_BOX[1] = param_.HIT_BOX[1];      // �l�W

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
                new WeaponComponent,
                nullptr
            ),
            &enmAimShotBehavior,
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
        obj->actorComponent_->parent_ = nullptr; // �e�������Z�b�g
        obj->behavior_ = nullptr;
        return;
    }

    OBJ2D* parent = obj->actorComponent_->parent_; // �����̂ŏȗ�

    // �e�����݂��Ă��āA�e�������łȂ��A�e�����ł��邩�e�̗̑͂�0�ɂȂ�ƃA�C�e��������
    if (parent && (parent->behavior_ == nullptr || !parent->actorComponent_->isAlive()) )
    {
        obj->actorComponent_->parent_ = nullptr; // �e���Z�b�g
        obj->actorComponent_->orgParent_ = nullptr; // ���̐e�����Z�b�g

        // ����behavior�Eeraser�i�h���b�v�A�C�e���j����
        obj->behavior_ = obj->nextBehavior_;
        obj->eraser_   = obj->nextEraser_;

        if (obj->behavior_ == nullptr) return;
        obj->update_ = PARTS_UPDATE;  // update��ύX

        obj->actorComponent_->hp_ = 0;  // HP��0�ɂ���

        obj->renderer_->flip(); // ���]������

        return;
    }

    // HP��0�ȉ��ɂȂ��
    if (!obj->actorComponent_->isAlive())
    {
        obj->actorComponent_->parent_ = nullptr; // �e�������Z�b�g

        // �������R�A�łȂ��Ȃ�S�~�A�C�e��������
        if (obj != parent)
        {
            // ����behavior�Eeraser�i�h���b�v�A�C�e���j����
            obj->behavior_ = &dropTrash01Behavior;
            obj->eraser_   = &eraseDropParts;
            
            if (obj->behavior_ == nullptr) return;
            obj->update_ = PARTS_UPDATE;  // update��ύX

            return;
        }

        // �R�A�Ȃ���ł���
        obj->behavior_ = nullptr;
        return;
    }

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
    default:break;
    }
}
// �p�[�c�̃A�b�v�f�[�g
void ENEMY_PARTS(OBJ2D* obj)
{
    Transform* t = obj->transform_;
    Transform* parent = obj->actorComponent_->orgParent_->transform_;

    t->velocity_ = parent->velocity_;
}