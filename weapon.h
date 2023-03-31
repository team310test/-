#pragma once

class BaseWeaponBehavior : public Behavior
{
protected:
    struct Param
    {
        GameLib::SpriteData*    SPR_WEAPON;     // スプライト
        Eraser*                 ERASER;         // イレイサー（削除用のアルゴリズム）
        float                   SPEED_X;        // 横方向の速度（手裏剣用）
        float                   ROT_SPEED;      // 回転速度（手裏剣用）
        int                     ATTACK_POWER;   // 攻撃力
        VECTOR2                 SCALE;          // スケール
        GameLib::fRECT          ATTACK_BOX;     // 攻撃用あたり領域
    } param_ = {};

protected:
    const Param* getParam() const { return &param_; }
private:
    void move(OBJ2D* obj) const override;
    virtual void update(OBJ2D* obj) const = 0;
    virtual void calcAttackBox(OBJ2D* obj) const = 0; // 攻撃用あたり領域の計算
    OBJ_TYPE getType() const override { return OBJ_TYPE::WEAPON; }
    OBJ_TYPE getAttackType() const override { return OBJ_TYPE::ENEMY; }
};

//----------------------------------------------------------------------
//  ShurikenBehavior
//----------------------------------------------------------------------
class ShurikenBehavior : public BaseWeaponBehavior
{
public:
    ShurikenBehavior();
private:
    void update(OBJ2D* obj) const override;
    void calcAttackBox(OBJ2D* obj) const override;
    void hit(OBJ2D* src, OBJ2D* dst) const override;
};
EXTERN ShurikenBehavior shurikenBehavior;

class ShurikenEraser : public Eraser
{
private:
    void erase(OBJ2D* obj) const override;
};
EXTERN ShurikenEraser shurikenEraser;

class SwordBehavior : public BaseWeaponBehavior
{
public:
    SwordBehavior();

private:
    void update(OBJ2D* obj) const override;
    void calcAttackBox(OBJ2D* obj) const override;
    void hit(OBJ2D* src, OBJ2D* dst) const override;
};
EXTERN SwordBehavior swordBehavior;

class SwordEraser : public Eraser
{
private:
    void erase(OBJ2D* obj) const override;
};
EXTERN SwordEraser swordEraser;
