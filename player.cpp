#include "all.h"


int BasePlayerBehavior::plShrinkCount_ = 0;

// アニメデータ
namespace
{
    // 待機
    GameLib::AnimeData animePlayerCore01[] = {
        { &sprPlayerCore01, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    //  タレット01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
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

void setPlayer(OBJ2DManager* obj2dManager, BG* bg, const bool makeOrgPlayer = false) // trueならこのobjをplayer_に代入する
{
    const VECTOR2 pos = { 500,500 };

    OBJ2D* player = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    player->zOrder_ = 3;
    player->actorComponent_->parent_ = player;

    player->actorComponent_->No = ActorComponent::playerNum;

    if (makeOrgPlayer == true) 
    {
        //Game::instance()->player_ = obj2dManager->add(player, &normalPlayerBehavior, pos); 
        Game::instance()->player_ = obj2dManager->add(player, &corePlayerBehavior, pos);
    }
    else
    {
        //obj2dManager->add(player, &normalPlayerBehavior, pos);
        obj2dManager->add(player, &corePlayerBehavior, pos);
    }
}
// 仮
void setCursor(OBJ2DManager* obj2dManager, BG* bg)
{
    const VECTOR2 pos = { 100,100 };

    OBJ2D* cursor = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    cursor->zOrder_ = 4;
    cursor->actorComponent_->parent_ = cursor;

    Game::instance()->cursor_ = obj2dManager->add(cursor, &cursorBehavior, pos);
}


//******************************************************************************
//
//      BasePlayerBehavior（プレイヤーのベース）
//
//******************************************************************************
void BasePlayerBehavior::init(OBJ2D* obj) const
{
    obj->collider_->judgeFlag_ = true;
    obj->collider_->isDrawHitRect_ = true;
    obj->collider_->isDrawAttackRect_ = true;

    obj->eraser_ = &erasePlayer;
}

void BasePlayerBehavior::moveY(OBJ2D* obj) const
{
    // 左右入力の取り出し
    switch (obj->actorComponent_->padState_ & (GameLib::input::PAD_UP | GameLib::input::PAD_DOWN))
    {
    case GameLib::input::PAD_UP:  // 上だけが押されている場合
        obj->transform_->velocity_.y -= getParam()->ACCEL_Y;
        break;
    case GameLib::input::PAD_DOWN: // 下だけが押されている場合
        obj->transform_->velocity_.y += getParam()->ACCEL_Y;
        obj->renderer_->animeData_ = obj->renderer_->animeData_;
        break;
    default:        // どちらも押されていないか相殺されている場合
        if (obj->transform_->velocity_.y > 0)
        {
            obj->transform_->velocity_.y -= getParam()->ACCEL_Y / 2;
            if (obj->transform_->velocity_.y < 0) obj->transform_->velocity_.y = 0;
        }
        if (obj->transform_->velocity_.y < 0)
        {
            obj->transform_->velocity_.y += getParam()->ACCEL_Y / 2;
            if (obj->transform_->velocity_.y > 0) obj->transform_->velocity_.y = 0;
        }
        break;
    }

    ActorBehavior::moveY(obj);
}

void BasePlayerBehavior::moveX(OBJ2D* obj) const
{
    // 左右入力の取り出し
    switch (obj->actorComponent_->padState_ & (GameLib::input::PAD_LEFT | GameLib::input::PAD_RIGHT))
    {
    case GameLib::input::PAD_LEFT:  // 左だけが押されている場合
        obj->transform_->velocity_.x -= getParam()->ACCEL_X;
        break;
    case GameLib::input::PAD_RIGHT: // 右だけが押されている場合
        obj->transform_->velocity_.x += getParam()->ACCEL_X;
        break;
    default:        // どちらも押されていないか相殺されている場合
        if (obj->transform_->velocity_.x > 0)
        {
            obj->transform_->velocity_.x -= getParam()->ACCEL_X / 2;
            if (obj->transform_->velocity_.x < 0) obj->transform_->velocity_.x = 0;
        }
        if (obj->transform_->velocity_.x < 0)
        {
            obj->transform_->velocity_.x += getParam()->ACCEL_X / 2;
            if (obj->transform_->velocity_.x > 0) obj->transform_->velocity_.x = 0;
        }
        break;
    }

    ActorBehavior::moveX(obj);
}

void BasePlayerBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
{
    // 敵のHPを減らす
    dst->actorComponent_->hp_ -= getParam()->ATTACK_POWER;

    //if (!src->actorComponent_->parent_) return; // もし自分が親、または親持ちでないか、
    //if (dst->actorComponent_->parent_) return;  // 相手が親を持っていない場合はcontinue;
    //
    //dst->actorComponent_->parent_ = src;        // 親を保存   
}

bool BasePlayerBehavior::isAlive(OBJ2D*) const
{
    return true;    // 生存している（仮）
}

void BasePlayerBehavior::damageProc(OBJ2D* obj) const
{
    // 入力処理
    obj->actorComponent_->padTrg_ = GameLib::input::TRG(0);
    obj->actorComponent_->padState_ = GameLib::input::STATE(0);

    // ダメージ処理
    obj->actorComponent_->damaged();

    // 無敵処理
    obj->actorComponent_->muteki();

    //if (GameLib::input::STATE(0) & GameLib::input::PAD_TRG2)
    //if (obj->actorComponent_->parent_->behavior_ != nullptr)
    //{
    //    GameLib::debug::setString("No:%d→[%d]", obj->actorComponent_->No,
    //        obj->actorComponent_->parent_->actorComponent_->No);
    //}
    //else
    //{
    //    GameLib::debug::setString("No:%d→[×]", obj->actorComponent_->No);
    //}
}

void BasePlayerBehavior::areaCheck(OBJ2D* /*obj*/) const
{
    //// 仮
    //if (obj->transform_->position_.x < obj->collider_->size_.x)
    //{
    //    obj->transform_->position_.x = obj->collider_->size_.x;
    //}
    //if (obj->transform_->position_.x > BG::WINDOW_W - obj->collider_->size_.x)
    //{
    //    obj->transform_->position_.x = BG::WINDOW_W - obj->collider_->size_.x;
    //}

    //if (obj->transform_->position_.y < obj->collider_->size_.y)
    //{
    //    obj->transform_->position_.y = obj->collider_->size_.y;
    //}
    //if (obj->transform_->position_.y > BG::WINDOW_H - obj->collider_->size_.y)
    //{
    //    obj->transform_->position_.y = BG::WINDOW_H - obj->collider_->size_.y;
    //}
}

//******************************************************************************
//
//      corePlayerBehavior（自機本体）
//
//******************************************************************************
CorePlayerBehavior::CorePlayerBehavior()
{
    // アニメーション
    param_.ANIME_WAIT    = animePlayerCore01;

    param_.SIZE    = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -player_hitBox, -player_hitBox, player_hitBox, player_hitBox };
    //param_.HIT_BOX = { -50, -175, 50, -75 };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP = 1000;

    // 速度関連のパラメータ
    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void CorePlayerBehavior::attack(OBJ2D* obj) const
{
    // 攻撃クールタイム減少
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // 指定ボタンが押されていない、または攻撃クールタイムが終わっていなければreturn
    if ( !(obj->actorComponent_->padState_ & GameLib::input::PAD_TRG3) ||
           obj->actorComponent_->attackTimer_ > 0) return; 

    // 後々(inline)関数化したい
    {
        const VECTOR2 pos = obj->transform_->position_/* + VECTOR2(0, -120)*/;

        OBJ2D* shot = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg_,
                nullptr,
                nullptr,
                new WeaponComponent
            ),
            &plPenetrateShotBehavior,
            pos
        );
        shot->zOrder_ = 2;
        shot->weaponComponent_->parent_ = obj;

    }

    obj->actorComponent_->attackTimer_ = 30;

}


//******************************************************************************
//
//      partsPlayerBehavior(パーツのベース)
//
//******************************************************************************
// パーツの縮小関数
void PartsPlayerBehavior::shrink(OBJ2D* obj) const
{
    Behavior::shrink(obj);  // 縮小処理
    contact(obj);           // 縮小に伴って位置を移動させる処理
}

// 接触する関数
void PartsPlayerBehavior::contact(OBJ2D* obj) const
{
    if (!obj->collider_->isShrink_) return; // 縮小していなければreturn

    // オリジナル自機の方へ移動する処理
    contactToOriginal(obj, Game::instance()->player_); 

    OBJ2D* parent = obj->actorComponent_->parent_;              // 自分の親のデータ
    if (parent->collider_->hitCheck(obj->collider_)) return;    // 親と接触していればreturn

    // 親の方へ移動する処理
    contactToParent(obj, parent); // (親とくっついていないobjがオリジナル自機に向かって突っ込んでいくのを軽減)
}

// オリジナル自機の方に向かって移動する関数
static const float toCoreVelocity = 0.085f; // 元になる速度(オリジナル自機へ向かう速さに影響)
void PartsPlayerBehavior::contactToOriginal(OBJ2D* obj, OBJ2D* original) const
{    
    const VECTOR2 orginalPos = original->transform_->position_; // 自機本体の位置
    const VECTOR2 objPos     = obj->transform_->position_;      // objの位置

    const VECTOR2 d  = { orginalPos - objPos };              // objから自機本体へ向かうベクトル
    const float dist = sqrtf( (d.x * d.x) + (d.y * d.y) );   // objから自機本体までの距離
                                                             
    float addVelocity = 0.0f;                                // objのvelocityに足す速度
    float num = 0.0f;                                        // for分のiみたいな役割
    const float copyDist = dist > 0 ? dist : -dist;          //
    while (true)
    {
        if (num > 100) // 一定以上数が増えてshrinkするとなぜか下のif処理で固まるので応急処置
        {
            addVelocity = toCoreVelocity * num;
            break;
        }

        // objから自機本体までの距離によって速度を上昇させる
        // (距離が遠すぎるとobjが自機本体に追いつけないため)
        if ((copyDist >=  (50.0f * num) && copyDist <=  50.0f * (num + 1.0f)))  // ±0から±50、±50から±100、±100から±150...
        {
            addVelocity = (num != 0) 
                        ? toCoreVelocity * num 
                        : 0.1f;    // ±0から±50までの距離はnumが0なので0.1fを代入

            break; // 代入したのでbreak;
        }
        ++num; // numを加算していく
    }

    obj->transform_->velocity_ = {
        (d.x / dist) * (addVelocity/* / obj->transform_->scale_.x*/), // scaleが小さくなった時に速度が落ちないようscaleで割る
        (d.y / dist) * (addVelocity/* / obj->transform_->scale_.y*/)
    };

    ActorBehavior::moveY(obj);
    ActorBehavior::moveX(obj);

    //obj->collider_->calcHitBox(getParam()->HIT_BOX);
    //obj->collider_->calcAttackBox(getParam()->ATTACK_BOX);
}

// 親の方に向かって移動する関数
static const float toParentVelocity = 0.5f; // 足す速度(親へ向かう速さに影響)
void PartsPlayerBehavior::contactToParent(OBJ2D* obj, OBJ2D* parent) const
{    
    const VECTOR2 parentPos = parent->transform_->position_;    // 親の位置
    const VECTOR2 objPos    = obj->transform_->position_;       // objの位置

    const VECTOR2 d  = { parentPos - objPos };               // objから親へ向かうベクトル
    const float dist = sqrtf( (d.x * d.x) + (d.y * d.y) );   // objから親までの距離

    obj->transform_->velocity_ = {
        (d.x / dist) * (toParentVelocity),
        (d.y / dist) * (toParentVelocity)
    };

    ActorBehavior::moveY(obj);
    ActorBehavior::moveX(obj);

    //obj->collider_->calcHitBox(getParam()->HIT_BOX);
    //obj->collider_->calcAttackBox(getParam()->ATTACK_BOX);
}



//******************************************************************************
// 
//      Turret（攻撃砲台パーツ）
// 
//******************************************************************************

// Turret01
PlayerTurret01Behavior::PlayerTurret01Behavior()
{
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -80, 48, 125, 95 };    // 下長方形
    param_.HIT_BOX[1] = { -125,-95,10,50 };      // ネジ

