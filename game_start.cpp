//�Q�[���J�n���̉��o
#include "all.h"

int game_start_state;
int game_start_timer;

int start_state;	//�����������ʂ�i�߂邽�߂̕ϐ�

float blackout;//��ʈÓ]�̂��߂̕ϐ�(�A���t�@)
int countdown;	//�Q�[���J�n���\������̃J�E���g�_�E��
int game_start_timer_num;	//1�O��timer�̒l
float text_size;	//�uGO�v�̃e�L�X�g�T�C�Y

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
		////////  �����ݒ�  ////////

		game_start_state++;
		/*fallthrough*/

	case 1:
		////////  �p�����[�^�ݒ�  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);

		text_size = 25;
		countdown = -1;
		game_start_timer_num = 0;

		game_start_state++;
		/*fallthrough*/
	case 2:
		////////  �ʏ펞  ////////

		//debug::setString("blackout:%lf", blackout);
		//debug::setString("countdown:%d", countdown);
		//debug::setString("count:%d", game_start_timer - game_start_timer_num);
		//debug::setString("state:%d", start_state);
		
		//��ʈÓ]����
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
		//�J�E���g�_�E��
		else if (start_state == 2) {
			if (game_start_timer - game_start_timer_num > 50) {
				countdown--;
				game_start_timer_num = game_start_timer;
			}
			if (countdown == 0) {
				start_state = 3;
			}
		}
		//�uGO�v�\��
		else if (start_state == 3) {
		//�uGO�v�g��
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
		////�J�E���g�_�E��
		//else if (countdown > 0) {
		//	if (game_start_timer - game_start_timer_num > 50) {
		//		countdown--;
		//		game_start_timer_num = game_start_timer;
		//	}
		//}
		////�uGO�v�\��
		//else if (countdown == 0) {
		//	//�uGO�v�g��
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

	//state==2�Ȃ�
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