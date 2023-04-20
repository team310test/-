//******************************************************************************
//
//
//		StageData
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

EnemyData Enemy01[] =
{
    SET_ENEMY_CORE(&enemyCore01Behavior,0),
    SET_ENEMY_PARTS(&enemyTurret01Behavior,{-64,96},0),
    SET_ENEMY_END
};

EnemyData Enemy02[] =
{
    SET_ENEMY_CORE(&enemyCore01Behavior,0),
    SET_ENEMY_PARTS(&enemyTurret01Behavior,{-128,0},0),
    SET_ENEMY_END
};