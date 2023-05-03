#include "all.h"

namespace
{
    // タレット01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    //  バフ01
    GameLib::AnimeData animeBuff01[] = {
        { &sprPartsBuff01, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    //  ゴミ01
    GameLib::AnimeData animeTrash01[] = {
        { &sprPartsTrash01, 10 },
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

void BaseDropPartsBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    if (!dst->actorComponent_->parent_) return; // もし相手が親を持っていなければreturn

    src->actorComponent_->parent_ = dst;        // 親を保存
}

bool BaseDropPartsBehavior::isAlive(OBJ2D* /*obj*/) const
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

    param_.SIZE = VECTOR2(PARTS_OBJ_SIZE, PARTS_OBJ_SIZE);

    // 画像サイズ(128*64の半分)
    param_.HIT_BOX[0] = { -64, -32, 64, 32 };    // 下長方形
    //param_.HIT_BOX[1] = { -125,-95,10,50 };    // ネジ

    param_.ATTACK_BOX[0] = param_.HIT_BOX[0]; // 下長方形
    //param_.ATTACK_BOX[1] = param_.HIT_BOX[1];   // ネジ

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
    param_.ANIME_WAIT = animeBuff01;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0] = {
        -PL_CORE_HITBOX, -PL_CORE_HITBOX,
         PL_CORE_HITBOX,  PL_CORE_HITBOX,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // 次のbehavior・eraser（プレイヤー）
    param_.NEXT_BEHAVIOR = &playerBuff01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;
}


//******************************************************************************
// 
//      Trash(ゴミパーツ)
// 
//******************************************************************************
DropTrash01Behavior::DropTrash01Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeTrash01;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0] = {
        -PL_CORE_HITBOX, -PL_CORE_HITBOX,
         PL_CORE_HITBOX,  PL_CORE_HITBOX,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // 次のbehavior・eraser（プレイヤー）
    param_.NEXT_BEHAVIOR = &playerTrash01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP = 3;
}


//******************************************************************************
// 
//      erase(消去)
// 
//******************************************************************************
void EraseDropParts::erase(OBJ2D* obj) const
{
    if (obj->transform_->scale_.x <= UPDATE_OBJ_SCALE_MIN_LIMIT) // スケールが0以下になったら
    {
        // 爆発エフェクト追加
        AddObj::addEffect(obj, &efcBombBehavior);

        obj->behavior_ = nullptr; // 消去
        return;
    }

    if (obj->actorComponent_->parent_) // 親を手に入れたらプレイヤーのパーツになる
    {
        // 合体エフェクト追加
        AddObj::addEffect(obj, &efcCombineBehavior);

        obj->behavior_ = obj->nextBehavior_; // 次のbehaviorを代入
        obj->eraser_   = obj->nextEraser_;   // 次のeraserを代入


        if (obj->behavior_ == nullptr) return;
        obj->update_ = PLAYER_PATRS_UPDATE;  // updateを変更

        obj->actorComponent_->hp_ = obj->actorComponent_->nextHp_;  // 次のHPを代入
        
        ++BasePlayerBehavior::plShrinkCount_; // 縮小までのカウントを加算

        return;
    }
}

//******************************************************************************
//      パーツのupdate
//******************************************************************************
void DROP_PARTS_UPDATE(OBJ2D* obj)
{
    Transform* t = obj->transform_;
    
    t->velocity_.x = DROP_PARTS_SPEED;
    t->velocity_.y = 0;
    t->position_ += t->velocity_;
}