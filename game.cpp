#include "all.h"

Game Game::instance_;


OBJ2D* setGameObj(OBJ2DManager* obj2dManager, Behavior* behavior, VECTOR2 pos)
{
    OBJ2D* obj = new OBJ2D(
        new Renderer,
        new Collider,
        nullptr,
        new ActorComponent,
        nullptr,
        nullptr,
        new PerformComponent
    );

    return obj2dManager->add(obj, behavior, pos);
}

void Game::init()
{
    Scene::init();	    // ���N���X��init���Ă�

    obj2dManager_   = new OBJ2DManager;
    bg_             = new BG;
    stage_          = new Stage;

    isPaused_   = false;   // �|�[�Y�t���O�̏�����

    gameOverState_ = 0;
    isGameOver_ = false;

    gameClearState_ = 0;
    isBossDied_ = false;

    //�t�F�[�h(�C��)�A�E�g�̏�����
    FADE::clear();
    FADE::getInstance2()->SetColorNum(1);

    Audio::gameInit();
}


void Game::deinit()
{
    // �e�}�l�[�W���̉��
    safe_delete(stage_);
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    player_ = nullptr;
    playerFrame_ = nullptr;
    playerHeart_ = nullptr;

    boss_ = nullptr;

    // �e�N�X�`���̉��
    GameLib::texture::releaseAll();

    // ���y�̃N���A
    Audio::clear();
}


