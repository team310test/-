#pragma once

//******************************************************************************
// 
//      パラメータ管理 
// 
//******************************************************************************

// 共通するパラメータ
namespace
{  
    #define PARTS_OBJ_SIZE              (128.0f)            // サイズ
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
        #define PL_CORE_HP          (1000)      // 体力
        #define PL_CORE_HITBOX      (45.0f)     // 当たり判定（被）
        #define PL_CORE_ATK         (1)         // 攻撃力(体当たりダメージ)
        #define PL_CORE_ATK_TIME    (30)        // 攻撃クールタイム
    }

    // プレイヤーパーツ
    // 体力はドロップパーツの方で設定(NEXT_HP)
    namespace
    {
        #define COMBINE_DMG_TIMER   (30)        // くっついた直後の無敵時間 
    
        #define TO_CORE_SPEED       (-0.14f * 4)  // プレイヤー本体へ向かう初期速度

        #define PL_PARTS_ATK_TIME   (30)        // 攻撃クールタイム

        // パーツ各攻撃力(体当たりダメージ)
        namespace
        {
            #define PL_TURRET01_ATK     (1)     // 攻撃力(体当たりダメージ)
                                                 
            #define PL_BUFF01_ATK       (0)     // 攻撃力(体当たりダメージ)
                                                // 攻撃力(体当たりダメージ)
            #define PL_TRASH01_ATK      (1)     // 攻撃力(体当たりダメージ)
                                                
            #define PL_COMMON01_ATK     (1)     // 攻撃力(体当たりダメージ)
            #define PL_COMMON01_2_ATK   (1)     // 攻撃力(体当たりダメージ)
            #define PL_COMMON02_ATK     (1)     // 攻撃力(体当たりダメージ)
            #define PL_COMMON02_2_ATK   (1)     // 攻撃力(体当たりダメージ)
            #define PL_COMMON03_ATK     (1)     // 攻撃力(体当たりダメージ)
            #define PL_COMMON03_2_ATK   (1)     // 攻撃力(体当たりダメージ)
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
    }

    // EnemyTurret
    namespace
    {
        #define ENM_TURRET01_HP         (1)         // 体力
        #define ENM_TURRET01_ATK        (1)         // 攻撃力(体当たりダメージ)
        #define ENM_TURRET01_ATK_TIME   (120)       // 攻撃間隔時間
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
         
        #define ENM_COMMON01_2_HP       (1)       // 体力
        #define ENM_COMMON01_2_ATK      (1)       // 攻撃力(体当たりダメージ)
    
        #define ENM_COMMON02_HP         (1)       // 体力
        #define ENM_COMMON02_ATK        (1)       // 攻撃力(体当たりダメージ)

        #define ENM_COMMON02_2_HP       (1)       // 体力
        #define ENM_COMMON02_2_ATK      (1)       // 攻撃力(体当たりダメージ)
    
        #define ENM_COMMON03_HP         (1)       // 体力
        #define ENM_COMMON03_ATK        (1)       // 攻撃力(体当たりダメージ)
    
        #define ENM_COMMON03_2_HP       (1)       // 体力
        #define ENM_COMMON03_2_ATK      (1)       // 攻撃力(体当たりダメージ)
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
    #define DROP_PARTS_SPEEDX (-2.0f)       // X速度

    // プレイヤーになるときの各体力
    namespace
    {
        #define DROP_TURRET01_NEXT_HP   (1) // プレイヤーになるときの体力
        #define DROP_BUFF01_NEXT_HP     (1) // プレイヤーになるときの体力
        #define DROP_TRASH01_NEXT_HP    (3) // プレイヤーになるときの体力
                                            
        #define DROP_COMMON01_NEXT_HP   (3) // プレイヤーになるときの体力
        #define DROP_COMMON01_2_NEXT_HP (3) // プレイヤーになるときの体力
                                            
        #define DROP_COMMON02_NEXT_HP   (3) // プレイヤーになるときの体力
        #define DROP_COMMON02_2_NEXT_HP (3) // プレイヤーになるときの体力
                                            
        #define DROP_COMMON03_NEXT_HP   (3) // プレイヤーになるときの体力
        #define DROP_COMMON03_2_NEXT_HP (3) // プレイヤーになるときの体力
    }

    // ドロップパーツの明滅関係
    namespace
    {
        #define ADD_BLINK_COLOR (0.025f)    // 明滅する速度に影響
        #define BLINK_COLOR_MAX (0.6f)      // 明滅カラーの最大値
        #define BLINK_COLOR_MIN (-0.5f)     // 明滅カラーの最低値
    }
}


// 弾関係のパラメータ
namespace
{
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
        #define CURVE_SHOT_SPEED_X          (-20.0f)
        #define CURVE_SHOT_SPEED_Y          (-25.0f)
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
        #define LETTER_BOX_ADD_SPEED    (0.015f)   // 加算(黒帯が上がる速度)					 
        #define LETTER_BOX_SUB_SPEED    (-0.005f)  // 減算(黒帯が降りる速度)				   	 
    }

}


// 地震（シェイク）関係のパラメータ
namespace
{
    #define ADD_QUAKE_POS   (10)   // 揺れ幅
    #define LOOP_MAX        (3)    // 繰り返す回数
}