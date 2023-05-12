#pragma once

#include "../GameLib/texture.h"

// ラベル定義

// タイトル
enum TITLE_TEXNO
{
    TITLE_PLAYER,       // プレイヤーコア
    TITLE_HEART,        // プレイヤーコアのハート
    TITLE_FRAME,        // プレイヤーコアの枠

    TITLE_LOGO,         // ロゴ
    TITLE_TRASH_BOX,    // ゴミ箱
    TITLE_USER01,       // 操作方法
    TITLE_USER02,       // 操作方法
};

// ゲーム
enum GAME_TEXNO
{    
    // 背景
    BG01,
    BG02,
    BG03,
    BG04,
    BG05,
    BG06,
    BG07,
    BG08,
    BG09,
    BG_END, // 背景の最後

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
    TURRET04,
    //防御パーツ
    SHIELD01,
    // バフパーツ
    BUFF01,
    // ごみパーツ
    TRASH01,
    TRASH02,
    TRASH03,
    // コモンパーツ(効果なしパーツ)
    COMMON01,
    COMMON02,
    COMMON03,

    // 弾丸
    BULLET01,

    // エフェクト
    EFC_BOMB,
    EFC_COMBINE,

    // GameOver
    GAME_HEART,        // プレイヤーコアのハート
    GAME_FRAME,        // プレイヤーコアの枠
};

extern GameLib::LoadTexture titleLoadTexture[];
extern GameLib::LoadTexture gameLoadTexture[];


///////////// タイトル //////////////////////////////////////////////
extern GameLib::SpriteData sprTitlePlayerCore;
extern GameLib::SpriteData sprTitleCoreFrame;
extern GameLib::SpriteData sprTitleCoreHeart;

extern GameLib::SpriteData sprTitleLogo;
extern GameLib::SpriteData sprTitleTrashBox01;
extern GameLib::SpriteData sprTitleTrashBox02;
extern GameLib::SpriteData sprTitleUser01;
extern GameLib::SpriteData sprTitleUser02;


///////////// ゲーム ////////////////////////////////////////////////

// プレイヤー
extern GameLib::SpriteData sprPlayerCore01;

// パーツ
extern GameLib::SpriteData sprEnemyCore01;
extern GameLib::SpriteData sprPartsCore02;

extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsTurret02;
extern GameLib::SpriteData sprPartsTurret03;
extern GameLib::SpriteData sprPartsTurret04;

extern GameLib::SpriteData sprPartsShield01;
extern GameLib::SpriteData sprPartsBuff01;
extern GameLib::SpriteData sprPartsTrash01;
extern GameLib::SpriteData sprPartsTrash02;
extern GameLib::SpriteData sprPartsTrash03;

extern GameLib::SpriteData sprPartsCommon01;
extern GameLib::SpriteData sprPartsCommon02;
extern GameLib::SpriteData sprPartsCommon03;

// 弾
extern GameLib::SpriteData sprShot_NormalShot;

// エフェクト

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

// GameOver
extern GameLib::SpriteData sprGamePlayerFrame;
extern GameLib::SpriteData sprGamePlayerHeart;
