#include "all.h"

// タイトル用音楽
void Audio::titleInit()
{
    using namespace GameLib;

    // BGM
    music::load(TITLE_AUDIO::BGM_TITLE, L"./Data/Musics/BGM/BGM_Title.wav", 1.0f);

    // SE
    music::load(TITLE_AUDIO::SE_HEART_BEAT, L"./Data/Musics/SE/SE_HeartBeat.wav", 2.0f);
    music::load(TITLE_AUDIO::SE_START, L"./Data/Musics/SE/SE_Gatya.wav",          2.0f);
    music::load(TITLE_AUDIO::SE_EXIT,  L"./Data/Musics/SE/SE_TrashBox.wav",       10.0f);
}

// ゲーム用音楽
void Audio::gameInit()
{
    using namespace GameLib;

    // BGM
    music::load(GAME_AUDIO::BGM_GAME, L"./Data/Musics/BGM/BGM_Game.wav", 0.0f);
    music::load(GAME_AUDIO::BGM_BOSS, L"./Data/Musics/BGM/BGM_Boss.wav", 1.0f);

    // SE
    music::load(GAME_AUDIO::SE_PL_CORE_ALERT,  L"./Data/Musics/SE/SE_PlayerCoreAlert.wav", 1.0f);

    music::load(GAME_AUDIO::SE_ENM_CORE_DEATH, L"./Data/Musics/SE/SE_EnemyCoreDeath.wav",  1.0f);

    music::load(GAME_AUDIO::SE_SHOT,    L"./Data/Musics/SE/SE_Shot.wav",     1.0f);
    music::load(GAME_AUDIO::SE_DMG,     L"./Data/Musics/SE/SE_Damage.wav",   2.0f);
    music::load(GAME_AUDIO::SE_DEATH,   L"./Data/Musics/SE/SE_Death.wav",    5.0f);
    music::load(GAME_AUDIO::SE_COMBINE, L"./Data/Musics/SE/SE_Combine2.wav", 1.0f);
    music::load(GAME_AUDIO::SE_SHRINK,  L"./Data/Musics/SE/SE_Shrink.wav",   2.0f);
    music::load(GAME_AUDIO::SE_GATYA,   L"./Data/Musics/SE/SE_Gatya.wav",    2.0f);
    music::load(GAME_AUDIO::SE_BAN,     L"./Data/Musics/SE/SE_Ban.wav",      2.0f);
}