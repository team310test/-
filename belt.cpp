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
		////////  初期設定  ////////

		//ベルトコンベア描画テスト
		BeltConveyorRight = sprite_load(L"./Data/Images/belt conveyor Right.png");
		BeltConveyorLeft = sprite_load(L"./Data/Images/belt conveyor Left.png");

		belt_state++;
		/*fallthrough*/

	case 1:
		////////  パラメータ設定  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		belt_state++;
		/*fallthrough*/
	case 2:
		////////  通常時  ////////

		BeltConveyor_Texpos = (belt_timer / BeltConveyor_speed % 2) * BELTCONBEYOR_SIZE_W;

		belt_timer++;

		break;
	}
}

void belt_render() {
	//ベルトコンベア右
	sprite_render(BeltConveyorRight,	//ポインタ
		SCREEN_W - BELTCONBEYOR_SIZE_W, blet_y,						//表示座標
		1, 1,							//表示スケール
		BeltConveyor_Texpos, 0,		//元画像位置
		BELTCONBEYOR_SIZE_W, BELTCONBEYOR_SIZE_H,//元画像サイズ
		0, 0,
		ToRadian(0),
		1, 1, 1, 1);
	//ベルトコンベア左
	sprite_render(BeltConveyorLeft,	//ポインタ
		0, blet_y,						//表示座標
		1, 1,							//表示スケール
		BeltConveyor_Texpos, 0,		//元画像位置
		BELTCONBEYOR_SIZE_W, BELTCONBEYOR_SIZE_H,//元画像サイズ
		0, 0,
		ToRadian(0),
		1, 1, 1, 1);
}