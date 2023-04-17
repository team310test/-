//******************************************************************************
//
//
//		StageData
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

#define x BG::WINDOW_W+300

STAGE_SCRIPT stageData[] =
{
    SET_ENEMY(180,&enemyCore01Behavior,VECTOR2(x,800)),
    SET_ENEMY(360,&enemyCore01Behavior,VECTOR2(x,500)),
    SET_ENEMY(540,&enemyCore01Behavior,VECTOR2(x,500)),
    SET_ENEMY(720,&enemyCore01Behavior,VECTOR2(x,500)),
    SET_END
};