#pragma once

#include "../GameLib/texture.h"

// ラベル定義
enum TEXNO
{
    // ゲーム
    BACK01,
    BACK02,
    ENEMY,
    SHOT,
    PL_CORE01,
    ENM_CORE01,
    TURRET01,
    BUFF01,
};

extern GameLib::LoadTexture loadTexture[];

//------< プレイヤー >----------------------------------------------------------------
extern GameLib::SpriteData sprPlayerCore01;

//------< パーツ >----------------------------------------------------------------
extern GameLib::SpriteData sprPartsCore01;
extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsBuff01;

//------< 弾 >----------------------------------------------------------------
extern GameLib::SpriteData sprShot_NormalShot;

//******************************************************************************
