#include "all.h"

// ※addition_(追加変数)は省略できる

//  X場所
namespace {
#define yoko_0 1920  
#define yoko_1 1600
#define yoko_2 1280
#define yoko_3 960

#define ue -256
#define sita 1080+256
}

//　Y場所
namespace {
#define Place_uuu 0
#define Place_uu 216
#define Place_u 432
#define Place_m 540
#define Place_s 648
#define Place_ss 864
#define Place_sss 1080-64
}


//スピード
namespace {
#define r0X 5.0f
#define r0Y 0.0f
#define r45X 5.0f
#define r45Y -5.0f
#define r90X 0.0f
#define r90Y -5.0f
#define r135X -5.0f
#define r135Y -5.0f
#define r180X -5.0f
#define r180Y 0.0f
#define r225X -5.0f
#define r225Y 5.0f
#define r270X 0.0f
#define r270Y 5.0f
#define r315X 5.0f
#define r315Y 5.0f

#define r0sX 2.5f
#define r0sY 0.0f
#define r0sX 2.5f
#define r45sX  2.5f
#define r45sY -2.5f
#define r90sX 0.0f
#define r90sY -2.5f
#define r135sX -2.5f
#define r135sY -2.5f
#define r180sX -2.5f
#define r180sY 0.0f
#define r225sX -2.5f
#define r225sY 2.5f
#define r270sX 0.0f
#define r270sY 2.5f
#define r315sX 2.5f
#define r315sY 2.5f

#define r0hX 7.5f
#define r0hY 0.0f
#define r45hX 7.5f
#define r45hY -7.5f
#define r90hX 0.0f
#define r90hY -7.5f
#define r135hX -7.5f
#define r135hY -7.5f
#define r180hX -7.5f
#define r180hY 0.0f
#define r225hX -7.5f
#define r225hY 7.5f
#define r270hX 0.0f
#define r270hY 7.5f
#define r315hX 7.5f
#define r315hY 7.5f

}

//全体スピード調整用
namespace {
#define T1 1
#define T2 1
#define T3 1
#define T4 1
#define T5 1
#define T6 1
}
//ごまかし
namespace {
#define goma_tp -7
#define goma_tps -14
#define goma_move 0.1f
}

//ターンポイント
namespace {
#define turn_x_m  960
#define turn_x_mm  1280
#define turn_x_mmm  1600
}

//時間
#define sec 60

//フェーズ分け  //フェーズ終わりの時間を必ず入力 
namespace {
#define Stage_Start_Delay sec*2 
#define Phase1 Stage_Start_Delay
#define Phase2 Phase1  +sec*(22+1)            
#define Phase3 Phase2 +sec*(8+4)    

#define Stage2_Start_Delay sec*2 
#define Phase21 Stage2_Start_Delay+0
#define Phase22 Phase21  +sec*(9+3)           
#define Phase23 Phase22  +sec*(17+3)     
#define Phase24 Phase23  +sec*21  

#define Stage3_Start_Delay sec*2 
#define Phase31 Stage3_Start_Delay+0
#define Phase32 Phase31  +sec*(11+1)         
#define Phase33 Phase32  +sec*(7+2)     
#define Phase34 Phase33  +sec*(6+2) 

#define Stage5_Start_Delay sec*0 
#define Phase51 Stage5_Start_Delay+0
#define Phase52 Phase51  +sec*(0)          
#define Phase53 Phase52  +sec*(0)    
#define Phase54 Phase53  +sec*(0)

#define Stage6_Start_Delay sec*0 
#define Phase61 Stage6_Start_Delay+0
#define Phase62 Phase61  +sec*(0)          
#define Phase63 Phase62  +sec*(0)    
#define Phase64 Phase63  +sec*(0)
}

#define Stage4_Start_Delay sec*1 
#define Phase41 Stage4_Start_Delay+0
#define Phase42 Phase41  +sec*(7+1)          
#define Phase43 Phase42  +sec*(10+3)    
#define Phase44 Phase43  +sec*(4+3)   

