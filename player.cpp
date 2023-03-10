#include "all.h"

int player_state;
int player_timer;
int player_timer_num;	//��O��timer�̒l

Sprite* player_Image;	//���@�摜
Sprite* stomach;		//�󕠃Q�[�W(��)
float player_direction;	//����(0:����,1:��,2:�E)
float player_anime;	//�A�j���[�V����(����2�R�})
bool coolDown;	//�N�[���_�E����(true)	�L�[����󂯕t���Ȃ��Ȃ�

//�X�R�A�\��
int calorie;		//�擾�����J�����[��ۑ�����ϐ�
int hungerGauge;

//�����ݒ�
void player_init() {
	player_state = 0;
	player_timer = 0;
	player_timer_num = 0;

	player_direction = 0;
	player_anime = 0;
	coolDown = false;

	calorie = 0;
}

//�폜
void player_deinit() {
	safe_delete(player_Image);
	safe_delete(stomach);
}

//�X�V����
void player_update() {

	switch (player_state) {
	case 0:
		////////  �����ݒ�  ////////

		player_Image = sprite_load(L"./Data/Images/player.png");
		stomach = sprite_load(L"./Data/Images/stomach.png");
		player_state++;
		/*fallthrough*/

	case 1:
		////////  �p�����[�^�ݒ�  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		player_state++;
		/*fallthrough*/
	case 2:
		////////  �ʏ펞  ////////

		stomach_gauge();	//�݃Q�[�W(�󕠃Q�[�W)����

		//�N�[���_�E���łȂ����(coolDown��false�ł����)
		if (!coolDown) {
			//�v���C���[�̑���
			player_control();
		}
		else {
			cool_down();	//�N�[���_�E������
		}

		break;
	}
	player_timer++;
	debug::setString("player_timer:%d", player_timer);
}

//�`�揈��
void player_render() {
	//���@
	sprite_render(player_Image,									//�|�C���^
		SCREEN_W / 2, SCREEN_H,									//���W
		1, 1,													//�\���P�[��
		player_anime * PLAYER_SIZE_X, player_direction * PLAYER_SIZE_Y,//���摜�ʒu
		PLAYER_SIZE_X, PLAYER_SIZE_Y,							//���摜�T�C�Y
		PLAYER_SIZE_X / 2, PLAYER_SIZE_Y,						//��_
		ToRadian(0),											//�p�x
		1, 1, 1, 1);											//�F�ʁA�����x

	//��(��)
	sprite_render(stomach,										//�|�C���^
		SCREEN_W - STOMACH_SIZE_X, STOMACH_SIZE_Y,				//���W
		1, 1,													//�\���P�[��
		0,0,													//���摜�ʒu
		STOMACH_SIZE_X, STOMACH_SIZE_Y,							//���摜�T�C�Y
		STOMACH_SIZE_X / 2, STOMACH_SIZE_Y / 2,					//��_
		ToRadian(0),											//�p�x
		1, 1, 1, 1);											//�F�ʁA�����x

		//��
	sprite_render(stomach,										//�|�C���^
		SCREEN_W - STOMACH_SIZE_X, STOMACH_SIZE_Y,			//���W
		1, 1,													//�\���P�[��
		STOMACH_SIZE_X, 0,					//���摜�ʒu
		STOMACH_SIZE_X, STOMACH_SIZE_Y*((float)hungerGauge*0.01),					//���摜�T�C�Y
		STOMACH_SIZE_X / 2, STOMACH_SIZE_Y / 2,													//�
		ToRadian(180),											//�p�x
		1, 1, 1, 1);											//�F�ʁA�����x										//�F�ʁA�����x
}

//���@�̑���
void player_control() {

	//�E						(�E��������Ă��ā@���@����������Ă��Ȃ�)
	if ((STATE(0) & PAD_RIGHT) && !(STATE(0) & PAD_LEFT)) {
		player_direction = player_right;
	}
	//��						(����������Ă��ā@���@�E��������Ă��Ȃ�)
	else if ((STATE(0) & PAD_LEFT) && !(STATE(0) & PAD_RIGHT)) {
		player_direction = player_left;
	}
	//����������Ă��Ȃ�
	else {
		player_direction = player_flont;
	}

}


//�݃Q�[�W(�󕠃Q�[�W)		�}�b�N�X�ɂȂ�ƃN�[���_�E��
void stomach_gauge() {
	if (hungerGauge >= 100) {
		player_direction = player_flont;//���ʂ���������
		player_anime = 1;	
		coolDown = true;	//�N�[���_�E����Ԃ�(true�ɂ���)
	}
}

//�N�[���_�E������
void cool_down() {
	static int cooldawn_state = 0;	
	
	//�ҋ@����
	if (cooldawn_state == 0) {
		player_timer_num = player_timer;
		cooldawn_state++;
	}
	else if (cooldawn_state == 1) {
		
		if (player_timer - player_timer_num > 30) 
			cooldawn_state++;
	}
	//�Q�[�W����
	else if (cooldawn_state == 2) {
		//0�ȉ��ɂȂ�܂ň���
		if (hungerGauge > 0) {
			hungerGauge--;
		}
		else {
			//0��菬�����Ȃ�����0�ɖ߂�
			if (hungerGauge < 0)hungerGauge == 0;
			cooldawn_state++;
		}
	}
	//�ҋ@����
	else if (cooldawn_state == 3) {
		player_timer_num = player_timer;
		cooldawn_state++;
	}
	else if (cooldawn_state == 4) {
		if (player_timer - player_timer_num > 30) {
			player_anime = 0;
			coolDown = false;	//�N�[���_�E����ԉ���(false�ɂ���)
			cooldawn_state = 0;
			cooldawn_state = 0;
		}
	}
}

//�X�R�A�\��
void score_disp() {

	//�ucalorie�v�\��
	//text_out(3,"calorie:", 0, 0, SCORE_TEXT_SIZE, SCORE_TEXT_SIZE, 0, 0, 0, 1);

	//�J�����[�w�i
	primitive::rect(0, 0, SCORE_TEXT_SIZE * 12 * 5, SCORE_TEXT_SIZE * 12,
		0,0,ToRadian(0),1,1,0,1);
	
	//�J�����[(���l)�\��
	text_out(3, std::to_string(calorie),0,0,
		SCORE_TEXT_SIZE, SCORE_TEXT_SIZE,0,0,0,1);

}

