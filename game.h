#ifndef INCLUDED_GAME
#define	INCLUDED_GAME

//******************************************************************************
//
//
//      �Q�[���V�[��
//
//
//******************************************************************************

//==============================================================================
//
//      Game�N���X
//
//==============================================================================

class Game : public Scene
{
public:
    // �N���X���ł̒萔�̒�`�̎d��
    // int�^�ł����const�ŗǂ����A����ȊO��constexpr���g�p����
    static constexpr float GROUND_POS_Y = 640.0f;

public:
    static Game* instance() { return &instance_; }

    void init();
    void deinit();
    void update();
    void draw();

    // �Q�b�^�[�͌���_�����Ȃ�
    PlayerManager*      playerManager()     { return playerManager_; }

private:
    bool                isPaused;

    // �����o�ϐ��͌���_������
    PlayerManager*      playerManager_;

    static Game instance_;
};

//******************************************************************************

#endif // !INCLUDED_GAME
