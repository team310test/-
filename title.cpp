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


        obj2dManager()->update();           // �I�u�W�F�N�g�X�V
        bg()->update();                     // BG�̍X�V
        
        // ���o���I����Ă��Ȃ�������return
        if (isStatePerform_ && !statePerform()) return;

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
        static bool isAnime = false;
        // �L�[�������ƃA�j���[�V�����Đ�
        if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG3 && !isAnime) 
            isAnime = true;

        // �L�[��������A�j���[�V�������Đ��I���ƃJ�E���g�𑝂₷
        if (isAnime && xAxisSclaeAnime(player_))
        {
            ++pushCount_;
            isAnime = false;
        }

        // ���񐔃A�j���[�V��������ƃQ�[����ʂɑJ��
        if (pushCount_ >= 3)
        {

            bool fadeOut = objFadeOut();    // �t�F�[�h�A�E�g
            bool shrink = objShrink();      // �k��

            // �����̏����������������ʂ�J�ڂ���
            if (fadeOut && shrink)
            {
                takeOverPos_ = player_->transform_->position_;
                takeOverScale_ = player_->renderer_->drawScale_;
                takeOverIsDrawShrink_ = player_->renderer_->isDrawShrink_;
                changeScene(Game::instance());
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
    if (player_->titleComponent_->isTrigger)
    {
        // �t�F�[�h�C��������treu��Ԃ�
        if (objFadeIn())
        {
            // player��update�ύX
            if (player_->update_ != PLAYER_CORE_UPDATE) player_->update_ = PLAYER_CORE_UPDATE;
            isStatePerform_ = false;
            return true;
        }
    }

    return false;
}

bool Title::objFadeOut()
{
    const float fadeSpeed = 0.01f;

    if (endCommand_->renderer_->color_.w >= 0)
    {
        endCommand_->renderer_->color_.w -= fadeSpeed;
        // ���ߏC��
        if(endCommand_->renderer_->color_.w < 0)
            endCommand_->renderer_->color_.w = 0.0f;
    }
    if (titleLoge_->renderer_->color_.w >= 0)
    {
        titleLoge_->renderer_->color_.w -= fadeSpeed;
        // ���ߏC��
        if (titleLoge_->renderer_->color_.w < 0)
            titleLoge_->renderer_->color_.w = 0.0f;
    }

    // �S�ē����ɂȂ�����treu��Ԃ�
    if (
        (endCommand_->renderer_->color_.w == 0)
        && (titleLoge_->renderer_->color_.w == 0)
        )
    {
        return true;
    }

    return false;
}

bool Title::objFadeIn()
{
    const float fadeSpeed = 0.01f;

    if (stateCommand_->renderer_->color_.w <= 1.0f)
    {
        stateCommand_->renderer_->color_.w += fadeSpeed;
        // ���ߏC��
        if (stateCommand_->renderer_->color_.w > 1.0f)
            stateCommand_->renderer_->color_.w = 1.0f;
    }
    if (endCommand_->renderer_->color_.w <= 1.0f)
    {
        endCommand_->renderer_->color_.w += fadeSpeed;
        // ���ߏC��
        if (endCommand_->renderer_->color_.w > 1.0f)
            endCommand_->renderer_->color_.w = 1.0f;
    }
    if (titleLoge_->renderer_->color_.w <= 1.0f)
    {
        titleLoge_->renderer_->color_.w += fadeSpeed;
        // ���ߏC��
        if (titleLoge_->renderer_->color_.w > 1.0f)
            titleLoge_->renderer_->color_.w = 1.0f;
    }

    // �S�ăt�F�[�h�C��������treu��Ԃ�
    if (
        (endCommand_->renderer_->color_.w == 1.0f)
        && (titleLoge_->renderer_->color_.w == 1.0f)
        )
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
