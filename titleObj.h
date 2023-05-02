#pragma once

class BaseTitleObjBehavior : public Behavior
{
protected:
	struct Param
	{
		// �摜
		//GameLib::AnimeData* ANIME_WAIT = nullptr;
		GameLib::SpriteData* SPR_DETA = nullptr;
		// �T�C�Y
		VECTOR2 SIZE = { 0, 0 };
		VECTOR2 SCALE = { 1, 1 };
		VECTOR4 COLOR = { 1,1,1,0 };	// �ŏ������ŏo��
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

// �X�^�[�g
class TitleStateObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleStateObjBehavior();
	void hit(OBJ2D*, OBJ2D*) const override;
};
EXTERN TitleStateObjBehavior titleStateObjBehavior;
// �G���h
class TitleEndObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleEndObjBehavior();
	void hit(OBJ2D*, OBJ2D*) const override;
};
EXTERN TitleEndObjBehavior titleEndObjBehavior;
// �^�C�g�����S
class TitleLogoObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleLogoObjBehavior();
private:
	void init(OBJ2D*) const override;
};
EXTERN TitleLogoObjBehavior titleLogoObjBehavior;