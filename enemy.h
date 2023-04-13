#pragma once

//******************************************************************************
//
//
//      Player.h
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
private:
    void init(OBJ2D* obj) const override;
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
    //OBJ_TYPE getType() const override { return OBJ_TYPE::TYPE_NULL; }
    OBJ_TYPE getType() const override { return OBJ_TYPE::ITEM; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::null; }
    void hit(OBJ2D*, OBJ2D*) const override;
    void attack(OBJ2D* obj) const override;
};
EXTERN ItemEnemyBehavior itemEnemyBehavior;

// <parts01Enemey(Lzi仮)>
class Parts01EnemyBehavior : public BaseEnemyBehavior
{
public:
    Parts01EnemyBehavior();
private:
    //void attack(OBJ2D* obj) const override;
};
EXTERN Parts01EnemyBehavior parts01EnemyBehavior;

// <parts01Item(Lzi仮)>
class Parts01ItemBehavior : public BaseEnemyBehavior
{
public:
    Parts01ItemBehavior();
private:
    OBJ_TYPE getType() const override { return OBJ_TYPE::ITEM; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::null; }
};
EXTERN Parts01ItemBehavior parts01ItemBehavior;


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