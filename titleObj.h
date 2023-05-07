#pragma once

class BaseTitleObjBehavior : public Behavior
{
protected:
	struct Param
	{
		// 画像
		//GameLib::AnimeData* ANIME_WAIT = nullptr;
		GameLib::SpriteData* SPR_DETA = nullptr;
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
};

// スタート
class TitleStateObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleStateObjBehavior();
	void hit(OBJ2D*, OBJ2D*) const override;
};
EXTERN TitleStateObjBehavior titleStateObjBehavior;
// エンド
class TitleEndObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleEndObjBehavior();
	void hit(OBJ2D*, OBJ2D*) const override;
};
EXTERN TitleEndObjBehavior titleEndObjBehavior;
// タイトルロゴ
class TitleLogoObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleLogoObjBehavior();
private:
	void init(OBJ2D*) const override;
};
EXTERN TitleLogoObjBehavior titleLogoObjBehavior;
// 操作説明[移動]
class TitleHintMoveObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleHintMoveObjBehavior();
private:
	void init(OBJ2D*) const override;
};
EXTERN TitleHintMoveObjBehavior titleHintMoveObjBehavior;
// 操作説明[攻撃]
class TitleHintShotObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleHintShotObjBehavior();
private:
	void init(OBJ2D*) const override;
};
EXTERN TitleHintShotObjBehavior titleHintShotObjBehavior;