STAGE_SCRIPT stageData01[] =
{
    //Phase1////////////////////////////////////////////////////////////////////////////////

    SET_ENEMY_TARGET_X(
     Phase1 + sec * 0,  //出現F
    enemy01,            //敵の種類
    X,Place_m,         //出現位置
    r0X * T1,r0Y * T1,  //スピード
    turn_x_m,           //目標のX軸
    r180X * T1,r180Y * T1),//目標に到達した後の動き 

    SET_ENEMY_TARGET_X(
     Phase1 + sec * 6,//出現F
    enemy01,//敵の種類
    X,Place_s,//出現位置
    r0X * T1,r0Y * T1,//スピード　
    turn_x_m,//目標のX軸
    r180X * T1,r180Y * T1),//目標に到達した後の動き

    SET_ENEMY_TARGET_X(
     Phase1 + sec * 10,//出現F
    enemy01,//敵の種類
    X,Place_m,//出現位置
    r0X * T1,r0Y * T1,//スピード　
    turn_x_m,//目標のX軸
    r180X * T1,r180Y * T1),//目標に到達した後の動き

    SET_ENEMY_TARGET_X(
     Phase1 + sec * 14,//出現F
    enemy02,//敵の種類
    yoko_1,ue,//出現位置
    r315sX * T1,r315sY * T1,//スピード　
    turn_x_m,//目標のX軸
    r225sX * T1,r225sY * T1),//目標に到達した後の動き   

    SET_ENEMY_TARGET_X(
     Phase1 + sec * 18,//出現F
    enemy02,//敵の種類
    yoko_0,ue,//出現位置
    r315sX * T1,r315sY * T1,//スピード　
    turn_x_m,//目標X軸
    r225sX * T1,r225sY * T1),//帰り

    SET_ENEMY_TARGET_X(
     Phase1 + sec * 22,//出現F
    enemy02,//敵の種類
    yoko_0,sita,//出現位置
    r45sX * T1,r45sY * T1,//スピード　
    turn_x_m,//目標X軸
    r225sX * T1,r225sY * T1),//帰り



    //Phase2//////////////////////////////////////////////////////////////////////

     SET_ENEMY_TARGET_X(
        Phase2 + sec * 0,        //出現時間
        enemy01,                 //敵の種類
        X,Place_m,               //出現位置
        r0X * T1,r0Y * T1,        //行き　
        turn_x_m,                //目標X軸
        r180X * T1,r180Y * T1),  //帰り

    SET_ENEMY_TARGET_X(
        Phase2 + sec * 4,        //出現時間
        enemy02,           //敵の種類
        X,Place_ss,               //出現位置
        r0X * T1,r0Y * T1,        //行き　
        turn_x_m,                //目標X軸
        r135X * T1,r135Y * T1),  //帰り

    SET_ENEMY_TARGET_X(
        Phase2 + sec * 4,        //出現時間
        enemy02,                 //敵の種類
        X,Place_uu,               //出現位置
        r0X * T1,r0Y * T1,        //行き　
        turn_x_m,                //目標X軸
        r225X * T1,r225Y * T1),  //帰り

     SET_ENEMY_TARGET_X(
        Phase2 + sec * 8,        //出現時間
        enemy01,                 //敵の種類
        X,Place_m,               //出現位置
        r0X * T1,r0Y * T1,        //行き　
        turn_x_m,                //目標X軸
        r180X * T1,r180Y * T1),  //帰り

     //Phase3//////////////////////////////////////////////////////////////////////

     SET_ENEMY_TARGET_X(
        Phase3 + sec * 0,       //出現時間
        enemy01,                //敵の種類
        X,Place_ss,             //出現位置
        r0X * T1,r0Y * T1,          //行き
        turn_x_m,               //チェックポイント
        r180X * T1,r180Y * T1),   //帰り 

    SET_ENEMY_TARGET_X(
        Phase3 + sec * 4,      //出現時間
        enemy01,               //敵の種類
        X,Place_uu,            //出現位置
        r0X * T1,r0Y * T1,         //行き
        turn_x_m,              //チェックポイント
        r180X * T1,r180Y * T1),  //帰り 

    SET_ENEMY_TARGET_X(
        Phase3 + sec * 8,     //出現時間
        enemy02,               //敵の種類
        yoko_0,sita,           //出現位置
        r45X * T1,r45Y * T1,     //行き
        turn_x_m,              //チェックポイント
        r225X * T1,r225Y * T1),  //帰り   

    SET_ENEMY_TARGET_X(
        Phase3 + sec * 12,     //出現時間
        enemy02,               //敵の種類
        yoko_0,ue,             //出現位置
        r315X * T1,r315Y * T1,   //行き
        turn_x_m,              //チェックポイント
        r135X * T1,r135Y * T1),  //帰り   

    SET_ENEMY_TARGET_X(
        Phase3 + sec * 16,     //出現時間
        enemy01,               //敵の種類
        yoko_0,ue,             //出現位置
        r315X * T1,r315Y * T1,   //行き
        turn_x_m,              //チェックポイント
        r135X * T1,r135Y * T1),  //帰り   

    SET_ENEMY_TARGET_X(
        Phase3 + sec * 20,     //出現時間
        enemy01,               //敵の種類
        yoko_0, sita,           //出現位置
        r45X * T1, r45Y * T1,     //行き
        turn_x_m,              //チェックポイント
        r225X * T1, r225Y * T1),  //帰り    




        SET_ENEMY_END//ステージ終わり

};

