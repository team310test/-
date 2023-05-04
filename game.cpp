#include "all.h"

Game Game::instance_;

void Game::init()
{
    Scene::init();	    // ���N���X��init���Ă�

    obj2dManager_   = new OBJ2DManager;
    bg_             = new BG;
    stage_          = new Stage;

    isPaused_ = false;   // �|�[�Y�t���O�̏�����

    isGameOver_ = false;
}


void Game::deinit()
{
    // �e�}�l�[�W���̉��
    safe_delete(stage_);
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    player_ = nullptr;

    // �e�N�X�`���̉��
    GameLib::texture::releaseAll();

    // ���y�̃N���A
    GameLib::music::clear();
}

int num = 2;

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
        BasePlayerBehavior::plShrinkCount_ = 0;
        Stage::resetShrinkNum();

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        GameLib::texture::load(loadTexture);

        // �v���C���[�}�l�[�W���̏�����
        obj2dManager()->init();

        // �v���C���[��ǉ�����
        setPlayer(obj2dManager(), bg(),takeOverPos_,takeOverScale_, takeOverIsDrawShrink_, true); // true�Ȃ炱��obj��player_�ɑ������

        //// �J�[�\���ǉ�(��)
        //setCursor(obj2dManager(), bg());

        bg()->init(); // BG�̏�����

        UI::init();

        ++state_;    // �����������̏I��
        /*fallthrough*/
    case 1:
        //////// �ʏ펞�̏��� ////////

        // �G�ǉ�4
        //if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG2)
        //{
        //    addEnemy(obj2dManager(), bg());
        //    ++num;
        //}

        // debug::setString
        {
            //GameLib::debug::setString("num:%d", num);
            //if (player_->transform_) GameLib::debug::setString("playerScale:%f", player_->transform_->scale_.x);
            GameLib::debug::setString("shrinkNum_:%d",stage_->getSrinkNum());
            //GameLib::debug::setString("plShrinkCount_:%d", BasePlayerBehavior::plShrinkCount_);
        }


        if (BasePlayerBehavior::plShrinkCount_ >= BasePlayerBehavior::PL_SHRINK_COUNT_MAX)  // �v���C���[�̐���Shrink�̋K�萔�ɒB������
        {
            if (Collider::isAllShrink_  == false && // Shrink���J�n����Ă��炸�A
                Behavior::isObjShrink() == false)   // ���ׂĂ�obj���k�����Ă��Ȃ����
            {
                Collider::isAllShrink_ = true;      // Shrink���J�n

                bg()->BG::setBGShrink();       // �w�i�̏k���ݒ�

                stage_->addSrinkNum();

            }
        }

        // �I�u�W�F�N�g�̍X�V
        obj2dManager()->update();

        
        if (Behavior::isObjShrink() == false) // ���ׂĂ�obj���k���I�����Ă����
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
            Behavior::shrinkVelocity_               += (-SHRINK_SPEED)  * 0.015f;
            PlayerPartsBehavior::toCoreVelocity_    += (-TO_CORE_SPEED) * 0.015f;
            BaseEnemyPartsBehavior::toCoreVelocity_ += (-TO_CORE_SPEED) * 0.015f;
            UI::letterBox_multiplySizeY_ = std::max(0.75f, UI::letterBox_multiplySizeY_ + LETTER_BOX_SUB_SPEED); // 0.0f��菬�������0.0f�ɏC��
        }
        else // ���ׂĂ�obj���k�����Ă��Ȃ����
        {
            Behavior::shrinkVelocity_               = SHRINK_SPEED;
            PlayerPartsBehavior::toCoreVelocity_    = TO_CORE_SPEED;
            BaseEnemyPartsBehavior::toCoreVelocity_ = TO_CORE_SPEED;
            UI::letterBox_multiplySizeY_ = std::min(1.0f, UI::letterBox_multiplySizeY_ + LETTER_BOX_ADD_SPEED); // 1.0f���傫�����1.0f�ɏC��
        }

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


    // �I�u�W�F�N�g�̕`��
    obj2dManager()->draw();

    // �h���b�v�p�[�c�𖾖ł�����
    drawblink();


    // �k���J�E���g���[�^�[�̕`��
    UI::drawShrinkValueMeter();

    // �f��̍��т̕`��
    UI::drawLetterBox();
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