void Game::update()
{


#ifdef DEBUG_MODE
    // �^���X���[���[�V����
    static bool isSleep = false;
    if (GetAsyncKeyState('2') < 0) isSleep = (!isSleep) ? true : false;
    if (isSleep) Sleep(60);
#endif

    // �|�[�Y����
    //if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
    //    isPaused_ = !isPaused_;       // 0�R���̃X�^�[�g�{�^���������ꂽ��|�[�Y��Ԃ����]
    //if (isPaused_) return;           // ���̎��_�Ń|�[�Y���Ȃ烊�^�[��


#ifdef DEBUG_MODE
    GameLib::debug::setString("shrinkNum_:%d", stage_->getSrinkNum());
    GameLib::debug::setString("[1]Key:ShowHitBox");     // 1�L�[�œ����蔻���\���iDEBUG_MODE�̂݁j
    GameLib::debug::setString("[2]Key:SlowMode");       // 2�L�[�ŋ^���I�ȃX���[���[�V�����ɂ��i(�����߂��Â炢)�iDEBUG_MODE�̂݁j
    GameLib::debug::setString("[3]Key:KillPlCore");     // 3�L�[�Ńv���C���[�R�A�����iDEBUG_MODE�̂݁j
#endif

    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////
        timer_ = 0;
        BasePlayerBehavior::plShrinkCount_       = 0;
        BasePlayerBehavior::plShrinkCountMax_    = 10;
        BasePlayerBehavior::plPartsCurrentCount_ = 0;
        Stage::resetShrinkNum();

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        GameLib::texture::load(gameLoadTexture);

        // �v���C���[�}�l�[�W���̏�����
        obj2dManager()->init();

        // �v���C���[��ǉ�����
        setPlayer(obj2dManager(), bg(),takeOverPos_, takeOverIsDrawShrink_, true); // true�Ȃ炱��obj��player_�ɑ������

        //// �J�[�\���ǉ�(��)
        //setCursor(obj2dManager(), bg());

        bg()->init(); // BG�̏�����

        UI::init();

        ++state_;    // �����������̏I��
        /*fallthrough*/
    case 1:
        //////// �ʏ펞�̏��� ////////
        
        // obj���k�����Ă��Ȃ���
        if (!Behavior::isObjShrink() && !isGameOver() && !isGameClear())
        {
            // �\�t�g���Z�b�g
            if ((GameLib::input::STATE(0) & GameLib::input::PAD_SELECT) &&  // 0�R���̃Z���N�g�{�^����������Ă����Ԃ�
                (GameLib::input::TRG(0) & GameLib::input::PAD_START))       // 0�R���̃X�^�[�g�{�^���������ꂽ�u��
            {
                changeScene(Title::instance());   // �^�C�g���V�[���ɐ؂�ւ���
                return;
            }

            // �Q�[���I�[�o�[�łȂ���΃X�e�[�W�X�V(�G�l�~�[�o��)
            stage_->update(obj2dManager_, bg_);
        }

        // �n�߂̏k���J�n
        if (isStartFirstShrink_)
        {
            // �I�u�W�F�N�g�̍X�V
            obj2dManager()->update();

            isStartFirstShrink_ = false; // ��x�����s���̂ł���ȍ~��false

            bg()->BG::setBGShrink();            // �w�i�̏k���ݒ�
            Collider::isAllShrink_ = true;      // Shrink���J�n

            // �k��SE�Đ�
            Audio::play(SE_SHRINK, false);

            // �Q�[��BGM���[�v�Đ�
            Audio::play(BGM_GAME, true);
            Audio::fade(BGM_GAME, 5.0f, 1.0f);
        }

        if (BasePlayerBehavior::plShrinkCount_ >= BasePlayerBehavior::plShrinkCountMax_)  // �v���C���[�̐���Shrink�̕K�v���ɒB������
        {
            if (Collider::isAllShrink_ == false &&  // Shrink���J�n����Ă��炸�A
                Behavior::isObjShrink() == false)   // ���ׂĂ�obj���k�����Ă��Ȃ����
            {
                bg()->BG::setBGShrink();            // �w�i�̏k���ݒ�

                stage_->addSrinkNum();              // shrinkNum���Z
                   
                //BasePlayerBehavior::plShrinkCountMax_ += 1; // �k������܂ł̃p�[�c�̕K�v���𑝉�

                Collider::isAllShrink_ = true;      // Shrink���J�n

                // �k��SE�Đ�
                Audio::play(SE_SHRINK, false);
            }
        }

        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();


        // �I�u�W�F�N�g�̍X�V���Shrink�̊J�n���~�߂�
        if (Collider::isAllShrink_)
        {
            Collider::isAllShrink_ = false;
            BasePlayerBehavior::plShrinkCount_ = 0; // �v���C���[�̃J�E���g�����Z�b�g
        }
        
        //// �k���ƃp�[�c�v���C���[�֌��������x������
        if (Behavior::isObjShrink()) // �ЂƂł�obj���k�����Ă����
        {
            BG::bgSubScale_                         += (-BG_SHRINK_SPEED) * 0.0225f;
            Behavior::shrinkVelocity_               += (-SHRINK_SPEED)    * 0.015f;
            PlayerPartsBehavior::toCoreVelocity_    += (-TO_CORE_SPEED)   * 0.015f;
            BaseEnemyPartsBehavior::toCoreVelocity_ += (-TO_CORE_SPEED)   * 0.015f;

            UI::plPartsCountPos_.y = std::min(0.0f, UI::plPartsCountPos_.y + 5.0f);

            //meterAlphaColor_

            UI::meterPos_.x = std::min(825.0f,  UI::meterPos_.x + 20.0f);
            UI::meterPos_.y = std::max(-450.0f, UI::meterPos_.y - 19.8f);
            // ������
            UI::meterAlphaColor_ = std::max(
                0.5f, UI::meterAlphaColor_ += (-0.05f)
            );

            UI::letterBox_multiplySizeY_ = std::max(0.7f, UI::letterBox_multiplySizeY_ + LETTER_BOX_SUB_SPEED); // 0.0f��菬�������0.0f�ɏC��
        }
        else // ���ׂĂ�obj���k�����Ă��Ȃ����
        {   
            Behavior::shrinkVelocity_               = SHRINK_SPEED;
            PlayerPartsBehavior::toCoreVelocity_    = TO_CORE_SPEED;
            BaseEnemyPartsBehavior::toCoreVelocity_ = TO_CORE_SPEED;

            UI::plPartsCountPos_.y = std::min(0.0f, UI::plPartsCountPos_.y + 5.0f);

            UI::meterPos_.x = std::max(0.0f, UI::meterPos_.x - 50.0f);
            UI::meterPos_.y = std::min(0.0f, UI::meterPos_.y + 28.0f);

            UI::letterBox_multiplySizeY_ = std::min(1.0f, UI::letterBox_multiplySizeY_ + LETTER_BOX_ADD_SPEED); // 1.0f���傫�����1.0f�ɏC��

            // �N�����Ă����瓧����
            if (UI::isInAreaMeter_)
            {
                UI::meterAlphaColor_ = std::max(
                    UI::UI_ALPHA_COLOR_MIN, UI::meterAlphaColor_ += (-0.05f)
                );
            }
            else // �łȂ���Ζ߂�
            {
                UI::meterAlphaColor_ = std::min(
                    UI::UI_ALPHA_COLOR_MAX, UI::meterAlphaColor_ += 0.05f
                );
            }

            // �k��SE�t�F�[�h�A�E�g
            Audio::fade(SE_SHRINK, 0.5f, 0.0f);
        }

#ifdef DEBUG_MODE
        // 3�L�[�Ńv���C���[�R�A����
        if (GetAsyncKeyState('3') & 1) player_->actorComponent_->hp_ = 0;
#endif

        bg()->update();   // BG�̍X�V

        UI::update();     // UI�̍X�V

        judge();


        // �Q�[���I�[�o�[�̏���
        if (isGameOver())
        {
            gameOverProc();
            break;
        }

        
        // �Q�[���N���A�̏���
        if (isGameClear())
        {
            gameClearProc();
            break;
        }

        ++timer_;
        break;
    }
}


