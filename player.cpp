//******************************************************************************
//
//
//      �v���C���[�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

int BasePlayerBehavior::plShrinkCount = 0;

//******************************************************************************
//
//      �v���C���[�ړ�����
//
//******************************************************************************

//------< �A�j���f�[�^ >----------------------------------------------
namespace
{   // �����̃f�[�^�͒����̂ŁAVisual Studio�̋@�\�ŕ�����悤��namespace�𕪂��Ă���

    //------< �A�j���f�[�^ >------------------------------------------
    // �ҋ@
    GameLib::AnimeData sprPlayer_Wait[] = {
        { &sprEnemey_test, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //  �^���b�g01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
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

void setPlayer(OBJ2DManager* obj2dManager, BG* bg, const bool makeOrgPlayer = false) // true�Ȃ炱��obj��player_�ɑ������
{
    const VECTOR2 pos = { 500,500 };

    OBJ2D* player = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    player->zOrder_ = 3;
    player->actorComponent_->parent_ = player;

    player->actorComponent_->No = ActorComponent::playerNum;

    if (makeOrgPlayer == true) 
    {
        //Game::instance()->player_ = obj2dManager->add(player, &normalPlayerBehavior, pos); 
        Game::instance()->player_ = obj2dManager->add(player, &normalPlayerBehavior, pos);
    }
    else
    {
        //obj2dManager->add(player, &normalPlayerBehavior, pos);
        obj2dManager->add(player, &normalPlayerBehavior, pos);
    }
}

// ��
void setCursor(OBJ2DManager* obj2dManager, BG* bg)
{
    const VECTOR2 pos = { 100,100 };

    OBJ2D* cursor = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    cursor->zOrder_ = 4;
    cursor->actorComponent_->parent_ = cursor;

    Game::instance()->cursor_ = obj2dManager->add(cursor, &cursorBehavior, pos);
}

//******************************************************************************
//
//      BasePlayerBehavior
//
//******************************************************************************

void BasePlayerBehavior::init(OBJ2D* obj) const
{
    obj->collider_->judgeFlag_ = true;
    obj->collider_->isDrawHitRect_ = true;
    obj->collider_->isDrawAttackRect_ = true;

    obj->eraser_ = &erasePlayer;
}

void BasePlayerBehavior::moveX(OBJ2D* obj) const
{
    // ���E���͂̎��o��
    switch (obj->actorComponent_->padState_ & (GameLib::input::PAD_LEFT | GameLib::input::PAD_RIGHT))
    {
    case GameLib::input::PAD_LEFT:  // ��������������Ă���ꍇ
        obj->transform_->velocity_.x -= getParam()->ACCEL_X;
        break;
    case GameLib::input::PAD_RIGHT: // �E������������Ă���ꍇ
        obj->transform_->velocity_.x += getParam()->ACCEL_X;
        break;
    default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
        if (obj->transform_->velocity_.x > 0)
        {
            obj->transform_->velocity_.x -= getParam()->ACCEL_X / 2;
            if (obj->transform_->velocity_.x < 0) obj->transform_->velocity_.x = 0;
        }
        if (obj->transform_->velocity_.x < 0)
        {
            obj->transform_->velocity_.x += getParam()->ACCEL_X / 2;
            if (obj->transform_->velocity_.x > 0) obj->transform_->velocity_.x = 0;
        }
        break;
    }

    ActorBehavior::moveX(obj);
}

void BasePlayerBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    // �G��HP�����炷
    dst->actorComponent_->hp_ -= getParam()->ATTACK_POWER;

    if (!src->actorComponent_->parent_) return; // �����������e�A�܂��͐e�����łȂ����A
    if (dst->actorComponent_->parent_) return;  // ���肪�e�������Ă��Ȃ��ꍇ��continue;
    
    dst->actorComponent_->parent_ = src;        // �e��ۑ�
    
}

bool BasePlayerBehavior::isAlive(OBJ2D*) const
{
    return true;    // �������Ă���i���j
}

void BasePlayerBehavior::damageProc(OBJ2D* obj) const
{
    // ���͏���
    obj->actorComponent_->padTrg_ = GameLib::input::TRG(0);
    obj->actorComponent_->padState_ = GameLib::input::STATE(0);

    // �_���[�W����
    obj->actorComponent_->damaged();

    // ���G����
    obj->actorComponent_->muteki();

    //if (GameLib::input::STATE(0) & GameLib::input::PAD_TRG2)
    //if (obj->actorComponent_->parent_->behavior_ != nullptr)
    //{
    //    GameLib::debug::setString("No:%d��[%d]", obj->actorComponent_->No,
    //        obj->actorComponent_->parent_->actorComponent_->No);
    //}
    //else
    //{
    //    GameLib::debug::setString("No:%d��[�~]", obj->actorComponent_->No);
    //}
}

void BasePlayerBehavior::areaCheck(OBJ2D* obj) const
{
    //// ��
    //if (obj->transform_->position_.x < obj->collider_->size_.x)
    //{
    //    obj->transform_->position_.x = obj->collider_->size_.x;
    //}
    //if (obj->transform_->position_.x > BG::WINDOW_W - obj->collider_->size_.x)
    //{
    //    obj->transform_->position_.x = BG::WINDOW_W - obj->collider_->size_.x;
    //}

    //if (obj->transform_->position_.y < obj->collider_->size_.y)
    //{
    //    obj->transform_->position_.y = obj->collider_->size_.y;
    //}
    //if (obj->transform_->position_.y > BG::WINDOW_H - obj->collider_->size_.y)
    //{
    //    obj->transform_->position_.y = BG::WINDOW_H - obj->collider_->size_.y;
    //}
}

//******************************************************************************
//
//      NormalPlayerBehavior
//
//******************************************************************************

NormalPlayerBehavior::NormalPlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animeCore01;

    param_.SIZE    = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -player_hitBox, -player_hitBox, player_hitBox, player_hitBox };
    //param_.HIT_BOX = { -50, -175, 50, -75 };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    param_.JUMP_POWER_Y = -12.0f;

