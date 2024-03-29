#pragma once

class Stage
{
public:
    static constexpr float ENEMY_SPAWN_POS_X = (BG::WINDOW_W + 256.0f);
    static const int STAGE_MAX = 6;

private:
    int timer_;
    STAGE_SCRIPT* pScript_;
    int stageNum_;

private:
    static int shrinkNum_;

public:
    Stage();
    void update(OBJ2DManager* obj2dManager, BG* bg);

    static void resetShrinkNum() { shrinkNum_ = 0; } // 縮小回数リセット

    static int getSrinkNum()    { return shrinkNum_; }
    static void addSrinkNum()   { ++shrinkNum_; }
};