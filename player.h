#pragma once

void setPlayer(OBJ2DManager* obj2dManager, BG* bg, const bool makeOrgPlayer);
void setCursor(OBJ2DManager* obj2dManager, BG* bg);


//******************************************************************************
// 
//      BasePlayerBehavior�i�v���C���[�̃x�[�X�j
// 
//******************************************************************************
class BasePlayerBehavior : public ActorBehavior
{
private:
    void init(OBJ2D* obj) const override;
    void moveY(OBJ2D* obj) const override;
    void moveX(OBJ2D* obj) const override;
    OBJ_TYPE getType() const override { return OBJ_TYPE::PLAYER; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ENEMY; }
    void hit(OBJ2D*, OBJ2D*) const override;

    bool isAlive(OBJ2D* obj) const override;
    void damageProc(OBJ2D* obj) const override;
    void areaCheck(OBJ2D* obj) const override;

public:
    static int plShrinkCount_; // �k������܂ł̃v���C���[�̐��𐔂���ϐ�
};


//******************************************************************************
// 
//      CorePlayerBehavior�i���@�{�́j
// 
//******************************************************************************
class CorePlayerBehavior : public BasePlayerBehavior
{
public:
    CorePlayerBehavior();
private:
    void attack(OBJ2D* obj) const override;
};
EXTERN CorePlayerBehavior corePlayerBehavior;


//******************************************************************************
// 
//      PartsPlayerBehavior�i�p�[�c�̃x�[�X�j
// 
//******************************************************************************
class PartsPlayerBehavior : public BasePlayerBehavior
{
private:
    void shrink(OBJ2D*) const override;           // �k���֐�

    void contact(OBJ2D*) const;                   // �k���ɔ����Ĉʒu���ړ�������֐�
    void contactToOriginal(OBJ2D*, OBJ2D*) const; // �I���W�i�����@�Ɍ������ĐڐG���ɍs���֐�
    void contactToParent(OBJ2D*, OBJ2D*) const;   // �e�Ɍ������ĐڐG���ɍs���֐�
};


//******************************************************************************
// 
//      CursorBehavior�i�J�[�\���j
// 
//******************************************************************************
class CursorBehavior : public BasePlayerBehavior
{
public:
    CursorBehavior();
private:
    OBJ_TYPE getType() const override { return OBJ_TYPE::MAX; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; }
    void hit(OBJ2D*, OBJ2D*) const override;

    void damageProc(OBJ2D*) const override;

    // �J�[�\���͏k�����Ȃ��̂Ło�p�ŏ��O
    void startAllShrink(OBJ2D*) const override {} 
    void shrink(OBJ2D*) const override {}         
};
EXTERN CursorBehavior cursorBehavior;



//******************************************************************************
// 
//      Turret�i�U���C��j
// 
//******************************************************************************

// Turret01
class PlayerTurret01Behavior : public PartsPlayerBehavior
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
class PlayerBuff01Behavior : public PartsPlayerBehavior
{
public:
    PlayerBuff01Behavior();
private:
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; } // �����i�v���C���[�j�ɉe����^����̂�PLAYER
    void hit(OBJ2D*, OBJ2D*) const override;
};
EXTERN PlayerBuff01Behavior playerBuff01Behavior;



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
