#include "all.h"

VECTOR2 Scene::takeOverPos_ = { 200.0f,500.0f };
VECTOR2 Scene::takeOverScale_ = { 1.0f,1.0f };
bool Scene::takeOverIsDrawShrink_ = false;

//--------------------------------------------------------------
//  ���s
//--------------------------------------------------------------
Scene* Scene::execute()
{
    using namespace GameLib;

    // ����������
    init();

    // �Q�[�����[�v
    while (isGameLoop(false))    // false��true�ɂ���ƃ^�C�g���o�[�Ƀt���[�����[�g�\��
    {
        // ���͏���
        input::update();

        // �X�V����
        update();

        // ���y�X�V
        Audio::update();

        // �X�e���V�����[�h�F�ʏ�
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // �`�揈��
        draw();

        // �X�e���V�����[�h�F�ʏ�
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // �f�o�b�O������̕`��
        debug::display(1, 1, 1, 1, 1);

        // ��ʃt���b�v
        GameLib::present(1, 0);

        // �I���`�F�b�N
        if (nextScene_) break;
    }

    // �I������
    deinit();

    return nextScene_;	// ���̃V�[����Ԃ�
}

//******************************************************************************
//
//      SceneManager�N���X
//
//******************************************************************************

//--------------------------------------------------------------
//  ���s
//--------------------------------------------------------------
void SceneManager::execute(Scene* scene)
{
    using namespace GameLib;

    bool isFullScreen = true;	// �t���X�N���[���ɂ���Ȃ�true�ɕς���
                                //�iRelease���[�h�̂݁j

    // �Q�[�����C�u�����̏���������
    GameLib::init(L"Junk Chunk", BG::WINDOW_W, BG::WINDOW_H, isFullScreen);

#ifndef _DEBUG
    ShowCursor(!isFullScreen);	// �t���X�N���[�����̓J�[�\��������
#endif

    // ���C�����[�v
    while (scene)
    {
        scene = scene->execute();
    }

    // �Q�[�����C�u�����̏I������
    GameLib::uninit();
}

//******************************************************************************
