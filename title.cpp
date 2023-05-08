#include "all.h"

Title Title::instance_;

OBJ2D* setTitleObj(OBJ2DManager* obj2dManager, Behavior* behavior,VECTOR2 pos)
{
    OBJ2D* obj = new OBJ2D(
        new Renderer,
        new Collider,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        new TitleComponent
    );

    return obj2dManager->add(obj, behavior, pos);
}

void Title::init()
{
    Scene::init();

    obj2dManager_ = new OBJ2DManager;
    bg_ = new BG;

    // �ϐ��̏�����
    isStatePerform_ = true;
    oldTImer_ = 0;
    pushCount_ = 0;

    // //�t�F�[�h(�C��)�A�E�g�̏�����
    FADE::clear();
}

void Title::deinit()
{
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    player_ = nullptr;
    stateCommand_ = nullptr;
    endCommand_ = nullptr;

    // �e�N�X�`���̉��
    GameLib::texture::releaseAll();

    // ���y�̃N���A
    GameLib::music::clear();
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
        GameLib::texture::load(loadTexture);
        obj2dManager()->init();

        
        player_ = setTitlePlayer(obj2dManager(),bg());
        stateCommand_ = setTitleObj(obj2dManager(), &titleStateObjBehavior, { 500,500 });
        endCommand_ = setTitleObj(obj2dManager(), &titleEndObjBehavior, { 1420,500 });
        titleLoge_ = setTitleObj(obj2dManager(), &titleLogoObjBehavior, { 960.0f,200.0f });

        bg()->init();

        state_++;                                    // �����������̏I��
        /*fallthrough*/                             // �Ӑ}�I��break;���L�q���Ă��Ȃ�

    case 1:
        //////// �ʏ펞�̏��� ////////
        GameLib::debug::setString("time:%d", timer_);

        obj2dManager()->update();           // �I�u�W�F�N�g�X�V
        bg()->update();                     // BG�̍X�V
        
        // ���o���I����Ă��Ȃ�������return
        if (!statePerform()) return;

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
    GameLib::clear(VECTOR4(0.75f, 0.45f, 0.3f, 1));

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
    if (stateCommand_ && stateCommand_->titleComponent_->isTrigger)
    {
        // ���Ԍo�߂Ńq���g�`��
        userHintShot();

        static bool isAnime = false;
        
        // ���񐔃A�j���[�V��������ƃQ�[����ʂɑJ��
        if (pushCount_ >= 3)
        {
            const float fadeSpeed = 0.01f;

            // �t�F�[�h�A�E�g
            const bool endFadeOut = objFadeOut(endCommand_, fadeSpeed);    
            const bool logoFadeOut = objFadeOut(titleLoge_, fadeSpeed);


            const bool shrink = objShrink();      // �k��

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
            // �L�[�������ƃA�j���[�V�����Đ�
            if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG3 && !isAnime)
                isAnime = true;

            // �L�[��������A�j���[�V�������Đ��I���ƃJ�E���g�𑝂₷
            if (isAnime && xAxisSclaeAnime(player_))
            {
                ++pushCount_;
                isAnime = false;
            }
        }
    }
}

void Title::endGame()
{
    // ���@���ڐG������
    if (endCommand_ && endCommand_->titleComponent_->isTrigger)
    {
        // ��ʂ��Ó]������Q�[���I��
        if (FADE::getInstance()->fadeOut(0.01f))
        {
            exit(0);
        }
    }
}

bool Title::statePerform()
{
    // ���o���I����Ă�����true��Ԃ�
    if (!isStatePerform_) return true;

    if (player_->titleComponent_->isTrigger)
    {
        const float fadeSpeed = 0.01f;

        const bool state = objFadeIn(stateCommand_, fadeSpeed);
        const bool end = objFadeIn(endCommand_, fadeSpeed);
        const bool logo = objFadeIn(titleLoge_, fadeSpeed);

        // �t�F�[�h�C��������������
        if (state && end && logo)
        {
            // player��update�ύX
            if (player_->update_ != PLAYER_CORE_UPDATE) player_->update_ = PLAYER_CORE_UPDATE;
            isStatePerform_ = false;
            return true;
        }
    }

    return false;
}

bool Title::objFadeOut(OBJ2D* obj, float fadeSpeed)
{
    //const float fadeSpeed = 0.01f;

    // �����x0�����̏ꍇ
    if (obj->renderer_->color_.w < 0.0f)
    {
        obj->renderer_->color_.w = 0.0f;
        return true;
    }

    // �����x0.0�𒴂��Ă���Ȃ猸��
    if (obj->renderer_->color_.w >= 0)
    {
        obj->renderer_->color_.w -= fadeSpeed;
        // ���ߏC��
        if(obj->renderer_->color_.w < 0)
            obj->renderer_->color_.w = 0.0f;
    }

    // �S�ē����ɂȂ�����treu��Ԃ�
    if (obj->renderer_->color_.w == 0)
    {
        return true;
    }

    return false;
}

bool Title::objFadeIn(OBJ2D* obj, float fadeSpeed)
{
    // �����x1.0�𒴂��Ă����ꍇ
    if (obj->renderer_->color_.w > 1.0f)
    {
        obj->renderer_->color_.w = 1.0f;
        return true;
    }

    // �����x1.0�����Ȃ瑝��
    if (obj->renderer_->color_.w <= 1.0f)
    {
        obj->renderer_->color_.w += fadeSpeed;
        // ���ߏC��
        if (obj->renderer_->color_.w > 1.0f)
            obj->renderer_->color_.w = 1.0f;
    }

    // �����x1.0�ɂȂ�����true��Ԃ�
    if (obj->renderer_->color_.w == 1.0f)
    {
        return true;
    }

    return false;
}

bool Title::objShrink()
{
    const float fadeSpeed = 0.01f;

    // Y��
    if (player_->renderer_->drawScale_.y >= 1.0f)
    {
        player_->renderer_->drawScale_.y -= fadeSpeed;
        // ���ߏC��
        if (player_->renderer_->drawScale_.y < 1.0f)
            player_->renderer_->drawScale_.y = 1.0f;
    }

    // X��
    if (player_->renderer_->drawScale_.x >= 1.0f)
    {
        player_->renderer_->drawScale_.x -= fadeSpeed;
        // ���ߏC��
        if (player_->renderer_->drawScale_.x < 1.0f)
            player_->renderer_->drawScale_.x = 1.0f;
    }

    // �����Ƃ�scale��1.0f�ɂȂ�����true�����Ԃ�
    if (
        (player_->renderer_->drawScale_.y == 1.0f)
        && (player_->renderer_->drawScale_.x == 1.0f)
        )
    {
        return true;
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
        if (objFadeOut(userHintMove_, 0.05f))
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
        objFadeIn(userHintMove_, 0.01f);
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
        if (objFadeOut(userHintShot_, 0.05f))
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
        objFadeIn(userHintShot_, 0.01f);
    }
}