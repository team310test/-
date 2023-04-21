#include "all.h"


int BasePlayerBehavior::plShrinkCount_ = 0;

// �A�j���f�[�^
namespace
{
    // �ҋ@
    GameLib::AnimeData animePlayerCore01[] = {
        { &sprPlayerCore01, 10 },
        { nullptr, -1 },// �I���t���O
    };

    //  �^���b�g01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
        { nullptr, -1 },// �I���t���O
    };    
    
    //  �o�t01
    GameLib::AnimeData animeBuff01[] = {
        { &sprPartsBuff01, 10 },
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
        Game::instance()->player_ = obj2dManager->add(player, &corePlayerBehavior, pos);
    }
    else
    {
        //obj2dManager->add(player, &normalPlayerBehavior, pos);
        obj2dManager->add(player, &corePlayerBehavior, pos);
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
//      BasePlayerBehavior�i�v���C���[�̃x�[�X�j
//
//******************************************************************************
void BasePlayerBehavior::init(OBJ2D* obj) const
{
    obj->collider_->judgeFlag_ = true;
    obj->collider_->isDrawHitRect_ = true;
    obj->collider_->isDrawAttackRect_ = true;

    obj->eraser_ = &erasePlayer;
}

void BasePlayerBehavior::moveY(OBJ2D* obj) const
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

    ActorBehavior::moveY(obj);
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

void BasePlayerBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
{
    // �G��HP�����炷
    dst->actorComponent_->hp_ -= getParam()->ATTACK_POWER;

    //if (!src->actorComponent_->parent_) return; // �����������e�A�܂��͐e�����łȂ����A
    //if (dst->actorComponent_->parent_) return;  // ���肪�e�������Ă��Ȃ��ꍇ��continue;
    //
    //dst->actorComponent_->parent_ = src;        // �e��ۑ�   
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

void BasePlayerBehavior::areaCheck(OBJ2D* /*obj*/) const
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
//      corePlayerBehavior�i���@�{�́j
//
//******************************************************************************
CorePlayerBehavior::CorePlayerBehavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animePlayerCore01;

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
}

void CorePlayerBehavior::attack(OBJ2D* obj) const
{
    // �v���C���[���w��iterator���擾����
    //auto objList = Game::instance()->obj2dManager()->getList();
    //std::list<OBJ2D*>::iterator iter = objList->begin();
    //for (; iter != objList->end(); ++iter)
    //{
    //    if ((*iter)->behavior_ == nullptr) { continue; }
    //    if ((*iter)->behavior_->getType() == OBJ_TYPE::PLAYER) 
    //    {
    //        break; 
    //    }
    //}

    // �U���N�[���^�C������
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �w��{�^����������Ă��Ȃ��A�܂��͍U���N�[���^�C�����I����Ă��Ȃ����return
    if ( !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) ||
           obj->actorComponent_->attackTimer_ > 0) return; 

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
            &plNormalShotBehavior,     // �m�[�}��
            //&plSineWaveShotBehavior,   // �����g
            //&plSquareWaveShotBehavior, // ��`�g
            //&plCurveWaveShotBehavior,  // ��J�[�u
            //&plPenetrateShotBehavior,  // �����E�ђ�(�\��)
            pos
        );
        shot->zOrder_ = 2;
        shot->weaponComponent_->parent_ = obj;

    }

    obj->actorComponent_->attackTimer_ = 30;

}


//******************************************************************************
//
//      partsPlayerBehavior(�p�[�c�̃x�[�X)
//
//******************************************************************************
// �p�[�c�̏k���֐�
void PartsPlayerBehavior::shrink(OBJ2D* obj) const
{
    Behavior::shrink(obj);  // �k������
    contact(obj);           // �k���ɔ����Ĉʒu���ړ������鏈��
}

