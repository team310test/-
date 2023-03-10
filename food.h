#ifndef FOOD_H
#define FOOD_H

#define interval 150	//表示する食べ物の間隔
#define INIT_POS_L -100
#define INIT_POS_R SCREEN_W + 100

//コンボリーチの幅・高さ
#define COMBOREACH_W 620
#define COMBOREACH_H 380

//コンボ名テキストの幅・高さ
#define COMBOSET_W 800
#define COMBOSET_H 100

extern int combo_bonus;	//コンボ発生回数

//料理名番号
enum {
	chahan=0,	//チャーハン
	ramen,		//ラーメン
	gyouza,		//餃子
	onigiri,	//おにぎり
	syake,		//鮭
	miso,		//味噌汁
	hanbaga,	//ハンバーガ
	poteto,		//ポテト
	kora,		//コーラ
	zerokora,	//ゼロカロリーコーラ
	hotate,		//ホタテ寿司
	tamago,		//タマゴ寿司
	maguro		//マグロ寿司
};

//コンボ番号
enum {
	china = 0,	//中華コンボ
	japan,		//日本の朝食コンボ
	happy,		//ニコニココンボ
	sushi		//寿司コンボ
};

//関数プロトタイプ宣言
void food_init();
void food_deinit();
void food_update();
void food_render();
void food_move_eat();	//食べ物移動処理
void food_eat(int i);	//食べ物食事処理
//void food_move_reset(int i);//食べ物移動リセット
void food_disp_on();//disp を一定時間ごとに on　にする 
int food_combo_numberGet(int eatNum/*食べた食べ物の番号*/);//コンボ番号を取得
void eat_calorie_disp(int eatNum);
void food_combo_load(int eatNum);
void food_combo_group_check(int combo, int nextCombo, int now/*最後に値が入った箇所*/);
void food_combo_check(int combo, int nextCombo, int now);//(同グループ内で)おなじ食べ物があればリセットする
void Reach();
void Combo();
void Combo_reset();

#endif