STAGE_SCRIPT stageData02[] =
{

    //Phase1////////////////////////////////////////////////////////////////////////////////

     SET_ENEMY_TARGET_X(
      Phase21 + sec * 0,     //出現時間
      enemy05,               //敵の種類
      yoko_2, sita,           //出現位置
      r90X + goma_move * T2, r90Y * T2,     //行き
      turn_x_mm + goma_tp,              //チェックポイント
      r180sX * T2, r180sY * T2),  //帰り  

    SET_ENEMY_TARGET_X(
      Phase21 + sec * 3,     //出現時間
      enemy04,               //敵の種類
      yoko_2, ue,           //出現位置
      r270X + goma_move * T2, r270Y * T2,     //行き
      turn_x_mm + goma_tp,              //チェックポイント
      r180sX * T2, r180sY * T2),  //帰り  

   SET_ENEMY_TARGET_X(
      Phase21 + sec * 6,     //出現時間
      enemy05,               //敵の種類
      yoko_3, sita,           //出現位置
      r90sX + goma_move * T2, r90sY * T2,     //行き
      turn_x_m + goma_tps,              //チェックポイント
      r180sX * T2, r180sY * T2),  //帰り  

   SET_ENEMY_TARGET_X(
     Phase21 + sec * 8, //出現F
    enemy01,            //敵の種類
    X,Place_u,          //出現位置
    r0hX * T2,r0hY * T2,    //スピード
    turn_x_m           ,//目標のX軸
    r225X * T2,r225Y * T2),       //目標に到達した後の動き 

   SET_ENEMY_TARGET_X(
     Phase21 + sec * 9 ,//出現F
    enemy01,            //敵の種類
    X,Place_s,          //出現位置
    r0hX * T2,r0hY * T2,    //スピード
    turn_x_m,          //目標のX軸
    r135X * T2,r135Y * T2),       //目標に到達した後の動き 


 //Phase2////////////////////////////////////////////////////////////////////////////////
    SET_ENEMY_TARGET_X(
     Phase22 + sec * 0, //出現F
    enemy01,            //敵の種類
    X,Place_u,          //出現位置
    r0hX * T2,r0hY * T2,    //スピード
    turn_x_m           ,//目標のX軸
    r225X * T2,r225Y * T2),       //目標に到達した後の動き 

    SET_ENEMY_TARGET_X(
     Phase22 + sec * 1 ,//出現F
    enemy01,            //敵の種類
    X,Place_s,          //出現位置
    r0hX * T2,r0hY * T2,    //スピード
    turn_x_m,          //目標のX軸
    r135X * T2,r135Y * T2),       //目標に到達した後の動き 

    SET_ENEMY_TARGET_X(
      Phase22 + sec * 8,     //出現時間
      enemy04,               //敵の種類
      yoko_3, ue,           //出現位置
      r270sX + goma_move * T2, r270sY * T2,     //行き
      turn_x_m + goma_tps,              //チェックポイント
      r90sX * T2, r90sY * T2),  //帰り  

   SET_ENEMY_TARGET_X(
     Phase22 + sec * 11, //出現F
    enemy02,            //敵の種類
    X,Place_uu,          //出現位置
    r0hX * T2,r0hY * T2,    //スピード
    turn_x_mm           ,//目標のX軸
    r135X * T2,r135Y * T2),       //目標に到達した後の動き 

    SET_ENEMY_TARGET_X(
      Phase22 + sec * 14,     //出現時間
      enemy05,               //敵の種類
      yoko_3, sita,           //出現位置
      r90sX + goma_move * T2, r90sY * T2,     //行き
      turn_x_m + goma_tps,              //チェックポイント
      r270sX * T2, r270sY * T2),  //帰り  

        SET_ENEMY_TARGET_X(
     Phase22 + sec * 17, //出現F
    enemy02,            //敵の種類
    X,Place_s,          //出現位置
    r0hX * T2,r0hY * T2,    //スピード
    turn_x_mm           ,//目標のX軸
    r225X * T2,r225Y * T2),       //目標に到達した後の動き 

  //Phase3////////////////////////////////////////////////////////////////////////////////
     SET_ENEMY_TARGET_X(
        Phase23 + sec * 0,        //出現時間
        enemy01,                 //敵の種類
        yoko_2,sita,               //出現位置
        r45hX * T2,r45hY * T2,        //行き　
        turn_x_m,                //目標X軸
        r135hX * T2,r135hY * T2),  //帰り 

    SET_ENEMY_TARGET_X(
        Phase23 + sec * 1,        //出現時間
        enemy01,                 //敵の種類
        yoko_2,ue,               //出現位置
        r315hX * T2,r315hY * T2,        //行き　
        turn_x_m,                //目標X軸
        r225hX * T2,r225hY * T2),  //帰り

       SET_ENEMY_TARGET_X(
        Phase23 + sec * 2,        //出現時間
        enemy01,                 //敵の種類
        yoko_2,sita,               //出現位置
        r45hX * T2,r45hY * T2,        //行き　
        turn_x_m,                //目標X軸
        r135hX * T2,r135hY * T2),  //帰り


    SET_ENEMY_TARGET_X(
      Phase23 + sec * 6,     //出現時間
      enemy04,               //敵の種類
      yoko_3, ue,           //出現位置
      r270sX + goma_move * T2, r270sY * T2,     //行き
      turn_x_m + goma_tps,              //チェックポイント
      r90sX * T2, r90sY * T2),  //帰り  

   SET_ENEMY_TARGET_X(
     Phase23 + sec * 9, //出現F
    enemy02,            //敵の種類
    X,Place_uu,          //出現位置
    r0X * T2,r0Y * T2,    //スピード
    turn_x_mm           ,//目標のX軸
    r225sX * T2,r225sY * T2),       //目標に到達した後の動き 

    SET_ENEMY_TARGET_X(
      Phase23 + sec * 13,     //出現時間
      enemy05,               //敵の種類
      yoko_3, sita,           //出現位置
      r90sX + goma_move * T2, r90sY * T2,     //行き
      turn_x_m + goma_tps,              //チェックポイント
      r270sX * T2, r270sY * T2),  //帰り  

        SET_ENEMY_TARGET_X(
     Phase23 + sec * 16, //出現F
    enemy02,            //敵の種類
    X,Place_s,          //出現位置
    r0X * T2,r0Y * T2,    //スピード
    turn_x_mm           ,//目標のX軸
    r135sX * T2,r135sY * T2),       //目標に到達した後の動き 

    SET_ENEMY_END
};

