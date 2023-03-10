//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �f�[�^ >---------------------------------------------------------------

// 2D�摜���[�h�f�[�^
LoadTexture loadTexture[] = {
    { TEXNO::PLAYER,    L"./Data/Images/player.png",    1U },// �v���C���[
    { -1, nullptr }	// �I���t���O
};

//------< �}�N�� >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // �摜�̑��������S

//------< �v���C���[ >----------------------------------------------------------
//�����
SpriteData sprPlayer_Up0    = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 0, 96, 128);
SpriteData sprPlayer_Up1    = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 0, 96, 128);
SpriteData sprPlayer_Up2    = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 0, 96, 128);

//�E����
SpriteData sprPlayer_Right0 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 1, 96, 128);
SpriteData sprPlayer_Right1 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 1, 96, 128);
SpriteData sprPlayer_Right2 = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 1, 96, 128);

//������
SpriteData sprPlayer_Down0  = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 2, 96, 128);
SpriteData sprPlayer_Down1  = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 2, 96, 128);
SpriteData sprPlayer_Down2  = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 2, 96, 128);

//������
SpriteData sprPlayer_Left0  = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 0, 128 * 3, 96, 128);
SpriteData sprPlayer_Left1  = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 1, 128 * 3, 96, 128);
SpriteData sprPlayer_Left2  = SPRITE_BOTTOM(TEXNO::PLAYER, 96 * 2, 128 * 3, 96, 128);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
