//******************************************************************************
//
//
//      �v���C���[�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//******************************************************************************
//
//      �v���C���[�ړ�����
//
//******************************************************************************

//------< �v���C���[�̃A�j���f�[�^(��) >----------------------------------------------
namespace
{   // �����̃f�[�^�͒����̂ŁAVisual Studio�̋@�\�ŕ�����悤��namespace�𕪂��Ă���

    //------< �v���C���[�̃A�j���f�[�^ >------------------------------------------
    //�����
    GameLib::AnimeData animePlayer_Up[] = {
        { &sprPlayer_Up0, 10 },
        { &sprPlayer_Up1, 10 },
        { &sprPlayer_Up2, 10 },
        { &sprPlayer_Up1, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //�E����
    GameLib::AnimeData animePlayer_Right[] = {
        { &sprPlayer_Right0, 10 },
        { &sprPlayer_Right1, 10 },
        { &sprPlayer_Right2, 10 },
        { &sprPlayer_Right1, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //������
    GameLib::AnimeData animePlayer_Down[] = {
        { &sprPlayer_Down0, 10 },
        { &sprPlayer_Down1, 10 },
        { &sprPlayer_Down2, 10 },
        { &sprPlayer_Down1, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //������
    GameLib::AnimeData animePlayer_Left[] = {
        { &sprPlayer_Left0, 10 },
        { &sprPlayer_Left1, 10 },
        { &sprPlayer_Left2, 10 },
        { &sprPlayer_Left1, 10 },
        { nullptr, -1 },// �I���t���O
    };
}

void setPlayer(OBJ2DManager* obj2dManager, BG* bg) 
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

    obj2dManager->add(player, &normalPlayerBehavior, pos);
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
        obj->renderer_->animeData_ = getParam()->ANIME_LEFT;
        obj->actorComponent_->xFlip_ = true;
        break;
    case GameLib::input::PAD_RIGHT: // �E������������Ă���ꍇ
        obj->transform_->velocity_.x += getParam()->ACCEL_X;
        obj->renderer_->animeData_ = getParam()->ANIME_RIGHT;
        obj->actorComponent_->xFlip_ = false;
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
}

void BasePlayerBehavior::areaCheck(OBJ2D* obj) const
{
    // ��
    if (obj->transform_->position_.x < obj->collider_->size_.x)
    {
        obj->transform_->position_.x = obj->collider_->size_.x;
    }
    if (obj->transform_->position_.x > BG::WINDOW_W - obj->collider_->size_.x)
    {
        obj->transform_->position_.x = BG::WINDOW_W - obj->collider_->size_.x;
    }

    if (obj->transform_->position_.y < obj->collider_->size_.y)
    {
        obj->transform_->position_.y = obj->collider_->size_.y;
    }
    if (obj->transform_->position_.y > BG::WINDOW_H)
    {
        obj->transform_->position_.y = BG::WINDOW_H;
    }
}

//******************************************************************************
//
//      NormalPlayerBehavior
//
//******************************************************************************

NormalPlayerBehavior::NormalPlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_UP = animePlayer_Up;
    param_.ANIME_RIGHT = animePlayer_Right;
    param_.ANIME_DOWN = animePlayer_Down;
    param_.ANIME_LEFT = animePlayer_Left;

    param_.SIZE = VECTOR2(48 / 2, 128 - 16);
    param_.HIT_BOX = { -48, -128, 48, 0 };
    param_.ATTACK_BOX = { -48, -128, 48, 0 };

    // ���x�֘A�̃p�����[�^
    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    param_.JUMP_POWER_Y = -12.0f;
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
    // �v���C���[���w��iterator���擾����
    auto objList = Game::instance()->obj2dManager()->getList();
    std::list<OBJ2D*>::iterator iter = objList->begin();
    for (; iter != objList->end(); ++iter)
    {
        if ((*iter)->behavior_ == nullptr) { continue; }
        if ((*iter)->behavior_->getType() == OBJ_TYPE::PLAYER) 
        {
            break; 
        }
    }

    obj->actorComponent_->attackTimer_--;

    if (obj->actorComponent_->padTrg_ & GameLib::input::PAD_TRG3 &&
        obj->actorComponent_->attackTimer_ <= 0)
    {
        const VECTOR2 pos = obj->transform_->position_ + VECTOR2(0, -48);
        OBJ2D* shuriken = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer, 
                new Collider, 
                obj->bg_, 
                nullptr, 
                nullptr, 
                new WeaponComponent
            ), 
            &shurikenBehavior, 
            pos
        );
        shuriken->zOrder_ = 2;
        shuriken->weaponComponent_->parent_ = obj;
        obj->actorComponent_->attackTimer_ = 10;
    }

    if (obj->actorComponent_->padTrg_ & GameLib::input::PAD_TRG2 &&
        obj->actorComponent_->attackTimer_ <= 0)
    {
        const VECTOR2 pos = obj->transform_->position_ + VECTOR2(0, -48);
        OBJ2D* sword = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer, 
                new Collider, 
                obj->bg_, 
                nullptr, 
                nullptr, 
                new WeaponComponent
            ), 
            &swordBehavior, 
            pos
        );
        sword->zOrder_ = 2;
        sword->weaponComponent_->parent_ = obj;
        obj->actorComponent_->attackTimer_ = 15;
    }
}

//--------------------------------------------------------------
//  ����
//--------------------------------------------------------------
void ErasePlayer::erase(OBJ2D* obj) const
{
    // �����T���v��
    //if (obj->transform_->position_.y > BG::HEIGHT + obj->collider_->size_.y)
    //{
    //    Game::instance()->setGameOver();
    //    obj->behavior_ = nullptr;
    //}
}
