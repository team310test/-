#include "all.h"


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
        obj->renderer_->drawScale_ = obj->weaponComponent_->parent_->transform_->scale_;

        obj->eraser_ = getParam()->ERASER;
        obj->collider_->judgeFlag_ = true;      // �����蔻����s��
        obj->collider_->isDrawAttackRect_ = true;  // �����蔻��̗̈��`�悷��i�f�o�b�O�p�j

        // ���E�̌����A���x��ݒ�i�v���C���[�ɂ�xFlip_�̐ݒ肪�K�v�j
        obj->transform_->velocity_.x = getParam()->SPEED_X;
        obj->transform_->velocity_.y = getParam()->SPEED_Y;


        // �摜�̌�����ݒ�
        obj->renderer_->drawXFlip_ = obj->weaponComponent_->parent_->renderer_->drawXFlip_;

        ++obj->state_;
        /*fallthrough*/
    case 1:
        //////// �ʏ펞 ////////

        startAllShrink(obj);    // �k���J�n
        shrink(obj);            // �摜�k��

        if (obj->collider_->isShrink_) break; // �k�����Ȃ��΂�

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
//      NormalShot�i�ʏ�e�j
//
//******************************************************************************

// �v���C���[
PlayerNormalShotBehavior::PlayerNormalShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER     = &eraseShot;

    param_.SPEED_X      = PL_NORMAL_SHOT_SPEED;
    param_.ATTACK_POWER = PL_NORMAL_SHOT_ATK;

    // �ύX�\��
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };

}

void PlayerNormalShotBehavior::update(OBJ2D* obj) const
{
    // �ʒu�ɑ��x�𑫂�
    obj->transform_->position_ += obj->transform_->velocity_;
}


// �G�l�~�[
EnmNormalShotBehavior::EnmNormalShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = 30.0f;
    param_.ATTACK_POWER = 1;

    // �ύX�\��
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };
}

void EnmNormalShotBehavior::update(OBJ2D* obj) const
{
    // �ʒu�ɑ��x�𑫂�
    obj->transform_->position_ -= obj->transform_->velocity_;
}


//******************************************************************************
//
//      SineWaveShot�i�����g�e�j
//
//******************************************************************************

// �v���C���[
PlSineWaveShotBehavior::PlSineWaveShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = 20.0f;
    param_.ATTACK_POWER = 1;

    // �ύX�\��
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };
}

static constexpr float SIN_YOFS = 64.0f;  // �U�ꕝ
void PlSineWaveShotBehavior::update(OBJ2D* obj) const
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

        // �U�ꕝ�̕�����Y���W�����炵����
        if (transform->position_.y >= transform->orgPosition_.y + (SIN_YOFS * transform->scale_.y) ) // scale�ɋ��������킹��
        {
            ++obj->act_;
            break;
        }

        break;
    case 3: // �g�`�ړ�
        transform->velocity_.y += 
            (transform->orgPosition_.y - transform->position_.y) / (128.0f * transform->scale_.y); // scale�ɋ��������킹��

        break;
    }

    transform->position_ += transform->velocity_; // �ʒu�ɑ��x�𑫂�

}


//******************************************************************************
//
//      SquareWaveShot�i��`�g�e�j
//
//******************************************************************************

// �v���C���[
PlSquareWaveShotBehavior::PlSquareWaveShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = 40.0f;
    param_.SPEED_Y = 20.0f;
    param_.ATTACK_POWER = 1;

    // �ύX�\��
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };
}

static constexpr float SQUARE_WAVE_SHOT_POSX_LIMIT = 300.0f; // ��x�ɑO�ɐi�߂鋗��
static constexpr float SQUARE_WAVE_SHOT_POSY_LIMIT = 75.0f;  // �㉺�ړ��ł�����E
void PlSquareWaveShotBehavior::update(OBJ2D* obj) const
{
    Transform* transform = obj->transform_;

    switch (obj->act_)
    {
    case 0: // ���݈ʒu��ۑ�
        transform->orgPosition_ = transform->position_; // ���݈ʒu��ۑ�

        ++obj->act_;
        /*fallthrough*/
    case 1: // �O�ɐi�ށiX�ړ��j
        transform->position_.x += transform->velocity_.x; //�@X�ʒu��X���x�𑫂�

        // orgX�ʒu���炵�΂炭�i�񂾂�
        if (transform->position_.x > transform->orgPosition_.x + (SQUARE_WAVE_SHOT_POSX_LIMIT * transform->scale_.x) ) // scale�ɋ��������킹��
        {
            ++obj->act_; // act�i�s
            break;
        }

        break;
    case 2: // ��A�܂��͉��Ɉړ��iY�ړ��j
        transform->position_.y += transform->velocity_.y; // Y�ʒu��Y���x�𑫂�

        // orgY�ʒu+�����Y�ʒu����������A�܂��͏������ꍇ
        if (transform->position_.y < transform->orgPosition_.y - (SQUARE_WAVE_SHOT_POSY_LIMIT * transform->scale_.x) || // scale�ɋ��������킹��
            transform->position_.y > transform->orgPosition_.y + (SQUARE_WAVE_SHOT_POSY_LIMIT * transform->scale_.y) )
        {
            transform->velocity_.y = -transform->velocity_.y;   // Y���x�𔽓]
            transform->orgPosition_.x = transform->position_.x; // ���݂�X�ʒu��ۑ�

            --obj->act_;  // act��߂�
            break;
        }

        break;
    }

}


