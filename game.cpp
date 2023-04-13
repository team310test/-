//******************************************************************************
//
//
//      �Q�[��
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//------< �ϐ� >----------------------------------------------------------------
Game Game::instance_;

//--------------------------------------------------------------
//  ����������
//--------------------------------------------------------------
void Game::init()
{
    Scene::init();	    // ���N���X��init���Ă�

    obj2dManager_   = new OBJ2DManager;
    bg_             = new BG;

    isPaused_ = false;   // �|�[�Y�t���O�̏�����

    isGameOver_ = false;
}

//--------------------------------------------------------------
//  �I������
//--------------------------------------------------------------
void Game::deinit()
{
    // �e�}�l�[�W���̉��
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    player_ = nullptr;

    // �e�N�X�`���̉��
    GameLib::texture::releaseAll();

    // ���y�̃N���A
    GameLib::music::clear();
}

int num = 2;
int shrinkNum = 0;

//--------------------------------------------------------------
//  �X�V����
//--------------------------------------------------------------
void Game::update()
{
    // �\�t�g���Z�b�g
    if ((GameLib::input::STATE(0) & GameLib::input::PAD_SELECT) &&  // 0�R���̃Z���N�g�{�^����������Ă����Ԃ�
        (GameLib::input::TRG(0) & GameLib::input::PAD_START))       // 0�R���̃X�^�[�g�{�^���������ꂽ�u��
    {
        changeScene(Title::instance());   // �^�C�g���V�[���ɐ؂�ւ���
        return;
    }

    // �|�[�Y����
    //if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
    //    isPaused_ = !isPaused_;       // 0�R���̃X�^�[�g�{�^���������ꂽ��|�[�Y��Ԃ����]
    //if (isPaused_) return;           // ���̎��_�Ń|�[�Y���Ȃ烊�^�[��

    switch (state_)
    {
    case 0:
        //////// �����ݒ� ////////
        timer_ = 0;
        num = 2;
        BasePlayerBehavior::plShrinkCount = 0;

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        GameLib::texture::load(loadTexture);

        // �v���C���[�}�l�[�W���̏�����
        obj2dManager()->init();

        // �v���C���[��ǉ�����
        setPlayer(obj2dManager(), bg(), true); // true�Ȃ炱��obj��player_�ɑ������

        // �J�[�\���ǉ�(��)
        setCursor(obj2dManager(), bg());

        // �G�l�~�[��ǉ�����
        setEnemy(obj2dManager(), bg());

        bg()->init(player_); // BG�̏�����

        ++state_;    // �����������̏I��
        /*fallthrough*/
    case 1:
        //////// �ʏ펞�̏��� ////////

        // �G�ǉ�4
        if (GameLib::input::STATE(0) & GameLib::input::PAD_TRG2)
        {
            addEnemy(obj2dManager(), bg());
            ++num;
        }

        GameLib::debug::setString("num:%d", num);
        if (player_->transform_) GameLib::debug::setString("playerScale:%f", player_->transform_->scale_.x);
        GameLib::debug::setString("shrinkNum:%d", shrinkNum);
        GameLib::debug::setString("plShrinkCount:%d", BasePlayerBehavior::plShrinkCount);


        if (BasePlayerBehavior::plShrinkCount >= 10)     // �v���C���[�̐���Shrink�̋K�萔�ɒB���Ă���
        {
            if (Collider::isAllShrink_  == false &&       // Shrink���J�n����Ă��炸�A
                Behavior::isObjShrink() == false)         // ���ׂĂ�obj��shrink���łȂ����
            {
                Collider::isAllShrink_ = true;           // Shrink���J�n
                BasePlayerBehavior::plShrinkCount -= 10; // �v���C���[�̃J�E���g�����Z�b�g
                ++shrinkNum;
            }
        }

        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();

        // �I�u�W�F�N�g�̍X�V���Shrink�̊J�n���~�߂�
        if (Collider::isAllShrink_) Collider::isAllShrink_ = false; 


        // �Q�[���I�[�o�[�̏���
        if (isGameOver())
        {
            gameOverProc();
            break;
        }

        bg()->update();   // BG�̍X�V

        judge();

        ++timer_;
        break;
    }
}

//--------------------------------------------------------------
//  �`�揈��
//--------------------------------------------------------------
void Game::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.6f, 0.4f, 0.3f, 1));

    bg()->drawBack();     // �w�i�̕`��

    // �I�u�W�F�N�g�̕`��
    obj2dManager()->draw();
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

void Game::gameOverProc()
{
    gameOverTimer_--;
    if (gameOverTimer_ <= 0)
    {
        changeScene(Title::instance());
    }
}
//******************************************************************************
