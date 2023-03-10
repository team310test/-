#include "all.h"

int result_state;
int result_timer;

int result_timer_num;
int calorie_disp;	//総カロリーを表示するための変数
int combo_disp;		//コンボボーナスを表示するための変数
int score;		//スコアを表示するための変数
int state_result;

int level;	//(胃)レベル
float level_scale;	//(胃)レベルのスケール

Sprite* result_back;
Sprite* stomach_level;	//(胃)レベル画像

void result_init() {
	result_state = 0;
	result_timer = 0;
	result_timer_num = 0;
	calorie_disp = 0;
	combo_disp = 0;
	state_result = 0;
	score = 0;
	level = 0;
	level_scale = 5;
};

void result_deinit() {
	safe_delete(result_back);
	safe_delete(stomach_level);
};

void result_update() {
	switch (result_state)
	{
	case 0:
		////////  初期設定  ////////
		
		//テスト時のみ
		//blackout = 1;	
		//calorie = 3004;
		//combo_bonus = 9;
		//score = 1;

		result_state++;
		/*fallthrough*/

	case 1:
		////////  パラメータ設定  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		result_back = sprite_load(L"./Data/Images/result_back.png");
		stomach_level = sprite_load(L"./Data/Images/level.png");
		
		stomachlevel();
		
		state_result = 0;

		result_state++;
		/*fallthrough*/
	case 2:
		////////  通常時  ////////
		//debug::setString("calorie:%d", calorie);
		//debug::setString("combo_bouns:%d", combo_bonus);
		//debug::setString("state_result:%d", state_result);
		//debug::setString("score:%d", calorie + combo_bonus * COMBOBONUS);
		//debug::setString("blackout:%lf",blackout);
		stomachlevel();
		//画面を明るくする
		if ((blackout >= 0)&&(state_result==0)) {
			blackout -= 0.02;
		}
		//待機
		else if(state_result==0){
			if (blackout > 0)blackout = 0;	//0より小さくなったら0に戻す
			result_timer_num = result_timer;
			state_result++;
		}
		else if (state_result == 1) {
			if (result_timer - result_timer_num > 30) {
				state_result++;
			}
		}
		//カロリー表示
		else if (state_result == 2) {
			if (calorie_disp < calorie) {
				calorie_disp += 91;
			}
			else {
				//calorie_disp が calorieより大きくなったら calorieに戻す
				if (calorie_disp > calorie) calorie_disp = calorie;
				result_timer_num = result_timer;
				state_result++;
			}
		}
		//待機
		else if (state_result == 3) {
			if (result_timer - result_timer_num > 30) {
				state_result++;
			}
		}
		//コンボボーナス表示
		else if (state_result == 4) {
			if (combo_disp < combo_bonus * COMBOBONUS) {
				combo_disp += COMBOBONUS / 5;
			}
			else {
				result_timer_num = result_timer;
				state_result++;
			}
		}
		//待機
		else if (state_result == 5) {
			if (result_timer - result_timer_num > 60) {
				state_result++;
			}
		}
		//総合スコア表示
		else if (state_result == 6) {
			if (score < calorie + combo_bonus * COMBOBONUS) {
				score += 101;
			}
			else {
				//正しい値に戻す
				if (score > calorie + combo_bonus * COMBOBONUS) {
					score = calorie + combo_bonus * COMBOBONUS;
				}
				result_timer_num = result_timer;
				state_result++;
			}
		}
		//待機
		else if (state_result == 7) {
			if (result_timer - result_timer_num > 30) {
				state_result++;
			}
		}
		//(胃)レベル(○○級)
		else if (state_result == 8) {
			if (level_scale > 1) {
				level_scale -= 0.05;
			}
			else {
				result_timer_num = result_timer;
				state_result++;
			}
		}
		//待機	or スペースキー
		else if (state_result == 9) {
			if (result_timer - result_timer_num > 60 * 20) {
				state_result++;
			}
			if (TRG(0) & PAD_TRG1) {
				state_result++;
			}
		}
		//画面暗転
		else if (state_result == 10) {
			//画面を暗転
			if (blackout < 1) {
				blackout += 0.05;
			}
			//暗転が終了
			else {
				if (blackout > 1)blackout = 1;	//1を超えていたら1に戻す
				nextScene = SCENE_TITLE;
			}
		}

		break;
	}

	result_timer++;
};

void result_render() {
	GameLib::clear(0, 0, 0);
	sprite_render(result_back, 0, 0);	//背景

	if (state_result >= 8) {
		//(胃)レベル	(○○級)
		sprite_render(stomach_level, 255, 275,
			level_scale, level_scale,
			0, LEVEL_SIZE_Y * level,
			LEVEL_SIZE_X, LEVEL_SIZE_Y,
			0, 0,
			ToRadian(0),
			1, 1, 1, 1
		);
	}

	//カロリー表示
	if (state_result >= 2) {
		text_out(3, std::to_string(calorie_disp), 110, 505,
			4, 4,
			1, 1, 1, 1);
	}
	//コンボボーナス表示
	if (state_result >= 4) {
		text_out(3, std::to_string(combo_disp), 110, 610,
			4, 4,
			1, 1, 1, 1);
	}
	//総合スコア表示
	if (state_result >= 6) {
		text_out(3, std::to_string(score),
			1150 -( 12 * 10 * (Digit(calorie + combo_bonus * 100) -1 ) ), 590,
			10, 10,
			1, 1, 1, 1);
	}

	primitive::rect(0, 0, SCREEN_W, SCREEN_H, 0, 0, ToRadian(0), 0, 0, 0, blackout);//画面暗転
};

//桁数を調べる変数
int Digit(int num) {
	static int digit;	//桁数を調べる
	digit = 1;	

	for (int i = num; i >= 10; i /= 10) {
		digit++;
	}

	return digit;
}

//(胃)レベルを調べる
void stomachlevel() {
	static int num;
	num = calorie + combo_bonus * COMBOBONUS;
//スコアが
	//BABY_LEVELより以下
	if (num <= BABY_LEVEL)level = baby;
	//CHILD_LEVELより以下
	else if (num <= CHILD_LEVEL)level = child;
	//GENERAL_LEVEL以下
	else if (num <= GENERAL_LEVEL)level = general;
	//GLITTON_LEVEL以下
	else if (num <= GLITTON_LEVEL)level = glutton;
	//FIGHTER_LEVEL以下
	else if (num <= FIGHTER_LEVEL)level = fighter;
	//ELEPHANT_LEVEL以下
	else if (num <= ELEPHANT_LEVEL)level = elephant;
	//WHALE_LEVEL
	else level = whale;

}