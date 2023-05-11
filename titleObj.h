#pragma once

class BaseTitleObjBehavior : public Behavior
{
protected:
	struct Param
	{
		// �摜
		//GameLib::AnimeData* ANIME_WAIT = nullptr;
		GameLib::SpriteData* SPR_DATA = nullptr;
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

protected:
	virtual void update(OBJ2D*) const {}; // �S�~���摜�X�V�̂��߂ɒǉ�
};

// �X�^�[�g
class TitleStartObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleStartObjBehavior();
	void hit(OBJ2D*, OBJ2D*) const override;

private:
	void update(OBJ2D* obj) const override; // �摜�X�V�p
};
EXTERN TitleStartObjBehavior titleStartObjBehavior;

// �G���h
class TitleEndObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleEndObjBehavior();
	void hit(OBJ2D*, OBJ2D*) const override;

private:
	void update(OBJ2D* obj) const override;
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

// �������[�ړ�]
class TitleHintMoveObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleHintMoveObjBehavior();
private:
	void init(OBJ2D*) const override;
};
EXTERN TitleHintMoveObjBehavior titleHintMoveObjBehavior;

// �������[�U��]
class TitleHintShotObjBehavior :public BaseTitleObjBehavior
{
public:
	TitleHintShotObjBehavior();
private:
	void init(OBJ2D*) const override;
};
EXTERN TitleHintShotObjBehavior titleHintShotObjBehavior;


//******************************************************************************
// 
//      TitlePlayer�i�^�C�g���p�̎��@)
// 
//******************************************************************************
OBJ2D* setTitlePlayer(OBJ2DManager* obj2dManager, BG* bg);

// �n�[�g�̂�
class TitlePlayerCoreHeartBehavior : public BasePlayerBehavior
{
public:
	TitlePlayerCoreHeartBehavior();
	void areaCheck(OBJ2D*) const override;
};
EXTERN TitlePlayerCoreHeartBehavior titlePlayerHeartBehavior;

// �R�A
class TitlePlayerCoreBehavior : public BasePlayerBehavior
{
public:
	TitlePlayerCoreBehavior();
};
EXTERN TitlePlayerCoreBehavior titlePlayerCoreBehavior;