#ifndef TEST_H
#define TEST_H

//食べ物処理
#define foodMAX (30)
#define halfFoodMAX (foodMAX / 2)

extern int blet_y;	//ベルトコンベアの座標

//関数プロトタイプ宣言
void test_init();
void test_deinit();
void test_update();
void test_render();

void test_loadimage();	//画像読み込み

//動作テスト関数
void test_title();	//タイトル画面(モード選択
void test_testBeltConveyor();	//ベルトコンベア描画テスト
void Player();	//人描画テスト

void eat_renfe();	//食事範囲目印

#endif
