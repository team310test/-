#pragma once

// debug::setString��\��������
#define DEBUG_MODE

//******************************************************************************
// 
//      �p�����[�^�Ǘ� 
// 
//******************************************************************************

// ���ʂ���p�����[�^
namespace
{  
    #define PARTS_OBJ_SIZE              (128.0f)            // �T�C�Y

    #define DMG_TIME                    (40)                // �_���[�W���󂯂����̓_�Ŏ���
    #define OBJ_DAMAGED_BLINK           (0x02)              // �_���[�W���󂯂����̓_�ŋ

    #define PARTS_DEATH_DELAY_TIME      (5)                 // �p�[�c���A���I�Ɏ��S����Ƃ��̒x������

    // OBJ���X�V�E�`��ł���e�X�P�[���Œ�l�i����ȉ��͍X�V�E�`�悵�Ȃ��j
    namespace
    {
        #define UPDATE_OBJ_SCALE_MIN_LIMIT  (0.0625f)       // 4�񕪂̏k������
        #define DRAW_OBJ_SCALE_MIN_LIMIT    (0.03125f)      // 5�񕪂̏k������
    }
 
    // �R�����p�[�c�̃T�C�Y�E�����蔻��
    namespace
    {
        #define COMMON_SIZE_36              (36.0f)         // �T�C�Y
        #define COMMON_HITBOX_64            (64.0f)         // �����蔻��
        #define COMMON_HITBOX_18            (18.0f)         // �����蔻��
    }

    // �p�x
    #define ROT_90                      (ToRadian(90.0f))   // 90�x
}


// �v���C���[�֌W�̃p�����[�^
namespace
{
    // �v���C���[�R�A�E�v���C���[�p�[�c�ɋ��ʂ������
    namespace
    {
        #define PL_SPEED            (6.0f)         // ���x
        #define PL_SPEED_MAX        (12.0f)        // �ő呬�x
    }

    // �v���C���[�R�A
    namespace
    {
        #define PL_CORE_HP          (100)      // �̗�
        #define PL_CORE_HITBOX      (45.0f)     // �����蔻��i��j
        #define PL_CORE_ATK         (1)         // �U����(�̓�����_���[�W)
        #define PL_CORE_ATK_TIME    (30)        // �U���N�[���^�C��
    }

    // �v���C���[�p�[�c
    // ���̗͂̓h���b�v�p�[�c�̕��Őݒ�(NEXT_HP)
    namespace
    {
        #define COMBINE_DMG_TIME   (30)        // ������������̓_�Ŏ��� 
    
        #define TO_CORE_SPEED       (-0.14f * 4) // �v���C���[�{�̂֌������������x

        #define PL_PARTS_ATK_TIME   (30)        // �U���N�[���^�C��

        // �p�[�c�e�U����(�̓�����_���[�W)
        namespace
        {
            #define PL_TURRET01_ATK     (1)     // �U����(�̓�����_���[�W)
            #define PL_TURRET02_ATK     (1)     // �U����(�̓�����_���[�W)
            #define PL_TURRET03_ATK     (1)     // �U����(�̓�����_���[�W)
            #define PL_TURRET03_ATK     (1)     // �U����(�̓�����_���[�W)                 

            #define PL_SHIELD01_ATK     (1)     // �U����(�̓�����_���[�W)

            #define PL_BUFF01_ATK       (0)     // �U����(�̓�����_���[�W)
                                                
            #define PL_TRASH01_ATK      (1)     // �U����(�̓�����_���[�W)
            #define PL_TRASH02_ATK      (1)     // �U����(�̓�����_���[�W)
            #define PL_TRASH03_ATK      (1)     // �U����(�̓�����_���[�W)
                                                
            #define PL_COMMON01_ATK     (1)     // �U����(�̓�����_���[�W)
            #define PL_COMMON02_ATK     (1)     // �U����(�̓�����_���[�W)
            #define PL_COMMON03_ATK     (1)     // �U����(�̓�����_���[�W)
            #define PL_COMMON04_ATK     (1)     // �U����(�̓�����_���[�W)
            #define PL_COMMON05_ATK     (1)     // �U����(�̓�����_���[�W)
            #define PL_COMMON06_ATK     (1)     // �U����(�̓�����_���[�W)
        }
        
    }

}


