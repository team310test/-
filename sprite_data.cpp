#include "all.h"

// 2D画像ロードデータ
// （1つのLoadTexture配列に画像を詰め込みすぎるとバグが生じやすくなるので読み込む画像をシーンごとに分けます）

// タイトル画像データ
GameLib::LoadTexture titleLoadTexture[] = {
    { TITLE_TEXNO::TITLE_PLAYER,     L"./Data/Images/Core/PlayerCore01.png",   1U }, // プレイヤーコア
    { TITLE_TEXNO::TITLE_HEART,      L"./Data/Images/Core/Core_Heart.png",     1U }, // プレイヤーコアのハート
    { TITLE_TEXNO::TITLE_FRAME,      L"./Data/Images/Core/Core_Frame.png",     1U }, // プレイヤーコアの枠
                                                                                     
    { TITLE_TEXNO::TITLE_LOGO,       L"./Data/Images/UI/title_logo.png",       1U }, // ロゴ
    { TITLE_TEXNO::TITLE_TRASH_BOX,  L"./Data/Images/UI/Title_TrashBox.png",   1U }, // ゴミ箱 
    { TITLE_TEXNO::TITLE_USER_MOVE,  L"./Data/Images/UI/Title_User_Move.png",  1U }, // 操作方法WASD→←↓→
    { TITLE_TEXNO::TITLE_USER_SPACE, L"./Data/Images/UI/Title_User_Space.png", 1U }, // 操作方法Space

    { TITLE_TEXNO::TITLE_TEXT_START, L"./Data/Images/UI/Title_Text_Start.png", 1U }, // Start
    { TITLE_TEXNO::TITLE_TEXT_EXIT,  L"./Data/Images/UI/Title_Text_Exit.png",  1U }, // Exit
    
    { -1, nullptr }	// 終了フラグ
};

