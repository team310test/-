#pragma once

//******************************************************************************
//
//
//      common
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include <DirectXMath.h>

//
#define PAD_MOVE    (PAD_RIGHT|PAD_LEFT|PAD_DOWN|PAD_UP)

//------< 関数ポインタ >----------------------------------------------------------------
// 角度変換用
extern float(* const ToRadian)(float);
extern float(* const ToDegree)(float);