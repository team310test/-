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
//      移動アルゴリズム
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
    static int plShrinkCount; // 縮小するまでのプレイヤーの数を数える変数
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

    void shrink(OBJ2D*) const override;           // 縮小関数
    void contact(OBJ2D*) const;                   // 縮小に伴って位置を移動させる関数
    void contactToOriginal(OBJ2D*, OBJ2D*) const; // オリジナル自機に向かって接触しに行く関数
    void contactToParent(OBJ2D*, OBJ2D*) const;   // 親に向かって接触しに行く関数
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

    void startAllShrink(OBJ2D*) const override {} // カーソルは縮小開始しないので｛｝で除外
    void shrink(OBJ2D*) const override {}         // カーソルは縮小しないので｛｝で除外
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
//      消去アルゴリズム
//
//==============================================================================

// 消去アルゴリズム
class ErasePlayer : public Eraser
{
    void erase(OBJ2D* obj) const;
};
EXTERN ErasePlayer erasePlayer;