// �h���b�v�p�[�c�𖾖ł�����֐�
void drawblink()
{
    static float blinkColor       = 0.0f;   // ���ŃJ���[
    static bool  isBlinkColorFlip = false;  // �J���[�̑��������߂�(false�Ȃ���Z�Atrue�Ȃ猸�Z)

    blinkColor += (!isBlinkColorFlip) ? ADD_BLINK_COLOR : -ADD_BLINK_COLOR;

    // �J���[���K��l�𒴂����瑝���𔽓]������
         if (blinkColor >= BLINK_COLOR_MAX) isBlinkColorFlip = true;
    else if (blinkColor <= BLINK_COLOR_MIN) isBlinkColorFlip = false;


    // �}�X�N�ɕ`��
    DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);
    GameLib::primitive::rect(
        { 0,0 }, { BG::WINDOW_W, BG::WINDOW_H },
        { 0,0 }, 0, { blinkColor,blinkColor,blinkColor,1 }
    );
    // �X�e���V�����Z�b�g
    DepthStencil::instance().clear();
    DepthStencil::instance().set(DepthStencil::MODE::NONE);
}

//--------------------------------------------------------------
//  �`�揈��
//--------------------------------------------------------------
void Game::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.75f, 0.45f, 0.3f, 1));
    //GameLib::clear(VECTOR4(1,1,1,1));

    // �w�i�̕`��
    bg()->drawBack();

    // gameovern�̎��w�i��^������
    FADE::getInstance2()->draw();

    // �I�u�W�F�N�g�̕`��
    obj2dManager()->draw();

    // �h���b�v�p�[�c�𖾖ł�����
    drawblink();

    // (�Q�[���I�[�o�[�E�Q�[���N���A�Ȃ�UI��\�����Ȃ�)
    if (!isGameOver() && !isGameClear())
    {
        // �k���J�E���g���[�^�[�̕`��
        UI::drawShrinkValueMeter();

        // ���݂̃v���C���[�p�[�c���`��
        UI::drawPlPartsCurrentCount();

        // �f��̍��т̕`��
        UI::drawLetterBox();
    }

    // �W�߂��p�[�c�E�o�ߎ��ԕ\��
    if (UI::isSpawnResultJunks_) UI::drawResultJunks();
    if (UI::isSpawnResultTimes_) UI::drawResultTimes();
}

void Game::judge()
{
    for (auto& src : *obj2dManager_->getList())
    {
        if (src->behavior_ == nullptr) continue;
        if (src->collider_->judgeFlag_ == false) continue;

        for (auto& dst : *obj2dManager_->getList())
        {
            if (src == dst) continue;
            if (src->behavior_ == nullptr) break;
            if (src->collider_->judgeFlag_ == false) break;
            if (dst->behavior_ == nullptr) continue;
            if (dst->collider_->judgeFlag_ == false) continue;

            // src�̍U���^�C�v��dst�̃^�C�v����v���Ȃ����continue;
            if (src->behavior_->getAttackType() != dst->behavior_->getType())
                continue;

            // �����蔻����s��
            if (src->collider_->hitCheck(dst))
            {
                // ���������ꍇ�̏���
                src->behavior_->hit(src, dst);
            }
        }
    }
}

// ��ʒ����Ɉړ�����
bool MoveToCenter(OBJ2D* obj)
{
    bool contact = objToul::instance().ContactPos(obj, { BG::WINDOW_W_F * 0.5f, BG::WINDOW_H_F * 0.5f }, 7.0f);
    bool enlarge = objToul::instance().Enlarge(obj, { GAME_OVER_SCALE, GAME_OVER_SCALE }, 0.04f);

    if (contact && enlarge) return true;

    return false;
}

