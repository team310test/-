#include "all.h"

// 2D�摜���[�h�f�[�^
GameLib::LoadTexture loadTexture[] = {
    // �w�i
    { TEXNO::BACK01,    L"./Data/Images/BackGround/BackGround01.png", 1U },
    { TEXNO::BACK02,    L"./Data/Images/BackGround/BackGround02.png", 1U },
    // UI
    { TEXNO::UI_METER_FRAME,    L"./Data/Images/UI/Meter_Frame.png",    1U },   // �v��̘g
    { TEXNO::UI_METER_READ,     L"./Data/Images/UI/Meter_Read.png",     1U },   // �v��̖ڐ���
    { TEXNO::UI_METER_NEEDLE,   L"./Data/Images/UI/Meter_Needle.png",   1U },   // �v��̐j

    // �R�A
    { TEXNO::PL_CORE01,  L"./Data/Images/Core/PlayerCore01.png", 1U },
    { TEXNO::ENM_CORE01, L"./Data/Images/Core/EnemyCore01.png",  1U },

    // �U���p�[�c
    { TEXNO::TURRET01,   L"./Data/Images/Turret/Turret01.png", 1U },
    { TEXNO::TURRET02,   L"./Data/Images/Turret/Turret02.png", 1U },
    { TEXNO::TURRET03,   L"./Data/Images/Turret/Turret03.png", 1U },
    // �o�t�p�[�c
    { TEXNO::BUFF01,     L"./Data/Images/Buff/Buff01.png",     1U },
    // ���݃p�[�c
    { TEXNO::TRASH01,    L"./Data/Images/Trash/Trash01.png",   1U },


    // �e
    { TEXNO::SHOT,       L"./Data/Images/Bullet/Bullet01.png", 1U },
    

    { -1, nullptr }	// �I���t���O
};

//------< �}�N�� >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // �摜�̑��������S

//------< �R�A>------------------------------------------------------------------
GameLib::SpriteData sprPlayerCore01 = SPRITE_CENTER(TEXNO::PL_CORE01,   0, 0, 128, 128);
GameLib::SpriteData sprEnemyCore01  = SPRITE_CENTER(TEXNO::ENM_CORE01,  0, 0, 128, 128);

//------< �p�[�c >------------------------------------------------------------------
GameLib::SpriteData sprPartsTurret01 = SPRITE_CENTER(TEXNO::TURRET01,   0, 0, 128, 128);
GameLib::SpriteData sprPartsTurret02 = SPRITE_CENTER(TEXNO::TURRET02,   0, 0, 128, 128);
GameLib::SpriteData sprPartsTurret03 = SPRITE_CENTER(TEXNO::TURRET03,   0, 0, 128, 128);
GameLib::SpriteData sprPartsBuff01   = SPRITE_CENTER(TEXNO::BUFF01,     0, 0, 250, 250);
GameLib::SpriteData sprPartsTrash01  = SPRITE_CENTER(TEXNO::TRASH01,    0, 0, 128, 128);

//------< �V���b�g >----------------------------------------------------------------
GameLib::SpriteData sprShot_NormalShot = SPRITE_CENTER(TEXNO::SHOT,     0, 0, 64, 64);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