    param_.ATTACK_BOX[0] = { -80, 48, 125, 95 }; // 下長方形
    param_.ATTACK_BOX[1] = { -125,-95,10,50 };   // ネジ

    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    //param_.JUMP_POWER_Y = -12.0f;

}

void PlayerTurret01Behavior::attack(OBJ2D* obj) const
{
    // 攻撃クールタイム減少
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // 攻撃クールタイムが終わっていなければreturn
    if (obj->actorComponent_->attackTimer_ > 0) return;

    // 後々(inline)関数化したい
    {
        const VECTOR2 pos = obj->transform_->position_/* + VECTOR2(0, -120)*/;

        OBJ2D* shot = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg_,
                nullptr,
                nullptr,
                new WeaponComponent
            ),
            &playerNormalShotBehavior,
            pos
        );
        shot->zOrder_ = 2;
        shot->weaponComponent_->parent_ = obj;
    }

    obj->actorComponent_->attackTimer_ = 30;

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
    param_.ANIME_WAIT = animeBuff01;

    param_.SIZE = { player_size, player_size };
    param_.HIT_BOX[0] = { 
        -player_hitBox, -player_hitBox, 
         player_hitBox,  player_hitBox,
    };
    param_.ATTACK_BOX[0] = { 
        -player_hitBox * BUFF_MALTIPLY_VALUE, 
        -player_hitBox * BUFF_MALTIPLY_VALUE,
         player_hitBox * BUFF_MALTIPLY_VALUE,  
         player_hitBox * BUFF_MALTIPLY_VALUE,
    };

    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
}                            

