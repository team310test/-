#ifndef TEST_H
#define TEST_H

//�H�ו�����
#define foodMAX (30)
#define halfFoodMAX (foodMAX / 2)

extern int blet_y;	//�x���g�R���x�A�̍��W

//�֐��v���g�^�C�v�錾
void test_init();
void test_deinit();
void test_update();
void test_render();

void test_loadimage();	//�摜�ǂݍ���

//����e�X�g�֐�
void test_title();	//�^�C�g�����(���[�h�I��
void test_testBeltConveyor();	//�x���g�R���x�A�`��e�X�g
void Player();	//�l�`��e�X�g

void eat_renfe();	//�H���͈͖ڈ�

#endif
