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
    { TEXNO::SHOT,      L"./Data/Images/Bullet01.png", 1U }, 
    //{TEXNO::TURRET01, L"./Data/Images/Lzi250.png",     1U },        // パーツ01(L字)
    //{TEXNO::CORE01,   L"./Data/Images/core.png",       1U },        // パーツ01(L字)
    {TEXNO::PL_CORE01,  L"./Data/Images/Core01.png",   1U },    
    {TEXNO::ENM_CORE01, L"./Data/Images/Turret02.png", 1U }, 
    {TEXNO::TURRET01,   L"./Data/Images/Turret01.png", 1U },     
    {TEXNO::BUFF01,     L"./Data/Images/Trash01.png",  1U },        

    { -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心


//------< テスト >------------------------------------------------------------------
GameLib::SpriteData sprPlayerCore01 = SPRITE_CENTER(TEXNO::PL_CORE01, 0, 0, 250, 250);

//------< パーツ >------------------------------------------------------------------
GameLib::SpriteData sprPartsCore01   = SPRITE_CENTER(TEXNO::ENM_CORE01, 0, 0, 250,250 );
GameLib::SpriteData sprPartsTurret01 = SPRITE_CENTER(TEXNO::TURRET01, 0, 0, 250,250 );
GameLib::SpriteData sprPartsBuff01   = SPRITE_CENTER(TEXNO::BUFF01, 0, 0, 250,250 );

//------< ショット >----------------------------------------------------------------
GameLib::SpriteData sprShot_NormalShot = SPRITE_CENTER(TEXNO::SHOT, 0, 0, 100, 100);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
