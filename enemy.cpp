#include "all.h"

// �A�j���f�[�^
namespace
{   
    //  �R�A01
    GameLib::AnimeData animeCore01[] = {
        { &sprEnemyCore01, 10 },
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

    param_.SIZE = VECTOR2(PARTS_OBJ_SIZE, PARTS_OBJ_SIZE);

    param_.HIT_BOX[0]    = { -64, -64, 64, 64 };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ����Behavior�Ȃ�
    param_.NEXT_BEHAVIOR = nullptr;
    param_.NEXT_ERASER   = nullptr;

    // �A�j���[�V�����̃p�����[�^
    param_.OBJ_ANIME = &rotateAnime;
    param_.ROT_SPEED = -0.05f;
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
    const VECTOR2 objPos = obj->transform_->position_;  // obj�̈ʒu

    const VECTOR2 d = { coreEnmPos - objPos };               // obj���玩�@�{�̂֌������x�N�g��
    const float dist = sqrtf((d.x * d.x) + (d.y * d.y));  // obj���玩�@�{�̂܂ł̋���

    float addVelocity = 0.0f;                               // obj��velocity�ɑ������x
    float num = 0.0f;                                       // for����i�݂����Ȗ���
    const float copyDist = dist >= 0 ? dist : dist * (-1);

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

// Turret01
EnemyTurret01Behavior::EnemyTurret01Behavior()
{
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

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

    // �e��ǉ�
    AddObj::addShot(obj, &enmAimShotBehavior, obj->transform_->position_);

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

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0] = {
        -PL_CORE_HITBOX, -PL_CORE_HITBOX,
         PL_CORE_HITBOX,  PL_CORE_HITBOX,
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
    // parent���ȗ�����Ɛ���ɓ��삵�Ȃ��̂œP�p
    //OBJ2D* parent    = obj->actorComponent_->parent_;
    //OBJ2D* orgParent = obj->actorComponent_->orgParent_;

    ActorComponent* a = obj->actorComponent_;


    // �X�P�[�������ȉ��ɂȂ��������
    if (obj->transform_->scale_.x <= UPDATE_OBJ_SCALE_MIN_LIMIT)
    {
        a->parent_      = nullptr; // �e�����Z�b�g
        a->orgParent_   = nullptr; // ���̐e�����Z�b�g
        obj->behavior_  = nullptr; // ����������

        // �����G�t�F�N�g
        AddObj::addEffect(obj, &efcBombBehavior);

        return;
    }


    // �e�������Ă��āA�������e�ł͂Ȃ��A�e�����ł���ƃA�C�e��������
    if (a->parent_ && obj != a->parent_ && a->parent_->behavior_ == nullptr)
    {
        a->parent_      = nullptr; // �e�����Z�b�g
        a->orgParent_   = nullptr; // ���̐e�����Z�b�g

        // ����behavior�Eeraser�i�h���b�v�A�C�e���j����
        obj->behavior_ = obj->nextBehavior_;
        obj->eraser_   = obj->nextEraser_;

        // �����G�t�F�N�g
        AddObj::addEffect(obj, &efcBombBehavior);

        if (obj->behavior_ == nullptr) return;

        obj->update_ = DROP_PARTS_UPDATE;  // update��ύX

        a->hp_ = 0;             // HP��0�ɂ���
        obj->renderer_->flip(); // ���]������

        return;
    }


    // HP��0�ȉ��ɂȂ��
    if (!a->isAlive())
    {
        a->parent_ = nullptr; // �e�����Z�b�g

        // �����G�t�F�N�g
        AddObj::addEffect(obj, &efcBombBehavior);


        // �������R�A�łȂ��Ȃ�S�~�A�C�e��������
        if (obj != a->orgParent_)
        {
            a->orgParent_ = nullptr; // ���̐e�����Z�b�g

            // ����behavior�Eeraser�i�h���b�v���݃A�C�e���j����
            obj->behavior_ = &dropTrash01Behavior;
            obj->eraser_   = &eraseDropParts;         
            obj->update_   = DROP_PARTS_UPDATE;  // update��ύX

            return;
        }

        a->orgParent_ = nullptr; // ���̐e�����Z�b�g

        // �R�A�Ȃ̂ŏ��ł���
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