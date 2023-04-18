//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"
//------< �f�[�^ >---------------------------------------------------------------

// 2D�摜���[�h�f�[�^
GameLib::LoadTexture loadTexture[] = {
    { TEXNO::SHOT,      L"./Data/Images/Bullet01.png", 1U }, 
    //{TEXNO::TURRET01, L"./Data/Images/Lzi250.png",     1U },        // �p�[�c01(L��)
    //{TEXNO::CORE01,   L"./Data/Images/core.png",       1U },        // �p�[�c01(L��)
    {TEXNO::PL_CORE01,  L"./Data/Images/Core01.png",   1U },    
    {TEXNO::ENM_CORE01, L"./Data/Images/Turret02.png", 1U }, 
    {TEXNO::TURRET01,   L"./Data/Images/Turret01.png", 1U },     
    {TEXNO::BUFF01,     L"./Data/Images/Trash01.png",  1U },        

    { -1, nullptr }	// �I���t���O
};

//------< �}�N�� >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // �摜�̑��������S


//------< �e�X�g >------------------------------------------------------------------
GameLib::SpriteData sprPlayerCore01 = SPRITE_CENTER(TEXNO::PL_CORE01, 0, 0, 250, 250);

//------< �p�[�c >------------------------------------------------------------------
GameLib::SpriteData sprPartsCore01   = SPRITE_CENTER(TEXNO::ENM_CORE01, 0, 0, 250,250 );
GameLib::SpriteData sprPartsTurret01 = SPRITE_CENTER(TEXNO::TURRET01, 0, 0, 250,250 );
GameLib::SpriteData sprPartsBuff01   = SPRITE_CENTER(TEXNO::BUFF01, 0, 0, 250,250 );

//------< �V���b�g >----------------------------------------------------------------
GameLib::SpriteData sprShot_NormalShot = SPRITE_CENTER(TEXNO::SHOT, 0, 0, 100, 100);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
