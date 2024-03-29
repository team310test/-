#pragma once


class ActorBehavior : public Behavior
{
protected:
    struct Param
    {
        // アニメーション
        GameLib::AnimeData* ANIME_WAIT = nullptr;

        // サイズ
        VECTOR2 SIZE = { 0, 0 };
        VECTOR2 SCALE = { 1, 1 };
        GameLib::fRECT HIT_BOX[Collider::boxMax] = {};
        GameLib::fRECT ATTACK_BOX[Collider::boxMax] = {};

        int HP = 1;
        int NEXT_HP = 1;
        int ATTACK_POWER = 1;

        int BOX_NUM = 1;
        Behavior* NEXT_BEHAVIOR = nullptr;
        Eraser* NEXT_ERASER = nullptr;
        float ROTATION = 0.0f;

        // アニメーション用パラメータ
        OBJ_DATA OBJ_ANIME = nullptr;
        float ROT_SPEED = 0.0f;

    } param_;
    const Param* getParam() const { return &param_; }

private:
    void move(OBJ2D* obj) const override;

    virtual void init(OBJ2D*) const = 0;
    virtual void areaCheck(OBJ2D*) const {}
    virtual void attack(OBJ2D*) const {}

    virtual bool isAlive(OBJ2D*) const = 0;
    virtual void damageProc(OBJ2D*) const {}  // ダメージ処理
};