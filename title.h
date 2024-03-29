#pragma once

class Title : public Scene
{
private:
	static Title instance_;
	OBJ2DManager* obj2dManager_;
	BG* bg_;

	//<追加>
	OBJ2D* player_;
	OBJ2D* startCommand_;
	OBJ2D* endCommand_;
	OBJ2D* titleLogo_;	// すぐに演出始まるので初期値はtrue
	OBJ2D* userHintMove_; // 移動方法
	OBJ2D* userHintShot_;	// 攻撃方法


	bool isStartPerform_;
	bool isPlayerMove_;
	int isPlayerShotState_;
	int oldTimer_;

	int pushCount_ = 0;
	//bool is

public:
	bool isDispTextStart_;		// Startテキストを表示させるか
	bool isDispTextExit_;		// Exitテキストを表示させるか
	float textStartColorAlpha_; // Start不透明度
	float textExitColorAlpha_;  // Exit不透明度
			  
public:
	static Title* instance() { return &instance_; }

	void init() override;
	void deinit() override;
	void update() override;
	void draw() override;

	void judge();

	void changeSceneGame();		// ゲーム画面への遷移処理
	void endGame();				// ゲーム終了処理
	bool startPerform();		// スタート演出

	void userHintMove();		// プレイヤーへのヒント
	void userHintShot();		// プレイヤーへのヒント

	OBJ2DManager* obj2dManager() { return obj2dManager_; }
	BG* bg() { return bg_; }

	OBJ2D* player() { return player_; };

private:
	Title()
		:obj2dManager_(nullptr)
		, bg_(nullptr)
		, player_(nullptr)

		//<追加>
		, startCommand_(nullptr)
		, endCommand_(nullptr)
		, titleLogo_(nullptr)
		, userHintMove_(nullptr)
		, userHintShot_(nullptr)
		, isStartPerform_(true)
		, isPlayerMove_(false)
		, isPlayerShotState_()	
		, oldTimer_(0)
		, pushCount_(0)
		, isDispTextStart_(false)
		, isDispTextExit_(false)
		, textStartColorAlpha_(0.0f)
		, textExitColorAlpha_(0.0f)
	{
	}
	Title(const Title&) = delete;
};