    param_.HP = 30;

    // �A�j���[�V�����̃p�����[�^
    param_.obj_ANIME = &rotateAnime;
    param_.ROT_SPEED = 0.05f;
}

void NormalPlayerBehavior::moveY(OBJ2D* obj) const
{
    // ���E���͂̎��o��
    switch (obj->actorComponent_->padState_ & (GameLib::input::PAD_UP | GameLib::input::PAD_DOWN))
    {
    case GameLib::input::PAD_UP:  // �ゾ����������Ă���ꍇ
        obj->transform_->velocity_.y -= getParam()->ACCEL_Y;
        break;
    case GameLib::input::PAD_DOWN: // ��������������Ă���ꍇ
        obj->transform_->velocity_.y += getParam()->ACCEL_Y;
        obj->renderer_->animeData_ = obj->renderer_->animeData_;
        break;
    default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
        if (obj->transform_->velocity_.y > 0)
        {
            obj->transform_->velocity_.y -= getParam()->ACCEL_Y / 2;
            if (obj->transform_->velocity_.y < 0) obj->transform_->velocity_.y = 0;
        }
        if (obj->transform_->velocity_.y < 0)
        {
            obj->transform_->velocity_.y += getParam()->ACCEL_Y / 2;
            if (obj->transform_->velocity_.y > 0) obj->transform_->velocity_.y = 0;
        }
        break;
    }

    BasePlayerBehavior::moveY(obj);
}

void NormalPlayerBehavior::attack(OBJ2D* obj) const
{
    obj->actorComponent_->attackTimer_--;

    if (obj->actorComponent_->padTrg_ & GameLib::input::PAD_TRG3 &&
        obj->actorComponent_->attackTimer_ <= 0)
    {
        const VECTOR2 pos = obj->transform_->position_/* + VECTOR2(0, -120)*/;

        OBJ2D* shuriken = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer, 
                new Collider, 
                obj->bg_, 
                nullptr, 
                nullptr, 
                new WeaponComponent
            ), 
            &playerNormalShotBehavior, 
            pos
        );
        shuriken->zOrder_ = 2;
        shuriken->weaponComponent_->parent_ = obj;
        obj->actorComponent_->attackTimer_ = 10;
    }
}


