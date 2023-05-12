#pragma once

#include "../GameLib/texture.h"

// ���x����`

// �^�C�g��
enum TITLE_TEXNO
{
    TITLE_PLAYER,       // �v���C���[�R�A
    TITLE_HEART,        // �v���C���[�R�A�̃n�[�g
    TITLE_FRAME,        // �v���C���[�R�A�̘g

    TITLE_LOGO,         // ���S
    TITLE_TRASH_BOX,    // �S�~��
    TITLE_USER01,       // ������@
    TITLE_USER02,       // ������@
};

// �Q�[��
enum GAME_TEXNO
{    
    // �w�i
    BG01,
    BG02,
    BG03,
    BG04,
    BG05,
    BG06,
    BG07,
    BG08,
    BG09,
    BG_END, // �w�i�̍Ō�

    // UI
    UI_METER_FRAME,     // �v��̘g
    UI_METER_READ,      // �v��̖ڐ���
    UI_METER_NEEDLE,    // �v��̐j

    // �R�A
    PL_CORE01,
    ENM_CORE01,

    // �U���p�[�c
    TURRET01,
    TURRET02,
    TURRET03,
    TURRET04,
    //�h��p�[�c
    SHIELD01,
    // �o�t�p�[�c
    BUFF01,
    // ���݃p�[�c
    TRASH01,
    TRASH02,
    TRASH03,
    // �R�����p�[�c(���ʂȂ��p�[�c)
    COMMON01,
    COMMON02,
    COMMON03,

    // �e��
    BULLET01,

    // �G�t�F�N�g
    EFC_BOMB,
    EFC_COMBINE,

    // GameOver
    GAME_HEART,        // �v���C���[�R�A�̃n�[�g
    GAME_FRAME,        // �v���C���[�R�A�̘g
};

extern GameLib::LoadTexture titleLoadTexture[];
extern GameLib::LoadTexture gameLoadTexture[];


///////////// �^�C�g�� //////////////////////////////////////////////
extern GameLib::SpriteData sprTitlePlayerCore;
extern GameLib::SpriteData sprTitleCoreFrame;
extern GameLib::SpriteData sprTitleCoreHeart;

extern GameLib::SpriteData sprTitleLogo;
extern GameLib::SpriteData sprTitleTrashBox01;
extern GameLib::SpriteData sprTitleTrashBox02;
extern GameLib::SpriteData sprTitleUser01;
extern GameLib::SpriteData sprTitleUser02;


///////////// �Q�[�� ////////////////////////////////////////////////

// �v���C���[
extern GameLib::SpriteData sprPlayerCore01;

// �p�[�c
extern GameLib::SpriteData sprEnemyCore01;
extern GameLib::SpriteData sprPartsCore02;

extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsTurret02;
extern GameLib::SpriteData sprPartsTurret03;
extern GameLib::SpriteData sprPartsTurret04;

extern GameLib::SpriteData sprPartsShield01;
extern GameLib::SpriteData sprPartsBuff01;
extern GameLib::SpriteData sprPartsTrash01;
extern GameLib::SpriteData sprPartsTrash02;
extern GameLib::SpriteData sprPartsTrash03;

extern GameLib::SpriteData sprPartsCommon01;
extern GameLib::SpriteData sprPartsCommon02;
extern GameLib::SpriteData sprPartsCommon03;

// �e
extern GameLib::SpriteData sprShot_NormalShot;

// �G�t�F�N�g

//�@�����G�t�F�N�g
extern GameLib::SpriteData sprEfcBomb_anime0;
extern GameLib::SpriteData sprEfcBomb_anime1;
extern GameLib::SpriteData sprEfcBomb_anime2;
extern GameLib::SpriteData sprEfcBomb_anime3;

// ���̃G�t�F�N�g
extern GameLib::SpriteData sprEfcCombine_anime0;
extern GameLib::SpriteData sprEfcCombine_anime1;
extern GameLib::SpriteData sprEfcCombine_anime2;
extern GameLib::SpriteData sprEfcCombine_anime3;

// GameOver
extern GameLib::SpriteData sprGamePlayerFrame;
extern GameLib::SpriteData sprGamePlayerHeart;
