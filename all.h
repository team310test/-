#ifndef ALL_H
#define ALL_H

//必要なインクルードファイル
#include "../GameLib/game_lib.h"

//共通で使われるヘッダー
#include "common.h"
#include "audio.h"
#include "tool.h"
#include "game_start.h"
#include "combo_list.h"	//共通で使われるか怪しい
#include "game_end.h"

//個々のヘッダーファイルは下の方へ
#include "scene_game.h"
#include "scene_title.h"
#include "scene_result.h"
#include "rule.h"
#include "player.h"
#include "food.h"
#include "belt.h"
#include "test.h"

//using ディレクティブ
using namespace GameLib;
using namespace input;

#endif	//ALL_H 