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
    player->update_ = PLAYER_CORE_UPDATE;

    if (makeOrgPlayer == true) 
    {
        Game::instance()->player_ = obj2dManager->add(player, &playerCoreBehavior, pos);
    }
    else
    {
        obj2dManager->add(player, &playerCoreBehavior, pos);
    }
}
//// ��
//void setCursor(OBJ2DManager* obj2dManager, BG* bg)
//{
//    const VECTOR2 pos = { 100,100 };
//
//    OBJ2D* cursor = new OBJ2D(
//        new Renderer,
//        new Collider,
//        bg,
//        new ActorComponent,
//        nullptr,
//        nullptr
//    );
//
//    cursor->zOrder_ = 4;
//    cursor->actorComponent_->parent_ = cursor;
//
//    Game::instance()->cursor_ = obj2dManager->add(cursor, &cursorBehavior, pos);
//}


//******************************************************************************
//      �v���C���[��update
//******************************************************************************
#define RATIO       (0.7f)
#define PAD_MOVE    (PAD_RIGHT|PAD_LEFT|PAD_DOWN|PAD_UP)

VECTOR2 speedData[16] = {
    { 0, 0 },								        //----
    { 0, -PL_SPEED },						        //---u
    { 0,  PL_SPEED },						        //--d-
    { 0, 0 },								        //--du
    { -PL_SPEED, 0 },						        //-l--
    { -PL_SPEED * RATIO, -PL_SPEED * RATIO },		//-l-u
    { -PL_SPEED * RATIO,  PL_SPEED * RATIO },		//-ld-
    { -PL_SPEED, 0 },						        //-ldu
    { PL_SPEED, 0 },						        //r---
    { PL_SPEED * RATIO, -PL_SPEED * RATIO },		//r--u
    { PL_SPEED * RATIO,  PL_SPEED * RATIO },		//r-d-
    { PL_SPEED, 0 },						        //r-du
    { 0, 0 },								        //rl--
    { 0, -PL_SPEED },						        //rl-u
    { 0,  PL_SPEED },						        //rld-
    { 0, 0 },								        //rldu
};

// ���@�{�̂�update
void PLAYER_CORE_UPDATE(OBJ2D* obj)
{
    using namespace GameLib::input;
    ActorComponent* a = obj->actorComponent_;
    Transform*      t = obj->transform_;

    t->velocity_ += speedData[a->padState_ & PAD_MOVE];

    // y���̌���
    if ( !(a->padState_ & (PAD_DOWN | PAD_UP)) )
    {
        if (t->velocity_.y > 0)
        {
            t->velocity_.y -= PL_SPEED / 2;
            if (t->velocity_.y < 0) t->velocity_.y = 0;
        }
        if (t->velocity_.y < 0)
        {
            t->velocity_.y += PL_SPEED / 2;
            if (t->velocity_.y > 0) t->velocity_.y = 0;
        }
    }

    // x���̌���
    if ( !(a->padState_ & (PAD_RIGHT | PAD_LEFT)) )
    {
        if (t->velocity_.x > 0)
        {
            t->velocity_.x -= PL_SPEED / 2;
            if (t->velocity_.x < 0) t->velocity_.x = 0;
        }
        if (t->velocity_.x < 0)
        {
            t->velocity_.x += PL_SPEED / 2;
            if (t->velocity_.x > 0) t->velocity_.x = 0;
        }
    }

    // �ő呬�x�`�F�b�N
    t->velocity_.x = clamp(t->velocity_.x, -PL_SPEED_MAX, PL_SPEED_MAX);
    t->velocity_.y = clamp(t->velocity_.y, -PL_SPEED_MAX, PL_SPEED_MAX);
}

// �p�[�c��update
void PLAYER_PATRS_UPDATE(OBJ2D* obj)
{
    Transform* t       = obj->transform_;
    Transform* parent = Game::instance()->player_->transform_;

    t->velocity_ = parent->velocity_;
}



//******************************************************************************
//
//      BasePlayerBehavior�i�v���C���[�̃x�[�X�j
//
//******************************************************************************
void BasePlayerBehavior::init(OBJ2D* obj) const
{
    obj->collider_->judgeFlag_         = true;
    obj->collider_->isDrawHitRect_     = true;
    obj->collider_->isDrawAttackRect_  = true;

    obj->eraser_ = &erasePlayer;
}

// BasePlayerBehavior::moveY(moveX)�O�̂��ߎc���Ă���

