#include "all.h"

int curScene = SCENE_NONE;	//現在のシーン
int nextScene = SCENE_TITLE;//次のシーン

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	
	GameLib::init(L"まんじゃーれ", SCREEN_W, SCREEN_H);
	
	srand((unsigned int)time(NULL));	//srand設定
	
	//ゲームループ
	while (GameLib::gameLoop()) {

		if (nextScene != curScene) {
			//現在のシーンに応じた終了処理
			switch (curScene) {
			case SCENE_TITLE:
				title_deinit();
				break;
			case SCENE_COMBO_LIST:
				combolist_deinit();
				break;
			case SCENE_GAME:
				game_deinit();
				break;
			case SCENE_RESULT:
				result_deinit();
				break;
			case SCENE_RULE:
				rule_deinit();
				break;
			case SCENE_TEST:
				test_deinit();
				break;
			}

			//次のシーンに応じた初期設定処理
			switch (nextScene) {
			case SCENE_TITLE:
				title_init();
				break;
			case SCENE_COMBO_LIST:
				combolist_init();
				break;
			case SCENE_GAME:
				game_init();
				break;
			case SCENE_RESULT:
				result_init();
				break;
			case SCENE_RULE:
				rule_init();
				break;
			case SCENE_TEST:
				test_init();
				break;
			}
		}

		//nextScnen　が　curScnen　になる
		curScene = nextScene;

		input::update();

		music::update(); //オーディオの更新処理

		//現在のシーンに応じた更新・描画処理
		switch (curScene) {
		case SCENE_TITLE:
			title_update();
			title_render();
			break;
		case SCENE_COMBO_LIST:
			combolist_update();
			combolist_render();
			break;
		case SCENE_GAME:
			game_update();
			game_render();
			break;
		case SCENE_RESULT:
			result_update();
			result_render();
			break;
		case SCENE_RULE:
			rule_update();
			rule_render();
			break;
		case SCENE_TEST:
			test_update();
			test_render();
			break;
		}
		
		debug::display(1, 1, 1, 1, 1);
		//画面を描画する
		GameLib::present(1, 0);
	}

	//現在のシーンに応じた終了処理
	switch (curScene) {
	case SCENE_TITLE:
		title_deinit();
		break;
	case SCENE_COMBO_LIST:
		combolist_deinit();
		break;
	case SCENE_GAME:
		game_deinit();
		break;
	case SCENE_RESULT:
		result_deinit();
		break;
	case SCENE_RULE:
		rule_deinit();
		break;
	case SCENE_TEST:
		test_deinit();
		break;
	}

	//ゲームライブラリ終了処理
	GameLib::uninit();

	return 0;

}