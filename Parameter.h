#pragma once

// �g�p����p�����[�^�ݒ�t�@�C���i.txt�j
#define USE_TEXT_FILE "./Parameter(�������ɏ���).txt"


#ifdef USE_TEXT_FILE // �J�����Ɏg����

#include USE_TEXT_FILE 

#else // �������Ɏg����(�p�����[�^�ݒ�t�@�C���̒��g���ڂ�)
                  
// ���@�{��
//#define CORE_PLAYER_HP  (1000)
//#define CORE_PLAYER_ATK (1)


#endif 

#undef DEBUG_MODE           // �}�N����`�폜