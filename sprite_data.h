#pragma once

//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

#include "../GameLib/texture.h"

// ラベル定義
enum TEXNO
{
    // ゲーム
    PLAYER,
    PLAYERT,
    PLAYER2,
    PLAYER3,
    BACK,
    ENEMY,
    SHOT,
    CORE01,
    TURRET01,
    TRASH01,
};

extern GameLib::LoadTexture loadTexture[];

//------< テスト >----------------------------------------------------------------
extern GameLib::SpriteData sprEnemey_test;

//------< パーツ >----------------------------------------------------------------
extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsCore01;
extern GameLib::SpriteData sprPartsTrash01;

//------< 球 >----------------------------------------------------------------
extern GameLib::SpriteData sprWeapon_NormalShot;

//******************************************************************************
