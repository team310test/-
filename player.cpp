//******************************************************************************
//
//
//      �v���C���[�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >--------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//******************************************************************************
//
//      �v���C���[�ړ�����
//
//******************************************************************************

//------< �v���C���[�̃A�j���f�[�^ >--------------------------------------------
namespace
{   // �����̃f�[�^�͒����̂ŁAVisual Studio�̋@�\�ŕ�����悤��namespace�𕪂��Ă���

    //------< �v���C���[�̃A�j���f�[�^ >------------------------------------------
    //�����
    AnimeData animePlayer_Up[] = {
        { &sprPlayer_Up0, 10 },
        { &sprPlayer_Up1, 10 },
        { &sprPlayer_Up2, 10 },
        { &sprPlayer_Up1, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //�E����
    AnimeData animePlayer_Right[] = {
        { &sprPlayer_Right0, 10 },
        { &sprPlayer_Right1, 10 },
        { &sprPlayer_Right2, 10 },
        { &sprPlayer_Right1, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //������
    AnimeData animePlayer_Down[] = {
        { &sprPlayer_Down0, 10 },
        { &sprPlayer_Down1, 10 },
        { &sprPlayer_Down2, 10 },
        { &sprPlayer_Down1, 10 },
        { nullptr, -1 },// �I���t���O
    };
    //������
    AnimeData animePlayer_Left[] = {
        { &sprPlayer_Left0, 10 },
        { &sprPlayer_Left1, 10 },
        { &sprPlayer_Left2, 10 },
        { &sprPlayer_Left1, 10 },
        { nullptr, -1 },// �I���t���O
    };
}

//--------------------------------
//  ���ڑ���
//--------------------------------
void Player::move(OBJ2D *obj)
{
    using namespace input;  // �֐����œ��͏������s���Ƃ��ɋL�q����

    // �萔�i�����͂��̊֐����ł����g�p���Ȃ����߁A�����Œ�`���Ă���j
    const float KASOKU          =  1.0f;    // �������E�c�����̉����x
    const float GENSOKU = KASOKU * 0.5f;    // �������E�c�����̌����x
    const float SPEED_MAX_X     =  8.0f;    // �������̍ő呬�x
    const float SPEED_MAX_Y     =  16.0f;   // �ő�̗������x
    const float SPEED_JUMP_Y    = -12.0f;   // �W�����v���̏㏸�X�s�[�h

    // �ϐ�
    AnimeData* animeData = nullptr;
    bool onGround = false;          // �n��t���O

    switch (obj->state)
    {
    case 0:
        //////// �����ݒ� ////////

        //�A�j���̏����ݒ�
        animeData = animePlayer_Down;   // �����l�Ƃ��ĉ������̃A�j����ݒ肷��

        // �T�C�Y�ݒ�i���������S�ł��邽�߁A���͂�����Ƃ��Ďg�p���锼���E�c�͂��̂܂܂������₷���j
        obj->size = VECTOR2(96 / 2, 128 - 2);

        obj->state++;

        break;

    case 1:
        //////// �ʏ펞 ////////

        // ���t���[�����̏����ݒ�
        onGround = false;   // �n�ʃt���O�͖��t���[���̍ŏ���false�ɂ��Ă����A�n�ʂɐڂ��Ă�����true��ݒ肷��
#if 1
//******************************************************************************
// TODO:01 �v���C���[�̈ړ��iY�����j
//------------------------------------------------------------------------------
/*
�ۑ�j
    �v���C���[�̏c�����̓�����������Ȃ���

�d�l�j
    �ʒu��obj->position�ł���
    ���x��obj->speed�ł���
    �c�����̉����x�� KASOKU�ł���

    �������x�� SPEED_MAX_Y �𒴂��Ȃ�
    �n�ʂ̍����� Game::GROUND_POS_Y

�q���g�j
    ���L�̎菇�ōs���Ƃ悢�i���̐ݖ�̏㉺�̕������m�F���Ă�����g�ނ��Ɓj

    �� ���x�ɉ����x��������
    �� �ő呬�x�`�F�b�N
    �� Y�����̈ʒu�X�V�iY�����̈ʒu��Y�����̑��x��������j
    �� Y�����n�`�����蔻��

����j
    ��̏����ƃq���g���悭�ǂݗ������āA����������g�����B
    Y�����n�`�����蔻��ɂ��ẮAobj->position.y�� Game::GROUND_POS_Y �𒴂�����
    obj->position.y�� Game::GROUND_POS_Y ��������
*/
//******************************************************************************
#endif
        //���x�ɉ����x��������
        obj->speed.y += KASOKU;

        //�ō����x�`�F�b�N
        obj->speed.y=(std::min)(obj->speed.y, SPEED_MAX_Y);
        //if (obj->speed.y > SPEED_MAX_Y) {
        //    obj->speed.y = SPEED_MAX_Y;
        //}

        //Y�������̈ʒu
        obj->position.y += obj->speed.y;

        //�n�ʂƂ̓����蔻��
        if (obj->position.y > Game::GROUND_POS_Y) {
            obj->position.y = Game::GROUND_POS_Y;
            onGround = true;
        }

#if 3
//******************************************************************************
// TODO:03 �v���C���[�̈ړ��iX�����j
//------------------------------------------------------------------------------
/*
�ۑ�j
    �v���C���[�̉������̓�����������Ȃ���

�d�l�j
    ���E�����ɃL�[�������Ă��A�ǂ���ɂ��i�܂Ȃ��i���͎��o�������͊��ɑg��ł���̂ňӖ����l���Ȃ����j
    �L�[���������u�Ԃɍō����x�œ����̂ł͂Ȃ��A�������ɂ������x�������悤�ɑg��
    �������̉����x��KASOKU
    ���x��SPEED_MAX_X�𒴂��Ȃ�
    ���͂��Ȃ��ꍇ�A���E�ő��E���Ă���ꍇ�͑��x��������x�̔��������炵�A�~�܂낤�Ƃ���
    ���E�̃A�j����ݒ肷��

�q���g�j
    ���L�̎菇�ōs���Ƃ悢�i���̐ݖ�̏㉺�̕������m�F���Ă�����g�ނ��Ɓj

    �� ���E���͂̎��o��
        �� ��������������Ă���ꍇ
            �� ���x�ɍ������̉����x��������i�����x�������j
            �� �������̃A�j����ݒ肷��
        �� �E������������Ă���ꍇ
            �� ���x�ɉE�����̉����x��������i�����x�𑫂��j
            �� �E�����̃A�j����ݒ肷��
        �� �ǂ����������Ă��Ȃ������E����Ă���ꍇ
            �� ���x��0���傫���ꍇ
                �� ���x��������x�̔����������i�~�܂낤�Ƃ���j
                �� ���x�����ɂȂ�����0�ɂ���
            �� ���x��0��菬�����ꍇ
                �� ���x�ɉ����x�̔����𑫂��i�~�܂낤�Ƃ���j
                �� ���x�����ɂȂ�����0�ɂ���
    �� �ő呬�x�`�F�b�N
    �� �ʒu�X�V�i�ʒu�ɑ��x��������j

����j
    ���E���͂̎��o����switch���̕ϐ���STATE(0) & (PAD_LEFT | PAD_RIGHT)�Ƃ���̂�
    �Ӗ����悭�l���Ă݂悤�B����2�s���R�s�[���Ē����ɓ\��A���s���Ă݂Ȃ���

    debug::setString("STATE(0) ALL:%s", strBit16(STATE(0)).c_str());
    debug::setString("STATE(0) LR :%s", strBit16(STATE(0) & (PAD_LEFT | PAD_RIGHT)).c_str());

    STATE(0)��0�R���̓��͏󋵂�\���Ă���BSTATE(0)��0�R���̏�Ԃ�Ԃ��֐��ŁA�߂�l��
    int�^�A�܂�32�r�b�g�̕ϐ��ł��邪�A16�r�b�g�����g�p���Ă��Ȃ��B
    PAD_UP�Ȃǂ́Ainput_manager.h�̐擪�Œ�`���Ă��邪�A(1 << 0)����(1 << 15)�܂ł�
    16�r�b�g���̂ݎg�p���Ă��邱�Ƃ��킩��B

    strBit16��user.h�ɒ�`���Ă���C�����C���֐��ŁA������2�i���i16bit�j��string�ւ�
    �ϊ�����Bdebug::setString�̈�����const char*�Ȃ̂ŁAc_str()���\�b�h��string�^����
    char *�ɕϊ����Ă���B
*/
//******************************************************************************
#endif
        debug::setString("STATE(0) ALL:%s", strBit16(STATE(0)).c_str());
        debug::setString("STATE(0) LR :%s", strBit16(STATE(0) & (PAD_LEFT | PAD_RIGHT)).c_str());

        //TODO_03 ���E���͂̎��o��
        switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
        {
        case PAD_LEFT:  // ��������������Ă���ꍇ
            //���x�ɉ����x��������
            obj->speed.x -= KASOKU;
            //�A�j����ݒ�    
            animeData = animePlayer_Left;
            break;
        case PAD_RIGHT: // �E������������Ă���ꍇ
            obj->speed.x += KASOKU;
            animeData = animePlayer_Right;
            break;
        default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
            //X�����̑��x��0���傫���ꍇ
            if (obj->speed.x > 0) {
                //X�����̑��x��������x�̔����������i�~�܂낤�Ƃ���j
                obj->speed.x -= GENSOKU;
                //0��菬�����Ȃ����� 
                obj->speed.x = (std::max)(obj->speed.x, 0.0f);
                //0��菬�����Ȃ�����
                //if (obj->speed.x < 0) {
                //    //���x��0�ɖ߂�
                //    obj->speed.x = 0;
                //}
            }
            //X�����̑��x��0��菬�����Ƃ�   
            if (obj->speed.x < 0) {
                //X�����̑��x��������x�̔����������i�~�܂낤�Ƃ���j
                obj->speed.x += GENSOKU;
                //0��菬�����Ȃ����� 
                obj->speed.x = (std::min)(obj->speed.x, 0.0f);
                //0���傫���Ȃ�����
                //if (obj->speed.x > 0) {
                //    //���x��0�ɖ߂�
                //    obj->speed.x = 0;
                //}
            }


            break;
        }

        //TODO_03 �ő呬�x�`�F�b�N
        obj->speed.x = clanp(obj->speed.x, SPEED_MAX_X ,-SPEED_MAX_X);
        //if (obj->speed.x > SPEED_MAX_X) {
        //    //��������ő�l�ɖ߂�
        //    obj->speed.x = SPEED_MAX_X;
        //}
        //if (obj->speed.x < -SPEED_MAX_X) {
        //    //��������ő�l�ɖ߂�
        //    obj->speed.x = -SPEED_MAX_X;
        //}

        //TODO_03 X�����ړ�
        obj->position.x += obj->speed.x;

#if 4
//******************************************************************************
// TODO:04 �W�����v����
//------------------------------------------------------------------------------
/*
�ۑ�j
    �v���C���[�̃W�����v�������������Ȃ���

�d�l�j
    obj->jumpTimer�F�W�����v�^�C�}�[�i���Ƃǂꂮ�炢�㏸���������邩�A0���傫�����l�������Ă��鎞�̓W�����v�㏸���ł���j
    onGround      �F�n�ʃt���O�i�n�ʂ̏�ɂ���ꍇ�Ftrue�A�W�����v���̏ꍇ�Ffalse�j

    �n�ʂɂ���PAD_TRG1�������ꂽ�u�ԁA�W�����v�^�C�}�[�ɐ��l��ݒ肷��i20�j
    �W�����v���APAD_TRG1��������i�����j�Ă���΁Ay�����̑��x��SPEED_JUMP_Y��ݒ肵�A�W�����v�^�C�}�[�����炷
    PAD_TRG1��������Ă��Ȃ���΁A�W�����v�^�C�}�[��0�ɂ���i�������炻��ȏ�㏸�ł��Ȃ��j

    ��TODO_01��Y�����n�`������ŁA�n�ʂɂ߂荞��ł��č��W��ύX����������onGround��true�ɂ��Ă������Ɓi�d�v�j

�菇�j
    �� �v���C���[���n�ʂɂ��āA0�R����PAD_TRG1�������ꂽ�u�ԂȂ�
        �� �W�����v�^�C�}�[�ɐ��l��ݒ肷��i20�j
    �� �W�����v�^�C�}�[�̐��l��0���傫�����
        �� 0�R����PAD_TRG1��������Ă����ԂȂ�
            �� y�����̑��x��SPEED_JUMP_Y
            �� �W�����v�^�C�}�[��1���炷
        �� �����łȂ��Ȃ�
            �� �W�����v�^�C�}�[��0�ɂ���

�q���g�j
    ���L���R�s�[���ă\�[�X�ɓ\��A������m�F���邱��
    debug::setString("onGround:%d", onGround);
    debug::setString("jumpTimer:%d", obj->jumpTimer);
*/
//******************************************************************************
#endif
        //TODO_04 �W�����v�`�F�b�N
        
        //�f�o�b�O
        debug::setString("onGround:%d", onGround);
        debug::setString("jumpTimer:%d", obj->jumpTimer);

        //�v���C���[���n��ɂ��ăL�[�������ꂽ�Ƃ�
        if (onGround && TRG(0) & PAD_TRG1) {
            obj->jumpTimer = 20;
        }

        //TODO_04 �W�����v��
         
        //�W�����v�^�C�}�[��0�ȏ�̎�
        if (obj->jumpTimer > 0) {
            //�L�[��������Ă����
            if (STATE(0) & PAD_TRG1) {
                //Y�����̑��x��SPEED_JUMP_Y��
                obj->speed.y = SPEED_JUMP_Y;
                //jumpTimer��1���炷
                obj->jumpTimer--;
            }
            //�����łȂ��Ȃ�
            else {
                obj->jumpTimer = 0;
            }
        }

#if 5
//******************************************************************************
// TODO:05 �G���A�`�F�b�N�i���E�����j
//------------------------------------------------------------------------------
/*
�ۑ�j
    �v���C���[����ʂ��獶�E�ɂ͂ݏo���Ȃ��悤�ɂ��Ȃ����B

�q���g�j
    �v���C���[����ʂ̈�ԍ��ɂ��鎞�̍��W�́H
    �v���C���[����ʂ̈�ԉE�ɂ��鎞�̍��W�́H
    obj->position.x�������𒴂�����A���̒l��������
    ����͕ǂɓ��������Ƃ������ƂȂ̂ŁAobj->speed.x��0�ɂ���

����j
    �v���C���[����ʂ̈�ԍ��ɂ��鎞�̍��W�́A0 + obj->size.x
    �v���C���[����ʂ̈�ԉE�ɂ��鎞�̍��W�́Awindow::getWidth() - obj->size.x
*/
//******************************************************************************
#endif
        //TODO_05 �G���A�`�F�b�N

        const float LEFT_END = window::getWidth() - obj->size.x;
        const float RIGHT_END = 0 + obj->size.x;
        
        //�v���C���[�����[
        if (obj->position.x < RIGHT_END) {
            //0�ɖ߂�
            obj->position.x = RIGHT_END;
            //���x��0�ɖ߂�
            obj->speed.x = 0;
        }
        //�v���C���[�����[
        if (obj->position.x > LEFT_END) {
            obj->position.x = LEFT_END;
            //���x��0�ɖ߂�
            obj->speed.x = 0;
        }

        break;
    }

    // �A�j���[�V�����X�V
    if (animeData)
    {
        // animeData�ɒl�������Ă���΁Aobj->animeUpdate���\�b�h���Ă�
        obj->animeUpdate(animeData);
    }
}

//--------------------------------
//  ����
//--------------------------------
void ErasePlayer::erase(OBJ2D* obj)
{
    obj->clear();           // OBJ2D����������
}
