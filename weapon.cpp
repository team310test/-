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
    ActorComponent* dstA = dst->actorComponent_;

    // HP�����炵�A0�������ꍇ��0����
    dstA->hp_ = std::max(dstA->hp_ -= getParam()->ATTACK_POWER, 0);

    src->behavior_ = nullptr; // �e������

    // ��eSE���Đ�
    Audio::play(SE_DMG, false);

    // �v���C���[�Ȃ��p��eSE���Đ�
    if (dst == Game::instance()->player_)
    {
        Audio::play(SE_DMG, false);
    }

    // ���肪�܂������Ă���ꍇ
    if (dstA->hp_ > 0)
    {
        // �����h�炷
        dst->isQuake_ = true;
        // �����_�ł����閳�G����
        dstA->damageTimer_ = DMG_TIME;
    }

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
    param_.ERASER     = &plShotEraser;

    param_.SPEED_X      = NORMAL_SHOT_SPEED;
    param_.ATTACK_POWER = NORMAL_SHOT_ATK;

    param_.ATTACK_BOX[0] = {
        -SHOT_HITBOX, -SHOT_HITBOX,
         SHOT_HITBOX,  SHOT_HITBOX
    };

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
    param_.ERASER     = &enmShotEraser;

    param_.SPEED_X      = NORMAL_SHOT_SPEED;
    param_.ATTACK_POWER = NORMAL_SHOT_ATK;

    param_.ATTACK_BOX[0] = { 
        -SHOT_HITBOX, -SHOT_HITBOX, 
         SHOT_HITBOX,  SHOT_HITBOX 
    };
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
    param_.ERASER = &plShotEraser;

    param_.SPEED_X      = SINE_WAVE_SHOT_SPEED;
    param_.ATTACK_POWER = SINE_WAVE_SHOT_ATK;

    param_.ATTACK_BOX[0] = { 
        -SHOT_HITBOX, -SHOT_HITBOX, 
         SHOT_HITBOX,  SHOT_HITBOX 
    };
}

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
    param_.SPR_WEAPON   = &sprShot_NormalShot;
    param_.ERASER       = &plShotEraser;

    param_.SPEED_X      = SQUARE_WAVE_SHOT_SPEED_X;
    param_.SPEED_Y      = SQUARE_WAVE_SHOT_SPEED_Y;
    param_.ATTACK_POWER = SQUARE_WAVE_SHOT_ATK;

    param_.ATTACK_BOX[0] = { 
        -SHOT_HITBOX, -SHOT_HITBOX, 
         SHOT_HITBOX,  SHOT_HITBOX 
    };
}

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
    param_.ERASER = &plShotEraser;

    param_.SPEED_X      = CURVE_SHOT_SPEED_X;
    param_.SPEED_Y      = CURVE_SHOT_SPEED_Y;
    param_.ATTACK_POWER = CURVE_SHOT_ATK;

    param_.ATTACK_BOX[0] = {
        -SHOT_HITBOX, -SHOT_HITBOX,
         SHOT_HITBOX,  SHOT_HITBOX
    };
}

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

// �v���C���[(Y�����])
PlCurveShotFlipBehavior::PlCurveShotFlipBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &plShotEraser;

    param_.SPEED_X = CURVE_SHOT_SPEED_X;
    param_.SPEED_Y = -CURVE_SHOT_SPEED_Y;
    param_.ATTACK_POWER = CURVE_SHOT_ATK;

    param_.ATTACK_BOX[0] = {
        -SHOT_HITBOX, -SHOT_HITBOX,
         SHOT_HITBOX,  SHOT_HITBOX
    };

}

void PlCurveShotFlipBehavior::update(OBJ2D* obj) const
{
    Transform* transform = obj->transform_;

    transform->position_ += transform->velocity_; // �ʒu�ɑ��x�𑫂�

    // ���x�ɉ����x�𑫂�
    transform->velocity_ += {
        CURVE_SHOT_ACCEL_X / transform->scale_.x,  // scale�ɋ��������킹��
            -CURVE_SHOT_ACCEL_Y / transform->scale_.y,  // scale�ɋ��������킹��
    };

}

