#ifndef FOOD_H
#define FOOD_H

#define interval 150	//�\������H�ו��̊Ԋu
#define INIT_POS_L -100
#define INIT_POS_R SCREEN_W + 100

//�R���{���[�`�̕��E����
#define COMBOREACH_W 620
#define COMBOREACH_H 380

//�R���{���e�L�X�g�̕��E����
#define COMBOSET_W 800
#define COMBOSET_H 100

extern int combo_bonus;	//�R���{������

//�������ԍ�
enum {
	chahan=0,	//�`���[�n��
	ramen,		//���[����
	gyouza,		//�L�q
	onigiri,	//���ɂ���
	syake,		//��
	miso,		//���X�`
	hanbaga,	//�n���o�[�K
	poteto,		//�|�e�g
	kora,		//�R�[��
	zerokora,	//�[���J�����[�R�[��
	hotate,		//�z�^�e���i
	tamago,		//�^�}�S���i
	maguro		//�}�O�����i
};

//�R���{�ԍ�
enum {
	china = 0,	//���؃R���{
	japan,		//���{�̒��H�R���{
	happy,		//�j�R�j�R�R���{
	sushi		//���i�R���{
};

//�֐��v���g�^�C�v�錾
void food_init();
void food_deinit();
void food_update();
void food_render();
void food_move_eat();	//�H�ו��ړ�����
void food_eat(int i);	//�H�ו��H������
//void food_move_reset(int i);//�H�ו��ړ����Z�b�g
void food_disp_on();//disp ����莞�Ԃ��Ƃ� on�@�ɂ��� 
int food_combo_numberGet(int eatNum/*�H�ׂ��H�ו��̔ԍ�*/);//�R���{�ԍ����擾
void eat_calorie_disp(int eatNum);
void food_combo_load(int eatNum);
void food_combo_group_check(int combo, int nextCombo, int now/*�Ō�ɒl���������ӏ�*/);
void food_combo_check(int combo, int nextCombo, int now);//(���O���[�v����)���Ȃ��H�ו�������΃��Z�b�g����
void Reach();
void Combo();
void Combo_reset();

#endif