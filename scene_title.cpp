#include "all.h"

int title_state;
int title_timer;

int Cursor;
int Nexcursor;
int Alpha[4];
int text_alpha;

Sprite* sprTitle;
Sprite* chapter;

//初期設定
void title_init() {

	title_state = 0;
	title_timer = 0;

	Nexcursor = 0;
	//透明度
	for (int i = 0; i < 4; i++) {
		Alpha[i] = 1;
	}

	text_alpha = 1;

}

//終了処理
void title_deinit() {

	//スプライトの消去
	safe_delete(sprTitle);
	safe_delete(chapter);

	//音楽のストップ
	music::stop(TITLE_BGM);
}

//更新処理
void title_update() {

	switch (title_state)
	{
	case 0:
		////////  初期設定  ////////
		sprTitle = sprite_load(L"./Data/Images/title_back.png");
		chapter = sprite_load(L"./Data/Images/chapter.png");

		title_state++;
		/*fallthrough*/

	case 1:
		////////  パラメータ設定  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(TITLE_BGM, true);
		music::setVolume(TITLE_BGM, 0.1f);


		title_state++;
		/*fallthrough*/
	case 2:
		////////  通常時  ////////

		//ボタンを押したらゲーム画面へ遷移
		if (TRG(0) & PAD_TRG1 && Nexcursor == 0) {
			sound::play(XWB_SIC_SOUND, XWB_SIC_SOUND_KETTEI);
			nextScene = SCENE_GAME;
		}

		if (TRG(0) & PAD_TRG1 && Nexcursor == 1) {
					nextScene = SCENE_RULE;
		}

		if (TRG(0) & PAD_TRG1 && Nexcursor == 2) {
			sound::play(XWB_SIC_SOUND, XWB_SIC_SOUND_KETTEI);
			nextScene = SCENE_COMBO_LIST;
		}

		if (TRG(0) & PAD_TRG1 && Nexcursor == 3) {
			sound::play(XWB_SIC_SOUND, XWB_SIC_SOUND_KETTEI);
			exit(0);
		}

		//キー入力での動作
		if (TRG(0) & PAD_UP) {
			sound::play(XWB_SIC_SOUND, XWB_SIC_SOUND_SENTAKU);
			if (Nexcursor >= 2) {
				Nexcursor -= 2;
			}
			break;
		}

		if (TRG(0) & PAD_DOWN) {
			sound::play(XWB_SIC_SOUND, XWB_SIC_SOUND_SENTAKU);
			if (Nexcursor <= 1) {
				Nexcursor += 2;
			}
			break;
		}

		if (TRG(0) & PAD_RIGHT) {
			sound::play(XWB_SIC_SOUND, XWB_SIC_SOUND_SENTAKU);
			if (Nexcursor % 2 == 0) {
				Nexcursor++;
			}
			break;
		}

		if (TRG(0) & PAD_LEFT) {
			sound::play(XWB_SIC_SOUND, XWB_SIC_SOUND_SENTAKU);
			if (Nexcursor % 2 == 1) {
				Nexcursor--;
			}
			break;
		}

		//点滅処理
		if (Nexcursor == Cursor) {
			if (title_timer / 20 % 2 == 1) {
				Alpha[Cursor] = 1;
			}
			else {
				Alpha[Cursor] = 0;
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				Alpha[i] = 1;
			}
		}

		Cursor = Nexcursor;

		if (title_timer / 32 % 2 == 1) {
			text_alpha = 0;
		}
		else {
			text_alpha = 1;
		}


		break;
	}

	title_timer++;
}

//描画処理
void title_render() {

	GameLib::clear(0, 0, 0);

	//背景
	sprite_render(
		sprTitle,
		0, 0,
		1.0f, 1.0f,
		0, 0,
		1280, 720,
		0, 0,
		ToRadian(0));


	//チャプター別
	sprite_render(
		chapter,
		350, 215,
		1.0f, 1.0f,
		0, 0,
		CHAPTER_W, CHAPTER_H,
		0, 0,
		ToRadian(0),
		1, 1, 1, Alpha[0]
	);

	sprite_render(
		chapter,
		663, 215,
		1.0f, 1.0f,
		CHAPTER_W, 0,
		CHAPTER_W, CHAPTER_H,
		0, 0,
		ToRadian(0),
		1, 1, 1, Alpha[1]
	);

	sprite_render(
		chapter,
		350, 433,
		1.0f, 1.0f,
		CHAPTER_W*2, 0,
		CHAPTER_W, CHAPTER_H,
		0, 0,
		ToRadian(0),
		1, 1, 1, Alpha[2]
	);

	sprite_render(
		chapter,
		663, 433,
		1.0f, 1.0f,
		CHAPTER_W*3, 0,
		CHAPTER_W, CHAPTER_H,
		0, 0,
		ToRadian(0),
		1, 1, 1, Alpha[3]
	);


	text_out(2, "Push to Space Key", 1000, 620, 0.6f, 0.6f, 0, 0, 0, text_alpha);

}