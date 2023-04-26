#include "all.h"

#define X BG::WINDOW_W + 256.0f

// addition_(�ǉ��ϐ�)�͏ȗ��ł���
STAGE_SCRIPT stageData01[] =
{
    SET_ENEMY_TARGET_X(180,enemy02, X,800.0f, 5.0f,0.0f, 1000.0f, 10.0f,-5.0f),
    SET_ENEMY_LENE(360,enemy01, X,300.0f, 5.0f),
    SET_ENEMY_END
};

Stage::Stage()
    : timer()
    , pScript(nullptr)
{
    pScript = stageData01;
}

void Stage::update(OBJ2DManager* obj2dManager, BG* bg)
{
    while (pScript->enemyData_ && pScript->time_ == timer)
    {
        OBJ2D* orgParent = nullptr;
        OBJ2D* Parent[10] = {};
        while (pScript->enemyData_ && pScript->enemyData_->behavior_)
        {
            // 0�Ԗڂł͂Ȃ�Parent��parentNo�Ԗڂ�nullptr�Ȃ�
            if(pScript->enemyData_->no_ != 0 && !Parent[pScript->enemyData_->parentNo_])
                assert(!"parent[parentNo]��nullptr�ł�");
            // parentNo��0�ȉ����ƃG���[��f��
            if(pScript->enemyData_->parentNo_ < PARENT_NO::PARENT0) assert(!"parentNo���g�p�ł��Ȃ��l�ł�");
            
            VECTOR2 pos = { pScript->pos_.x + pScript->enemyData_->pos_.x, pScript->pos_.y + pScript->enemyData_->pos_.y };
            
            OBJ2D* hold =
            setEnemy
            (
                obj2dManager
                , bg
                , pos
                , pScript->enemyData_->behavior_
                , pScript->update_
                , Parent[pScript->enemyData_->parentNo_]
                , orgParent
                , pScript->enemyData_->zOrder_
                , pScript->addition_
            );
            // ���x�E�ǉ��p�����[�^�ݒ�
            hold->actorComponent_->accel_ = pScript->accel_;
            hold->actorComponent_->addition_ = pScript->addition_;

            if (!orgParent) orgParent = hold;                           // orgParent��nullptr�Ȃ猳�̐e��ݒ肷��
            
            // no��-1���傫��������
            if (pScript->enemyData_->no_ > -1)
            {
                // Parent��no�Ԗڂɒl�������Ă����
                if (Parent[pScript->enemyData_->no_])assert(!"parent���㏑�����悤�Ƃ��Ă��܂�");

                Parent[pScript->enemyData_->no_] = hold;                    // no�Ԗڂ�Parent��ݒ�
            }

            pScript->enemyData_++;
        }
        pScript->DataReset();   // enemyData��擪�ɖ߂�
        pScript++;
    }

    ++timer;

    // �Ō�̓G���o������ƃ��[�v����
    if (!pScript->enemyData_)
    {
        timer = 0;
        pScript = stageData01;
    }
}