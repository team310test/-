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
		GameLib::SpriteData* SPR_DATA  = nullptr;
		GameLib::AnimeData* ANIME_DATA = nullptr;
		// サイズ
		VECTOR2 SIZE = { 1, 1 };
		VECTOR2 SCALE = { 1, 1 };
		VECTOR4 COLOR = { 1,1,1,1 };
		GameLib::fRECT HIT_BOX[Collider::boxMax] = {};
		GameLib::fRECT ATTACK_BOX[Collider::boxMax] = {};
		int BOX_NUM = 1;
	} param_;
	const Param* getParam() const { return &param_; }

	virtual void update(OBJ2D*) const {};

public:
	void move(OBJ2D* obj) const override;
	OBJ_TYPE getType() const override { return OBJ_TYPE::NONE; }
	OBJ_TYPE getAttackType() const override { return OBJ_TYPE::PLAYER; }
protected:
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



// Back
class GameResult_Back : public BaseGameObjBehavior
{
public: 
	GameResult_Back();
private:
	void update(OBJ2D* obj) const override; // アニメーション処理
};
EXTERN GameResult_Back gameResult_back;


// ベースリザルト
class BaseGameResult : public BaseGameObjBehavior
{
public:
	BaseGameResult() {}
protected:
	void update(OBJ2D* obj) const override; // 揺れる更新処理
};

// Junks
class GameResult_Junks : public BaseGameResult
{
public: GameResult_Junks();
};
EXTERN GameResult_Junks gameResult_junks;

// Times
class GameResult_Times : public BaseGameResult
{
public: GameResult_Times();
};
EXTERN GameResult_Times gameResult_times;

// Rank
class GameResult_Rank : public BaseGameResult
{
public: GameResult_Rank();
};
EXTERN GameResult_Rank gameResult_rank;


// Text_Junkie
class GameResult_Text_Junkie : public BaseGameResult
{
public: 
	GameResult_Text_Junkie();
private:
	void init(OBJ2D* obj) const override;
};
EXTERN GameResult_Text_Junkie gameResult_text_junkie;

// Text_Great
class GameResult_Text_Great : public BaseGameResult
{
public:
	GameResult_Text_Great();
private:
	void init(OBJ2D* obj) const override;
};
EXTERN GameResult_Text_Great gameResult_text_great;

// Text_Nice
class GameResult_Text_Nice : public BaseGameResult
{
public: 
	GameResult_Text_Nice();
private:
	void init(OBJ2D* obj) const override;
};
EXTERN GameResult_Text_Nice gameResult_text_nice;

// Text_Soso
class GameResult_Text_Soso : public BaseGameResult
{
public: 
	GameResult_Text_Soso();
private:
	void init(OBJ2D* obj) const override;
};
EXTERN GameResult_Text_Soso gameResult_text_soso;


// AnyPush
class GameResult_AnyPush : public BaseGameResult
{
public: 
	GameResult_AnyPush();
private:
	void init(OBJ2D* obj) const override;
	void update(OBJ2D* obj) const override; // 点滅更新
};
EXTERN GameResult_AnyPush gameResult_anyPush;


// S・A・B・C
class GameResult_S : public BaseGameResult
{
public: GameResult_S();
};
EXTERN GameResult_S gameResult_S;

class GameResult_A : public BaseGameResult
{
public: GameResult_A();
};
EXTERN GameResult_A gameResult_A;

class GameResult_B : public BaseGameResult
{
public: GameResult_B();
};
EXTERN GameResult_B gameResult_B;

class GameResult_C : public BaseGameResult
{
public: GameResult_C();
};
EXTERN GameResult_C gameResult_C;



