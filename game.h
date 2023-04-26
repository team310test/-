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

    float           letterBox_multiplySizeY_;     // �f��̍��т̏c��

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

    void drawLetterBox(); // �f��̍��ѕ`��i���j

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
    Game(const Game&) = delete; // = delete �R�s�[�R���X�g���N�^�����݂��Ȃ����Ƃ𖾎�

    void judge();
    void gameOverProc();
};
//******************************************************************************