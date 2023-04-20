#pragma once

//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

#include "../GameLib/texture.h"

// ���x����`
enum TEXNO
{
    // �Q�[��
    PLAYER,
    PLAYERT,
    PLAYER2,
    PLAYER3,
    BACK,
    ENEMY,
    SHOT,
    CORE01,
    TURRET01,
    TRASH01,
};

extern GameLib::LoadTexture loadTexture[];

//------< �e�X�g >----------------------------------------------------------------
extern GameLib::SpriteData sprEnemey_test;

//------< �p�[�c >----------------------------------------------------------------
extern GameLib::SpriteData sprPartsTurret01;
extern GameLib::SpriteData sprPartsCore01;
extern GameLib::SpriteData sprPartsTrash01;

//------< �� >----------------------------------------------------------------
extern GameLib::SpriteData sprWeapon_NormalShot;

//******************************************************************************
