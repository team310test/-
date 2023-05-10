#pragma once

class Quake
{
private:
    int state_ = 0;
    int loop_  = 0;

public:
    void quakeDamage(OBJ2D* obj); // ダメージを受けた時の揺れる演出を行う
};

