#include "all.h"

void ActorBehavior::move(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = nullptr;
    switch (obj->state_)
    {
    case 0:
        //////// �����ݒ� ////////
        // �A�j���̏����ݒ�
        obj->renderer_->animeData_  = getParam()->ANIME_WAIT;
        obj->transform_->scale_     = getParam()->SCALE;
        obj->renderer_->drawScale_  = getParam()->SCALE;
        obj->collider_->size_ = {
            getParam()->SIZE.x * getParam()->SCALE.x, 
            getParam()->SIZE.y * getParam()->SCALE.y
        };
        obj->actorComponent_->hp_     = getParam()->HP;
        obj->actorComponent_->nextHp_ = getParam()->NEXT_HP;

        obj->nextBehavior_ = getParam()->NEXT_BEHAVIOR;
        obj->nextEraser_   = getParam()->NEXT_ERASER;

        // �A�j���p�p�����[�^
        obj->actorComponent_->objAnimeAlways_ = getParam()->OBJ_ANIME;
        obj->actorComponent_->rotSpeed_ = getParam()->ROT_SPEED;

        init(obj);

        obj->state_++;
        break;

    case 1:
        //////// �ʏ펞 ////////
        // ���݂�behavior�Eeraser��param�ƈႤ�ꍇ�Aparam�̕�����
        if (obj->nextBehavior_ != getParam()->NEXT_BEHAVIOR) obj->nextBehavior_ = getParam()->NEXT_BEHAVIOR;
        if (obj->nextEraser_   != getParam()->NEXT_ERASER)   obj->nextEraser_   = getParam()->NEXT_ERASER;


        startAllShrink(obj);    // �k���J�n
        shrink(obj);            // �摜�k��


        if (obj->collider_->isShrink_) break; // �k�����Ȃ��΂�
        // obj���v���C���[�̏ꍇ
        if (obj == Game::instance()->player_) { if (Behavior::isObjShrink()) break; }// ���ׂĂ�obj���k���I�����Ă��Ȃ���Δ�΂�


        // PG�ɂ��A�j���[�V����(objAnimeTemporary_��D��I�ɍs��)
        if (obj->actorComponent_->objAnimeTemporary_)
        {
            if (obj->actorComponent_->objAnimeTemporary_(obj))
                obj->actorComponent_->objAnimeTemporary_ = nullptr; // �A�j�����I����objAnimeTemporary��nullptr�ɂ���
        }
        else if (obj->actorComponent_->objAnimeAlways_) obj->actorComponent_->objAnimeAlways_(obj);

        damageProc(obj);

        // update������Ȃ�update���g�p����
        if (obj->update_) obj->update_(obj);

        areaCheck(obj);

        obj->transform_->position_ += obj->transform_->velocity_;   // ���x���ʒu�ɉ��Z

        if (obj->transform_->scale_.x > UPDATE_OBJ_SCALE_MIN_LIMIT)
        {
            attack(obj); // �X�P�[�����X�P�[���X�V�Œ�l���傫����΍U���������s��
        }

        break;
    }

    for (int i = 0; i < Collider::boxMax; ++i)
        obj->collider_->calcHitBox(getParam()->HIT_BOX[i], i);

    for (int i = 0; i < Collider::boxMax; ++i)
        obj->collider_->calcAttackBox(getParam()->ATTACK_BOX[i], i);

    // �A�j���[�V�����X�V
    obj->renderer_->animeData_ = getParam()->ANIME_WAIT;

    if (obj->renderer_->animeData_) 
        obj->renderer_->animeUpdate();
}


// ���ׂĂ�obj��Shrink���J�n������֐�
void Behavior::startAllShrink(OBJ2D* obj) const
{
    if (!Collider::isAllShrink_)        return; // Shrink���J�n����Ă��Ȃ����return
    if (obj->collider_->isShrink_)      return; // obj�����ł�shrink���Ȃ�return
    if (obj->transform_->scale_.x <= 0) return; // scale��0�ȉ��Ȃ�return

    VECTOR2* currentScale = &obj->transform_->scale_;       // ���݂�scale
    VECTOR2* targetScale  = &obj->collider_->targetScale_;  // �ŏI�I�ɖڎw��scale 
    *targetScale = (*currentScale) * SHRINK_DIVIDE_VALUE;           // ���݂�scale��?����?���ŏI�ڕW�ɐݒ�

    obj->collider_->judgeFlag_ = false;
    obj->collider_->isShrink_ = true; // obj��shrink���J�n
}

// �k���֐�
float Behavior::shrinkVelocity_ = SHRINK_SPEED; // �k�����鑬�x
void Behavior::shrink(OBJ2D* obj) const
{
    Transform* t = obj->transform_;
    Collider*  c = obj->collider_;

    // �I���W�i�����@��scale��0.5f�ȉ��Ȃ�shrink�������I��
    if (obj->behavior_ == &playerCoreBehavior && t->scale_.x <= 0.5f)
    {
        c->isShrink_ = false;
        return; 
    }

    if (c->isShrink_ == false) return; // Shrink���Ă��Ȃ����return



    // Shrink���̏ꍇ
    if (t->scale_.x > c->targetScale_.x) // ���݂�scale���ŏI�ڕW���傫�����
    {
        t->scale_ += {                // �k��
            shrinkVelocity_ * t->scale_.x, 
            shrinkVelocity_ * t->scale_.y
        };  
        if (t->scale_.x < c->targetScale_.x)  t->scale_ = c->targetScale_; // �ŏI�ڕW��菬�����Ȃ�����l���C��
    }

    // scaleAnime���ݒ肳��Ă��Ȃ���Ε`��p�Ɣ���p��scale�̃T�C�Y�����킹��
/*    if (obj->actorComponent_)
    {
        if (obj->actorComponent_->objAnimeAlways_ != &scaleAnime)
            obj->renderer_->drawScale_ = t->scale_;
    }
    else */obj->renderer_->drawScale_ = t->scale_;


    // �ڕW��B�������ꍇ
    if (t->scale_.x == c->targetScale_.x)
    {
        obj->collider_->judgeFlag_ = true;
        c->isShrink_ = false;   // Shrink�I��
    }
}

// shrink���Ă���obj�����邩���ׂ�֐��ishrink���Ă���obj��������true, ���Ȃ����false�j
bool Behavior::isObjShrink()
{
    for (auto& list : *Game::instance()->obj2dManager()->getList())
    {
        if (!list->behavior_) continue;              // obj�����݂��Ă��Ȃ����continue
        if (list->collider_->isShrink_) return true; // shrink���I����Ă��Ȃ�obj�������true
    }

    return false; // ���ׂ�shrink���I����Ă����false
}