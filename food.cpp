#include "all.h"

int food_state;
int food_timer;

//int food_timer_num;	//前回のfood_timer記録
int FoodDataNum;	//FoodDataの数
int food_speed;	//食べ物の移動速度
int foodNum;	//順番にdisupをtrueにするのに使う

int eat_calorie;//取得したカロリーを表示する変数(値が-1の時は表示されてない)

int timer_num_d;//前回のfood_timer記録	disp

Sprite* combo_Reach;

//コンボ用変数
int food_combo_group[3];//同じグループであるか調べる(初期値は-1)
int food_combo[3];		//同じ食べ物がないか調べる(初期値は-1)
int food_combo_disp[3];	//画面に表示する(初期値は-1)
int combo_bonus;	//コンボ発生回数
Sprite* Betubara;
Sprite* comboSet;	//コンボの名
bool reach;	//リーチ状態なら(true)
bool combo;	//コンボ状態(true)		⇒コンボ成功
bool betubara;	//別腹状態(true)	true時空間ゲージ増加しない
int timer_num_c;//前回のfood_timer記録	combo
int conbo_state;
int combo_name;	//成功したコンボのセット番号

struct FOOD_DATA {
	Sprite* spr;				//画像
	const wchar_t* filePath;	//ファイルパス
	int calorie;				//カロリー(変数名仮)
	float hunger;				//満腹ゲージ(胃ゲージ増加量)(変数名仮)
	VECTOR2 pos_R;				//左側 座標
	VECTOR2 pos_L;				//左側 座標
	bool disp_R;				//左側 画面表示判定	true:画面表示
	bool disp_L;				//右側 画面表示判定	true:画面表示
	//bool eat;					//完食判定		teue:完食
};