//void BasePlayerBehavior::moveY(OBJ2D* obj) const
//{
//    // �ȗ�
//    using namespace GameLib::input;
//    ActorComponent* a = obj->actorComponent_;
//    Transform* t = obj->transform_;
//
//
//    // �΂߈ړ����̑��x���C��
//    const float fixSpeedY = (a->padState_ & PAD_LEFT || a->padState_ & PAD_RIGHT) &&
//                            (a->padState_ & PAD_DOWN || a->padState_ & PAD_UP)
//                            ? 0.71f : 1.0f;
//    const float  fixedAccelY = param_.ACCEL_Y * fixSpeedY;
//
//    // �㉺���͂̎��o��
//    switch (a->padState_ & (PAD_UP | PAD_DOWN))
//    {
//    case PAD_UP:    // �ゾ����������Ă���ꍇ
//        t->velocity_.y -= fixedAccelY;
//        break;
//    case PAD_DOWN:  // ��������������Ă���ꍇ
//        t->velocity_.y += fixedAccelY;
//        //obj->renderer_->animeData_ = obj->renderer_->animeData_;
//        break;
//    default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
//        if (t->velocity_.y > 0)
//        {
//            t->velocity_.y -= getParam()->ACCEL_Y / 2;
//            if (t->velocity_.y < 0) t->velocity_.y = 0;
//        }
//        if (t->velocity_.y < 0)
//        {
//            t->velocity_.y += getParam()->ACCEL_Y / 2;
//            if (t->velocity_.y > 0) t->velocity_.y = 0;
//        }
//        break;
//    }
//
//    ActorBehavior::moveY(obj);
//}
//
//void BasePlayerBehavior::moveX(OBJ2D* obj) const
//{
//    // �ȗ�
//    using namespace GameLib::input;
//    ActorComponent* a = obj->actorComponent_;
//    Transform*      t = obj->transform_;
//
//
//    // �΂߈ړ����̑��x���C��
//    const float fixSpeedX = (a->padState_ & PAD_LEFT || a->padState_ & PAD_RIGHT) &&
//                            (a->padState_ & PAD_DOWN || a->padState_ & PAD_UP   ) 
//                            ? 0.71f : 1.0f;
//    const float fixedAccelX = param_.ACCEL_X * fixSpeedX;
//
//    // ���E���͂̎��o��
//    switch (a->padState_ & (PAD_LEFT | PAD_RIGHT))
//    {
//    case PAD_LEFT:  // ��������������Ă���ꍇ
//        t->velocity_.x -= fixedAccelX;
//        break;
//    case PAD_RIGHT: // �E������������Ă���ꍇ
//        t->velocity_.x += fixedAccelX;
//        break;
//    default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
//        if (t->velocity_.x > 0)
//        {
//            t->velocity_.x -= getParam()->ACCEL_X / 2;
//            if (t->velocity_.x < 0) t->velocity_.x = 0;
//        }
//        if (t->velocity_.x < 0)
//        {
//            t->velocity_.x += getParam()->ACCEL_X / 2;
//            if (t->velocity_.x > 0) t->velocity_.x = 0;
//        }
//        break;
//    }
//
//    ActorBehavior::moveX(obj);
//}

void BasePlayerBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
{
    // �G��HP�����炷
    dst->actorComponent_->hp_ -= getParam()->ATTACK_POWER;

}

void BasePlayerBehavior::damageProc(OBJ2D* obj) const
{
    ActorComponent* a = obj->actorComponent_;

    // ���͏���
    a->padTrg_   = GameLib::input::TRG(0);
    a->padState_ = GameLib::input::STATE(0);

    // �_���[�W����
    //obj->actorComponent_->damaged();

    // ���G����
    //obj->actorComponent_->muteki();

    // �_�ł�����
    if (a->damageTimer_ > 0)
    {
        VECTOR4 color = obj->renderer_->color_;
        color.w = a->damageTimer_ & 0x02 ? 1.0f : 0.2f;
        obj->renderer_->color_ = color;

        --a->damageTimer_;
        if (a->damageTimer_ <= 0) obj->renderer_->color_ = { 1,1,1,1 };
    }

    if (!obj->actorComponent_->isQuake_) return;

    // �h�炷
    static Quake quake;
    quake.quakeDamage(obj);
}

void BasePlayerBehavior::areaCheck(OBJ2D* /*obj*/) const
{
}

