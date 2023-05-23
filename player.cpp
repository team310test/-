#include "all.h"


int BasePlayerBehavior::plShrinkCount_      = 0;
int BasePlayerBehavior::plShrinkCountMax_   = 0;

int BasePlayerBehavior::plPartsCurrentCount_ = 0;

// �A�j���f�[�^
namespace
{
    // �ҋ@
    GameLib::AnimeData animePLayerCore[] = {
        { &sprPlayerCore01, 10 },
        { nullptr, -1 },// �I���t���O
    };

    // �^���b�g01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
        //{ &sprPlayer_test, 10 },
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

    // �^���b�g03
    GameLib::AnimeData animeTurret03[] = {
        { &sprPartsTurret03, 10 },
        //{ &sprPlayer_test, 10 },
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

    //  �S�~01
    GameLib::AnimeData animeTrash01[] = {
        { &sprPartsTrash01, 10 },
        { nullptr, -1 },// �I���t���O
    };    
    //  �S�~02
    GameLib::AnimeData animeTrash02[] = {
        { &sprPartsTrash02, 10 },
        { nullptr, -1 },// �I���t���O
    };     
    //  �S�~02
    GameLib::AnimeData animeTrash03[] = {
        { &sprPartsTrash03, 10 },
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

void setPlayer(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos, bool isDrawShrink, const bool makeOrgPlayer = false)
// true�Ȃ炱��obj��player_�ɑ������
{
    //const VECTOR2 pos = { 500,500 };

    OBJ2D* player = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr,
        new PerformComponent
    );

    player->zOrder_ = 3;
    player->actorComponent_->parent_ = player;

    player->transform_->position_ = pos;
    player->renderer_->isDrawShrink_ = isDrawShrink;

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

    // �R���g���[���[����
    {
        t->velocity_.x += PL_SPEED * GameLib::input::getPadState(0)->leftX;
        t->velocity_.y -= PL_SPEED * GameLib::input::getPadState(0)->leftY;
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
// �^�C�g���p��update
void TITLE_PLAYER_UPDATE(OBJ2D* obj)
{
    using namespace GameLib::input;
    //ActorComponent* a = obj->actorComponent_;
    Transform* t        = obj->transform_;
    const float floor   = 890.0f;
    static bool isBound = false;

    t->velocity_ += {0.1f, 2.5f};

    // ������
    if (t->position_.y >= floor)
    {
        // ���ߏC��
        if (t->position_.y > floor) t->position_.y = floor;

        // �o�E���h
        t->velocity_.y = -t->velocity_.y * 0.4f;

        // �o�E���h�͂����ȉ��ɂȂ�����
        if (t->velocity_.y >= -10)
        {
            t->velocity_ = { 0.0f,0.0f };
            obj->performComponent_->isTrigger = true;
        }
    }
}
// �Q�[��(�I�[�o�[)�p��update
void GAME_OVER_PLAYER_UPDATE(OBJ2D* obj)
{
    Transform* t = obj->transform_;

    t->velocity_ += {GAME_OVER_SPEED_X, GAME_OVER_SPEED_Y};
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
    }

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
    param_.ANIME_WAIT    = animePLayerCore;

    param_.SIZE          = { PARTS_OBJ_SIZE * 0.5f, PARTS_OBJ_SIZE * 0.5f };
    param_.SCALE         = { 2.0f,2.0f };

    param_.HIT_BOX[0]    = { -PL_CORE_HITBOX, -PL_CORE_HITBOX, PL_CORE_HITBOX,  PL_CORE_HITBOX };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = PL_CORE_HP;
    param_.ATTACK_POWER  = PL_CORE_ATK;

    // �A�j���p�f�[�^
    param_.OBJ_ANIME = scaleAnime;
}

void PlayerCoreBehavior::attack(OBJ2D* obj) const
{
    // �̗͂�0�Ȃ�return
    if (!obj->actorComponent_->isAlive()) return;

    if (Game::instance()->isGameClear()) return;

    // �U���N�[���^�C������
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �w��{�^��(Space,A,B,X,Y)��������Ă��Ȃ��A�܂��͍U���N�[���^�C�����I����Ă��Ȃ����return
    if ( (!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
           obj->actorComponent_->attackTimer_ > 0) return; 

    // �e��ǉ�
    AddObj::addShot(obj, &plNormalShotBehavior, obj->transform_->position_);

    // �e����SE�Đ�
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_CORE_ATK_TIME;

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
    param_.ANIME_WAIT    = animeTurret01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = { 
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f, 
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };   
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_TURRET01_ATK;
}

void PlayerTurret01Behavior::attack(OBJ2D* obj) const
{
    if (Game::instance()->isGameClear()) return;

    // �U���N�[���^�C������
    // �i�o���o���ɑł����邽�߂Ɏw��{�^��(Space,A,B,X,Y)�������Ă���Ƃ��������炷�j
    if ( (obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1 ||
          obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2 ||
          obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3 ||
          obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4) &&
          obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;
    
        // �w��{�^��(Space,A,B,X,Y)��������Ă��Ȃ��A�܂��͍U���N�[���^�C�����I����Ă��Ȃ����return
    if ( (!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
            obj->actorComponent_->attackTimer_ > 0) return;

    // �e��ǉ�
    AddObj::addShot(obj, &plNormalShotBehavior, obj->transform_->position_);

    // �e����SE�Đ�
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_PARTS_ATK_TIME;

}

// Turret01(���])
PlayerTurret01FlipBehavior::PlayerTurret01FlipBehavior()
{
    param_.ANIME_WAIT = animeTurret01Flip;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER = PL_TURRET01_ATK;
}

void PlayerTurret01FlipBehavior::attack(OBJ2D* obj) const
{
    if (Game::instance()->isGameClear()) return;

    // �U���N�[���^�C������
    // �i�o���o���ɑł����邽�߂Ɏw��{�^��(Space,A,B,X,Y)�������Ă���Ƃ��������炷�j
    if ((obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4) &&
        obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �w��{�^��(Space,A,B,X,Y)��������Ă��Ȃ��A�܂��͍U���N�[���^�C�����I����Ă��Ȃ����return
    if ((!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
        obj->actorComponent_->attackTimer_ > 0) return;

    // �e��ǉ�
    AddObj::addShot(obj, &plNormalShotBehavior, obj->transform_->position_);

    // �e����SE�Đ�
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_PARTS_ATK_TIME;

}

// Turret02(CurveShot)
PlayerTurret02Behavior::PlayerTurret02Behavior()
{
    param_.ANIME_WAIT = animeTurret02;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ROTATION = ToRadian(-ENM_TURRET02_ANGLE);

    param_.ATTACK_POWER = PL_TURRET03_ATK;
}

void PlayerTurret02Behavior::attack(OBJ2D* obj) const
{
    if (Game::instance()->isGameClear()) return;

    // �U���N�[���^�C������
    // �i�o���o���ɑł����邽�߂Ɏw��{�^��(Space,A,B,X,Y)�������Ă���Ƃ��������炷�j
    if ((obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4) &&
        obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �w��{�^��(Space,A,B,X,Y)��������Ă��Ȃ��A�܂��͍U���N�[���^�C�����I����Ă��Ȃ����return
    if ((!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
        obj->actorComponent_->attackTimer_ > 0) return;

    // �e��ǉ�
    const float radius = obj->collider_->size_.x * 0.5f;
    const float angle = obj->transform_->rotation_;
    VECTOR2 pos = obj->transform_->position_;
    pos.x += cosf(angle) * radius;
    pos.y += sinf(angle) * radius;

    AddObj::addShot(obj, &plCurveShotBehavior, pos);

    // �e����SE�Đ�
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_PARTS_ATK_TIME;

}

// Turret02Flip
PlayerTurret02FlipBehavior::PlayerTurret02FlipBehavior()
{
    param_.ANIME_WAIT = animeTurret02Flip;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ROTATION = ToRadian(ENM_TURRET02_ANGLE);

    param_.ATTACK_POWER = PL_TURRET03_ATK;
}

void PlayerTurret02FlipBehavior::attack(OBJ2D* obj) const
{
    if (Game::instance()->isGameClear()) return;

    // �U���N�[���^�C������
    // �i�o���o���ɑł����邽�߂Ɏw��{�^��(Space,A,B,X,Y)�������Ă���Ƃ��������炷�j
    if ((obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4) &&
        obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �w��{�^��(Space,A,B,X,Y)��������Ă��Ȃ��A�܂��͍U���N�[���^�C�����I����Ă��Ȃ����return
    if ((!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
        obj->actorComponent_->attackTimer_ > 0) return;

    // �e��ǉ�
    const float radius = obj->collider_->size_.x * 0.5f;
    const float angle = obj->transform_->rotation_;
    VECTOR2 pos = obj->transform_->position_;
    pos.x += cosf(angle) * radius;
    pos.y += sinf(angle) * radius;

    AddObj::addShot(obj, &plCurveShotFlipBehavior, pos);

    // �e����SE�Đ�
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_PARTS_ATK_TIME;

}

// Turret03(�ђʒe�j
PlayerTurret03Behavior::PlayerTurret03Behavior()
{
    param_.ANIME_WAIT = animeTurret03;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER = PL_TURRET03_ATK;
}

void PlayerTurret03Behavior::attack(OBJ2D* obj) const
{
    if (Game::instance()->isGameClear()) return;

    // �U���N�[���^�C������
    // �i�o���o���ɑł����邽�߂Ɏw��{�^��(Space,A,B,X,Y)�������Ă���Ƃ��������炷�j
    if ((obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4) &&
        obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // �w��{�^��(Space,A,B,X,Y)��������Ă��Ȃ��A�܂��͍U���N�[���^�C�����I����Ă��Ȃ����return
    if ((!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
        obj->actorComponent_->attackTimer_ > 0) return;

    // �e��ǉ�
    AddObj::addShot(obj, &plPenetrateShotBehavior, obj->transform_->position_);

    // �e����SE�Đ�
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_PARTS_ATK_TIME;

}


//******************************************************************************
// 
//      Shield�i�h��p�[�c�j
// 
//******************************************************************************

// Shield01
PlayerShield01Behavior::PlayerShield01Behavior()
{
    param_.ANIME_WAIT    = animeShield01;
                         
    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
                         
    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.25f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.25f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_SHIELD01_ATK;
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
    param_.ANIME_WAIT    = animeBuff01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = { 
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = { 
        -PARTS_OBJ_SIZE * 0.6f, 
        -PARTS_OBJ_SIZE * 0.6f,
         PARTS_OBJ_SIZE * 0.6f,  
         PARTS_OBJ_SIZE * 0.6f,
    };

    param_.ATTACK_POWER  = PL_BUFF01_ATK;
}                            

// �U���^�C�v��PLAYER�Ȃ̂�dst�͖���(�v���C���[)�ɂȂ�(����ɑ̓�����_���[�W���^�����Ȃ�)
void PlayerBuff01Behavior::hit(OBJ2D*, OBJ2D* dst) const
{
    // �U���N�[���^�C���������i�e���㏸�j
    dst->actorComponent_->attackTimer_ -= BUFF_SUB_ATK_TIMER; 
}


//******************************************************************************
// 
//      Trash(�S�~�p�[�c)
// 
//******************************************************************************

// Trash01
PlayerTrash01Behavior::PlayerTrash01Behavior()
{
    param_.ANIME_WAIT    = animeTrash01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = { 
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f, 
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f 
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_TRASH01_ATK;
}

// Trash02
PlayerTrash02Behavior::PlayerTrash02Behavior()
{
    param_.ANIME_WAIT    = animeTrash02;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_TRASH02_ATK;
}

// Trash03
PlayerTrash03Behavior::PlayerTrash03Behavior()
{
    param_.ANIME_WAIT    = animeTrash03;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_TRASH03_ATK;
}


//******************************************************************************
// 
//      Common(���ʂȂ��p�[�c)
// 
//******************************************************************************

// Common01
PlayerCommon01Behavior::PlayerCommon01Behavior()
{
    param_.ANIME_WAIT    = animeCommon01;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_64,-COMMON_HITBOX_18,
          COMMON_HITBOX_64, COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON01_ATK;
}

// Common01_2(90�x��])
PlayerCommon01_2Behavior::PlayerCommon01_2Behavior()
{
    //param_.ANIME_WAIT    = animeCommon01;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18,-COMMON_HITBOX_64,
          COMMON_HITBOX_18, COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON04_ATK;
}

// Common02
PlayerCommon02Behavior::PlayerCommon02Behavior()
{
    param_.ANIME_WAIT    = animeCommon02;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_64,-COMMON_HITBOX_18,
          COMMON_HITBOX_64, COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON02_ATK;
}

// Common02_2(90�x��])
PlayerCommon02_2Behavior::PlayerCommon02_2Behavior()
{
    param_.ANIME_WAIT    = animeCommon02;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18,-COMMON_HITBOX_64,
          COMMON_HITBOX_18, COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON05_ATK;
}

// Common03
PlayerCommon03Behavior::PlayerCommon03Behavior()
{
    param_.ANIME_WAIT    = animeCommon03;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_64,-COMMON_HITBOX_18,
          COMMON_HITBOX_64, COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON03_ATK;
}

// Common03_2(90�x��])
PlayerCommon03_2Behavior::PlayerCommon03_2Behavior()
{
    param_.ANIME_WAIT    = animeCommon03;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18,-COMMON_HITBOX_64,
          COMMON_HITBOX_18, COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON06_ATK;
}


//******************************************************************************
// 
//      erase�i�����j
// 
//******************************************************************************

// �e�T��(�i�V���Ɖ�ꂽ���̑u����������)
#define USE_FIND_PARENT

bool ErasePlayer::isPartsClear = false;

void ErasePlayer::erase(OBJ2D* obj) const
{
    // behavior���Ȃ����return
    if (!obj->behavior_) return;

    ActorComponent* a = obj->actorComponent_;

    //  PL�ȊO������(�Q�[���N���A�̏����Ŏg�p)
    if (isPartsClear && obj != a->parent_) obj->behavior_ = nullptr;

    // HP��0�ȉ��ɂȂ邩�AGameOver�Ȃ�
    if (!a->isAlive() || Game::instance()->isGameOver())
    {
        // �{�̂̏ꍇ
        if (obj == Game::instance()->player_)
        {
            if (!obj->performComponent_->isTrigger)
            {
                // Trigger��true��(GameOver�̃t���O������)
                obj->performComponent_->isTrigger = true;
            }
            return;
        }

        // �����G�t�F�N�g
        AddObj::addEffect(obj, &efcBombBehavior);

        // ���SSE
        Audio::play(SE_DEATH, false);

        a->parent_     = nullptr; // �e�������Z�b�g
        obj->behavior_ = nullptr; // ����������

        // �k���J�E���g����
        BasePlayerBehavior::plShrinkCount_ = std::max(
            0, BasePlayerBehavior::plShrinkCount_ - 1
        );

        --BasePlayerBehavior::plPartsCurrentCount_;

        return;
    }


    // �e�����݂��Ȃ����
    if (!a->parent_)
    {      
        ++a->deathDelayTimer_; // ���S�f�B���C�^�C�}�[�����Z����
    }
    else // �e�����݂��Ă���
    {
        if (a->parent_->behavior_) return;   // �e���܂������Ă����return

        // ����ł����

        // �V�����e��T��
#ifdef  USE_FIND_PARENT
        for (auto& dst : *Game::instance()->obj2dManager()->getList())
        {
            if (!dst->behavior_) continue;                               // ���肪���݂��Ȃ����continue;
            if (obj == dst)      continue;                               // ���肪�����Ȃ�continue;

            if (!obj->collider_->hitCheck(dst->collider_)) continue;     // ���肪�ڐG���Ă��Ȃ����continue;

            if (dst->behavior_->getType() != OBJ_TYPE::PLAYER) continue; // ���肪�����Ɠ����v���C���[�łȂ����continue

            if (!dst->actorComponent_->parent_) continue;                // ���肪�e�������Ă��Ȃ����continue;
            if (obj == dst->actorComponent_->parent_) continue;          // ���肪�����̎q�Ȃ�continue;

            obj->actorComponent_->parent_ = dst;                         // �����e�ɂ���

            return; // �e�����������̂�return
        }
#endif

        // �e��������Ȃ������ꍇ

        obj->actorComponent_->parent_ = nullptr; // �e�������Z�b�g

        // �k���J�E���g����
        BasePlayerBehavior::plShrinkCount_ = std::max(0, --BasePlayerBehavior::plShrinkCount_);

        --BasePlayerBehavior::plPartsCurrentCount_;

        return;
    }
    

    if (a->deathDelayTimer_ < PARTS_DEATH_DELAY_TIME) return;

    // ���S�f�B���C�^�C�}�[����莞�Ԃ������玀�S�������s��
    //�i�e�����񂾂Ƃ��̃p�[�c�̘A�����U�ɒx�������肾���j

    // �����G�t�F�N�g
    AddObj::addEffect(obj, &efcBombBehavior);

    // ���SSE
    Audio::play(SE_DEATH, false);

    obj->behavior_ = nullptr; // ����������

    return;
}

#undef USE_FIND_PARENT



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
//
//// �J�[�\���̍��W�擾
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
//    if ( (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4) ||
//         (GetAsyncKeyState(VK_LBUTTON) & 1) )
//    {
//        dst->behavior_ = nullptr;
//    
//        // �k���J�E���g����
//        BasePlayerBehavior::plShrinkCount_ = std::max(0, BasePlayerBehavior::plShrinkCount_ - 1);
//    }
//}