//******************************************************************************
//
//
//		StageData
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

// 画面外
#define x BG::WINDOW_W+300

STAGE_SCRIPT stageData[] =
{
    SET_ENEMY_DATA(0,Enemy01,VECTOR2(x,800)),
    //SET_ENEMY_DATA(360,Enemy02,VECTOR2(x,500)),
    //SET_ENEMY_DATA(540,Enemy01,VECTOR2(x,500)),
    //SET_ENEMY_DATA(720,Enemy02,VECTOR2(x,500)),
    SET_ENEMY_DATA_END
};