//******************************************************************************
//
//      CurveShot�i�J�[�u�e�j
//
//******************************************************************************

// �v���C���[
PlCurveShotBehavior::PlCurveShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = -20.0f;
    param_.SPEED_Y = -25.0f;
    param_.ATTACK_POWER = 1;

    // �ύX�\��
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };

}

static constexpr float CURVE_SHOT_ACCEL_X = 1.4f; // X���x�ɑ���X�����x
static constexpr float CURVE_SHOT_ACCEL_Y = 0.9f; // Y���x�ɑ���Y�����x
void PlCurveShotBehavior::update(OBJ2D* obj) const
{
    Transform* transform = obj->transform_;

    transform->position_ += transform->velocity_; // �ʒu�ɑ��x�𑫂�

    // ���x�ɉ����x�𑫂�
    transform->velocity_ += {
        CURVE_SHOT_ACCEL_X / transform->scale_.x,  // scale�ɋ��������킹��
        CURVE_SHOT_ACCEL_Y / transform->scale_.y,  // scale�ɋ��������킹��
    };  

}

//******************************************************************************
//
//      CurveShot�i�J�[�u�e�j
//
//******************************************************************************

// �v���C���[
PlPenetrateShotBehavior::PlPenetrateShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = 100.0f;
    param_.ATTACK_POWER = 1;

    // �ύX�\��
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };

}

void PlPenetrateShotBehavior::update(OBJ2D* obj) const
{
    Transform* transform = obj->transform_;

    switch (obj->act_)
    {
    case 0: // X���x�𗎂Ƃ�
        transform->velocity_.x *= 0.8f;

        // �e���قڎ~�܂�����ԂɂȂ�����
        if (transform->velocity_.x <= 0.05f)
        {
            // ���x����
            transform->velocity_.x += param_.SPEED_X / transform->scale_.x;  // scale�ɋ��������킹��  
            ++obj->act_;
            break;
        }
        break;

    case 1: // �����ړ�

        break;
    }

    //transform->position_ += transform->velocity_; // �ʒu�ɑ��x�𑫂�
    transform->position_ +=
    {
        transform->velocity_.x * obj->transform_->scale_.x, // �ʒu�ɑ��x�𑫂�
        transform->velocity_.y * obj->transform_->scale_.y, // �ʒu�ɑ��x�𑫂�
    };
}


//******************************************************************************
//
//      AimShot�i�v���C���[�_���e�j
//
//******************************************************************************

// �G�l�~�[
EnmAimShotBehavior::EnmAimShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER     = &eraseShot;

    param_.SPEED_X = 20.0f;
    param_.SPEED_Y = 20.0f;
    param_.ATTACK_POWER = 1;

    // �ύX�\��
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };
}

void EnmAimShotBehavior::update(OBJ2D* obj) const
{
    // �ȗ�
    Transform* t = obj->transform_;
    Transform* corePl = Game::instance()->player_->transform_;

    switch (obj->act_) 
    {
    case 0:
        {
            const VECTOR2 d  = corePl->position_ - t->position_;
            const float dist = sqrtf(d.x * d.x + d.y * d.y);

            t->velocity_ = {
                param_.SPEED_X * d.x / dist,
                param_.SPEED_Y * d.y / dist,
            };
        }

        ++obj->act_;
        /*fallthrough*/
    case 1:
        t->position_ += t->velocity_;

        break;
    }
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

    const float leftLimit   = size->x;
    const float rightLimit  = BG::WINDOW_W + size->x;
    const float topLimit    = size->y;
    const float bottomLimit = BG::WINDOW_H + size->y;

    if (pos->x < leftLimit  ||
        pos->x > rightLimit ||
        pos->y < topLimit   ||
        pos->y > bottomLimit)
    {
        obj->behavior_ = nullptr; // ��ʊO�ɍs���������
    }

}
