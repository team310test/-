#include "all.h"

int result_state;
int result_timer;

int result_timer_num;
int calorie_disp;	//���J�����[��\�����邽�߂̕ϐ�
int combo_disp;		//�R���{�{�[�i�X��\�����邽�߂̕ϐ�
int score;		//�X�R�A��\�����邽�߂̕ϐ�
int state_result;

int level;	//(��)���x��
float level_scale;	//(��)���x���̃X�P�[��

Sprite* result_back;
Sprite* stomach_level;	//(��)���x���摜

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
		////////  �����ݒ�  ////////
		
		//�e�X�g���̂�
		//blackout = 1;	
		//calorie = 3004;
		//combo_bonus = 9;
		//score = 1;

		result_state++;
		/*fallthrough*/

	case 1:
		////////  �p�����[�^�ݒ�  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		result_back = sprite_load(L"./Data/Images/result_back.png");
		stomach_level = sprite_load(L"./Data/Images/level.png");
		
		stomachlevel();
		
		state_result = 0;

		result_state++;
		/*fallthrough*/
	case 2:
		////////  �ʏ펞  ////////
		//debug::setString("calorie:%d", calorie);
		//debug::setString("combo_bouns:%d", combo_bonus);
		//debug::setString("state_result:%d", state_result);
		//debug::setString("score:%d", calorie + combo_bonus * COMBOBONUS);
		//debug::setString("blackout:%lf",blackout);
		stomachlevel();
		//��ʂ𖾂邭����
		if ((blackout >= 0)&&(state_result==0)) {
			blackout -= 0.02;
		}
		//�ҋ@
		else if(state_result==0){
			if (blackout > 0)blackout = 0;	//0��菬�����Ȃ�����0�ɖ߂�
			result_timer_num = result_timer;
			state_result++;
		}
		else if (state_result == 1) {
			if (result_timer - result_timer_num > 30) {
				state_result++;
			}
		}
		//�J�����[�\��
		else if (state_result == 2) {
			if (calorie_disp < calorie) {
				calorie_disp += 91;
			}
			else {
				//calorie_disp �� calorie���傫���Ȃ����� calorie�ɖ߂�
				if (calorie_disp > calorie) calorie_disp = calorie;
				result_timer_num = result_timer;
				state_result++;
			}
		}
		//�ҋ@
		else if (state_result == 3) {
			if (result_timer - result_timer_num > 30) {
				state_result++;
			}
		}
		//�R���{�{�[�i�X�\��
		else if (state_result == 4) {
			if (combo_disp < combo_bonus * COMBOBONUS) {
				combo_disp += COMBOBONUS / 5;
			}
			else {
				result_timer_num = result_timer;
				state_result++;
			}
		}
		//�ҋ@
		else if (state_result == 5) {
			if (result_timer - result_timer_num > 60) {
				state_result++;
			}
		}
		//�����X�R�A�\��
		else if (state_result == 6) {
			if (score < calorie + combo_bonus * COMBOBONUS) {
				score += 101;
			}
			else {
				//�������l�ɖ߂�
				if (score > calorie + combo_bonus * COMBOBONUS) {
					score = calorie + combo_bonus * COMBOBONUS;
				}
				result_timer_num = result_timer;
				state_result++;
			}
		}
		//�ҋ@
		else if (state_result == 7) {
			if (result_timer - result_timer_num > 30) {
				state_result++;
			}
		}
		//(��)���x��(������)
		else if (state_result == 8) {
			if (level_scale > 1) {
				level_scale -= 0.05;
			}
			else {
				result_timer_num = result_timer;
				state_result++;
			}
		}
		//�ҋ@	or �X�y�[�X�L�[
		else if (state_result == 9) {
			if (result_timer - result_timer_num > 60 * 20) {
				state_result++;
			}
			if (TRG(0) & PAD_TRG1) {
				state_result++;
			}
		}
		//��ʈÓ]
		else if (state_result == 10) {
			//��ʂ��Ó]
			if (blackout < 1) {
				blackout += 0.05;
			}
			//�Ó]���I��
			else {
				if (blackout > 1)blackout = 1;	//1�𒴂��Ă�����1�ɖ߂�
				nextScene = SCENE_TITLE;
			}
		}

		break;
	}

	result_timer++;
};

void result_render() {
	GameLib::clear(0, 0, 0);
	sprite_render(result_back, 0, 0);	//�w�i

	if (state_result >= 8) {
		//(��)���x��	(������)
		sprite_render(stomach_level, 255, 275,
			level_scale, level_scale,
			0, LEVEL_SIZE_Y * level,
			LEVEL_SIZE_X, LEVEL_SIZE_Y,
			0, 0,
			ToRadian(0),
			1, 1, 1, 1
		);
	}

	//�J�����[�\��
	if (state_result >= 2) {
		text_out(3, std::to_string(calorie_disp), 110, 505,
			4, 4,
			1, 1, 1, 1);
	}
	//�R���{�{�[�i�X�\��
	if (state_result >= 4) {
		text_out(3, std::to_string(combo_disp), 110, 610,
			4, 4,
			1, 1, 1, 1);
	}
	//�����X�R�A�\��
	if (state_result >= 6) {
		text_out(3, std::to_string(score),
			1150 -( 12 * 10 * (Digit(calorie + combo_bonus * 100) -1 ) ), 590,
			10, 10,
			1, 1, 1, 1);
	}

	primitive::rect(0, 0, SCREEN_W, SCREEN_H, 0, 0, ToRadian(0), 0, 0, 0, blackout);//��ʈÓ]
};

//�����𒲂ׂ�ϐ�
int Digit(int num) {
	static int digit;	//�����𒲂ׂ�
	digit = 1;	

	for (int i = num; i >= 10; i /= 10) {
		digit++;
	}

	return digit;
}

//(��)���x���𒲂ׂ�
void stomachlevel() {
	static int num;
	num = calorie + combo_bonus * COMBOBONUS;
//�X�R�A��
	//BABY_LEVEL���ȉ�
	if (num <= BABY_LEVEL)level = baby;
	//CHILD_LEVEL���ȉ�
	else if (num <= CHILD_LEVEL)level = child;
	//GENERAL_LEVEL�ȉ�
	else if (num <= GENERAL_LEVEL)level = general;
	//GLITTON_LEVEL�ȉ�
	else if (num <= GLITTON_LEVEL)level = glutton;
	//FIGHTER_LEVEL�ȉ�
	else if (num <= FIGHTER_LEVEL)level = fighter;
	//ELEPHANT_LEVEL�ȉ�
	else if (num <= ELEPHANT_LEVEL)level = elephant;
	//WHALE_LEVEL
	else level = whale;

}