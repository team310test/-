#include "all.h"

int test_state;
int test_timer;

//�H�ו�����
bool food;
bool disp_R[halfFoodMAX];	//�E���̐H�ו��\������(tlre:�\��)
bool eat_R[halfFoodMAX];	//�E���̐H�ׂ����̔���(tlre:�H�ׂ��ĂȂ�)

int order_R[halfFoodMAX];	//�E���̕\�����鏇��
int order_ALL[foodMAX];		//�S�̂̕\�����鏇��

int stageFoodMAX[3] = { 10, 20, 30 };  //�X�e�[�W���Ƃ̍ő�l
int stage_No = 2;	//���X�e�[�W�ԍ�(��)

//struct FOOD_DETA {
//	Sprite* spr;				//�摜
//	const wchar_t* filePath;	//�t�@�C���p�X
//	//char name[16];				//������
//	int karori;					//�J�����[(�ϐ�����)
//	float mannpuku;				//�����Q�[�W(�݃Q�[�W������)(�ϐ�����)
//	VECTOR2 pos;				//���W
//	//float Texpos;				//��_
//};

//FOOD_DETA FoodDeta[/*��*/]{
//	{NULL,L"./Data/Images/food00.png",1,11,{100,100}, },
//	{NULL,L"./Data/Images/food01.png",2,22,{200,100}},
//	{NULL,L"./Data/Images/food02.png",3,33,{300,100}}
//};


//�^�C�g�����[�h�؂�ւ�(��)
bool title;	//�^�C�g�����[�h�؂�ւ�����؂�ւ�
int nextcursor;
int cursor;
int alpha[4];
Sprite* Back1;
Sprite* Back2;
Sprite* Back3;
Sprite* Back4;

//�x���g�R���x�A�`��e�X�g
bool belt;	//�x���g�R���x�A�`��e�X�g����؂�ւ�

//int BeltConveyor_anime_R;
//int BeltConveyor_anime_L;
//int BeltConveyor_Texpos_L;

//�l�`��e�X�g
bool hito;
bool hito_move;

//�����ݒ�
void test_init() {

	test_state = 0;
	test_timer = 0;

	//�^�C�g�����[�h�؂�ւ�(��)
	title = false;
	nextcursor = 0;
	cursor = 0;
	for (int i = 0; i < 4; ++i) {alpha[i] = 1;}

	//�x���g�R���x�A�`��e�X�g
	belt = true;

	//BeltConveyor_anime_R = 0;
	//BeltConveyor_anime_L = 0;
	//BeltConveyor_Texpos_L = 0;

	//�l�`��
	hito = false;
	hito_move = false;

	//�H�ו�����
	food = false;


	//food.cpp�e�X�g
	food_init();

	//player.cpp�e�X�g
	player_init();

}

//�I������
void test_deinit() {

	//safe_delete(sprCar);
	food_deinit();
	player_deinit();
}

//�X�V����
void test_update() {

	switch (test_state)
	{
	case 0:
		////////  �����ݒ�  ////////
		
		test_loadimage();

		//�V���b�t���֐��e�X�g

		for (int i = 0; i < halfFoodMAX; ++i)
		{
			disp_R[i] = false;
			eat_R[i] = false;
		}

		for (int i = 0; i < stageFoodMAX[stage_No]; ++i)
		{
			order_ALL[i] = i;
		}

		test_state++;
		/*fallthrough*/

	case 1:
		////////  �p�����[�^�ݒ�  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		test_state++;
		/*fallthrough*/
	case 2:
		////////  �ʏ펞  ////////
		debug::setString("title_timer:%d", test_timer);
		debug::setString("title_state:%d", test_state);

		srand((unsigned int)time(NULL));

		///////	�^�C�g�����[�h�؂�ւ��e�X�g  ///////
		debug::setString("[1]titl:%d",title);
		if(title)
			test_title();	
		//[1]��taitle on,off
		if (GetAsyncKeyState('1') & 1) {
			if (title)
				title = false;
			else
				title = true;
		}

		///////	�^�C�g�����[�h�؂�ւ��e�X�g  ///////
		debug::setString("[2]belt:%d",belt);
		if (belt)
			test_testBeltConveyor();
			//[1]��taitle on,off
		if (GetAsyncKeyState('2') & 1) {
			if (belt)
				belt = false;
			else
				belt = true;
		}

		///////	�H�ו������؂�ւ��e�X�g  ///////
		debug::setString("[3]food:%d",food);
		if (belt)
			test_testBeltConveyor();
		//[3]��taitle on,off
		if (GetAsyncKeyState('3') & 1) {
			if (food)
				food = false;
			else {
				food = true;
				shuffle(order_ALL, /*sizeof(order_ALL) / sizeof(order_ALL[0])*/stageFoodMAX[stage_No]);
			}
		}
		//oreder_ALL �\��
		if (food) {

			for (int i = 0; i < stageFoodMAX[stage_No]; ++i) {
				debug::setString("order_ALL[%d]:%d", i, order_ALL[i]);
			}
		}

		//food_updeta �e�X�g
		food_update();

		///////	�l�`��`��؂�ւ��e�X�g  ///////
		debug::setString("[4]hito:%d", hito);debug::setString("[5]hito_move:%d", hito_move);
		if (belt)
			test_testBeltConveyor();
		//[4]��hito on,off
		if (GetAsyncKeyState('4') & 1) {
			if (hito)
				hito = false;
			else {
				hito = true;
			}
		}
		//[5]��hito_move on,off
		if (GetAsyncKeyState('5') & 1) {
			if (hito_move)
				hito_move = false;
			else {
				hito_move = true;
			}
		}
		if (hito && hito_move) {
			Player();
		}


		//player.cpp�e�X�g
		player_update();

		//�{�^������������Q�[����ʂ֑J��
		if (TRG(0) & PAD_START) {
			nextScene = SCENE_GAME;
		}

		break;
	}

	test_timer++;
}

