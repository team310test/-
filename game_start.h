#ifndef GAME_START_H
#define GAME_START_H

extern float blackout;//画面暗転のための変数(アルファ)

enum {
	game_start = 0,	//ゲーム開始演出
	game_play,		//ゲームプレイ
	game_end,		//ゲーム終了演出
};

//関数プロトタイプ宣言
void game_start_init();
void game_start_deinit();
void game_start_updata();
void game_start_render();

#endif
