#include "all.h"

// ��addition_(�ǉ��ϐ�)�͏ȗ��ł���

//  X�ꏊ
namespace {
#define yoko_0 1920  
#define yoko_1 1600
#define yoko_2 1280
#define yoko_3 960

#define ue -256
#define sita 1080+256
}

//�@Y�ꏊ
namespace {
#define Place_uuu 0
#define Place_uu 216
#define Place_u 432
#define Place_m 540
#define Place_s 648
#define Place_ss 864
#define Place_sss 1080-64
}


//�X�s�[�h
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

//�S�̃X�s�[�h�����p
namespace {
#define T1 1
#define T2 1
#define T3 1
#define T4 1
#define T5 1
#define T6 1
}
//���܂���
namespace {
#define goma_tp -7
#define goma_tps -14
#define goma_move 0.1f
}

//�^�[���|�C���g
namespace {
#define turn_x_m  960
#define turn_x_mm  1280
#define turn_x_mmm  1600
}

//����
#define sec 60

//�t�F�[�Y����  //�t�F�[�Y�I���̎��Ԃ�K������ 
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
     Phase1 + sec * 0,  //�o��F
    enemy01,            //�G�̎��
    X,Place_m,         //�o���ʒu
    r0X * T1,r0Y * T1,  //�X�s�[�h
    turn_x_m,           //�ڕW��X��
    r180X * T1,r180Y * T1),//�ڕW�ɓ��B������̓��� 

    SET_ENEMY_TARGET_X(
     Phase1 + sec * 6,//�o��F
    enemy01,//�G�̎��
    X,Place_s,//�o���ʒu
    r0X * T1,r0Y * T1,//�X�s�[�h�@
    turn_x_m,//�ڕW��X��
    r180X * T1,r180Y * T1),//�ڕW�ɓ��B������̓���

    SET_ENEMY_TARGET_X(
     Phase1 + sec * 10,//�o��F
    enemy01,//�G�̎��
    X,Place_m,//�o���ʒu
    r0X * T1,r0Y * T1,//�X�s�[�h�@
    turn_x_m,//�ڕW��X��
    r180X * T1,r180Y * T1),//�ڕW�ɓ��B������̓���

    SET_ENEMY_TARGET_X(
     Phase1 + sec * 14,//�o��F
    enemy02,//�G�̎��
    yoko_1,ue,//�o���ʒu
    r315sX * T1,r315sY * T1,//�X�s�[�h�@
    turn_x_m,//�ڕW��X��
    r225sX * T1,r225sY * T1),//�ڕW�ɓ��B������̓���   

    SET_ENEMY_TARGET_X(
     Phase1 + sec * 18,//�o��F
    enemy02,//�G�̎��
    yoko_0,ue,//�o���ʒu
    r315sX * T1,r315sY * T1,//�X�s�[�h�@
    turn_x_m,//�ڕWX��
    r225sX * T1,r225sY * T1),//�A��

    SET_ENEMY_TARGET_X(
     Phase1 + sec * 22,//�o��F
    enemy02,//�G�̎��
    yoko_0,sita,//�o���ʒu
    r45sX * T1,r45sY * T1,//�X�s�[�h�@
    turn_x_m,//�ڕWX��
    r225sX * T1,r225sY * T1),//�A��



    //Phase2//////////////////////////////////////////////////////////////////////

     SET_ENEMY_TARGET_X(
        Phase2 + sec * 0,        //�o������
        enemy01,                 //�G�̎��
        X,Place_m,               //�o���ʒu
        r0X * T1,r0Y * T1,        //�s���@
        turn_x_m,                //�ڕWX��
        r180X * T1,r180Y * T1),  //�A��

    SET_ENEMY_TARGET_X(
        Phase2 + sec * 4,        //�o������
        enemy02,           //�G�̎��
        X,Place_ss,               //�o���ʒu
        r0X * T1,r0Y * T1,        //�s���@
        turn_x_m,                //�ڕWX��
        r135X * T1,r135Y * T1),  //�A��

    SET_ENEMY_TARGET_X(
        Phase2 + sec * 4,        //�o������
        enemy02,                 //�G�̎��
        X,Place_uu,               //�o���ʒu
        r0X * T1,r0Y * T1,        //�s���@
        turn_x_m,                //�ڕWX��
        r225X * T1,r225Y * T1),  //�A��

     SET_ENEMY_TARGET_X(
        Phase2 + sec * 8,        //�o������
        enemy01,                 //�G�̎��
        X,Place_m,               //�o���ʒu
        r0X * T1,r0Y * T1,        //�s���@
        turn_x_m,                //�ڕWX��
        r180X * T1,r180Y * T1),  //�A��

     //Phase3//////////////////////////////////////////////////////////////////////

     SET_ENEMY_TARGET_X(
        Phase3 + sec * 0,       //�o������
        enemy01,                //�G�̎��
        X,Place_ss,             //�o���ʒu
        r0X * T1,r0Y * T1,          //�s��
        turn_x_m,               //�`�F�b�N�|�C���g
        r180X * T1,r180Y * T1),   //�A�� 

    SET_ENEMY_TARGET_X(
        Phase3 + sec * 4,      //�o������
        enemy01,               //�G�̎��
        X,Place_uu,            //�o���ʒu
        r0X * T1,r0Y * T1,         //�s��
        turn_x_m,              //�`�F�b�N�|�C���g
        r180X * T1,r180Y * T1),  //�A�� 

    SET_ENEMY_TARGET_X(
        Phase3 + sec * 8,     //�o������
        enemy02,               //�G�̎��
        yoko_0,sita,           //�o���ʒu
        r45X * T1,r45Y * T1,     //�s��
        turn_x_m,              //�`�F�b�N�|�C���g
        r225X * T1,r225Y * T1),  //�A��   

    SET_ENEMY_TARGET_X(
        Phase3 + sec * 12,     //�o������
        enemy02,               //�G�̎��
        yoko_0,ue,             //�o���ʒu
        r315X * T1,r315Y * T1,   //�s��
        turn_x_m,              //�`�F�b�N�|�C���g
        r135X * T1,r135Y * T1),  //�A��   

    SET_ENEMY_TARGET_X(
        Phase3 + sec * 16,     //�o������
        enemy01,               //�G�̎��
        yoko_0,ue,             //�o���ʒu
        r315X * T1,r315Y * T1,   //�s��
        turn_x_m,              //�`�F�b�N�|�C���g
        r135X * T1,r135Y * T1),  //�A��   

    SET_ENEMY_TARGET_X(
        Phase3 + sec * 20,     //�o������
        enemy01,               //�G�̎��
        yoko_0, sita,           //�o���ʒu
        r45X * T1, r45Y * T1,     //�s��
        turn_x_m,              //�`�F�b�N�|�C���g
        r225X * T1, r225Y * T1),  //�A��    




        SET_ENEMY_END//�X�e�[�W�I���

};

