#pragma once
//******************************************************************************
//
//
//      Stage.h
//
//
//******************************************************************************
class STAGE_SCRIPT
{
public:
    int time_;
    BaseEnemyBehavior* behavior_;
    VECTOR2 pos_;

    STAGE_SCRIPT(int time, BaseEnemyBehavior* behavior, VECTOR2 pos)
        :time_(time)
        , behavior_(behavior)
        , pos_(pos)
    {}
};

#define SET_ENEMY(time,behavior,y)		{(time),(behavior),VECTOR2(BG::WINDOW_W + 200,y)}
#define SET_END                     		{(0),(nullptr),{0,0}}

class Stage
{
private:
    int timer;
    STAGE_SCRIPT* pScript;
public:
    Stage();
    void update();
};