STAGE_SCRIPT stageData03[] =
{
    //Phase1////////////////////////////////////////////////////////////////////////////////

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 0,        //出現時間
         enemy06,                 //敵の種類
        yoko_2,sita,               //出現位置
        r90X + goma_move * T3,r90Y + goma_move * T3,        //行き　
        turn_x_mm + goma_tp,               //目標X軸
        0 * T3, 0 * T3),  //帰り

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 6,        //出現時間
         enemy03,                 //敵の種類
        X,Place_u,               //出現位置
        r0X * T3,r0Y * T3,        //行き　
        turn_x_mm,               //目標X軸
        r180hX * T3,r180hY * T3),  //帰り

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 6,        //出現時間
        enemy01,                  //敵の種類
        X,Place_ss,               //出現位置
        r0hX * T3,r0hY * T3,        //行き　
        turn_x_mm,                //目標X軸
        r45hX * T3,r45hY * T3),  //帰り

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 7,        //出現時間
        enemy01,                  //敵の種類
        X,Place_ss,               //出現位置
        r0hX * T3,r0hY * T3,        //行き　
        turn_x_mm,                //目標X軸
        r45hX * T3,r45hY * T3),  //帰り 

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 9,        //出現時間
        enemy07,                 //敵の種類
        yoko_2,ue,               //出現位置
        r270X + goma_move * T3,r270Y + goma_move * T3,        //行き　
        turn_x_mm + goma_tp,               //目標X軸
        r180sX * T3, r180sY * T3),  //帰り

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 11,        //出現時間
        enemy03,                 //敵の種類
        X,Place_uu,               //出現位置
        r0X * T3,r0Y * T3,        //行き　
        turn_x_mm,               //目標X軸
        r180hX * T3,r180hY * T3),  //帰り


     //Phase2////////////////////////////////////////////////////////////////////////////////

    SET_ENEMY_TARGET_X(
        Phase32 + sec * 0,        //出現時間
        enemy06,                 //敵の種類
        yoko_2,sita,               //出現位置
        r90X + goma_move * T3,r90Y + goma_move * T3,        //行き　
        turn_x_mm + goma_tp,               //目標X軸
        r180X * T3, r180Y * T3),  //帰り

    SET_ENEMY_TARGET_X(//////////////////////
        Phase32 + sec * 1,        //出現時間
        enemy01,                  //敵の種類
        X,Place_uu,               //出現位置
        r0hX * T3,r0hY * T3,        //行き　
        turn_x_mm,                //目標X軸
        r45hX * T3,r45hY * T3),  //帰り

    SET_ENEMY_TARGET_X(
        Phase32 + sec * 2,        //出現時間
        enemy07,                 //敵の種類
        yoko_2,ue,               //出現位置
        r270X + goma_move * T3,r270Y + goma_move * T3,        //行き　
        turn_x_mm + goma_tp,               //目標X軸
        r180X * T3, r180Y * T3),  //帰り

      SET_ENEMY_TARGET_X(//////////////////////
        Phase32 + sec * 3,        //出現時間
        enemy01,                  //敵の種類
        X,Place_uu,               //出現位置
        r0hX * T3,r0hY * T3,        //行き　
        turn_x_mm,                //目標X軸
        r45hX * T3,r45hY * T3),  //帰り 
    SET_ENEMY_TARGET_X(//////////////////////
        Phase32 + sec * 4,        //出現時間
        enemy01,                  //敵の種類
        X,Place_uu,               //出現位置
        r0hX * T3,r0hY * T3,        //行き　
        turn_x_mm,                //目標X軸
        r45hX * T3,r45hY * T3),  //帰り

      SET_ENEMY_TARGET_X(//////////////////////
        Phase32 + sec * 5,        //出現時間
        enemy01,                  //敵の種類
        X,Place_ss,               //出現位置
        r0hX * T3,r0hY * T3,        //行き　
        turn_x_mm,                //目標X軸
        r315hX * T3,r315hY * T3),  //帰り

    SET_ENEMY_TARGET_X(
        Phase32 + sec * 6,        //出現時間
        enemy06,                //敵の種類
        yoko_2,sita,               //出現位置
        r90X + goma_move * T3,r90Y + goma_move * T3,        //行き　
        turn_x_mm + goma_tp,               //目標X軸
        r180X * T3, r180Y * T3),  //帰り

    SET_ENEMY_TARGET_X(
        Phase32 + sec * 7,        //出現時間
        enemy07,                 //敵の種類
        yoko_1,ue,               //出現位置
        r270X + goma_move * T3,r270Y + goma_move * T3,        //行き　
        turn_x_mmm + goma_tp,               //目標X軸
        r180X * T3, r180Y * T3),  //帰り  