// �G�l�~�[�֌W�̃p�����[�^
namespace
{
    // EnemyCore
    namespace
    {
        #define ENM_CORE01_HP           (1)         // �̗�
        #define ENM_CORE01_ATK          (1)         // �U����(�̓�����_���[�W)
        #define ENM_CORE01_ROT_SPEED    (-0.05f)    // ��]���x
        #define ENM_CORE02_HP           (1)         // �̗�
        #define ENM_CORE02_ATK          (1)         // �U����(�̓�����_���[�W)
    }

    // EnemyTurret
    namespace
    {
        #define ENM_TURRET01_HP         (1)         // �̗�
        #define ENM_TURRET01_ATK        (1)         // �U����(�̓�����_���[�W)
        #define ENM_TURRET01_ATK_TIME   (120)       // �U���Ԋu����
        #define ENM_TURRET02_ANGLE      (45.0f)     // �^���b�g�̊p�x
        //#define ENM_TURRET03_ANGLE      (45.0f)     // �^���b�g�̊p�x
    }    
    
    // EnemyShield
    namespace
    {
        #define ENM_SHIELD01_HP         (15)        // �̗�
        #define ENM_SHIELD01_ATK        (1)         // �U����(�̓�����_���[�W)
    }    
    
    // EnemyBuff
    namespace
    {
        #define ENM_BUFF01_HP           (1)         // �̗�
        #define ENM_BUFF01_ATK          (0)         // �U����(�̓�����_���[�W)
    }
 
    // EnemyCommon
    namespace
    {
        #define ENM_COMMON01_HP         (1)       // �̗�
        #define ENM_COMMON01_ATK        (1)       // �U����(�̓�����_���[�W)
         
        #define ENM_COMMON02_HP         (1)       // �̗�
        #define ENM_COMMON02_ATK        (1)       // �U����(�̓�����_���[�W)

        #define ENM_COMMON03_HP         (1)       // �̗�
        #define ENM_COMMON03_ATK        (1)       // �U����(�̓�����_���[�W)

        #define ENM_COMMON04_HP         (1)       // �̗�
        #define ENM_COMMON04_ATK        (1)       // �U����(�̓�����_���[�W)
    
        #define ENM_COMMON05_HP         (1)       // �̗�
        #define ENM_COMMON05_ATK        (1)       // �U����(�̓�����_���[�W)
    
        #define ENM_COMMON06_HP         (1)       // �̗�
        #define ENM_COMMON06_ATK        (1)       // �U����(�̓�����_���[�W)
   }

}


// �o�t�p�[�c�֌W�̃p�����[�^
namespace
{
    #define BUFF_SUB_ATK_TIMER  (1)             // �o�t�p�[�c���U���N�[���^�C�������炷�l
}


// �h���b�v�p�[�c�֌W�̃p�����[�^
namespace
{
    #define DROP_PARTS_SPEED_X (-2.0f)           // X���x

    // �v���C���[�ɂȂ�Ƃ��̊e�̗�
    namespace
    {
        #define DROP_TURRET01_NEXT_HP   (1)     // �v���C���[�ɂȂ�Ƃ��̗̑�
        #define DROP_TURRET02_NEXT_HP   (1)     // �v���C���[�ɂȂ�Ƃ��̗̑�
        #define DROP_TURRET03_NEXT_HP   (1)     // �v���C���[�ɂȂ�Ƃ��̗̑�
        #define DROP_SHIELD01_NEXT_HP   (15)    // �v���C���[�ɂȂ�Ƃ��̗̑�
        #define DROP_BUFF01_NEXT_HP     (1)     // �v���C���[�ɂȂ�Ƃ��̗̑�
        #define DROP_TRASH01_NEXT_HP    (3)     // �v���C���[�ɂȂ�Ƃ��̗̑�
        #define DROP_TRASH02_NEXT_HP    (3)     // �v���C���[�ɂȂ�Ƃ��̗̑�
        #define DROP_TRASH03_NEXT_HP    (3)     // �v���C���[�ɂȂ�Ƃ��̗̑�
                                                
        #define DROP_COMMON01_NEXT_HP   (3)     // �v���C���[�ɂȂ�Ƃ��̗̑�                                          
        #define DROP_COMMON02_NEXT_HP   (3)     // �v���C���[�ɂȂ�Ƃ��̗̑�
        #define DROP_COMMON03_NEXT_HP   (3)     // �v���C���[�ɂȂ�Ƃ��̗̑�
        #define DROP_COMMON04_NEXT_HP   (3)     // �v���C���[�ɂȂ�Ƃ��̗̑�
        #define DROP_COMMON05_NEXT_HP   (3)     // �v���C���[�ɂȂ�Ƃ��̗̑�                                          
        #define DROP_COMMON06_NEXT_HP   (3)     // �v���C���[�ɂȂ�Ƃ��̗̑�
    }

