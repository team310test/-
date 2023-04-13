#pragma once

//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

#include "../GameLib/texture.h"

// ラベル定義
enum TEXNO
{
    // ゲーム
    PLAYER,
    PLAYERT,
    PLAYER2,
    PLAYER3,
    BACK,
    ENEMY,
    SHOT,
    PARTS01
};

extern GameLib::LoadTexture loadTexture[];

//------< プレイヤー >----------------------------------------------------------
//上歩き
extern GameLib::SpriteData sprPlayer_Up0;
extern GameLib::SpriteData sprPlayer_Up1;
extern GameLib::SpriteData sprPlayer_Up2;

//右歩き
extern GameLib::SpriteData sprPlayer_Right0;
extern GameLib::SpriteData sprPlayer_Right1;
extern GameLib::SpriteData sprPlayer_Right2;

//下歩き
extern GameLib::SpriteData sprPlayer_Down0;
extern GameLib::SpriteData sprPlayer_Down1;
extern GameLib::SpriteData sprPlayer_Down2;

//左歩き
extern GameLib::SpriteData sprPlayer_Left0;
extern GameLib::SpriteData sprPlayer_Left1;
extern GameLib::SpriteData sprPlayer_Left2;

extern GameLib::SpriteData sprPlayer_test;

//------< アイテム >-------------------------------------------------------------

extern GameLib::SpriteData sprItem_Sword;
extern GameLib::SpriteData sprItem_Key;
extern GameLib::SpriteData sprItem_Orb;

//------< 敵 >------------------------------------------------------------------

extern GameLib::SpriteData sprEnemey_test;
extern GameLib::SpriteData sprPlayer_test;
extern GameLib::SpriteData sprParts01;

// Enemy0
extern GameLib::SpriteData sprEnemy0_Up0;
extern GameLib::SpriteData sprEnemy0_Up1;
extern GameLib::SpriteData sprEnemy0_Up2;

extern GameLib::SpriteData sprEnemy0_Right0;
extern GameLib::SpriteData sprEnemy0_Right1;
extern GameLib::SpriteData sprEnemy0_Right2;

extern GameLib::SpriteData sprEnemy0_Down0;
extern GameLib::SpriteData sprEnemy0_Down1;
extern GameLib::SpriteData sprEnemy0_Down2;

extern GameLib::SpriteData sprEnemy0_Left0;
extern GameLib::SpriteData sprEnemy0_Left1;
extern GameLib::SpriteData sprEnemy0_Left2;

// Enemy1
extern GameLib::SpriteData sprEnemy1_Up0;
extern GameLib::SpriteData sprEnemy1_Up1;
extern GameLib::SpriteData sprEnemy1_Up2;

extern GameLib::SpriteData sprEnemy1_Right0;
extern GameLib::SpriteData sprEnemy1_Right1;
extern GameLib::SpriteData sprEnemy1_Right2;

extern GameLib::SpriteData sprEnemy1_Down0;
extern GameLib::SpriteData sprEnemy1_Down1;
extern GameLib::SpriteData sprEnemy1_Down2;

extern GameLib::SpriteData sprEnemy1_Left0;
extern GameLib::SpriteData sprEnemy1_Left1;
extern GameLib::SpriteData sprEnemy1_Left2;

// Enemy5
extern GameLib::SpriteData sprEnemy5_Up0;
extern GameLib::SpriteData sprEnemy5_Up1;
extern GameLib::SpriteData sprEnemy5_Up2;

extern GameLib::SpriteData sprEnemy5_Right0;
extern GameLib::SpriteData sprEnemy5_Right1;
extern GameLib::SpriteData sprEnemy5_Right2;

extern GameLib::SpriteData sprEnemy5_Down0;
extern GameLib::SpriteData sprEnemy5_Down1;
extern GameLib::SpriteData sprEnemy5_Down2;

extern GameLib::SpriteData sprEnemy5_Left0;
extern GameLib::SpriteData sprEnemy5_Left1;
extern GameLib::SpriteData sprEnemy5_Left2;

//------< 武器 >----------------------------------------------------------------

extern GameLib::SpriteData sprWeapon_Sword;
extern GameLib::SpriteData sprWeapon_Katana;
extern GameLib::SpriteData sprWeapon_Axe;
extern GameLib::SpriteData sprWeapon_Spear;
extern GameLib::SpriteData sprWeapon_Shuriken;

//******************************************************************************
