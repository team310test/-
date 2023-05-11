#include "all.h"

Title Title::instance_;

OBJ2D* setTitleObj(OBJ2DManager* obj2dManager, Behavior* behavior, VECTOR2 pos)
{
    OBJ2D* obj = new OBJ2D(
        new Renderer,
        new Collider,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        new PerformComponent
    );

    return obj2dManager->add(obj, behavior, pos);
}

void Title::init()
{
    Scene::init();

    obj2dManager_ = new OBJ2DManager;
    bg_ = new BG;

    // �ϐ��̏�����
    isStartPerform_ = true;
    oldTImer_ = 0;
    pushCount_ = 0;

    //�t�F�[�h(�C��)�A�E�g�̏�����
    FADE::clear();

    // �����w�i�𔒂�
    FADE::getInstance2()->SetColorNum(FADE::COLER::WHITE);
    FADE::getInstance2()->SetAlpha(1.0f);

    Audio::titleInit();
}

void Title::deinit()
{
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    player_         = nullptr;
    startCommand_   = nullptr;
    endCommand_     = nullptr;

    // �e�N�X�`���̉��
    GameLib::texture::releaseAll();

    // ���y�̃N���A
    Audio::clear();
}

void Title::update()
{
    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////
        timer_ = 0;
        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        GameLib::texture::load(titleLoadTexture);
        obj2dManager()->init();

        
        player_         = setTitlePlayer(obj2dManager(),bg());
        startCommand_   = setTitleObj(obj2dManager(), &titleStartObjBehavior, { 500,500 } );
        endCommand_     = setTitleObj(obj2dManager(), &titleEndObjBehavior,   { 1420,500 } );
        titleLogo_      = setTitleObj(obj2dManager(), &titleLogoObjBehavior,  { 960.0f,200.0f } );

        bg()->init();

        ++state_;                                    // �����������̏I��
        /*fallthrough*/                             // �Ӑ}�I��break;���L�q���Ă��Ȃ�
    case 1:
        //////// �ʏ펞�̏��� ////////
        obj2dManager()->update();           // �I�u�W�F�N�g�X�V
        bg()->update();                     // BG�̍X�V
        
        // ���o���I����Ă��Ȃ�������return
        if (!startPerform()) return;

        userHintMove();

        judge();
        changeSceneGame();                  // ��ʑJ��(Game)
        endGame();                          // �Q�[���I��

        ++timer_;                           // �^�C�}�[�𑫂�
        break;
    }
}

void Title::draw()
{
    // ��ʃN���A
    //GameLib::clear(VECTOR4(1.0f, 1.0f, 1.0f, 1));
    GameLib::clear(VECTOR4(0.75f, 0.45f, 0.3f, 1));

    FADE::getInstance2()->draw();

    // �I�u�W�F�N�g�̕`��
    obj2dManager()->draw();

    //�t�F�[�h(�C��)�A�E�g
    FADE::getInstance()->draw();
}

void Title::judge()
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

void Title::changeSceneGame()
{
    // ���@���ڐG������
    if (startCommand_ && startCommand_->performComponent_->isTrigger)
    {
        // ���Ԍo�߂Ńq���g�`��
        userHintShot();

        static bool isAnime = false;
        const int pushMax = 5;

        // ���񐔃A�j���[�V��������ƃQ�[����ʂɑJ��
        if (pushCount_ >= pushMax)
        {
            // �t�F�[�h�A�E�g
            const bool endFadeOut = objToul::instance().FadeOut(endCommand_);
            const bool logoFadeOut = objToul::instance().FadeOut(titleLogo_);
            const bool shrink = objToul::instance().Shrink(player_);      // �k��

            // �^�C�g��BGM�t�F�[�h�A�E�g
            Audio::fade(BGM_TITLE, 2.0f, 0.0f);

            // �����̏����������������ʂ�J�ڂ���
            if (endFadeOut && logoFadeOut && shrink)
            {
                takeOverPos_ = player_->transform_->position_;
                takeOverScale_ = player_->renderer_->drawScale_;
                takeOverIsDrawShrink_ = player_->renderer_->isDrawShrink_;
                changeScene(Game::instance());
            }
        }
        else
        {
            // �w��L�[(Space,A,B,X,Y)�������ƃA�j���[�V�����Đ�
            if ( (GameLib::input::STATE(0) & GameLib::input::PAD_TRG1 ||
                  GameLib::input::STATE(0) & GameLib::input::PAD_TRG2 ||
                  GameLib::input::STATE(0) & GameLib::input::PAD_TRG3 ||
                  GameLib::input::STATE(0) & GameLib::input::PAD_TRG4) &&
                  !isAnime)
            {
                isAnime = true;

                // �ۓ�SE�Đ�
                Audio::play(SE_HEART_BEAT, false);
            }

            // �L�[��������A�j���[�V�������Đ��I���ƃJ�E���g�𑝂₷
            if (isAnime && xAxisSclaeAnime(player_))
            {
                ++pushCount_;
                isAnime = false;

                FADE::getInstance2()->SetAlpha(1.0f - 1.0f / pushMax * pushCount_);
            }
        }
    }
}

