#pragma once

class BaseTitleObjBehavior : public Behavior
{
protected:
	struct Param
	{
		// 画像
		GameLib::SpriteData* SPR_DATA = nullptr;
		// アニメーション
		GameLib::AnimeData* ANIME = nullptr;
		// サイズ
		VECTOR2 SIZE = { 0, 0 };
		VECTOR2 SCALE = { 1, 1 };
		VECTOR4 COLOR = { 1,1,1,0 };	// 最初透明で出現
		GameLib::fRECT HIT_BOX[Collider::boxMax] = {};
		GameLib::fRECT ATTACK_BOX[Collider::boxMax] = {};
		int BOX_NUM = 1;
	} param_;

	const Param* getParam() const { return &param_; }

public:
	void move(OBJ2D* obj) const override;
	OBJ_TYPE getType() const override { return OBJ_TYPE::NONE; }
	OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; }

private:
	virtual void init(OBJ2D*) const;

protected:
	virtual void update(OBJ2D*) const {}; // ゴミ箱画像更新のために追加
};

// スタート
class TitleStartObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleStartObjBehavior();
	void hit(OBJ2D*, OBJ2D*) const override;

private:
	void update(OBJ2D* obj) const override; // 画像更新用
};
EXTERN TitleStartObjBehavior titleStartObjBehavior;

// エンド
class TitleEndObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleEndObjBehavior();
	void hit(OBJ2D*, OBJ2D*) const override;

private:
	void update(OBJ2D* obj) const override;
};
EXTERN TitleEndObjBehavior titleEndObjBehavior;

// タイトルロゴ
class TitleLogoObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleLogoObjBehavior();
private:
	void init(OBJ2D*) const override;
	void update(OBJ2D* obj) const override;
};
EXTERN TitleLogoObjBehavior titleLogoObjBehavior;

// 操作説明[移動](キーボード)
class TitleHintKeyboardMoveObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleHintKeyboardMoveObjBehavior();
private:
	void init(OBJ2D*) const override;
};
EXTERN TitleHintKeyboardMoveObjBehavior titleHintKeyboardMoveObjBehavior;

// 操作説明[移動](コントローラー)
class TitleHintControllerMoveObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleHintControllerMoveObjBehavior();
private:
	void init(OBJ2D*) const override;
};
EXTERN TitleHintControllerMoveObjBehavior titleHintControllerMoveObjBehavior;

// 操作説明[攻撃](キーボード)
class TitleHintKeyboardShotObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleHintKeyboardShotObjBehavior();
private:
	void init(OBJ2D*) const override;
};
EXTERN TitleHintKeyboardShotObjBehavior titleHintKeyboardShotObjBehavior;

// 操作説明[攻撃](コントローラー)
class TitleHintControllerShotObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleHintControllerShotObjBehavior();
private:
	void init(OBJ2D*) const override;
};
EXTERN TitleHintControllerShotObjBehavior titleHintControllerShotObjBehavior;

// 操作説明[長押し]
class TitleHintHoldObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleHintHoldObjBehavior();
private:
	void init(OBJ2D*) const override;
};
EXTERN TitleHintHoldObjBehavior titleHintHoldObjBehavior;


//******************************************************************************
// 
//      TitlePlayer（タイトル用の自機)
// 
//******************************************************************************
OBJ2D* setTitlePlayer(OBJ2DManager* obj2dManager, BG* bg);

// ハートのみ
class TitlePlayerCoreHeartBehavior : public BasePlayerBehavior
{
public:
	TitlePlayerCoreHeartBehavior();
	void areaCheck(OBJ2D*) const override;
};
EXTERN TitlePlayerCoreHeartBehavior titlePlayerHeartBehavior;

// コア
class TitlePlayerCoreBehavior : public BasePlayerBehavior
{
public:
	TitlePlayerCoreBehavior();
};
EXTERN TitlePlayerCoreBehavior titlePlayerCoreBehavior;