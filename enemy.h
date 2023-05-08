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
//      Common(���ʂȂ��p�[�c)
// 
//******************************************************************************

// Common01
class EnemyCommon01Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon01Behavior();
};
EXTERN EnemyCommon01Behavior enemyCommon01Behavior;

// Common04([01]��90�x��])
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

// Common05([02]��90�x��])
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

// Common06([03]��90�x��])
class EnemyCommon06Behavior : public BaseEnemyPartsBehavior
{
public:
    EnemyCommon06Behavior();
};
EXTERN EnemyCommon06Behavior enemyCommon06Behavior;


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