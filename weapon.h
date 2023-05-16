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
        float                   SPEED_Y;        // �������̑��x�i�藠���p�j
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
//      NormalShot�i�ʏ�e�j
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
EXTERN PlayerNormalShotBehavior plNormalShotBehavior;

// �G�l�~�[
class EnmNormalShotBehavior : public BaseEnemyShotBehavior
{
public:
    EnmNormalShotBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN EnmNormalShotBehavior enmNormalShotBehavior;


//******************************************************************************
//
//      SineWaveShot�i�����g�e�j
//
//******************************************************************************

// �v���C���[
class PlSineWaveShotBehavior : public BasePlayerShotBehavior
{
public:
    PlSineWaveShotBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN PlSineWaveShotBehavior plSineWaveShotBehavior;


//******************************************************************************
//
//      SquareWaveShot�i��`�g�e�j
//
//******************************************************************************

// �v���C���[
class PlSquareWaveShotBehavior : public BasePlayerShotBehavior
{
public:
    PlSquareWaveShotBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN PlSquareWaveShotBehavior plSquareWaveShotBehavior;


//******************************************************************************
//
//      CurveShot�i�J�[�u�e�j
//
//******************************************************************************

// �v���C���[
class PlCurveShotBehavior : public BasePlayerShotBehavior
{
public:
    PlCurveShotBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN PlCurveShotBehavior plCurveShotBehavior;

// �v���C���[(Y�����])
class PlCurveShotFlipBehavior : public BasePlayerShotBehavior
{
public:
    PlCurveShotFlipBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN PlCurveShotFlipBehavior plCurveShotFlipBehavior;

// �G�l�~�[
class EnmCurveShotBehavior : public BaseEnemyShotBehavior
{
public:
    EnmCurveShotBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN EnmCurveShotBehavior enmCurveShotBehavior;

// �G�l�~�[(Y�����])
class EnmCurveShotFlirpBehavior : public BaseEnemyShotBehavior
{
public:
    EnmCurveShotFlirpBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN EnmCurveShotFlirpBehavior enmCurveShotFlipBehavior;


//******************************************************************************
//
//      PenetrateShot�i�ђʒe�j
//
//******************************************************************************

// �v���C���[
class PlPenetrateShotBehavior : public BasePlayerShotBehavior
{
public:
    PlPenetrateShotBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN PlPenetrateShotBehavior plPenetrateShotBehavior;

// �G�l�~�[
class EnmPenetrateShotBehavior : public BaseEnemyShotBehavior
{
public:
    EnmPenetrateShotBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN EnmPenetrateShotBehavior enmPenetrateShotBehavior;


//******************************************************************************
//
//      AimShot�i�v���C���[�_���e�j
//
//******************************************************************************

// �G�l�~�[
class EnmAimShotBehavior : public BaseEnemyShotBehavior
{
public:
    EnmAimShotBehavior();
private:
    void update(OBJ2D* obj) const override;
};
EXTERN EnmAimShotBehavior enmAimShotBehavior;



//******************************************************************************
//
//      erase�i�����j
//
//******************************************************************************
// �v���C���[
class PlShotEraser : public Eraser
{
private:
    void erase(OBJ2D* obj) const override;
};
EXTERN PlShotEraser plShotEraser;

// �G�l�~�[
class EnmShotEraser : public Eraser
{
private:
    void erase(OBJ2D* obj) const override;
};
EXTERN EnmShotEraser enmShotEraser;