#include "all.h"


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
        obj->renderer_->drawScale_ = obj->weaponComponent_->parent_->transform_->scale_;

        obj->eraser_ = getParam()->ERASER;
        obj->collider_->judgeFlag_ = true;      // あたり判定を行う
        obj->collider_->isDrawAttackRect_ = true;  // あたり判定の領域を描画する（デバッグ用）

        // 左右の向き、速度を設定（プレイヤーにもxFlip_の設定が必要）
        obj->transform_->velocity_.x = getParam()->SPEED_X;
        obj->transform_->velocity_.y = getParam()->SPEED_Y;


        // 画像の向きを設定
        obj->renderer_->drawXFlip_ = obj->weaponComponent_->parent_->renderer_->drawXFlip_;

        ++obj->state_;
        /*fallthrough*/
    case 1:
        //////// 通常時 ////////

        startAllShrink(obj);    // 縮小開始
        shrink(obj);            // 画像縮小

        if (obj->collider_->isShrink_) break; // 縮小中なら飛ばす

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
//      NormalShot（通常弾）
//
//******************************************************************************

// プレイヤー
PlayerNormalShotBehavior::PlayerNormalShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER     = &eraseShot;

    param_.SPEED_X      = PL_NORMAL_SHOT_SPEED;
    param_.ATTACK_POWER = PL_NORMAL_SHOT_ATK;

    // 変更予定
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };

}

void PlayerNormalShotBehavior::update(OBJ2D* obj) const
{
    // 位置に速度を足す
    obj->transform_->position_ += obj->transform_->velocity_;
}


// エネミー
EnmNormalShotBehavior::EnmNormalShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = 30.0f;
    param_.ATTACK_POWER = 1;

    // 変更予定
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };
}

void EnmNormalShotBehavior::update(OBJ2D* obj) const
{
    // 位置に速度を足す
    obj->transform_->position_ -= obj->transform_->velocity_;
}


//******************************************************************************
//
//      SineWaveShot（正弦波弾）
//
//******************************************************************************

// プレイヤー
PlSineWaveShotBehavior::PlSineWaveShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = 20.0f;
    param_.ATTACK_POWER = 1;

    // 変更予定
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };
}

static constexpr float SIN_YOFS = 64.0f;  // 振れ幅
void PlSineWaveShotBehavior::update(OBJ2D* obj) const
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

        // 振れ幅の分だけY座標をずらしたら
        if (transform->position_.y >= transform->orgPosition_.y + (SIN_YOFS * transform->scale_.y) ) // scaleに挙動を合わせる
        {
            ++obj->act_;
            break;
        }

        break;
    case 3: // 波形移動
        transform->velocity_.y += 
            (transform->orgPosition_.y - transform->position_.y) / (128.0f * transform->scale_.y); // scaleに挙動を合わせる

        break;
    }

    transform->position_ += transform->velocity_; // 位置に速度を足す

}


//******************************************************************************
//
//      SquareWaveShot（矩形波弾）
//
//******************************************************************************

// プレイヤー
PlSquareWaveShotBehavior::PlSquareWaveShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = 40.0f;
    param_.SPEED_Y = 20.0f;
    param_.ATTACK_POWER = 1;

    // 変更予定
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };
}