FOOD_DATA FoodData[/*仮*/]{
	{NULL,L"./Data/Images/food00.png",600,15,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//ラーメン[0]
	{NULL,L"./Data/Images/food01.png",400,20,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//チャーハン[1]
	{NULL,L"./Data/Images/food02.png",200,10,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//餃子[2]
	{NULL,L"./Data/Images/food03.png",180,8,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//おにぎり[3]
	{NULL,L"./Data/Images/food04.png",130,6,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//鮭[4]
	{NULL,L"./Data/Images/food05.png",30,3,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//味噌汁[5]
	{NULL,L"./Data/Images/food06.png",300,12,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//ハンバーガ[6]
	{NULL,L"./Data/Images/food07.png",250,8,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//ポテト[7]
	{NULL,L"./Data/Images/food08.png",230,30,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//コーラ[8]
	{NULL,L"./Data/Images/food09.png",0,50,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//ゼロコーラ[9]
	{NULL,L"./Data/Images/food10.png",50,2,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//ホタテ[10]
	{NULL,L"./Data/Images/food11.png",73,2,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false},//たまご[11]
	{NULL,L"./Data/Images/food12.png",60,2,{INIT_POS_R,BELT_POS_Y},{INIT_POS_L,BELT_POS_Y},false,false}//まぐろ[12]
};///Data/Images/right.png

int food_order_L[sizeof(FoodData) / sizeof(FOOD_DATA)];	//右側の表示する順番
int food_order_R[sizeof(FoodData) / sizeof(FOOD_DATA)];	//右側の表示する順番

void food_init() {
	food_state = 0;
	food_timer = 0;
	//food_timer_num = 0;
	foodNum = 0;
	combo_bonus = 0;
	eat_calorie = -1;
	for (int i = 0; i < 3; i++)
	{food_combo_group[i] = -1; food_combo_disp[i] = -1; food_combo[i] = -1;}
	//[FoodData]の数取得
	FoodDataNum = sizeof(FoodData) / sizeof(FOOD_DATA);
	for (int i = 0; i < FoodDataNum; ++i) {food_order_L[i] = i; food_order_R[i] = i;}
	//FoodData初期化
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

	int detaNum = ARRAYSIZE(FoodData);//ARRAYSIZE(配列名）で配列サイズを得る

	for (int i = 0; i < detaNum; ++i) {
		safe_delete(FoodData[i].spr);
	}
	safe_delete(combo_Reach);
	safe_delete(Betubara);
}

void food_update() {

	switch (food_state) {
	case 0:
		////////  初期設定  ////////

		//スプライト読み込み
		for (int i = 0; i < FoodDataNum; ++i) {
			FoodData[i].spr = sprite_load(FoodData[i].filePath);
		}
		combo_Reach = sprite_load(L"./Data/Images/combo_reach.png");
		Betubara = sprite_load(L"./Data/Images/betubara.png");
		comboSet = sprite_load(L"./Data/Images/combo_name.png");
		food_state++;
		/*fallthrough*/
	case 1:
		////////  パラメータ設定  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		food_speed = 5;

		//初期シャッフル
		shuffle(food_order_R, sizeof(food_order_R) / sizeof(int));
		shuffle(food_order_L, sizeof(food_order_L) / sizeof(int));
		
		
		food_state++;
		/*fallthrough*/
	case 2:
		////////  通常時  ////////

		//シャッフルテストR
		//for (int i = 0; i < dataNum; ++i) {
		//	debug::setString("food_order_R[%d]:%d", i, food_order_L[i]);
		//}

		//food_comco表示
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

		//disp を一定時間ごとに on　にする 
		food_disp_on();

		//食べ物移動、食べた処理(仮)
		food_move_eat();

		Combo();	//コンボ成功時処理

		food_timer++;

		break;
	}
}

//food[].disp を　true
void food_disp_on() {


	if (food_timer - timer_num_d > interval /food_speed) {

		//右
		if (FoodData[food_order_R[foodNum]].disp_R == false) {
			FoodData[food_order_R[foodNum]].disp_R = true;
		}

		//左
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

//食べ物移動・食べられた処理
void food_move_eat() {

	for (int i = 0; i < FoodDataNum; i++) {
		
		//右
		if (FoodData[i].disp_R) {
			//食べ物移動
			if (FoodData[i].pos_R.x > SCREEN_W - BELTCONBEYOR_SIZE_W - FOOD_SIZE / 2) {
				FoodData[i].pos_R.x -= food_speed;
			}
			//食べられてない(落下する)
			else if (FoodData[i].pos_R.y <= SCREEN_H + FOOD_SIZE) {
				FoodData[i].pos_R.y += 10;
			}
			//リセット
			else {
				FoodData[i].pos_R.x = INIT_POS_R;
				FoodData[i].pos_R.y = BELT_POS_Y;
				FoodData[i].disp_R = false;
			}
		}
		//左
		if (FoodData[i].disp_L) {
			//食べ物移動
			if (FoodData[i].pos_L.x < BELTCONBEYOR_SIZE_W + FOOD_SIZE / 2) {
				FoodData[i].pos_L.x += food_speed;
			}
			//食べられてない(落下する)
			else if(FoodData[i].pos_L.y <= SCREEN_H + FOOD_SIZE){
				FoodData[i].pos_L.y += 10;
			}
			//リセット
			else {
				FoodData[i].pos_L.x = INIT_POS_L;
				FoodData[i].pos_L.y = BELT_POS_Y;
				FoodData[i].disp_L = false;
			}
			//食べられた(eat on)
		}
			food_eat(i);
	}

}

//void food_move_reset(int i) {
//	FoodData[i].pos_L.x = -100;
//	FoodData[i].pos_L.y = BELT_POS_Y;
//	FoodData[i].disp_L = false;
//}

//食事処理
void food_eat(int i) {
	//右側を向いている
	if (player_direction == player_right) {
		//food の x　EAT_RENGE_S_R 以上　EAT_RENGE_F_R　以下 
		if ((FoodData[i].pos_R.x >= EAT_RENGE_S_R) && (FoodData[i].pos_R.x <= EAT_RENGE_E_R)) {
			food_combo_load(i);	//コンボ番号を代入
			calorie += FoodData[i].calorie;//カロリー加算
			if(betubara){//別腹状態
				betubara = false;
			}
			else {//別腹状態でない
				hungerGauge += FoodData[i].hunger;//空腹ゲージ加算
			}
			//eat_calorie_disp(i);	//取得したカロリーを表示させる
			//リセット
			FoodData[i].pos_R.x = INIT_POS_R;
			FoodData[i].pos_R.y = BELT_POS_Y;
			FoodData[i].disp_R = false;
		}
	}
	//左側を向いている
	if (player_direction == player_left) {
		//food の x　EAT_RENGE_S_L 以上　EAT_RENGE_F_L　以下 
		if ((FoodData[i].pos_L.x >= EAT_RENGE_S_L) && (FoodData[i].pos_L.x <= EAT_RENGE_E_L)) {
			food_combo_load(i);	//コンボ番号を代入
			calorie += FoodData[i].calorie;//カロリー加算
			if (betubara) {//別腹状態
				betubara = false;
			}
			else {//別腹状態でない
				hungerGauge += FoodData[i].hunger;//空腹ゲージ加算
			}
			//eat_calorie_disp(i);	//取得したカロリーを表示させる
			//リセット
			FoodData[i].pos_L.x = INIT_POS_L;
			FoodData[i].pos_L.y = BELT_POS_Y;
			FoodData[i].disp_L = false;
		}
	}

}

//食べた食べ物のカロリーを表示(仮)
void eat_calorie_disp(int eatNum) {
	static int state = 0;
	static int timer_num;//前回のfood_timer記録

	//eat_calorieに取得した(表示するする)カロリーを代入

	//画面に表示されていないとき
	if (eat_calorie > 0) {
		eat_calorie = -1;	//非表示に戻す
		state = 0;
	}
	//既に画面に表示されているとき
	//⇒なにもしない

	//画面に表示
	if (state == 0) {
		eat_calorie = FoodData[foodNum].calorie;
		timer_num = food_timer;
		state++;
	}
	//待機
	else if (state == 1) {
		if (food_timer - timer_num > 30) {
			eat_calorie = -1;	//非表示に戻す
			state = 0;
		}
	}
	debug::setString("state:%d",state);

}

//描画処理
void food_render() {

	//食べ物
	for (int i = 0; i < FoodDataNum; ++i) {
		//食べ物 右側
		if (FoodData[i].disp_R) {
			sprite_render(FoodData[i].spr,				//スプライト
				FoodData[i].pos_R.x, FoodData[i].pos_R.y,	//座標
				1, 1,									//スケール
				0, 0,									//元画像位置
				FOOD_SIZE, FOOD_SIZE,					//画像サイズ
				FOOD_SIZE / 2, FOOD_SIZE					//基準点
			);

			////中心目印
			//primitive::circle(
			//	FoodData[i].pos_R.x, FoodData[i].pos_R.y,
			//	10,
			//	1, 1,
			//	ToRadian(0)
			//	, 1, 0, 0);
		}

		//食べ物 左側
		if (FoodData[i].disp_L) {
			sprite_render(FoodData[i].spr,				//スプライト
				FoodData[i].pos_L.x, FoodData[i].pos_L.y,	//座標
				1, 1,									//スケール
				0, 0,									//元画像位置
				FOOD_SIZE, FOOD_SIZE,					//画像サイズ
				FOOD_SIZE/2, FOOD_SIZE					//基準点
			);

			////中心目印
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

	//取得したカロリーを表示	
	if (eat_calorie > 0) {
		text_out(2, std::to_string(eat_calorie),
			100, 100,
			10, 10,
			0, 0, 0, 1); {

		}
	}

}

//////コンボ処理

//コンボ番号をfood_comboに代入
void food_combo_load(int eatNum/*食べた食べ物の番号*/) {

	//food_combo[0]が-1なら代入
	if (food_combo_group[0] == -1) {
		food_combo_group[0] = food_combo_numberGet(eatNum);
		food_combo[0] = eatNum;
	}
	//food_combo[0]が-1でなくfood_combo[1]が-1
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
	//food_combo[1]が-1でなくfood_combo[1]が-1
	else if(food_combo_group[2] == -1){
		food_combo_group[2] = food_combo_numberGet(eatNum);
		food_combo[2] = eatNum;
		food_combo_group_check(food_combo_group[1], food_combo_group[2],2);
		food_combo_check(food_combo[1], food_combo[2],2);
		//food_combo_check(food_combo[0], food_combo[2],2);
		//コンボ成功	コンボ発生回数に+1してfood_comboをリセットする
		if (food_combo_group[2] != -1) {
			food_combo_disp[2] = food_combo[2];
			combo_name = food_combo_group[0];
			reach = false;
			combo = true;
			betubara = true;
			combo_bonus++;
			for (int i = 0; i < 3; i++) { food_combo_group[i] = -1; };//リセット
			for (int i = 0; i < 3; i++) { food_combo[i] = -1; };
		}
	}
}

//コンボ番号(グループ)が同じでないならリセットする
void food_combo_group_check(int combo,int nextCombo,int now/*最後に値が入った箇所*/) {
	//コンボが同じなら
	if (combo != nextCombo) {
		//リセット
		reach = false;
		//最後に食べた食べ物を1つ目に記憶する
		food_combo_group[0] = food_combo_group[now];
		food_combo[0] = food_combo[now];
		for (int i = 1; i < 3; i++) { food_combo_group[i] = -1; };
		for (int i = 1; i < 3; i++) { food_combo[i] = -1; };
		for (int i = 0; i < 3; i++) { food_combo_disp[i] = -1; };
	}
	//コンボが同じなら
	//⇒何もしない
}

//(同グループ内で)おなじ食べ物があればリセットする
void food_combo_check(int combo, int nextCombo,int now) {
	//コンボが同じなら
	if (combo == nextCombo) {
		//リセット
		reach = false;
		//最後に食べた食べ物を1つ目に記憶する
		food_combo_group[0] = food_combo_group[now];
		food_combo[0] = food_combo[now];
		for (int i = 1; i < 3; i++) { food_combo_group[i] = -1; };
		for (int i = 1; i < 3; i++) { food_combo[i] = -1; };
		for (int i = 0; i < 3; i++) { food_combo_disp[i] = -1; };
	}
	//同じ食べ物でなければ
	//⇒何もしない
}

//コンボ番号を取得
int food_combo_numberGet(int eatNum/*食べた食べ物の番号*/) {
	//debug::setString("eatNum:%")
	//中華[0]
	if ((eatNum == chahan) || (eatNum == ramen) || (eatNum == gyouza))
		return china;
	//日本の朝食[1]
	if ((eatNum == onigiri) || (eatNum == syake) || (eatNum == miso))
		return japan;
	//ニコニコセット[2]
	if ((eatNum == hanbaga) || (eatNum == poteto) || (eatNum == kora))
		return happy;
	//寿司[3]
	if ((eatNum == hotate) || (eatNum == tamago) || (eatNum == maguro))
		return sushi;

	return -1;
}

//コンボリーチ(描画)
void Reach() {

	if (reach || combo) {
		//看板
		sprite_render(combo_Reach, 342, 89,	//座標
			1, 1,							//スケール
			COMBOREACH_W * (food_timer / 7 % 5), 0,				//画像位置
			COMBOREACH_W, COMBOREACH_W);	//幅・高さ
		//food_combo[0]
		//食べ物1つ目
		sprite_render(FoodData[food_combo_disp[0]].spr, 386, 265,
			1, 1,
			0, 0,
			FOOD_SIZE, FOOD_SIZE);

		//食べ物2つ目
		sprite_render(FoodData[food_combo_disp[1]].spr, 593, 239,
			1, 1,
			0, 0,
			FOOD_SIZE, FOOD_SIZE);

		//食べ物3つ目
		sprite_render(FoodData[food_combo_disp[2]].spr, 808, 200,
			1, 1,
			0, 0,
			FOOD_SIZE, FOOD_SIZE);
	}

	if (combo) {
		sprite_render(Betubara, 870, 145, 1, 1);	//別腹
		//コンボネーム
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
		//待機
		if (conbo_state == 0) {
			timer_num_c = food_timer;
			conbo_state++;
		}
		//リセット
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