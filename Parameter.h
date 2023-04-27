#pragma once

// 使用するパラメータ設定ファイル（.txt）
// #define USE_TEXT_FILE "./Parameter(完成時に消す).txt"


#ifdef USE_TEXT_FILE // 開発中に使う方

#include USE_TEXT_FILE 

#else // 完成時に使う方(パラメータ設定ファイルの中身を移す)
             
//////////////////////////////
// HP	：体力
// SPEED：速度
// ATK	：攻撃力
//////////////////////////////



///// プレイヤー本体・プレイヤーパーツの速度 //////

#define PL_SPEED     (6.0f)
#define PL_SPEED_MAX (12.0f)

////////////////////////////////////////////////



//////// プレイヤー本体 /////////////////////////

#define CORE_PLAYER_HP (1000)

////////////////////////////////////////////////



//////// ドロップパーツ /////////////////////////

#define DROP_PARTS_SPEED (-2.0f)

////////////////////////////////////////////////



///////////// 弾 ///////////////////////////////

// 通常弾
#define NORMAL_SHOT_SPEED           (30.0f)
#define NORMAL_SHOT_ATK             (1)

// 正弦波弾（波）					         
#define SINE_WAVE_SHOT_SPEED        (20.0f)
#define SIN_YOFS                    (64.0f)  // 振れ幅
#define SINE_WAVE_SHOT_ATK          (1)

// 矩形波弾（カクカク）
#define SQUARE_WAVE_SHOT_SPEED_X    (40.0f)
#define SQUARE_WAVE_SHOT_SPEED_Y    (20.0f)
#define SQUARE_WAVE_SHOT_POSX_LIMIT (300.0f) // 一度に前に進める距離
#define SQUARE_WAVE_SHOT_POSY_LIMIT (75.0f)  // 上下移動できる限界
#define SQUARE_WAVE_SHOT_ATK        (1)

// カーブ弾（上カーブ）
#define CURVE_SHOT_SPEED_X          (-20.0f)
#define CURVE_SHOT_SPEED_Y          (-25.0f)
#define CURVE_SHOT_ACCEL_X          (1.4f)   // X速度に足すX加速度
#define CURVE_SHOT_ACCEL_Y          (0.9f)   // Y速度に足すY加速度
#define CURVE_SHOT_ATK              (1)

// 貫通弾（高速弾）
#define PENETRATE_SHOT_SPEED        (100.0f)
#define PENETRATE_SHOT_ATK          (1)

// プレイヤー狙撃弾
#define AIM_SHOT_SPEED_X            (10.0f)
#define AIM_SHOT_SPEED_Y            (10.0f)
#define AIM_SHOT_ATK                (1)

////////////////////////////////////////////////




////////// 縮小関連 /////////////////////////////

// OBJが更新できるスケール最低値（これ以下は更新しない）
#define UPDATE_OBJ_SCALE_MIN_LIMIT (0.0625f) // 4回分の縮小相当

// OBJが描画できるスケール最低値（これ以下は描画しない）
#define DRAW_OBJ_SCALE_MIN_LIMIT (0.03125f) // 5回分の縮小相当


#define SHRINK_SPEED  (0.0025f * 4) // 縮小の初期速度

#define TO_CORE_SPEED (-0.14f * 4) // パーツがプレイヤー本体へ向かう初期速度

////////////////////////////////////////////////




//////////////////////// 背景 //////////////////////////////////////////////


/////// 背景スクロール速度 //////////////////////

#define BG_SCROLL_SPEED (-5.0f)

/////// 映画の黒帯(LetterBox)の速度 /////////////

#define LETTER_BOX_ADD_SPEED (0.0125f) // 加算(黒帯が上がる速度)					 
#define LETTER_BOX_SUB_SPEED (-0.005f) // 減算(黒帯が降りる速度)				   	 

///////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////


#endif 


#undef DEBUG_MODE           // マクロ定義削除