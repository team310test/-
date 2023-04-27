#pragma once

// �g�p����p�����[�^�ݒ�t�@�C���i.txt�j
// #define USE_TEXT_FILE "./Parameter(�������ɏ���).txt"


#ifdef USE_TEXT_FILE // �J�����Ɏg����

#include USE_TEXT_FILE 

#else // �������Ɏg����(�p�����[�^�ݒ�t�@�C���̒��g���ڂ�)
             
//////////////////////////////
// HP	�F�̗�
// SPEED�F���x
// ATK	�F�U����
//////////////////////////////



///// �v���C���[�{�́E�v���C���[�p�[�c�̑��x //////

#define PL_SPEED     (6.0f)
#define PL_SPEED_MAX (12.0f)

////////////////////////////////////////////////



//////// �v���C���[�{�� /////////////////////////

#define CORE_PLAYER_HP (1000)

////////////////////////////////////////////////



//////// �h���b�v�p�[�c /////////////////////////

#define DROP_PARTS_SPEED (-2.0f)

////////////////////////////////////////////////



///////////// �e ///////////////////////////////

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

////////////////////////////////////////////////




////////// �k���֘A /////////////////////////////

// OBJ���X�V�ł���X�P�[���Œ�l�i����ȉ��͍X�V���Ȃ��j
#define UPDATE_OBJ_SCALE_MIN_LIMIT (0.0625f) // 4�񕪂̏k������

// OBJ���`��ł���X�P�[���Œ�l�i����ȉ��͕`�悵�Ȃ��j
#define DRAW_OBJ_SCALE_MIN_LIMIT (0.03125f) // 5�񕪂̏k������


#define SHRINK_SPEED  (0.0025f * 4) // �k���̏������x

#define TO_CORE_SPEED (-0.14f * 4) // �p�[�c���v���C���[�{�̂֌������������x

////////////////////////////////////////////////




//////////////////////// �w�i //////////////////////////////////////////////


/////// �w�i�X�N���[�����x //////////////////////

#define BG_SCROLL_SPEED (-5.0f)

/////// �f��̍���(LetterBox)�̑��x /////////////

#define LETTER_BOX_ADD_SPEED (0.0125f) // ���Z(���т��オ�鑬�x)					 
#define LETTER_BOX_SUB_SPEED (-0.005f) // ���Z(���т��~��鑬�x)				   	 

///////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////


#endif 


#undef DEBUG_MODE           // �}�N����`�폜