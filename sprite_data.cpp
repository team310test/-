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
    { TEXNO::PLAYER,      L"./Data/Images/player.png",    1U },// �v���C���[(��)
    //{ TEXNO::PLAYERT,      L"./Data/Images/player(test).png",    1U },// �v���C���[(��)
    { TEXNO::PLAYER2,      L"./Data/Images/Weapon1.png",    1U },// 250*250
    { TEXNO::SHOT,        L"./Data/Images/weapon.png",    1U },// �V���b�g(��)
    //{ TEXNO::ENEMY,        L"./Data/Images/enemy(test).png",    1U },// �G�l�~�[(��)
    {TEXNO::TURRET01,    L"./Data/Images/Lzi250.png",    1U},        // �p�[�c01(Lzi)
    {TEXNO::CORE01,    L"./Data/Images/core.png",    1U},        // �p�[�c01(Lzi)
    { -1, nullptr }	// �I���t���O
};

//------< �}�N�� >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // �摜�̑��������S


//------< �e�X�g >------------------------------------------------------------------
GameLib::SpriteData sprEnemey_test = SPRITE_CENTER(TEXNO::PLAYER2, 0, 0, 250, 250);

//------< �p�[�c >------------------------------------------------------------------
GameLib::SpriteData sprPartsCore01 = SPRITE_CENTER(TEXNO::CORE01, 0, 0, 250,250 );
GameLib::SpriteData sprPartsTurret01 = SPRITE_CENTER(TEXNO::TURRET01, 0, 0, 250,250 );

//------< �V���b�g >----------------------------------------------------------------
GameLib::SpriteData sprWeapon_NormalShot = SPRITE_CENTER(TEXNO::SHOT, 128 * 4, 0, 128, 128);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