// �G�l�~�[
EnmCurveShotBehavior::EnmCurveShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &enmShotEraser;

    param_.SPEED_X = -CURVE_SHOT_SPEED_X;
    param_.SPEED_Y =  CURVE_SHOT_SPEED_Y;
    param_.ATTACK_POWER = CURVE_SHOT_ATK;

    param_.ATTACK_BOX[0] = { 
        -SHOT_HITBOX, -SHOT_HITBOX, 
         SHOT_HITBOX,  SHOT_HITBOX 
    };

}

void EnmCurveShotBehavior::update(OBJ2D* obj) const
{
    Transform* transform = obj->transform_;

    transform->position_ += transform->velocity_; // �ʒu�ɑ��x�𑫂�

    // ���x�ɉ����x�𑫂�
    transform->velocity_ += {
        -CURVE_SHOT_ACCEL_X / transform->scale_.x,  // scale�ɋ��������킹��
         CURVE_SHOT_ACCEL_Y / transform->scale_.y,  // scale�ɋ��������킹��
    };

}

// �G�l�~�[(Y�����])
EnmCurveShotFlirpBehavior::EnmCurveShotFlirpBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &enmShotEraser;

    param_.SPEED_X = -CURVE_SHOT_SPEED_X;
    param_.SPEED_Y = -CURVE_SHOT_SPEED_Y;
    param_.ATTACK_POWER = CURVE_SHOT_ATK;

    param_.ATTACK_BOX[0] = {
        -SHOT_HITBOX, -SHOT_HITBOX,
         SHOT_HITBOX,  SHOT_HITBOX
    };

}

void EnmCurveShotFlirpBehavior::update(OBJ2D* obj) const
{
    Transform* transform = obj->transform_;

    transform->position_ += transform->velocity_; // �ʒu�ɑ��x�𑫂�

    // ���x�ɉ����x�𑫂�
    transform->velocity_ += {
        -CURVE_SHOT_ACCEL_X / transform->scale_.x,  // scale�ɋ��������킹��
            -CURVE_SHOT_ACCEL_Y / transform->scale_.y,  // scale�ɋ��������킹��
    };

}


//******************************************************************************
//
//      PenetrateShot�i�ђʒe�j
//
//******************************************************************************

// �v���C���[
PlPenetrateShotBehavior::PlPenetrateShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &plShotEraser;

    param_.SPEED_X      = PENETRATE_SHOT_SPEED;
    param_.ATTACK_POWER = PENETRATE_SHOT_ATK;

    param_.ATTACK_BOX[0] = { 
        -SHOT_HITBOX, -SHOT_HITBOX, 
         SHOT_HITBOX,  SHOT_HITBOX 
    };

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

EnmPenetrateShotBehavior::EnmPenetrateShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &plShotEraser;

    param_.SPEED_X = PENETRATE_SHOT_SPEED;
    param_.ATTACK_POWER = PENETRATE_SHOT_ATK;

    param_.ATTACK_BOX[0] = {
        -SHOT_HITBOX, -SHOT_HITBOX,
         SHOT_HITBOX,  SHOT_HITBOX
    };

}

void EnmPenetrateShotBehavior::update(OBJ2D* obj) const
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
    transform->position_ -=
    {
        transform->velocity_.x* obj->transform_->scale_.x, // �ʒu�ɑ��x�𑫂�
            transform->velocity_.y* obj->transform_->scale_.y, // �ʒu�ɑ��x�𑫂�
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
    param_.ERASER     = &enmShotEraser;

    param_.SPEED_X      = AIM_SHOT_SPEED_X;
    param_.SPEED_Y      = AIM_SHOT_SPEED_Y;
    param_.ATTACK_POWER = AIM_SHOT_ATK;

    param_.ATTACK_BOX[0] = { 
        -SHOT_HITBOX, -SHOT_HITBOX, 
         SHOT_HITBOX,  SHOT_HITBOX
    };
}

