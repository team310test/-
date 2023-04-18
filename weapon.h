#pragma once

class BaseWeaponBehavior : public Behavior
{
protected:
    struct Param
    {
        GameLib::SpriteData*    SPR_WEAPON;     // �X�v���C�g
        Eraser*                 ERASER;         // �C���C�T�[�i�폜�p�̃A���S���Y���j
        float                   SPEED_X;        // �������̑��x�i�藠���p�j
        float                   ROT_SPEED;      // ��]���x�i�藠���p�j
        int                     ATTACK_POWER;   // �U����
        VECTOR2                 SCALE;          // �X�P�[��
        GameLib::fRECT          ATTACK_BOX;     // �U���p������̈�
    } param_ = {};

protected:
    const Param* getParam() const { return &param_; }
private:
    void move(OBJ2D* obj) const override;
    virtual void update(OBJ2D* obj) const = 0;
    virtual void calcAttackBox(OBJ2D* obj) const = 0; // �U���p������̈�̌v�Z
    OBJ_TYPE getType() const override { return OBJ_TYPE::WEAPON; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ENEMY; }
};

//----------------------------------------------------------------------
//  PlayerNormalShotBehavior
//----------------------------------------------------------------------
class PlayerNormalShotBehavior : public BaseWeaponBehavior
{
public:
    PlayerNormalShotBehavior();
private:
    void update(OBJ2D* obj) const override;
    void calcAttackBox(OBJ2D* obj) const override;
    void hit(OBJ2D* src, OBJ2D* dst) const override;
};
EXTERN PlayerNormalShotBehavior playerNormalShotBehavior;

//----------------------------------------------------------------------
//  PlayerNormalShotBehavior
//----------------------------------------------------------------------
class EnemyNormalShotBehavior : public PlayerNormalShotBehavior
{
public:
    EnemyNormalShotBehavior();
private:
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; }
};
EXTERN EnemyNormalShotBehavior enemyNormalShotBehavior;

//----------------------------------------------------------------------
//  Eraser
//----------------------------------------------------------------------
class NormalShotEraser : public Eraser
{
private:
    void erase(OBJ2D* obj) const override;
};
EXTERN NormalShotEraser normalShotEraser;
