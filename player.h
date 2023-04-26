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
    OBJ_TYPE getType() const override       { return OBJ_TYPE::PLAYER; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ENEMY; }
    void hit(OBJ2D*, OBJ2D*) const override;

    bool isAlive(OBJ2D* obj) const override { return obj->actorComponent_->hp_; }
    void damageProc(OBJ2D* obj) const override;
    void areaCheck(OBJ2D* obj) const override;

public:
    static const int PL_SHRINK_COUNT_MAX = 10; // 縮小するプレイヤーの規定数
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
    void shrink(OBJ2D*) const override;             // 縮小関数
    void contactToOriginal(OBJ2D*, OBJ2D*) const;   // オリジナル自機に向かって接触しに行く関数

public:
    static float toCoreVelocity;  // オリジナル自機へ向かう速度
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
    OBJ_TYPE getType() const override { return OBJ_TYPE::CURSOR; }
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


//******************************************************************************
// 
//      Trash(ゴミパーツ)
// 
//******************************************************************************

// Trach01
class  PlayerTrash01Behavior : public PartsPlayerBehavior
{
public:
    PlayerTrash01Behavior();
};
EXTERN PlayerTrash01Behavior playerTrash01Behavior;


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


//******************************************************************************
//      エネミーのupdate
//******************************************************************************
// 自機本体のupdate
void PLAYER_UPDATE(OBJ2D* obj);
// パーツのupdate
void PATRS_PLAYER_UPDATE(OBJ2D* obj);