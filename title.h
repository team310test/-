#pragma once

class Title : public Scene
{
private:
	static Title instance_;
	OBJ2DManager* obj2dManager_;
	BG* bg_;

	OBJ2D* player_;
	OBJ2D* stateCommand_;
	OBJ2D* endCommand_;
	OBJ2D* titleLoge_;	// �����ɉ��o�n�܂�̂ŏ����l��true

	//<�ǉ�>
	bool isStatePerform_;
public:
	static Title* instance() { return &instance_; }

	void init() override;
	void deinit() override;
	void update() override;
	void draw() override;

	void judge();

	void changeSceneGame();		// �Q�[����ʂւ̑J�ڏ���
	void endGame();				// �Q�[���I������
	bool statePerform();		// �X�^�[�g���o

	bool objFadeOut();			// �t�F�[�h�A�E�g
	bool objFadeIn();			// �t�F�[�h�C��

	OBJ2DManager* obj2dManager() { return obj2dManager_; }
	BG* bg() { return bg_; }
private:
	Title()
		:obj2dManager_(nullptr)
		, bg_(nullptr)
		, player_(nullptr)

		//<�ǉ�>
		, stateCommand_(nullptr)
		, endCommand_(nullptr)
		, titleLoge_(nullptr)
		, isStatePerform_(true)
	{
	}
	Title(const Title&) = delete;
};