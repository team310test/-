#pragma once

class Title : public Scene
{
private:
	static Title instance_;
	OBJ2DManager* obj2dManager_;
	BG* bg_;
	static bool isFallPerform_;

public:
	static Title* instance() { return &instance_; }

	void init() override;
	void deinit() override;
	void update() override;
	void draw() override;

	void judge();

	OBJ2DManager* obj2dManager() { return obj2dManager_; }
	BG* bg() { return bg_; }
private:
	Title()
		:obj2dManager_(nullptr)
		, bg_(nullptr)
	{
		isFallPerform_ = false;
	}
	Title(const Title&) = delete;
};