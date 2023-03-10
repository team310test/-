#ifndef AUDIO_H
#define AUDIO_H

//XWBの種類定義
#define XWB_SIC_SOUND (0)

// SIC_SOUND内の効果音
#define XWB_SIC_SOUND_SENTAKU (0)
#define XWB_SIC_SOUND_KETTEI (1)


// musicの種類
#define TITLE_BGM (0)
#define COMBO_LIST_BGM (1)
#define GAME_BGM (2)




void audio_init();
void audio_deinit();



#endif // !AUDIO_H

