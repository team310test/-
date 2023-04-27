#pragma once

#include "../GameLib/texture.h"

// ラベル定義
enum TEXNO
{
    // ゲーム
    BACK01,
    BACK02,
    UI_METER_FRAME,     // 計器の枠
    //UI_METER_READ,      // 計器の目盛り
    UI_METER_NEEDLE,    // 計器の針
    SHOT,
    PL_CORE01,
    ENM_CORE01,
    ENM_CORE02,
    TURRET01,
    TURRET02,
    TURRET03,
    BUFF01,
    TRASH01,
};

extern GameLib::LoadTexture loadTexture[];


//------< プレイヤー >------------------------------------------------------------------
extern GameLib::SpriteData sprPlayerCore01;

//------< パーツ >------------------------------------------------------------------
extern GameLib::SpriteData sprPartsCore01;
extern GameLib::SpriteData sprPartsCore02;
extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsTurret03;
extern GameLib::SpriteData sprPartsBuff01;
extern GameLib::SpriteData sprPartsTrash01;

//------< 弾 >----------------------------------------------------------------
extern GameLib::SpriteData sprShot_NormalShot;

//******************************************************************************
