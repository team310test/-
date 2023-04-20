//******************************************************************************
//
//
//      �G�l�~�[�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//******************************************************************************
//
//      �G�l�~�[�ړ�����
//
//******************************************************************************

//------< �A�j���f�[�^ >----------------------------------------------
namespace
{   
    //------< �A�j���f�[�^ >------------------------------------------
    //�����
    GameLib::AnimeData animeEnemey_Up[] = {
        { &sprEnemey_test, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // �^���b�g01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //  �R�A01
    GameLib::AnimeData animeCore01[] = {
        { &sprPartsCore01, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //  �S�~01
    GameLib::AnimeData animeTrash01[] = {
        { &sprPartsTrash01, 10 },
        { nullptr, -1 },// �I���t���O
    };
}

void setSubEnemy(BaseEnemyBehavior* behavior, OBJ2D* parent, VECTOR2 pos)
{
    if (behavior->isCore())
    {
        assert(!"core��core���Ăяo���Ă��܂�");
    };

    VECTOR2 POS = { parent->transform_->position_.x + pos.x,parent->transform_->position_.y + pos.y };

    OBJ2D* subEnemy = new OBJ2D(
        new Renderer,
        new Collider,
        Game::instance()->bg(),
        new ActorComponent,
        nullptr,
        nullptr
    );

    subEnemy->zOrder_ = 3;
    // �e��ݒ�
    subEnemy->actorComponent_->parent_ = parent;

    Game::instance()->obj2dManager()->add(subEnemy, behavior, POS);
}

void setEnemy(OBJ2DManager* obj2dManager, BG* bg)
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
}

void BaseEnemyBehavior::moveX(OBJ2D* obj) const
{
    // �����ړ�(��)
    obj->transform_->velocity_.x -= getParam()->ACCEL_X;
    
    ActorBehavior::moveX(obj);
}

void BaseEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    // �v���C���[��HP�����炷
    dst->actorComponent_->hp_ -= getParam()->ATTACK_POWER;
}

bool BaseEnemyBehavior::isAlive(OBJ2D* obj) const
{
    return obj->actorComponent_->hp_ > 0;
}

void BaseEnemyBehavior::damageProc(OBJ2D* obj) const
{
    // �_���[�W����
    //obj->actorComponent_->damaged();

    // ���G����
    //obj->actorComponent_->muteki();
}

void BaseEnemyBehavior::areaCheck(OBJ2D* obj) const
{
    // ���[�ɐi�ނƉE�[����o�Ă���(��)
    //if (obj->transform_->position_.x < -obj->collider_->size_.x)
    //{
    //    obj->transform_->position_.x = obj->collider_->size_.x + BG::WINDOW_W;
    //}
}

//******************************************************************************
//
//      NormalEnemyBehavior
//
//******************************************************************************
NormalEnemyBehavior::NormalEnemyBehavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeEnemey_Up;

    param_.SIZE    = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -player_hitBox, -player_hitBox, player_hitBox, player_hitBox };
    //param_.ATTACK_BOX = { -250 / 2, -250, 250 / 2, 0 };
    param_.HP = 1;

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 1.0f;
    param_.ACCEL_Y = 1.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void NormalEnemyBehavior::moveY(OBJ2D* obj) const
{
    BaseEnemyBehavior::moveY(obj);
}

void NormalEnemyBehavior::attack(OBJ2D* obj) const
{
}

//******************************************************************************
//
//      ItemEnemyBehavior
//
//******************************************************************************
ItemEnemyBehavior::ItemEnemyBehavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeEnemey_Up;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.ATTACK_BOX[0] = { -player_hitBox, -player_hitBox, player_hitBox, player_hitBox };
    param_.HIT_BOX[0] = { -player_hitBox, -player_hitBox, player_hitBox, player_hitBox };
    param_.HP = 1;

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 4.0f;
    param_.ACCEL_Y = 4.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void ItemEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    src->actorComponent_->hp_ = 0;
}

