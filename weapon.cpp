#include "all.h"

// 敵がTurret01のときで左上に敵がいるときに弾を打つと消える

//******************************************************************************
//
//      BaseShotBehavior（弾のベース）
//
//******************************************************************************
void BaseShotBehavior::move(OBJ2D* obj) const
{
    switch (obj->state_)
    {
    case 0:
        //////// 初期設定 ////////
        obj->renderer_->data_ = getParam()->SPR_WEAPON;

        //obj->transform_->scale_ = getParam()->SCALE;
        obj->transform_->scale_ = obj->weaponComponent_->parent_->transform_->scale_;

        obj->eraser_ = getParam()->ERASER;
        obj->collider_->judgeFlag_ = true;      // あたり判定を行う
        obj->collider_->isDrawAttackRect_ = true;  // あたり判定の領域を描画する（デバッグ用）

        // 左右の向き、速度を設定（プレイヤーにもxFlip_の設定が必要）
        obj->transform_->velocity_.x =  getParam()->SPEED_X;
        obj->transform_->velocity_.y = 0.0f;    // 念のため

        ++obj->state_;
        /*fallthrough*/
    case 1:
        //////// 通常時 ////////

        update(obj);        // 武器の位置更新

        break;
    }
        
    calcAttackBox(obj); // 当たり判定の更新
}

void BaseShotBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    // hpから攻撃力を引いた値が0より小さかったら0に修正、そうでなければhpから攻撃を引く
    dst->actorComponent_->hp_ = std::max(
        dst->actorComponent_->hp_ - getParam()->ATTACK_POWER, 0
    );

    src->behavior_ = nullptr; // 弾を消去
}

// 縮小に伴って弾の大きさの更新が必要
void BaseShotBehavior::calcAttackBox(OBJ2D* obj) const
{
    // 攻撃判定の計算
    for (int i = 0; i < Collider::boxMax; ++i)
    {
        obj->collider_->calcAttackBox(getParam()->ATTACK_BOX[i], i);
    }
}


//******************************************************************************
//
//      NormalShotBehavior（ノーマル弾）
//
//******************************************************************************

// プレイヤー
PlayerNormalShotBehavior::PlayerNormalShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER     = &eraseShot;

    param_.SPEED_X = 30.0f;
    param_.ATTACK_POWER = 1;

    // 変更予定
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };

}

void PlayerNormalShotBehavior::update(OBJ2D* obj) const
{
    // 位置に速度を足す
    obj->transform_->position_ += obj->transform_->velocity_;
}


//******************************************************************************
//
//      SinShotBehavior（波形移動弾）
//
//******************************************************************************

// プレイヤー
PlayerWaveShotBehavior::PlayerWaveShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = 20.0f;
    param_.ATTACK_POWER = 1;

    // 変更予定
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };
}

static constexpr float SIN_YOFS = 64.0f;  // 振れ幅
void PlayerWaveShotBehavior::update(OBJ2D* obj) const
{
    Transform* transform = obj->transform_;

    switch (obj->act_) 
    {
    case 0: // 初期位置を保存
        transform->orgPosition_ = transform->position_; // 初期位置を保存

#if 1
        obj->act_ = 2;
        break;
#else
        ++obj->act_;
        /*fallthrough*/
    case 1: // 波形移動する前に少し前に進む
        if (transform->position_.x > transform->orgPosition_.x + 200) // 初期位置からしばらく進んだらact進行
        {
            transform->orgPosition_.y = transform->position_.y;	// Y座標を中心軸とする
            ++obj->act_;
            break;
        }

        break;
#endif
    case 2: // 波形移動の前準備
        transform->velocity_.y += 2.0f; // 振れ幅の分まで徐々にずらす

        if (transform->position_.y >= transform->orgPosition_.y + SIN_YOFS) // 振れ幅の分だけY座標をずらしたら
        {
            ++obj->act_;
            break;
        }

        break;
    case 3: // 波形移動
        transform->velocity_.y += (transform->orgPosition_.y - transform->position_.y) / 128.0f;

        break;
    }

    transform->position_ += transform->velocity_; // 位置に速度を足す

}


//******************************************************************************
//
//      erase（消去）
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
        obj = nullptr; // 画面外に行ったら消去
    }
}