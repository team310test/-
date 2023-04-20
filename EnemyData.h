#pragma once
//******************************************************************************
//
//
//		EnemyData
//
//
//******************************************************************************

class EnemyData
{
public:
    BaseEnemyBehavior* behavior_;
    VECTOR2 pos_;
    int zOrder_;

    EnemyData(BaseEnemyBehavior* behavior, VECTOR2 pos, int zOrder)
        :behavior_(behavior)
        , pos_(pos)
        , zOrder_(zOrder)
    {}
};

#define SET_ENEMY_CORE(behavior,zOrder)		        {(behavior),{0,0},(zOrder)}
#define SET_ENEMY_PARTS(behavior,x,y,zOrder)		{(behavior),VECTOR2(x,y),(zOrder)}
#define SET_ENEMY_END                     		    {(nullptr),VECTOR2(0,0),(0)}

//******************************************************************************
//		DATA
//******************************************************************************
extern EnemyData Enemy01[];
extern EnemyData Enemy02[];