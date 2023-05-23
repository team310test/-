#pragma once

#include "../GameLib/texture.h"

// ���x����`

// �^�C�g��
enum TITLE_TEXNO
{
    TITLE_PLAYER,               // �v���C���[�R�A
    TITLE_HEART,                // �v���C���[�R�A�̃n�[�g
    TITLE_FRAME,                // �v���C���[�R�A�̘g

    TITLE_LOGO,                 // ���S
    TITLE_TRASH_BOX,            // �S�~��
    TITLE_USER_KEYBOARD_MOVE,   // ������@WASD��������(�L�[�{�[�h)
    TITLE_USER_CONTROLLER_MOVE, // ������@WASD��������(�R���g���[���[)
    TITLE_USER_SPACE,           // ������@Space
    TITLE_USER_ABXY,            // ������@abxy
    TITLE_USER_HOLD,            // ������@������

    TITLE_TEXT_START,           // Start
    TITLE_TEXT_EXIT,            // Exit
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
    BG10,
    BG11,
    BG12,
    BG13,
    BG14,
    BG15,
    BG16,
    BG17,
    BG_END, // �w�i�̍Ō�

    // UI
    UI_METER_FRAME,     // �v��̘g
    UI_METER_NEEDLE,    // �v��̐j

    UI_RESULT_BACK,     // ���U���g�̃o�b�N

    UI_RESULT_JUNKS,
    UI_RESULT_TIMES,
    UI_RESULT_RANK,
    UI_RESULT_ANY_PUSH,
    UI_RESULT_S,
    UI_RESULT_A,
    UI_RESULT_B,
    UI_RESULT_C,
    UI_RESULT_TEXT_JUNKIE,
    UI_RESULT_TEXT_GREAT,
    UI_RESULT_TEXT_NICE,
    UI_RESULT_TEXT_SOSO,

    // �R�A
    PL_CORE01,
    ENM_CORE01,
    ENM_CORE02,

    // �U���p�[�c
    TURRET01,
    TURRET01FLIP,
    TURRET02,
    TURRET02FLIP,
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
extern GameLib::SpriteData sprTitleUserKeyboardMove;
extern GameLib::SpriteData sprTitleUserControllerMove_01;
extern GameLib::SpriteData sprTitleUserControllerMove_02;
extern GameLib::SpriteData sprTitleUserControllerMove_03;
extern GameLib::SpriteData sprTitleUserSpace;
extern GameLib::SpriteData sprTitleUserAbxy;
extern GameLib::SpriteData sprTitleUserHold;


///////////// �Q�[�� ////////////////////////////////////////////////

// ���U���gUI
extern GameLib::SpriteData sprResult_back01;
extern GameLib::SpriteData sprResult_back02;
extern GameLib::SpriteData sprResult_back03;
extern GameLib::SpriteData sprResult_back04;
extern GameLib::SpriteData sprResult_junks;
extern GameLib::SpriteData sprResult_times;
extern GameLib::SpriteData sprResult_rank;
extern GameLib::SpriteData sprResult_anyPush;
extern GameLib::SpriteData sprResult_S;
extern GameLib::SpriteData sprResult_A;
extern GameLib::SpriteData sprResult_B;
extern GameLib::SpriteData sprResult_C;
extern GameLib::SpriteData sprResult_textJunkie;
extern GameLib::SpriteData sprResult_textGreat;
extern GameLib::SpriteData sprResult_textNice;
extern GameLib::SpriteData sprResult_textSoso;

// �R�A
extern GameLib::SpriteData sprPlayerCore01;
extern GameLib::SpriteData sprEnemyCore01;
extern GameLib::SpriteData sprEnemyCore02;
extern GameLib::SpriteData sprPartsCore02;

// �p�[�c
extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsTurret01Flip;
extern GameLib::SpriteData sprPartsTurret02;
extern GameLib::SpriteData sprPartsTurret02Flip;
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
