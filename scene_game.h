#ifndef SCENE_GAME_H
#define SCENE_GAME_H

extern int game_scene;	//ゲームのシーン;

//関数プロトタイプ宣言
void game_init();
void game_deinit();
void game_update();
void game_render();
void TimeLimit();	//制限時間

#endif