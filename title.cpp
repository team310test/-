#include "all.h"

Title Title::instance_;
bool Title::isFallPerform_ = false;

void Title::init()
{
    Scene::init();
    isFallPerform_ = false;

    obj2dManager_ = new OBJ2DManager;
    bg_ = new BG;
}

void Title::deinit()
{
    safe_delete(bg_);
    safe_delete(obj2dManager_);

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

        //setPlayer(obj2dManager(), bg(), true); // true�Ȃ炱��obj��player_�ɑ������
        setTitlePlayer(obj2dManager(),bg(),true);
        
        bg()->init();

        state_++;                                    // �����������̏I��
        /*fallthrough*/                             // �Ӑ}�I��break;���L�q���Ă��Ȃ�

    case 1:
        //////// �ʏ펞�̏��� ////////

        if (GameLib::input::TRG(0) & GameLib::input::PAD_START)             // PAD_TRG1�������ꂽ��
            changeScene(Game::instance());  // �Q�[���V�[���ɐ؂�ւ�

        // �������o�����Ă��Ȃ�������
        if (isFallPerform_);

        obj2dManager()->update();           // �I�u�W�F�N�g�X�V
        bg()->update();                     // BG�̍X�V

        ++timer_;                           // �^�C�}�[�𑫂�
        break;
    }
}

void Title::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.0f, 1.0f, 0.0f, 1));

    // �I�u�W�F�N�g�̕`��
    obj2dManager()->draw();
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