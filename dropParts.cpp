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

    // コモン01
    GameLib::AnimeData animeCommon01[] = {
    { &sprPartsCommon01, 10 },
    { nullptr, -1 },// 終了フラグ
    };

    // コモン02
    GameLib::AnimeData animeCommon02[] = {
    { &sprPartsCommon02, 10 },
    { nullptr, -1 },// 終了フラグ
    };

    // コモン03
    GameLib::AnimeData animeCommon03[] = {
    { &sprPartsCommon03, 10 },
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

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    // 画像サイズ(128*64の半分)
    param_.HIT_BOX[0]    = { -64, -32, 64, 32 };   // 下長方形
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];   // 下長方形

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
        -64, -64,
         64,  64,
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
        -64, -64,
         64,  64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // 次のbehavior・eraser（プレイヤー）
    param_.NEXT_BEHAVIOR = &playerTrash01Behavior;
    param_.NEXT_ERASER   = &erasePlayer;

    param_.NEXT_HP = 3;
}


//******************************************************************************
// 
//      Common(効果なしパーツ)
// 
//******************************************************************************

// Common01
DropCommon01Behavior::DropCommon01Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeCommon01;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
        -64.0f, -18.0f,
         64.0f,  18.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // 次のbehavior・eraser（プレイヤー）
    param_.NEXT_BEHAVIOR = &playerCommon01Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

// Common01_2(90度回転)
DropCommon01_2Behavior::DropCommon01_2Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeCommon01;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
         -18.0f,-64.0f,
          18.0f, 64.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // 次のbehavior・eraser（プレイヤー）
    param_.NEXT_BEHAVIOR = &playerCommon01_2Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

// Common02
DropCommon02Behavior::DropCommon02Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeCommon02;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
        -64.0f, -18.0f,
         64.0f,  18.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // 次のbehavior・eraser（プレイヤー）
    param_.NEXT_BEHAVIOR = &playerCommon02Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

// Common02_2(90度回転)
DropCommon02_2Behavior::DropCommon02_2Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeCommon02;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
         -18.0f,-64.0f,
          18.0f, 64.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // 次のbehavior・eraser（プレイヤー）
    param_.NEXT_BEHAVIOR = &playerCommon02_2Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

// Common03
DropCommon03Behavior::DropCommon03Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeCommon03;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
        -64.0f, -18.0f,
         64.0f,  18.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // 次のbehavior・eraser（プレイヤー）
    param_.NEXT_BEHAVIOR = &playerCommon03Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

// Common03_2(90度回転)
DropCommon03_2Behavior::DropCommon03_2Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeCommon03;

    param_.SIZE = { 128.0f, 36.0f };
    param_.HIT_BOX[0] = {
         -18.0f,-64.0f,
          18.0f, 64.0f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // 次のbehavior・eraser（プレイヤー）
    param_.NEXT_BEHAVIOR = &playerCommon03_2Behavior;
    param_.NEXT_ERASER = &erasePlayer;

    param_.NEXT_HP = 3;
}

//******************************************************************************
// 
//      erase(消去)
// 
//******************************************************************************
void EraseDropParts::erase(OBJ2D* obj) const
{
    ActorComponent* a = obj->actorComponent_;


    if (obj->transform_->scale_.x <= UPDATE_OBJ_SCALE_MIN_LIMIT) // スケールが0以下になったら
    {
        // 爆発エフェクト追加
        AddObj::addEffect(obj, &efcBombBehavior);

        obj->behavior_ = nullptr; // 消去
        return;
    }


    if (a->parent_) // 親を手に入れたらプレイヤーのパーツになる
    {
        // 合体エフェクト追加
        AddObj::addEffect(obj, &efcCombineBehavior);

        obj->behavior_ = obj->nextBehavior_;    // 次のbehaviorを代入
        obj->eraser_   = obj->nextEraser_;      // 次のeraserを代入

        if (obj->behavior_ == nullptr) return;
        obj->update_ = PLAYER_PATRS_UPDATE;     // updateを変更
        
        a->hp_ = a->nextHp_;

        obj->isBlink_ = false;    // 明滅終了
       
        ++BasePlayerBehavior::plShrinkCount_;   // 縮小までのカウントを加算

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