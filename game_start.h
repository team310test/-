#ifndef GAME_START_H
#define GAME_START_H

extern float blackout;//��ʈÓ]�̂��߂̕ϐ�(�A���t�@)

enum {
	game_start = 0,	//�Q�[���J�n���o
	game_play,		//�Q�[���v���C
	game_end,		//�Q�[���I�����o
};

//�֐��v���g�^�C�v�錾
void game_start_init();
void game_start_deinit();
void game_start_updata();
void game_start_render();

#endif
