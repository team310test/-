#ifndef RESULT
#define RESULT

#define COMBOBONUS 1500 //1�R���{�̒ǉ��_
#define LEVEL_SIZE_X 648	//(��)���x���T�C�YX
#define LEVEL_SIZE_Y 75		//(��)���x���T�C�YY

#define BABY_LEVEL 10000		//�Ԃ���񃌃x��
#define CHILD_LEVEL 12000		//�q�����x��
#define GENERAL_LEVEL 20000		//��ʐl���x��
#define GLITTON_LEVEL 30000		//�H������V���x��
#define FIGHTER_LEVEL 35000		//�t�[�h�t�@�C�^�[���x��
#define ELEPHANT_LEVEL 40000		//�]�E���x��
#define WHALE_LEVEL 50000		//�N�W�����x��

enum LEVEL {
	baby = 0,
	child,
	general,
	glutton,
	fighter,
	elephant,
	whale
};

//�֐��v���g�^�C�v�錾
void result_init();
void result_deinit();
void result_update();
void result_render();

int Digit(int num);	//�����𒲂ׂ�
void stomachlevel();//(��)���x���𒲂ׂ�

#endif