// ��ʊO�܂ŗ�������
bool objFall(OBJ2D* /*obj*/)
{

    return false;
}

void Game::gameOverProc()
{
    //if (wait(60)) ++gameOverState_;
    switch (gameOverState_)
    {
    case 0:
        //--< �����ݒ� >--
        
        // judge���s��Ȃ��悤�ɂ���
        player_->collider_->judgeFlag_ = false;
        // Trigger��true��(GameOver�̃t���O������)
        player_->performComponent_->isTrigger = true;
        // ����ł��Ȃ�����
        player_->update_ = nullptr;
        player_->transform_->velocity_ = { 0.0f,0.0f };
        // �A�j���[�V�����I��
        player_->actorComponent_->objAnimeAlways_ = nullptr;

        // �Q�[���E�{�X��BGM�t�F�[�h�A�E�g
        Audio::fade(BGM_GAME, 2.0f, 0.0f);
        Audio::fade(BGM_BOSS, 2.0f, 0.0f);

        ++gameOverState_;
        break;
    case 1:
        //--< �����G�t�F�N�g >--

        if (!player_->isQuake_) player_->isQuake_ = true; // ���j���͐U��������
        if (ChainEffect(player_)) ++gameOverState_;
        break;
    case 2:
        // --< �G�t�F�N�g�̍Đ��I���҂� >--

        if (!objToul::instance().isObjType(obj2dManager(), OBJ_TYPE::EFFECT)) ++gameOverState_;
        break;
    case 3:
        //--< �E�F�C�g >--

        if (wait(10)) ++gameOverState_;
        break;
    case 4:
        //--<player�{�̈ȊO���폜>--

        for (auto& obj : *obj2dManager_->getList())
        {
            if (!obj->behavior_) continue;
            // ���@�{�̂Ȃ��΂�
            if (obj == player_)continue;

            obj->behavior_ = nullptr;
        }

        // �w�i�𔒂ɂ���
        FADE::getInstance2()->SetAlpha(1.0f);
        ++gameOverState_;
        break;
    case 5:
        //--< �E�F�C�g >--

        if (wait(30)) ++gameOverState_;
        break;
    case 6:
        //--<��ʒ��S�Ɉړ�>--

        if (MoveToCenter(player_)) ++gameOverState_;

        break;
    case 7:
        //--< �E�F�C�g >--

        if (wait(30))++gameOverState_;
        break;
    case 8:
        //--< ���@�t���[���E�n�[�g�̐��� >--

        playerFrame_ = setGameObj(obj2dManager(), &gamePlayerFrameObjBehavior, player_->transform_->position_);
        playerHeart_ = setGameObj(obj2dManager(), &gamePlayerHeartObjBehavior,
            { player_->transform_->position_.x - 7.0f * GAME_OVER_SCALE,player_->transform_->position_.y + 28.0f * GAME_OVER_SCALE }); 

        ++gameOverState_;
        break;
    case 9:
        //--< �n�[�g�̗�����^�C�g���֑J�� >--
        if (player_->renderer_->color_.w) player_->renderer_->color_.w = 0.0f;

        if (playerHeart_->performComponent_->isTrigger) changeScene(Title::instance());
        break;
    }
}


enum RANK
{
    S, A, B, C,
};

// �����N�t���̎d��
// { S+S=S, S+A=A, S+B=A, S+C=B }
// { A+S=A, A+A=A, A+B=B, A+C=B }
// { B+S=A, B+A=B, B+B=B, B+C=C }
// { C+S=B, C+A=B, C+B=C, C+C=C }

// ���������N�����߂�
Behavior* decideRank[][4] = {
    { &gameResult_S, &gameResult_A, &gameResult_A, &gameResult_B },
    { &gameResult_A, &gameResult_A, &gameResult_B, &gameResult_B },
    { &gameResult_A, &gameResult_B, &gameResult_B, &gameResult_C },
    { &gameResult_B, &gameResult_B, &gameResult_C, &gameResult_C },
};
// �ꌾ�R�����g�����߂�
Behavior* decideText[][4] = {
    { &gameResult_text_junkie, &gameResult_text_great, &gameResult_text_great, &gameResult_text_nice },
    { &gameResult_text_great,  &gameResult_text_great, &gameResult_text_nice,  &gameResult_text_nice },
    { &gameResult_text_great,  &gameResult_text_nice,  &gameResult_text_nice,  &gameResult_text_soso },
    { &gameResult_text_nice,   &gameResult_text_nice,  &gameResult_text_soso,  &gameResult_text_soso },
};

