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
//      �ړ��A���S���Y��
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
    OBJ_TYPE getType() const override { return OBJ_TYPE::ITEM; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::null; }
    void hit(OBJ2D*, OBJ2D*) const override;
    void attack(OBJ2D* obj) const override;
};
EXTERN ItemEnemyBehavior itemEnemyBehavior;

//******************************************************************************
//      Turret01
//******************************************************************************
class EnemyTurret01Behavior : public BaseEnemyBehavior
{
public:
    EnemyTurret01Behavior();
private:
    //void attack(OBJ2D* obj) const override;
};
EXTERN EnemyTurret01Behavior enemyTurret01Behavior;

// <parts01Item(Lzi��)>
class ItemTurret01Behavior : public BaseEnemyBehavior
{
public:
    ItemTurret01Behavior();
private:
    OBJ_TYPE getType() const override { return OBJ_TYPE::ITEM; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::null; }
};
EXTERN ItemTurret01Behavior itemTurret01Behavior;


//==============================================================================
//
//      �����A���S���Y��
//
//==============================================================================

// �����A���S���Y��
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