#pragma once


//******************************************************************************
//
//      BaseShotBehavior�i�e�̃x�[�X�j
//
//******************************************************************************

class BaseShotBehavior : public Behavior
{
protected:
    struct Param
    {
        GameLib::SpriteData*    SPR_WEAPON;     // �X�v���C�g
        Eraser*                 ERASER;         // �C���C�T�[�i�폜�p�̃A���S���Y���j
        float                   SPEED_X;        // �������̑��x�i�藠���p�j
        float                   ROT_SPEED;      // ��]���x�i�藠���p�j
        int                     ATTACK_POWER;   // �U����
        //GameLib::fRECT          ATTACK_BOX;     // �U���p������̈�
        GameLib::fRECT ATTACK_BOX[Collider::boxMax];
        GameLib::fRECT HIT_BOX[Collider::boxMax];

    } param_ = {};

protected:
    const Param* getParam() const { return &param_; }

private:
    void move(OBJ2D* obj) const override;
    OBJ_TYPE getType() const override { return OBJ_TYPE::SHOT; }
    OBJ_TYPE getAttackType() const override = 0; 
    void hit(OBJ2D* src, OBJ2D* dst) const override;

    virtual void update(OBJ2D* obj) const = 0;
    virtual void calcAttackBox(OBJ2D* obj) const; // �U���p������̈�̌v�Z�i�k���ɔ����Ēe�̑傫���̍X�V���K�v�j
};


//******************************************************************************
//
//      Base{Player�EEnemy}ShotBehavior�i�v���C���[�ƃG�l�~�[�̒e�̃x�[�X�j
//
//******************************************************************************

// �v���C���[�̍U���^�C�v�������L
class BasePlayerShotBehavior : public BaseShotBehavior 
{
private:
    virtual void update(OBJ2D* obj) const = 0;
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ENEMY; };
};
// �G�l�~�[�̍U���^�C�v�������L
class BaseEnemyShotBehavior : public BaseShotBehavior 
{
private:
    virtual void update(OBJ2D* obj) const = 0;
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; };
};


//******************************************************************************
//
//      NormalShotBehavior�i�ʏ�e�j
//
//******************************************************************************

// �v���C���[
class PlayerNormalShotBehavior : public BasePlayerShotBehavior
{
public:
    PlayerNormalShotBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN PlayerNormalShotBehavior playerNormalShotBehavior;


//******************************************************************************
//
//      SinShotBehavior�i�g�`�ړ��e�j
//
//******************************************************************************

// �v���C���[
class PlayerWaveShotBehavior : public BasePlayerShotBehavior
{
public:
    PlayerWaveShotBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN PlayerWaveShotBehavior playerWaveShotBehavior;


//class EnemyNormalShotBehavior : public BaseShotBehavior
//{
//public:
//    EnemyNormalShotBehavior();
//private:
//    void update(OBJ2D* obj) const override;
//    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; };
//};
//EXTERN EnemyNormalShotBehavior enemyNormalShotBehavior;




class ShotEraser : public Eraser
{
private:
    void erase(OBJ2D* obj) const override;
};
EXTERN ShotEraser eraseShot;
