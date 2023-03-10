#include "all.h"

int rule_state;
int rule_timer;


Sprite* rule_explanation;	//ルール説明データ

void rule_init(){
	rule_state = 0;
	rule_timer = 0;
	TEXT_ALPHA = 0;
}

void rule_deinit() {
	safe_delete(rule_explanation);

	music::stop(COMBO_LIST_BGM);
}

void rule_update(){
	;

	switch (rule_state) {

	case 0:
		/////// 初期設定 ///////
		rule_explanation = sprite_load(L"./Data/Images/rule.png");

		rule_state++;
		/*fallthrough*/

	case 1:
		/////// パラメータ設定 ///////
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(COMBO_LIST_BGM, true);
		music::setVolume(COMBO_LIST_BGM, 0.1f);

		rule_state++;
		/*fallthrough*/

	case 2:
		/////// 通常時 ///////

		//backspaceキーを入力したらタイトルに戻る(後に変更可能性あり
		if (TRG(0) & PAD_TRG1) {
			sound::play(XWB_SIC_SOUND, XWB_SIC_SOUND_KETTEI);
			nextScene = SCENE_TITLE;
			break;
		}

		if (rule_timer / 32 % 2 == 1) {
			TEXT_ALPHA = 0;
		}
		else {
			TEXT_ALPHA = 1;
		}

		rule_timer++;
	}
}

void rule_render(){
	//画面をクリア
	GameLib::clear(0, 0, 0);


	//コンボリストの描画
	sprite_render(
		rule_explanation,
		0, 0
	);

	text_out(3, "space key to TITLE", 960, 700, 1.4f, 1.4f, 0, 0, 0, TEXT_ALPHA);

}