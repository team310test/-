//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"
//------< データ >---------------------------------------------------------------

// 2D画像ロードデータ
GameLib::LoadTexture loadTexture[] = {
    { TEXNO::SHOT,      L"./Data/Images/weapon.png",    1U },// ショット(仮)
    //{TEXNO::TURRET01, L"./Data/Images/Lzi250.png",    1U },        // パーツ01(L字)
    //{TEXNO::CORE01,   L"./Data/Images/core.png",      1U },        // パーツ01(L字)
    {TEXNO::TURRET01,   L"./Data/Images/Weapon1.png",   1U },        // パーツ01(L字)
    {TEXNO::CORE01,     L"./Data/Images/Weapon1.png",   1U },        // パーツ01(L字)

    { -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心


//------< テスト >------------------------------------------------------------------
GameLib::SpriteData sprEnemey_test = SPRITE_CENTER(TEXNO::TURRET01, 0, 0, 250, 250);

//------< パーツ >------------------------------------------------------------------
GameLib::SpriteData sprPartsCore01 = SPRITE_CENTER(TEXNO::CORE01, 0, 0, 250,250 );
GameLib::SpriteData sprPartsTurret01 = SPRITE_CENTER(TEXNO::TURRET01, 0, 0, 250,250 );

//------< ショット >----------------------------------------------------------------
GameLib::SpriteData sprWeapon_NormalShot = SPRITE_CENTER(TEXNO::SHOT, 128 * 4, 0, 128, 128);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
