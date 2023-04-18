#include "all.h"

namespace
{
    // タレット01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// 終了フラグ
    };
}

void BaseDropPartsBehavior::init(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = getParam()->ANIME_WAIT;

    obj->collider_->judgeFlag_        = true; // 当たり判定を行う
    obj->collider_->isDrawHitRect_    = true;
    obj->collider_->isDrawAttackRect_ = false;

    obj->eraser_ = &eraseDropParts;
}

void BaseDropPartsBehavior::moveX(OBJ2D* obj) const
{
    // 直線移動(仮)
    obj->transform_->velocity_.x -= getParam()->ACCEL_X;

    ActorBehavior::moveX(obj);
}

void BaseDropPartsBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    if (!dst->actorComponent_->parent_) return; // もし相手が親を持っていなければreturn

    src->actorComponent_->parent_ = dst;        // 親を保存
}

bool BaseDropPartsBehavior::isAlive(OBJ2D* obj) const
{
    return true;
}

void BaseDropPartsBehavior::areaCheck(OBJ2D* obj) const
{
    if (obj->transform_->position_.x < 0) // 画面右に行ったら
    {
        obj->behavior_ = nullptr; // 消去
    }
}


//******************************************************************************
// 
//      Turret(攻撃パーツ)
// 
//******************************************************************************

// Turret01
DropTurret01Behavior::DropTurret01Behavior()
{
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -80, 48, 125, 95 };   // 下長方形
    param_.HIT_BOX[1] = { -125,-95,10,50 };      // ネジ

    param_.ATTACK_BOX[0] = { -80, 48, 125, 95 };   // 下長方形
    param_.ATTACK_BOX[1] = { -125,-95,10,50 };      // ネジ

    param_.ACCEL_X = 2.0f;
    param_.ACCEL_Y = 2.0f;
    param_.SPEED_X_MAX = 2.0f;
    param_.SPEED_Y_MAX = 2.0f;

    // 次のbehavior・eraser（プレイヤー）
    param_.NEXT_BEHAVIOR = &playerTurret01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;
}


//******************************************************************************
// 
//      Buff(バフパーツ)
// 
//******************************************************************************

// Buff01
DropBuff01Behavior::DropBuff01Behavior()
{
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = { player_size, player_size };
    param_.HIT_BOX[0] = {
        -player_hitBox, -player_hitBox,
         player_hitBox,  player_hitBox,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ACCEL_X = 2.0f;
    param_.ACCEL_Y = 2.0f;
    param_.SPEED_X_MAX = 2.0f;
    param_.SPEED_Y_MAX = 2.0f;

    // 次のbehavior・eraser（プレイヤー）
    param_.NEXT_BEHAVIOR = &playerBuff01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;
}


//******************************************************************************
// 
//      erase(消去)
// 
//******************************************************************************
void EraseDropParts::erase(OBJ2D* obj) const
{
    if (obj->transform_->scale_.x <= 0) // スケールが0以下になったら
    {
        obj->behavior_ = nullptr; // 消去
        return;
    }

    if (obj->actorComponent_->parent_) // 親を手に入れたらプレイヤーのパーツになる
    {
        obj->behavior_ = obj->nextBehavior_; // 次のbehaviorを代入
        obj->eraser_   = obj->nextEraser_;   // 次のeraserを代入
        
        ++BasePlayerBehavior::plShrinkCount_; // 縮小までのカウントを加算
        return;
    }
}