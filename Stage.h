#pragma once

class Stage
{
public:
    static constexpr float ENEMY_SPAWN_POS_X = (BG::WINDOW_W + 256.0f);

private:
    int timer_;
    STAGE_SCRIPT* pScript_;

    static const int stageMax = 2;
    int stageNum_;
    static int shrinkNum_;

public:
    Stage();
    void update(OBJ2DManager* obj2dManager, BG* bg);
    static int getSrinkNum() { return shrinkNum_; }
    static void addSrinkNum() { ++shrinkNum_; }
};