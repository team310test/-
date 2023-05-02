#pragma once


//******************************************************************************
// 
//      AddEffect（エフェクトを追加するクラス）
// 
//******************************************************************************
class AddEffect
{
public:
    // エフェクト追加
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
//      BaseEffectBehavior（エフェクトのベース）
//
//******************************************************************************
class BaseEffectBehavior : public Behavior
{
protected:
    struct Param
    {
        GameLib::AnimeData* ANIME;    // スプライト
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
//      EffectBombBehavior（爆発エフェクト）
//******************************************************************************
class EffectBombBehavior : public BaseEffectBehavior
{
public:
    EffectBombBehavior();

private:
    void update(OBJ2D* obj) const override;
};
EXTERN EffectBombBehavior efcBombBehavior;