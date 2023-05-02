#pragma once

#include "../GameLib/texture.h"

// ���x����`
enum TEXNO
{
    // �Q�[��
    BACK01,
    BACK02,
    UI_METER_FRAME,     // �v��̘g
    UI_METER_NEEDLE,    // �v��̐j
    SHOT,
    PL_CORE01,
    ENM_CORE01,
    ENM_CORE02,
    TURRET01,
    TURRET02,
    TURRET03,
    BUFF01,
    TRASH01,
    TITLE_CORE,
    TITLE_USER,
    TITLE_TRASH,
    TITLE_LOGO,
    TITLE_HEART
};

extern GameLib::LoadTexture loadTexture[];


//------< �v���C���[ >------------------------------------------------------------------
extern GameLib::SpriteData sprPlayerCore01;

//------< �p�[�c >------------------------------------------------------------------
extern GameLib::SpriteData sprPartsCore01;
extern GameLib::SpriteData sprPartsCore02;
extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsTurret03;
extern GameLib::SpriteData sprPartsBuff01;
extern GameLib::SpriteData sprPartsTrash01;

//------< �e >----------------------------------------------------------------
extern GameLib::SpriteData sprShot_NormalShot;

//------< �^�C�g�� >----------------------------------------------------------------
extern GameLib::SpriteData sprTitleCore;
extern GameLib::SpriteData sprTitleUser;
extern GameLib::SpriteData sprTitleTrash;
extern GameLib::SpriteData sprTitleLogo;
extern GameLib::SpriteData sprTitleHeart;

//******************************************************************************