//Phase3////////////////////////////////////////////////////////////////////////////////

  SET_ENEMY_TARGET_X(
        Phase33 + sec * 0,        //出現時間
        enemy03,                 //敵の種類
        X,Place_u,               //出現位置
        r0X * T3,r0Y * T3,        //行き　
        turn_x_mm,               //目標X軸
        0 * T3,0 * T3),  //帰り 

  SET_ENEMY_TARGET_X(
        Phase33 + sec * 3,        //出現時間
        enemy03,                 //敵の種類
        X,Place_m,               //出現位置
        r0X * T3,r0Y * T3,        //行き　
        turn_x_mm,               //目標X軸
        r90X * T3,r90Y * T3),   //帰り

  SET_ENEMY_TARGET_X(
        Phase33 + sec * 6 ,        //出現時間
        enemy06,                 //敵の種類
        yoko_2,sita,               //出現位置
        r90X + goma_move * T3,r90Y + goma_move * T3,        //行き　
        turn_x_mm + goma_tp,               //目標X軸
        r135sX * T3, r135sY * T3),  //帰り

//Phase4////////////////////////////////////////////////////////////////////////////////

SET_ENEMY_TARGET_X(
        Phase34 + sec * 0,        //出現時間
        enemy03,                 //敵の種類
        X,Place_s,               //出現位置
        r0X * T3,r0Y * T3,        //行き　
        turn_x_mm,               //目標X軸
        0 * T3, 0 * T3),  //帰り 

  SET_ENEMY_TARGET_X(
        Phase34 + sec * 3,        //出現時間
        enemy03,                 //敵の種類
        X,Place_ss,               //出現位置
        r0X * T3,r0Y * T3,        //行き　
        turn_x_mm,               //目標X軸
        r90X * T3,r90Y * T3),  //帰り

  SET_ENEMY_TARGET_X(
        Phase34 + sec * 6,        //出現時間
        enemy07,                 //敵の種類
        yoko_2,ue,               //出現位置
        r270X + goma_move * T3,r270Y + goma_move * T3,        //行き　
        turn_x_mm + goma_tp,               //目標X軸
        r225sX * T3, r225sY * T3),  //帰り

    SET_ENEMY_END
};

