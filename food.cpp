#include "all.h"

int food_state;
int food_timer;

//int food_timer_num;	//�O���food_timer�L�^
int FoodDataNum;	//FoodData�̐�
int food_speed;	//�H�ו��̈ړ����x
int foodNum;	//���Ԃ�disup��true�ɂ���̂Ɏg��

int eat_calorie;//�擾�����J�����[��\������ϐ�(�l��-1�̎��͕\������ĂȂ�)

int timer_num_d;//�O���food_timer�L�^	disp

Sprite* combo_Reach;

//�R���{�p�ϐ�
int food_combo_group[3];//�����O���[�v�ł��邩���ׂ�(�����l��-1)
int food_combo[3];		//�����H�ו����Ȃ������ׂ�(�����l��-1)
int food_combo_disp[3];	//��ʂɕ\������(�����l��-1)
int combo_bonus;	//�R���{������
Sprite* Betubara;
Sprite* comboSet;	//�R���{�̖�
bool reach;	//���[�`��ԂȂ�(true)
bool combo;	//�R���{���(true)		�˃R���{����
bool betubara;	//�ʕ����(true)	true����ԃQ�[�W�������Ȃ�
int timer_num_c;//�O���food_timer�L�^	combo
int conbo_state;
int combo_name;	//���������R���{�̃Z�b�g�ԍ�

struct FOOD_DATA {
	Sprite* spr;				//�摜
	const wchar_t* filePath;	//�t�@�C���p�X
	int calorie;				//�J�����[(�ϐ�����)
	float hunger;				//�����Q�[�W(�݃Q�[�W������)(�ϐ�����)
	VECTOR2 pos_R;				//���� ���W
	VECTOR2 pos_L;				//���� ���W
	bool disp_R;				//���� ��ʕ\������	true:��ʕ\��
	bool disp_L;				//�E�� ��ʕ\������	true:��ʕ\��
	//bool eat;					//���H����		teue:���H
};

