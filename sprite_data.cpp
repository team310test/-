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

    { -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心

//------< プレイヤー >----------------------------------------------------------
//上歩き
GameLib::SpriteData sprPlayer_Up0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 0, 96, 128);
GameLib::SpriteData sprPlayer_Up1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 0, 96, 128);
GameLib::SpriteData sprPlayer_Up2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 0, 96, 128);

//右歩き
GameLib::SpriteData sprPlayer_Right0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 1, 96, 128);
GameLib::SpriteData sprPlayer_Right1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 1, 96, 128);
GameLib::SpriteData sprPlayer_Right2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 1, 96, 128);

//下歩き
GameLib::SpriteData sprPlayer_Down0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 2, 96, 128);
GameLib::SpriteData sprPlayer_Down1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 2, 96, 128);
GameLib::SpriteData sprPlayer_Down2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 2, 96, 128);

//左歩き
GameLib::SpriteData sprPlayer_Left0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 3, 96, 128);
GameLib::SpriteData sprPlayer_Left1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 3, 96, 128);
GameLib::SpriteData sprPlayer_Left2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 3, 96, 128);

//GameLib::SpriteData sprPlayer_test = SPRITE_BOTTOM(TEXNO::PLAYERT,64 * 0, 128 * 0, 128, 128);

//------< アイテム >-------------------------------------------------------------

//------< 敵 >------------------------------------------------------------------
//GameLib::SpriteData sprEnemey_test = SPRITE_BOTTOM(TEXNO::ENEMY, 0, 0, 128, 128);
//GameLib::SpriteData sprEnemey_test = SPRITE_BOTTOM(TEXNO::PLAYER2, 0, 0, 250, 250);
GameLib::SpriteData sprEnemey_test = SPRITE_CENTER(TEXNO::PLAYER2, 0, 0, 250, 250);

//------< ショット >----------------------------------------------------------------
GameLib::SpriteData sprWeapon_Sword = SPRITE_BOTTOM(TEXNO::SHOT, 128 * 0, 0, 128, 128);
GameLib::SpriteData sprWeapon_Shuriken = SPRITE_CENTER(TEXNO::SHOT, 128 * 4, 0, 128, 128);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
