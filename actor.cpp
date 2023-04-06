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
        obj->renderer_->animeData_ = getParam()->ANIME_RIGHT;
        obj->transform_->scale_ = getParam()->SCALE;
        obj->collider_->size_ = {
            getParam()->SIZE.x * getParam()->SCALE.x, 
            getParam()->SIZE.y * getParam()->SCALE.y
        };
        obj->actorComponent_->hp_ = getParam()->HP;

        init(obj);

        obj->state_++;
        break;

    case 1:
        //////// �ʏ펞 ////////

        damageProc(obj);
        shrink(obj);    // �摜�k��

        moveY(obj);
        moveX(obj);
        areaCheck(obj);
        attack(obj);
        break;
    }

    obj->collider_->calcHitBox(getParam()->HIT_BOX);
    obj->collider_->calcAttackBox(getParam()->ATTACK_BOX);

    // �A�j���[�V�����X�V
    obj->renderer_->animeData_ = getParam()->ANIME_LEFT;

    if (obj->renderer_->animeData_) 
        obj->renderer_->animeUpdate();
}

// �k�������̔���
bool ShrinkJudge(OBJ2D* obj,VECTOR2 targetScale)
{
    //if (obj->collider_->targetScale_.x == 0 ||
    //    obj->collider_->targetScale_.y == 0)
    //    return false;

    //if (obj->transform_->scale_.x > targetScale.x)
    //    return true;
    //if (obj->transform_->scale_.x > targetScale.y)
    //    return true;

    return false;
}

// �k���֐�
static const float divideValue = 0.9f;                 // scale������l
static const VECTOR2 shrinkValue = { -0.01f, -0.01f }; // �k������l

void Behavior::shrink(OBJ2D* obj) const
{
    if (obj->behavior_ != &normalPlayerBehavior &&
        obj->behavior_ != &itemPlayerBehavior) return;
    static VECTOR2 endScale{}; // �ŏI�I��scale�̑傫��

    VECTOR2* currentScale = &obj->transform_->scale_;   // ���݂�scale
    bool* isShrink        = &obj->collider_->isShrink_; // �k�����Ă��邩����


    if ((GameLib::input::TRG(0) & GameLib::input::PAD_TRG1) && // Z�ŏk��
        *isShrink == false)                                    // Shrink���Ă��Ȃ����
    {
        endScale  = *currentScale * divideValue; // ���݂�scale��?����?���ŏI�ڕW�ɐݒ�
        *isShrink = true;                        // Shrink�J�n
    }

    if (*isShrink == false) return; // Shrink���Ă��Ȃ����return
    
    //const VECTOR2 corePos = Game::instance()->getPlayer() ? 
    //                        Game::instance()->getPlayer()->transform_->position_ :
    //                        VECTOR2(0,0); // �{�̂̈ʒu    
    VECTOR2* pos = &obj->transform_->position_;          // obj�̈ʒu
    const VECTOR2 corePos = obj->actorComponent_->parent_ ?
                            obj->actorComponent_->parent_->transform_->position_:
        *pos;

    const VECTOR2 d  = { *pos - corePos };               // �{�̂̈ʒu����obj�̈ʒu���������Ƃ�obj����{�̂֌������x�N�g�����ł���
    const float dist = sqrtf(d.x * d.x * + d.y * d.y);    // ���������v�Z
    const VECTOR2 velocity = { d.x / dist * 0.1f, d.y / dist * 0.1f }; // ���x������

    *pos += velocity;

    // Shrink���̏ꍇ
    if (currentScale->x > endScale.x) // �ŏI�ڕW��茻�݂�scale���傫�����
    {
        *currentScale += shrinkValue; // �k��

        if (currentScale->x <= endScale.x) // �ŏI�ڕW�Ɠ������A�����菬�����Ȃ�����
        {
            *currentScale = endScale; // �l���C��
            *isShrink     = false;     // Shrink�I��
        }
    }
    

    //// [Z]�ŏk��
    //if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG1)
    //{ 
    //    obj->collider_->targetScale_.x = obj->transform_->scale_.x * 0.9f;
    //    obj->collider_->targetScale_.y = obj->transform_->scale_.y * 0.9f;
    //    obj->collider_->isShrink_ = true;
    //    obj->actorComponent_->padTrg_ = 0;
    //    obj->actorComponent_->padState_ = 0;
    //}
    //
    //if(ShrinkJudge(obj, obj->collider_->targetScale_))
    //{
    //    obj->transform_->scale_.x -= 0.01f * obj->transform_->scale_.x;
    //    obj->transform_->scale_.y -= 0.01f * obj->transform_->scale_.y;
    //}
    //else
    //{
    //    obj->collider_->isShrink_ = false;
    //    obj->actorComponent_->padTrg_ = GameLib::input::TRG(0);
    //    obj->actorComponent_->padState_ = GameLib::input::STATE(0);
    //}
}
