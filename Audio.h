#pragma once

enum TITLE_AUDIO
{    
    // BGM
    BGM_TITLE,          // �^�C�g��BGM

    // SE
    SE_HEART_BEAT       // �S���ۓ�
};

enum GAME_AUDIO
{
    // BGM              
    BGM_GAME,           // �Q�[��BGM
    BGM_BOSS,           // �{�X��BGM

    // SE
    SE_PL_CORE_ALERT,   // �v���C���[�R�A��p�̔�e
    SE_ENM_CORE_DEATH,  // �G�l�~�[�R�A��p�̎��S

    SE_SHOT,            // �e����
    SE_DMG,             // ��e
    SE_DEATH,           // ���S
    SE_COMBINE,         // �p�[�c����
    SE_SHRINK           // ��ʏk��
};


class Audio
{
public:
    static void titleInit();    // �^�C�g���p���y�̓ǂݍ���
    static void gameInit();     // �Q�[���p���y�̓ǂݍ���

    static void update() { GameLib::music::update(); }  // �t�F�[�h�̍X�V
    static void clear()  { GameLib::music::clear();  }  // ���y�N���A
   
public:
    // ���y�Đ��itrackNo�F�Đ�����g���b�N�ԍ��A isLoop�F���[�v���邩�j
    static void play(const int& trackNo, const bool& isLoop)
    {
        GameLib::music::play(trackNo, isLoop);
    }

    //  ���y�̃t�F�[�h�C���E�t�F�[�h�A�E�g
    //  int   trackNo �F�t�F�[�h������g���b�N�̃C���f�b�N�X(0 ~ 31)
    //  float fadeTime�F�t�F�[�h����
    //  float volume  �F�t�F�[�h��̃{�����[��
    static void fade(const int& trackNo, const float& fadeTime, const float& volume = 0.0f)
    {
        GameLib::music::fade(trackNo, fadeTime, volume);
    }

};

