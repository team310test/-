#pragma once

class AddObj
{
public:
    // �e�ǉ��i�����ʒu�𒲐����₷���悤��pos�������ɒǉ��j
    // 
    // &plNormalShotBehavior,     // �m�[�}��
    // &plSineWaveShotBehavior,   // �����g
    // &plSquareWaveShotBehavior, // ��`�g
    // &plCurveWaveShotBehavior,  // ��J�[�u
    // &plPenetrateShotBehavior,  // �����E�ђ�(�\��)
    // &enmAimShotBehavior        // �v���C���[�_���i�G�l�~�[��p�j
    template <typename T>
    inline static void addShot(OBJ2D*& obj, T* behavior, const VECTOR2& pos)
    {
        OBJ2D* shot = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg_,
                nullptr,
                nullptr,
                new WeaponComponent
            ),
            behavior,
            pos
        );
        shot->zOrder_ = 2;
        shot->weaponComponent_->parent_ = obj;
    }


    // �G�t�F�N�g�ǉ�
    template <typename T>
    inline static void addEffect(OBJ2D*& obj, T* behavior, VECTOR2 add = { 0.0f,0.0f }) // obj�͒��ڎQ��
    {
        const VECTOR2 pos =
        { obj->transform_->position_.x + add.x,obj->transform_->position_.y + add.y };

        OBJ2D* effect = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg_,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                new EffectComponent
            ),
            behavior,
            pos
        );
        effect->zOrder_ = 10;

        effect->transform_->scale_    = obj->transform_->scale_;
        effect->renderer_->drawScale_ = obj->renderer_->drawScale_;

        //effect->effectComponent_->parent_ = obj;
    }
};