//******************************************************************************
//
//      ItemPlayerBehavior
//
//******************************************************************************
ItemPlayerBehavior::ItemPlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = sprPlayer_Wait;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -player_hitBox, -player_hitBox, player_hitBox, player_hitBox };
    //param_.HIT_BOX = { -50, -175, 50, -75 };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void ItemPlayerBehavior::moveY(OBJ2D* obj) const
{
    // ���E���͂̎��o��
    switch (obj->actorComponent_->padState_ & (GameLib::input::PAD_UP | GameLib::input::PAD_DOWN))
    {
    case GameLib::input::PAD_UP:  // �ゾ����������Ă���ꍇ
        obj->transform_->velocity_.y -= getParam()->ACCEL_Y;
        break;
    case GameLib::input::PAD_DOWN: // ��������������Ă���ꍇ
        obj->transform_->velocity_.y += getParam()->ACCEL_Y;
        obj->renderer_->animeData_ = obj->renderer_->animeData_;
        break;
    default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
        if (obj->transform_->velocity_.y > 0)
        {
            obj->transform_->velocity_.y -= getParam()->ACCEL_Y / 2;
            if (obj->transform_->velocity_.y < 0) obj->transform_->velocity_.y = 0;
        }
        if (obj->transform_->velocity_.y < 0)
        {
            obj->transform_->velocity_.y += getParam()->ACCEL_Y / 2;
            if (obj->transform_->velocity_.y > 0) obj->transform_->velocity_.y = 0;
        }
        break;
    }

    BasePlayerBehavior::moveY(obj);
}

void ItemPlayerBehavior::attack(OBJ2D* obj) const
{
    obj->actorComponent_->attackTimer_--;

    if (obj->actorComponent_->padTrg_ & GameLib::input::PAD_TRG3 &&
        obj->actorComponent_->attackTimer_ <= 0)
    {
        const VECTOR2 pos = obj->transform_->position_/* + VECTOR2(0, -120)*/;
        OBJ2D* shuriken = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg_,
                nullptr,
                nullptr,
                new WeaponComponent
            ),
            &playerNormalShotBehavior,
            pos
        );
        shuriken->zOrder_ = 2;
        shuriken->weaponComponent_->parent_ = obj;
        obj->actorComponent_->attackTimer_ = 10;
    }
}

// �p�[�c�̏k���֐�
void ItemPlayerBehavior::shrink(OBJ2D* obj) const
{
    Behavior::shrink(obj);  // �k������
    contact(obj);           // �k���ɔ����Ĉʒu���ړ������鏈��
}

// �ڐG����֐�
void ItemPlayerBehavior::contact(OBJ2D* obj) const
{
    if (!obj->collider_->isShrink_) return; // �k�����Ă��Ȃ����return

    // �I���W�i�����@�̕��ֈړ����鏈��
    contactToOriginal(obj, Game::instance()->player_); 

    OBJ2D* parent = obj->actorComponent_->parent_;              // �����̐e�̃f�[�^
    if (parent->collider_->hitCheck(obj->collider_)) return;    // �e�ƐڐG���Ă����return

    // �e�̕��ֈړ����鏈��
    contactToParent(obj, parent); // (�e�Ƃ������Ă��Ȃ�obj���I���W�i�����@�Ɍ������ē˂�����ł����̂��y��)
}

// �I���W�i�����@�̕��ֈړ�(�I���W�i�����@�֌����������ɉe��)
//static const float defaultVelocity = 0.1f; // ���ɂȂ鑬�x
static const float defaultVelocity = 0.085f; // ���ɂȂ鑬�x
void ItemPlayerBehavior::contactToOriginal(OBJ2D* obj, OBJ2D* original) const
{    
    const VECTOR2 orginalPos = original->transform_->position_; // ���@�{�̂̈ʒu
    const VECTOR2 objPos     = obj->transform_->position_;      // obj�̈ʒu

    const VECTOR2 d  = { orginalPos - objPos };              // obj���玩�@�{�̂֌������x�N�g��
    const float dist = sqrtf( (d.x * d.x) + (d.y * d.y) );   // obj���玩�@�{�̂܂ł̋���
                                                             
    float addVelocity = 0.0f;                                // obj��velocity�ɑ������x
    float num = 0.0f;                                        // for����i�݂����Ȗ���

    while (1)
    {
        // obj���玩�@�{�̂܂ł̋����ɂ���đ��x���㏸������
        // (���������������obj�����@�{�̂ɒǂ����Ȃ�����)
        if ((dist >=  50.0f * num && dist <=  50.0f * (num + 1.0f)) ||  // �}0����}50�A�}50����}100�A�}100����}150...
            (dist <= -50.0f * num && dist >= -50.0f * (num + 1.0f)))
        {
            addVelocity = (num != 0) ? defaultVelocity * num : 0.1f;    // �}0����}50�܂ł̋�����num��0�Ȃ̂�0.1f����
            break; // ��������̂�break;
        }

        ++num; // num�����Z���Ă���
    }

    obj->transform_->velocity_ = {
        (d.x / dist) * (addVelocity/* / obj->transform_->scale_.x*/), // scale���������Ȃ������ɑ��x�������Ȃ��悤scale�Ŋ���
        (d.y / dist) * (addVelocity/* / obj->transform_->scale_.y*/)
    };

    BasePlayerBehavior::moveY(obj);
    ActorBehavior::moveX(obj);

    //obj->collider_->calcHitBox(getParam()->HIT_BOX);
    //obj->collider_->calcAttackBox(getParam()->ATTACK_BOX);
}

