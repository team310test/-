#pragma once

class Game : public Scene
{
private:
    OBJ2DManager*   obj2dManager_;
    BG*             bg_;
    Stage*          stage_;

    bool            isPaused_;
    static Game     instance_;

    bool            isGameOver_;
    int             gameOverState_;

public:
    OBJ2D*          player_;
    OBJ2D*          playerFrame_;
    OBJ2D*          playerHeart_;

    OBJ2D*          cursor_;
    static Game* instance()         { return &instance_; }

    OBJ2DManager* obj2dManager()    { return obj2dManager_; }
    BG* bg()                        { return bg_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

    bool isGameOver() const { return (player_ && player_->performComponent_->isTrigger); }

private:
    Game()
        :obj2dManager_(nullptr)
        , bg_(nullptr)
        , stage_(nullptr)
        , isPaused_(false)
        , isGameOver_(false)
        , gameOverState_(0)
        , player_(nullptr) 
        , playerFrame_(nullptr)
        , playerHeart_(nullptr)
        , cursor_(nullptr)
    {}
    Game(const Game&) = delete; // = delete コピーコンストラクタが存在しないことを明示

    void judge();
    void gameOverProc();
};
//******************************************************************************