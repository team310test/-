#pragma once

class Scene
{
protected:
    int state_ = 0;              // ���
    int timer_ = 0;              // �^�C�}�[
    Scene* nextScene_ = nullptr; // ���̃V�[��

    // �V�[���؂�ւ�������p���ϐ�
    static VECTOR2 takeOverPos_;            
    static VECTOR2 takeOverScale_;          
    static bool takeOverIsDrawShrink_;

    // �Q�[�����[�v�֐��|�C���^
    bool (*isGameLoop)(bool) = GameLib::gameLoop;

public:
    Scene* execute();   // ���s����
    

    virtual void init()
    { // ����������
        state_ = 0;
        timer_ = 0;
        nextScene_ = nullptr;
    };
    virtual void deinit() {};   // �I������
    virtual void update() = 0;  // �X�V����
    virtual void draw() = 0;    // �`�揈��

    void changeScene(Scene *scene) { nextScene_ = scene; }   // �V�[���ύX����
    Scene *getScene() const { return nextScene_; }           // nextScene�̃Q�b�^�[
};

//******************************************************************************
//
//
//      �V�[���Ǘ�
//
//
//******************************************************************************
class SceneManager
{
public:
    void execute(Scene*);  // ���s����
};

//******************************************************************************

