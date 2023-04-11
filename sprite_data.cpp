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

    { -1, nullptr }	// �I���t���O
};

//------< �}�N�� >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // �摜�̑��������S

//------< �v���C���[ >----------------------------------------------------------
//�����
GameLib::SpriteData sprPlayer_Up0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 0, 96, 128);
GameLib::SpriteData sprPlayer_Up1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 0, 96, 128);
GameLib::SpriteData sprPlayer_Up2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 0, 96, 128);

//�E����
GameLib::SpriteData sprPlayer_Right0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 1, 96, 128);
GameLib::SpriteData sprPlayer_Right1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 1, 96, 128);
GameLib::SpriteData sprPlayer_Right2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 1, 96, 128);

//������
GameLib::SpriteData sprPlayer_Down0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 2, 96, 128);
GameLib::SpriteData sprPlayer_Down1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 2, 96, 128);
GameLib::SpriteData sprPlayer_Down2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 2, 96, 128);

//������
GameLib::SpriteData sprPlayer_Left0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 3, 96, 128);
GameLib::SpriteData sprPlayer_Left1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 3, 96, 128);
GameLib::SpriteData sprPlayer_Left2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 3, 96, 128);

//GameLib::SpriteData sprPlayer_test = SPRITE_BOTTOM(TEXNO::PLAYERT,64 * 0, 128 * 0, 128, 128);

//------< �A�C�e�� >-------------------------------------------------------------

//------< �G >------------------------------------------------------------------
//GameLib::SpriteData sprEnemey_test = SPRITE_BOTTOM(TEXNO::ENEMY, 0, 0, 128, 128);
//GameLib::SpriteData sprEnemey_test = SPRITE_BOTTOM(TEXNO::PLAYER2, 0, 0, 250, 250);
GameLib::SpriteData sprEnemey_test = SPRITE_CENTER(TEXNO::PLAYER2, 0, 0, 250, 250);

//------< �V���b�g >----------------------------------------------------------------
GameLib::SpriteData sprWeapon_Sword = SPRITE_BOTTOM(TEXNO::SHOT, 128 * 0, 0, 128, 128);
GameLib::SpriteData sprWeapon_Shuriken = SPRITE_CENTER(TEXNO::SHOT, 128 * 4, 0, 128, 128);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
