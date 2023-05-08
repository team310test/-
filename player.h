#pragma once

void setPlayer(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos, VECTOR2 scale,bool isDrawShrink, const bool makeOrgPlayer);
OBJ2D* setTitlePlayer(OBJ2DManager* obj2dManager, BG* bg);
//void setCursor(OBJ2DManager* obj2dManager, BG* bg);


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
//      PlayerCoreBehavior（自機本体）
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
//      PlayerPartsBehavior（パーツのベース）
// 
//******************************************************************************
class PlayerPartsBehavior : public BasePlayerBehavior
{
private:
    void shrink(OBJ2D*) const override;             // 縮小関数
    void contactToPlCore(OBJ2D*, OBJ2D*) const;   // オリジナル自機に向かって接触しに行く関数

public:
    static float toCoreVelocity_;  // オリジナル自機へ向かう速度
};

//
////******************************************************************************
//// 
////      CursorBehavior（カーソル）
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
//    // カーソルは縮小しないので｛｝で除外
//    void startAllShrink(OBJ2D*) const override {} 
//    void shrink(OBJ2D*) const override {}         
//};
//EXTERN CursorBehavior cursorBehavior;



//******************************************************************************
// 
//      Turret（攻撃砲台）
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
//      Buff(バフパーツ)
// 
//******************************************************************************

// Buff01
class PlayerBuff01Behavior : public PlayerPartsBehavior
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
class  PlayerTrash01Behavior : public PlayerPartsBehavior
{
public:
    PlayerTrash01Behavior();
};
EXTERN PlayerTrash01Behavior playerTrash01Behavior;


//******************************************************************************
// 
//      Common(効果なしパーツ)
// 
//******************************************************************************

// Common01
class  PlayerCommon01Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon01Behavior();
};
EXTERN PlayerCommon01Behavior playerCommon01Behavior;

// Common01_2(90度回転)
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

// Common02_2(90度回転)
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

// Common03_2(90度回転)
class  PlayerCommon03_2Behavior : public PlayerPartsBehavior
{
public:
    PlayerCommon03_2Behavior();
};
EXTERN PlayerCommon03_2Behavior playerCommon03_2Behavior;


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
//      プレイヤーのupdate
//******************************************************************************
// 自機本体のupdate
void PLAYER_CORE_UPDATE(OBJ2D* obj);
// パーツのupdate
void PLAYER_PATRS_UPDATE(OBJ2D* obj);
// タイトル用のupdate
void TITLE_PLAYER_UPDATE(OBJ2D*);