#pragma once

void addEnemy(OBJ2DManager* obj2dManager, BG* bg);

//******************************************************************************
// 
//      BaseEnemyBehavior(�G�l�~�[�̃x�[�X)
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
//      EnemyCore�i�G�l�~�[�̖{�́j
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
//      BaseEnemyPartsBehavior�i�G�l�~�[�̃p�[�c�̃x�[�X�j
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
//      Turret�i�U���p�[�c�j
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
//      Buff(�o�t�p�[�c)
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
//      erase(����)
// 
//******************************************************************************
class EraseEnemy : public Eraser
{
    void erase(OBJ2D* obj) const;
};
EXTERN EraseEnemy eraseEnemy;


//******************************************************************************
//      �G�l�~�[��update
//******************************************************************************
// �R�A�̃A�b�v�f�[�^
extern void ENEMY_LINE(OBJ2D*);
extern void ENEMY_TARGET_X(OBJ2D* obj);
// �p�[�c�̃A�b�v�f�[�g
extern void ENEMY_PARTS(OBJ2D* obj);