    // �h���b�v�p�[�c�̖��Ŋ֌W
    namespace
    {
        #define ADD_BLINK_COLOR (0.025f)        // ���ł��鑬�x�ɉe��
        #define BLINK_COLOR_MAX (0.6f)          // ���ŃJ���[�̍ő�l
        #define BLINK_COLOR_MIN (-0.5f)         // ���ŃJ���[�̍Œ�l
    }
}


// �e�֌W�̃p�����[�^
namespace
{
    #define SHOT_HITBOX                     (12.0f) // �e�̓����蔻��

    // �ʏ�e
    namespace
    {
        #define NORMAL_SHOT_SPEED           (30.0f)
        #define NORMAL_SHOT_ATK             (1)
    }

    // �����g�e�i�g�j		
    namespace
    {
        #define SINE_WAVE_SHOT_SPEED        (20.0f)
        #define SIN_YOFS                    (64.0f)  // �U�ꕝ
        #define SINE_WAVE_SHOT_ATK          (1)
    }

    // ��`�g�e�i�J�N�J�N�j
    namespace
    {
        #define SQUARE_WAVE_SHOT_SPEED_X    (40.0f)
        #define SQUARE_WAVE_SHOT_SPEED_Y    (20.0f)
        #define SQUARE_WAVE_SHOT_POSX_LIMIT (300.0f) // ��x�ɑO�ɐi�߂鋗��
        #define SQUARE_WAVE_SHOT_POSY_LIMIT (75.0f)  // �㉺�ړ��ł�����E
        #define SQUARE_WAVE_SHOT_ATK        (1)
    }

    // �J�[�u�e�i��J�[�u�j
    namespace
    {
        #define CURVE_SHOT_SPEED_X          (-25.0f)
        #define CURVE_SHOT_SPEED_Y          (-20.0f)
        #define CURVE_SHOT_ACCEL_X          (1.4f)   // X���x�ɑ���X�����x
        #define CURVE_SHOT_ACCEL_Y          (0.9f)   // Y���x�ɑ���Y�����x
        #define CURVE_SHOT_ATK              (1)
    }

    // �ђʒe�i�����e�j
    namespace
    {
        #define PENETRATE_SHOT_SPEED        (100.0f)
        #define PENETRATE_SHOT_ATK          (1)
    }

    // �v���C���[�_���e
    namespace
    {
        #define AIM_SHOT_SPEED_X            (10.0f)
        #define AIM_SHOT_SPEED_Y            (10.0f)
        #define AIM_SHOT_ATK                (1)
    }

}


// �k���֘A�̃p�����[�^
namespace
{   
    // �w�i�̏k���̏������x
    #define BG_SHRINK_SPEED (0.0025f * 4)

    // �k���̏������x
    #define SHRINK_SPEED  (0.0025f * 4) 
}


// �w�i�֌W�̃p�����[�^
namespace
{
    #define BG_SCROLL_SPEED             (-5.0f)    // �w�i�X�N���[�����x

    // �f��̍���(LetterBox)
    namespace
    {
        #define LETTER_BOX_ADD_SPEED    (0.02f)   // ���Z(���т��オ�鑬�x)					 
        #define LETTER_BOX_SUB_SPEED    (-0.01f)  // ���Z(���т��~��鑬�x)				   	 
    }

}

// �n�k�i�V�F�C�N�j�֌W�̃p�����[�^
namespace
{
    #define ADD_QUAKE_POS   (10)   // �h�ꕝ
    #define LOOP_MAX        (3)    // �J��Ԃ���
}

// �Q�[���I�[�o�[�֌W�̃p�����[�^
namespace
{
    #define GAME_OVER_SCALE (3.0f)              // ���@�X�P�[��
    
    // �������x
    #define GAME_OVER_SPEED_X (0.1f)            // ���x(X)
    #define GAME_OVER_SPEED_Y (1.5f)            // ���x(Y)
    #define GAME_OVER_Initial_SPEED_X (0.0f)    // �����x(X)
    #define GAME_OVER_Initial_SPEED_Y (-30.0f)  // �����x(Y)
}