STAGE_SCRIPT stageData04[] =
{
    //Phase1////////////////////////////////////////////////////////////////////////////////
    SET_ENEMY_TARGET_X(
        Phase41 + sec * 0,        //出現時間
        enemy01,                  //敵の種類
        yoko_1,ue,               //出現位置
        r315hX * T4,r315hY * T4,        //行き　
        turn_x_m,                //目標X軸
        r225X * T4,r225Y * T4),  //帰り 

    SET_ENEMY_TARGET_X(
        Phase41 + sec * 1,        //出現時間
        enemy01,                  //敵の種類
        yoko_1,ue,                //出現位置
        r315hX * T4,r315hY * T4,        //行き　
        turn_x_m,                //目標X軸
        r225X * T4,r225Y * T4),  //帰り

    SET_ENEMY_TARGET_X(
        Phase41 + sec * 2,        //出現時間
        enemy01,                  //敵の種類
        yoko_1,ue,                //出現位置
        r315hX * T4,r315hY * T4,        //行き　
        turn_x_m,                //目標X軸
        r225X * T4,r225Y * T4),  //帰り 

    SET_ENEMY_TARGET_X(
        Phase41 + sec * 3,        //出現時間
        enemy01,                  //敵の種類
        X,Place_sss,                //出現位置
        r0hX * T4,r0hY * T4,        //行き　
        turn_x_mm,                //目標X軸
        r270X * T4,r270Y * T4),  //帰り 
     SET_ENEMY_TARGET_X(
        Phase41 + sec * 4,        //出現時間
        enemy01,                  //敵の種類
        X,Place_sss,                //出現位置
        r0hX * T4,r0hY * T4,        //行き　
        turn_x_mm,                //目標X軸
        r270X * T4,r270Y * T4),  //帰り 
     SET_ENEMY_TARGET_X(
        Phase41 + sec * 5,        //出現時間
        enemy01,                  //敵の種類
        X,Place_uu,                //出現位置
        r0hX * T4,r0hY * T4,        //行き　
        turn_x_m,                //目標X軸
        r90X * T4,r90Y * T4),  //帰り

    SET_ENEMY_TARGET_X(
        Phase41 + sec * 6,        //出現時間
        enemy09,                  //敵の種類
        X,Place_uuu + 128,                //出現位置
        r0hX * T4,r0hY * T4,        //行き　
        turn_x_mm,                //目標X軸
        0 * T4,0 * T4),  //帰り

    SET_ENEMY_TARGET_X(
        Phase41 + sec * 6,        //出現時間
        enemy09,                  //敵の種類
        X,Place_sss,                //出現位置
        r0hX * T4,r0hY * T4,        //行き　
        turn_x_mm,                //目標X軸
        0 * T4,0 * T4),  //帰り 




    SET_ENEMY_TARGET_X(
      Phase41 + sec * 7,     //出現時間
      enemy05,               //敵の種類
      yoko_3, sita,           //出現位置
      r90X + goma_move * T4, r90Y * T4,     //行き
      turn_x_m + goma_tp,              //チェックポイント
      r270X * T4, r270Y * T4),  //帰り  

    SET_ENEMY_TARGET_X(
      Phase41 + sec * 7,     //出現時間
      enemy04,               //敵の種類
      yoko_3, ue,           //出現位置
      r270X + goma_move * T4, r270Y * T4,     //行き
      turn_x_m + goma_tp,              //チェックポイント
      r90X * T4, r90Y * T4),  //帰り  

    //Phase2////////////////////////////////////////////////////////////////////////////////

    SET_ENEMY_TARGET_X(
        Phase42 + sec * 0,        //出現時間
        enemy02,                  //敵の種類
        yoko_1,ue,               //出現位置
        r315X * T4,r315Y * T4,        //行き　
        turn_x_m,                //目標X軸
        r315X * T4,r315Y * T4),  //帰り 

    SET_ENEMY_TARGET_X(
        Phase42 + sec * 1,        //出現時間
        enemy02,                  //敵の種類
        yoko_1,sita,                //出現位置
        r315X * T4,r315Y * T4,        //行き　
        turn_x_m,                //目標X軸
        r315X * T4,r315Y * T4),  //帰り

    SET_ENEMY_TARGET_X(
        Phase42 + sec * 2,        //出現時間
        enemy02,                  //敵の種類
        yoko_1,sita,                //出現位置
        r315X * T4,r315Y * T4,        //行き　
        turn_x_m,                //目標X軸
        r315X * T4,r315Y * T4),  //帰り 

    SET_ENEMY_TARGET_X(
      Phase42 + sec * 5,     //出現時間
      enemy06,               //敵の種類
      yoko_3, sita,           //出現位置
      r90X + goma_move * T4, r90Y * T4,     //行き
      turn_x_m + goma_tp,              //チェックポイント
      r180sX * T4, r180sY * T4),  //帰り  

    SET_ENEMY_TARGET_X(
      Phase42 + sec * 6,     //出現時間
      enemy07,               //敵の種類
      yoko_3, ue,           //出現位置
      r270X + goma_move * T4, r270Y * T4,     //行き
      turn_x_m + goma_tp,              //チェックポイント
      r180sX * T4, r180sY * T4),  //帰り 

    SET_ENEMY_TARGET_X(   //BuFF
      Phase42 + sec * 10,     //出現時間
      enemy08,               //敵の種類
      X, Place_m,           //出現位置
      r0X * T4, r0Y * T4,     //行き
      turn_x_mm ,              //チェックポイント
      0 * T4, 0 * T4),  //帰り 

 //Phase3////////////////////////////////////////////////////////////////////////////////
   SET_ENEMY_TARGET_X(
        Phase43 + sec * 0,        //出現時間
        enemy02,                  //敵の種類
        yoko_1,ue,               //出現位置
        r315X * T4,r315Y * T4,        //行き　
        turn_x_m,                //目標X軸
        0 * T4, 0 * T4),  //帰り 

    SET_ENEMY_TARGET_X(
      Phase43 + sec * 0,     //出現時間
      enemy06,               //敵の種類
      yoko_3, sita,           //出現位置
      r90X + goma_move * T4, r90Y * T4,     //行き
      turn_x_m + goma_tp,              //チェックポイント
      r180sX * T4, r180sY * T4),  //帰り  

   SET_ENEMY_TARGET_X(
        Phase43 + sec * 4,        //出現時間
        enemy02,                  //敵の種類
        yoko_1,ue,               //出現位置
        r315X * T4,r315Y * T4,        //行き　
        turn_x_mm,                //目標X軸
        0 * T4, 0 * T4),  //帰り 

    SET_ENEMY_TARGET_X(
      Phase43 + sec * 4,     //出現時間
      enemy06,               //敵の種類
      yoko_2, sita,           //出現位置
      r90X + goma_move * T4, r90Y * T4,     //行き
      turn_x_mm + goma_tp,              //チェックポイント
      r0X * T4, r0Y * T4),  //帰り  

 //Phase3////////////////////////////////////////////////////////////////////////////////
    SET_ENEMY_TARGET_X(
      Phase44 + sec * 0,     //出現時間
      enemy03,               //敵の種類
      X,Place_uu ,           //出現位置
      r0X * T4, r0Y * T4,     //行き
      turn_x_mmm + goma_tp,              //チェックポイント
      0 * T4, 0 * T4),  //帰り  

    SET_ENEMY_TARGET_X(
      Phase44 + sec * 0,     //出現時間
      enemy08,               //敵の種類
      X,Place_m ,           //出現位置
      r0X * T4, r0Y * T4,     //行き
      turn_x_mmm + goma_tp,              //チェックポイント
      0 * T4, 0 * T4),  //帰り

   SET_ENEMY_TARGET_X(
      Phase44 + sec * 0,     //出現時間
      enemy03,               //敵の種類
      X,Place_ss ,           //出現位置
      r0X * T4, r0Y * T4,     //行き
      turn_x_mmm + goma_tp,              //チェックポイント
      0 * T4, 0 * T4),  //帰り  


    SET_ENEMY_END
};


