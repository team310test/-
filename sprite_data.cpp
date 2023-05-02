#include "all.h"

// 2D画像ロードデータ
GameLib::LoadTexture loadTexture[] = {
    // 背景
    { TEXNO::BACK01,    L"./Data/Images/BackGround/BackGround01.png", 1U },
    { TEXNO::BACK02,    L"./Data/Images/BackGround/BackGround02.png", 1U },
    // UI
    { TEXNO::UI_METER_FRAME,    L"./Data/Images/UI/Meter_Frame.png",    1U },   // 計器の枠
    { TEXNO::UI_METER_READ,     L"./Data/Images/UI/Meter_Read.png",     1U },   // 計器の目盛り
    { TEXNO::UI_METER_NEEDLE,   L"./Data/Images/UI/Meter_Needle.png",   1U },   // 計器の針

    // コア
    { TEXNO::PL_CORE01,  L"./Data/Images/Core/PlayerCore01.png", 1U },
    { TEXNO::ENM_CORE01, L"./Data/Images/Core/EnemyCore01.png",  1U },

    // 攻撃パーツ
    { TEXNO::TURRET01,  L"./Data/Images/Parts/Turret/Turret01.png", 1U },
    { TEXNO::TURRET02,  L"./Data/Images/Parts/Turret/Turret02.png", 1U },
    { TEXNO::TURRET03,  L"./Data/Images/Parts/Turret/Turret03.png", 1U },
    // バフパーツ
    { TEXNO::BUFF01,    L"./Data/Images/Parts/Buff/Buff01.png",     1U },
    // ごみパーツ
    { TEXNO::TRASH01,   L"./Data/Images/Parts/Trash/Trash01.png",   1U },


    // 弾
    { TEXNO::BULLET01,  L"./Data/Images/Bullet/Bullet01.png",   1U },

    // エフェクト
    { TEXNO::EFC_BOMB,  L"./Data/Images/Effect/Effect_Bomb.png", 1U },
    

    { -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心

//------< コア>------------------------------------------------------------------
GameLib::SpriteData sprPlayerCore01 = SPRITE_CENTER(TEXNO::PL_CORE01,   0, 0, 128, 128);
GameLib::SpriteData sprEnemyCore01  = SPRITE_CENTER(TEXNO::ENM_CORE01,  0, 0, 128, 128);

//------< パーツ >------------------------------------------------------------------
GameLib::SpriteData sprPartsTurret01 = SPRITE_CENTER(TEXNO::TURRET01,   0, 0, 128, 128);
GameLib::SpriteData sprPartsTurret02 = SPRITE_CENTER(TEXNO::TURRET02,   0, 0, 128, 128);
GameLib::SpriteData sprPartsTurret03 = SPRITE_CENTER(TEXNO::TURRET03,   0, 0, 128, 128);
GameLib::SpriteData sprPartsBuff01   = SPRITE_CENTER(TEXNO::BUFF01,     0, 0, 250, 250);
GameLib::SpriteData sprPartsTrash01  = SPRITE_CENTER(TEXNO::TRASH01,    0, 0, 128, 128);

//------< 弾 >----------------------------------------------------------------
GameLib::SpriteData sprShot_NormalShot  = SPRITE_CENTER(TEXNO::BULLET01, 0, 0, 64, 64);

//------< エフェクト >----------------------------------------------------------------
GameLib::SpriteData sprEfcBomb_anime0   = SPRITE_CENTER(TEXNO::EFC_BOMB, (256 * 0), 0, 256, 256);
GameLib::SpriteData sprEfcBomb_anime1   = SPRITE_CENTER(TEXNO::EFC_BOMB, (256 * 1), 0, 256, 256);
GameLib::SpriteData sprEfcBomb_anime2   = SPRITE_CENTER(TEXNO::EFC_BOMB, (256 * 2), 0, 256, 256);
GameLib::SpriteData sprEfcBomb_anime3   = SPRITE_CENTER(TEXNO::EFC_BOMB, (256 * 3), 0, 256, 256);


//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