// 攻撃タイプがPLAYERなのでdstは味方(プレイヤー)になる
void PlayerBuff01Behavior::hit(OBJ2D*, OBJ2D* dst) const
{
    dst->actorComponent_->attackTimer_ += -1; // 攻撃クールタイムを減少（弾速上昇）
}


//******************************************************************************
// 
//      Trash(ゴミパーツ)
// 
//******************************************************************************
PlayerTrash01Behavior::PlayerTrash01Behavior()
{
    param_.ANIME_WAIT = animeTrash01;

    param_.SIZE = { player_size, player_size };
    param_.HIT_BOX[0] = {
        -player_hitBox, -player_hitBox,
         player_hitBox,  player_hitBox,
    };
    param_.ATTACK_BOX[0] = {
        -player_hitBox,
        -player_hitBox,
         player_hitBox,
         player_hitBox,
    };

    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
}


//******************************************************************************
// 
//      erase（消去）
// 
//******************************************************************************
// 親探し(ナシだと壊れた時の爽快感がある)
#define USE_FIND_PARENT

void ErasePlayer::erase(OBJ2D* obj) const
{
    // HPが0以下になったら
    if (!obj->actorComponent_->isAlive())
    {
        obj->behavior_ = nullptr;
    }

    if (obj->actorComponent_->parent_->behavior_) return;   // もし自分の親が存在するならreturn

#ifdef USE_FIND_PARENT
    // 新しい親を探す
    for (auto& dst : *Game::instance()->obj2dManager()->getList())
    {
        if (!dst->behavior_) continue;                      // 相手が存在しなければcontinue;
        if (obj == dst) continue;                           // 相手が自分ならcontinue;
        if (!dst->actorComponent_) continue;                // 相手がactorComponent_を持っていなければcontinue;
        if (!dst->actorComponent_->parent_) continue;       // 相手が親を持っていなければcontinue;
        if (obj == dst->actorComponent_->parent_) continue; // 相手が自分の子ならcontinue;

        if (!obj->collider_->hitCheck(dst->collider_)) continue; // 相手が接触していなければcontinue;

        obj->actorComponent_->parent_ = dst;                // 相手を親にする

        return; // 親が見つかっているのでreturn
    }
#endif

    // 親が見つからなかった場合
    obj->actorComponent_->parent_ = nullptr; // 親情報をリセット
    obj->behavior_ = nullptr;                // 自分を消去
    return;
}


//******************************************************************************
// 
//      CusorBehavior（カーソル）（仮）
// 
//****************************************************************************** 
CursorBehavior::CursorBehavior()
{
    param_.SIZE = VECTOR2( 5, 5);
    param_.HIT_BOX[0] = { -5, -5, 5 , 5 };
    param_.ATTACK_BOX[0] = { -5, -5, 5 , 5 };

    // 速度関連のパラメータ
    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

// カーソルの座標取得
VECTOR2 getCursorPoint()
{
    static POINT point_;

    GetCursorPos(&point_);
    ScreenToClient(GetActiveWindow(), &point_);

    VECTOR2 pos = { static_cast<float>(point_.x), 
                    static_cast<float>(point_.y) 
    };
    return pos;
}

void CursorBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
{
    if ( (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4) ||
         (GetAsyncKeyState(VK_LBUTTON) & 1) )
    {
        dst->behavior_ = nullptr;
    }
}

void CursorBehavior::damageProc(OBJ2D* obj) const
{
    obj->transform_->position_ = getCursorPoint();
}