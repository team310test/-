#pragma once

class AddObj
{
public:
    // 弾追加（生成位置を調整しやすいようにposを引数に追加）
    // 
    // &plNormalShotBehavior,     // ノーマル
    // &plSineWaveShotBehavior,   // 正弦波
    // &plSquareWaveShotBehavior, // 矩形波
    // &plCurveWaveShotBehavior,  // 上カーブ
    // &plPenetrateShotBehavior,  // 高速・貫通(予定)
    // &enmAimShotBehavior        // プレイヤー狙撃（エネミー専用）
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


    // エフェクト追加
    template <typename T>
    inline static void addEffect(OBJ2D*& obj, T* behavior, VECTOR2 add = { 0.0f,0.0f }) // objは直接参照
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