#pragma once


//******************************************************************************
// 
//      BaseDropPartsBehavior(ドロップしたパーツのベース)
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
//      Turret(攻撃パーツ)
// 
//******************************************************************************

// Turret01
class DropTurret01Behavior : public BaseDropPartsBehavior
{
public:
    DropTurret01Behavior();
};
EXTERN DropTurret01Behavior dropTurret01Behavior;

// Turret01(反転)
class DropTurret01FlipBehavior : public BaseDropPartsBehavior
{
public:
    DropTurret01FlipBehavior();
};
EXTERN DropTurret01FlipBehavior dropTurret01FlipBehavior;

// Turret02(CurveShot)
class DropTurret02Behavior : public BaseDropPartsBehavior
{
public:
    DropTurret02Behavior();
};
EXTERN DropTurret02Behavior dropTurret02Behavior;

// Turret02Flip
class DropTurret02FlipBehavior : public BaseDropPartsBehavior
{
public:
    DropTurret02FlipBehavior();
};
EXTERN DropTurret02FlipBehavior dropTurret02FlipBehavior;

//******************************************************************************
// 
//      Shield(防御パーツ)
// 
//******************************************************************************

// Shield01
class DropShield01Behavior : public BaseDropPartsBehavior
{
public:
    DropShield01Behavior();
};
EXTERN DropShield01Behavior dropShield01Behavior;


//******************************************************************************
// 
//      Buff(バフパーツ)
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
//      Trash(ゴミパーツ)
// 
//******************************************************************************

// Trash01
class DropTrash01Behavior : public BaseDropPartsBehavior
{
public:
    DropTrash01Behavior();
};
EXTERN DropTrash01Behavior dropTrash01Behavior;

// Trash02
class DropTrash02Behavior : public BaseDropPartsBehavior
{
public:
    DropTrash02Behavior();
};
EXTERN DropTrash02Behavior dropTrash02Behavior;

// Trash03
class DropTrash03Behavior : public BaseDropPartsBehavior
{
public:
    DropTrash03Behavior();
};
EXTERN DropTrash03Behavior dropTrash03Behavior;


//******************************************************************************
// 
//      Common(効果なしパーツ)
// 
//******************************************************************************

// Common01
class DropCommon01Behavior : public BaseDropPartsBehavior
{
public:
    DropCommon01Behavior();
};
EXTERN DropCommon01Behavior dropCommon01Behavior;

// Common01_2(90度回転)
class DropCommon01_2Behavior : public BaseDropPartsBehavior
{
public:
    DropCommon01_2Behavior();
};
EXTERN DropCommon01_2Behavior dropCommon01_2Behavior;

// Common02
class DropCommon02Behavior : public BaseDropPartsBehavior
{
public:
    DropCommon02Behavior();
};
EXTERN DropCommon02Behavior dropCommon02Behavior;

// Common02_2(90度回転)
class DropCommon02_2Behavior : public BaseDropPartsBehavior
{
public:
    DropCommon02_2Behavior();
};
EXTERN DropCommon02_2Behavior dropCommon02_2Behavior;

// Common03
class DropCommon03Behavior : public BaseDropPartsBehavior
{
public:
    DropCommon03Behavior();
};
EXTERN DropCommon03Behavior dropCommon03Behavior;

// Common03_2(90度回転)
class DropCommon03_2Behavior : public BaseDropPartsBehavior
{
public:
    DropCommon03_2Behavior();
};
EXTERN DropCommon03_2Behavior dropCommon03_2Behavior;

//******************************************************************************
// 
//      erase(消去)
// 
//******************************************************************************
class EraseDropParts : public Eraser
{
    void erase(OBJ2D* obj) const;
};
EXTERN EraseDropParts eraseDropParts;

//******************************************************************************
//      パーツのupdate
//******************************************************************************
extern void DROP_PARTS_UPDATE(OBJ2D* obj);