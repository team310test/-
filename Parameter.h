#pragma once

// debug::setStringを表示させる
#define DEBUG_MODE

//******************************************************************************
// 
//      パラメータ管理 
// 
//******************************************************************************

// 共通するパラメータ
namespace
{  
    #define PARTS_OBJ_SIZE              (128.0f)            // サイズ

    #define DMG_TIME                    (40)                // ダメージを受けた時の点滅時間
    #define OBJ_DAMAGED_BLINK           (0x02)              // ダメージを受けた時の点滅具合

    #define PARTS_DEATH_DELAY_TIME      (5)                 // パーツが連鎖的に死亡するときの遅延時間

    // OBJが更新・描画できる各スケール最低値（これ以下は更新・描画しない）
    namespace
    {
        #define UPDATE_OBJ_SCALE_MIN_LIMIT  (0.0625f)       // 4回分の縮小相当
        #define DRAW_OBJ_SCALE_MIN_LIMIT    (0.03125f)      // 5回分の縮小相当
    }
 
    // コモンパーツのサイズ・当たり判定
    namespace
    {
        #define COMMON_SIZE_36              (36.0f)         // サイズ
        #define COMMON_HITBOX_64            (64.0f)         // 当たり判定
        #define COMMON_HITBOX_18            (18.0f)         // 当たり判定
    }

    // 角度
    #define ROT_90                      (ToRadian(90.0f))   // 90度
}


// プレイヤー関係のパラメータ
namespace
{
    // プレイヤーコア・プレイヤーパーツに共通するもの
    namespace
    {
        #define PL_SPEED            (6.0f)         // 速度
        #define PL_SPEED_MAX        (12.0f)        // 最大速度
    }

    // プレイヤーコア
    namespace
    {
        #define PL_CORE_HP          (100)      // 体力
        #define PL_CORE_HITBOX      (45.0f)     // 当たり判定（被）
        #define PL_CORE_ATK         (1)         // 攻撃力(体当たりダメージ)
        #define PL_CORE_ATK_TIME    (30)        // 攻撃クールタイム
    }

    // プレイヤーパーツ
    // ※体力はドロップパーツの方で設定(NEXT_HP)
    namespace
    {
        #define COMBINE_DMG_TIME   (30)        // くっついた直後の点滅時間 
    
        #define TO_CORE_SPEED       (-0.14f * 4) // プレイヤー本体へ向かう初期速度

        #define PL_PARTS_ATK_TIME   (30)        // 攻撃クールタイム

        // パーツ各攻撃力(体当たりダメージ)
        namespace
        {
            #define PL_TURRET01_ATK     (1)     // 攻撃力(体当たりダメージ)
            #define PL_TURRET02_ATK     (1)     // 攻撃力(体当たりダメージ)
            #define PL_TURRET03_ATK     (1)     // 攻撃力(体当たりダメージ)
            #define PL_TURRET03_ATK     (1)     // 攻撃力(体当たりダメージ)                 

            #define PL_SHIELD01_ATK     (1)     // 攻撃力(体当たりダメージ)

            #define PL_BUFF01_ATK       (0)     // 攻撃力(体当たりダメージ)
                                                
            #define PL_TRASH01_ATK      (1)     // 攻撃力(体当たりダメージ)
            #define PL_TRASH02_ATK      (1)     // 攻撃力(体当たりダメージ)
            #define PL_TRASH03_ATK      (1)     // 攻撃力(体当たりダメージ)
                                                
            #define PL_COMMON01_ATK     (1)     // 攻撃力(体当たりダメージ)
            #define PL_COMMON02_ATK     (1)     // 攻撃力(体当たりダメージ)
            #define PL_COMMON03_ATK     (1)     // 攻撃力(体当たりダメージ)
            #define PL_COMMON04_ATK     (1)     // 攻撃力(体当たりダメージ)
            #define PL_COMMON05_ATK     (1)     // 攻撃力(体当たりダメージ)
            #define PL_COMMON06_ATK     (1)     // 攻撃力(体当たりダメージ)
        }
        
    }

}


