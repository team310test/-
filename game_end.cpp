//�Q�[���I�����̉��o
#include "all.h"

int game_end_state;
int game_end_timer;
int game_end_timer_num;	//1�O��timer�̒l
int end_state;	

float text_x;	//timer_out	�̍��W(x)

void game_end_init(){
	game_end_state = 0;
	game_end_timer = 0;
	end_state = 0;

	text_x = -TIMER_SIZE * 12 * 8;
};

void game_end_deinit(){

};

void game_end_updata(){
	switch (game_end_state)
	{
	case 0:
		////////  �����ݒ�  ////////

		game_end_state++;
		/*fallthrough*/

	case 1:
		////////  �p�����[�^�ݒ�  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);


		game_end_state++;
		/*fallthrough*/
	case 2:
		////////  �ʏ펞  ////////
		//debug::setString("text_x:%lf", text_x);
		//debug::setString("blackout:%lf", blackout);

		//���S�Ɉړ�
		if (text_x<SCREEN_W/2 - ( TIMER_SIZE * 12 * 8) / 2) {
			text_x += 5;
		}
		else if (end_state == 0) {
			game_end_timer_num = game_end_timer;
			end_state++;
		}
		else if (end_state == 1) {
			if (game_end_timer - game_end_timer_num > 100) {
				end_state++;
			}
		}
		else if (end_state == 2) {
			//��ʂ��Ó]
			if (blackout < 1) {
				blackout += 0.05;
			}
			//�Ó]���I��
			else {
				if (blackout > 1)blackout = 1;	//1�𒴂��Ă�����1�ɖ߂�
				nextScene = SCENE_RESULT;
			}
		}
		

		break;
	}

	game_end_timer++;
};

void game_end_render(){
	//12
	text_out(3, "TIME_OUT",
		text_x, 160, TIMER_SIZE, TIMER_SIZE,
		1, 0, 0, 1);

	primitive::rect(0, 0, SCREEN_W, SCREEN_H, 0, 0, ToRadian(0), 0, 0, 0, blackout);//��ʈÓ]
};