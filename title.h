#pragma once

class Title : public Scene
{
private:
	static Title instance_;
	OBJ2DManager* obj2dManager_;
	BG* bg_;

	//<�ǉ�>
	OBJ2D* player_;
	OBJ2D* startCommand_;
	OBJ2D* endCommand_;
	OBJ2D* titleLogo_;	// �����ɉ��o�n�܂�̂ŏ����l��true
	OBJ2D* userHintMove_; // �ړ����@
	OBJ2D* userHintShot_;	// �U�����@


	bool isStartPerform_;
	bool isPlayerMove_;
	bool isPlayerShot_;
	int oldTimer_;

	int pushCount_ = 0;
	//bool is
public:
	static Title* instance() { return &instance_; }

	void init() override;
	void deinit() override;
	void update() override;
	void draw() override;

	void judge();

	void changeSceneGame();		// �Q�[����ʂւ̑J�ڏ���
	void endGame();				// �Q�[���I������
	bool startPerform();		// �X�^�[�g���o

	void userHintMove();		// �v���C���[�ւ̃q���g
	void userHintShot();		// �v���C���[�ւ̃q���g

	OBJ2DManager* obj2dManager() { return obj2dManager_; }
	BG* bg() { return bg_; }

	OBJ2D* player() { return player_; };

private:
	Title()
		:obj2dManager_(nullptr)
		, bg_(nullptr)
		, player_(nullptr)

		//<�ǉ�>
		, startCommand_(nullptr)
		, endCommand_(nullptr)
		, titleLogo_(nullptr)
		, userHintMove_(nullptr)
		, userHintShot_(nullptr)
		, isStartPerform_(true)
		, isPlayerMove_(false)
		, isPlayerShot_(false)	
		, oldTimer_(0)
		, pushCount_(0)
	{
	}
	Title(const Title&) = delete;
};