// ゲーム画像データ
GameLib::LoadTexture gameLoadTexture[] = {
    // 背景
    { GAME_TEXNO::BG01, L"./Data/Images/BackGround/BackGround01.png",   1U },
    { GAME_TEXNO::BG02, L"./Data/Images/BackGround/BackGround02.png",   1U },
    { GAME_TEXNO::BG03, L"./Data/Images/BackGround/BackGround03.png",   1U },
    { GAME_TEXNO::BG04, L"./Data/Images/BackGround/BackGround01.png",   1U },
    { GAME_TEXNO::BG05, L"./Data/Images/BackGround/BackGround04.png",   1U },
    { GAME_TEXNO::BG06, L"./Data/Images/BackGround/BackGround02.png",   1U },
    { GAME_TEXNO::BG07, L"./Data/Images/BackGround/BackGround05(未完成).png",   1U },
    { GAME_TEXNO::BG08, L"./Data/Images/BackGround/BackGround01.png",   1U },
    { GAME_TEXNO::BG09, L"./Data/Images/BackGround/BackGround06.png",   1U },

    // UI
    { GAME_TEXNO::UI_METER_FRAME,    L"./Data/Images/UI/Meter_Frame.png",   1U },   // 計器の枠
    { GAME_TEXNO::UI_METER_READ,     L"./Data/Images/UI/Meter_Read.png",    1U },   // 計器の目盛り
    { GAME_TEXNO::UI_METER_NEEDLE,   L"./Data/Images/UI/Meter_Needle.png",  1U },   // 計器の針

    // コア
    { GAME_TEXNO::PL_CORE01,  L"./Data/Images/Core/PlayerCore01.png", 1U },
    { GAME_TEXNO::ENM_CORE01, L"./Data/Images/Core/EnemyCore01.png",  1U },

    // 攻撃パーツ
    { GAME_TEXNO::TURRET01,  L"./Data/Images/Parts/Turret/Turret01.png", 1U },
    { GAME_TEXNO::TURRET02,  L"./Data/Images/Parts/Turret/Turret02.png", 1U },
    { GAME_TEXNO::TURRET03,  L"./Data/Images/Parts/Turret/Turret03.png", 1U },
    { GAME_TEXNO::TURRET04,  L"./Data/Images/Parts/Turret/Turret03.png", 1U },
    //防御パーツ
    { GAME_TEXNO::SHIELD01,  L"./Data/Images/Parts/Shield/Shield01.png", 1U },
    // バフパーツ
    { GAME_TEXNO::BUFF01,    L"./Data/Images/Parts/Buff/Buff01.png",     1U },
    // ごみパーツ
    { GAME_TEXNO::TRASH01,   L"./Data/Images/Parts/Trash/Trash01.png",   1U },
    { GAME_TEXNO::TRASH02,   L"./Data/Images/Parts/Trash/Trash02.png",   1U },
    { GAME_TEXNO::TRASH03,   L"./Data/Images/Parts/Trash/Trash03.png",   1U },

    // コモンパーツ(効果なしパーツ)
    { GAME_TEXNO::COMMON01,   L"./Data/Images/Parts/Common/Steel_Frame01.png",   1U },
    { GAME_TEXNO::COMMON02,   L"./Data/Images/Parts/Common/Steel_Frame02.png",   1U },
    { GAME_TEXNO::COMMON03,   L"./Data/Images/Parts/Common/Steel_Frame03.png",   1U },

    // 弾
    { GAME_TEXNO::BULLET01,   L"./Data/Images/Bullet/Bullet01.png",   1U },

    // エフェクト
    { GAME_TEXNO::EFC_BOMB,      L"./Data/Images/Effect/Effect_Bomb.png",    1U },
    { GAME_TEXNO::EFC_COMBINE,   L"./Data/Images/Effect/Effect_Combine.png", 1U },

    // GameOver
    { GAME_TEXNO::GAME_HEART,     L"./Data/Images/Core/Core_Heart.png",   1U }, // プレイヤーコアのハート
    { GAME_TEXNO::GAME_FRAME,     L"./Data/Images/Core/Core_Frame.png",   1U }, // プレイヤーコアのフレーム

    { -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心


////////////////////////// タイトル /////////////////////////////////////////////////////////////////

GameLib::SpriteData sprTitlePlayerCore  = SPRITE_CENTER(TITLE_TEXNO::TITLE_PLAYER,    0, 0, 128, 128);
GameLib::SpriteData sprTitleCoreHeart   = SPRITE_CENTER(TITLE_TEXNO::TITLE_HEART,     0, 0, 128, 128);
GameLib::SpriteData sprTitleCoreFrame   = SPRITE_CENTER(TITLE_TEXNO::TITLE_FRAME,     0, 0, 128, 128);
GameLib::SpriteData sprTitleLogo        = SPRITE_CENTER(TITLE_TEXNO::TITLE_LOGO,      0, 0, 640, 128);

GameLib::SpriteData sprTitleTrashBox01  = SPRITE_CENTER(TITLE_TEXNO::TITLE_TRASH_BOX, (128 * 0), 0, 128, 128);
GameLib::SpriteData sprTitleTrashBox02  = SPRITE_CENTER(TITLE_TEXNO::TITLE_TRASH_BOX, (128 * 1), 0, 128, 128);

GameLib::SpriteData sprTitleUserMove    = SPRITE_CENTER(TITLE_TEXNO::TITLE_USER_MOVE,  0, 0, 512, 128);
GameLib::SpriteData sprTitleUserSpace   = SPRITE_CENTER(TITLE_TEXNO::TITLE_USER_SPACE, 0, 0, 384, 128);

////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////// ゲーム //////////////////////////////////////////////////////////////////

//------< コア>------------------------------------------------------------------
GameLib::SpriteData sprPlayerCore01     = SPRITE_CENTER(GAME_TEXNO::PL_CORE01,   0, 0, 128, 128);
GameLib::SpriteData sprEnemyCore01      = SPRITE_CENTER(GAME_TEXNO::ENM_CORE01,  0, 0, 128, 128);

//------< パーツ >------------------------------------------------------------------
GameLib::SpriteData sprPartsTurret01    = SPRITE_CENTER(GAME_TEXNO::TURRET01, 0, 0, 128, 128);
GameLib::SpriteData sprPartsTurret02    = SPRITE_CENTER(GAME_TEXNO::TURRET02, 0, 0, 128, 128);
GameLib::SpriteData sprPartsTurret03    = SPRITE_CENTER(GAME_TEXNO::TURRET03, 0, 0, 128, 128);
GameLib::SpriteData sprPartsTurret04    = SPRITE_CENTER(GAME_TEXNO::TURRET04, 0, 0, 128, 128);

GameLib::SpriteData sprPartsShield01    = SPRITE_CENTER(GAME_TEXNO::SHIELD01, 0, 0, 128, 128);
GameLib::SpriteData sprPartsBuff01      = SPRITE_CENTER(GAME_TEXNO::BUFF01,   0, 0, 250, 250);

GameLib::SpriteData sprPartsTrash01     = SPRITE_CENTER(GAME_TEXNO::TRASH01,  0, 0, 128, 128);
GameLib::SpriteData sprPartsTrash02     = SPRITE_CENTER(GAME_TEXNO::TRASH02,  0, 0, 128, 128);
GameLib::SpriteData sprPartsTrash03     = SPRITE_CENTER(GAME_TEXNO::TRASH03,  0, 0, 128, 128);

GameLib::SpriteData sprPartsCommon01    = SPRITE_CENTER(GAME_TEXNO::COMMON01, 0, 0, 128, 128);
GameLib::SpriteData sprPartsCommon02    = SPRITE_CENTER(GAME_TEXNO::COMMON02, 0, 0, 128, 128);
GameLib::SpriteData sprPartsCommon03    = SPRITE_CENTER(GAME_TEXNO::COMMON03, 0, 0, 128, 128);

//------< 弾 >----------------------------------------------------------------
GameLib::SpriteData sprShot_NormalShot  = SPRITE_CENTER(GAME_TEXNO::BULLET01, 0, 0, 64, 64);

//------< エフェクト >----------------------------------------------------------------

// 爆発エフェクト
GameLib::SpriteData sprEfcBomb_anime0    = SPRITE_CENTER(GAME_TEXNO::EFC_BOMB, (256 * 0), 0, 256, 256);
GameLib::SpriteData sprEfcBomb_anime1    = SPRITE_CENTER(GAME_TEXNO::EFC_BOMB, (256 * 1), 0, 256, 256);
GameLib::SpriteData sprEfcBomb_anime2    = SPRITE_CENTER(GAME_TEXNO::EFC_BOMB, (256 * 2), 0, 256, 256);
GameLib::SpriteData sprEfcBomb_anime3    = SPRITE_CENTER(GAME_TEXNO::EFC_BOMB, (256 * 3), 0, 256, 256);

// 合体エフェクト
GameLib::SpriteData sprEfcCombine_anime0 = SPRITE_CENTER(GAME_TEXNO::EFC_COMBINE, (256 * 0), 0, 256, 256);
GameLib::SpriteData sprEfcCombine_anime1 = SPRITE_CENTER(GAME_TEXNO::EFC_COMBINE, (256 * 1), 0, 256, 256);
GameLib::SpriteData sprEfcCombine_anime2 = SPRITE_CENTER(GAME_TEXNO::EFC_COMBINE, (256 * 2), 0, 256, 256);
GameLib::SpriteData sprEfcCombine_anime3 = SPRITE_CENTER(GAME_TEXNO::EFC_COMBINE, (256 * 3), 0, 256, 256);

//------< GameOver >----------------------------------------------------------------
GameLib::SpriteData sprGamePlayerFrame = SPRITE_CENTER(GAME_TEXNO::GAME_FRAME, 0, 0, 128, 128);
GameLib::SpriteData sprGamePlayerHeart = SPRITE_CENTER(GAME_TEXNO::GAME_HEART, 0, 0, 128, 128);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
