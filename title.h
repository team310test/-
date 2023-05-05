#pragma once

class Title : public Scene
{
private:
	static Title instance_;
	OBJ2DManager* obj2dManager_;
	BG* bg_;

	OBJ2D* player_;
	OBJ2D* startCommand_;
	OBJ2D* endCommand_;
	OBJ2D* titleLoge_;	// すぐに演出始まるので初期値はtrue

	//<追加>
	bool isStartPerform_;
	int pushCount_;
	//bool is
public:
	static Title* instance() { return &instance_; }

	void init() override;
	void deinit() override;
	void update() override;
	void draw() override;

	void judge();

	void changeSceneGame();		// ゲーム画面への遷移処理
	void endGame();				// ゲーム終了処理
	bool statePerform();		// スタート演出

	bool objFadeOut();			// フェードアウト
	bool objFadeIn();			// フェードイン
	bool objShrink();			// obj(player)の縮小

	OBJ2DManager* obj2dManager() { return obj2dManager_; }
	BG* bg() { return bg_; }
private:
	Title()
		:obj2dManager_(nullptr)
		, bg_(nullptr)
		, player_(nullptr)

		//<追加>
		, startCommand_(nullptr)
		, endCommand_(nullptr)
		, titleLoge_(nullptr)
		, isStartPerform_(true)
		, pushCount_(0)
	{
	}
	Title(const Title&) = delete;
};