#pragma once

//******************************************************************************
//
//      BaseEffectBehavior�i�G�t�F�N�g�̃x�[�X�j
//
//******************************************************************************
class BaseEffectBehavior : public Behavior
{
protected:
    struct Param
    {
        GameLib::AnimeData* ANIME;    // �X�v���C�g
    } param_ = {};

protected:
    const Param* getParam() const { return &param_; }

private:
    void move(OBJ2D* obj) const override;

    OBJ_TYPE getType() const override { return OBJ_TYPE::EFFECT; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::NONE; };

    void startAllShrink(OBJ2D* /*obj*/) const override {}
    void shrink(OBJ2D* /*obj*/) const override {}

protected:
    virtual void update(OBJ2D* obj) const;
};


//******************************************************************************
//      EffectBeatBehavior�i�ۓ��G�t�F�N�g�j
//******************************************************************************
class EffectBeatBehavior : public BaseEffectBehavior
{
public:
    EffectBeatBehavior();
    void update(OBJ2D* obj) const override;
};
EXTERN EffectBeatBehavior efcBeatBehavior;

//******************************************************************************
//      EffectBombBehavior�i�����G�t�F�N�g�j
//******************************************************************************
class EffectBombBehavior : public BaseEffectBehavior
{
public:
    EffectBombBehavior();
};
EXTERN EffectBombBehavior efcBombBehavior;


//******************************************************************************
//      EffectCombineBehavior�i���̃G�t�F�N�g�j
//******************************************************************************
class EffectCombineBehavior : public BaseEffectBehavior
{
public:
    EffectCombineBehavior();
public:
    void update(OBJ2D* obj) const override;
};
EXTERN EffectCombineBehavior efcCombineBehavior;


// �A���I�ɃG�t�F�N�g�𗬂����߂̃f�[�^
class ChainEffectData
{
public:
    int time_;
    Behavior* behavior_;
    VECTOR2 add_;

    ChainEffectData(int time,Behavior* behavior, VECTOR2 add)
        :time_(time)
        , behavior_(behavior)
        , add_(add)
    {}
};


// obj�̎��͂ɃG�t�F�N�g��A���I�ɔ���������֐�
bool ChainEffect(OBJ2D*);