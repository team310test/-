#pragma once

void setPlayer(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos, bool isDrawShrink, const bool makeOrgPlayer);
//void setCursor(OBJ2DManager* obj2dManager, BG* bg);


//******************************************************************************
// 
//      BasePlayerBehavior�i�v���C���[�̃x�[�X�j
// 
//******************************************************************************
class BasePlayerBehavior : public ActorBehavior
{
private:
    void init(OBJ2D* obj) const override;
    OBJ_TYPE getType() const override       { return OBJ_TYPE::PLAYER; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ENEMY; }
    void hit(OBJ2D*, OBJ2D*) const override;

    bool isAlive(OBJ2D* obj) const override { return obj->actorComponent_->hp_; }
    void damageProc(OBJ2D* obj) const override;
    void areaCheck(OBJ2D* obj) const override;

public:
    static int plShrinkCount_;       // ���݂̃v���C���[�p�[�c�̃J�E���g�i�����ł͂Ȃ��j
    static int plShrinkCountMax_;    // �k������̂ɕK�v�ȃv���C���[�p�[�c�̐�

    static int plPartsCurrentCount_; // ���݂̃v���C���[�p�[�c�̑���
};


//******************************************************************************
// 
//      PlayerCoreBehavior�i���@�{�́j
// 
//******************************************************************************
class PlayerCoreBehavior : public BasePlayerBehavior
{
public:
    PlayerCoreBehavior();
private:
    void attack(OBJ2D* obj) const override;
    void areaCheck(OBJ2D* obj) const override;
};
EXTERN PlayerCoreBehavior playerCoreBehavior;


//******************************************************************************
// 
//      PlayerPartsBehavior�i�p�[�c�̃x�[�X�j
// 
//******************************************************************************
class PlayerPartsBehavior : public BasePlayerBehavior
{
private:
    void shrink(OBJ2D*) const override;             // �k���֐�
    void contactToPlCore(OBJ2D*, OBJ2D*) const;   // �I���W�i�����@�Ɍ������ĐڐG���ɍs���֐�

public:
    static float toCoreVelocity_;  // �I���W�i�����@�֌��������x
};


//******************************************************************************
// 
//      Turret�i�U���C��j
// 
//******************************************************************************

// Turret01
class PlayerTurret01Behavior : public PlayerPartsBehavior
{
public:
    PlayerTurret01Behavior();
private:
    void attack(OBJ2D* obj) const override;
};
EXTERN PlayerTurret01Behavior playerTurret01Behavior;

// Turret01(���])
class PlayerTurret01FlipBehavior : public PlayerPartsBehavior
{
public:
    PlayerTurret01FlipBehavior();
private:
    void attack(OBJ2D* obj) const override;
};
EXTERN PlayerTurret01FlipBehavior playerTurret01FlipBehavior;

// Turret02(CurveShot)
class PlayerTurret02Behavior : public PlayerPartsBehavior
{
public:
    PlayerTurret02Behavior();
private:
    void attack(OBJ2D* obj) const override;
};
EXTERN PlayerTurret02Behavior playerTurret02Behavior;

// Turret02Flip
class PlayerTurret02FlipBehavior : public PlayerPartsBehavior
{
public:
    PlayerTurret02FlipBehavior();
private:
    void attack(OBJ2D* obj) const override;
};
EXTERN PlayerTurret02FlipBehavior playerTurret02FlipBehavior;

// Turret03(�ђʒe�j
class PlayerTurret03Behavior : public PlayerPartsBehavior
{
public:
    PlayerTurret03Behavior();
private:
    void attack(OBJ2D* obj) const override;
};
EXTERN PlayerTurret03Behavior playerTurret03Behavior;


//******************************************************************************
// 
//      Shield(�h��p�[�c)
// 
//******************************************************************************

// Shield01
class PlayerShield01Behavior : public PlayerPartsBehavior
{
public:
    PlayerShield01Behavior();
};
EXTERN PlayerShield01Behavior playerShield01Behavior;


//******************************************************************************
// 
//      Buff(�o�t�p�[�c)
// 
//******************************************************************************

// Buff01
class PlayerBuff01Behavior : public PlayerPartsBehavior
{
public:
    PlayerBuff01Behavior();
private:
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; } // �����i�v���C���[�j�ɉe����^����̂�PLAYER
    void hit(OBJ2D*, OBJ2D*) const override;
};
EXTERN PlayerBuff01Behavior playerBuff01Behavior;


//******************************************************************************
// 
//      Trash(�S�~�p�[�c)
// 
//******************************************************************************

// Trash01
class PlayerTrash01Behavior : public PlayerPartsBehavior
{
public:
    PlayerTrash01Behavior();
};
EXTERN PlayerTrash01Behavior playerTrash01Behavior;

// Trash02
class PlayerTrash02Behavior : public PlayerPartsBehavior
{
public:
    PlayerTrash02Behavior();
};
EXTERN PlayerTrash02Behavior playerTrash02Behavior;

// Trash03
class PlayerTrash03Behavior : public PlayerPartsBehavior
{
public:
    PlayerTrash03Behavior();
};
EXTERN PlayerTrash03Behavior playerTrash03Behavior;


//******************************************************************************
// 
//      Common(���ʂȂ��p�[�c)
// 
//******************************************************************************

// Common01
class PlayerCommon01Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon01Behavior();
};
EXTERN PlayerCommon01Behavior playerCommon01Behavior;

// Common01_2(90�x��])
class PlayerCommon01_2Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon01_2Behavior();
};
EXTERN PlayerCommon01_2Behavior playerCommon01_2Behavior;

// Common02
class PlayerCommon02Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon02Behavior();
};
EXTERN PlayerCommon02Behavior playerCommon02Behavior;

// Common02_2(90�x��])
class PlayerCommon02_2Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon02_2Behavior();
};
EXTERN PlayerCommon02_2Behavior playerCommon02_2Behavior;

// Common03
class PlayerCommon03Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon03Behavior();
};
EXTERN PlayerCommon03Behavior playerCommon03Behavior;

// Common03_2(90�x��])
class PlayerCommon03_2Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon03_2Behavior();
};
EXTERN PlayerCommon03_2Behavior playerCommon03_2Behavior;


//==============================================================================
//
//      �����A���S���Y��
//
//==============================================================================
class ErasePlayer : public Eraser
{
    void erase(OBJ2D* obj) const override;
};
EXTERN ErasePlayer erasePlayer;


//******************************************************************************
//      �v���C���[��update
//******************************************************************************
// ���@�{�̂�update
void PLAYER_CORE_UPDATE(OBJ2D* obj);
// �p�[�c��update
void PLAYER_PATRS_UPDATE(OBJ2D* obj);
// �^�C�g���p��update
void TITLE_PLAYER_UPDATE(OBJ2D*);
// �Q�[��(�I�[�o�[)�p��update
void GAME_OVER_PLAYER_UPDATE(OBJ2D * obj);


////******************************************************************************
//// 
////      CursorBehavior�i�J�[�\���j
//// 
////******************************************************************************
//class CursorBehavior : public BasePlayerBehavior
//{
//public:
//    CursorBehavior() {}
//private:
//    OBJ_TYPE getType() const override { return OBJ_TYPE::CURSOR; }
//    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; }
//    void hit(OBJ2D*, OBJ2D*) const override;
//
//    void damageProc(OBJ2D*) const override {};
//
//    // �J�[�\���͏k�����Ȃ��̂Ło�p�ŏ��O
//    void startAllShrink(OBJ2D*) const override {} 
//    void shrink(OBJ2D*) const override {}         
//};
//EXTERN CursorBehavior cursorBehavior;