static constexpr float SQUARE_WAVE_SHOT_POSX_LIMIT = 300.0f; // 一度に前に進める距離
static constexpr float SQUARE_WAVE_SHOT_POSY_LIMIT = 75.0f;  // 上下移動できる限界
void PlSquareWaveShotBehavior::update(OBJ2D* obj) const
{
    Transform* transform = obj->transform_;

    switch (obj->act_)
    {
    case 0: // 現在位置を保存
        transform->orgPosition_ = transform->position_; // 現在位置を保存

        ++obj->act_;
        /*fallthrough*/
    case 1: // 前に進む（X移動）
        transform->position_.x += transform->velocity_.x; //　X位置にX速度を足す

        // orgX位置からしばらく進んだら
        if (transform->position_.x > transform->orgPosition_.x + (SQUARE_WAVE_SHOT_POSX_LIMIT * transform->scale_.x) ) // scaleに挙動を合わせる
        {
            ++obj->act_; // act進行
            break;
        }

        break;
    case 2: // 上、または下に移動（Y移動）
        transform->position_.y += transform->velocity_.y; // Y位置にY速度を足す

        // orgY位置+αよりY位置が下回った、または上回った場合
        if (transform->position_.y < transform->orgPosition_.y - (SQUARE_WAVE_SHOT_POSY_LIMIT * transform->scale_.x) || // scaleに挙動を合わせる
            transform->position_.y > transform->orgPosition_.y + (SQUARE_WAVE_SHOT_POSY_LIMIT * transform->scale_.y) )
        {
            transform->velocity_.y = -transform->velocity_.y;   // Y速度を反転
            transform->orgPosition_.x = transform->position_.x; // 現在のX位置を保存

            --obj->act_;  // actを戻す
            break;
        }

        break;
    }

}


//******************************************************************************
//
//      CurveShot（カーブ弾）
//
//******************************************************************************

// プレイヤー
PlCurveShotBehavior::PlCurveShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = -20.0f;
    param_.SPEED_Y = -25.0f;
    param_.ATTACK_POWER = 1;

    // 変更予定
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };

}

static constexpr float CURVE_SHOT_ACCEL_X = 1.4f; // X速度に足すX加速度
static constexpr float CURVE_SHOT_ACCEL_Y = 0.9f; // Y速度に足すY加速度
void PlCurveShotBehavior::update(OBJ2D* obj) const
{
    Transform* transform = obj->transform_;

    transform->position_ += transform->velocity_; // 位置に速度を足す

    // 速度に加速度を足す
    transform->velocity_ += {
        CURVE_SHOT_ACCEL_X / transform->scale_.x,  // scaleに挙動を合わせる
        CURVE_SHOT_ACCEL_Y / transform->scale_.y,  // scaleに挙動を合わせる
    };  

}

//******************************************************************************
//
//      CurveShot（カーブ弾）
//
//******************************************************************************

// プレイヤー
PlPenetrateShotBehavior::PlPenetrateShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER = &eraseShot;

    param_.SPEED_X = 100.0f;
    param_.ATTACK_POWER = 1;

    // 変更予定
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };

}

void PlPenetrateShotBehavior::update(OBJ2D* obj) const
{
    Transform* transform = obj->transform_;

    switch (obj->act_)
    {
    case 0: // X速度を落とす
        transform->velocity_.x *= 0.8f;

        // 弾がほぼ止まった状態になったら
        if (transform->velocity_.x <= 0.05f)
        {
            // 速度を代入
            transform->velocity_.x += param_.SPEED_X / transform->scale_.x;  // scaleに挙動を合わせる  
            ++obj->act_;
            break;
        }
        break;

    case 1: // 高速移動

        break;
    }

    //transform->position_ += transform->velocity_; // 位置に速度を足す
    transform->position_ +=
    {
        transform->velocity_.x * obj->transform_->scale_.x, // 位置に速度を足す
        transform->velocity_.y * obj->transform_->scale_.y, // 位置に速度を足す
    };
}


//******************************************************************************
//
//      AimShot（プレイヤー狙撃弾）
//
//******************************************************************************

// エネミー
EnmAimShotBehavior::EnmAimShotBehavior()
{
    param_.SPR_WEAPON = &sprShot_NormalShot;
    param_.ERASER     = &eraseShot;

    param_.SPEED_X = 20.0f;
    param_.SPEED_Y = 20.0f;
    param_.ATTACK_POWER = 1;

    // 変更予定
    param_.ATTACK_BOX[0] = { -24, -24, 24, 24 };
}

void EnmAimShotBehavior::update(OBJ2D* obj) const
{
    // 省略
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
//      erase（消去）
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
        obj->behavior_ = nullptr; // 画面外に行ったら消去
    }

}
