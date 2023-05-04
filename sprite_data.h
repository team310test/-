#pragma once

#include "../GameLib/texture.h"

// ラベル定義
enum TEXNO
{
    // ゲーム
    
    // 背景
    BACK01,
    BACK02,
    // UI
    UI_METER_FRAME,     // 計器の枠
    UI_METER_READ,      // 計器の目盛り
    UI_METER_NEEDLE,    // 計器の針

    // コア
    PL_CORE01,
    ENM_CORE01,

    // 攻撃パーツ
    TURRET01,
    TURRET02,
    TURRET03,
    // バフパーツ
    BUFF01,
    // ごみパーツ
    TRASH01,

    // 弾丸
    BULLET01,

    // エフェクト
    EFC_BOMB,
    EFC_COMBINE,

    // タイトル
    TITLE_FRAME,
    TITLE_USER,
    TITLE_TRASH,
    TITLE_LOGO,
    TITLE_HEART,
};

extern GameLib::LoadTexture loadTexture[];


//------< プレイヤー >------------------------------------------------------------------
extern GameLib::SpriteData sprPlayerCore01;

//------< パーツ >------------------------------------------------------------------
extern GameLib::SpriteData sprEnemyCore01;
extern GameLib::SpriteData sprPartsCore02;
extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsTurret03;
extern GameLib::SpriteData sprPartsBuff01;
extern GameLib::SpriteData sprPartsTrash01;

//------< 弾 >----------------------------------------------------------------
extern GameLib::SpriteData sprShot_NormalShot;

//------< エフェクト >----------------------------------------------------------------

//　爆発エフェクト
extern GameLib::SpriteData sprEfcBomb_anime0;
extern GameLib::SpriteData sprEfcBomb_anime1;
extern GameLib::SpriteData sprEfcBomb_anime2;
extern GameLib::SpriteData sprEfcBomb_anime3;

// 合体エフェクト
extern GameLib::SpriteData sprEfcCombine_anime0;
extern GameLib::SpriteData sprEfcCombine_anime1;
extern GameLib::SpriteData sprEfcCombine_anime2;
extern GameLib::SpriteData sprEfcCombine_anime3;

//------< タイトル >----------------------------------------------------------------
extern GameLib::SpriteData sprTitleCore;
extern GameLib::SpriteData sprTitleUser;
extern GameLib::SpriteData sprTitleTrash;
extern GameLib::SpriteData sprTitleLogo;
extern GameLib::SpriteData sprTitleHeart;

//******************************************************************************