struct ResultTextData
{
    int       spawnTime; // ��������
    Behavior* behavior;  // Behavior
    VECTOR2   pos;       // �����ʒu
};


// ���U���g�e�L�X�g����
bool spawnResultText(const int& spawnTimer)
{
    // TODO: �����N�t���̐ݒ�
    
    // �p�[�c�̃����N�t��
    int junkRank  = RANK::S;
    const int partsCount = BasePlayerBehavior::plPartsCurrentCount_;
         if (partsCount >= 50) junkRank = RANK::S; // 50�ȏ�
    else if (partsCount >= 30) junkRank = RANK::A; // 30~49��
    else if (partsCount >= 20) junkRank = RANK::B; // 20~29��
    else                       junkRank = RANK::C; // 20����

    // �N���A���Ԃ̃����N�t��
    int timesRank = RANK::S;
    const int clearTime = Game::instance()->getTimer();
         if (clearTime <= 60 * 20) timesRank = RANK::S; // 2���ȉ�
    else if (clearTime <= 60 * 40) timesRank = RANK::A; // 2��~4��
    else if (clearTime <= 60 * 60) timesRank = RANK::B; // 4��~6��
    else                           timesRank = RANK::C; // 6����

    // �����I�ȃ����N�t��
    Behavior* gameResultSABC = decideRank[junkRank][timesRank];
    Behavior* gameResultText = decideText[junkRank][timesRank];


    // ���ԂɃe�L�X�g�𐶐�
    ResultTextData resultTextData[] = {
        { 60,  &gameResult_junks,   { 390,  400 } }, // JUNK'S
        { 120, &gameResult_times,   { 400,  550 } }, // TIME'S
        { 180, &gameResult_rank,    { 1350, 170 } }, // RANK
        { 210, gameResultSABC,      { 1355, 470 } }, // S�EA�EB�EC
        { 240, gameResultText,      { 1450, 740 } }, // �Ђƌ�
        { 300, &gameResult_anyPush, { 575,  800 } }, // ANY PUSH
                                                         
        { 0, nullptr, { 0.0f,0.0f } },
    };
    if (spawnTimer == 90) UI::isSpawnResultJunks_ = true;
    if (spawnTimer == 150) UI::isSpawnResultTimes_ = true;

    static ResultTextData* currentData = nullptr;
    if (!currentData) currentData = resultTextData;


    while (currentData->behavior && currentData->spawnTime == spawnTimer)
    {
        OBJ2D* resultText = setGameObj(
            Game::instance()->obj2dManager(), currentData->behavior, currentData->pos
        );
        resultText->zOrder_  = 100;   // �őO��
        resultText->isQuake_ = true; // �������ɗh�炷
        ++currentData;
    }

    // behavior��nullptr�Ȃ�
    if (!currentData->behavior)
    {
        currentData = nullptr;
        return true; // �������I������̂�true
    }

    return false;
}