STAGE_SCRIPT stageData02[] =
{

    //Phase1////////////////////////////////////////////////////////////////////////////////

     SET_ENEMY_TARGET_X(
      Phase21 + sec * 0,     //�o������
      enemy05,               //�G�̎��
      yoko_2, sita,           //�o���ʒu
      r90X + goma_move * T2, r90Y * T2,     //�s��
      turn_x_mm + goma_tp,              //�`�F�b�N�|�C���g
      r180sX * T2, r180sY * T2),  //�A��  

    SET_ENEMY_TARGET_X(
      Phase21 + sec * 3,     //�o������
      enemy04,               //�G�̎��
      yoko_2, ue,           //�o���ʒu
      r270X + goma_move * T2, r270Y * T2,     //�s��
      turn_x_mm + goma_tp,              //�`�F�b�N�|�C���g
      r180sX * T2, r180sY * T2),  //�A��  

   SET_ENEMY_TARGET_X(
      Phase21 + sec * 6,     //�o������
      enemy05,               //�G�̎��
      yoko_3, sita,           //�o���ʒu
      r90sX + goma_move * T2, r90sY * T2,     //�s��
      turn_x_m + goma_tps,              //�`�F�b�N�|�C���g
      r180sX * T2, r180sY * T2),  //�A��  

   SET_ENEMY_TARGET_X(
     Phase21 + sec * 8, //�o��F
    enemy01,            //�G�̎��
    X,Place_u,          //�o���ʒu
    r0hX * T2,r0hY * T2,    //�X�s�[�h
    turn_x_m           ,//�ڕW��X��
    r225X * T2,r225Y * T2),       //�ڕW�ɓ��B������̓��� 

   SET_ENEMY_TARGET_X(
     Phase21 + sec * 9 ,//�o��F
    enemy01,            //�G�̎��
    X,Place_s,          //�o���ʒu
    r0hX * T2,r0hY * T2,    //�X�s�[�h
    turn_x_m,          //�ڕW��X��
    r135X * T2,r135Y * T2),       //�ڕW�ɓ��B������̓��� 


 //Phase2////////////////////////////////////////////////////////////////////////////////
    SET_ENEMY_TARGET_X(
     Phase22 + sec * 0, //�o��F
    enemy01,            //�G�̎��
    X,Place_u,          //�o���ʒu
    r0hX * T2,r0hY * T2,    //�X�s�[�h
    turn_x_m           ,//�ڕW��X��
    r225X * T2,r225Y * T2),       //�ڕW�ɓ��B������̓��� 

    SET_ENEMY_TARGET_X(
     Phase22 + sec * 1 ,//�o��F
    enemy01,            //�G�̎��
    X,Place_s,          //�o���ʒu
    r0hX * T2,r0hY * T2,    //�X�s�[�h
    turn_x_m,          //�ڕW��X��
    r135X * T2,r135Y * T2),       //�ڕW�ɓ��B������̓��� 

    SET_ENEMY_TARGET_X(
      Phase22 + sec * 8,     //�o������
      enemy04,               //�G�̎��
      yoko_3, ue,           //�o���ʒu
      r270sX + goma_move * T2, r270sY * T2,     //�s��
      turn_x_m + goma_tps,              //�`�F�b�N�|�C���g
      r90sX * T2, r90sY * T2),  //�A��  

   SET_ENEMY_TARGET_X(
     Phase22 + sec * 11, //�o��F
    enemy02,            //�G�̎��
    X,Place_uu,          //�o���ʒu
    r0hX * T2,r0hY * T2,    //�X�s�[�h
    turn_x_mm           ,//�ڕW��X��
    r135X * T2,r135Y * T2),       //�ڕW�ɓ��B������̓��� 

    SET_ENEMY_TARGET_X(
      Phase22 + sec * 14,     //�o������
      enemy05,               //�G�̎��
      yoko_3, sita,           //�o���ʒu
      r90sX + goma_move * T2, r90sY * T2,     //�s��
      turn_x_m + goma_tps,              //�`�F�b�N�|�C���g
      r270sX * T2, r270sY * T2),  //�A��  

        SET_ENEMY_TARGET_X(
     Phase22 + sec * 17, //�o��F
    enemy02,            //�G�̎��
    X,Place_s,          //�o���ʒu
    r0hX * T2,r0hY * T2,    //�X�s�[�h
    turn_x_mm           ,//�ڕW��X��
    r225X * T2,r225Y * T2),       //�ڕW�ɓ��B������̓��� 

  //Phase3////////////////////////////////////////////////////////////////////////////////
     SET_ENEMY_TARGET_X(
        Phase23 + sec * 0,        //�o������
        enemy01,                 //�G�̎��
        yoko_2,sita,               //�o���ʒu
        r45hX * T2,r45hY * T2,        //�s���@
        turn_x_m,                //�ڕWX��
        r135hX * T2,r135hY * T2),  //�A�� 

    SET_ENEMY_TARGET_X(
        Phase23 + sec * 1,        //�o������
        enemy01,                 //�G�̎��
        yoko_2,ue,               //�o���ʒu
        r315hX * T2,r315hY * T2,        //�s���@
        turn_x_m,                //�ڕWX��
        r225hX * T2,r225hY * T2),  //�A��

       SET_ENEMY_TARGET_X(
        Phase23 + sec * 2,        //�o������
        enemy01,                 //�G�̎��
        yoko_2,sita,               //�o���ʒu
        r45hX * T2,r45hY * T2,        //�s���@
        turn_x_m,                //�ڕWX��
        r135hX * T2,r135hY * T2),  //�A��


    SET_ENEMY_TARGET_X(
      Phase23 + sec * 6,     //�o������
      enemy04,               //�G�̎��
      yoko_3, ue,           //�o���ʒu
      r270sX + goma_move * T2, r270sY * T2,     //�s��
      turn_x_m + goma_tps,              //�`�F�b�N�|�C���g
      r90sX * T2, r90sY * T2),  //�A��  

   SET_ENEMY_TARGET_X(
     Phase23 + sec * 9, //�o��F
    enemy02,            //�G�̎��
    X,Place_uu,          //�o���ʒu
    r0X * T2,r0Y * T2,    //�X�s�[�h
    turn_x_mm           ,//�ڕW��X��
    r225sX * T2,r225sY * T2),       //�ڕW�ɓ��B������̓��� 

    SET_ENEMY_TARGET_X(
      Phase23 + sec * 13,     //�o������
      enemy05,               //�G�̎��
      yoko_3, sita,           //�o���ʒu
      r90sX + goma_move * T2, r90sY * T2,     //�s��
      turn_x_m + goma_tps,              //�`�F�b�N�|�C���g
      r270sX * T2, r270sY * T2),  //�A��  

        SET_ENEMY_TARGET_X(
     Phase23 + sec * 16, //�o��F
    enemy02,            //�G�̎��
    X,Place_s,          //�o���ʒu
    r0X * T2,r0Y * T2,    //�X�s�[�h
    turn_x_mm           ,//�ڕW��X��
    r135sX * T2,r135sY * T2),       //�ڕW�ɓ��B������̓��� 

    SET_ENEMY_END
};

