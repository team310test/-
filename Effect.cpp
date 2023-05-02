#include "all.h"

namespace 
{
    GameLib::AnimeData animeEfcBomb[] = {
        { &sprEfcBomb_anime0,  2  },
        { &sprEfcBomb_anime1,  2  },
        { &sprEfcBomb_anime2,  2  },
        { &sprEfcBomb_anime3,  3  },
        { nullptr,            -1  },    // �I���t���O
    };
}


//******************************************************************************
//
//      BaseEffectBehavior�i�G�t�F�N�g�̃x�[�X�j
//
//******************************************************************************
void BaseEffectBehavior::move(OBJ2D* obj) const
{
    Collider*  c = obj->collider_;
    Renderer*  r = obj->renderer_;

    switch (obj->state_)
    {
    case 0:
        r->animeData_   = getParam()->ANIME;

        c->judgeFlag_           = false;    // �����蔻����s��Ȃ�
        c->isDrawAttackRect_    = false;    // �����蔻��̗̈��`�悵�Ȃ�

        ++obj->state_;
        /*fallthrough*/
    case 1:
        update(obj);        

        break;
    }
}

void BaseEffectBehavior::update(OBJ2D* obj) const
{
    Renderer* r = obj->renderer_;

    // ���X�ɔ�������
    //float addColor = -0.04f;
    //r->color_ = {
    //    r->color_.x + addColor, r->color_.y + addColor, 
    //    r->color_.z + addColor, r->color_.w + addColor
    //};
    //r->targetColor_ = r->color_;

    if (!r->animeData_) return; // �A�j���f�[�^���Ȃ����return

    // �A�j�������؂��������
    if (r->animeUpdate()) obj->behavior_ = nullptr;

}


//******************************************************************************
//      EffectBombBehavior�i�����G�t�F�N�g�j
//******************************************************************************
EffectBombBehavior::EffectBombBehavior()
{
    param_.ANIME = animeEfcBomb;
}
