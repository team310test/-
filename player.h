#ifndef PLAYER_H
#define PLAYER_H

#define SCORE_TEXT_SIZE 8

//�v���C���[�̌���
enum DIRECTION {
	player_flont = 0,		//0,�O
	player_left	,			//1,��
	player_right			//2,�E

};

extern float player_direction;	//����(0:����,1:��,2:�E)

//�֐��v���g�^�C�v�錾
void player_init();
void player_deinit();
void player_update();
void player_render();

void cool_down();	//�N�[���_�E������
void player_control();	//PL�����@�𑀍삷��֐�
void stomach_gauge();	//�󕠃Q�[�W(��)
void score_disp();	//�X�R�A�\��

#endif