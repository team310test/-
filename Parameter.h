#pragma once

//******************************************************************************
// 
//      �p�����[�^�Ǘ� 
// 
//******************************************************************************

// �S�p�[�c�ɋ��ʂ���p�����[�^
namespace
{  
    #define PARTS_OBJ_SIZE              (128.0f)        // �T�C�Y

    // OBJ���X�V�ł���X�P�[���Œ�l�i����ȉ��͍X�V���Ȃ��j
    #define UPDATE_OBJ_SCALE_MIN_LIMIT  (0.0625f)       // 4�񕪂̏k������

    // OBJ���`��ł���X�P�[���Œ�l�i����ȉ��͕`�悵�Ȃ��j
    #define DRAW_OBJ_SCALE_MIN_LIMIT    (0.03125f)      // 5�񕪂̏k������

    #define OBJ_DAMAGED_BLINK           (0x02)          // �_���[�W���󂯂����̓_�ŋ

    #define ROT_90                      (ToRadian(90)) // 90�x
}


// �v���C���[�֌W�̃p�����[�^
namespace
{
    // �v���C���[�R�A�E�v���C���[�p�[�c�ɋ��ʂ������
    namespace
    {
        #define PL_SPEED     (6.0f)         // ���x
        #define PL_SPEED_MAX (12.0f)        // �ő呬�x
    }

    // �v���C���[�R�A
    namespace
    {
        #define PL_CORE_HP      (1000)      // �̗�
        #define PL_CORE_HITBOX  (45.0f)     // �����蔻��i��j
    }

    // �v���C���[�p�[�c
    namespace
    {
        #define COMBINE_DMG_TIMER (30)      // ������������̖��G���� 

        #define DEATH_DELAY_TIME (5)        // �p�[�c���A���I�Ɏ��S����Ƃ��̒x������
    
        #define TO_CORE_SPEED (-0.14f * 4)  // �v���C���[�{�̂֌������������x
    }

}


// �G�l�~�[�֌W�̃p�����[�^
namespace
{
    // EnemyCore01
    namespace
    {
        #define ENM_CORE01_HP           (1)         // �̗�
        #define ENM_CORE01_ATK          (1)         // �U����
        #define ENM_CORE01_ROT_SPEED    (-0.05f)    // ��]���x
    }

    // EnemyTurret01
    namespace
    {
        #define ENM_TURRET01_HP         (1)         // �̗�
        #define ENM_TURRET01_ATK        (1)         // �U����
        #define ENM_TURRET01_ATK_TIME   (120)       // �U���Ԋu����
    }    
    
    // EnemyBuff01
    namespace
    {
        #define ENM_BUFF01_HP           (1)         // �̗�
        #define ENM_BUFF01_ATK          (1)         // �U����
        #define ENM_BUFF01_ATK_TIME     (120)       // �U���N�[���^�C��
    }

    // EnemyCommon
    namespace
    {
        #define ENM_COMMON_SIZE_36      (36.0f)     // �T�C�Y
        #define ENM_COMMON_SIZE_64      (64.0f)     // �����蔻��
        #define ENM_COMMON_SIZE_18      (18.0f)     // �����蔻��

        // EnemyCommon01
        namespace
        {
            #define ENM_COMMON01_HP     (1)         // �̗�
            #define ENM_COMMON01_ATK    (1)         // �U����
        }        

        // EnemyCommon01_2
        namespace
        {
            #define ENM_COMMON01_2_HP     (1)         // �̗�
            #define ENM_COMMON01_2_ATK    (1)         // �U����
        }

    }

}


// �o�t�p�[�c�֌W�̃p�����[�^
namespace
{
    #define BUFF_SUB_ATK_TIMER  (1)                 // �o�t�p�[�c���U���N�[���^�C�������炷�l
}


// �h���b�v�p�[�c�֌W�̃p�����[�^
namespace
{
    #define DROP_PARTS_SPEED (-2.0f)    // ���x

    // �h���b�v�p�[�c�̖��Ŋ֌W
    #define ADD_BLINK_COLOR (0.025f)    // ���ł��鑬�x�ɉe��
    #define BLINK_COLOR_MAX (0.6f)      // ���ŃJ���[�̍ő�l
    #define BLINK_COLOR_MIN (-0.5f)     // ���ŃJ���[�̍Œ�l
}


// �e�֌W�̃p�����[�^
namespace
{
    // �ʏ�e
    #define NORMAL_SHOT_SPEED           (30.0f)
    #define NORMAL_SHOT_ATK             (1)
    
    // �����g�e�i�g�j					         
    #define SINE_WAVE_SHOT_SPEED        (20.0f)
    #define SIN_YOFS                    (64.0f)  // �U�ꕝ
    #define SINE_WAVE_SHOT_ATK          (1)
    
    // ��`�g�e�i�J�N�J�N�j
    #define SQUARE_WAVE_SHOT_SPEED_X    (40.0f)
    #define SQUARE_WAVE_SHOT_SPEED_Y    (20.0f)
    #define SQUARE_WAVE_SHOT_POSX_LIMIT (300.0f) // ��x�ɑO�ɐi�߂鋗��
    #define SQUARE_WAVE_SHOT_POSY_LIMIT (75.0f)  // �㉺�ړ��ł�����E
    #define SQUARE_WAVE_SHOT_ATK        (1)
    
    // �J�[�u�e�i��J�[�u�j
    #define CURVE_SHOT_SPEED_X          (-20.0f)
    #define CURVE_SHOT_SPEED_Y          (-25.0f)
    #define CURVE_SHOT_ACCEL_X          (1.4f)   // X���x�ɑ���X�����x
    #define CURVE_SHOT_ACCEL_Y          (0.9f)   // Y���x�ɑ���Y�����x
    #define CURVE_SHOT_ATK              (1)
    
    // �ђʒe�i�����e�j
    #define PENETRATE_SHOT_SPEED        (100.0f)
    #define PENETRATE_SHOT_ATK          (1)
    
    // �v���C���[�_���e
    #define AIM_SHOT_SPEED_X            (10.0f)
    #define AIM_SHOT_SPEED_Y            (10.0f)
    #define AIM_SHOT_ATK                (1)

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
    #define BG_SCROLL_SPEED (-5.0f) // �w�i�X�N���[�����x

    // �f��̍���(LetterBox)
    namespace
    {
        #define LETTER_BOX_ADD_SPEED (0.015f)   // ���Z(���т��オ�鑬�x)					 
        #define LETTER_BOX_SUB_SPEED (-0.005f)  // ���Z(���т��~��鑬�x)				   	 
    }

}