STAGE_SCRIPT stageData05[] =
{
    //Phase1////////////////////////////////////////////////////////////////////////////////
      SET_ENEMY_TARGET_X(
        Phase51 + 45,        //出現時間
        enemy01,                  //敵の種類
        X,Place_u,               //出現位置
        r0X * T5,r0Y * T5,        //行き　
        turn_x_m,                //目標X軸
        r135X * T5,r135Y * T5),  //帰り  

      SET_ENEMY_TARGET_X(
        Phase51 + 90,        //出現時間
        enemy02,                  //敵の種類
        X,Place_s,               //出現位置
        r0X * T5,r0Y * T5,        //行き　
        turn_x_m,                //目標X軸
        r225X * T5,r225Y * T5),  //帰り 

      SET_ENEMY_TARGET_X(
        Phase51 + 135,        //出現時間
        enemy03,                  //敵の種類
        X,Place_u,               //出現位置
        r0X * T5,r0Y * T5,        //行き　
        turn_x_m,                //目標X軸
        r135X * T5,r135Y * T5),  //帰り  

      SET_ENEMY_TARGET_X(
        Phase51 + 180,        //出現時間
        enemy04,                  //敵の種類
        X,Place_s,               //出現位置
        r0X * T5,r0Y * T5,        //行き　
        turn_x_m,                //目標X軸
        r225X * T5,r225Y * T5),  //帰り 

      SET_ENEMY_TARGET_X(
        Phase51 + 225,        //出現時間
        enemy05,                  //敵の種類
        X,Place_u,               //出現位置
        r0X * T5,r0Y * T5,        //行き　
        turn_x_m,                //目標X軸
        r135X * T5,r135Y * T5),  //帰り  

      SET_ENEMY_TARGET_X(
        Phase51 + 270,        //出現時間
        enemy06,                  //敵の種類
        X,Place_s,               //出現位置
        r0X * T5,r0Y * T5,        //行き　
        turn_x_m,                //目標X軸
        r225X * T5,r225Y * T5),  //帰り  

      SET_ENEMY_TARGET_X(
        Phase51 + 315,        //出現時間
        enemy07,                  //敵の種類
        X,Place_u,               //出現位置
        r0X * T5,r0Y * T5,        //行き　
        turn_x_m,                //目標X軸
        r135X * T5,r135Y * T5),  //帰り  

      SET_ENEMY_TARGET_X(
        Phase51 + 360,        //出現時間
        enemy08,                  //敵の種類
        X,Place_s,               //出現位置
        r0X * T5,r0Y * T5,        //行き　
        turn_x_m,                //目標X軸
        r225X * T5,r225Y * T5),  //帰り 

      SET_ENEMY_TARGET_X(
        Phase51 + 405,        //出現時間
        enemy09,                  //敵の種類
        X,Place_u,               //出現位置
        r0X * T5,r0Y * T5,        //行き　
        turn_x_m,                //目標X軸
        r135X * T5,r135Y * T5),  //帰り  

      //SET_ENEMY_TARGET_X(
      //  Phase51 + 450,        //出現時間
      //  enemy01,                  //敵の種類
      //  X,Place_s,               //出現位置
      //  r0X * T5,r0Y * T5,        //行き　
      //  turn_x_m,                //目標X軸
      //  r225X * T5,r225Y * T5),  //帰り 

      //SET_ENEMY_TARGET_X(
      //  Phase51 + 495,        //出現時間
      //  enemy02,                  //敵の種類
      //  X,Place_u,               //出現位置
      //  r0X * T5,r0Y * T5,        //行き　
      //  turn_x_m,                //目標X軸
      //  r135X * T5,r135Y * T5),  //帰り  

      //SET_ENEMY_TARGET_X(
      //  Phase51 + 540,        //出現時間
      //  enemy03,                  //敵の種類
      //  X,Place_s,               //出現位置
      //  r0X * T5,r0Y * T5,        //行き　
      //  turn_x_m,                //目標X軸
      //  r225X * T5,r225Y * T5),  //帰り 



        SET_ENEMY_END
};
STAGE_SCRIPT stageDataBoss[] =
{
     SET_ENEMY_TARGET_X(
        10,        //出現時間
        enemyBoss,                  //敵の種類
        1600,Place_m,               //出現位置
        0 * T5,0 * T5,        //行き　
        turn_x_m,                //目標X軸
        0 * T5,0 * T5),  //帰り  
    SET_ENEMY_END
};