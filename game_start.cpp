//ゲーム開始時の演出
#include "all.h"

int game_start_state;
int game_start_timer;

int start_state;	//処理を順序通り進めるための変数

float blackout;//画面暗転のための変数(アルファ)
int countdown;	//ゲーム開始時表示するのカウントダウン
int game_start_timer_num;	//1つ前のtimerの値
float text_size;	//「GO」のテキストサイズ

void game_start_init() {
	game_start_state = 0;
	game_start_timer = 0;
	start_state = 0;
	blackout = 1;
}

void game_start_deinit() {

}

void game_start_updata() {
	switch (game_start_state)
	{
	case 0:
		////////  初期設定  ////////

		game_start_state++;
		/*fallthrough*/

	case 1:
		////////  パラメータ設定  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);

		text_size = 25;
		countdown = -1;
		game_start_timer_num = 0;

		game_start_state++;
		/*fallthrough*/
	case 2:
		////////  通常時  ////////

		//debug::setString("blackout:%lf", blackout);
		//debug::setString("countdown:%d", countdown);
		//debug::setString("count:%d", game_start_timer - game_start_timer_num);
		//debug::setString("state:%d", start_state);
		
		//画面暗転解除
		if (start_state == 0) {
			blackout -= 0.05;
			countdown = 3;
			if (blackout < 0) {
				game_start_timer_num = game_start_timer;
				start_state = 1;
			}
		}
		else if (start_state == 1) {
			if (game_start_timer - game_start_timer_num > 50) {
				start_state = 5;
			}
			else {
				game_start_timer_num = game_start_timer;
				start_state = 2;
			}
		}
		//カウントダウン
		else if (start_state == 2) {
			if (game_start_timer - game_start_timer_num > 50) {
				countdown--;
				game_start_timer_num = game_start_timer;
			}
			if (countdown == 0) {
				start_state = 3;
			}
		}
		//「GO」表示
		else if (start_state == 3) {
		//「GO」拡大
		if (text_size < 35) {
			text_size += 4;
		}
		else {
			start_state = 4;
			game_start_timer_num = game_start_timer;
		}
		}
		else if(start_state==4) {
			if (game_start_timer - game_start_timer_num > 50) {
				start_state = 5;
			}
		}
		else if (start_state == 5) {
			if (text_size > 0) {
				text_size -= 3;
			}
			else {
				game_scene = game_play;
			}
		}
		//if (blackout >= 0) {
		//	blackout -= 0.05;
		//	countdown = 3;
		//	game_start_timer_num = game_start_timer;
		//}
		////カウントダウン
		//else if (countdown > 0) {
		//	if (game_start_timer - game_start_timer_num > 50) {
		//		countdown--;
		//		game_start_timer_num = game_start_timer;
		//	}
		//}
		////「GO」表示
		//else if (countdown == 0) {
		//	//「GO」拡大
		//	if(text_size<35) {
		//		text_size+=3;
		//	}
		//	else {
		//		game_start_timer_num = game_start_timer;
		//	}
		//}
		//else {
		//	if (game_start_timer - game_start_timer_num < 100) {
		//		game_scene = game_play;
		//	}
		//}


		break;
	}

	game_start_timer++;
}

void game_start_render() {	

	//state==2なら
	if(start_state == 2){
		text_out(3, std::to_string(countdown),
			SCREEN_W / 2 - 180, SCREEN_H / 2 - 180,
			30, 30,
			1, 0, 0, 1);
	}
	if (countdown == 0) {
		text_out(3, "GO",
			SCREEN_W / 2 -6 * text_size * 2  , SCREEN_H / 2 - 6 * text_size,
			text_size, text_size,
			1, 0, 0, 1);
	}

	primitive::rect(0,0,SCREEN_W, SCREEN_H,0,0,ToRadian(0),0,0,0,blackout);
}