// �ڐG����֐�
void PartsPlayerBehavior::contact(OBJ2D* obj) const 
{
    if (!obj->collider_->isShrink_) return; // �k�����Ă��Ȃ����return

    // �I���W�i�����@�̕��ֈړ����鏈��
    contactToOriginal(obj, Game::instance()->player_); 
    

    // contactToOriginal�֐���obj�Ǝ��@�{�̂̋����ɍ��킹��
    // ���x�����ł���悤�ɂȂ��Ă����̂ŕK�v�Ȃ�����
    // if (obj->actorComponent_->parent_->behavior_ == nullptr) return;        // �k�����ɐe�������Ă���ꍇreturn
    // if (obj->collider_->hitCheck(obj->actorComponent_->parent_)) return;    // �e�ƐڐG���Ă����return
    //
    // �e�̕��ֈړ����鏈��
    // contactToParent(obj, obj->actorComponent_->parent_); // (�e�Ƃ������Ă��Ȃ�obj���I���W�i�����@�Ɍ������ē˂�����ł����̂��y��)
}

// �I���W�i�����@�̕��Ɍ������Ĉړ�����֐�
//static const float toCoreVelocity = 0.085f; // ���ɂȂ鑬�x(�I���W�i�����@�֌����������ɉe��)
static const float toCoreVelocity = 0.14f; // ���ɂȂ鑬�x(�I���W�i�����@�֌����������ɉe��)
void PartsPlayerBehavior::contactToOriginal(OBJ2D* obj, OBJ2D* original) const
{    
    const VECTOR2 orginalPos = original->transform_->position_; // ���@�{�̂̈ʒu
    const VECTOR2 objPos     = obj->transform_->position_;      // obj�̈ʒu

    const VECTOR2 d  = { orginalPos - objPos };              // obj���玩�@�{�̂֌������x�N�g��
    const float dist = sqrtf( (d.x * d.x) + (d.y * d.y) );   // obj���玩�@�{�̂܂ł̋���
                                                             
    float addVelocity = 0.0f;                                // obj��velocity�ɑ������x
    float num = 0.0f;                                        // for����i�݂����Ȗ���
    const float copyDist = dist > 0 ? dist : -dist;          //
    while (true)
    {
        if (num > 999) // �I�_
        {
            addVelocity = toCoreVelocity * num;
            break;
        }

        // obj���玩�@�{�̂܂ł̋����������Ȃ�����x���㏸������
        // (���������������obj�����@�{�̂ɒǂ����Ȃ�����)
        if ((copyDist >=  (50.0f * num) && copyDist <=  50.0f * (num + 1.0f)))  // �}0����}50�A�}50����}100�A�}100����}150...
        {
            addVelocity = (num != 0.0f) ? (toCoreVelocity * num ): toCoreVelocity; // �}0����}50�܂ł̋�����num��0�Ȃ̂Ńf�t�H���g�̒l����

            break; // ��������̂�break;
        }

        ++num; // num�����Z���Ă���
    }

    obj->transform_->velocity_ = {
        (d.x / dist) * (addVelocity),
        (d.y / dist) * (addVelocity),
    };

    ActorBehavior::moveY(obj);
    ActorBehavior::moveX(obj);
}

// �e�̕��Ɍ������Ĉړ�����֐�
//static const float toParentVelocity = 0.5f; // �������x(�e�֌����������ɉe��)
//void PartsPlayerBehavior::contactToParent(OBJ2D* obj, OBJ2D* parent) const
//{    
//    const VECTOR2 parentPos = parent->transform_->position_;    // �e�̈ʒu
//    const VECTOR2 objPos    = obj->transform_->position_;       // obj�̈ʒu
//
//    const VECTOR2 d  = { parentPos - objPos };               // obj����e�֌������x�N�g��
//    const float dist = sqrtf( (d.x * d.x) + (d.y * d.y) );   // obj����e�܂ł̋���
//
//    obj->transform_->velocity_ = {
//        (d.x / dist) * (toParentVelocity),
//        (d.y / dist) * (toParentVelocity)
//    };
//
//    ActorBehavior::moveY(obj);
//    ActorBehavior::moveX(obj);
//
//    //obj->collider_->calcHitBox(getParam()->HIT_BOX);
//    //obj->collider_->calcAttackBox(getParam()->ATTACK_BOX);
//}



//******************************************************************************
// 
//      Turret�i�U���C��p�[�c�j
// 
//******************************************************************************

// Turret01
PlayerTurret01Behavior::PlayerTurret01Behavior()
{
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -80, 48, 125, 95 };    // �������`
    param_.HIT_BOX[1] = { -125,-95,10,50 };      // �l�W

    param_.ATTACK_BOX[0] = { -80, 48, 125, 95 }; // �������`
    param_.ATTACK_BOX[1] = { -125,-95,10,50 };   // �l�W

    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    //param_.JUMP_POWER_Y = -12.0f;

}

