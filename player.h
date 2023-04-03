#pragma once

//******************************************************************************
//
//
//      Player.h
//
//
//******************************************************************************

void setPlayer(OBJ2DManager* obj2dManager, BG* bg);

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
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ITEM; }
    void hit(OBJ2D*, OBJ2D*) const override;

    bool isAlive(OBJ2D* obj) const;
    void damageProc(OBJ2D* obj) const override;
    void areaCheck(OBJ2D* obj) const;
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

    void shrink(OBJ2D*) const override;
    void contact(OBJ2D*,OBJ2D*) const;   // org自機の方へ移動(仮)
    void hitCheck(OBJ2D*) const;  // org自機と接触しているか判定(仮)
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
};
EXTERN CursorBehavior cursorBehavior;

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
