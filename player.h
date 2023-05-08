#pragma once

void setPlayer(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos, VECTOR2 scale,bool isDrawShrink, const bool makeOrgPlayer);
OBJ2D* setTitlePlayer(OBJ2DManager* obj2dManager, BG* bg);
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
    static const int PL_SHRINK_COUNT_MAX = 10; // �k������v���C���[�̋K�萔
public:
    static int plShrinkCount_; // �k������܂ł̃v���C���[�̐��𐔂���ϐ�
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

//
////******************************************************************************
//// 
////      CursorBehavior�i�J�[�\���j
//// 
////******************************************************************************
//class CursorBehavior : public BasePlayerBehavior
//{
//public:
//    CursorBehavior();
//private:
//    OBJ_TYPE getType() const override { return OBJ_TYPE::CURSOR; }
//    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; }
//    void hit(OBJ2D*, OBJ2D*) const override;
//
//    void damageProc(OBJ2D*) const override;
//
//    // �J�[�\���͏k�����Ȃ��̂Ło�p�ŏ��O
//    void startAllShrink(OBJ2D*) const override {} 
//    void shrink(OBJ2D*) const override {}         
//};
//EXTERN CursorBehavior cursorBehavior;



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

// Trach01
class  PlayerTrash01Behavior : public PlayerPartsBehavior
{
public:
    PlayerTrash01Behavior();
};
EXTERN PlayerTrash01Behavior playerTrash01Behavior;


//******************************************************************************
// 
//      Common(���ʂȂ��p�[�c)
// 
//******************************************************************************

// Common01
class  PlayerCommon01Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon01Behavior();
};
EXTERN PlayerCommon01Behavior playerCommon01Behavior;

// Common01_2(90�x��])
class  PlayerCommon01_2Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon01_2Behavior();
};
EXTERN PlayerCommon01_2Behavior playerCommon01_2Behavior;

// Common02
class  PlayerCommon02Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon02Behavior();
};
EXTERN PlayerCommon02Behavior playerCommon02Behavior;

// Common02_2(90�x��])
class  PlayerCommon02_2Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon02_2Behavior();
};
EXTERN PlayerCommon02_2Behavior playerCommon02_2Behavior;

// Common03
class  PlayerCommon03Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon03Behavior();
};
EXTERN PlayerCommon03Behavior playerCommon03Behavior;

// Common03_2(90�x��])
class  PlayerCommon03_2Behavior : public PlayerPartsBehavior
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
    void erase(OBJ2D* obj) const;
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