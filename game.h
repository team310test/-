#pragma once

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
private:
    OBJ2DManager*   obj2dManager_;
    BG*             bg_;
    bool            isPaused_;
    OBJ2D*          player_;
    static Game     instance_;

    bool            isGameOver_;
    int             gameOverTimer_;

public:
    static Game* instance()         { return &instance_; }

    OBJ2DManager* obj2dManager()    { return obj2dManager_; }
    BG* bg()                        { return bg_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

    void setGameOver()
    {
        isGameOver_ = true;
        gameOverTimer_ = 60;
    }
    bool isGameOver() const { return isGameOver_; }

private:
    Game()
        :obj2dManager_(nullptr)
        , bg_(nullptr)
        , isPaused_(false)
        , player_(nullptr) {}
    Game(const Game&) = delete; // = delete コピーコンストラクタが存在しないことを明示

    void judge();
    void gameOverProc();
};

//******************************************************************************