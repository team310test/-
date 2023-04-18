#pragma once

//******************************************************************************
//
//
//      Player.h
//
//
//******************************************************************************

void setPlayer(OBJ2DManager* obj2dManager, BG* bg, const bool makeOrgPlayer);

void setCursor(OBJ2DManager* obj2dManager, BG* bg);

//==============================================================================
//
//      �ړ��A���S���Y��
//
//==============================================================================
class BasePlayerBehavior : public ActorBehavior
{
private:
    void init(OBJ2D* obj) const override;
    void moveX(OBJ2D* obj) const;
    OBJ_TYPE getType() const override { return OBJ_TYPE::PLAYER; }
    //OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ENEMY; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ITEM; }
    void hit(OBJ2D*, OBJ2D*) const override;

    bool isAlive(OBJ2D* obj) const;
    void damageProc(OBJ2D* obj) const override;
    void areaCheck(OBJ2D* obj) const;

public:
    static int plShrinkCount; // �k������܂ł̃v���C���[�̐��𐔂���ϐ�
};

class NormalPlayerBehavior : public BasePlayerBehavior
{
public:
    NormalPlayerBehavior();
private:
    void moveY(OBJ2D* obj) const override;
    void attack(OBJ2D* obj) const override;
};
EXTERN NormalPlayerBehavior normalPlayerBehavior;


class ItemPlayerBehavior : public BasePlayerBehavior
{
public:
    ItemPlayerBehavior();
private:
    void moveY(OBJ2D* obj) const override;
    void attack(OBJ2D* obj) const override;

    void shrink(OBJ2D*) const override;           // �k���֐�
    void contact(OBJ2D*) const;                   // �k���ɔ����Ĉʒu���ړ�������֐�
    void contactToOriginal(OBJ2D*, OBJ2D*) const; // �I���W�i�����@�Ɍ������ĐڐG���ɍs���֐�
    void contactToParent(OBJ2D*, OBJ2D*) const;   // �e�Ɍ������ĐڐG���ɍs���֐�
};
EXTERN ItemPlayerBehavior itemPlayerBehavior;

class CursorBehavior : public BasePlayerBehavior
{
public:
    CursorBehavior();
private:
    OBJ_TYPE getType() const override { return OBJ_TYPE::MAX; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; }
    void hit(OBJ2D*, OBJ2D*) const override;

    void damageProc(OBJ2D*) const override;

    void startAllShrink(OBJ2D*) const override {} // �J�[�\���͏k���J�n���Ȃ��̂Ło�p�ŏ��O
    void shrink(OBJ2D*) const override {}         // �J�[�\���͏k�����Ȃ��̂Ło�p�ŏ��O
};
EXTERN CursorBehavior cursorBehavior;

//******************************************************************************
//      Turret01
//******************************************************************************
class PlayerTurret01Behavior : public ItemPlayerBehavior
{
public:
    PlayerTurret01Behavior();
private:
};
EXTERN PlayerTurret01Behavior playerTurret01Behavior;

//==============================================================================
//
//      �����A���S���Y��
//
//==============================================================================

// �����A���S���Y��
class ErasePlayer : public Eraser
{
    void erase(OBJ2D* obj) const;
};
EXTERN ErasePlayer erasePlayer;