void ItemEnemyBehavior::attack(OBJ2D* obj) const
{
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
    param_.HIT_BOX[0] = { -64,-64,64,64 };

    param_.ATTACK_BOX[0] = { -64, -64, 64, 64 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 4.0f;
    param_.ACCEL_Y = 4.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;

    // �A�j���[�V�����̃p�����[�^
    param_.obj_ANIME = &rotateAnime;
    param_.ROT_SPEED = -0.05f;
}

void EnemyCore01Behavior::init(OBJ2D* obj) const
{
    // �T�u�p�[�c����
    setSubEnemy(&enemyTurret01Behavior, obj, { -64,96 });

    BaseEnemyBehavior::init(obj);
}

//******************************************************************************
//
//      Turret01
//
//******************************************************************************
// �G�l�~�[
EnemyTurret01Behavior::EnemyTurret01Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] =  { -64,-64,64,64 };

    param_.ATTACK_BOX[0] =  { -64,-64,64,64 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 4.0f;
    param_.ACCEL_Y = 4.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;

    // ����Behavior�EEraser
    param_.NEXT_BEHAVIOR = &playerTurret01Behavior;

    // �A�j���[�V�����̃p�����[�^
    param_.obj_ANIME = &scaleAnime;
}

void EnemyTurret01Behavior::attack(OBJ2D* obj) const
{
    obj->actorComponent_->attackTimer_--;

    if (obj->actorComponent_->attackTimer_ >= 0)return;

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
    obj->actorComponent_->attackTimer_ = 180;

}

// �A�C�e��
ItemTurret01Behavior::ItemTurret01Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -64,-64,64,64 };

    param_.ATTACK_BOX[0] = { -64,-64,64,64 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 2.0f;
    param_.ACCEL_Y = 2.0f;
    param_.SPEED_X_MAX = 2.0f;
    param_.SPEED_Y_MAX = 2.0f;
    param_.JUMP_POWER_Y = -12.0f;
}


//******************************************************************************
//      EnemyTrash01
//******************************************************************************
// �A�C�e��
ItemTrash01Behavior::ItemTrash01Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeTrash01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -64,-64,64,64 };

    param_.ATTACK_BOX[0] = { -64,-64,64,64 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 2.0f;
    param_.ACCEL_Y = 2.0f;
    param_.SPEED_X_MAX = 2.0f;
    param_.SPEED_Y_MAX = 2.0f;
    param_.JUMP_POWER_Y = -12.0f;
}


//--------------------------------------------------------------
//  ����
//--------------------------------------------------------------
void EraseEnemy::erase(OBJ2D* obj) const
{
    // �e�����ł���ƃA�C�e��������
    if (obj->actorComponent_->parent_->actorComponent_->parent_ == nullptr)
    {
        obj->actorComponent_->parent_ = nullptr;
        obj->behavior_ = &itemTurret01Behavior;
        obj->actorComponent_->hp_ = 1;
        obj->eraser_ = &eraseItem;

        // ���]������
        obj->renderer_->flip();
    }

    // HP��0�ȉ��ɂȂ��Trash�A�C�e��������
    if (!obj->actorComponent_->isAlive())
    {
        obj->actorComponent_->parent_ = nullptr;
        obj->behavior_ = &itemTrash01Behavior;
        obj->actorComponent_->hp_ = 1;
        obj->eraser_ = &eraseItem;
        // �A�j���[�V������~
        obj->actorComponent_->objAnime_ = nullptr;
        // nextBehavior_�ύX
        obj->actorComponent_->nextBehavior_ = &playerTrash01Behavior;

        // ���]������
        obj->renderer_->flip();
    }

    // ��ʊO�֍s���Ə���
    if (obj->transform_->position_.x < -obj->collider_->size_.x)
    {
        obj->actorComponent_->parent_ = nullptr;
        obj->behavior_ = nullptr;
        return;
    }
}

void EraseItem::erase(OBJ2D* obj) const
{
    if (!obj->actorComponent_->isAlive())
    {
        obj->behavior_ = obj->actorComponent_->nextBehavior_;
        
        obj->eraser_ = &erasePlayer;
        
        obj->actorComponent_->hp_ = obj->behavior_->getParam_HP();

        ++BasePlayerBehavior::plShrinkCount;
    }

    //��ʊO�֍s���� ����
    if (obj->transform_->position_.x < -obj->collider_->size_.x)
    {
        obj->actorComponent_->parent_ = nullptr;
        obj->behavior_ = nullptr;
        return;
    }
}