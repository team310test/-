#include "all.h"

int curScene = SCENE_NONE;	//���݂̃V�[��
int nextScene = SCENE_TITLE;//���̃V�[��

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	
	GameLib::init(L"�܂񂶂�[��", SCREEN_W, SCREEN_H);
	
	srand((unsigned int)time(NULL));	//srand�ݒ�
	
	//�Q�[�����[�v
	while (GameLib::gameLoop()) {

		if (nextScene != curScene) {
			//���݂̃V�[���ɉ������I������
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

			//���̃V�[���ɉ����������ݒ菈��
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

		//nextScnen�@���@curScnen�@�ɂȂ�
		curScene = nextScene;

		input::update();

		music::update(); //�I�[�f�B�I�̍X�V����

		//���݂̃V�[���ɉ������X�V�E�`�揈��
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
		//��ʂ�`�悷��
		GameLib::present(1, 0);
	}

	//���݂̃V�[���ɉ������I������
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

	//�Q�[�����C�u�����I������
	GameLib::uninit();

	return 0;

}