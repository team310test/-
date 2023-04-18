#pragma once

static constexpr float player_hitBox = 70.0f;
static constexpr float player_size   = 125.0f;

class ActorBehavior : public Behavior
{
protected:
    struct Param
    {
        // �A�j���[�V����
        GameLib::AnimeData* ANIME_WAIT = nullptr;

        // �T�C�Y
        VECTOR2 SIZE = { 0, 0 };
        VECTOR2 SCALE = { 1, 1 };
        GameLib::fRECT HIT_BOX[Collider::boxMax] = {};
        GameLib::fRECT ATTACK_BOX[Collider::boxMax] = {};

        int HP = 1;
        int ATTACK_POWER = 1;

        // ���x�֘A�̃p�����[�^
        float ACCEL_X = 0.0f;
        float ACCEL_Y = 0.0f;
        float SPEED_X_MAX = 0.0f;
        float SPEED_Y_MAX = 0.0f;
        float JUMP_POWER_Y = 0.0f;

        int BOX_NUM = 1;
        Behavior* NEXT_BEHAVIOR = nullptr;
        Eraser* NEXT_ERASER = nullptr;
        
        // �A�j���[�V�����p�p�����[�^
        float ROT_SPEED = 0.0f;
    } param_;

    virtual void moveY(OBJ2D* obj) const;
    virtual void moveX(OBJ2D* obj) const;
    const Param* getParam() const { return &param_; }
private:
    void move(OBJ2D* obj) const override;

    virtual void init(OBJ2D*) const = 0;
    virtual void areaCheck(OBJ2D*) const {}
    virtual void attack(OBJ2D*) const {}

    virtual bool isAlive(OBJ2D*) const = 0;
    virtual void damageProc(OBJ2D*) const {}  // �_���[�W����

    // �A�j���[�V����
    virtual void rotateAnime(OBJ2D*)const override;
    virtual void XscaleAnime(OBJ2D*)const override;

public:
    int getParam_HP() override { return param_.HP; }
};