void PlayerTurret01Behavior::attack(OBJ2D* obj) const
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
            &plNormalShotBehavior,
            pos
        );
        shot->zOrder_ = 2;
        shot->weaponComponent_->parent_ = obj;
    }

    obj->actorComponent_->attackTimer_ = 30;

}


//******************************************************************************
// 
//      Buff�i�o�t�p�[�c�j
// 
//******************************************************************************

//Buff01
static constexpr int BUFF_MALTIPLY_VALUE = 2; // ATTACK_BOX�ɂ�����l�i�o�t�̉e���͈͂��ς��j
PlayerBuff01Behavior::PlayerBuff01Behavior()
{
    param_.ANIME_WAIT = animeBuff01;

    param_.SIZE = { player_size, player_size };
    param_.HIT_BOX[0] = { 
        -player_hitBox, -player_hitBox, 
         player_hitBox,  player_hitBox,
    };
    param_.ATTACK_BOX[0] = { 
        -player_hitBox * BUFF_MALTIPLY_VALUE, 
        -player_hitBox * BUFF_MALTIPLY_VALUE,
         player_hitBox * BUFF_MALTIPLY_VALUE,  
         player_hitBox * BUFF_MALTIPLY_VALUE,
    };

    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
}                            

// �U���^�C�v��PLAYER�Ȃ̂�dst�͖���(�v���C���[)�ɂȂ�
void PlayerBuff01Behavior::hit(OBJ2D*, OBJ2D* dst) const
{
    dst->actorComponent_->attackTimer_ += -1; // �U���N�[���^�C���������i�e���㏸�j
}


//******************************************************************************
// 
//      erase�i�����j
// 
//******************************************************************************
// �e�T��(�i�V���Ɖ�ꂽ���̑u����������)
#define USE_FIND_PARENT

void ErasePlayer::erase(OBJ2D* obj) const
{
    if (obj->actorComponent_->parent_->behavior_) return;   // ���������̐e�����݂���Ȃ�return

#ifdef USE_FIND_PARENT
    // �V�����e��T��
    for (auto& dst : *Game::instance()->obj2dManager()->getList())
    {
        if (!dst->behavior_) continue;                      // ���肪���݂��Ȃ����continue;
        if (obj == dst) continue;                           // ���肪�����Ȃ�continue;

        if (dst->behavior_->getType() != OBJ_TYPE::PLAYER) continue; // ���肪�����Ɠ����v���C���[�łȂ����continue

        if (!dst->actorComponent_->parent_) continue;       // ���肪�e�������Ă��Ȃ����continue;
        if (obj == dst->actorComponent_->parent_) continue; // ���肪�����̎q�Ȃ�continue;

        if (!obj->collider_->hitCheck(dst->collider_)) continue; // ���肪�ڐG���Ă��Ȃ����continue;

        obj->actorComponent_->parent_ = dst;                // �����e�ɂ���

        return; // �e���������Ă���̂�return
    }
#endif

    // �e��������Ȃ������ꍇ
    obj->actorComponent_->parent_ = nullptr; // �e�������Z�b�g
    obj->behavior_ = nullptr;                // ����������
    BasePlayerBehavior::plShrinkCount_ = std::max(0, BasePlayerBehavior::plShrinkCount_ - 1);
    return;
}
#undef USE_FIND_PARENT


//******************************************************************************
// 
//      CusorBehavior�i�J�[�\���j�i���j
// 
//****************************************************************************** 
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

    VECTOR2 pos = { static_cast<float>(point_.x), 
                    static_cast<float>(point_.y) 
    };
    return pos;
}

void CursorBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
{
    if ( (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4) ||
         (GetAsyncKeyState(VK_LBUTTON) & 1) )
    {
        dst->behavior_ = nullptr;
        BasePlayerBehavior::plShrinkCount_ = std::max(0, BasePlayerBehavior::plShrinkCount_ - 1);
    }
}

void CursorBehavior::damageProc(OBJ2D* obj) const
{
    obj->transform_->position_ = getCursorPoint();
}