void Title::endGame()
{
    // ���@���ڐG������
    if (endCommand_ && endCommand_->performComponent_->isTrigger)
    {
        // �^�C�g��BGM�t�F�[�h�A�E�g
        Audio::fade(BGM_TITLE, 2.0f, 0.0f);

        // ��ʂ��Ó]������Q�[���I��
        if (FADE::getInstance()->fadeOut(0.01f))
        {
            exit(0);
        }
    }
}

bool Title::startPerform()
{
    // ���o���I����Ă�����true��Ԃ�
    if (!isStartPerform_) return true;

    if (player_->performComponent_->isTrigger)
    {
        const bool state = objToul::instance().FadeIn(startCommand_);
        const bool end = objToul::instance().FadeIn(endCommand_);
        const bool logo = objToul::instance().FadeIn(titleLogo_);

        // �t�F�[�h�C��������������
        if (state && end && logo)
        {
            // player��update�ύX
            if (player_->update_ != PLAYER_CORE_UPDATE) player_->update_ = PLAYER_CORE_UPDATE;
            isStartPerform_ = false;

            // �^�C�g��BGM���[�v�Đ�
            Audio::play(BGM_TITLE, true);
            
            return true;
        }
    }

    return false;
}

void Title::userHintMove()
{
    // PL���ړ�������
    if (isPlayerMove_)
    {
        // userHintMove_��nullpyr�Ȃ�return
        if (!userHintMove_) return;

        // userHintMove_��nullptr�łȂ��Ȃ�t�F�[�h�A�E�g������nullptr�ɂ���
        if (objToul::instance().FadeOut(userHintMove_, 0.05f))
        {
            userHintMove_->behavior_ = nullptr;
            userHintMove_ = nullptr;
        }
        return;
    }

    // oldTImer_��0�Ȃ�timer�̒l����
    if (!oldTImer_) oldTImer_ = timer_;

    // PL�̈ړ����̓`�F�b�N
    if (GameLib::input::TRG(0) & (GameLib::input::PAD_UP | GameLib::input::PAD_DOWN | GameLib::input::PAD_LEFT | GameLib::input::PAD_RIGHT))
    {
        isPlayerMove_ = true;
        oldTImer_ = 0;
        return;
    }

    // ��莞�ԗ��ƃq���g��`��
    if (timer_ - oldTImer_ > 200)
    {
        if (!userHintMove_)
        {
            VECTOR2 pos = player_->transform_->position_;
            pos += {0.0f, -100.0f};
            userHintMove_ = setTitleObj(obj2dManager(), &titleHintMoveObjBehavior, pos);
        }
        objToul::instance().FadeIn(userHintMove_);
    }
}

void Title::userHintShot()
{
    // PL���U��������
    if (isPlayerShot_)
    {
        // userHintMove_��nullpyr�Ȃ�return
        if (!userHintShot_) return;

        // userHintMove_��nullptr�łȂ��Ȃ�t�F�[�h�A�E�g������nullptr�ɂ���
        if (objToul::instance().FadeOut(userHintShot_, 0.05f))
        {
            userHintShot_->behavior_ = nullptr;
            userHintShot_ = nullptr;
        }
        return;
    }

    // oldTImer_��0�Ȃ�timer�̒l����
    if (!oldTImer_) oldTImer_ = timer_;

    // PL�̍U�����̓`�F�b�N
    if (GameLib::input::TRG(0) & (GameLib::input::PAD_TRG3))
    {
        isPlayerShot_ = true;
        oldTImer_ = 0;
        return;
    }

    // ��莞�ԗ��ƃq���g��`��
    if (timer_ - oldTImer_ > 200)
    {
        if (!userHintShot_)
        {
            VECTOR2 pos = player_->transform_->position_;
            pos += {0.0f, -200.0f};
            userHintShot_ = setTitleObj(obj2dManager(), &titleHintShotObjBehavior, pos);
        }
        objToul::instance().FadeIn(userHintShot_);
    }
}