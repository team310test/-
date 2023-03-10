#include "all.h"


void audio_init() {

	music::load(0, L"./Data/Musics/bgm_kari_title.wav");  // 0
	music::load(1, L"./Data/Musics/bgm_kari_comboLIST.wav"); // 1
	music::load(2, L"./Data/Musics/bgm_kari_game.wav"); // 2

	sound::load(0, L"./Data/Sounds/SICsound.xwb");

}
void audio_deinit() {
	
	music::clear();
}