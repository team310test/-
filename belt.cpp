#include "all.h"

int belt_timer;
int belt_state;

int blet_y;
int BeltConveyor_Texpos;
int BeltConveyor_speed;
Sprite* BeltConveyorRight;
Sprite* BeltConveyorLeft;

void belt_init() {
	belt_timer = 0;
	belt_state = 0;

	BeltConveyor_Texpos = 0;
	BeltConveyor_speed = 5;
	blet_y = BELT_POS_Y;
}

void belt_deinit() {
	safe_delete(BeltConveyorRight);
	safe_delete(BeltConveyorLeft);
}

void belt_update() {

	switch (belt_state) {
	case 0:
		////////  �����ݒ�  ////////

		//�x���g�R���x�A�`��e�X�g
		BeltConveyorRight = sprite_load(L"./Data/Images/belt conveyor Right.png");
		BeltConveyorLeft = sprite_load(L"./Data/Images/belt conveyor Left.png");

		belt_state++;
		/*fallthrough*/

	case 1:
		////////  �p�����[�^�ݒ�  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		belt_state++;
		/*fallthrough*/
	case 2:
		////////  �ʏ펞  ////////

		BeltConveyor_Texpos = (belt_timer / BeltConveyor_speed % 2) * BELTCONBEYOR_SIZE_W;

		belt_timer++;

		break;
	}
}

void belt_render() {
	//�x���g�R���x�A�E
	sprite_render(BeltConveyorRight,	//�|�C���^
		SCREEN_W - BELTCONBEYOR_SIZE_W, blet_y,						//�\�����W
		1, 1,							//�\���X�P�[��
		BeltConveyor_Texpos, 0,		//���摜�ʒu
		BELTCONBEYOR_SIZE_W, BELTCONBEYOR_SIZE_H,//���摜�T�C�Y
		0, 0,
		ToRadian(0),
		1, 1, 1, 1);
	//�x���g�R���x�A��
	sprite_render(BeltConveyorLeft,	//�|�C���^
		0, blet_y,						//�\�����W
		1, 1,							//�\���X�P�[��
		BeltConveyor_Texpos, 0,		//���摜�ʒu
		BELTCONBEYOR_SIZE_W, BELTCONBEYOR_SIZE_H,//���摜�T�C�Y
		0, 0,
		ToRadian(0),
		1, 1, 1, 1);
}