STAGE_SCRIPT stageData03[] =
{
    //Phase1////////////////////////////////////////////////////////////////////////////////

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 0,        //�o������
         enemy06,                 //�G�̎��
        yoko_2,sita,               //�o���ʒu
        r90X + goma_move * T3,r90Y + goma_move * T3,        //�s���@
        turn_x_mm + goma_tp,               //�ڕWX��
        0 * T3, 0 * T3),  //�A��

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 6,        //�o������
         enemy03,                 //�G�̎��
        X,Place_u,               //�o���ʒu
        r0X * T3,r0Y * T3,        //�s���@
        turn_x_mm,               //�ڕWX��
        r180hX * T3,r180hY * T3),  //�A��

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 6,        //�o������
        enemy01,                  //�G�̎��
        X,Place_ss,               //�o���ʒu
        r0hX * T3,r0hY * T3,        //�s���@
        turn_x_mm,                //�ڕWX��
        r45hX * T3,r45hY * T3),  //�A��

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 7,        //�o������
        enemy01,                  //�G�̎��
        X,Place_ss,               //�o���ʒu
        r0hX * T3,r0hY * T3,        //�s���@
        turn_x_mm,                //�ڕWX��
        r45hX * T3,r45hY * T3),  //�A�� 

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 9,        //�o������
        enemy07,                 //�G�̎��
        yoko_2,ue,               //�o���ʒu
        r270X + goma_move * T3,r270Y + goma_move * T3,        //�s���@
        turn_x_mm + goma_tp,               //�ڕWX��
        r180sX * T3, r180sY * T3),  //�A��

    SET_ENEMY_TARGET_X(
        Phase31 + sec * 11,        //�o������
        enemy03,                 //�G�̎��
        X,Place_uu,               //�o���ʒu
        r0X * T3,r0Y * T3,        //�s���@
        turn_x_mm,               //�ڕWX��
        r180hX * T3,r180hY * T3),  //�A��


     //Phase2////////////////////////////////////////////////////////////////////////////////

    SET_ENEMY_TARGET_X(
        Phase32 + sec * 0,        //�o������
        enemy06,                 //�G�̎��
        yoko_2,sita,               //�o���ʒu
        r90X + goma_move * T3,r90Y + goma_move * T3,        //�s���@
        turn_x_mm + goma_tp,               //�ڕWX��
        r180X * T3, r180Y * T3),  //�A��

    SET_ENEMY_TARGET_X(//////////////////////
        Phase32 + sec * 1,        //�o������
        enemy01,                  //�G�̎��
        X,Place_uu,               //�o���ʒu
        r0hX * T3,r0hY * T3,        //�s���@
        turn_x_mm,                //�ڕWX��
        r45hX * T3,r45hY * T3),  //�A��

    SET_ENEMY_TARGET_X(
        Phase32 + sec * 2,        //�o������
        enemy07,                 //�G�̎��
        yoko_2,ue,               //�o���ʒu
        r270X + goma_move * T3,r270Y + goma_move * T3,        //�s���@
        turn_x_mm + goma_tp,               //�ڕWX��
        r180X * T3, r180Y * T3),  //�A��

      SET_ENEMY_TARGET_X(//////////////////////
        Phase32 + sec * 3,        //�o������
        enemy01,                  //�G�̎��
        X,Place_uu,               //�o���ʒu
        r0hX * T3,r0hY * T3,        //�s���@
        turn_x_mm,                //�ڕWX��
        r45hX * T3,r45hY * T3),  //�A�� 
    SET_ENEMY_TARGET_X(//////////////////////
        Phase32 + sec * 4,        //�o������
        enemy01,                  //�G�̎��
        X,Place_uu,               //�o���ʒu
        r0hX * T3,r0hY * T3,        //�s���@
        turn_x_mm,                //�ڕWX��
        r45hX * T3,r45hY * T3),  //�A��

      SET_ENEMY_TARGET_X(//////////////////////
        Phase32 + sec * 5,        //�o������
        enemy01,                  //�G�̎��
        X,Place_ss,               //�o���ʒu
        r0hX * T3,r0hY * T3,        //�s���@
        turn_x_mm,                //�ڕWX��
        r315hX * T3,r315hY * T3),  //�A��

    SET_ENEMY_TARGET_X(
        Phase32 + sec * 6,        //�o������
        enemy06,                //�G�̎��
        yoko_2,sita,               //�o���ʒu
        r90X + goma_move * T3,r90Y + goma_move * T3,        //�s���@
        turn_x_mm + goma_tp,               //�ڕWX��
        r180X * T3, r180Y * T3),  //�A��

    SET_ENEMY_TARGET_X(
        Phase32 + sec * 7,        //�o������
        enemy07,                 //�G�̎��
        yoko_1,ue,               //�o���ʒu
        r270X + goma_move * T3,r270Y + goma_move * T3,        //�s���@
        turn_x_mmm + goma_tp,               //�ڕWX��
        r180X * T3, r180Y * T3),  //�A��  


