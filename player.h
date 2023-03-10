#ifndef PLAYER_H
#define PLAYER_H

#define SCORE_TEXT_SIZE 8

//プレイヤーの向き
enum DIRECTION {
	player_flont = 0,		//0,前
	player_left	,			//1,左
	player_right			//2,右

};

extern float player_direction;	//向き(0:正面,1:左,2:右)

//関数プロトタイプ宣言
void player_init();
void player_deinit();
void player_update();
void player_render();

void cool_down();	//クールダウン処理
void player_control();	//PLが自機を操作する関数
void stomach_gauge();	//空腹ゲージ(胃)
void score_disp();	//スコア表示

#endif