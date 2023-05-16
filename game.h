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

    int             gameClearState_;

public:
    OBJ2D*          player_;
    OBJ2D*          playerFrame_;
    OBJ2D*          playerHeart_;

    OBJ2D*          boss_;

    OBJ2D*          cursor_;

    bool            isStartFirstShrink_; //�@�^�C�g������Q�[���ɓ���ŏ��̏k�����o

    bool            isBossDied_; // �{�X�����񂾂�

    static Game* instance()         { return &instance_; }

    OBJ2DManager* obj2dManager()    { return obj2dManager_; }
    BG* bg()                        { return bg_; }

    void init() override;
    void deinit() override;
    void update() override;
    void draw() override;

    bool isGameOver()  const { return (player_ && player_->performComponent_->isTrigger); }
    bool isGameClear() const { return (!isGameOver() && isBossDied_); } // �N���A������

private:
    Game()
        :obj2dManager_(nullptr)
        , bg_(nullptr)
        , stage_(nullptr)
        , isPaused_(false)
        , isGameOver_(false)
        , gameOverState_(0)
        , gameClearState_(0)
        , player_(nullptr) 
        , playerFrame_(nullptr)
        , playerHeart_(nullptr)
        , boss_(nullptr)
        , cursor_(nullptr)
        , isStartFirstShrink_(false)
        , isBossDied_(false)
    {}
    Game(const Game&) = delete; // = delete �R�s�[�R���X�g���N�^�����݂��Ȃ����Ƃ𖾎�

    void judge();
    void gameOverProc();
    void gameClearProc(); // �N���A����
};
//******************************************************************************