//Phase3////////////////////////////////////////////////////////////////////////////////

  SET_ENEMY_TARGET_X(
        Phase33 + sec * 0,        //�o������
        enemy03,                 //�G�̎��
        X,Place_u,               //�o���ʒu
        r0X * T3,r0Y * T3,        //�s���@
        turn_x_mm,               //�ڕWX��
        0 * T3,0 * T3),  //�A�� 

  SET_ENEMY_TARGET_X(
        Phase33 + sec * 3,        //�o������
        enemy03,                 //�G�̎��
        X,Place_m,               //�o���ʒu
        r0X * T3,r0Y * T3,        //�s���@
        turn_x_mm,               //�ڕWX��
        r90X * T3,r90Y * T3),   //�A��

  SET_ENEMY_TARGET_X(
        Phase33 + sec * 6 ,        //�o������
        enemy06,                 //�G�̎��
        yoko_2,sita,               //�o���ʒu
        r90X + goma_move * T3,r90Y + goma_move * T3,        //�s���@
        turn_x_mm + goma_tp,               //�ڕWX��
        r135sX * T3, r135sY * T3),  //�A��

//Phase4////////////////////////////////////////////////////////////////////////////////

SET_ENEMY_TARGET_X(
        Phase34 + sec * 0,        //�o������
        enemy03,                 //�G�̎��
        X,Place_s,               //�o���ʒu
        r0X * T3,r0Y * T3,        //�s���@
        turn_x_mm,               //�ڕWX��
        0 * T3, 0 * T3),  //�A�� 

  SET_ENEMY_TARGET_X(
        Phase34 + sec * 3,        //�o������
        enemy03,                 //�G�̎��
        X,Place_ss,               //�o���ʒu
        r0X * T3,r0Y * T3,        //�s���@
        turn_x_mm,               //�ڕWX��
        r90X * T3,r90Y * T3),  //�A��

  SET_ENEMY_TARGET_X(
        Phase34 + sec * 6,        //�o������
        enemy07,                 //�G�̎��
        yoko_2,ue,               //�o���ʒu
        r270X + goma_move * T3,r270Y + goma_move * T3,        //�s���@
        turn_x_mm + goma_tp,               //�ڕWX��
        r225sX * T3, r225sY * T3),  //�A��

    SET_ENEMY_END
};

