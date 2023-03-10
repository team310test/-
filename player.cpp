#include "all.h"

int player_state;
int player_timer;
int player_timer_num;	//一つ前のtimerの値

Sprite* player_Image;	//自機画像
Sprite* stomach;		//空腹ゲージ(胃)
float player_direction;	//向き(0:正面,1:左,2:右)
float player_anime;	//アニメーション(現状2コマ)
bool coolDown;	//クールダウン中(true)	キー操作受け付けなくなる

//スコア表示
int calorie;		//取得したカロリーを保存する変数
int hungerGauge;

//初期設定
void player_init() {
	player_state = 0;
	player_timer = 0;
	player_timer_num = 0;

	player_direction = 0;
	player_anime = 0;
	coolDown = false;

	calorie = 0;
}

//削除
void player_deinit() {
	safe_delete(player_Image);
	safe_delete(stomach);
}

//更新処理
void player_update() {

	switch (player_state) {
	case 0:
		////////  初期設定  ////////

		player_Image = sprite_load(L"./Data/Images/player.png");
		stomach = sprite_load(L"./Data/Images/stomach.png");
		player_state++;
		/*fallthrough*/

	case 1:
		////////  パラメータ設定  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		player_state++;
		/*fallthrough*/
	case 2:
		////////  通常時  ////////

		stomach_gauge();	//胃ゲージ(空腹ゲージ)処理

		//クールダウンでなければ(coolDownがfalseであれば)
		if (!coolDown) {
			//プレイヤーの操作
			player_control();
		}
		else {
			cool_down();	//クールダウン処理
		}

		break;
	}
	player_timer++;
	debug::setString("player_timer:%d", player_timer);
}

//描画処理
void player_render() {
	//自機
	sprite_render(player_Image,									//ポインタ
		SCREEN_W / 2, SCREEN_H,									//座標
		1, 1,													//表示ケール
		player_anime * PLAYER_SIZE_X, player_direction * PLAYER_SIZE_Y,//元画像位置
		PLAYER_SIZE_X, PLAYER_SIZE_Y,							//元画像サイズ
		PLAYER_SIZE_X / 2, PLAYER_SIZE_Y,						//基準点
		ToRadian(0),											//角度
		1, 1, 1, 1);											//色彩、透明度

	//胃(空)
	sprite_render(stomach,										//ポインタ
		SCREEN_W - STOMACH_SIZE_X, STOMACH_SIZE_Y,				//座標
		1, 1,													//表示ケール
		0,0,													//元画像位置
		STOMACH_SIZE_X, STOMACH_SIZE_Y,							//元画像サイズ
		STOMACH_SIZE_X / 2, STOMACH_SIZE_Y / 2,					//基準点
		ToRadian(0),											//角度
		1, 1, 1, 1);											//色彩、透明度

		//胃
	sprite_render(stomach,										//ポインタ
		SCREEN_W - STOMACH_SIZE_X, STOMACH_SIZE_Y,			//座標
		1, 1,													//表示ケール
		STOMACH_SIZE_X, 0,					//元画像位置
		STOMACH_SIZE_X, STOMACH_SIZE_Y*((float)hungerGauge*0.01),					//元画像サイズ
		STOMACH_SIZE_X / 2, STOMACH_SIZE_Y / 2,													//基準
		ToRadian(180),											//角度
		1, 1, 1, 1);											//色彩、透明度										//色彩、透明度
}

//自機の操作
void player_control() {

	//右						(右が押されていて　かつ　左が押されていない)
	if ((STATE(0) & PAD_RIGHT) && !(STATE(0) & PAD_LEFT)) {
		player_direction = player_right;
	}
	//左						(左がおされていて　かつ　右がおされていない)
	else if ((STATE(0) & PAD_LEFT) && !(STATE(0) & PAD_RIGHT)) {
		player_direction = player_left;
	}
	//何も押されていない
	else {
		player_direction = player_flont;
	}

}


//胃ゲージ(空腹ゲージ)		マックスになるとクールダウン
void stomach_gauge() {
	if (hungerGauge >= 100) {
		player_direction = player_flont;//正面を向かせる
		player_anime = 1;	
		coolDown = true;	//クールダウン状態に(trueにする)
	}
}

//クールダウン処理
void cool_down() {
	static int cooldawn_state = 0;	
	
	//待機時間
	if (cooldawn_state == 0) {
		player_timer_num = player_timer;
		cooldawn_state++;
	}
	else if (cooldawn_state == 1) {
		
		if (player_timer - player_timer_num > 30) 
			cooldawn_state++;
	}
	//ゲージ減少
	else if (cooldawn_state == 2) {
		//0以下になるまで引く
		if (hungerGauge > 0) {
			hungerGauge--;
		}
		else {
			//0より小さくなったら0に戻す
			if (hungerGauge < 0)hungerGauge == 0;
			cooldawn_state++;
		}
	}
	//待機時間
	else if (cooldawn_state == 3) {
		player_timer_num = player_timer;
		cooldawn_state++;
	}
	else if (cooldawn_state == 4) {
		if (player_timer - player_timer_num > 30) {
			player_anime = 0;
			coolDown = false;	//クールダウン状態解除(falseにする)
			cooldawn_state = 0;
			cooldawn_state = 0;
		}
	}
}

//スコア表示
void score_disp() {

	//「calorie」表示
	//text_out(3,"calorie:", 0, 0, SCORE_TEXT_SIZE, SCORE_TEXT_SIZE, 0, 0, 0, 1);

	//カロリー背景
	primitive::rect(0, 0, SCORE_TEXT_SIZE * 12 * 5, SCORE_TEXT_SIZE * 12,
		0,0,ToRadian(0),1,1,0,1);
	
	//カロリー(数値)表示
	text_out(3, std::to_string(calorie),0,0,
		SCORE_TEXT_SIZE, SCORE_TEXT_SIZE,0,0,0,1);

}

