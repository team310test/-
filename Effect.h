#pragma once


//******************************************************************************
// 
//      AddEffect�i�G�t�F�N�g��ǉ�����N���X�j
// 
//******************************************************************************
class AddEffect
{
public:
    // �G�t�F�N�g�ǉ�
    template <typename T>
    inline static void addEffect(const OBJ2D* obj, T* behavior)
    {
        const VECTOR2 pos = obj->transform_->position_;

        OBJ2D* effect = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg_,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                new EffectComponent
            ),
            behavior,
            pos
        );

        effect->zOrder_ = 10;
        effect->transform_->scale_ = obj->transform_->scale_;
    }
};


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

    virtual void update(OBJ2D* obj) const = 0;
};


//******************************************************************************
//      EffectBombBehavior�i�����G�t�F�N�g�j
//******************************************************************************
class EffectBombBehavior : public BaseEffectBehavior
{
public:
    EffectBombBehavior();

private:
    void update(OBJ2D* obj) const override;
};
EXTERN EffectBombBehavior efcBombBehavior;