STAGE_SCRIPT stageData04[] =
{
    //Phase1////////////////////////////////////////////////////////////////////////////////
    SET_ENEMY_TARGET_X(
        Phase41 + sec * 0,        //�o������
        enemy01,                  //�G�̎��
        yoko_1,ue,               //�o���ʒu
        r315hX * T4,r315hY * T4,        //�s���@
        turn_x_m,                //�ڕWX��
        r225X * T4,r225Y * T4),  //�A�� 

    SET_ENEMY_TARGET_X(
        Phase41 + sec * 1,        //�o������
        enemy01,                  //�G�̎��
        yoko_1,ue,                //�o���ʒu
        r315hX * T4,r315hY * T4,        //�s���@
        turn_x_m,                //�ڕWX��
        r225X * T4,r225Y * T4),  //�A��

    SET_ENEMY_TARGET_X(
        Phase41 + sec * 2,        //�o������
        enemy01,                  //�G�̎��
        yoko_1,ue,                //�o���ʒu
        r315hX * T4,r315hY * T4,        //�s���@
        turn_x_m,                //�ڕWX��
        r225X * T4,r225Y * T4),  //�A�� 

    SET_ENEMY_TARGET_X(
        Phase41 + sec * 3,        //�o������
        enemy01,                  //�G�̎��
        X,Place_sss,                //�o���ʒu
        r0hX * T4,r0hY * T4,        //�s���@
        turn_x_mm,                //�ڕWX��
        r270X * T4,r270Y * T4),  //�A�� 
     SET_ENEMY_TARGET_X(
        Phase41 + sec * 4,        //�o������
        enemy01,                  //�G�̎��
        X,Place_sss,                //�o���ʒu
        r0hX * T4,r0hY * T4,        //�s���@
        turn_x_mm,                //�ڕWX��
        r270X * T4,r270Y * T4),  //�A�� 
     SET_ENEMY_TARGET_X(
        Phase41 + sec * 5,        //�o������
        enemy01,                  //�G�̎��
        X,Place_uu,                //�o���ʒu
        r0hX * T4,r0hY * T4,        //�s���@
        turn_x_m,                //�ڕWX��
        r90X * T4,r90Y * T4),  //�A��

    SET_ENEMY_TARGET_X(
        Phase41 + sec * 6,        //�o������
        enemy09,                  //�G�̎��
        X,Place_uuu + 128,                //�o���ʒu
        r0hX * T4,r0hY * T4,        //�s���@
        turn_x_mm,                //�ڕWX��
        0 * T4,0 * T4),  //�A��

    SET_ENEMY_TARGET_X(
        Phase41 + sec * 6,        //�o������
        enemy09,                  //�G�̎��
        X,Place_sss,                //�o���ʒu
        r0hX * T4,r0hY * T4,        //�s���@
        turn_x_mm,                //�ڕWX��
        0 * T4,0 * T4),  //�A�� 




    SET_ENEMY_TARGET_X(
      Phase41 + sec * 7,     //�o������
      enemy05,               //�G�̎��
      yoko_3, sita,           //�o���ʒu
      r90X + goma_move * T4, r90Y * T4,     //�s��
      turn_x_m + goma_tp,              //�`�F�b�N�|�C���g
      r270X * T4, r270Y * T4),  //�A��  

    SET_ENEMY_TARGET_X(
      Phase41 + sec * 7,     //�o������
      enemy04,               //�G�̎��
      yoko_3, ue,           //�o���ʒu
      r270X + goma_move * T4, r270Y * T4,     //�s��
      turn_x_m + goma_tp,              //�`�F�b�N�|�C���g
      r90X * T4, r90Y * T4),  //�A��  

    //Phase2////////////////////////////////////////////////////////////////////////////////

    SET_ENEMY_TARGET_X(
        Phase42 + sec * 0,        //�o������
        enemy02,                  //�G�̎��
        yoko_1,ue,               //�o���ʒu
        r315X * T4,r315Y * T4,        //�s���@
        turn_x_m,                //�ڕWX��
        r315X * T4,r315Y * T4),  //�A�� 

    SET_ENEMY_TARGET_X(
        Phase42 + sec * 1,        //�o������
        enemy02,                  //�G�̎��
        yoko_1,sita,                //�o���ʒu
        r315X * T4,r315Y * T4,        //�s���@
        turn_x_m,                //�ڕWX��
        r315X * T4,r315Y * T4),  //�A��

    SET_ENEMY_TARGET_X(
        Phase42 + sec * 2,        //�o������
        enemy02,                  //�G�̎��
        yoko_1,sita,                //�o���ʒu
        r315X * T4,r315Y * T4,        //�s���@
        turn_x_m,                //�ڕWX��
        r315X * T4,r315Y * T4),  //�A�� 

    SET_ENEMY_TARGET_X(
      Phase42 + sec * 5,     //�o������
      enemy06,               //�G�̎��
      yoko_3, sita,           //�o���ʒu
      r90X + goma_move * T4, r90Y * T4,     //�s��
      turn_x_m + goma_tp,              //�`�F�b�N�|�C���g
      r180sX * T4, r180sY * T4),  //�A��  

    SET_ENEMY_TARGET_X(
      Phase42 + sec * 6,     //�o������
      enemy07,               //�G�̎��
      yoko_3, ue,           //�o���ʒu
      r270X + goma_move * T4, r270Y * T4,     //�s��
      turn_x_m + goma_tp,              //�`�F�b�N�|�C���g
      r180sX * T4, r180sY * T4),  //�A�� 

    SET_ENEMY_TARGET_X(   //BuFF
      Phase42 + sec * 10,     //�o������
      enemy08,               //�G�̎��
      X, Place_m,           //�o���ʒu
      r0X * T4, r0Y * T4,     //�s��
      turn_x_mm ,              //�`�F�b�N�|�C���g
      0 * T4, 0 * T4),  //�A�� 

 //Phase3////////////////////////////////////////////////////////////////////////////////
   SET_ENEMY_TARGET_X(
        Phase43 + sec * 0,        //�o������
        enemy02,                  //�G�̎��
        yoko_1,ue,               //�o���ʒu
        r315X * T4,r315Y * T4,        //�s���@
        turn_x_m,                //�ڕWX��
        0 * T4, 0 * T4),  //�A�� 

    SET_ENEMY_TARGET_X(
      Phase43 + sec * 0,     //�o������
      enemy06,               //�G�̎��
      yoko_3, sita,           //�o���ʒu
      r90X + goma_move * T4, r90Y * T4,     //�s��
      turn_x_m + goma_tp,              //�`�F�b�N�|�C���g
      r180sX * T4, r180sY * T4),  //�A��  

   SET_ENEMY_TARGET_X(
        Phase43 + sec * 4,        //�o������
        enemy02,                  //�G�̎��
        yoko_1,ue,               //�o���ʒu
        r315X * T4,r315Y * T4,        //�s���@
        turn_x_mm,                //�ڕWX��
        0 * T4, 0 * T4),  //�A�� 

    SET_ENEMY_TARGET_X(
      Phase43 + sec * 4,     //�o������
      enemy06,               //�G�̎��
      yoko_2, sita,           //�o���ʒu
      r90X + goma_move * T4, r90Y * T4,     //�s��
      turn_x_mm + goma_tp,              //�`�F�b�N�|�C���g
      r0X * T4, r0Y * T4),  //�A��  

 //Phase3////////////////////////////////////////////////////////////////////////////////
    SET_ENEMY_TARGET_X(
      Phase44 + sec * 0,     //�o������
      enemy03,               //�G�̎��
      X,Place_uu ,           //�o���ʒu
      r0X * T4, r0Y * T4,     //�s��
      turn_x_mmm + goma_tp,              //�`�F�b�N�|�C���g
      0 * T4, 0 * T4),  //�A��  

    SET_ENEMY_TARGET_X(
      Phase44 + sec * 0,     //�o������
      enemy08,               //�G�̎��
      X,Place_m ,           //�o���ʒu
      r0X * T4, r0Y * T4,     //�s��
      turn_x_mmm + goma_tp,              //�`�F�b�N�|�C���g
      0 * T4, 0 * T4),  //�A��

   SET_ENEMY_TARGET_X(
      Phase44 + sec * 0,     //�o������
      enemy03,               //�G�̎��
      X,Place_ss ,           //�o���ʒu
      r0X * T4, r0Y * T4,     //�s��
      turn_x_mmm + goma_tp,              //�`�F�b�N�|�C���g
      0 * T4, 0 * T4),  //�A��  


    SET_ENEMY_END
};