//******************************************************************************
//
//      PlayerCoreBehavior�i���@�{�́j
//
//******************************************************************************
PlayerCoreBehavior::PlayerCoreBehavior()
{
    // �A�j���[�V����
    param_.ANIME_WAIT    = animePlayerCore01;

    param_.SIZE    = VECTOR2(PARTS_OBJ_SIZE, PARTS_OBJ_SIZE);

    param_.HIT_BOX[0]    = { -PL_CORE_HITBOX, -PL_CORE_HITBOX, PL_CORE_HITBOX,  PL_CORE_HITBOX };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP = PL_CORE_HP;

    // �A�j���p�f�[�^
    param_.OBJ_ANIME = scaleAnime;
}

void PlayerCoreBehavior::attack(OBJ2D* obj) const
{
    // �U���N�[���^�C������
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �w��{�^����������Ă��Ȃ��A�܂��͍U���N�[���^�C�����I����Ă��Ȃ����return
    if ( !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) ||
           obj->actorComponent_->attackTimer_ > 0) return; 

    // �e��ǉ�
    AddObj::addShot(obj, &plNormalShotBehavior, obj->transform_->position_);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = 30;

}

void PlayerCoreBehavior::areaCheck(OBJ2D* obj) const
{
    Transform* t = obj->transform_;
    Collider*  c = obj->collider_;

    const float leftLimit   =                (c->size_.x * 0.5f) * t->scale_.x;
    const float rightLimit  = BG::WINDOW_W - (c->size_.x * 0.5f) * t->scale_.x;
    const float topLimit    =                (c->size_.y * 0.5f) * t->scale_.y;
    const float bottomLimit = BG::WINDOW_H - (c->size_.y * 0.5f) * t->scale_.y;

    if (t->position_.x >= rightLimit)
    {
        t->position_.x += rightLimit - t->position_.x;
        if (t->velocity_.x > 0) t->velocity_.x = 0;
    }
    if (t->position_.x <= leftLimit)
    {
        t->position_.x += leftLimit - t->position_.x;
        if (t->velocity_.x < 0) t->velocity_.x = 0;
    }
    if (t->position_.y >= bottomLimit)
    {
        t->position_.y += bottomLimit - t->position_.y;
        if (t->velocity_.y > 0) t->velocity_.y = 0;
    }
    if (t->position_.y <= topLimit)
    {
        t->position_.y += topLimit - t->position_.y;
        if (t->velocity_.y < 0) t->velocity_.y = 0;
    }
}


//******************************************************************************
//
//      partsPlayerBehavior(�p�[�c�̃x�[�X)
//
//******************************************************************************
// �p�[�c�̏k���֐�
void PlayerPartsBehavior::shrink(OBJ2D* obj) const
{
    Behavior::shrink(obj);  // �k������
    contactToPlCore(obj, Game::instance()->player_); // �k���ɔ����Ĉʒu���ړ������鏈��
}

// �I���W�i�����@�̕��Ɍ������Ĉړ�����֐�
//static const float toCoreVelocity = 0.085f; // ���ɂȂ鑬�x(�I���W�i�����@�֌����������ɉe��)
float PlayerPartsBehavior::toCoreVelocity_ = TO_CORE_SPEED;  // �I���W�i�����@�֌��������x
void PlayerPartsBehavior::contactToPlCore(OBJ2D* obj, OBJ2D* orgPl) const
{    
    if (!obj->collider_->isShrink_) return; // �k�����Ă��Ȃ����return

    const VECTOR2 orgPlPos = orgPl->transform_->position_;  // ���@�{�̂̈ʒu
    const VECTOR2 objPos     = obj->transform_->position_;  // obj�̈ʒu

    const VECTOR2 d  = { orgPlPos - objPos };               // obj���玩�@�{�̂֌������x�N�g��
    const float dist = sqrtf( (d.x * d.x) + (d.y * d.y) );  // obj���玩�@�{�̂܂ł̋���
                                                             
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
        if ((copyDist >=  (50.0f * num) && copyDist <=  50.0f * (num + 1.0f)))  // �}0����}50�A�}50����}100�A�}100����}150...
        {
            addVelocity = (num != 0.0f) ? (toCoreVelocity_ * num ): toCoreVelocity_; // �}0����}50�܂ł̋�����num��0�Ȃ̂Ńf�t�H���g�̒l����

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
//      Turret�i�U���C��p�[�c�j
// 
//******************************************************************************

// Turret01
PlayerTurret01Behavior::PlayerTurret01Behavior()
{
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = VECTOR2(PARTS_OBJ_SIZE, PARTS_OBJ_SIZE);

    // �摜�T�C�Y(128*64�̔���)
    param_.HIT_BOX[0] = { -64, -32, 64, 32 };   // �����`
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];   // �����`

}

void PlayerTurret01Behavior::attack(OBJ2D* obj) const
{
    // �U���N�[���^�C������
    // �i�o���o���ɑł����邽�߂Ɏw��{�^���������Ă���Ƃ��������炷�j
    if (obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3 && 
        obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �w��{�^����������Ă��Ȃ��A�܂��͍U���N�[���^�C�����I����Ă��Ȃ����return
    if (!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) ||
        obj->actorComponent_->attackTimer_ > 0) return;

    // �e��ǉ�
    AddObj::addShot(obj, &plNormalShotBehavior, obj->transform_->position_);

    setXAxisScaleAnime(obj);
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

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0] = { 
        -64, -64, 
         64,  64,
    };
    param_.ATTACK_BOX[0] = { 
        -64 * BUFF_MALTIPLY_VALUE, 
        -64 * BUFF_MALTIPLY_VALUE,
         64 * BUFF_MALTIPLY_VALUE,  
         64 * BUFF_MALTIPLY_VALUE,
    };

}                            

// �U���^�C�v��PLAYER�Ȃ̂�dst�͖���(�v���C���[)�ɂȂ�
void PlayerBuff01Behavior::hit(OBJ2D*, OBJ2D* dst) const
{
    dst->actorComponent_->attackTimer_ += -1; // �U���N�[���^�C���������i�e���㏸�j
}


//******************************************************************************
// 
//      Trash(�S�~�p�[�c)
// 
//******************************************************************************
PlayerTrash01Behavior::PlayerTrash01Behavior()
{
    param_.ANIME_WAIT = animeTrash01;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0] = { -64, -64, 64, 64 };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

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
    // HP��0�ȉ��ɂȂ�����
    if (!obj->actorComponent_->isAlive())
    {
        // �����G�t�F�N�g
        AddObj::addEffect(obj, &efcBombBehavior);

        obj->actorComponent_->parent_ = nullptr; // �e�������Z�b�g
        obj->behavior_ = nullptr;

        // �k���J�E���g����
        BasePlayerBehavior::plShrinkCount_ = std::max(0, BasePlayerBehavior::plShrinkCount_ - 1);

        return;
    }

    if (obj->actorComponent_->parent_->behavior_) return;   // �����̐e�����݂���Ȃ�return


    // �V�����e��T��
#ifdef USE_FIND_PARENT
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

    // �����G�t�F�N�g
    AddObj::addEffect(obj, &efcBombBehavior);

    // �e��������Ȃ������ꍇ
    obj->actorComponent_->parent_ = nullptr; // �e�������Z�b�g
    obj->behavior_ = nullptr;                // ����������

    // �k���J�E���g����
    BasePlayerBehavior::plShrinkCount_ = std::max(0, BasePlayerBehavior::plShrinkCount_ - 1);

    return;
}
#undef USE_FIND_PARENT


//******************************************************************************
// 
//      CusorBehavior�i�J�[�\���j�i���j
// 
//****************************************************************************** 
//CursorBehavior::CursorBehavior()
//{
//    param_.SIZE = VECTOR2( 5, 5);
//    param_.HIT_BOX[0] = { -5, -5, 5 , 5 };
//    param_.ATTACK_BOX[0] = { -5, -5, 5 , 5 };
//
//}

// �J�[�\���̍��W�擾
//VECTOR2 getCursorPoint()
//{
//    static POINT point_;
//
//    GetCursorPos(&point_);
//    ScreenToClient(GetActiveWindow(), &point_);
//
//    VECTOR2 pos = { static_cast<float>(point_.x), 
//                    static_cast<float>(point_.y) 
//    };
//    return pos;
//}
//
//void CursorBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
//{
    //if ( (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4) ||
    //     (GetAsyncKeyState(VK_LBUTTON) & 1) )
    //{
    //    dst->behavior_ = nullptr;

    //    // �k���J�E���g����
    //    BasePlayerBehavior::plShrinkCount_ = std::max(0, BasePlayerBehavior::plShrinkCount_ - 1);
    //}
//}

//void CursorBehavior::damageProc(OBJ2D* obj) const
//{
//    obj->transform_->position_ = getCursorPoint();
//}