//******************************************************************************
// 
//      �Q�[���p��obj
// 
//******************************************************************************
// BaseGameObjBehavior
class BaseGameObjBehavior : public Behavior
{
protected:
	struct Param
	{
		// �摜
		//GameLib::AnimeData* ANIME_WAIT = nullptr;
		GameLib::SpriteData* SPR_DATA = nullptr;
		// �T�C�Y
		VECTOR2 SIZE = { 1, 1 };
		VECTOR2 SCALE = { 1, 1 };
		VECTOR4 COLOR = { 1,1,1,1 };
		GameLib::fRECT HIT_BOX[Collider::boxMax] = {};
		GameLib::fRECT ATTACK_BOX[Collider::boxMax] = {};
		int BOX_NUM = 1;
	} param_;
	const Param* getParam() const { return &param_; }

	virtual void updateQuake(OBJ2D*) const {};

public:
	void move(OBJ2D* obj) const override;
	OBJ_TYPE getType() const override { return OBJ_TYPE::NONE; }
	OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; }
private:
	virtual void init(OBJ2D*) const;
};

// player�̘g
class GamePlayerFrameObjBehavior :public BaseGameObjBehavior
{
public:
	GamePlayerFrameObjBehavior();
};
EXTERN GamePlayerFrameObjBehavior gamePlayerFrameObjBehavior;


//******************************************************************************
// 
//      Game(Over)Player�i�^�C�g���p�̎��@)
// 
//******************************************************************************

// player�̃n�[�g
class GamePlayerHheartObjBehavior : public BasePlayerBehavior
{
public:
	GamePlayerHheartObjBehavior();
	void init(OBJ2D* obj) const override;
	void areaCheck(OBJ2D*) const override;
};
EXTERN GamePlayerHheartObjBehavior gamePlayerHeartObjBehavior;



 // �x�[�X���U���g�e�L�X�g
class BaseGameResultText : public BaseGameObjBehavior
{
public:
	BaseGameResultText();
private:
	void updateQuake(OBJ2D* obj) const override;
};
EXTERN BaseGameResultText baseGameResultText;