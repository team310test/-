#include "all.h"


int BasePlayerBehavior::plShrinkCount_      = 0;
int BasePlayerBehavior::plShrinkCountMax_   = 0;

int BasePlayerBehavior::plPartsCurrentCount_ = 0;

// アニメデータ
namespace
{
    // 待機
    GameLib::AnimeData animePLayerCore[] = {
        { &sprPlayerCore01, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // タレット01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // タレット01(反転)
    GameLib::AnimeData animeTurret01Flip[] = {
        { &sprPartsTurret01Flip, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // タレット02
    GameLib::AnimeData animeTurret02[] = {
        { &sprPartsTurret02, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // タレット02(反転)
    GameLib::AnimeData animeTurret02Flip[] = {
        { &sprPartsTurret02Flip, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // タレット03
    GameLib::AnimeData animeTurret03[] = {
        { &sprPartsTurret03, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    
    // シールド01
    GameLib::AnimeData animeShield01[] = {
    { &sprPartsShield01, 10 },
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
    //  ゴミ02
    GameLib::AnimeData animeTrash02[] = {
        { &sprPartsTrash02, 10 },
        { nullptr, -1 },// 終了フラグ
    };     
    //  ゴミ02
    GameLib::AnimeData animeTrash03[] = {
        { &sprPartsTrash03, 10 },
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

void setPlayer(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos, bool isDrawShrink, const bool makeOrgPlayer = false)
// trueならこのobjをplayer_に代入する
{
    //const VECTOR2 pos = { 500,500 };

    OBJ2D* player = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr,
        new PerformComponent
    );

    player->zOrder_ = 3;
    player->actorComponent_->parent_ = player;

    player->transform_->position_ = pos;
    player->renderer_->isDrawShrink_ = isDrawShrink;

    player->actorComponent_->No = ActorComponent::playerNum;
    player->update_ = PLAYER_CORE_UPDATE;

    if (makeOrgPlayer == true) 
    {
        Game::instance()->player_ = obj2dManager->add(player, &playerCoreBehavior, pos);
    }
    else
    {
        obj2dManager->add(player, &playerCoreBehavior, pos);
    }
}


//******************************************************************************
//      プレイヤーのupdate
//******************************************************************************
#define RATIO       (0.7f)
#define PAD_MOVE    (PAD_RIGHT|PAD_LEFT|PAD_DOWN|PAD_UP)

VECTOR2 speedData[16] = {
    { 0, 0 },								        //----
    { 0, -PL_SPEED },						        //---u
    { 0,  PL_SPEED },						        //--d-
    { 0, 0 },								        //--du
    { -PL_SPEED, 0 },						        //-l--
    { -PL_SPEED * RATIO, -PL_SPEED * RATIO },		//-l-u
    { -PL_SPEED * RATIO,  PL_SPEED * RATIO },		//-ld-
    { -PL_SPEED, 0 },						        //-ldu
    { PL_SPEED, 0 },						        //r---
    { PL_SPEED * RATIO, -PL_SPEED * RATIO },		//r--u
    { PL_SPEED * RATIO,  PL_SPEED * RATIO },		//r-d-
    { PL_SPEED, 0 },						        //r-du
    { 0, 0 },								        //rl--
    { 0, -PL_SPEED },						        //rl-u
    { 0,  PL_SPEED },						        //rld-
    { 0, 0 },								        //rldu
};

// 自機本体のupdate
void PLAYER_CORE_UPDATE(OBJ2D* obj)
{
    using namespace GameLib::input;
    ActorComponent* a = obj->actorComponent_;
    Transform*      t = obj->transform_;

    t->velocity_ += speedData[a->padState_ & PAD_MOVE];

    // y軸の減速
    if ( !(a->padState_ & (PAD_DOWN | PAD_UP)) )
    {
        if (t->velocity_.y > 0)
        {
            t->velocity_.y -= PL_SPEED / 2;
            if (t->velocity_.y < 0) t->velocity_.y = 0;
        }
        if (t->velocity_.y < 0)
        {
            t->velocity_.y += PL_SPEED / 2;
            if (t->velocity_.y > 0) t->velocity_.y = 0;
        }
    }

    // x軸の減速
    if ( !(a->padState_ & (PAD_RIGHT | PAD_LEFT)) )
    {
        if (t->velocity_.x > 0)
        {
            t->velocity_.x -= PL_SPEED / 2;
            if (t->velocity_.x < 0) t->velocity_.x = 0;
        }
        if (t->velocity_.x < 0)
        {
            t->velocity_.x += PL_SPEED / 2;
            if (t->velocity_.x > 0) t->velocity_.x = 0;
        }
    }

    // コントローラー操作
    {
        t->velocity_.x += PL_SPEED * GameLib::input::getPadState(0)->leftX;
        t->velocity_.y -= PL_SPEED * GameLib::input::getPadState(0)->leftY;
    }

    // 最大速度チェック
    t->velocity_.x = clamp(t->velocity_.x, -PL_SPEED_MAX, PL_SPEED_MAX);
    t->velocity_.y = clamp(t->velocity_.y, -PL_SPEED_MAX, PL_SPEED_MAX);
}

// パーツのupdate
void PLAYER_PATRS_UPDATE(OBJ2D* obj)
{
    Transform* t       = obj->transform_;
    Transform* parent = Game::instance()->player_->transform_;

    t->velocity_ = parent->velocity_;
}
// タイトル用のupdate
void TITLE_PLAYER_UPDATE(OBJ2D* obj)
{
    using namespace GameLib::input;
    //ActorComponent* a = obj->actorComponent_;
    Transform* t        = obj->transform_;
    const float floor   = 890.0f;
    static bool isBound = false;

    t->velocity_ += {0.1f, 2.5f};

    // 床判定
    if (t->position_.y >= floor)
    {
        // 超過修正
        if (t->position_.y > floor) t->position_.y = floor;

        // バウンド
        t->velocity_.y = -t->velocity_.y * 0.4f;

        // バウンド力が一定以下になったら
        if (t->velocity_.y >= -10)
        {
            t->velocity_ = { 0.0f,0.0f };
            obj->performComponent_->isTrigger = true;
        }
    }
}
// ゲーム(オーバー)用のupdate
void GAME_OVER_PLAYER_UPDATE(OBJ2D* obj)
{
    Transform* t = obj->transform_;

    t->velocity_ += {GAME_OVER_SPEED_X, GAME_OVER_SPEED_Y};
}


//******************************************************************************
//
//      BasePlayerBehavior（プレイヤーのベース）
//
//******************************************************************************
void BasePlayerBehavior::init(OBJ2D* obj) const
{
    obj->collider_->judgeFlag_         = true;
    obj->collider_->isDrawHitRect_     = true;
    obj->collider_->isDrawAttackRect_  = true;

    obj->eraser_ = &erasePlayer;
}

// BasePlayerBehavior::moveY(moveX)念のため残している

//void BasePlayerBehavior::moveY(OBJ2D* obj) const
//{
//    // 省略
//    using namespace GameLib::input;
//    ActorComponent* a = obj->actorComponent_;
//    Transform* t = obj->transform_;
//
//
//    // 斜め移動時の速度を修正
//    const float fixSpeedY = (a->padState_ & PAD_LEFT || a->padState_ & PAD_RIGHT) &&
//                            (a->padState_ & PAD_DOWN || a->padState_ & PAD_UP)
//                            ? 0.71f : 1.0f;
//    const float  fixedAccelY = param_.ACCEL_Y * fixSpeedY;
//
//    // 上下入力の取り出し
//    switch (a->padState_ & (PAD_UP | PAD_DOWN))
//    {
//    case PAD_UP:    // 上だけが押されている場合
//        t->velocity_.y -= fixedAccelY;
//        break;
//    case PAD_DOWN:  // 下だけが押されている場合
//        t->velocity_.y += fixedAccelY;
//        //obj->renderer_->animeData_ = obj->renderer_->animeData_;
//        break;
//    default:        // どちらも押されていないか相殺されている場合
//        if (t->velocity_.y > 0)
//        {
//            t->velocity_.y -= getParam()->ACCEL_Y / 2;
//            if (t->velocity_.y < 0) t->velocity_.y = 0;
//        }
//        if (t->velocity_.y < 0)
//        {
//            t->velocity_.y += getParam()->ACCEL_Y / 2;
//            if (t->velocity_.y > 0) t->velocity_.y = 0;
//        }
//        break;
//    }
//
//    ActorBehavior::moveY(obj);
//}
//
//void BasePlayerBehavior::moveX(OBJ2D* obj) const
//{
//    // 省略
//    using namespace GameLib::input;
//    ActorComponent* a = obj->actorComponent_;
//    Transform*      t = obj->transform_;
//
//
//    // 斜め移動時の速度を修正
//    const float fixSpeedX = (a->padState_ & PAD_LEFT || a->padState_ & PAD_RIGHT) &&
//                            (a->padState_ & PAD_DOWN || a->padState_ & PAD_UP   ) 
//                            ? 0.71f : 1.0f;
//    const float fixedAccelX = param_.ACCEL_X * fixSpeedX;
//
//    // 左右入力の取り出し
//    switch (a->padState_ & (PAD_LEFT | PAD_RIGHT))
//    {
//    case PAD_LEFT:  // 左だけが押されている場合
//        t->velocity_.x -= fixedAccelX;
//        break;
//    case PAD_RIGHT: // 右だけが押されている場合
//        t->velocity_.x += fixedAccelX;
//        break;
//    default:        // どちらも押されていないか相殺されている場合
//        if (t->velocity_.x > 0)
//        {
//            t->velocity_.x -= getParam()->ACCEL_X / 2;
//            if (t->velocity_.x < 0) t->velocity_.x = 0;
//        }
//        if (t->velocity_.x < 0)
//        {
//            t->velocity_.x += getParam()->ACCEL_X / 2;
//            if (t->velocity_.x > 0) t->velocity_.x = 0;
//        }
//        break;
//    }
//
//    ActorBehavior::moveX(obj);
//}

void BasePlayerBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
{
    ActorComponent* dstA = dst->actorComponent_;

    // プレイヤーのHPを減らす
    dstA->hp_ = std::max(dstA->hp_ - getParam()->ATTACK_POWER, 0);

    // 被弾SEを再生
    Audio::play(SE_DMG, false);

    // 相手がまだ生きている場合
    if (dstA->hp_ > 0)
    {
        // 相手を揺らす
        dst->isQuake_ = true;
        // 相手を点滅させる無敵時間
        dstA->damageTimer_ = DMG_TIME;
    }

}

void BasePlayerBehavior::damageProc(OBJ2D* obj) const
{
    ActorComponent* a = obj->actorComponent_;

    // 入力処理
    a->padTrg_   = GameLib::input::TRG(0);
    a->padState_ = GameLib::input::STATE(0);

    // ダメージ処理
    //obj->actorComponent_->damaged();

    // 無敵処理
    //obj->actorComponent_->muteki();

    // 点滅させる
    if (a->damageTimer_ > 0)
    {
        VECTOR4 color = obj->renderer_->color_;
        color.w = a->damageTimer_ & OBJ_DAMAGED_BLINK ? 1.0f : 0.2f;
        obj->renderer_->color_ = color;

        --a->damageTimer_;

        // ダメージタイマーが0以下になるか、縮小中ならcolorを戻す
        if (a->damageTimer_ <= 0 || obj->collider_->isShrink_)
        {
            obj->renderer_->color_ = { 1,1,1,1 };
        }
    }

    if (!obj->isQuake_) return;

    // 揺らす
    static Quake quake;
    quake.quakeDamage(obj);
}

void BasePlayerBehavior::areaCheck(OBJ2D* /*obj*/) const
{
}

//******************************************************************************
//
//      PlayerCoreBehavior（自機本体）
//
//******************************************************************************
PlayerCoreBehavior::PlayerCoreBehavior()
{
    // アニメーション
    param_.ANIME_WAIT    = animePLayerCore;

    param_.SIZE          = { PARTS_OBJ_SIZE * 0.5f, PARTS_OBJ_SIZE * 0.5f };
    param_.SCALE         = { 2.0f,2.0f };

    param_.HIT_BOX[0]    = { -PL_CORE_HITBOX, -PL_CORE_HITBOX, PL_CORE_HITBOX,  PL_CORE_HITBOX };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = PL_CORE_HP;
    param_.ATTACK_POWER  = PL_CORE_ATK;

    // アニメ用データ
    param_.OBJ_ANIME = scaleAnime;
}

void PlayerCoreBehavior::attack(OBJ2D* obj) const
{
    // 体力が0ならreturn
    if (!obj->actorComponent_->isAlive()) return;

    if (Game::instance()->isGameClear()) return;

    // 攻撃クールタイム減少
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // 指定ボタン(Space,A,B,X,Y)が押されていない、または攻撃クールタイムが終わっていなければreturn
    if ( (!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
           obj->actorComponent_->attackTimer_ > 0) return; 

    // 弾を追加
    AddObj::addShot(obj, &plNormalShotBehavior, obj->transform_->position_);

    // 弾発射SE再生
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_CORE_ATK_TIME;

}

void PlayerCoreBehavior::areaCheck(OBJ2D* obj) const
{
    Transform* t = obj->transform_;
    Collider*  c = obj->collider_;

    const float leftLimit   =                (c->size_.x * 0.5f) * t->scale_.x;
    const float rightLimit  = BG::WINDOW_W - (c->size_.x * 0.5f) * t->scale_.x;
    const float topLimit    =                (c->size_.y * 0.5f) * t->scale_.y;
    const float bottomLimit = BG::WINDOW_H - (c->size_.y * 0.5f) * t->scale_.y;

    if (t->position_.x >= rightLimit)
    {
        t->position_.x += rightLimit - t->position_.x;
        if (t->velocity_.x > 0) t->velocity_.x = 0;
    }
    if (t->position_.x <= leftLimit)
    {
        t->position_.x += leftLimit - t->position_.x;
        if (t->velocity_.x < 0) t->velocity_.x = 0;
    }
    if (t->position_.y >= bottomLimit)
    {
        t->position_.y += bottomLimit - t->position_.y;
        if (t->velocity_.y > 0) t->velocity_.y = 0;
    }
    if (t->position_.y <= topLimit)
    {
        t->position_.y += topLimit - t->position_.y;
        if (t->velocity_.y < 0) t->velocity_.y = 0;
    }
}


//******************************************************************************
//
//      partsPlayerBehavior(パーツのベース)
//
//******************************************************************************
// パーツの縮小関数
void PlayerPartsBehavior::shrink(OBJ2D* obj) const
{
    Behavior::shrink(obj);  // 縮小処理
    contactToPlCore(obj, Game::instance()->player_); // 縮小に伴って位置を移動させる処理
}

// オリジナル自機の方に向かって移動する関数
//static const float toCoreVelocity = 0.085f; // 元になる速度(オリジナル自機へ向かう速さに影響)
float PlayerPartsBehavior::toCoreVelocity_ = TO_CORE_SPEED;  // オリジナル自機へ向かう速度
void PlayerPartsBehavior::contactToPlCore(OBJ2D* obj, OBJ2D* orgPl) const
{    
    if (!obj->collider_->isShrink_) return; // 縮小していなければreturn

    const VECTOR2 orgPlPos = orgPl->transform_->position_;  // 自機本体の位置
    const VECTOR2 objPos     = obj->transform_->position_;  // objの位置

    const VECTOR2 d  = { orgPlPos - objPos };               // objから自機本体へ向かうベクトル
    const float dist = sqrtf( (d.x * d.x) + (d.y * d.y) );  // objから自機本体までの距離
                                                             
    float addVelocity = 0.0f;                               // objのvelocityに足す速度
    float num = 0.0f;                                       // for分のiみたいな役割
    const float copyDist = dist >= 0 ? dist : dist * (-1);

    while (true)
    {
        if (num > 999) // 念のために終点を設置
        {
            addVelocity = toCoreVelocity_ * num;
            break;
        }

        // objから自機本体までの距離が遠くなるたび速度を上昇させる
        // (距離が遠すぎるとobjが自機本体に追いつけないため)
        if ((copyDist >=  (50.0f * num) && copyDist <=  50.0f * (num + 1.0f)))  // ±0から±50、±50から±100、±100から±150...
        {
            addVelocity = (num != 0.0f) ? (toCoreVelocity_ * num ): toCoreVelocity_; // ±0から±50までの距離はnumが0なのでデフォルトの値を代入

            break; // 代入したのでbreak;
        }

        // objから自機本体までの距離によって速度を上昇させる
        // (距離が遠すぎるとobjが自機本体に追いつけないため)
        if ((copyDist >= (50.0f * num) && copyDist <= 50.0f * (num + 1.0f)))  // ±0から±50、±50から±100、±100から±150...
        {
            addVelocity = (num != 0) ? (toCoreVelocity_ * num) : toCoreVelocity_;   // ±0から±50までの距離はnumが0なので0.1fを代入

            break; // 代入したのでbreak;
        }
        ++num; // numを加算していく
    }

    obj->transform_->velocity_ = {
        (d.x / dist) * (addVelocity),
        (d.y / dist) * (addVelocity),
    };


    // 位置更新
    obj->transform_->position_ += obj->transform_->velocity_;
}


//******************************************************************************
// 
//      Turret（攻撃砲台パーツ）
// 
//******************************************************************************

// Turret01
PlayerTurret01Behavior::PlayerTurret01Behavior()
{
    param_.ANIME_WAIT    = animeTurret01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = { 
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f, 
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };   
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_TURRET01_ATK;
}

void PlayerTurret01Behavior::attack(OBJ2D* obj) const
{
    if (Game::instance()->isGameClear()) return;

    // 攻撃クールタイム減少
    // （バラバラに打たせるために指定ボタン(Space,A,B,X,Y)を押しているときだけ減らす）
    if ( (obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1 ||
          obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2 ||
          obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3 ||
          obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4) &&
          obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;
    
        // 指定ボタン(Space,A,B,X,Y)が押されていない、または攻撃クールタイムが終わっていなければreturn
    if ( (!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
          !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
            obj->actorComponent_->attackTimer_ > 0) return;

    // 弾を追加
    AddObj::addShot(obj, &plNormalShotBehavior, obj->transform_->position_);

    // 弾発射SE再生
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_PARTS_ATK_TIME;

}

// Turret01(反転)
PlayerTurret01FlipBehavior::PlayerTurret01FlipBehavior()
{
    param_.ANIME_WAIT = animeTurret01Flip;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER = PL_TURRET01_ATK;
}

void PlayerTurret01FlipBehavior::attack(OBJ2D* obj) const
{
    if (Game::instance()->isGameClear()) return;

    // 攻撃クールタイム減少
    // （バラバラに打たせるために指定ボタン(Space,A,B,X,Y)を押しているときだけ減らす）
    if ((obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4) &&
        obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // 指定ボタン(Space,A,B,X,Y)が押されていない、または攻撃クールタイムが終わっていなければreturn
    if ((!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
        obj->actorComponent_->attackTimer_ > 0) return;

    // 弾を追加
    AddObj::addShot(obj, &plNormalShotBehavior, obj->transform_->position_);

    // 弾発射SE再生
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_PARTS_ATK_TIME;

}

// Turret02(CurveShot)
PlayerTurret02Behavior::PlayerTurret02Behavior()
{
    param_.ANIME_WAIT = animeTurret02;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ROTATION = ToRadian(-ENM_TURRET02_ANGLE);

    param_.ATTACK_POWER = PL_TURRET03_ATK;
}

void PlayerTurret02Behavior::attack(OBJ2D* obj) const
{
    if (Game::instance()->isGameClear()) return;

    // 攻撃クールタイム減少
    // （バラバラに打たせるために指定ボタン(Space,A,B,X,Y)を押しているときだけ減らす）
    if ((obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4) &&
        obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // 指定ボタン(Space,A,B,X,Y)が押されていない、または攻撃クールタイムが終わっていなければreturn
    if ((!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
        obj->actorComponent_->attackTimer_ > 0) return;

    // 弾を追加
    const float radius = obj->collider_->size_.x * 0.5f;
    const float angle = obj->transform_->rotation_;
    VECTOR2 pos = obj->transform_->position_;
    pos.x += cosf(angle) * radius;
    pos.y += sinf(angle) * radius;

    AddObj::addShot(obj, &plCurveShotBehavior, pos);

    // 弾発射SE再生
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_PARTS_ATK_TIME;

}

// Turret02Flip
PlayerTurret02FlipBehavior::PlayerTurret02FlipBehavior()
{
    param_.ANIME_WAIT = animeTurret02Flip;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ROTATION = ToRadian(ENM_TURRET02_ANGLE);

    param_.ATTACK_POWER = PL_TURRET03_ATK;
}

void PlayerTurret02FlipBehavior::attack(OBJ2D* obj) const
{
    if (Game::instance()->isGameClear()) return;

    // 攻撃クールタイム減少
    // （バラバラに打たせるために指定ボタン(Space,A,B,X,Y)を押しているときだけ減らす）
    if ((obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4) &&
        obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // 指定ボタン(Space,A,B,X,Y)が押されていない、または攻撃クールタイムが終わっていなければreturn
    if ((!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
        obj->actorComponent_->attackTimer_ > 0) return;

    // 弾を追加
    const float radius = obj->collider_->size_.x * 0.5f;
    const float angle = obj->transform_->rotation_;
    VECTOR2 pos = obj->transform_->position_;
    pos.x += cosf(angle) * radius;
    pos.y += sinf(angle) * radius;

    AddObj::addShot(obj, &plCurveShotFlipBehavior, pos);

    // 弾発射SE再生
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_PARTS_ATK_TIME;

}

// Turret03(貫通弾）
PlayerTurret03Behavior::PlayerTurret03Behavior()
{
    param_.ANIME_WAIT = animeTurret03;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER = PL_TURRET03_ATK;
}

void PlayerTurret03Behavior::attack(OBJ2D* obj) const
{
    if (Game::instance()->isGameClear()) return;

    // 攻撃クールタイム減少
    // （バラバラに打たせるために指定ボタン(Space,A,B,X,Y)を押しているときだけ減らす）
    if ((obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3 ||
        obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4) &&
        obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // 指定ボタン(Space,A,B,X,Y)が押されていない、または攻撃クールタイムが終わっていなければreturn
    if ((!(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG1) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG2) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) &&
        !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG4)) ||
        obj->actorComponent_->attackTimer_ > 0) return;

    // 弾を追加
    AddObj::addShot(obj, &plPenetrateShotBehavior, obj->transform_->position_);

    // 弾発射SE再生
    Audio::play(SE_SHOT, false);

    setXAxisScaleAnime(obj);
    obj->actorComponent_->attackTimer_ = PL_PARTS_ATK_TIME;

}


//******************************************************************************
// 
//      Shield（防御パーツ）
// 
//******************************************************************************

// Shield01
PlayerShield01Behavior::PlayerShield01Behavior()
{
    param_.ANIME_WAIT    = animeShield01;
                         
    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
                         
    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.25f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.25f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_SHIELD01_ATK;
}


//******************************************************************************
// 
//      Buff（バフパーツ）
// 
//******************************************************************************

//Buff01
static constexpr int BUFF_MALTIPLY_VALUE = 2; // ATTACK_BOXにかける値（バフの影響範囲が変わる）
PlayerBuff01Behavior::PlayerBuff01Behavior()
{
    param_.ANIME_WAIT    = animeBuff01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = { 
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = { 
        -PARTS_OBJ_SIZE * 0.6f, 
        -PARTS_OBJ_SIZE * 0.6f,
         PARTS_OBJ_SIZE * 0.6f,  
         PARTS_OBJ_SIZE * 0.6f,
    };

    param_.ATTACK_POWER  = PL_BUFF01_ATK;
}                            

// 攻撃タイプがPLAYERなのでdstは味方(プレイヤー)になる(代わりに体当たりダメージが与えられない)
void PlayerBuff01Behavior::hit(OBJ2D*, OBJ2D* dst) const
{
    // 攻撃クールタイムを減少（弾速上昇）
    dst->actorComponent_->attackTimer_ -= BUFF_SUB_ATK_TIMER; 
}


//******************************************************************************
// 
//      Trash(ゴミパーツ)
// 
//******************************************************************************

// Trash01
PlayerTrash01Behavior::PlayerTrash01Behavior()
{
    param_.ANIME_WAIT    = animeTrash01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = { 
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f, 
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f 
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_TRASH01_ATK;
}

// Trash02
PlayerTrash02Behavior::PlayerTrash02Behavior()
{
    param_.ANIME_WAIT    = animeTrash02;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_TRASH02_ATK;
}

// Trash03
PlayerTrash03Behavior::PlayerTrash03Behavior()
{
    param_.ANIME_WAIT    = animeTrash03;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_TRASH03_ATK;
}


//******************************************************************************
// 
//      Common(効果なしパーツ)
// 
//******************************************************************************

// Common01
PlayerCommon01Behavior::PlayerCommon01Behavior()
{
    param_.ANIME_WAIT    = animeCommon01;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_64,-COMMON_HITBOX_18,
          COMMON_HITBOX_64, COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON01_ATK;
}

// Common01_2(90度回転)
PlayerCommon01_2Behavior::PlayerCommon01_2Behavior()
{
    //param_.ANIME_WAIT    = animeCommon01;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18,-COMMON_HITBOX_64,
          COMMON_HITBOX_18, COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON04_ATK;
}

// Common02
PlayerCommon02Behavior::PlayerCommon02Behavior()
{
    param_.ANIME_WAIT    = animeCommon02;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_64,-COMMON_HITBOX_18,
          COMMON_HITBOX_64, COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON02_ATK;
}

// Common02_2(90度回転)
PlayerCommon02_2Behavior::PlayerCommon02_2Behavior()
{
    param_.ANIME_WAIT    = animeCommon02;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18,-COMMON_HITBOX_64,
          COMMON_HITBOX_18, COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON05_ATK;
}

// Common03
PlayerCommon03Behavior::PlayerCommon03Behavior()
{
    param_.ANIME_WAIT    = animeCommon03;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_64,-COMMON_HITBOX_18,
          COMMON_HITBOX_64, COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON03_ATK;
}

// Common03_2(90度回転)
PlayerCommon03_2Behavior::PlayerCommon03_2Behavior()
{
    param_.ANIME_WAIT    = animeCommon03;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18,-COMMON_HITBOX_64,
          COMMON_HITBOX_18, COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ATTACK_POWER  = PL_COMMON06_ATK;
}


//******************************************************************************
// 
//      erase（消去）
// 
//******************************************************************************

// 親探し(ナシだと壊れた時の爽快感がある)
#define USE_FIND_PARENT

bool ErasePlayer::isPartsClear = false;

void ErasePlayer::erase(OBJ2D* obj) const
{
    // behaviorがなければreturn
    if (!obj->behavior_) return;

    ActorComponent* a = obj->actorComponent_;

    //  PL以外を消す(ゲームクリアの処理で使用)
    if (isPartsClear && obj != a->parent_) obj->behavior_ = nullptr;

    // HPが0以下になるか、GameOverなら
    if (!a->isAlive() || Game::instance()->isGameOver())
    {
        // 本体の場合
        if (obj == Game::instance()->player_)
        {
            if (!obj->performComponent_->isTrigger)
            {
                // Triggerをtrueに(GameOverのフラグが立つ)
                obj->performComponent_->isTrigger = true;
            }
            return;
        }

        // 爆発エフェクト
        AddObj::addEffect(obj, &efcBombBehavior);

        // 死亡SE
        Audio::play(SE_DEATH, false);

        a->parent_     = nullptr; // 親情報をリセット
        obj->behavior_ = nullptr; // 自分を消去

        // 縮小カウント減少
        BasePlayerBehavior::plShrinkCount_ = std::max(
            0, BasePlayerBehavior::plShrinkCount_ - 1
        );

        --BasePlayerBehavior::plPartsCurrentCount_;

        return;
    }


    // 親が存在しなければ
    if (!a->parent_)
    {      
        ++a->deathDelayTimer_; // 死亡ディレイタイマーを加算する
    }
    else // 親が存在していて
    {
        if (a->parent_->behavior_) return;   // 親がまだ生きていればreturn

        // 死んでいれば

        // 新しい親を探す
#ifdef  USE_FIND_PARENT
        for (auto& dst : *Game::instance()->obj2dManager()->getList())
        {
            if (!dst->behavior_) continue;                               // 相手が存在しなければcontinue;
            if (obj == dst)      continue;                               // 相手が自分ならcontinue;

            if (!obj->collider_->hitCheck(dst->collider_)) continue;     // 相手が接触していなければcontinue;

            if (dst->behavior_->getType() != OBJ_TYPE::PLAYER) continue; // 相手が自分と同じプレイヤーでなければcontinue

            if (!dst->actorComponent_->parent_) continue;                // 相手が親を持っていなければcontinue;
            if (obj == dst->actorComponent_->parent_) continue;          // 相手が自分の子ならcontinue;

            obj->actorComponent_->parent_ = dst;                         // 相手を親にする

            return; // 親が見つかったのでreturn
        }
#endif

        // 親が見つからなかった場合

        obj->actorComponent_->parent_ = nullptr; // 親情報をリセット

        // 縮小カウント減少
        BasePlayerBehavior::plShrinkCount_ = std::max(0, --BasePlayerBehavior::plShrinkCount_);

        --BasePlayerBehavior::plPartsCurrentCount_;

        return;
    }
    

    if (a->deathDelayTimer_ < PARTS_DEATH_DELAY_TIME) return;

    // 死亡ディレイタイマーが一定時間たったら死亡処理を行う
    //（親が死んだときのパーツの連鎖爆散に遅延をつくりだす）

    // 爆発エフェクト
    AddObj::addEffect(obj, &efcBombBehavior);

    // 死亡SE
    Audio::play(SE_DEATH, false);

    obj->behavior_ = nullptr; // 自分を消去

    return;
}

#undef USE_FIND_PARENT



//// 仮
//void setCursor(OBJ2DManager* obj2dManager, BG* bg)
//{
//    const VECTOR2 pos = { 100,100 };
//
//    OBJ2D* cursor = new OBJ2D(
//        new Renderer,
//        new Collider,
//        bg,
//        new ActorComponent,
//        nullptr,
//        nullptr
//    );
//
//    cursor->zOrder_ = 4;
//    cursor->actorComponent_->parent_ = cursor;
//
//    Game::instance()->cursor_ = obj2dManager->add(cursor, &cursorBehavior, pos);
//}
//
//// カーソルの座標取得
//VECTOR2 getCursorPoint()
//{
//    static POINT point_;
//
//    GetCursorPos(&point_);
//    ScreenToClient(GetActiveWindow(), &point_);
//
//    VECTOR2 pos = { static_cast<float>(point_.x), 
//                    static_cast<float>(point_.y) 
//    };
//    return pos;
//}
//
//void CursorBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
//{
//    if ( (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4) ||
//         (GetAsyncKeyState(VK_LBUTTON) & 1) )
//    {
//        dst->behavior_ = nullptr;
//    
//        // 縮小カウント減少
//        BasePlayerBehavior::plShrinkCount_ = std::max(0, BasePlayerBehavior::plShrinkCount_ - 1);
//    }
//}