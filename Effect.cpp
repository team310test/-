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


// obj�̎��͂ɃG�t�F�N�g��A���I�ɔ���������֐�
bool ChainEffect(OBJ2D* obj)
{
    // �A���I�ɃG�t�F�N�g�𗬂����߂̃f�[�^
    ChainEffectData chainEffectData[] =
    {
        {0,&efcBombBehavior,{0.0f,0.0f}}
        ,{20,&efcBombBehavior,{-100.0f,-100.0f}}
        ,{40,&efcBombBehavior,{100.0f,-100.0f}}
        ,{60,&efcBombBehavior,{-100.0f,100.0f}}
        ,{80,&efcBombBehavior,{100.0f,100.0f}}

        ,{0,nullptr,{0.0f,0.0f}}
    };

    static int Timer = 0;
    static ChainEffectData* data = nullptr;
    if (!data)data = chainEffectData;


    while (data->behavior_ && data->time_ == Timer)
    {
        AddObj::addEffect(obj, data->behavior_, data->add_);
        ++data;
    }
    ++Timer;

    // behavior��nullptr�Ȃ�
    if (!data->behavior_)
    {
        Timer = 0;
        data = nullptr;
        return true;
    }
    return false;
}
