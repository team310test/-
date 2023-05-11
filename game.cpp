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

    // �e�N�X�`���̉��
    GameLib::texture::releaseAll();

    // ���y�̃N���A
    Audio::clear();
}


void Game::update()
{
    // �\�t�g���Z�b�g
    if ((GameLib::input::STATE(0) & GameLib::input::PAD_SELECT) &&  // 0�R���̃Z���N�g�{�^����������Ă����Ԃ�
        (GameLib::input::TRG(0) & GameLib::input::PAD_START))       // 0�R���̃X�^�[�g�{�^���������ꂽ�u��
    {
        changeScene(Title::instance());   // �^�C�g���V�[���ɐ؂�ւ���
        return;
    }

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

    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////
        timer_ = 0;
        BasePlayerBehavior::plShrinkCount_      = 0;
        BasePlayerBehavior::plShrinkCountMax_   = 10;
        Stage::resetShrinkNum();

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        GameLib::texture::load(gameLoadTexture);

        // �v���C���[�}�l�[�W���̏�����
        obj2dManager()->init();

        // �v���C���[��ǉ�����
        setPlayer(obj2dManager(), bg(),takeOverPos_,takeOverScale_, takeOverIsDrawShrink_, true); // true�Ȃ炱��obj��player_�ɑ������

        //// �J�[�\���ǉ�(��)
        //setCursor(obj2dManager(), bg());

        bg()->init(); // BG�̏�����

        UI::init();

        // �Q�[��BGM���[�v�Đ�
        Audio::play(BGM_GAME, true);

        ++state_;    // �����������̏I��
        /*fallthrough*/
    case 1:
        //////// �ʏ펞�̏��� ////////

#ifdef DEBUG_MODE
            GameLib::debug::setString("shrinkNum_:%d",stage_->getSrinkNum());               
            GameLib::debug::setString("[1]Key:ShowHitBox");             // 1�L�[�œ����蔻���\���iDEBUG_MODE�̂݁j
            GameLib::debug::setString("[2]Key:SlowMode");               // 2�L�[�ŋ^���I�ȃX���[���[�V�����ɂ���(�����߂��Â炢)�iDEBUG_MODE�̂݁j
            GameLib::debug::setString("[3]Key:AllPlPartsKill");  // 3�L�[��PL�p�[�c�S�j��iDEBUG_MODE�̂݁j
#endif

        //if (BasePlayerBehavior::plShrinkCount_ >= BasePlayerBehavior::PL_SHRINK_COUNT_MAX ||
        //    GameLib::input::TRG(0) & GameLib::input::PAD_TRG3)
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

        
        if (
            (Behavior::isObjShrink() == false)   // ���ׂĂ�obj���k���I�����Ă����
            && (!isGameOver())                   // �Q�[���I�[�o�[�łȂ����  
            )
        {
            // �X�e�[�W�X�V(�G�l�~�[�o��)
            stage_->update(obj2dManager_, bg_);
        }

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
            UI::letterBox_multiplySizeY_ = std::max(0.75f, UI::letterBox_multiplySizeY_ + LETTER_BOX_SUB_SPEED); // 0.0f��菬�������0.0f�ɏC��
        }
        else // ���ׂĂ�obj���k�����Ă��Ȃ����
        {
            Behavior::shrinkVelocity_               = SHRINK_SPEED;
            PlayerPartsBehavior::toCoreVelocity_    = TO_CORE_SPEED;
            BaseEnemyPartsBehavior::toCoreVelocity_ = TO_CORE_SPEED;
            UI::letterBox_multiplySizeY_ = std::min(1.0f, UI::letterBox_multiplySizeY_ + LETTER_BOX_ADD_SPEED); // 1.0f���傫�����1.0f�ɏC��

            // �k��SE�t�F�[�h�A�E�g
            Audio::fade(SE_SHRINK, 2.0f, 0.0f);
        }

        // ����
        if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4)
            player_->actorComponent_->hp_ = 0;


        // �Q�[���I�[�o�[�̏���
        if (isGameOver())
        {
            gameOverProc();
        }

        bg()->update();   // BG�̍X�V

        judge();

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

    // �k���J�E���g���[�^�[�̕`��(gameover�Ȃ�\�����Ȃ�)
    if(!isGameOver())UI::drawShrinkValueMeter();

    // �f��̍��т̕`��(gameover�Ȃ�\�����Ȃ�)
    if (!isGameOver())UI::drawLetterBox();
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
    bool contact = objToul::instance().ContactPos(obj, { BG::WINDOW_W_F * 0.5f,BG::WINDOW_H_F * 0.5f },2.0f);
    bool enlarge = objToul::instance().Enlarge(obj, { GAME_OVER_SCALE,GAME_OVER_SCALE },0.04f);

    if (contact && enlarge)return true;

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

        ++gameOverState_;
        break;
    case 1:
        //--< �����G�t�F�N�g >--

        if (!player_->actorComponent_->isQuake_) player_->actorComponent_->isQuake_ = true; // ���j���͐U��������
        if(ChainEffect(player_)) ++gameOverState_;
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
        playerHeart_ = setGameObj(obj2dManager(), &gamePlayerHheartObjBehavior,
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