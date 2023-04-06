//******************************************************************************
//
//
//      プレイヤークラス
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//******************************************************************************
//
//      プレイヤー移動処理
//
//******************************************************************************

//------< プレイヤーのアニメデータ(仮) >----------------------------------------------
namespace
{   // ※このデータは長いので、Visual Studioの機能で閉じられるようにnamespaceを分けている

    //------< プレイヤーのアニメデータ >------------------------------------------
    //上方向
    GameLib::AnimeData sprPlayer_Up[] = {
        { &sprEnemey_test, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //右方向
    GameLib::AnimeData sprPlayer_Right[] = {
        { &sprEnemey_test, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //下方向
    GameLib::AnimeData sprPlayer_Down[] = {
        { &sprEnemey_test, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //左方向
    GameLib::AnimeData sprPlayer_Left[] = {
        { &sprEnemey_test, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// 終了フラグ
    };
}

//namespace
//{   // ※このデータは長いので、Visual Studioの機能で閉じられるようにnamespaceを分けている
//
//    //------< プレイヤーのアニメデータ >------------------------------------------
//    //上方向
//    GameLib::AnimeData animeEnemey_Up[] = {
//        { &sprPlayer_Up0, 10 },
//        { &sprPlayer_Up1, 10 },
//        { &sprPlayer_Up2, 10 },
//        { &sprPlayer_Up1, 10 },
//        { nullptr, -1 },// 終了フラグ
//    };
//    //右方向
//    GameLib::AnimeData animeEnemey_Right[] = {
//        { &sprPlayer_Right0, 10 },
//        { &sprPlayer_Right1, 10 },
//        { &sprPlayer_Right2, 10 },
//        { &sprPlayer_Right1, 10 },
//        { nullptr, -1 },// 終了フラグ
//    };
//    //下方向
//    GameLib::AnimeData animeEnemey_Down[] = {
//        { &sprPlayer_Down0, 10 },
//        { &sprPlayer_Down1, 10 },
//        { &sprPlayer_Down2, 10 },
//        { &sprPlayer_Down1, 10 },
//        { nullptr, -1 },// 終了フラグ
//    };
//    //左方向
//    GameLib::AnimeData animeEnemey_Left[] = {
//        { &sprPlayer_Left0, 10 },
//        { &sprPlayer_Left1, 10 },
//        { &sprPlayer_Left2, 10 },
//        { &sprPlayer_Left1, 10 },
//        { nullptr, -1 },// 終了フラグ
//    };
//}

void setPlayer(OBJ2DManager* obj2dManager, BG* bg) 
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

    obj2dManager->add(player, &normalPlayerBehavior, pos);
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

    obj2dManager->add(cursor, &cursorBehavior, pos);
}

//******************************************************************************
//
//      BasePlayerBehavior
//
//******************************************************************************

void BasePlayerBehavior::init(OBJ2D* obj) const
{
    obj->collider_->judgeFlag_ = true;
    obj->collider_->isDrawHitRect_ = true;
    obj->collider_->isDrawAttackRect_ = true;

    obj->eraser_ = &erasePlayer;
}

void BasePlayerBehavior::moveX(OBJ2D* obj) const
{
    // 左右入力の取り出し
    switch (obj->actorComponent_->padState_ & (GameLib::input::PAD_LEFT | GameLib::input::PAD_RIGHT))
    {
    case GameLib::input::PAD_LEFT:  // 左だけが押されている場合
        obj->transform_->velocity_.x -= getParam()->ACCEL_X;
        obj->renderer_->animeData_ = getParam()->ANIME_LEFT;
        obj->actorComponent_->xFlip_ = true;
        break;
    case GameLib::input::PAD_RIGHT: // 右だけが押されている場合
        obj->transform_->velocity_.x += getParam()->ACCEL_X;
        obj->renderer_->animeData_ = getParam()->ANIME_RIGHT;
        obj->actorComponent_->xFlip_ = false;
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

void BasePlayerBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    // 敵のHPを減らす
    dst->actorComponent_->hp_ -= getParam()->ATTACK_POWER;

    // 親を保存
    if (dst->actorComponent_->parent_ == nullptr)
        dst->actorComponent_->parent_ = src;
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

void BasePlayerBehavior::areaCheck(OBJ2D* obj) const
{
    // 仮
    if (obj->transform_->position_.x < obj->collider_->size_.x)
    {
        obj->transform_->position_.x = obj->collider_->size_.x;
    }
    if (obj->transform_->position_.x > BG::WINDOW_W - obj->collider_->size_.x)
    {
        obj->transform_->position_.x = BG::WINDOW_W - obj->collider_->size_.x;
    }

    if (obj->transform_->position_.y < obj->collider_->size_.y)
    {
        obj->transform_->position_.y = obj->collider_->size_.y;
    }
    if (obj->transform_->position_.y > BG::WINDOW_H)
    {
        obj->transform_->position_.y = BG::WINDOW_H;
    }
}

//******************************************************************************
//
//      NormalPlayerBehavior
//
//******************************************************************************

NormalPlayerBehavior::NormalPlayerBehavior()
{
    // アニメーション
    param_.ANIME_UP = sprPlayer_Up;
    param_.ANIME_RIGHT = sprPlayer_Right;
    param_.ANIME_DOWN = sprPlayer_Down;
    param_.ANIME_LEFT = sprPlayer_Left;

    param_.SIZE = VECTOR2(48 / 2, 128 - 16);
    param_.HIT_BOX = { -100, -200, 100 , 0 };
    param_.ATTACK_BOX = { -100 , -200, 100 , 0 };

    // 速度関連のパラメータ
    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void NormalPlayerBehavior::moveY(OBJ2D* obj) const
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

    BasePlayerBehavior::moveY(obj);
}

void NormalPlayerBehavior::attack(OBJ2D* obj) const
{
    // プレイヤーを指すiteratorを取得する
    auto objList = Game::instance()->obj2dManager()->getList();
    std::list<OBJ2D*>::iterator iter = objList->begin();
    for (; iter != objList->end(); ++iter)
    {
        if ((*iter)->behavior_ == nullptr) { continue; }
        if ((*iter)->behavior_->getType() == OBJ_TYPE::PLAYER) 
        {
            break; 
        }
    }

    obj->actorComponent_->attackTimer_--;

    if (obj->actorComponent_->padTrg_ & GameLib::input::PAD_TRG3 &&
        obj->actorComponent_->attackTimer_ <= 0)
    {
        const VECTOR2 pos = obj->transform_->position_;
        OBJ2D* shuriken = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer, 
                new Collider, 
                obj->bg_, 
                nullptr, 
                nullptr, 
                new WeaponComponent
            ), 
            &shurikenBehavior, 
            pos
        );
        shuriken->zOrder_ = 2;
        shuriken->weaponComponent_->parent_ = obj;
        obj->actorComponent_->attackTimer_ = 10;
    }
}

//******************************************************************************
//
//      ItemPlayerBehavior
//
//******************************************************************************
ItemPlayerBehavior::ItemPlayerBehavior()
{
    // アニメーション
    param_.ANIME_UP = sprPlayer_Up;
    param_.ANIME_RIGHT = sprPlayer_Right;
    param_.ANIME_DOWN = sprPlayer_Down;
    param_.ANIME_LEFT = sprPlayer_Left;

    param_.SIZE = VECTOR2(48 / 2, 128 - 16);
    param_.HIT_BOX = { -100, -200, 100 , 0 };
    param_.ATTACK_BOX = { -100 , -200, 100 , 0 };

    // 速度関連のパラメータ
    param_.ACCEL_X = 8.0f;
    param_.ACCEL_Y = 8.0f;
    param_.SPEED_X_MAX = 8.0f;
    param_.SPEED_Y_MAX = 8.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void ItemPlayerBehavior::moveY(OBJ2D* obj) const
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

    BasePlayerBehavior::moveY(obj);
}

void ItemPlayerBehavior::attack(OBJ2D* obj) const
{
    // プレイヤーを指すiteratorを取得する
    auto objList = Game::instance()->obj2dManager()->getList();
    std::list<OBJ2D*>::iterator iter = objList->begin();
    for (; iter != objList->end(); ++iter)
    {
        if ((*iter)->behavior_ == nullptr) { continue; }
        if ((*iter)->behavior_->getType() == OBJ_TYPE::PLAYER)
        {
            break;
        }
    }

    obj->actorComponent_->attackTimer_--;

    if (obj->actorComponent_->padTrg_ & GameLib::input::PAD_TRG3 &&
        obj->actorComponent_->attackTimer_ <= 0)
    {
        const VECTOR2 pos = obj->transform_->position_ + VECTOR2(0, -48);
        OBJ2D* shuriken = Game::instance()->obj2dManager()->add(
            new OBJ2D(
                new Renderer,
                new Collider,
                obj->bg_,
                nullptr,
                nullptr,
                new WeaponComponent
            ),
            &shurikenBehavior,
            pos
        );
        shuriken->zOrder_ = 2;
        shuriken->weaponComponent_->parent_ = obj;
        obj->actorComponent_->attackTimer_ = 10;
    }
}

// 縮小関数(仮)
void ItemPlayerBehavior::shrink(OBJ2D* obj) const
{
    hitCheck(obj);

    Behavior::shrink(obj);
}

// org自機の方へ移動(仮)
void ItemPlayerBehavior::contact(OBJ2D* obj,OBJ2D* orgObj) const
{
    float dx = orgObj->transform_->position_.x - obj->transform_->position_.x;
    float dy = orgObj->transform_->position_.y - obj->transform_->position_.y;

    float dist = sqrtf(dx * dx + dy * dy);

    obj->transform_->velocity_ = { dx / dist * 10.0f,dy / dist * 10.0f };

    BasePlayerBehavior::moveY(obj);
    ActorBehavior::moveX(obj);

    obj->collider_->calcHitBox(getParam()->HIT_BOX);
    obj->collider_->calcAttackBox(getParam()->ATTACK_BOX);
}

// org自機と接触しているか判定(仮)
void ItemPlayerBehavior::hitCheck(OBJ2D* obj) const 
{
    if (!obj->collider_->isShrink_) return;

    // メインの自機のデータ
    OBJ2D* main = obj->actorComponent_->parent_;

    while (!main->collider_->hitCheck(obj->collider_))
    {
        contact(obj, main);
    }
}

//--------------------------------------------------------------
//  消去
//--------------------------------------------------------------
void ErasePlayer::erase(OBJ2D* obj) const
{
    // 親のbehaviorがあれば かつ　削除待ちでないなら
    if (obj->actorComponent_->parent_->behavior_) return;
    
    for (auto& iter : *(Game::instance()->obj2dManager()->getList()))
    {
        // behaviorがなければ
        if (!iter->behavior_) continue;
        // 相手が自分なら
        if (obj == iter) continue;
        //　親を持っていなければ
        if (!iter->actorComponent_->parent_) continue;
        // 親が自分なら
        if (obj == iter->actorComponent_->parent_) continue;

        // あたっていなければ
        if (!obj->collider_->hitCheck(iter->collider_)) continue;

        // 親を変更する
        obj->actorComponent_->parent_ = iter;
        return;
    }

    obj->behavior_ = nullptr;
    obj->actorComponent_->parent_ = nullptr;
}

// カーソル(仮)
CursorBehavior::CursorBehavior()
{
    param_.SIZE = VECTOR2( 5, 5);
    param_.HIT_BOX = { -5, -5, 5 , 5 };
    param_.ATTACK_BOX = { -5, -5, 5 , 5 };

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

    VECTOR2 pos = { static_cast<float>(point_.x), static_cast<float>(point_.y) };
    return pos;
}

void CursorBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4)
    {
        dst->behavior_ = nullptr;
    }
}

void CursorBehavior::damageProc(OBJ2D* obj) const
{
    obj->transform_->position_ = getCursorPoint();
}
