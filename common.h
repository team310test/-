#ifndef COMMON_H
#define COMMON_H

//シーンラベル
#define SCENE_TEST -2	//テスト用シーン
#define SCENE_NONE -1
#define SCENE_TITLE 0
#define SCENE_COMBO_LIST 1
#define SCENE_GAME 2
#define SCENE_RESULT 3
#define SCENE_RULE 4

//画面の大きさ
#define SCREEN_W 1280
#define SCREEN_H 720

//ベルトコンベア画像サイズ
#define BELTCONBEYOR_SIZE_W 444		//旧 460
#define BELTCONBEYOR_SIZE_H 67		//旧 110
//ベルトコンベア描画位置(仮)
#define BELT_POS_Y 600

//料理画像サイズ(正方形)
#define FOOD_SIZE 90

//食事判定距離
#define EAT_RENGE_S_L 400 //食事判定の範囲の始まり
#define EAT_RENGE_E_L 480 //食事判定の範囲の終わり

#define EAT_RENGE_S_R 800 //食事判定の範囲の始まり
#define EAT_RENGE_E_R 880 //食事判定の範囲の終わり

//プレイヤー画像サイズ
#define PLAYER_SIZE_X 455
#define PLAYER_SIZE_Y 350

//空腹ゲージ(胃)画像サイズ
#define STOMACH_SIZE_X 85
#define STOMACH_SIZE_Y 100

//変数の宣言
extern int curScene;
extern int nextScene;

extern int calorie;		//取得したカロリーを保存する変数
extern int hungerGauge;	//空腹ゲージを保存する変数

//  関数ポインタ
float(* const ToRadian)(float) = DirectX::XMConvertToRadians;  // 角度をラジアンに
float(* const ToDegree)(float) = DirectX::XMConvertToDegrees;  // ラジアンを角度に

#endif