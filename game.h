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
    int             gameOverTimer_;

    float           letterBox_multiplySizeY_;     // 映画の黒帯の縦幅

public:
    OBJ2D*          player_;
    OBJ2D*          cursor_;
    static Game* instance()         { return &instance_; }

    OBJ2DManager* obj2dManager()    { return obj2dManager_; }
    BG* bg()                        { return bg_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

    void drawLetterBox(); // 映画の黒帯描画（仮）

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
        , stage_(nullptr)
        , isPaused_(false)
        , isGameOver_(false)
        , gameOverTimer_(0)
        , letterBox_multiplySizeY_(1.0f)
        , player_(nullptr) 
        , cursor_(nullptr)
    {}
    Game(const Game&) = delete; // = delete コピーコンストラクタが存在しないことを明示

    void judge();
    void gameOverProc();
};
//******************************************************************************