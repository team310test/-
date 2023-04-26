#include "all.h"

#define X BG::WINDOW_W + 256.0f

// addition_(�ǉ��ϐ�)�͏ȗ��ł���
STAGE_SCRIPT stageData01[] =
{
    SET_ENEMY_TARGET_X(180,enemy02, X,800.0f, 5.0f,0.0f, 1000.0f, 10.0f,-5.0f),
    SET_ENEMY_LENE(360,enemy01, X,300.0f, 5.0f),
    SET_ENEMY_END
};
STAGE_SCRIPT stageData02[] =
{
    SET_ENEMY_LENE(520,enemy01, X,300.0f, 10.0f),
    SET_ENEMY_LENE(520,enemy01, X,900.0f, 10.0f),
    SET_ENEMY_LENE(700,enemy01, X,500.0f, 5.0f),
    SET_ENEMY_END
};

STAGE_SCRIPT* STAGE_DATA[] =
{
    stageData01,
    stageData02,
};

Stage::Stage()
    : timer_()
    , pScript_(nullptr)
    , stageNum_()
{
    pScript_ = STAGE_DATA[stageNum_];
}
int Stage::shrinkNum = 0;
//#define error

void Stage::update(OBJ2DManager* obj2dManager, BG* bg)
{
    // timer�\��
    GameLib::debug::setString("timer:%d", timer_);

    // �X�e�[�W�J��
    if (stageNum_ != shrinkNum)
    {
        if (shrinkNum > 0 && shrinkNum < stageMax)
        {
            timer_ = 0;
            pScript_ = STAGE_DATA[stageNum_];
        }
#ifdef error
        else
        {
            assert(!"shrinkNum�Ɉُ�Ȓl�������Ă��܂�");
        }
#endif
        stageNum_ = shrinkNum;
    }

    // �G�o��
    while (pScript_->enemyData_ && pScript_->time_ == timer_)
    {
        OBJ2D* orgParent = nullptr;
        OBJ2D* Parent[10] = {};
        while (pScript_->enemyData_ && pScript_->enemyData_->behavior_)
        {
            // 0�Ԗڂł͂Ȃ�Parent��parentNo�Ԗڂ�nullptr�Ȃ�
            if(pScript_->enemyData_->no_ != 0 && !Parent[pScript_->enemyData_->parentNo_])
                assert(!"parent[parentNo]��nullptr�ł�");
            // parentNo��0�ȉ����ƃG���[��f��
            if(pScript_->enemyData_->parentNo_ < PARENT_NO::PARENT0) 
                assert(!"parentNo���g�p�ł��Ȃ��l�ł�");
            
            VECTOR2 pos = { pScript_->pos_.x + pScript_->enemyData_->pos_.x, pScript_->pos_.y + pScript_->enemyData_->pos_.y };
            
            OBJ2D* hold =
            setEnemy
            (
                obj2dManager
                , bg
                , pos
                , pScript_->enemyData_->behavior_
                , pScript_->update_
                , Parent[pScript_->enemyData_->parentNo_]
                , orgParent
                , pScript_->enemyData_->zOrder_
                , pScript_->addition_
            );
            // ���x�E�ǉ��p�����[�^�ݒ�
            hold->actorComponent_->accel_ = pScript_->accel_;
            hold->actorComponent_->addition_ = pScript_->addition_;

            if (!orgParent) orgParent = hold;                           // orgParent��nullptr�Ȃ猳�̐e��ݒ肷��
            
            // no��-1���傫��������
            if (pScript_->enemyData_->no_ > -1)
            {
                // Parent��no�Ԗڂɒl�������Ă����
                if (Parent[pScript_->enemyData_->no_])assert(!"parent���㏑�����悤�Ƃ��Ă��܂�");

                Parent[pScript_->enemyData_->no_] = hold;                    // no�Ԗڂ�Parent��ݒ�
            }

            pScript_->enemyData_++;
        }
        pScript_->DataReset();   // enemyData��擪�ɖ߂�
        pScript_++;
    }

    ++timer_;

    // �Ō�̓G���o������ƃ��[�v����
    if (!pScript_->enemyData_)
    {
        timer_ = 0;
        pScript_ = STAGE_DATA[stageNum_];
    }
}