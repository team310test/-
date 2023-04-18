#include "all.h"

// �G��Turret01�̂Ƃ��ō���ɓG������Ƃ��ɒe��łƏ�����

//******************************************************************************
//
//      BaseShotBehavior�i�e�̃x�[�X�j
//
//******************************************************************************
void BaseShotBehavior::move(OBJ2D* obj) const
{
    switch (obj->state_)
    {
    case 0:
        //////// �����ݒ� ////////
        obj->renderer_->data_ = getParam()->SPR_WEAPON;

        //obj->transform_->scale_ = getParam()->SCALE;
        obj->transform_->scale_ = obj->weaponComponent_->parent_->transform_->scale_;

        obj->eraser_ = getParam()->ERASER;
        obj->collider_->judgeFlag_ = true;      // �����蔻����s��
        obj->collider_->isDrawAttackRect_ = true;  // �����蔻��̗̈��`�悷��i�f�o�b�O�p�j

        // ���E�̌����A���x��ݒ�i�v���C���[�ɂ�xFlip_�̐ݒ肪�K�v�j
        obj->transform_->velocity_.x =  getParam()->SPEED_X;
        obj->transform_->velocity_.y = 0.0f;    // �O�̂���

        ++obj->state_;
        /*fallthrough*/
    case 1:
        //////// �ʏ펞 ////////

        update(obj);        // ����̈ʒu�X�V

        break;
    }
        
    calcAttackBox(obj); // �����蔻��̍X�V
}

void BaseShotBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    // hp����U���͂��������l��0��菬����������0�ɏC���A�����łȂ����hp����U��������
    dst->actorComponent_->hp_ = std::max(
        dst->actorComponent_->hp_ - getParam()->ATTACK_POWER, 0
    );

    src->behavior_ = nullptr; // �e������
}

// �k���ɔ����Ēe�̑傫���̍X�V���K�v
void BaseShotBehavior::calcAttackBox(OBJ2D* obj) const
{
    // �U������̌v�Z
    for (int i = 0; i < Collider::boxMax; ++i)
    {
        obj->collider_->calcAttackBox(getParam()->ATTACK_BOX[i], i);
    }
}


//******************************************************************************
//
//      NormalShotBehavior�i�m�[�}���e�j
//
//******************************************************************************

// �v���C���[
PlayerNormalShotBehavior::PlayerNormalShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER     = &eraseShot;

    param_.SPEED_X = 30.0f;
    param_.ATTACK_POWER = 1;

    // �ύX�\��
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };

}

void PlayerNormalShotBehavior::update(OBJ2D* obj) const
{
    // �ʒu�ɑ��x�𑫂�
    obj->transform_->position_ += obj->transform_->velocity_;
}


//******************************************************************************
//
//      SinShotBehavior�i�g�`�ړ��e�j
//
//******************************************************************************

// �v���C���[
PlayerWaveShotBehavior::PlayerWaveShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = 20.0f;
    param_.ATTACK_POWER = 1;

    // �ύX�\��
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };
}

static constexpr float SIN_YOFS = 64.0f;  // �U�ꕝ
void PlayerWaveShotBehavior::update(OBJ2D* obj) const
{
    Transform* transform = obj->transform_;

    switch (obj->act_) 
    {
    case 0: // �����ʒu��ۑ�
        transform->orgPosition_ = transform->position_; // �����ʒu��ۑ�

#if 1
        obj->act_ = 2;
        break;
#else
        ++obj->act_;
        /*fallthrough*/
    case 1: // �g�`�ړ�����O�ɏ����O�ɐi��
        if (transform->position_.x > transform->orgPosition_.x + 200) // �����ʒu���炵�΂炭�i�񂾂�act�i�s
        {
            transform->orgPosition_.y = transform->position_.y;	// Y���W�𒆐S���Ƃ���
            ++obj->act_;
            break;
        }

        break;
#endif
    case 2: // �g�`�ړ��̑O����
        transform->velocity_.y += 2.0f; // �U�ꕝ�̕��܂ŏ��X�ɂ��炷

        if (transform->position_.y >= transform->orgPosition_.y + SIN_YOFS) // �U�ꕝ�̕�����Y���W�����炵����
        {
            ++obj->act_;
            break;
        }

        break;
    case 3: // �g�`�ړ�
        transform->velocity_.y += (transform->orgPosition_.y - transform->position_.y) / 128.0f;

        break;
    }

    transform->position_ += transform->velocity_; // �ʒu�ɑ��x�𑫂�

}


//******************************************************************************
//
//      erase�i�����j
//
//******************************************************************************
void ShotEraser::erase(OBJ2D* obj) const
{
    const VECTOR2* size = &obj->collider_->size_;
    const VECTOR2* pos = &obj->transform_->position_;

    const float leftLimit = size->x;
    const float rightLimit = BG::WINDOW_W + size->x;
    const float topLimit = size->y;
    const float bottomLimit = BG::WINDOW_H + size->y;

    if (pos->x < leftLimit ||
        pos->x > rightLimit ||
        pos->y < topLimit ||
        pos->y > bottomLimit)
    {
        obj = nullptr; // ��ʊO�ɍs���������
    }
}