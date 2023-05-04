#include "all.h"

namespace 
{
    // �����A�j��
    GameLib::AnimeData animeEfcBomb[] = {
        { &sprEfcBomb_anime0,  2  },
        { &sprEfcBomb_anime1,  2  },
        { &sprEfcBomb_anime2,  2  },
        { &sprEfcBomb_anime3,  3  },
        { nullptr,            -1  },    // �I���t���O
    };

    // ���̃A�j��
    GameLib::AnimeData animeEfcCombine[] = {
    { &sprEfcCombine_anime0,  4  },
    { &sprEfcCombine_anime1,  4  },
    { &sprEfcCombine_anime2,  4  },
    { &sprEfcCombine_anime3,  4  },
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
        r->animeData_ = getParam()->ANIME;

        c->judgeFlag_ = false;    // �����蔻����s��Ȃ�
        c->isDrawAttackRect_ = false;    // �����蔻��̗̈��`�悵�Ȃ�

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
    const float addColor = -0.04f;
    r->color_ = {
        r->color_.x + addColor, r->color_.y + addColor,
        r->color_.z + addColor, r->color_.w + addColor
    };
    r->targetColor_ = r->color_;

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

//******************************************************************************
//      EffectBombBehavior�i�����G�t�F�N�g�j
//******************************************************************************
EffectCombineBehavior::EffectCombineBehavior()
{
    param_.ANIME = animeEfcCombine;
}

void EffectCombineBehavior::update(OBJ2D* obj) const
{
    Transform* t       = obj->transform_;
    Transform* plCoreT = Game::instance()->player_->transform_;

    // �v���C���[�p�[�c�Ɠ��������ŃG�t�F�N�g��Ǐ]������  
    // �v���C���[�R�A�̑��x����
    t->velocity_ = plCoreT->velocity_;
    // �k�����łȂ���Έʒu�ɑ��x�𑫂�
    if (!Behavior::isObjShrink()) t->position_ += plCoreT->velocity_;

    // �A�j���[�V�����X�V
    BaseEffectBehavior::update(obj);
}
