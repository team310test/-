#include "all.h"

// 2D画像ロードデータ
// （1つのLoadTexture配列に画像を詰め込みすぎるとバグが生じやすくなるので読み込む画像をシーンごとに分けます）

// タイトル画像データ
GameLib::LoadTexture titleLoadTexture[] = {
    { TITLE_TEXNO::TITLE_HEART,     L"./Data/Images/Core/Core_Heart.png",   1U }, // プレイヤーコアのハート
    { TITLE_TEXNO::TITLE_FRAME,     L"./Data/Images/Core/Core_Frame.png",   1U }, // プレイヤーコアの枠
                                                                                   
    { TITLE_TEXNO::TITLE_LOGO,      L"./Data/Images/UI/title_logo.png",     1U }, // ロゴ
    { TITLE_TEXNO::TITLE_TRASH_BOX, L"./Data/Images/UI/title_trash.png",    1U }, // ゴミ箱 
    { TITLE_TEXNO::TITLE_USER,      L"./Data/Images/UI/title_user.png",     1U }, // 操作方法

    { TITLE_TEXNO::TITLE_PL_CORE01, L"./Data/Images/Core/PlayerCore01.png",  1U }, // プレイヤーコア

    
    { -1, nullptr }	// 終了フラグ
};

// ゲーム画像データ
GameLib::LoadTexture gameLoadTexture[] = {
    // 背景
    { GAME_TEXNO::BACK01,    L"./Data/Images/BackGround/BackGround01.png", 1U },
    { GAME_TEXNO::BACK02,    L"./Data/Images/BackGround/BackGround02.png", 1U },

    // UI
    { GAME_TEXNO::UI_METER_FRAME,    L"./Data/Images/UI/Meter_Frame.png",    1U },   // 計器の枠
    { GAME_TEXNO::UI_METER_READ,     L"./Data/Images/UI/Meter_Read.png",     1U },   // 計器の目盛り
    { GAME_TEXNO::UI_METER_NEEDLE,   L"./Data/Images/UI/Meter_Needle.png",   1U },   // 計器の針

    // コア
    { GAME_TEXNO::PL_CORE01,  L"./Data/Images/Core/PlayerCore01.png", 1U },
    { GAME_TEXNO::ENM_CORE01, L"./Data/Images/Core/EnemyCore01.png",  1U },

    // 攻撃パーツ
    { GAME_TEXNO::TURRET01,  L"./Data/Images/Parts/Turret/Turret01.png", 1U },
    { GAME_TEXNO::TURRET02,  L"./Data/Images/Parts/Turret/Turret02.png", 1U },
    { GAME_TEXNO::TURRET03,  L"./Data/Images/Parts/Turret/Turret03.png", 1U },
    // バフパーツ
    { GAME_TEXNO::BUFF01,    L"./Data/Images/Parts/Buff/Buff01.png",     1U },
    // ごみパーツ
    { GAME_TEXNO::TRASH01,   L"./Data/Images/Parts/Trash/Trash01.png",   1U },

    // 弾
    { GAME_TEXNO::BULLET01,  L"./Data/Images/Bullet/Bullet01.png",   1U },

    // エフェクト
    { GAME_TEXNO::EFC_BOMB,      L"./Data/Images/Effect/Effect_Bomb.png",    1U },
    { GAME_TEXNO::EFC_COMBINE,   L"./Data/Images/Effect/Effect_Combine.png", 1U },


    { -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心


////////////////////////// タイトル /////////////////////////////////////////////////////////////////

GameLib::SpriteData sprTitleCoreHeart   = SPRITE_CENTER(TITLE_TEXNO::TITLE_HEART,     0, 0, 128, 128);
GameLib::SpriteData sprTitleCoreFrame   = SPRITE_CENTER(TITLE_TEXNO::TITLE_FRAME,     0, 0, 128, 128);
GameLib::SpriteData sprTitleLogo        = SPRITE_CENTER(TITLE_TEXNO::TITLE_LOGO,      0, 0, 640, 128);
GameLib::SpriteData sprTitleTrashBox    = SPRITE_CENTER(TITLE_TEXNO::TITLE_TRASH_BOX, 0, 0, 128, 128);
GameLib::SpriteData sprTitleUser        = SPRITE_CENTER(TITLE_TEXNO::TITLE_USER,      0, 0, 640, 128);

////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////// ゲーム //////////////////////////////////////////////////////////////////

//------< コア>------------------------------------------------------------------
GameLib::SpriteData sprPlayerCore01 = SPRITE_CENTER(GAME_TEXNO::PL_CORE01,   0, 0, 128, 128);
GameLib::SpriteData sprEnemyCore01  = SPRITE_CENTER(GAME_TEXNO::ENM_CORE01,  0, 0, 128, 128);

//------< パーツ >------------------------------------------------------------------
GameLib::SpriteData sprPartsTurret01 = SPRITE_CENTER(GAME_TEXNO::TURRET01,   0, 0, 128, 128);
GameLib::SpriteData sprPartsTurret02 = SPRITE_CENTER(GAME_TEXNO::TURRET02,   0, 0, 128, 128);
GameLib::SpriteData sprPartsTurret03 = SPRITE_CENTER(GAME_TEXNO::TURRET03,   0, 0, 128, 128);
GameLib::SpriteData sprPartsBuff01   = SPRITE_CENTER(GAME_TEXNO::BUFF01,     0, 0, 250, 250);
GameLib::SpriteData sprPartsTrash01  = SPRITE_CENTER(GAME_TEXNO::TRASH01,    0, 0, 128, 128);

//------< 弾 >----------------------------------------------------------------
GameLib::SpriteData sprShot_NormalShot  = SPRITE_CENTER(GAME_TEXNO::BULLET01, 0, 0, 64, 64);

//------< エフェクト >----------------------------------------------------------------

// 爆発エフェクト
GameLib::SpriteData sprEfcBomb_anime0       = SPRITE_CENTER(GAME_TEXNO::EFC_BOMB, (256 * 0), 0, 256, 256);
GameLib::SpriteData sprEfcBomb_anime1       = SPRITE_CENTER(GAME_TEXNO::EFC_BOMB, (256 * 1), 0, 256, 256);
GameLib::SpriteData sprEfcBomb_anime2       = SPRITE_CENTER(GAME_TEXNO::EFC_BOMB, (256 * 2), 0, 256, 256);
GameLib::SpriteData sprEfcBomb_anime3       = SPRITE_CENTER(GAME_TEXNO::EFC_BOMB, (256 * 3), 0, 256, 256);

// 合体エフェクト
GameLib::SpriteData sprEfcCombine_anime0    = SPRITE_CENTER(GAME_TEXNO::EFC_COMBINE, (256 * 0), 0, 256, 256);
GameLib::SpriteData sprEfcCombine_anime1    = SPRITE_CENTER(GAME_TEXNO::EFC_COMBINE, (256 * 1), 0, 256, 256);
GameLib::SpriteData sprEfcCombine_anime2    = SPRITE_CENTER(GAME_TEXNO::EFC_COMBINE, (256 * 2), 0, 256, 256);
GameLib::SpriteData sprEfcCombine_anime3    = SPRITE_CENTER(GAME_TEXNO::EFC_COMBINE, (256 * 3), 0, 256, 256);

////////////////////////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
