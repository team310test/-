#pragma once


#define NEW_SET_ENEMY 1


//void setEnemy01(OBJ2DManager* obj2dManager, BG* bg);
//void setEnemy01(OBJ2DManager* obj2dManager, BG* bg);

void addEnemy(OBJ2DManager* obj2dManager, BG* bg);

void setEnemy01(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos,OBJ_DATA update);
void setEnemy02(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos,OBJ_DATA update);
void setEnemyT(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos, OBJ_DATA update);

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
//      Turret（攻撃パーツ）
// 
//******************************************************************************

// Turret01
class EnemyTurret01Behavior : public BaseEnemyBehavior
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
class EnemyBuff01Behavior : public BaseEnemyBehavior
{
public:
    EnemyBuff01Behavior();
};
EXTERN EnemyBuff01Behavior enemyBuff01Behavior;


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
extern void ENEMY_LINE(OBJ2D*);
extern void ENEMY_LINE_SLOW(OBJ2D* obj);