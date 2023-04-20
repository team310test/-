#pragma once

#include "../GameLib/texture.h"

// ���x����`
enum TEXNO
{
    // �Q�[��
    BACK01,
    BACK02,
    ENEMY,
    SHOT,
    PL_CORE01,
    ENM_CORE01,
    TURRET01,
    BUFF01,
};

extern GameLib::LoadTexture loadTexture[];

//------< �v���C���[ >----------------------------------------------------------------
extern GameLib::SpriteData sprPlayerCore01;

//------< �p�[�c >----------------------------------------------------------------
extern GameLib::SpriteData sprPartsCore01;
extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsBuff01;

//------< �e >----------------------------------------------------------------
extern GameLib::SpriteData sprShot_NormalShot;

//******************************************************************************
