#pragma once

enum TITLE_AUDIO
{    
    // BGM
    BGM_TITLE,          // タイトルBGM

    // SE
    SE_HEART_BEAT       // 心臓鼓動
};

enum GAME_AUDIO
{
    // BGM              
    BGM_GAME,           // ゲームBGM
    BGM_BOSS,           // ボス戦BGM

    // SE
    SE_PL_CORE_ALERT,   // プレイヤーコア専用の被弾
    SE_ENM_CORE_DEATH,  // エネミーコア専用の死亡

    SE_SHOT,            // 弾発射
    SE_DMG,             // 被弾
    SE_DEATH,           // 死亡
    SE_COMBINE,         // パーツ合体
    SE_SHRINK           // 画面縮小
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
    static void play(const int& trackNo, const bool& isLoop)
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

