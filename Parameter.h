#pragma once

// 使用するパラメータ設定ファイル（.txt）
#define USE_TEXT_FILE "./Parameter(完成時に消す).txt"


#ifdef USE_TEXT_FILE // 開発中に使う方

#include USE_TEXT_FILE 

#else // 完成時に使う方(パラメータ設定ファイルの中身を移す)
                  
// 自機本体
//#define CORE_PLAYER_HP  (1000)
//#define CORE_PLAYER_ATK (1)


#endif 

#undef DEBUG_MODE           // マクロ定義削除