//�`�揈��
void test_render() {

	GameLib::clear(0, 1, 1);

	//�^�C�g�����[�h�؂�ւ�(��)
	if (title) {
		sprite_render(
			Back1,
			285, 174,
			1.0f, 1.0f,
			0, 0,
			1280, 720,
			0, 0,
			ToRadian(0),
			1, 1, 1, alpha[0]
		);
		sprite_render(
			Back2,
			680, 173,
			1.0f, 1.0f,
			0, 0,
			1280, 720,
			0, 0,
			ToRadian(0),
			1, 1, 1, alpha[1]
		);
		sprite_render(
			Back3,
			285, 411,
			1.0f, 1.0f,
			0, 0,
			1280, 720,
			0, 0,
			ToRadian(0),
			1, 1, 1, alpha[2]
		);
		sprite_render(
			Back4,
			680, 412,
			1.0f, 1.0f,
			0, 0,
			1280, 720,
			0, 0,
			ToRadian(0),
			1, 1, 1, alpha[3]
		);
	}
	//�x���g�R���x�A�`��e�X�g
	if (belt) {

	}
	//food.cpp�e�X�g
	food_render();
	//player.cpp�e�X�g
	player_render();
	if (hito) {
		
	}

}

//�摜�ǂݍ���
void test_loadimage() {
	//�^�C�g�����[�h�؂�ւ�(��)
	Back1 = sprite_load(L"./Data/Images/right.png");
	Back2 = sprite_load(L"./Data/Images/right.png");
	Back3 = sprite_load(L"./Data/Images/right.png");
	Back4 = sprite_load(L"./Data/Images/right.png");

	
}

//�^�C�g�����[�h�I���e�X�g
void test_title() {
	//�^�C�g�����[�h�؂�ւ�(��)
	debug::setString("cursor:%d", nextcursor);


	//�\���L�[�őI��
	if (TRG(0) & PAD_RIGHT)
	{
		if (nextcursor % 2 == 0) {
			nextcursor++;
		}
	}

	if (TRG(0) & PAD_LEFT)
	{
		if (nextcursor % 2 == 1) {
			nextcursor--;
		}
	}

	if (TRG(0) & PAD_DOWN)
	{
		if (nextcursor <= 1) {
			nextcursor += 2;
		}
	}

	if (TRG(0) & PAD_UP)
	{
		if (nextcursor >= 2) {
			nextcursor -= 2;
		}
	}

	//�_�ŏ���

	if (nextcursor == cursor) {
		if (test_timer / 18 % 2 == 1) {
			alpha[cursor] = 1;
		}
		else {
			alpha[cursor] = 0;
		}
	}
	else {
		//alpha[cursor] = 1;
		for (int i = 0; i < 4; ++i) {
			alpha[i] = 1;
		}
	}

	cursor = nextcursor;
}

//�x���g�R���x�A�`��e�X�g
void test_testBeltConveyor() {

	//debug::setString("BeltConveyor_Texpos_R:%d", BeltConveyor_Texpos_R);
	debug::setString("UPkey:speedUp::::DOWNley:speedDown");
	//debug::setString("BeltConveyor_speed%d", BeltConveyor_speed);
	debug::setString("blet_y%d", blet_y);

	//�x���g�R���x�A�����E����
	//if (TRG(0) & PAD_RIGHT) {
	//	if (BeltConveyor_speed > 2)
	//		BeltConveyor_speed--;
	//}
	//if (TRG(0) & PAD_LEFT) {
	//	BeltConveyor_speed++;
	//}

	//�x���g�R���x�A���W�ύX
	//if (STATE(0) & PAD_UP) {
	//	blet_y--;
	//}
	//if (STATE(0) & PAD_DOWN) {
	//	blet_y++;
	//}

	//�x���g�R���x�A�A�j���[�V��������
	//test_timer / BeltConveyor_speed % 2;
	

}

//�V���t���֐�
//void shuffle(int order[], unsigned int size)
//{
//	unsigned int i, j;
//	int tmp;
//
//
//	i = size - 1;
//
//	while (i > 0) {
//
//		j = rand() % (i + 1);
//
//
//		tmp = order[j];
//		order[j] = order[i];
//		order[i] = tmp;
//
//		i--;
//	}
//}

void Player() {

	//debug::setString("direction:%lf",direction);
	//debug::setString("player_anime:%lf",player_anime);

	////��
	//if (TRG(0) & PAD_LEFT) {
	//	if (player_anime == 1)
	//		player_anime = 0;
	//}
	////�E
	//if (TRG(0) & PAD_RIGHT) {
	//	if (player_anime == 0)
	//		player_anime = 1;
	//}

	////��
	//if (TRG(0) & PAD_UP) {
	//	if (direction >= 1) {
	//		direction--;
	//	}
	//}
	////��
	//if (TRG(0) & PAD_DOWN) {
	//	if (direction <= 1) {
	//		direction++;
	//	}
	//}
}

//�H�����苗��
void eat_renfe() {

	primitive::line(
		EAT_RENGE_S_L, BELT_POS_Y,
		EAT_RENGE_E_L, BELT_POS_Y,
		//0,0,
		//100,100,
		0,1,0,1,
		10);
	primitive::line(
		EAT_RENGE_S_R, BELT_POS_Y,
		EAT_RENGE_E_R, BELT_POS_Y,
		//0,0,
		//100,100,
		0, 1, 0, 1,
		10);

}