// エネミー関係のパラメータ
namespace
{
    // EnemyCore
    namespace
    {
        #define ENM_CORE01_HP           (1)         // 体力
        #define ENM_CORE01_ATK          (1)         // 攻撃力(体当たりダメージ)
        #define ENM_CORE01_ROT_SPEED    (-0.05f)    // 回転速度
        #define ENM_CORE02_HP           (1)         // 体力
        #define ENM_CORE02_ATK          (1)         // 攻撃力(体当たりダメージ)
    }

    // EnemyTurret
    namespace
    {
        #define ENM_TURRET01_HP         (1)         // 体力
        #define ENM_TURRET01_ATK        (1)         // 攻撃力(体当たりダメージ)
        #define ENM_TURRET01_ATK_TIME   (120)       // 攻撃間隔時間
        #define ENM_TURRET02_ANGLE      (45.0f)     // タレットの角度
        //#define ENM_TURRET03_ANGLE      (45.0f)     // タレットの角度
    }    
    
    // EnemyShield
    namespace
    {
        #define ENM_SHIELD01_HP         (15)        // 体力
        #define ENM_SHIELD01_ATK        (1)         // 攻撃力(体当たりダメージ)
    }    
    
    // EnemyBuff
    namespace
    {
        #define ENM_BUFF01_HP           (1)         // 体力
        #define ENM_BUFF01_ATK          (0)         // 攻撃力(体当たりダメージ)
    }
 
    // EnemyCommon
    namespace
    {
        #define ENM_COMMON01_HP         (1)       // 体力
        #define ENM_COMMON01_ATK        (1)       // 攻撃力(体当たりダメージ)
         
        #define ENM_COMMON02_HP         (1)       // 体力
        #define ENM_COMMON02_ATK        (1)       // 攻撃力(体当たりダメージ)

        #define ENM_COMMON03_HP         (1)       // 体力
        #define ENM_COMMON03_ATK        (1)       // 攻撃力(体当たりダメージ)

        #define ENM_COMMON04_HP         (1)       // 体力
        #define ENM_COMMON04_ATK        (1)       // 攻撃力(体当たりダメージ)
    
        #define ENM_COMMON05_HP         (1)       // 体力
        #define ENM_COMMON05_ATK        (1)       // 攻撃力(体当たりダメージ)
    
        #define ENM_COMMON06_HP         (1)       // 体力
        #define ENM_COMMON06_ATK        (1)       // 攻撃力(体当たりダメージ)
   }

}


// バフパーツ関係のパラメータ
namespace
{
    #define BUFF_SUB_ATK_TIMER  (1)             // バフパーツが攻撃クールタイムを減らす値
}


// ドロップパーツ関係のパラメータ
namespace
{
    #define DROP_PARTS_SPEED_X (-2.0f)           // X速度

    // プレイヤーになるときの各体力
    namespace
    {
        #define DROP_TURRET01_NEXT_HP   (1)     // プレイヤーになるときの体力
        #define DROP_TURRET02_NEXT_HP   (1)     // プレイヤーになるときの体力
        #define DROP_TURRET03_NEXT_HP   (1)     // プレイヤーになるときの体力
        #define DROP_SHIELD01_NEXT_HP   (15)    // プレイヤーになるときの体力
        #define DROP_BUFF01_NEXT_HP     (1)     // プレイヤーになるときの体力
        #define DROP_TRASH01_NEXT_HP    (3)     // プレイヤーになるときの体力
        #define DROP_TRASH02_NEXT_HP    (3)     // プレイヤーになるときの体力
        #define DROP_TRASH03_NEXT_HP    (3)     // プレイヤーになるときの体力
                                                
        #define DROP_COMMON01_NEXT_HP   (3)     // プレイヤーになるときの体力                                          
        #define DROP_COMMON02_NEXT_HP   (3)     // プレイヤーになるときの体力
        #define DROP_COMMON03_NEXT_HP   (3)     // プレイヤーになるときの体力
        #define DROP_COMMON04_NEXT_HP   (3)     // プレイヤーになるときの体力
        #define DROP_COMMON05_NEXT_HP   (3)     // プレイヤーになるときの体力                                          
        #define DROP_COMMON06_NEXT_HP   (3)     // プレイヤーになるときの体力
    }

