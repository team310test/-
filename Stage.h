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
    EnemyData* enemyData_;
    VECTOR2 pos_;

    STAGE_SCRIPT(int time, EnemyData* enemyData, VECTOR2 pos)
        :time_(time)
        , enemyData_(enemyData)
        , pos_(pos)
    {}
};

#define SET_ENEMY_DATA(time,enemyData,pos)		{(time),(enemyData),(pos)}
#define SET_ENEMY_DATA_END                     	{(0),(nullptr),{0,0}}

class Stage
{
private:
    int timer;
    STAGE_SCRIPT* pScript;
public:
    Stage();
    void update();
};