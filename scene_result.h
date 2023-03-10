#ifndef RESULT
#define RESULT

#define COMBOBONUS 1500 //1コンボの追加点
#define LEVEL_SIZE_X 648	//(胃)レベルサイズX
#define LEVEL_SIZE_Y 75		//(胃)レベルサイズY

#define BABY_LEVEL 10000		//赤ちゃんレベル
#define CHILD_LEVEL 12000		//子供レベル
#define GENERAL_LEVEL 20000		//一般人レベル
#define GLITTON_LEVEL 30000		//食いしん坊レベル
#define FIGHTER_LEVEL 35000		//フードファイターレベル
#define ELEPHANT_LEVEL 40000		//ゾウレベル
#define WHALE_LEVEL 50000		//クジラレベル

enum LEVEL {
	baby = 0,
	child,
	general,
	glutton,
	fighter,
	elephant,
	whale
};

//関数プロトタイプ宣言
void result_init();
void result_deinit();
void result_update();
void result_render();

int Digit(int num);	//桁数を調べる
void stomachlevel();//(胃)レベルを調べる

#endif