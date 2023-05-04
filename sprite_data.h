#pragma once

#include "../GameLib/texture.h"

// ���x����`
enum TEXNO
{
    // �Q�[��
    
    // �w�i
    BACK01,
    BACK02,
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
    // �o�t�p�[�c
    BUFF01,
    // ���݃p�[�c
    TRASH01,

    // �e��
    BULLET01,

    // �G�t�F�N�g
    EFC_BOMB,
    EFC_COMBINE,

    // �^�C�g��
    TITLE_FRAME,
    TITLE_USER,
    TITLE_TRASH,
    TITLE_LOGO,
    TITLE_HEART,
};

extern GameLib::LoadTexture loadTexture[];


//------< �v���C���[ >------------------------------------------------------------------
extern GameLib::SpriteData sprPlayerCore01;

//------< �p�[�c >------------------------------------------------------------------
extern GameLib::SpriteData sprEnemyCore01;
extern GameLib::SpriteData sprPartsCore02;
extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsTurret03;
extern GameLib::SpriteData sprPartsBuff01;
extern GameLib::SpriteData sprPartsTrash01;

//------< �e >----------------------------------------------------------------
extern GameLib::SpriteData sprShot_NormalShot;

//------< �G�t�F�N�g >----------------------------------------------------------------

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

//------< �^�C�g�� >----------------------------------------------------------------
extern GameLib::SpriteData sprTitleCore;
extern GameLib::SpriteData sprTitleUser;
extern GameLib::SpriteData sprTitleTrash;
extern GameLib::SpriteData sprTitleLogo;
extern GameLib::SpriteData sprTitleHeart;

//******************************************************************************
