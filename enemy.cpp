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

//------< �v���C���[�̃A�j���f�[�^(��) >----------------------------------------------
namespace
{   
    //------< �v���C���[�̃A�j���f�[�^ >------------------------------------------
    //�����
    GameLib::AnimeData animeEnemey_Up[] = {
        { &sprEnemey_test, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //�E����
    GameLib::AnimeData animeEnemey_Right[] = {
        { &sprEnemey_test, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //������
    GameLib::AnimeData animeEnemey_Down[] = {
    { &sprEnemey_test, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //������
    GameLib::AnimeData animeEnemey_Left[] = {
        { &sprEnemey_test, 10 },
        { nullptr, -1 },// �I���t���O
    };

    //parts01
    GameLib::AnimeData animeParts01[] = {
        { &sprParts01, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// �I���t���O
    };
}

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

    obj2dManager->add(subEnemy, &parts01EnemyBehavior, pos);
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

    obj2dManager->add(enemy, &normalEnemyBehavior, pos);

    // �T�u�p�[�c
    setSubEnemy(obj2dManager, bg, enemy, { pos.x,pos.y-229 });
    setSubEnemy(obj2dManager, bg, enemy, { pos.x,pos.y+229 });
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

    obj2dManager->add(enemy, &normalEnemyBehavior, pos);

    // �T�u�p�[�c
    setSubEnemy(obj2dManager, bg, enemy, { pos.x,pos.y - 229 });
    setSubEnemy(obj2dManager, bg, enemy, { pos.x,pos.y + 229 });
}

//******************************************************************************
//
//      BaseEnemyBehavior
//
//******************************************************************************
void BaseEnemyBehavior::init(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = getParam()->ANIME_LEFT;

    obj->collider_->judgeFlag_ = true;
    obj->collider_->isDrawHitRect_ = true;
    obj->collider_->isDrawAttackRect_ = true;

    //TODO 01 eraser
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
    if (obj->transform_->position_.x < -obj->collider_->size_.x)
    {
        obj->transform_->position_.x = obj->collider_->size_.x + BG::WINDOW_W;
    }
}

//******************************************************************************
//
//      NormalEnemyBehavior
//
//******************************************************************************
NormalEnemyBehavior::NormalEnemyBehavior()
{
    // �A�j���[�V����
    param_.ANIME_UP = animeEnemey_Up;
    param_.ANIME_RIGHT = animeEnemey_Right;
    param_.ANIME_DOWN = animeEnemey_Down;
    param_.ANIME_LEFT = animeEnemey_Left;

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
    param_.ANIME_UP = animeEnemey_Up;
    param_.ANIME_RIGHT = animeEnemey_Right;
    param_.ANIME_DOWN = animeEnemey_Down;
    param_.ANIME_LEFT = animeEnemey_Left;

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

//--------------------------------------------------------------
//  ����
//--------------------------------------------------------------
void EraseEnemy::erase(OBJ2D* obj) const
{
    // �e�����ł���ƃA�C�e��������
    if (obj->actorComponent_->parent_->actorComponent_->parent_ == nullptr)
    {
        obj->actorComponent_->parent_ = nullptr;
        obj->behavior_ = &parts01ItemBehavior;
        obj->actorComponent_->hp_ = 1;
        obj->eraser_ = &eraseItem;
    }

    // HP��0�ȉ��ɂȂ�Ə���
    if (!obj->actorComponent_->isAlive())
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
        obj->behavior_ = &parts01PlayerBehavior;
        obj->eraser_ = &erasePlayer;
        ++BasePlayerBehavior::plShrinkCount;
    }

    //if (obj->transform_->position_.x < 0)
    //{
    //    obj->behavior_ = nullptr;
    //}
}

// <parts01Enemey(Lzi��)>
Parts01EnemyBehavior::Parts01EnemyBehavior()
{
    // �A�j���[�V����
    param_.ANIME_UP = animeParts01;
    param_.ANIME_RIGHT = animeParts01;
    param_.ANIME_DOWN = animeParts01;
    param_.ANIME_LEFT = animeParts01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -206, 50, 130, 155 };   // �������`
    param_.HIT_BOX[1] = { -20,-154,206,50 };      // �l�W
    //param_.HIT_BOX = { -50, -175, 50, -75 };

    param_.ATTACK_BOX[0] = { -206, 50, 130, 155 };// �������`
    param_.ATTACK_BOX[1] = { -20,-154,206,50 };   // �l�W;

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 4.0f;
    param_.ACCEL_Y = 4.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

// <parts01Item(Lzi��)>
Parts01ItemBehavior::Parts01ItemBehavior()
{
    // �A�j���[�V����
    param_.ANIME_UP = animeParts01;
    param_.ANIME_RIGHT = animeParts01;
    param_.ANIME_DOWN = animeParts01;
    param_.ANIME_LEFT = animeParts01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -206, 50, 130, 155 };   // �������`
    param_.HIT_BOX[1] = { -20,-154,206,50 };      // �l�W
    //param_.HIT_BOX = { -50, -175, 50, -75 };

    param_.ATTACK_BOX[0] = { -206, 50, 130, 155 };// �������`
    param_.ATTACK_BOX[1] = { -20,-154,206,50 };   // �l�W;

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 2.0f;
    param_.ACCEL_Y = 2.0f;
    param_.SPEED_X_MAX = 2.0f;
    param_.SPEED_Y_MAX = 2.0f;
    param_.JUMP_POWER_Y = -12.0f;
}