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
