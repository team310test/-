#pragma once

class Quake
{
private:
    static constexpr float ADD_QUAKE_POS = 10;
    static const     int   LOOP_MAX      = 3;

private:
    int state_ = 0;
    int loop_  = 0;

public:
    void quakeDamage(OBJ2D* obj); // �_���[�W���󂯂����̗h��鉉�o���s��
};

