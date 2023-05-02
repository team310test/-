#include "all.h"

//******************************************************************************
//
//      BaseEffectBehavior�i�G�t�F�N�g�̃x�[�X�j
//
//******************************************************************************
void BaseEffectBehavior::move(OBJ2D* obj) const
{
    switch (obj->state_)
    {
    case 0:
        obj->renderer_->animeData_   = getParam()->ANIME;
        obj->transform_->scale_ = obj->weaponComponent_->parent_->transform_->scale_;

        obj->collider_->judgeFlag_          = false;    // �����蔻����s��Ȃ�
        obj->collider_->isDrawAttackRect_   = false;    // �����蔻��̗̈��`�悵�Ȃ�

        ++obj->state_;
        /*fallthrough*/
    case 1:
        startAllShrink(obj);    // �k���J�n
        shrink(obj);            // �摜�k��

        if (obj->collider_->isShrink_) break; // �k�����Ȃ��΂�

        // �ʒu�X�V
        update(obj);        

        // �A�j���[�V�����X�V
        if (obj->renderer_->animeData_) obj->renderer_->animeUpdate();

        break;
    }
}


//******************************************************************************
//      EffectBombBehavior�i�����G�t�F�N�g�j
//******************************************************************************
EffectBombBehavior::EffectBombBehavior()
{
    //param_.ANIME = spr;
}

void EffectBombBehavior::update(OBJ2D* obj) const
{
    //EffectComponent* e = obj->effectComponent_;
}
