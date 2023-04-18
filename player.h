#pragma once

void setPlayer(OBJ2DManager* obj2dManager, BG* bg, const bool makeOrgPlayer);
void setCursor(OBJ2DManager* obj2dManager, BG* bg);


//******************************************************************************
// 
//      BasePlayerBehavior（プレイヤーのベース）
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
    static int plShrinkCount_; // 縮小するまでのプレイヤーの数を数える変数
};


//******************************************************************************
// 
//      CorePlayerBehavior（自機本体）
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
//      PartsPlayerBehavior（パーツのベース）
// 
//******************************************************************************
class PartsPlayerBehavior : public BasePlayerBehavior
{
private:
    void shrink(OBJ2D*) const override;           // 縮小関数

    void contact(OBJ2D*) const;                   // 縮小に伴って位置を移動させる関数
    void contactToOriginal(OBJ2D*, OBJ2D*) const; // オリジナル自機に向かって接触しに行く関数
    void contactToParent(OBJ2D*, OBJ2D*) const;   // 親に向かって接触しに行く関数
};


//******************************************************************************
// 
//      CursorBehavior（カーソル）
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

    // カーソルは縮小しないので｛｝で除外
    void startAllShrink(OBJ2D*) const override {} 
    void shrink(OBJ2D*) const override {}         
};
EXTERN CursorBehavior cursorBehavior;



//******************************************************************************
// 
//      Turret（攻撃砲台）
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
//      Buff(バフパーツ)
// 
//******************************************************************************

// Buff01
class PlayerBuff01Behavior : public PartsPlayerBehavior
{
public:
    PlayerBuff01Behavior();
private:
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; } // 味方（プレイヤー）に影響を与えるのでPLAYER
    void hit(OBJ2D*, OBJ2D*) const override;
};
EXTERN PlayerBuff01Behavior playerBuff01Behavior;



//==============================================================================
//
//      消去アルゴリズム
//
//==============================================================================
class ErasePlayer : public Eraser
{
    void erase(OBJ2D* obj) const;
};
EXTERN ErasePlayer erasePlayer;
