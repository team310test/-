#pragma once


//******************************************************************************
// 
//      BaseDropPartsBehavior(�h���b�v�����p�[�c�̃x�[�X)
// 
//******************************************************************************
class BaseDropPartsBehavior : public ActorBehavior
{
private:
    void init(OBJ2D* obj)    const override;
    OBJ_TYPE getType()       const override { return OBJ_TYPE::PARTS; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; }
    void hit(OBJ2D*, OBJ2D*) const override;

    bool isAlive(OBJ2D* obj)   const override;
    void areaCheck(OBJ2D* obj) const override;
};


//******************************************************************************
// 
//      Turret(�U���p�[�c)
// 
//******************************************************************************

// Turret01
class DropTurret01Behavior : public BaseDropPartsBehavior
{
public:
    DropTurret01Behavior();
};
EXTERN DropTurret01Behavior dropTurret01Behavior;


//******************************************************************************
// 
//      Buff(�o�t�p�[�c)
// 
//******************************************************************************

// Buff01
class DropBuff01Behavior : public BaseDropPartsBehavior
{
public:
    DropBuff01Behavior();
};
EXTERN DropBuff01Behavior dropBuff01Behavior;


//******************************************************************************
// 
//      Trash(�S�~�p�[�c)
// 
//******************************************************************************

// Trash01
class DropTrash01Behavior : public BaseDropPartsBehavior
{
public:
    DropTrash01Behavior();
};
EXTERN DropTrash01Behavior dropTrash01Behavior;

//******************************************************************************
// 
//      erase(����)
// 
//******************************************************************************
class EraseDropParts : public Eraser
{
    void erase(OBJ2D* obj) const;
};
EXTERN EraseDropParts eraseDropParts;

//******************************************************************************
//      �p�[�c��update
//******************************************************************************
extern void PARTS_UPDATE(OBJ2D* obj);