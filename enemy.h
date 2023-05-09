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

// Turret01
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
private:
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ENEMY; } // 味方（エネミー）に影響を与えるのでENEMY
    void hit(OBJ2D*, OBJ2D*) const override;
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

// Common01_2(90度回転)
class EnemyCommon01_2Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon01_2Behavior();
};
EXTERN EnemyCommon01_2Behavior enemyCommon01_2Behavior;

// Common02
class EnemyCommon02Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon02Behavior();
};
EXTERN EnemyCommon02Behavior enemyCommon02Behavior;

// Common01_2(90度回転)
class EnemyCommon02_2Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon02_2Behavior();
};
EXTERN EnemyCommon02_2Behavior enemyCommon02_2Behavior;

// Common03
class EnemyCommon03Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon03Behavior();
};
EXTERN EnemyCommon03Behavior enemyCommon03Behavior;

// Common03_2(90度回転)
class EnemyCommon03_2Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon03_2Behavior();
};
EXTERN EnemyCommon03_2Behavior enemyCommon03_2Behavior;


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