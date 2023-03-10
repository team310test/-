#ifndef COMMON_H
#define COMMON_H

//�V�[�����x��
#define SCENE_TEST -2	//�e�X�g�p�V�[��
#define SCENE_NONE -1
#define SCENE_TITLE 0
#define SCENE_COMBO_LIST 1
#define SCENE_GAME 2
#define SCENE_RESULT 3
#define SCENE_RULE 4

//��ʂ̑傫��
#define SCREEN_W 1280
#define SCREEN_H 720

//�x���g�R���x�A�摜�T�C�Y
#define BELTCONBEYOR_SIZE_W 444		//�� 460
#define BELTCONBEYOR_SIZE_H 67		//�� 110
//�x���g�R���x�A�`��ʒu(��)
#define BELT_POS_Y 600

//�����摜�T�C�Y(�����`)
#define FOOD_SIZE 90

//�H�����苗��
#define EAT_RENGE_S_L 400 //�H������͈̔͂̎n�܂�
#define EAT_RENGE_E_L 480 //�H������͈̔͂̏I���

#define EAT_RENGE_S_R 800 //�H������͈̔͂̎n�܂�
#define EAT_RENGE_E_R 880 //�H������͈̔͂̏I���

//�v���C���[�摜�T�C�Y
#define PLAYER_SIZE_X 455
#define PLAYER_SIZE_Y 350

//�󕠃Q�[�W(��)�摜�T�C�Y
#define STOMACH_SIZE_X 85
#define STOMACH_SIZE_Y 100

//�ϐ��̐錾
extern int curScene;
extern int nextScene;

extern int calorie;		//�擾�����J�����[��ۑ�����ϐ�
extern int hungerGauge;	//�󕠃Q�[�W��ۑ�����ϐ�

//  �֐��|�C���^
float(* const ToRadian)(float) = DirectX::XMConvertToRadians;  // �p�x�����W�A����
float(* const ToDegree)(float) = DirectX::XMConvertToDegrees;  // ���W�A�����p�x��

#endif