FOOD_DATA FoodData[/*��*/]{
	{NULL,L"./Data/Images/food00.png",600,15,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//���[����[0]
	{NULL,L"./Data/Images/food01.png",400,20,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//�`���[�n��[1]
	{NULL,L"./Data/Images/food02.png",200,10,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//�L�q[2]
	{NULL,L"./Data/Images/food03.png",180,8,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//���ɂ���[3]
	{NULL,L"./Data/Images/food04.png",130,6,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//��[4]
	{NULL,L"./Data/Images/food05.png",30,3,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//���X�`[5]
	{NULL,L"./Data/Images/food06.png",300,12,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//�n���o�[�K[6]
	{NULL,L"./Data/Images/food07.png",250,8,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//�|�e�g[7]
	{NULL,L"./Data/Images/food08.png",230,30,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//�R�[��[8]
	{NULL,L"./Data/Images/food09.png",0,50,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//�[���R�[��[9]
	{NULL,L"./Data/Images/food10.png",50,2,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//�z�^�e[10]
	{NULL,L"./Data/Images/food11.png",73,2,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//���܂�[11]
	{NULL,L"./Data/Images/food12.png",60,2,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false}//�܂���[12]
};///Data/Images/right.png

int food_order_L[sizeof(FoodData) / sizeof(FOOD_DATA)];	//�E���̕\�����鏇��
int food_order_R[sizeof(FoodData) / sizeof(FOOD_DATA)];	//�E���̕\�����鏇��

void food_init() {
	food_state = 0;
	food_timer = 0;
	//food_timer_num = 0;
	foodNum = 0;
	combo_bonus = 0;
	eat_calorie = -1;
	for (int i = 0; i < 3; i++)
	{food_combo_group[i] = -1; food_combo_disp[i] = -1; food_combo[i] = -1;}
	//[FoodData]�̐��擾
	FoodDataNum = sizeof(FoodData) / sizeof(FOOD_DATA);
	for (int i = 0; i < FoodDataNum; ++i) {food_order_L[i] = i; food_order_R[i] = i;}
	//FoodData������
	for (int i = 0; i < FoodDataNum; ++i) {
		FoodData[i].pos_R = { INIT_POS_R,BELT_POS_Y };
		FoodData[i].pos_L = { INIT_POS_L,BELT_POS_Y };
		FoodData[i].disp_R = false;
		FoodData[i].disp_L = false;
	}
	reach = false;
	combo = false;
	betubara = false;
	combo_name = 0;
	conbo_state = 0;
	timer_num_d = food_timer;
	timer_num_c = 0;
}

void food_deinit() {

	int detaNum = ARRAYSIZE(FoodData);//ARRAYSIZE(�z�񖼁j�Ŕz��T�C�Y�𓾂�

	for (int i = 0; i < detaNum; ++i) {
		safe_delete(FoodData[i].spr);
	}
	safe_delete(combo_Reach);
	safe_delete(Betubara);
}

void food_update() {

	switch (food_state) {
	case 0:
		////////  �����ݒ�  ////////

		//�X�v���C�g�ǂݍ���
		for (int i = 0; i < FoodDataNum; ++i) {
			FoodData[i].spr = sprite_load(FoodData[i].filePath);
		}
		combo_Reach = sprite_load(L"./Data/Images/combo_reach.png");
		Betubara = sprite_load(L"./Data/Images/betubara.png");
		comboSet = sprite_load(L"./Data/Images/combo_name.png");
		food_state++;
		/*fallthrough*/
	case 1:
		////////  �p�����[�^�ݒ�  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		food_speed = 5;

		//�����V���b�t��
		shuffle(food_order_R, sizeof(food_order_R) / sizeof(int));
		shuffle(food_order_L, sizeof(food_order_L) / sizeof(int));
		
		
		food_state++;
		/*fallthrough*/
	case 2:
		////////  �ʏ펞  ////////

		//�V���b�t���e�X�gR
		//for (int i = 0; i < dataNum; ++i) {
		//	debug::setString("food_order_R[%d]:%d", i, food_order_L[i]);
		//}

		//food_comco�\��
		//for (int i = 0; i < 3; ++i) { debug::setString("group[%d]:%d__kind:%d"
		//	, i, food_combo_group[i], food_combo[i]); }

		//debug::setString("foodNum%d:", foodNum);
		//debug::setString("food_timer:%d", food_timer);
		//debug::setString("player_direction:%lf", player_direction);

		//debug::setString("food_Num:%lf", player_direction);
		//debug::setString("dataNum:%d", FoodDataNum);
		//debug::setString("FoodData[food_order_R[foodNum]]:%d",food_order_R[foodNum]);
		//debug::setString("hungerGauge:%d", hungerGauge);
		//debug::setString("combo_bonus:%d", combo_bonus);
		//debug::setString("eat_calorie:%d", eat_calorie);
		//debug::setString("reach:%d", reach);
		//debug::setString("combo:%d", combo);
		//debug::setString("betubara:%d", betubara);

		//disp ����莞�Ԃ��Ƃ� on�@�ɂ��� 
		food_disp_on();

		//�H�ו��ړ��A�H�ׂ�����(��)
		food_move_eat();

		Combo();	//�R���{����������

		food_timer++;

		break;
	}
}

//food[].disp ���@true
void food_disp_on() {


	if (food_timer - timer_num_d > interval /food_speed) {

		//�E
		if (FoodData[food_order_R[foodNum]].disp_R == false) {
			FoodData[food_order_R[foodNum]].disp_R = true;
		}

		//��
		if (FoodData[food_order_L[foodNum]].disp_L == false) {
			FoodData[food_order_L[foodNum]].disp_L = true;

			foodNum++;
			if (foodNum >= FoodDataNum) {
				foodNum = 0;
			}
			timer_num_d = food_timer;
		}
	}

}

//�H�ו��ړ��E�H�ׂ�ꂽ����
void food_move_eat() {

	for (int i = 0; i < FoodDataNum; i++) {
		
		//�E
		if (FoodData[i].disp_R) {
			//�H�ו��ړ�
			if (FoodData[i].pos_R.x > SCREEN_W - BELTCONBEYOR_SIZE_W - FOOD_SIZE / 2) {
				FoodData[i].pos_R.x -= food_speed;
			}
			//�H�ׂ��ĂȂ�(��������)
			else if (FoodData[i].pos_R.y <= SCREEN_H + FOOD_SIZE) {
				FoodData[i].pos_R.y += 10;
			}
			//���Z�b�g
			else {
				FoodData[i].pos_R.x = INIT_POS_R;
				FoodData[i].pos_R.y = BELT_POS_Y;
				FoodData[i].disp_R = false;
			}
		}
		//��
		if (FoodData[i].disp_L) {
			//�H�ו��ړ�
			if (FoodData[i].pos_L.x < BELTCONBEYOR_SIZE_W + FOOD_SIZE / 2) {
				FoodData[i].pos_L.x += food_speed;
			}
			//�H�ׂ��ĂȂ�(��������)
			else if(FoodData[i].pos_L.y <= SCREEN_H + FOOD_SIZE){
				FoodData[i].pos_L.y += 10;
			}
			//���Z�b�g
			else {
				FoodData[i].pos_L.x = INIT_POS_L;
				FoodData[i].pos_L.y = BELT_POS_Y;
				FoodData[i].disp_L = false;
			}
			//�H�ׂ�ꂽ(eat on)
		}
			food_eat(i);
	}

}

//void food_move_reset(int i) {
//	FoodData[i].pos_L.x = -100;
//	FoodData[i].pos_L.y = BELT_POS_Y;
//	FoodData[i].disp_L = false;
//}

//�H������
void food_eat(int i) {
	//�E���������Ă���
	if (player_direction == player_right) {
		//food �� x�@EAT_RENGE_S_R �ȏ�@EAT_RENGE_F_R�@�ȉ� 
		if ((FoodData[i].pos_R.x >= EAT_RENGE_S_R) && (FoodData[i].pos_R.x <= EAT_RENGE_E_R)) {
			food_combo_load(i);	//�R���{�ԍ�����
			calorie += FoodData[i].calorie;//�J�����[���Z
			if(betubara){//�ʕ����
				betubara = false;
			}
			else {//�ʕ���ԂłȂ�
				hungerGauge += FoodData[i].hunger;//�󕠃Q�[�W���Z
			}
			//eat_calorie_disp(i);	//�擾�����J�����[��\��������
			//���Z�b�g
			FoodData[i].pos_R.x = INIT_POS_R;
			FoodData[i].pos_R.y = BELT_POS_Y;
			FoodData[i].disp_R = false;
		}
	}
	//�����������Ă���
	if (player_direction == player_left) {
		//food �� x�@EAT_RENGE_S_L �ȏ�@EAT_RENGE_F_L�@�ȉ� 
		if ((FoodData[i].pos_L.x >= EAT_RENGE_S_L) && (FoodData[i].pos_L.x <= EAT_RENGE_E_L)) {
			food_combo_load(i);	//�R���{�ԍ�����
			calorie += FoodData[i].calorie;//�J�����[���Z
			if (betubara) {//�ʕ����
				betubara = false;
			}
			else {//�ʕ���ԂłȂ�
				hungerGauge += FoodData[i].hunger;//�󕠃Q�[�W���Z
			}
			//eat_calorie_disp(i);	//�擾�����J�����[��\��������
			//���Z�b�g
			FoodData[i].pos_L.x = INIT_POS_L;
			FoodData[i].pos_L.y = BELT_POS_Y;
			FoodData[i].disp_L = false;
		}
	}

}

//�H�ׂ��H�ו��̃J�����[��\��(��)
void eat_calorie_disp(int eatNum) {
	static int state = 0;
	static int timer_num;//�O���food_timer�L�^

	//eat_calorie�Ɏ擾����(�\�����邷��)�J�����[����

	//��ʂɕ\������Ă��Ȃ��Ƃ�
	if (eat_calorie > 0) {
		eat_calorie = -1;	//��\���ɖ߂�
		state = 0;
	}
	//���ɉ�ʂɕ\������Ă���Ƃ�
	//�˂Ȃɂ����Ȃ�

	//��ʂɕ\��
	if (state == 0) {
		eat_calorie = FoodData[foodNum].calorie;
		timer_num = food_timer;
		state++;
	}
	//�ҋ@
	else if (state == 1) {
		if (food_timer - timer_num > 30) {
			eat_calorie = -1;	//��\���ɖ߂�
			state = 0;
		}
	}
	debug::setString("state:%d",state);

}

//�`�揈��
void food_render() {

	//�H�ו�
	for (int i = 0; i < FoodDataNum; ++i) {
		//�H�ו� �E��
		if (FoodData[i].disp_R) {
			sprite_render(FoodData[i].spr,				//�X�v���C�g
				FoodData[i].pos_R.x, FoodData[i].pos_R.y,	//���W
				1, 1,									//�X�P�[��
				0, 0,									//���摜�ʒu
				FOOD_SIZE, FOOD_SIZE,					//�摜�T�C�Y
				FOOD_SIZE / 2, FOOD_SIZE					//��_
			);

			////���S�ڈ�
			//primitive::circle(
			//	FoodData[i].pos_R.x, FoodData[i].pos_R.y,
			//	10,
			//	1, 1,
			//	ToRadian(0)
			//	, 1, 0, 0);
		}

		//�H�ו� ����
		if (FoodData[i].disp_L) {
			sprite_render(FoodData[i].spr,				//�X�v���C�g
				FoodData[i].pos_L.x, FoodData[i].pos_L.y,	//���W
				1, 1,									//�X�P�[��
				0, 0,									//���摜�ʒu
				FOOD_SIZE, FOOD_SIZE,					//�摜�T�C�Y
				FOOD_SIZE/2, FOOD_SIZE					//��_
			);

			////���S�ڈ�
			//primitive::circle(
			//	FoodData[i].pos_L.x, FoodData[i].pos_L.y,
			//	10,
			//	1,1,
			//	ToRadian(0)
			//	,1,0,0);
		}
	}

	//if(reach)
		Reach();

	//�擾�����J�����[��\��	
	if (eat_calorie > 0) {
		text_out(2, std::to_string(eat_calorie),
			100, 100,
			10, 10,
			0, 0, 0, 1); {

		}
	}

}

//////�R���{����

//�R���{�ԍ���food_combo�ɑ��
void food_combo_load(int eatNum/*�H�ׂ��H�ו��̔ԍ�*/) {

	//food_combo[0]��-1�Ȃ���
	if (food_combo_group[0] == -1) {
		food_combo_group[0] = food_combo_numberGet(eatNum);
		food_combo[0] = eatNum;
	}
	//food_combo[0]��-1�łȂ�food_combo[1]��-1
	else if(food_combo_group[1] == -1) {
		food_combo_group[1] = food_combo_numberGet(eatNum);
		food_combo[1] = eatNum;
		reach = true;
		if (combo)Combo_reset();
		food_combo_disp[0] = food_combo[0];
		food_combo_disp[1] = food_combo[1];
		food_combo_group_check(food_combo_group[0], food_combo_group[1],1);
		food_combo_check(food_combo[0], food_combo[1],2);
	}
	//food_combo[1]��-1�łȂ�food_combo[1]��-1
	else if(food_combo_group[2] == -1){
		food_combo_group[2] = food_combo_numberGet(eatNum);
		food_combo[2] = eatNum;
		food_combo_group_check(food_combo_group[1], food_combo_group[2],2);
		food_combo_check(food_combo[1], food_combo[2],2);
		//food_combo_check(food_combo[0], food_combo[2],2);
		//�R���{����	�R���{�����񐔂�+1����food_combo�����Z�b�g����
		if (food_combo_group[2] != -1) {
			food_combo_disp[2] = food_combo[2];
			combo_name = food_combo_group[0];
			reach = false;
			combo = true;
			betubara = true;
			combo_bonus++;
			for (int i = 0; i < 3; i++) { food_combo_group[i] = -1; };//���Z�b�g
			for (int i = 0; i < 3; i++) { food_combo[i] = -1; };
		}
	}
}

//�R���{�ԍ�(�O���[�v)�������łȂ��Ȃ烊�Z�b�g����
void food_combo_group_check(int combo,int nextCombo,int now/*�Ō�ɒl���������ӏ�*/) {
	//�R���{�������Ȃ�
	if (combo != nextCombo) {
		//���Z�b�g
		reach = false;
		//�Ō�ɐH�ׂ��H�ו���1�ڂɋL������
		food_combo_group[0] = food_combo_group[now];
		food_combo[0] = food_combo[now];
		for (int i = 1; i < 3; i++) { food_combo_group[i] = -1; };
		for (int i = 1; i < 3; i++) { food_combo[i] = -1; };
		for (int i = 0; i < 3; i++) { food_combo_disp[i] = -1; };
	}
	//�R���{�������Ȃ�
	//�ˉ������Ȃ�
}

//(���O���[�v����)���Ȃ��H�ו�������΃��Z�b�g����
void food_combo_check(int combo, int nextCombo,int now) {
	//�R���{�������Ȃ�
	if (combo == nextCombo) {
		//���Z�b�g
		reach = false;
		//�Ō�ɐH�ׂ��H�ו���1�ڂɋL������
		food_combo_group[0] = food_combo_group[now];
		food_combo[0] = food_combo[now];
		for (int i = 1; i < 3; i++) { food_combo_group[i] = -1; };
		for (int i = 1; i < 3; i++) { food_combo[i] = -1; };
		for (int i = 0; i < 3; i++) { food_combo_disp[i] = -1; };
	}
	//�����H�ו��łȂ����
	//�ˉ������Ȃ�
}

//�R���{�ԍ����擾
int food_combo_numberGet(int eatNum/*�H�ׂ��H�ו��̔ԍ�*/) {
	//debug::setString("eatNum:%")
	//����[0]
	if ((eatNum == chahan) || (eatNum == ramen) || (eatNum == gyouza))
		return china;
	//���{�̒��H[1]
	if ((eatNum == onigiri) || (eatNum == syake) || (eatNum == miso))
		return japan;
	//�j�R�j�R�Z�b�g[2]
	if ((eatNum == hanbaga) || (eatNum == poteto) || (eatNum == kora))
		return happy;
	//���i[3]
	if ((eatNum == hotate) || (eatNum == tamago) || (eatNum == maguro))
		return sushi;

	return -1;
}

//�R���{���[�`(�`��)
void Reach() {

	if (reach || combo) {
		//�Ŕ�
		sprite_render(combo_Reach, 342, 89,	//���W
			1, 1,							//�X�P�[��
			COMBOREACH_W * (food_timer / 7 % 5), 0,				//�摜�ʒu
			COMBOREACH_W, COMBOREACH_W);	//���E����
		//food_combo[0]
		//�H�ו�1��
		sprite_render(FoodData[food_combo_disp[0]].spr, 386, 265,
			1, 1,
			0, 0,
			FOOD_SIZE, FOOD_SIZE);

		//�H�ו�2��
		sprite_render(FoodData[food_combo_disp[1]].spr, 593, 239,
			1, 1,
			0, 0,
			FOOD_SIZE, FOOD_SIZE);

		//�H�ו�3��
		sprite_render(FoodData[food_combo_disp[2]].spr, 808, 200,
			1, 1,
			0, 0,
			FOOD_SIZE, FOOD_SIZE);
	}

	if (combo) {
		sprite_render(Betubara, 870, 145, 1, 1);	//�ʕ�
		//�R���{�l�[��
		sprite_render(comboSet,
			265, 80,
			1, 1,
			0, COMBOSET_H * combo_name,
			COMBOSET_W, COMBOSET_H,
			0,0,
			ToRadian(0), 1, 0, 0, 1
		);
	}
	
}

void Combo() {
	//debug::setString("conbo_state:%d", conbo_state);
	if (combo) {
		//�ҋ@
		if (conbo_state == 0) {
			timer_num_c = food_timer;
			conbo_state++;
		}
		//���Z�b�g
		else if (conbo_state == 1) {
			if (food_timer - timer_num_c > 100) {
				Combo_reset();
			}
		}
	}
}

void Combo_reset() {
	combo = false;
	conbo_state = 0;
	for (int i = 0; i < 3; i++) { food_combo_disp[i] = -1; };
}