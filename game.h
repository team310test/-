#ifndef INCLUDED_GAME
#define	INCLUDED_GAME

//******************************************************************************
//
//
//      ゲームシーン
//
//
//******************************************************************************

//==============================================================================
//
//      Gameクラス
//
//==============================================================================

class Game : public Scene
{
public:
    // クラス内での定数の定義の仕方
    // int型であればconstで良いが、それ以外はconstexprを使用する
    static constexpr float GROUND_POS_Y = 640.0f;

public:
    static Game* instance() { return &instance_; }

    void init();
    void deinit();
    void update();
    void draw();

    // ゲッターは後ろに_をつけない
    PlayerManager*      playerManager()     { return playerManager_; }

private:
    bool                isPaused;

    // メンバ変数は後ろに_をつける
    PlayerManager*      playerManager_;

    static Game instance_;
};

//******************************************************************************

#endif // !INCLUDED_GAME
