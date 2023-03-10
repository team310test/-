#include "all.h"

int test_state;
int test_timer;

//食べ物処理
bool food;
bool disp_R[halfFoodMAX];	//右側の食べ物表示判定(tlre:表示)
bool eat_R[halfFoodMAX];	//右側の食べたかの判定(tlre:食べられてない)

int order_R[halfFoodMAX];	//右側の表示する順番
int order_ALL[foodMAX];		//全体の表示する順番

int stageFoodMAX[3] = { 10, 20, 30 };  //ステージごとの最大値
int stage_No = 2;	//現ステージ番号(仮)

//struct FOOD_DETA {
//	Sprite* spr;				//画像
//	const wchar_t* filePath;	//ファイルパス
//	//char name[16];				//料理名
//	int karori;					//カロリー(変数名仮)
//	float mannpuku;				//満腹ゲージ(胃ゲージ増加量)(変数名仮)
//	VECTOR2 pos;				//座標
//	//float Texpos;				//基準点
//};

//FOOD_DETA FoodDeta[/*仮*/]{
//	{NULL,L"./Data/Images/food00.png",1,11,{100,100}, },
//	{NULL,L"./Data/Images/food01.png",2,22,{200,100}},
//	{NULL,L"./Data/Images/food02.png",3,33,{300,100}}
//};


//タイトルモード切り替え(仮)
bool title;	//タイトルモード切り替え動作切り替え
int nextcursor;
int cursor;
int alpha[4];
Sprite* Back1;
Sprite* Back2;
Sprite* Back3;
Sprite* Back4;

//ベルトコンベア描画テスト
bool belt;	//ベルトコンベア描画テスト動作切り替え

//int BeltConveyor_anime_R;
//int BeltConveyor_anime_L;
//int BeltConveyor_Texpos_L;

//人描画テスト
bool hito;
bool hito_move;

//初期設定
void test_init() {

	test_state = 0;
	test_timer = 0;

	//タイトルモード切り替え(仮)
	title = false;
	nextcursor = 0;
	cursor = 0;
	for (int i = 0; i < 4; ++i) {alpha[i] = 1;}

	//ベルトコンベア描画テスト
	belt = true;

	//BeltConveyor_anime_R = 0;
	//BeltConveyor_anime_L = 0;
	//BeltConveyor_Texpos_L = 0;

	//人描画
	hito = false;
	hito_move = false;

	//食べ物処理
	food = false;


	//food.cppテスト
	food_init();

	//player.cppテスト
	player_init();

}

//終了処理
void test_deinit() {

	//safe_delete(sprCar);
	food_deinit();
	player_deinit();
}

//更新処理
void test_update() {

	switch (test_state)
	{
	case 0:
		////////  初期設定  ////////
		
		test_loadimage();

		//シャッフル関数テスト

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
		////////  パラメータ設定  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		test_state++;
		/*fallthrough*/
	case 2:
		////////  通常時  ////////
		debug::setString("title_timer:%d", test_timer);
		debug::setString("title_state:%d", test_state);

		srand((unsigned int)time(NULL));

		///////	タイトルモード切り替えテスト  ///////
		debug::setString("[1]titl:%d",title);
		if(title)
			test_title();	
		//[1]でtaitle on,off
		if (GetAsyncKeyState('1') & 1) {
			if (title)
				title = false;
			else
				title = true;
		}

		///////	タイトルモード切り替えテスト  ///////
		debug::setString("[2]belt:%d",belt);
		if (belt)
			test_testBeltConveyor();
			//[1]でtaitle on,off
		if (GetAsyncKeyState('2') & 1) {
			if (belt)
				belt = false;
			else
				belt = true;
		}

		///////	食べ物処理切り替えテスト  ///////
		debug::setString("[3]food:%d",food);
		if (belt)
			test_testBeltConveyor();
		//[3]でtaitle on,off
		if (GetAsyncKeyState('3') & 1) {
			if (food)
				food = false;
			else {
				food = true;
				shuffle(order_ALL, /*sizeof(order_ALL) / sizeof(order_ALL[0])*/stageFoodMAX[stage_No]);
			}
		}
		//oreder_ALL 表示
		if (food) {

			for (int i = 0; i < stageFoodMAX[stage_No]; ++i) {
				debug::setString("order_ALL[%d]:%d", i, order_ALL[i]);
			}
		}

		//food_updeta テスト
		food_update();

		///////	人描画描画切り替えテスト  ///////
		debug::setString("[4]hito:%d", hito);debug::setString("[5]hito_move:%d", hito_move);
		if (belt)
			test_testBeltConveyor();
		//[4]でhito on,off
		if (GetAsyncKeyState('4') & 1) {
			if (hito)
				hito = false;
			else {
				hito = true;
			}
		}
		//[5]でhito_move on,off
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


		//player.cppテスト
		player_update();

		//ボタンを押したらゲーム画面へ遷移
		if (TRG(0) & PAD_START) {
			nextScene = SCENE_GAME;
		}

		break;
	}

	test_timer++;
}

//描画処理
void test_render() {

	GameLib::clear(0, 1, 1);

	//タイトルモード切り替え(仮)
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
	//ベルトコンベア描画テスト
	if (belt) {

	}
	//food.cppテスト
	food_render();
	//player.cppテスト
	player_render();
	if (hito) {
		
	}

}

//画像読み込み
void test_loadimage() {
	//タイトルモード切り替え(仮)
	Back1 = sprite_load(L"./Data/Images/right.png");
	Back2 = sprite_load(L"./Data/Images/right.png");
	Back3 = sprite_load(L"./Data/Images/right.png");
	Back4 = sprite_load(L"./Data/Images/right.png");

	
}

//タイトルモード選択テスト
void test_title() {
	//タイトルモード切り替え(仮)
	debug::setString("cursor:%d", nextcursor);


	//十字キーで選択
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

	//点滅処理

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

//ベルトコンベア描画テスト
void test_testBeltConveyor() {

	//debug::setString("BeltConveyor_Texpos_R:%d", BeltConveyor_Texpos_R);
	debug::setString("UPkey:speedUp::::DOWNley:speedDown");
	//debug::setString("BeltConveyor_speed%d", BeltConveyor_speed);
	debug::setString("blet_y%d", blet_y);

	//ベルトコンベア加速・減速
	//if (TRG(0) & PAD_RIGHT) {
	//	if (BeltConveyor_speed > 2)
	//		BeltConveyor_speed--;
	//}
	//if (TRG(0) & PAD_LEFT) {
	//	BeltConveyor_speed++;
	//}

	//ベルトコンベア座標変更
	//if (STATE(0) & PAD_UP) {
	//	blet_y--;
	//}
	//if (STATE(0) & PAD_DOWN) {
	//	blet_y++;
	//}

	//ベルトコンベアアニメーション処理
	//test_timer / BeltConveyor_speed % 2;
	

}

//シャフル関数
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

	////左
	//if (TRG(0) & PAD_LEFT) {
	//	if (player_anime == 1)
	//		player_anime = 0;
	//}
	////右
	//if (TRG(0) & PAD_RIGHT) {
	//	if (player_anime == 0)
	//		player_anime = 1;
	//}

	////上
	//if (TRG(0) & PAD_UP) {
	//	if (direction >= 1) {
	//		direction--;
	//	}
	//}
	////下
	//if (TRG(0) & PAD_DOWN) {
	//	if (direction <= 1) {
	//		direction++;
	//	}
	//}
}

//食事判定距離
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