// �e�̕��ֈړ�
//static const float parentVelocity = 0.9f; // �������x(�e�֌����������ɉe��)
static const float parentVelocity = 0.75f; // �������x(�e�֌����������ɉe��)
void ItemPlayerBehavior::contactToParent(OBJ2D* obj, OBJ2D* parent) const
{    
    const VECTOR2 parentPos = parent->transform_->position_;    // �e�̈ʒu
    const VECTOR2 objPos    = obj->transform_->position_;       // obj�̈ʒu

    const VECTOR2 d  = { parentPos - objPos };               // obj����e�֌������x�N�g��
    const float dist = sqrtf( (d.x * d.x) + (d.y * d.y) );   // obj����e�܂ł̋���

    obj->transform_->velocity_ = {
        (d.x / dist) * (parentVelocity),
        (d.y / dist) * (parentVelocity)
    };

    BasePlayerBehavior::moveY(obj);
    ActorBehavior::moveX(obj);

    //obj->collider_->calcHitBox(getParam()->HIT_BOX);
    //obj->collider_->calcAttackBox(getParam()->ATTACK_BOX);
}

//******************************************************************************
//      Turret01
//******************************************************************************
PlayerTurret01Behavior::PlayerTurret01Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -64,-64,64,64 };

    param_.ATTACK_BOX[0] = { -64,-64,64,64 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

//******************************************************************************
//       PlayerTrash01
//******************************************************************************
PlayerTrash01Behavior::PlayerTrash01Behavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT = animeTrash01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -64,-64,64,64 };

    param_.ATTACK_BOX[0] = { -64,-64,64,64 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

//--------------------------------------------------------------
//  ����
//--------------------------------------------------------------

// �e�T��(�i�V���Ɖ�ꂽ���̑u����������)
#define USE_FIND_PARENT
void ErasePlayer::erase(OBJ2D* obj) const
{
    // HP��0�ȉ��ɂȂ�����
    if (!obj->actorComponent_->isAlive())
    {
        obj->behavior_ = nullptr;
    }

    if (obj->actorComponent_->parent_->behavior_) return;   // ���������̐e�����݂���Ȃ�return

#ifdef USE_FIND_PARENT
    // �V�����e��T��
    for (auto& dst : *Game::instance()->obj2dManager()->getList())
    {
        if (!dst->behavior_) continue;                      // ���肪���݂��Ȃ����continue;
        if (obj == dst) continue;                           // ���肪�����Ȃ�continue;
        if (!dst->actorComponent_) continue;                // ���肪actorComponent�������Ă��Ȃ����continue;
        if (!dst->actorComponent_->parent_) continue;       // ���肪�e�������Ă��Ȃ����continue;
        if (obj == dst->actorComponent_->parent_) continue; // ���肪�����̎q�Ȃ�continue;

        if (!obj->collider_->hitCheck(dst->collider_)) continue; // ���肪�ڐG���Ă��Ȃ����continue;

        obj->actorComponent_->parent_ = dst;                // �����e�ɂ���

        return;                                             // �e���������Ă���̂�return
    }
#endif

    // �e��������Ȃ������ꍇ
    obj->actorComponent_->parent_ = nullptr; // �e�������Z�b�g
    obj->behavior_ = nullptr;                // ����������
}

// �J�[�\��(��)
CursorBehavior::CursorBehavior()
{
    param_.SIZE = VECTOR2( 5, 5);
    param_.HIT_BOX[0] = { -5, -5, 5 , 5 };
    param_.ATTACK_BOX[0] = { -5, -5, 5 , 5 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

// �J�[�\���̍��W�擾
VECTOR2 getCursorPoint()
{
    static POINT point_;

    GetCursorPos(&point_);
    ScreenToClient(GetActiveWindow(), &point_);

    VECTOR2 pos = { static_cast<float>(point_.x), static_cast<float>(point_.y) };
    return pos;
}

void CursorBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    if ( (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4) ||
         (GetAsyncKeyState(VK_LBUTTON) & 1) )
    {
        dst->behavior_ = nullptr;
    }
}

void CursorBehavior::damageProc(OBJ2D* obj) const
{
    obj->transform_->position_ = getCursorPoint();
}