STAGE_SCRIPT stageData05[] =
{
    //Phase1////////////////////////////////////////////////////////////////////////////////
      SET_ENEMY_TARGET_X(
        Phase51 + 45,        //�o������
        enemy01,                  //�G�̎��
        X,Place_u,               //�o���ʒu
        r0X * T5,r0Y * T5,        //�s���@
        turn_x_m,                //�ڕWX��
        r135X * T5,r135Y * T5),  //�A��  

      SET_ENEMY_TARGET_X(
        Phase51 + 90,        //�o������
        enemy02,                  //�G�̎��
        X,Place_s,               //�o���ʒu
        r0X * T5,r0Y * T5,        //�s���@
        turn_x_m,                //�ڕWX��
        r225X * T5,r225Y * T5),  //�A�� 

      SET_ENEMY_TARGET_X(
        Phase51 + 135,        //�o������
        enemy03,                  //�G�̎��
        X,Place_u,               //�o���ʒu
        r0X * T5,r0Y * T5,        //�s���@
        turn_x_m,                //�ڕWX��
        r135X * T5,r135Y * T5),  //�A��  

      SET_ENEMY_TARGET_X(
        Phase51 + 180,        //�o������
        enemy04,                  //�G�̎��
        X,Place_s,               //�o���ʒu
        r0X * T5,r0Y * T5,        //�s���@
        turn_x_m,                //�ڕWX��
        r225X * T5,r225Y * T5),  //�A�� 

      SET_ENEMY_TARGET_X(
        Phase51 + 225,        //�o������
        enemy05,                  //�G�̎��
        X,Place_u,               //�o���ʒu
        r0X * T5,r0Y * T5,        //�s���@
        turn_x_m,                //�ڕWX��
        r135X * T5,r135Y * T5),  //�A��  

      SET_ENEMY_TARGET_X(
        Phase51 + 270,        //�o������
        enemy06,                  //�G�̎��
        X,Place_s,               //�o���ʒu
        r0X * T5,r0Y * T5,        //�s���@
        turn_x_m,                //�ڕWX��
        r225X * T5,r225Y * T5),  //�A��  

      SET_ENEMY_TARGET_X(
        Phase51 + 315,        //�o������
        enemy07,                  //�G�̎��
        X,Place_u,               //�o���ʒu
        r0X * T5,r0Y * T5,        //�s���@
        turn_x_m,                //�ڕWX��
        r135X * T5,r135Y * T5),  //�A��  

      SET_ENEMY_TARGET_X(
        Phase51 + 360,        //�o������
        enemy08,                  //�G�̎��
        X,Place_s,               //�o���ʒu
        r0X * T5,r0Y * T5,        //�s���@
        turn_x_m,                //�ڕWX��
        r225X * T5,r225Y * T5),  //�A�� 

      SET_ENEMY_TARGET_X(
        Phase51 + 405,        //�o������
        enemy09,                  //�G�̎��
        X,Place_u,               //�o���ʒu
        r0X * T5,r0Y * T5,        //�s���@
        turn_x_m,                //�ڕWX��
        r135X * T5,r135Y * T5),  //�A��  

      //SET_ENEMY_TARGET_X(
      //  Phase51 + 450,        //�o������
      //  enemy01,                  //�G�̎��
      //  X,Place_s,               //�o���ʒu
      //  r0X * T5,r0Y * T5,        //�s���@
      //  turn_x_m,                //�ڕWX��
      //  r225X * T5,r225Y * T5),  //�A�� 

      //SET_ENEMY_TARGET_X(
      //  Phase51 + 495,        //�o������
      //  enemy02,                  //�G�̎��
      //  X,Place_u,               //�o���ʒu
      //  r0X * T5,r0Y * T5,        //�s���@
      //  turn_x_m,                //�ڕWX��
      //  r135X * T5,r135Y * T5),  //�A��  

      //SET_ENEMY_TARGET_X(
      //  Phase51 + 540,        //�o������
      //  enemy03,                  //�G�̎��
      //  X,Place_s,               //�o���ʒu
      //  r0X * T5,r0Y * T5,        //�s���@
      //  turn_x_m,                //�ڕWX��
      //  r225X * T5,r225Y * T5),  //�A�� 



        SET_ENEMY_END
};
STAGE_SCRIPT stageDataBoss[] =
{
     SET_ENEMY_TARGET_X(
        10,        //�o������
        enemyBoss,                  //�G�̎��
        1600,Place_m,               //�o���ʒu
        0 * T5,0 * T5,        //�s���@
        turn_x_m,                //�ڕWX��
        0 * T5,0 * T5),  //�A��  
    SET_ENEMY_END
};