#include "all.h"

int game_state;
int game_timer;
int time_Limit;	//��������

Sprite* game_back;	//�w�i

int game_scene;	//�Q�[���̃V�[��

//�����ݒ�
void game_init() {

	game_state = 0;
	game_timer = 0;
	game_scene = game_start;
	time_Limit = 60 * 100;	//��������

	game_start_init();	//�Q�[���J�n�����o
	game_end_init();	//�Q�[���I�������o

	food_init();
	belt_init();
	player_init();
}

//�I������
void game_deinit() {
	game_start_deinit();	//�Q�[���J�n�����o
	game_end_deinit();		//�Q�[���I�������o

	food_deinit();
	belt_deinit();
	player_deinit();

	music::stop(GAME_BGM);
}

//�X�V����
void game_update() {
	//debug::setString("time_Limit:%d", time_Limit);
	switch (game_state)
	{
	case 0:
		////////  �����ݒ�  ////////
		game_state++;
		/*fallthrough*/

	case 1:
		////////  �p�����[�^�ݒ�  ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		game_back = sprite_load(L"./Data/Images/back.png");

				music::play(GAME_BGM, true);
		music::setVolume(GAME_BGM,0.1f);
		game_state++;
		/*fallthrough*/
	case 2:
		////////  �ʏ펞  ////////
		//�Q�[���V�[��
		switch (game_scene)
		{
		case game_start:
			game_start_updata();//�Q�[���J�n�����o

			break;
		case game_play:
			belt_update();
			food_update();
			player_update();
			TimeLimit();	//��������
			////�X�y�[�X�L�[�� �I��������
			//if (TRG(0) & PAD_START) {
			//	game_scene = game_end;
			//}

			break;
		case game_end:
			game_end_updata();//�Q�[���I�������o

			break;
		}





		break;
	}

	game_timer++;
}

//�`�揈��
void game_render() {
	GameLib::clear(0, 0, 1);
	sprite_render(game_back, 0, 0);	//�w�i
	
	belt_render();
	//eat_renfe();	//�H������ �ڈ�E�e�X�g
	food_render();	//food_render()�ɖڈ󂠂�
	player_render();
	score_disp();	//�X�R�A

	//��������	�w�i
	primitive::rect(0, 0, TIMER_SIZE * 12 * 3, TIMER_SIZE * 12,
		0, 0, ToRadian(0), 0, 0, 0, 1);

	//��������		�Q�[���J�n���o�łȂ���Ε\��
	if (game_scene != game_start) {
		text_out(3, std::to_string(time_Limit / 60),
			0, 0, TIMER_SIZE, TIMER_SIZE,
			1, 1, 1, 1);
	}

	if (game_scene == game_start)
		game_start_render();	//�Q�[���J�n�����o
	if (game_scene == game_end)
		game_end_render();		//�Q�[���I�������o

	//primitive::rect(0, 0, SCREEN_W, SCREEN_H, 0, 0, ToRadian(0), 0, 0, 0, 1);//��ʈÓ]
}

//��������
void TimeLimit() {
	
	//�c��0�b�ɂȂ�
	if (time_Limit <= 0)
		game_scene = game_end;	//�Q�[���I��
	
	time_Limit--;
	if (time_Limit < 0)time_Limit = 0;	//0��菬�����Ȃ�����0�ɖ߂�
}