#pragma once

//******************************************************************************
//
//
//      Enemyh
//
//
//******************************************************************************

void setEnemy(OBJ2DManager* obj2dManager, BG* bg);

void addEnemy(OBJ2DManager* obj2dManager, BG* bg);

//==============================================================================
//
//      移動アルゴリズム
//
//==============================================================================
class BaseEnemyBehavior : public ActorBehavior
{
protected:
    void init(OBJ2D* obj) const override;
private:
    void moveX(OBJ2D* obj) const;
    OBJ_TYPE getType() const override { return OBJ_TYPE::ENEMY; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; }
    void hit(OBJ2D*, OBJ2D*) const override;

    bool isAlive(OBJ2D* obj) const;
    void damageProc(OBJ2D* obj) const override;
    void areaCheck(OBJ2D* obj) const;
};

class NormalEnemyBehavior : public BaseEnemyBehavior
{
public:    
    NormalEnemyBehavior();
private:
    void moveY(OBJ2D* obj) const override;
    void attack(OBJ2D* obj) const override;
};
EXTERN NormalEnemyBehavior normalEnemyBehavior;

class ItemEnemyBehavior : public BaseEnemyBehavior
{
public:
    ItemEnemyBehavior();
private:
    OBJ_TYPE getType() const override { return OBJ_TYPE::ITEM; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::null; }
    void hit(OBJ2D*, OBJ2D*) const override;
    void attack(OBJ2D* obj) const override;
};
EXTERN ItemEnemyBehavior itemEnemyBehavior;


//******************************************************************************
//      EnemyCore01
//******************************************************************************
// エネミー
class EnemyCore01Behavior : public BaseEnemyBehavior
{
public:
    EnemyCore01Behavior();
private:
    void init(OBJ2D* obj)const override;
};
EXTERN EnemyCore01Behavior enemyCore01Behavior;

//******************************************************************************
//      EnemyCore02
//******************************************************************************
// エネミー
class EnemyCore02Behavior : public BaseEnemyBehavior
{
public:
    EnemyCore02Behavior();
private:
    void init(OBJ2D* obj)const override;
};
EXTERN EnemyCore02Behavior enemyCore02Behavior;


//******************************************************************************
//      Turret01
//******************************************************************************
// エネミー
class EnemyTurret01Behavior : public BaseEnemyBehavior
{
public:
    EnemyTurret01Behavior();
private:
    void attack(OBJ2D* obj) const override;
};
EXTERN EnemyTurret01Behavior enemyTurret01Behavior;
// アイテム
class ItemTurret01Behavior : public BaseEnemyBehavior
{
public:
    ItemTurret01Behavior();
private:
    OBJ_TYPE getType() const override { return OBJ_TYPE::ITEM; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::null; }
};
EXTERN ItemTurret01Behavior itemTurret01Behavior;

//******************************************************************************
//      EnemyTrash01
//******************************************************************************
// エネミー
class ItemTrash01Behavior : public BaseEnemyBehavior
{
public:
    ItemTrash01Behavior();
    OBJ_TYPE getType() const override { return OBJ_TYPE::ITEM; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::null; }
};
EXTERN ItemTrash01Behavior itemTrash01Behavior;

//==============================================================================
//
//      消去アルゴリズム
//
//==============================================================================

// 消去アルゴリズム
class EraseEnemy : public Eraser
{
    void erase(OBJ2D* obj) const;
};
EXTERN EraseEnemy eraseEnemy;

class EraseItem : public Eraser
{
    void erase(OBJ2D* obj) const;
};
EXTERN EraseItem eraseItem;