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
        Game::instance()->player_ = obj2dManager->add(player, &corePlayerBehavior, pos, PLAYER_UPDATE);
    }
    else
    {
        //obj2dManager->add(player, &normalPlayerBehavior, pos);
        obj2dManager->add(player, &corePlayerBehavior, pos, PLAYER_UPDATE);
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

    Game::instance()->cursor_ = obj2dManager->add(cursor, &cursorBehavior, pos,nullptr);
}

//******************************************************************************
//      エネミーのupdate
//******************************************************************************
#define RATIO 0.7f
#define PAD_MOVE		(PAD_RIGHT|PAD_LEFT|PAD_DOWN|PAD_UP)

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
void PLAYER_UPDATE(OBJ2D* obj)
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

    // 最大速度チェック
    t->velocity_.x = clamp(t->velocity_.x, -PL_SPEED_MAX, PL_SPEED_MAX);
    t->velocity_.y = clamp(t->velocity_.y, -PL_SPEED_MAX, PL_SPEED_MAX);

    // 移動
    t->position_ += t->velocity_;
}

#undef RATIO
#undef PAD_MOVE


// パーツのupdate
void PATRS_PLAYER_UPDATE(OBJ2D* obj)
{
    Transform* t       = obj->transform_;
    Transform* parentT = Game::instance()->player_->transform_;

    t->position_ += parentT->velocity_;
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
    // 敵のHPを減らす
    dst->actorComponent_->hp_ -= getParam()->ATTACK_POWER;
}

void BasePlayerBehavior::damageProc(OBJ2D* obj) const
{
    // 入力処理
    obj->actorComponent_->padTrg_   = GameLib::input::TRG(0);
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

    //param_.HP = 1000;
    param_.HP = CORE_PLAYER_HP;

    // アニメ用データ
    param_.OBJ_ANIME = scaleAnime;
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
            &plNormalShotBehavior,     // ノーマル
            //&plSineWaveShotBehavior,   // 正弦波
            //&plSquareWaveShotBehavior, // 矩形波
            //&plCurveWaveShotBehavior,  // 上カーブ
            //&plPenetrateShotBehavior,  // 高速・貫通(予定)
            pos,
            nullptr
        );
        shot->zOrder_ = 2;
        shot->weaponComponent_->parent_ = obj;

    }


    setXAxisScaleAnime(obj);
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
    contactToOriginal(obj, Game::instance()->player_); // 縮小に伴って位置を移動させる処理
}

// オリジナル自機の方に向かって移動する関数
//static const float toCoreVelocity = 0.085f; // 元になる速度(オリジナル自機へ向かう速さに影響)
float PartsPlayerBehavior::toCoreVelocity = TO_CORE_SPEED;  // オリジナル自機へ向かう速度
void PartsPlayerBehavior::contactToOriginal(OBJ2D* obj, OBJ2D* orgPl) const
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
            addVelocity = toCoreVelocity * num;
            break;
        }

        // objから自機本体までの距離が遠くなるたび速度を上昇させる
        // (距離が遠すぎるとobjが自機本体に追いつけないため)
        if ((copyDist >=  (50.0f * num) && copyDist <=  50.0f * (num + 1.0f)))  // ±0から±50、±50から±100、±100から±150...
        {
            addVelocity = (num != 0.0f) ? (toCoreVelocity * num ): toCoreVelocity; // ±0から±50までの距離はnumが0なのでデフォルトの値を代入

            break; // 代入したのでbreak;
        }

        // objから自機本体までの距離によって速度を上昇させる
        // (距離が遠すぎるとobjが自機本体に追いつけないため)
        if ((copyDist >= (50.0f * num) && copyDist <= 50.0f * (num + 1.0f)))  // ±0から±50、±50から±100、±100から±150...
        {
            addVelocity = (num != 0) ? (toCoreVelocity * num) : toCoreVelocity;   // ±0から±50までの距離はnumが0なので0.1fを代入

            break; // 代入したのでbreak;
        }
        ++num; // numを加算していく
    }

    obj->transform_->velocity_ = {
        (d.x / dist) * (addVelocity),
        (d.y / dist) * (addVelocity),
    };


    // 最大速度チェックを行う
    obj->transform_->velocity_.y = clamp(
        obj->transform_->velocity_.y, -PL_SPEED_MAX, PL_SPEED_MAX
    );
    obj->transform_->velocity_.x = clamp(
        obj->transform_->velocity_.x, -PL_SPEED_MAX, PL_SPEED_MAX
    );
    // 位置更新
    obj->transform_->position_ += obj->transform_->velocity_;
}

// 親の方に向かって移動する関数
//static const float toParentVelocity = 0.5f; // 足す速度(親へ向かう速さに影響)
//void PartsPlayerBehavior::contactToParent(OBJ2D* obj, OBJ2D* parent) const
//{    
//    const VECTOR2 parentPos = parent->transform_->position_;    // 親の位置
//    const VECTOR2 objPos    = obj->transform_->position_;       // objの位置
//
//    const VECTOR2 d  = { parentPos - objPos };               // objから親へ向かうベクトル
//    const float dist = sqrtf( (d.x * d.x) + (d.y * d.y) );   // objから親までの距離
//
//    obj->transform_->velocity_ = {
//        (d.x / dist) * (toParentVelocity),
//        (d.y / dist) * (toParentVelocity)
//    };
//
//    ActorBehavior::moveY(obj);
//    ActorBehavior::moveX(obj);
//
//    //obj->collider_->calcHitBox(getParam()->HIT_BOX);
//    //obj->collider_->calcAttackBox(getParam()->ATTACK_BOX);
//}



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

    // 画像サイズ(128*64の半分)
    param_.HIT_BOX[0] = { -64, -32, 64, 32 };    // 下長方形
    //param_.HIT_BOX[1] = { -125,-95,10,50 };      // ネジ

    param_.ATTACK_BOX[0] = param_.HIT_BOX[0]; // 下長方形
    //param_.ATTACK_BOX[1] = param_.HIT_BOX[1];   // ネジ
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
            &plNormalShotBehavior,
            pos,
            nullptr
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
        obj->actorComponent_->parent_ = nullptr; // 親情報をリセット
        obj->behavior_ = nullptr;

        // 縮小カウント減少
        BasePlayerBehavior::plShrinkCount_ = std::max(0, BasePlayerBehavior::plShrinkCount_ - 1);

        return; // returnを付ける
    }

    if (obj->actorComponent_->parent_->behavior_) return;   // 自分の親が存在するならreturn


    // 新しい親を探す
#ifdef USE_FIND_PARENT
    for (auto& dst : *Game::instance()->obj2dManager()->getList())
    {
        if (!dst->behavior_) continue;                      // 相手が存在しなければcontinue;
        if (obj == dst) continue;                           // 相手が自分ならcontinue;

        if (dst->behavior_->getType() != OBJ_TYPE::PLAYER) continue; // 相手が自分と同じプレイヤーでなければcontinue

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

    // 縮小カウント減少
    BasePlayerBehavior::plShrinkCount_ = std::max(0, BasePlayerBehavior::plShrinkCount_ - 1);
    return;
}
#undef USE_FIND_PARENT


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

        // 縮小カウント減少
        BasePlayerBehavior::plShrinkCount_ = std::max(0, BasePlayerBehavior::plShrinkCount_ - 1);
    }
}

void CursorBehavior::damageProc(OBJ2D* obj) const
{
    obj->transform_->position_ = getCursorPoint();
}