void EnmAimShotBehavior::update(OBJ2D* obj) const
{
    // �ȗ�
    Transform* t = obj->transform_;
    Transform* corePlT = Game::instance()->player_->transform_;

    switch (obj->act_) 
    {
    case 0:    
        {
            // �v���C���[�Ɍ�����
            const VECTOR2 d = corePlT->position_ - t->position_;
            const float dist = sqrtf(d.x * d.x + d.y * d.y);

            t->velocity_ = {
                param_.SPEED_X * d.x / dist,
                param_.SPEED_Y * d.y / dist,
            };


            // �v���C���[�̕���������
            obj->renderer_->Xflip(); // �p�x�ݒ�̂��߂Ƀt���b�v����
            float r = atan2f(d.y, d.x);
            if (r < 0) r = r + DirectX::XM_2PI;
            obj->transform_->rotation_ = ToRadian(r * 360.0f / (DirectX::XM_2PI));
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
// �v���C���[
void PlShotEraser::erase(OBJ2D* obj) const
{
    if (!obj->behavior_) return;

    Transform* t = obj->transform_;
    Collider*  c = obj->collider_;
    OBJ_TYPE   objAtkType = obj->behavior_->getAttackType();

    // TODO: �{�X������ł�����c���Ă���G�l�~�[�e������
    if (Game::instance()->isBossDied_ && objAtkType == OBJ_TYPE::PLAYER)
    {
        // �����G�t�F�N�g
        AddObj::addEffect(obj, &efcBombBehavior);

        obj->behavior_ = nullptr;
        return;
    }

    // �������G�̒e��1��ł��k�����Ă��������
    if (objAtkType == OBJ_TYPE::PLAYER &&
        t->scale_.x < 1.0f && !c->isShrink_) 
    {
        // �����G�t�F�N�g
        AddObj::addEffect(obj, &efcBombBehavior);

        obj->behavior_ = nullptr;
        return;
    }

    const VECTOR2* pos  = &t->position_;
    const VECTOR2* size = &c->size_;

    const float leftLimit   = size->x - PL_SHOT_AREA_MARGIN;
    const float rightLimit  = BG::WINDOW_W + size->x + PL_SHOT_AREA_MARGIN;
    const float topLimit    = size->y - PL_SHOT_AREA_MARGIN;
    const float bottomLimit = BG::WINDOW_H + size->y + PL_SHOT_AREA_MARGIN;

    if (pos->x < leftLimit  || pos->x > rightLimit ||
        pos->y < topLimit   || pos->y > bottomLimit)
    {
        obj->behavior_ = nullptr; // ��ʊO�ɍs���������
        return;
    }

}

// �G�l�~�[
void EnmShotEraser::erase(OBJ2D* obj) const
{
    if (!obj->behavior_) return;

    Transform* t = obj->transform_;
    Collider* c = obj->collider_;
    OBJ_TYPE   objAtkType = obj->behavior_->getAttackType();

    // �������G�̒e��1��ł��k�����Ă��������
    if (objAtkType == OBJ_TYPE::PLAYER &&
        t->scale_.x < 1.0f && !c->isShrink_)
    {
        // �����G�t�F�N�g
        AddObj::addEffect(obj, &efcBombBehavior);

        obj->behavior_ = nullptr;
        return;
    }

    const VECTOR2* pos = &t->position_;
    const VECTOR2* size = &c->size_;

    const float leftLimit = size->x;
    const float rightLimit = BG::WINDOW_W + size->x;
    const float topLimit = size->y;
    const float bottomLimit = BG::WINDOW_H + size->y;

    if (pos->x < leftLimit || pos->x > rightLimit ||
        pos->y < topLimit || pos->y > bottomLimit)
    {
        obj->behavior_ = nullptr; // ��ʊO�ɍs���������
        return;
    }

}