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
    { TEXNO::PLAYER,      L"./Data/Images/player.png",    1U },// プレイヤー(仮)
    //{ TEXNO::PLAYERT,      L"./Data/Images/player(test).png",    1U },// プレイヤー(仮)
    { TEXNO::PLAYER2,      L"./Data/Images/Weapon1.png",    1U },// 250*250
    { TEXNO::SHOT,        L"./Data/Images/weapon.png",    1U },// ショット(仮)
    //{ TEXNO::ENEMY,        L"./Data/Images/enemy(test).png",    1U },// エネミー(仮)
    {TEXNO::TURRET01,    L"./Data/Images/Lzi250.png",    1U},        // パーツ01(Lzi)
    {TEXNO::CORE01,    L"./Data/Images/core.png",    1U},        // パーツ01(Lzi)
    { -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心


//------< テスト >------------------------------------------------------------------
GameLib::SpriteData sprEnemey_test = SPRITE_CENTER(TEXNO::PLAYER2, 0, 0, 250, 250);

//------< パーツ >------------------------------------------------------------------
GameLib::SpriteData sprPartsCore01 = SPRITE_CENTER(TEXNO::CORE01, 0, 0, 250,250 );
GameLib::SpriteData sprPartsTurret01 = SPRITE_CENTER(TEXNO::TURRET01, 0, 0, 250,250 );

//------< ショット >----------------------------------------------------------------
GameLib::SpriteData sprWeapon_NormalShot = SPRITE_CENTER(TEXNO::SHOT, 128 * 4, 0, 128, 128);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
