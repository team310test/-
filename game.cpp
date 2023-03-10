//******************************************************************************
//
//
//      �Q�[��
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �ϐ� >----------------------------------------------------------------
Game Game::instance_;

//--------------------------------
//  ����������
//--------------------------------
void Game::init()
{
    Scene::init();	    // ���N���X��init���Ă�

    playerManager_      = new PlayerManager;

    isPaused = false;   // �|�[�Y�t���O�̏�����
}

//--------------------------------
//  �I������
//--------------------------------
void Game::deinit()
{
    // �e�}�l�[�W���̉��
    safe_delete(playerManager_);

    // �e�N�X�`���̉��
    texture::releaseAll();

    // ���y�̃N���A
    music::clear();
}

//--------------------------------
//  �X�V����
//--------------------------------
void Game::update()
{
    using namespace input;

    // �\�t�g���Z�b�g
    if ((STATE(0) & PAD_SELECT) &&  // 0�R���̃Z���N�g�{�^����������Ă����Ԃ�
        (TRG(0) & PAD_START))       // 0�R���̃X�^�[�g�{�^���������ꂽ�u��
    {
        changeScene(Title::instance());   // �^�C�g���V�[���ɐ؂�ւ���
        return;
    }

    // �f�o�b�O������\��
    debug::setString("state:%d", state);
    debug::setString("timer:%d", timer);

    // �|�[�Y����
    if (TRG(0) & PAD_START)
        isPaused = !isPaused;       // 0�R���̃X�^�[�g�{�^���������ꂽ��|�[�Y��Ԃ����]
    if (isPaused) return;           // ���̎��_�Ń|�[�Y���Ȃ烊�^�[��

    switch (state)
    {
    case 0:
        //////// �����ݒ� ////////

        timer = 0;
        GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        texture::load(loadTexture);

        // �v���C���[�}�l�[�W���̏�����
        playerManager()->init();

        // �v���C���[�i�����ő���j��ǉ�����
        playerManager()->add(&player, VECTOR2(window::getWidth() / 2, window::getHeight() / 2));

        state++;    // �����������̏I��

        /*fallthrough*/     // case 1:�̏����������ɍs���K�v�����邽�߁A�킴��break;���L�q���Ă��Ȃ�

    case 1:
        //////// �ʏ펞�̏��� ////////

        timer++;

        // �v���C���[�̍X�V
        playerManager()->update();

        break;
    }
}

//--------------------------------
//  �`�揈��
//--------------------------------
void Game::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0, 0, 0, 1));

#if 2
    //******************************************************************************
    // TODO:02 �n�ʂ̕`��
    //------------------------------------------------------------------------------
    /*
    �ۑ�j
        �n�ʂ�`�悵�Ȃ���

    �q���g�j
        0, GROUND_POS_Y����A�� window::getWidth()�A���� window::getHeight() - GROUND_POS_Y��
        ��`��`�悵�Ȃ����B�F�͔w�i�F�ȊO�ł���΁A���F�ł��ǂ��B
    */
    //******************************************************************************
#endif

    const VECTOR2 pos{ 0,Game::GROUND_POS_Y };
    const VECTOR2 size{ window::getWidth(), window::getHeight() - GROUND_POS_Y };
    const VECTOR2 pivot{ 0.0f,0.0f };
    const VECTOR4 color{ 0.0f, 1.0f, 0.0f, 1.0f };

    //TODO_02 �n�ʂ̕`��
    primitive::rect(pos, size,pivot, 0, color);

    // �v���C���[�̕`��
    playerManager()->draw();
}

//******************************************************************************
