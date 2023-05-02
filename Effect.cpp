#include "all.h"

namespace
{
    GameLib::AnimeData animeEfcBomb[] = {
        { &sprEfcBomb_anime0,  10 },
        { &sprEfcBomb_anime1,  10 },
        { &sprEfcBomb_anime2,  10 },
        { nullptr,      -1 },    // �I���t���O
    };
}


//******************************************************************************
//
//      BaseEffectBehavior�i�G�t�F�N�g�̃x�[�X�j
//
//******************************************************************************
void BaseEffectBehavior::move(OBJ2D* obj) const
{
    Collider* c = obj->collider_;
    Renderer* r = obj->renderer_;

    switch (obj->state_)
    {
    case 0:
        r->animeData_ = getParam()->ANIME;

        c->judgeFlag_ = false;    // �����蔻����s��Ȃ�
        c->isDrawAttackRect_ = false;    // �����蔻��̗̈��`�悵�Ȃ�

        ++obj->state_;
        /*fallthrough*/
    case 1:
        startAllShrink(obj);    // �k���J�n
        shrink(obj);            // �摜�k��

        //if (c->isShrink_) break; // �k�����Ȃ��΂�


        // �X�V
        update(obj);

        r->animeData_ = param_.ANIME;
        // �A�j���[�V�����X�V(�A�j���[�V�������I������Ǝ��g���폜����)
        if (r->animeData_) if (r->animeUpdate())obj->behavior_ = nullptr;

        break;
    }
}


//******************************************************************************
//      EffectBombBehavior�i�����G�t�F�N�g�j
//******************************************************************************
EffectBombBehavior::EffectBombBehavior()
{
    param_.ANIME = animeEfcBomb;
}

void EffectBombBehavior::update(OBJ2D* obj) const
{
    //if (obj->renderer_->animeData_->data == nullptr)
    //{
    //    obj->behavior_ = nullptr;
    //}
}