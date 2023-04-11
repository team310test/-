#pragma once

static constexpr float player_hitBox = 70.0f;
static constexpr float player_size   = 125.0f;

class ActorBehavior : public Behavior
{
protected:
    struct Param
    {
        // アニメーション
        GameLib::AnimeData* ANIME_UP = nullptr;
        GameLib::AnimeData* ANIME_RIGHT = nullptr;
        GameLib::AnimeData* ANIME_DOWN = nullptr;
        GameLib::AnimeData* ANIME_LEFT = nullptr;

        // サイズ
        VECTOR2 SIZE = { 0, 0 };
        VECTOR2 SCALE = { 1, 1 };
        GameLib::fRECT HIT_BOX = {};
        GameLib::fRECT ATTACK_BOX = {};

        int HP = 1;
        int ATTACK_POWER = 1;

        // 速度関連のパラメータ
        float ACCEL_X = 0.0f;
        float ACCEL_Y = 0.0f;
        float SPEED_X_MAX = 0.0f;
        float SPEED_Y_MAX = 0.0f;
        float JUMP_POWER_Y = 0.0f;
    } param_;
    const Param* getParam() const { return &param_; }

    virtual void moveY(OBJ2D* obj) const;
    virtual void moveX(OBJ2D* obj) const;

private:
    void move(OBJ2D* obj) const override;

    virtual void init(OBJ2D*) const = 0;
    virtual void areaCheck(OBJ2D* obj) const {}
    virtual void attack(OBJ2D*) const {}

    virtual bool isAlive(OBJ2D*) const = 0;
    virtual void damageProc(OBJ2D*) const {}  // ダメージ処理
};