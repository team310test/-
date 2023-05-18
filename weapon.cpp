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
    ActorComponent* dstA = dst->actorComponent_;

    // HPを減らし、0を下回る場合は0を代入
    dstA->hp_ = std::max(dstA->hp_ -= getParam()->ATTACK_POWER, 0);

    src->behavior_ = nullptr; // 弾を消去

    // 被弾SEを再生
    Audio::play(SE_DMG, false);

    // プレイヤーなら専用被弾SEを再生
    if (dst == Game::instance()->player_)
    {
        Audio::play(SE_DMG, false);
    }

    // 相手がまだ生きている場合
    if (dstA->hp_ > 0)
    {
        // 相手を揺らす
        dst->isQuake_ = true;
        // 相手を点滅させる無敵時間
        dstA->damageTimer_ = DMG_TIME;
    }

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
    // 位置に速度を足す
    obj->transform_->position_ += obj->transform_->velocity_;
}


// エネミー
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

    transform->position_ += transform->velocity_; // 位置に速度を足す

    // 速度に加速度を足す
    transform->velocity_ += {
        CURVE_SHOT_ACCEL_X / transform->scale_.x,  // scaleに挙動を合わせる
        CURVE_SHOT_ACCEL_Y / transform->scale_.y,  // scaleに挙動を合わせる
    };  

}

// プレイヤー(Y軸反転)
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

    transform->position_ += transform->velocity_; // 位置に速度を足す

    // 速度に加速度を足す
    transform->velocity_ += {
        CURVE_SHOT_ACCEL_X / transform->scale_.x,  // scaleに挙動を合わせる
            -CURVE_SHOT_ACCEL_Y / transform->scale_.y,  // scaleに挙動を合わせる
    };

}

// エネミー
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

    transform->position_ += transform->velocity_; // 位置に速度を足す

    // 速度に加速度を足す
    transform->velocity_ += {
        -CURVE_SHOT_ACCEL_X / transform->scale_.x,  // scaleに挙動を合わせる
         CURVE_SHOT_ACCEL_Y / transform->scale_.y,  // scaleに挙動を合わせる
    };

}

// エネミー(Y軸反転)
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

    transform->position_ += transform->velocity_; // 位置に速度を足す

    // 速度に加速度を足す
    transform->velocity_ += {
        -CURVE_SHOT_ACCEL_X / transform->scale_.x,  // scaleに挙動を合わせる
            -CURVE_SHOT_ACCEL_Y / transform->scale_.y,  // scaleに挙動を合わせる
    };

}


//******************************************************************************
//
//      PenetrateShot（貫通弾）
//
//******************************************************************************

// プレイヤー
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
    transform->position_ -=
    {
        transform->velocity_.x* obj->transform_->scale_.x, // 位置に速度を足す
            transform->velocity_.y* obj->transform_->scale_.y, // 位置に速度を足す
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
    // 省略
    Transform* t = obj->transform_;
    Transform* corePlT = Game::instance()->player_->transform_;

    switch (obj->act_) 
    {
    case 0:    
        {
            // プレイヤーに向かう
            const VECTOR2 d = corePlT->position_ - t->position_;
            const float dist = sqrtf(d.x * d.x + d.y * d.y);

            t->velocity_ = {
                param_.SPEED_X * d.x / dist,
                param_.SPEED_Y * d.y / dist,
            };


            // プレイヤーの方向を向く
            obj->renderer_->Xflip(); // 角度設定のためにフリップする
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
//      erase（消去）
//
//******************************************************************************
// プレイヤー
void PlShotEraser::erase(OBJ2D* obj) const
{
    if (!obj->behavior_) return;

    Transform* t = obj->transform_;
    Collider*  c = obj->collider_;
    OBJ_TYPE   objAtkType = obj->behavior_->getAttackType();

    // TODO: ボスが死んでいたら残っているエネミー弾を消去
    if (Game::instance()->isBossDied_ && objAtkType == OBJ_TYPE::PLAYER)
    {
        // 爆発エフェクト
        AddObj::addEffect(obj, &efcBombBehavior);

        obj->behavior_ = nullptr;
        return;
    }

    // 自分が敵の弾で1回でも縮小していたら消す
    if (objAtkType == OBJ_TYPE::PLAYER &&
        t->scale_.x < 1.0f && !c->isShrink_) 
    {
        // 爆発エフェクト
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
        obj->behavior_ = nullptr; // 画面外に行ったら消去
        return;
    }

}

// エネミー
void EnmShotEraser::erase(OBJ2D* obj) const
{
    if (!obj->behavior_) return;

    Transform* t = obj->transform_;
    Collider* c = obj->collider_;
    OBJ_TYPE   objAtkType = obj->behavior_->getAttackType();

    // 自分が敵の弾で1回でも縮小していたら消す
    if (objAtkType == OBJ_TYPE::PLAYER &&
        t->scale_.x < 1.0f && !c->isShrink_)
    {
        // 爆発エフェクト
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
        obj->behavior_ = nullptr; // 画面外に行ったら消去
        return;
    }

}