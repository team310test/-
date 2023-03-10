#include "all.h"

int game_state;
int game_timer;
int time_Limit;	//制限時間

Sprite* game_back;	//背景

int game_scene;	//ゲームのシーン

//初期設定
void game_init() {

	game_state = 0;
	game_timer = 0;
	game_scene = game_start;
	time_Limit = 60 * 100;	//制限時間

	game_start_init();	//ゲーム開始時演出
	game_end_init();	//ゲーム終了時演出

	food_init();
	belt_init();
	player_init();
}

//終了処理
void game_deinit() {
	game_start_deinit();	//ゲーム開始時演出
	game_end_deinit();		//ゲーム終了時演出

	food_deinit();
	belt_deinit();
	player_deinit();

	music::stop(GAME_BGM);
}

//更新処理
void game_update() {
	//debug::setString("time_Limit:%d", time_Limit);
	switch (game_state)
	{
	case 0:
		////////  初期設定  ////////
		game_state++;
		/*fallthrough*/

	case 1:
		////////  パラメータ設定  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		game_back = sprite_load(L"./Data/Images/back.png");

				music::play(GAME_BGM, true);
		music::setVolume(GAME_BGM,0.1f);
		game_state++;
		/*fallthrough*/
	case 2:
		////////  通常時  ////////
		//ゲームシーン
		switch (game_scene)
		{
		case game_start:
			game_start_updata();//ゲーム開始時演出

			break;
		case game_play:
			belt_update();
			food_update();
			player_update();
			TimeLimit();	//制限時間
			////スペースキーで 終了処理へ
			//if (TRG(0) & PAD_START) {
			//	game_scene = game_end;
			//}

			break;
		case game_end:
			game_end_updata();//ゲーム終了時演出

			break;
		}





		break;
	}

	game_timer++;
}

//描画処理
void game_render() {
	GameLib::clear(0, 0, 1);
	sprite_render(game_back, 0, 0);	//背景
	
	belt_render();
	//eat_renfe();	//食事距離 目印・テスト
	food_render();	//food_render()に目印あり
	player_render();
	score_disp();	//スコア

	//制限時間	背景
	primitive::rect(0, 0, TIMER_SIZE * 12 * 3, TIMER_SIZE * 12,
		0, 0, ToRadian(0), 0, 0, 0, 1);

	//制限時間		ゲーム開始演出でなければ表示
	if (game_scene != game_start) {
		text_out(3, std::to_string(time_Limit / 60),
			0, 0, TIMER_SIZE, TIMER_SIZE,
			1, 1, 1, 1);
	}

	if (game_scene == game_start)
		game_start_render();	//ゲーム開始時演出
	if (game_scene == game_end)
		game_end_render();		//ゲーム終了時演出

	//primitive::rect(0, 0, SCREEN_W, SCREEN_H, 0, 0, ToRadian(0), 0, 0, 0, 1);//画面暗転
}

//制限時間
void TimeLimit() {
	
	//残り0秒になる
	if (time_Limit <= 0)
		game_scene = game_end;	//ゲーム終了
	
	time_Limit--;
	if (time_Limit < 0)time_Limit = 0;	//0より小さくなったら0に戻す
}