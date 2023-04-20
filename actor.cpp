#include "all.h"

void ActorBehavior::moveY(OBJ2D* obj) const
{
    // �ő呬�x�`�F�b�N���s��
    obj->transform_->velocity_.y = clamp(obj->transform_->velocity_.y, -getParam()->SPEED_Y_MAX, getParam()->SPEED_Y_MAX);

    // �ʒu�X�V
    float oldY = obj->transform_->position_.y;           // �ړ��O�̈ʒu��ێ�
    obj->transform_->position_.y += obj->transform_->velocity_.y;
    float deltaY = obj->transform_->position_.y - oldY;  // �ړ���̈ʒu����ړ��O�̈ʒu������
}

void ActorBehavior::moveX(OBJ2D* obj) const
{
    // �ő呬�x�`�F�b�N
    if (obj->transform_->velocity_.x > getParam()->SPEED_X_MAX) obj->transform_->velocity_.x = getParam()->SPEED_X_MAX;
    if (obj->transform_->velocity_.x < -getParam()->SPEED_X_MAX) obj->transform_->velocity_.x = -getParam()->SPEED_X_MAX;

    // X�����ړ�
    float oldX = obj->transform_->position_.x;
    obj->transform_->position_.x += obj->transform_->velocity_.x;
    float deltaX = obj->transform_->position_.x - oldX;
}

void ActorBehavior::move(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = nullptr;
    switch (obj->state_)
    {
    case 0:
        //////// �����ݒ� ////////
        // �A�j���̏����ݒ�
        obj->renderer_->animeData_ = getParam()->ANIME_WAIT;
        obj->transform_->scale_ = getParam()->SCALE;
        obj->renderer_->scale_ = getParam()->SCALE;
        obj->collider_->size_ = {
            getParam()->SIZE.x * getParam()->SCALE.x, 
            getParam()->SIZE.y * getParam()->SCALE.y
        };
        obj->actorComponent_->hp_ = getParam()->HP;

        obj->actorComponent_->nextBehavior_ = getParam()->NEXT_BEHAVIOR;
        obj->actorComponent_->nextEraser_ = getParam()->NEXT_ERASER;

        // �A�j���p�p�����[�^
        obj->actorComponent_->objAnime_ = getParam()->obj_ANIME;
        obj->actorComponent_->rotSpeed_ = getParam()->ROT_SPEED;


        init(obj);

        obj->state_++;
        break;

    case 1:
        //////// �ʏ펞 ////////

        damageProc(obj);

        startAllShrink(obj); //�k���J�n
        shrink(obj);    // �摜�k��

        // �A�j���[�V����
        if(obj->actorComponent_->objAnime_) obj->actorComponent_->objAnime_(obj);

        moveY(obj);
        moveX(obj);
        areaCheck(obj);
        attack(obj);
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

//// <��]�A�j���[�V����>
//void ActorBehavior::rotateAnime(OBJ2D* obj) const
//{
//    if (getParam()->ROT_SPEED == 0.0f) return;  // ��]���x��0�Ȃ� return
//
//    obj->transform_->rotation_ += getParam()->ROT_SPEED;
//}
//
//// <X���̃X�P�[���ϓ��A�j���[�V����>
//void ActorBehavior::XscaleAnime(OBJ2D* obj) const
//{
//    // ��ʂ̏k�����Ȃ� return
//    if (obj->collider_->isShrink_) return;
//
//    VECTOR2 orgScale = obj->transform_->scale_;
//    float shrinkScale = orgScale.x * 0.05;
//    static bool isShrink;
//}


static const float divideValue = 0.5f;     // scale������l(�ŏI�I��scale�̑傫���ɉe��)

// ���ׂĂ�obj��Shrink���J�n������֐�
void Behavior::startAllShrink(OBJ2D* obj) const
{
    if (!Collider::isAllShrink_)   return; // Shrink���J�n����Ă��Ȃ����return
    if (obj->collider_->isShrink_) return; // obj�����ł�shrink���Ȃ�return;

    VECTOR2* currentScale = &obj->transform_->scale_;       // ���݂�scale
    VECTOR2* targetScale = &obj->collider_->targetScale_;  // �ŏI�I�ɖڎw��scale 
    *targetScale = (*currentScale) * divideValue;           // ���݂�scale��?����?���ŏI�ڕW�ɐݒ�

    obj->collider_->isShrink_ = true; // obj��shrink���J�n
}

static const float shrinkVelocity = -0.0025f; // �k�����鑬�x(�k���̑����ɉe��)

// �k���֐�
void Behavior::shrink(OBJ2D* obj) const
{
    bool* isShrink = &obj->collider_->isShrink_; // �k�����Ă��邩�ǂ���

    // �I���W�i�����@��scale��0.5f�ȉ��Ȃ�shrink�������I��
    if (obj->behavior_ == &normalPlayerBehavior &&
        obj->transform_->scale_.x <= 0.5f)
    {
        *isShrink = false;
        return; 
    }

    if (*isShrink == false) return; // Shrink���Ă��Ȃ����return

    VECTOR2* currentScale = &obj->transform_->scale_;      // ���݂�scale
    VECTOR2* targetScale  = &obj->collider_->targetScale_; // �ŏI�I�ɖڎw��scale 

    // Shrink���̏ꍇ
    if (currentScale->x > targetScale->x) // �ŏI�ڕW��茻�݂�scale���傫�����
    {
        *currentScale += {                // �k��
            shrinkVelocity * obj->transform_->scale_.x, 
            shrinkVelocity * obj->transform_->scale_.y,
        };  
        if (currentScale->x < targetScale->x)  *currentScale = *targetScale; // �ŏI�ڕW��菬�����Ȃ�����l���C��
    }
    
    // �`��p�Ɣ���p��scale�̃T�C�Y�����킹��
    obj->renderer_->scale_ = obj->transform_->scale_;


    // �ڕW��B�������ꍇ
    if (currentScale->x == targetScale->x)
    {
        *isShrink = false;           // Shrink�I��

        //obj->actorComponent_->padTrg_ = GameLib::input::TRG(0);
        //obj->actorComponent_->padState_ = GameLib::input::STATE(0);
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