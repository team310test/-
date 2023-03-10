#include "all.h"

int combolist_state;
int combolist_timer;

float TEXT_ALPHA;

Sprite* SprComboList;

void combolist_init() {

	combolist_state = 0;
	combolist_timer = 0;
	TEXT_ALPHA = 1;
}
void combolist_deinit() {

	safe_delete(SprComboList);

	music::stop(COMBO_LIST_BGM);
}
void combolist_update() {

	switch (combolist_state) {

	case 0:
		/////// �����ݒ� ///////
		SprComboList = sprite_load(L"./Data/Images/combo_list.png");

		combolist_state++;
		/*fallthrough*/

	case 1:
		/////// �p�����[�^�ݒ� ///////
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(COMBO_LIST_BGM, true);
		music::setVolume(COMBO_LIST_BGM, 0.1f);

		combolist_state++;
		/*fallthrough*/

	case 2:
		/////// �ʏ펞 ///////

		//backspace�L�[����͂�����^�C�g���ɖ߂�(��ɕύX�\������
		if (TRG(0) & PAD_TRG1) {
			sound::play(XWB_SIC_SOUND, XWB_SIC_SOUND_KETTEI);
			nextScene = SCENE_TITLE;
			break;
		}

		if (combolist_timer / 32 % 2 == 1) {
			TEXT_ALPHA = 0;
		}
		else {
			TEXT_ALPHA = 1;
		}

		combolist_timer++;
	}
}
void combolist_render() {
	//��ʂ��N���A
	GameLib::clear(0, 0, 0);


	//�R���{���X�g�̕`��
	sprite_render(
		SprComboList,
		0, 0,
		1.0f, 1.0f,
		0, 0,
		1280, 720,
		0, 0
	);

	text_out(3, "space key to TITLE", 780, 30, 1.4f, 1.4f, 1, 0, 0, TEXT_ALPHA);

}