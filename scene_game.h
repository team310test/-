#ifndef SCENE_GAME_H
#define SCENE_GAME_H

extern int game_scene;	//�Q�[���̃V�[��;

//�֐��v���g�^�C�v�錾
void game_init();
void game_deinit();
void game_update();
void game_render();
void TimeLimit();	//��������

#endif