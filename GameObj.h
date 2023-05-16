//******************************************************************************
// 
//      ゲーム用のobj
// 
//******************************************************************************
// BaseGameObjBehavior
class BaseGameObjBehavior : public Behavior
{
protected:
	struct Param
	{
		// 画像
		//GameLib::AnimeData* ANIME_WAIT = nullptr;
		GameLib::SpriteData* SPR_DATA = nullptr;
		// サイズ
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

// playerの枠
class GamePlayerFrameObjBehavior :public BaseGameObjBehavior
{
public:
	GamePlayerFrameObjBehavior();
};
EXTERN GamePlayerFrameObjBehavior gamePlayerFrameObjBehavior;


//******************************************************************************
// 
//      Game(Over)Player（タイトル用の自機)
// 
//******************************************************************************

// playerのハート
class GamePlayerHheartObjBehavior : public BasePlayerBehavior
{
public:
	GamePlayerHheartObjBehavior();
	void init(OBJ2D* obj) const override;
	void areaCheck(OBJ2D*) const override;
};
EXTERN GamePlayerHheartObjBehavior gamePlayerHeartObjBehavior;



 // ベースリザルトテキスト
class BaseGameResultText : public BaseGameObjBehavior
{
public:
	BaseGameResultText();
private:
	void updateQuake(OBJ2D* obj) const override;
};
EXTERN BaseGameResultText baseGameResultText;