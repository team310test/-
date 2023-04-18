#pragma once


//******************************************************************************
//
//      BaseShotBehavior（弾のベース）
//
//******************************************************************************

class BaseShotBehavior : public Behavior
{
protected:
    struct Param
    {
        GameLib::SpriteData*    SPR_WEAPON;     // スプライト
        Eraser*                 ERASER;         // イレイサー（削除用のアルゴリズム）
        float                   SPEED_X;        // 横方向の速度（手裏剣用）
        float                   ROT_SPEED;      // 回転速度（手裏剣用）
        int                     ATTACK_POWER;   // 攻撃力
        //GameLib::fRECT          ATTACK_BOX;     // 攻撃用あたり領域
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
    virtual void calcAttackBox(OBJ2D* obj) const; // 攻撃用あたり領域の計算（縮小に伴って弾の大きさの更新が必要）
};


//******************************************************************************
//
//      Base{Player・Enemy}ShotBehavior（プレイヤーとエネミーの弾のベース）
//
//******************************************************************************

// プレイヤーの攻撃タイプだけ所有
class BasePlayerShotBehavior : public BaseShotBehavior 
{
private:
    virtual void update(OBJ2D* obj) const = 0;
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ENEMY; };
};
// エネミーの攻撃タイプだけ所有
class BaseEnemyShotBehavior : public BaseShotBehavior 
{
private:
    virtual void update(OBJ2D* obj) const = 0;
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; };
};


//******************************************************************************
//
//      NormalShotBehavior（通常弾）
//
//******************************************************************************

// プレイヤー
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
//      SinShotBehavior（波形移動弾）
//
//******************************************************************************

// プレイヤー
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
