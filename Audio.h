#pragma once

enum TITLE_AUDIO
{    
    // BGM
    BGM_TITLE,          // タイトルBGM

    // SE
    SE_HEART_BEAT       // 心臓鼓動SE
};

enum GAME_AUDIO
{
    // BGM              
    BGM_GAME,           // ゲームBGM
    BGM_BOSS,           // ボス戦BGM

    // SE
    SE_PL_CORE_ALERT,   // プレイヤーコア専用の被弾SE
    SE_ENM_CORE_DEATH,  // エネミーコア専用の死亡SE

    SE_SHOT,            // 弾発射SE
    SE_DMG,             // 被弾SE
    SE_DEATH,           // 死亡SE
    SE_COMBINE,         // パーツ合体SE
    SE_SHRINK           // 画面縮小SE
};


class Audio
{
public:
    static void titleInit();    // タイトル用音楽の読み込み
    static void gameInit();     // ゲーム用音楽の読み込み

    static void update() { GameLib::music::update(); }  // フェードの更新
    static void clear()  { GameLib::music::clear();  }  // 音楽クリア
   
public:
    // 音楽再生（trackNo：再生するトラック番号、 isLoop：ループするか）
    static void play(const int& trackNo, const bool& isLoop = false)
    {
        GameLib::music::play(trackNo, isLoop);
    }

    //  音楽のフェードイン・フェードアウト
    //  int   trackNo ：フェードさせるトラックのインデックス(0 ~ 31)
    //  float fadeTime：フェード時間
    //  float volume  ：フェード後のボリューム
    static void fade(const int& trackNo, const float& fadeTime, const float& volume = 0.0f)
    {
        GameLib::music::fade(trackNo, fadeTime, volume);
    }

};

