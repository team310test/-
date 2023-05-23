#pragma once

#include "../GameLib/texture.h"

// ラベル定義

// タイトル
enum TITLE_TEXNO
{
    TITLE_PLAYER,               // プレイヤーコア
    TITLE_HEART,                // プレイヤーコアのハート
    TITLE_FRAME,                // プレイヤーコアの枠

    TITLE_LOGO,                 // ロゴ
    TITLE_TRASH_BOX,            // ゴミ箱
    TITLE_USER_KEYBOARD_MOVE,   // 操作方法WASD→←↓→(キーボード)
    TITLE_USER_CONTROLLER_MOVE, // 操作方法WASD→←↓→(コントローラー)
    TITLE_USER_SPACE,           // 操作方法Space
    TITLE_USER_ABXY,            // 操作方法abxy
    TITLE_USER_HOLD,            // 操作方法長押し

    TITLE_TEXT_START,           // Start
    TITLE_TEXT_EXIT,            // Exit
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
    BG10,
    BG11,
    BG12,
    BG13,
    BG14,
    BG15,
    BG16,
    BG17,
    BG_END, // 背景の最後

    // UI
    UI_METER_FRAME,     // 計器の枠
    UI_METER_NEEDLE,    // 計器の針

    UI_RESULT_BACK,     // リザルトのバック

    UI_RESULT_JUNKS,
    UI_RESULT_TIMES,
    UI_RESULT_RANK,
    UI_RESULT_ANY_PUSH,
    UI_RESULT_S,
    UI_RESULT_A,
    UI_RESULT_B,
    UI_RESULT_C,
    UI_RESULT_TEXT_JUNKIE,
    UI_RESULT_TEXT_GREAT,
    UI_RESULT_TEXT_NICE,
    UI_RESULT_TEXT_SOSO,

    // コア
    PL_CORE01,
    ENM_CORE01,
    ENM_CORE02,

    // 攻撃パーツ
    TURRET01,
    TURRET01FLIP,
    TURRET02,
    TURRET02FLIP,
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
extern GameLib::SpriteData sprTitleUserKeyboardMove;
extern GameLib::SpriteData sprTitleUserControllerMove_01;
extern GameLib::SpriteData sprTitleUserControllerMove_02;
extern GameLib::SpriteData sprTitleUserControllerMove_03;
extern GameLib::SpriteData sprTitleUserSpace;
extern GameLib::SpriteData sprTitleUserAbxy;
extern GameLib::SpriteData sprTitleUserHold;


///////////// ゲーム ////////////////////////////////////////////////

// リザルトUI
extern GameLib::SpriteData sprResult_back01;
extern GameLib::SpriteData sprResult_back02;
extern GameLib::SpriteData sprResult_back03;
extern GameLib::SpriteData sprResult_back04;
extern GameLib::SpriteData sprResult_junks;
extern GameLib::SpriteData sprResult_times;
extern GameLib::SpriteData sprResult_rank;
extern GameLib::SpriteData sprResult_anyPush;
extern GameLib::SpriteData sprResult_S;
extern GameLib::SpriteData sprResult_A;
extern GameLib::SpriteData sprResult_B;
extern GameLib::SpriteData sprResult_C;
extern GameLib::SpriteData sprResult_textJunkie;
extern GameLib::SpriteData sprResult_textGreat;
extern GameLib::SpriteData sprResult_textNice;
extern GameLib::SpriteData sprResult_textSoso;

// コア
extern GameLib::SpriteData sprPlayerCore01;
extern GameLib::SpriteData sprEnemyCore01;
extern GameLib::SpriteData sprEnemyCore02;
extern GameLib::SpriteData sprPartsCore02;

// パーツ
extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsTurret01Flip;
extern GameLib::SpriteData sprPartsTurret02;
extern GameLib::SpriteData sprPartsTurret02Flip;
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
