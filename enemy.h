#pragma once

void addEnemy(OBJ2DManager* obj2dManager, BG* bg);

//******************************************************************************
// 
//      BaseEnemyBehavior(エネミーのベース)
// 
//******************************************************************************
class BaseEnemyBehavior : public ActorBehavior
{
private:
    void init(OBJ2D* obj) const override;
    OBJ_TYPE getType() const override       { return OBJ_TYPE::ENEMY; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; }
    void hit(OBJ2D*, OBJ2D*) const override;

    bool isAlive(OBJ2D* obj) const override;
    void damageProc(OBJ2D* obj) const override;
    void areaCheck(OBJ2D* obj) const override;
};


//******************************************************************************
// 
//      EnemyCore（エネミーの本体）
// 
//******************************************************************************

// EnemyCore01
class EnemyCore01Behavior : public BaseEnemyBehavior
{
public:
    EnemyCore01Behavior();
private:
    //void attack(OBJ2D* obj) const override;
};
EXTERN EnemyCore01Behavior enemyCore01Behavior;


//******************************************************************************
// 
//      BaseEnemyPartsBehavior（エネミーのパーツのベース）
// 
//******************************************************************************

class BaseEnemyPartsBehavior : public BaseEnemyBehavior
{
private:
    void shrink(OBJ2D* obj) const override;
    void contactToEnmCore(OBJ2D*, OBJ2D*) const;

public:
    static float toCoreVelocity_;
};



//******************************************************************************
// 
//      Turret（攻撃パーツ）
// 
//******************************************************************************

// Turret01(AimShot)
class EnemyTurret01Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyTurret01Behavior();
private:
    void attack(OBJ2D* obj) const override;
};
EXTERN EnemyTurret01Behavior enemyTurret01Behavior;


//******************************************************************************
// 
//      Buff(バフパーツ)
// 
//******************************************************************************

// Buff01
class EnemyBuff01Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyBuff01Behavior();
};
EXTERN EnemyBuff01Behavior enemyBuff01Behavior;


//******************************************************************************
// 
//      Common(効果なしパーツ)
// 
//******************************************************************************

// Common01
class EnemyCommon01Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon01Behavior();
};
EXTERN EnemyCommon01Behavior enemyCommon01Behavior;

// Common04([01]の90度回転)
class EnemyCommon04Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon04Behavior();
};
EXTERN EnemyCommon04Behavior enemyCommon04Behavior;

// Common02
class EnemyCommon02Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon02Behavior();
};
EXTERN EnemyCommon02Behavior enemyCommon02Behavior;

// Common05([02]の90度回転)
class EnemyCommon05Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon05Behavior();
};
EXTERN EnemyCommon05Behavior enemyCommon05Behavior;

// Common03
class EnemyCommon03Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon03Behavior();
};
EXTERN EnemyCommon03Behavior enemyCommon03Behavior;

// Common06([03]の90度回転)
class EnemyCommon06Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon06Behavior();
};
EXTERN EnemyCommon06Behavior enemyCommon06Behavior;


//******************************************************************************
// 
//      erase(消去)
// 
//******************************************************************************
class EraseEnemy : public Eraser
{
    void erase(OBJ2D* obj) const;
};
EXTERN EraseEnemy eraseEnemy;


//******************************************************************************
//      エネミーのupdate
//******************************************************************************
// コアのアップデータ
extern void ENEMY_LINE(OBJ2D*);
extern void ENEMY_TARGET_X(OBJ2D* obj);
// パーツのアップデート
extern void ENEMY_PARTS(OBJ2D* obj);