void Game::gameClearProc()
{
    if (!boss_) return;

    Transform*      bossT = boss_->transform_;
    ActorComponent* bossA = boss_->actorComponent_;

    static OBJ2D* resultBack = nullptr; // ���U���g�o�b�N
    static int spawnTimer = 0;

    switch (gameClearState_)
    {
    case 0: // �����ݒ�
        // judge���s��Ȃ��悤�ɂ���
        player_->collider_->judgeFlag_ = false;

        // ����ł��Ȃ�����
        boss_->update_ = nullptr;
        bossT->velocity_ = {};
        // �A�j���[�V�����I��
        bossA->objAnimeAlways_ = nullptr;

        // �Q�[���E�{�X��BGM�t�F�[�h�A�E�g
        Audio::fade(BGM_GAME, 2.0f, 0.0f);
        Audio::fade(BGM_BOSS, 2.0f, 0.0f);

        ++gameClearState_;
        /*fallthrough*/
    case 1: // ���΂炭����
        // �A�������G�t�F�N�g
        if (!boss_->isQuake_) boss_->isQuake_ = true; // ���j���͐U��������
        ChainEffect(boss_);

        if (wait(120))
        {
            // ���U���g�o�b�N����
            resultBack = setGameObj(
                Game::instance()->obj2dManager(), &gameResult_back,
                { BG::WINDOW_W_F * 0.5f, BG::WINDOW_H_F * 0.5f }
            );
            resultBack->zOrder_ = 100;

            ++gameClearState_;
            break;
        }

        break;
    case 2: // ���U���g
        // �A�������G�t�F�N�g
        if (!boss_->isQuake_) boss_->isQuake_ = true; // ���j���͐U��������
        ChainEffect(boss_);

        // ���U���g�o�b�N�̃A�j���[�V�������I�����sprData�ɐ؂�ւ���Ă��Ȃ����break
        if (!resultBack->renderer_->data_) break;

            // ���U���g�e�L�X�g���������I����Ă��Ȃ����break
        if (!spawnResultText(spawnTimer))
        {
            ++spawnTimer;
            break;
        }

        spawnTimer = 0;
        ++gameClearState_;
        break;      
    case 3: // �{�^���A�N�V�����҂�
        // �A�������G�t�F�N�g
        if (!boss_->isQuake_) boss_->isQuake_ = true; // ���j���͐U��������
        ChainEffect(boss_);

        // �w��̃{�^�����������玟�ɐi��
        if ((GameLib::input::TRG(0) & GameLib::input::PAD_TRG1) ||
            (GameLib::input::TRG(0) & GameLib::input::PAD_TRG2) ||
            (GameLib::input::TRG(0) & GameLib::input::PAD_TRG3) ||
            (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4))
        {
            UI::isSpawnResultJunks_ = false;
            UI::isSpawnResultTimes_ = false;

            ++gameClearState_;
            break;
        }

        break;
    case 4: // ���U���g��ʂ̃o�b�N�̕s�����x��������
        // ���U���g�o�b�N�ȊO�̃��U���gUI������
        for (auto& obj : *obj2dManager_->getList())
        {
            if (!obj->behavior_) continue;
            if (obj->behavior_->getType() == OBJ_TYPE::PLAYER) continue;
            if (obj->behavior_->getType() == OBJ_TYPE::EFFECT) continue;
            if (obj == boss_)      continue;
            if (obj == resultBack) continue;

            obj->behavior_ = nullptr;
        }

        // �A�������G�t�F�N�g
        if (!boss_->isQuake_) boss_->isQuake_ = true; // ���j���͐U��������
        ChainEffect(boss_);

        // ���U���g�o�b�N�̕s�����x��������
        resultBack->renderer_->color_.w = std::max(
            -0.5f, resultBack->renderer_->color_.w - 0.025f
        );

        // ���U���g�o�b�N�s�����x��������؂�����
        if (resultBack->renderer_->color_.w == -0.5f)
        {
            ++gameClearState_;
            break;
        }

        break;
    case 5: // �G�t�F�N�g�̍Đ��I���҂�
        if (!objToul::instance().isObjType(obj2dManager(), OBJ_TYPE::EFFECT))
        {
            ++gameClearState_;
            break;
        }

        break;
    case 6: // �E�F�C�g
        if (wait(10))
        {
            ++gameClearState_;
            break;
        }

        break;
    case 7:
        // �v���C���[�𓧖��ɂ���
        player_->renderer_->color_.w = 0.0f;

        // �w�i�𔒂ɂ���
        FADE::getInstance2()->SetAlpha(1.0f);

        ++gameClearState_;
        break;
    case 8: // �E�F�C�g
        if (wait(30))
        {
            ++gameClearState_;
            break;
        }

        break;
    case 9: // ��ʒ��S�Ɉړ�
        if (MoveToCenter(boss_))
        {
            ++gameClearState_;
            break;
        }

        break;
    case 10: // �E�F�C�g
        if (wait(30))
        {
            ++gameClearState_;
            break;
        }

        break;
    case 11: // ���@�t���[���E�n�[�g�̐���
        playerFrame_ = setGameObj(
            obj2dManager(), &gamePlayerFrameObjBehavior, bossT->position_
        );
        playerFrame_->renderer_->Xflip(); // ���]

        playerHeart_ = setGameObj(
            obj2dManager(), &gamePlayerHeartObjBehavior, 
            { bossT->position_.x + 7.0f  * GAME_OVER_SCALE,
              bossT->position_.y + 28.0f * GAME_OVER_SCALE }
            );           
        playerHeart_->renderer_->Xflip(); // ���]

        ++gameClearState_;
        break;
    case 12: // �n�[�g�̗�����^�C�g���֑J��
        boss_->renderer_->color_.w = 0.0f;

        if (playerHeart_->performComponent_->isTrigger)
        {
            changeScene(Title::instance());
            return;
        }

        break;
    }
}