    // ドロップパーツの明滅関係
    namespace
    {
        #define ADD_BLINK_COLOR (0.025f)        // 明滅する速度に影響
        #define BLINK_COLOR_MAX (0.6f)          // 明滅カラーの最大値
        #define BLINK_COLOR_MIN (-0.5f)         // 明滅カラーの最低値
    }
}


// 弾関係のパラメータ
namespace
{
    #define SHOT_HITBOX                     (12.0f) // 弾の当たり判定

    // 通常弾
    namespace
    {
        #define NORMAL_SHOT_SPEED           (30.0f)
        #define NORMAL_SHOT_ATK             (1)
    }

    // 正弦波弾（波）		
    namespace
    {
        #define SINE_WAVE_SHOT_SPEED        (20.0f)
        #define SIN_YOFS                    (64.0f)  // 振れ幅
        #define SINE_WAVE_SHOT_ATK          (1)
    }

    // 矩形波弾（カクカク）
    namespace
    {
        #define SQUARE_WAVE_SHOT_SPEED_X    (40.0f)
        #define SQUARE_WAVE_SHOT_SPEED_Y    (20.0f)
        #define SQUARE_WAVE_SHOT_POSX_LIMIT (300.0f) // 一度に前に進める距離
        #define SQUARE_WAVE_SHOT_POSY_LIMIT (75.0f)  // 上下移動できる限界
        #define SQUARE_WAVE_SHOT_ATK        (1)
    }

    // カーブ弾（上カーブ）
    namespace
    {
        #define CURVE_SHOT_SPEED_X          (-25.0f)
        #define CURVE_SHOT_SPEED_Y          (-20.0f)
        #define CURVE_SHOT_ACCEL_X          (1.4f)   // X速度に足すX加速度
        #define CURVE_SHOT_ACCEL_Y          (0.9f)   // Y速度に足すY加速度
        #define CURVE_SHOT_ATK              (1)
    }

    // 貫通弾（高速弾）
    namespace
    {
        #define PENETRATE_SHOT_SPEED        (100.0f)
        #define PENETRATE_SHOT_ATK          (1)
    }

    // プレイヤー狙撃弾
    namespace
    {
        #define AIM_SHOT_SPEED_X            (10.0f)
        #define AIM_SHOT_SPEED_Y            (10.0f)
        #define AIM_SHOT_ATK                (1)
    }

}


// 縮小関連のパラメータ
namespace
{   
    // 背景の縮小の初期速度
    #define BG_SHRINK_SPEED (0.0025f * 4)

    // 縮小の初期速度
    #define SHRINK_SPEED  (0.0025f * 4) 
}


// 背景関係のパラメータ
namespace
{
    #define BG_SCROLL_SPEED             (-5.0f)    // 背景スクロール速度

    // 映画の黒帯(LetterBox)
    namespace
    {
        #define LETTER_BOX_ADD_SPEED    (0.02f)   // 加算(黒帯が上がる速度)					 
        #define LETTER_BOX_SUB_SPEED    (-0.01f)  // 減算(黒帯が降りる速度)				   	 
    }

}

// 地震（シェイク）関係のパラメータ
namespace
{
    #define ADD_QUAKE_POS   (10)   // 揺れ幅
    #define LOOP_MAX        (3)    // 繰り返す回数
}

// ゲームオーバー関係のパラメータ
namespace
{
    #define GAME_OVER_SCALE (3.0f)              // 自機スケール
    
    // 落下速度
    #define GAME_OVER_SPEED_X (0.1f)            // 速度(X)
    #define GAME_OVER_SPEED_Y (1.5f)            // 速度(Y)
    #define GAME_OVER_Initial_SPEED_X (0.0f)    // 初速度(X)
    #define GAME_OVER_Initial_SPEED_Y (-30.0f)  // 初速度(Y)
}