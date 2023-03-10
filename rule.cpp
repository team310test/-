#include "all.h"

int rule_state;
int rule_timer;


Sprite* rule_explanation;	//���[�������f�[�^

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
		/////// �����ݒ� ///////
		rule_explanation = sprite_load(L"./Data/Images/rule.png");

		rule_state++;
		/*fallthrough*/

	case 1:
		/////// �p�����[�^�ݒ� ///////
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(COMBO_LIST_BGM, true);
		music::setVolume(COMBO_LIST_BGM, 0.1f);

		rule_state++;
		/*fallthrough*/

	case 2:
		/////// �ʏ펞 ///////

		//backspace�L�[����͂�����^�C�g���ɖ߂�(��ɕύX�\������
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
	//��ʂ��N���A
	GameLib::clear(0, 0, 0);


	//�R���{���X�g�̕`��
	sprite_render(
		rule_explanation,
		0, 0
	);

	text_out(3, "space key to TITLE", 960, 700, 1.4f, 1.4f, 0, 0, 0, TEXT_ALPHA);

}