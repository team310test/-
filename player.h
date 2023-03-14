#pragma once

//******************************************************************************
//
//
//      Player.h
//
//
//******************************************************************************

void setPlayer(OBJ2DManager* obj2dManager, BG* bg);

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
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ENEMY; }
    void hit(OBJ2D*, OBJ2D*) const override;

    bool isAlive(OBJ2D* obj) const;
    void damageProc(OBJ2D* obj) const override;
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
