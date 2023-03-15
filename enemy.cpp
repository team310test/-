//******************************************************************************
//
//
//      エネミークラス
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//******************************************************************************
//
//      エネミー移動処理
//
//******************************************************************************

//------< プレイヤーのアニメデータ(仮) >----------------------------------------------
namespace
{   
    //------< プレイヤーのアニメデータ >------------------------------------------
    //上方向
    GameLib::AnimeData animePlayer_Up[] = {
        { &sprPlayer_Up0, 10 },
        { &sprPlayer_Up1, 10 },
        { &sprPlayer_Up2, 10 },
        { &sprPlayer_Up1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //右方向
    GameLib::AnimeData animePlayer_Right[] = {
        { &sprPlayer_Right0, 10 },
        { &sprPlayer_Right1, 10 },
        { &sprPlayer_Right2, 10 },
        { &sprPlayer_Right1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //下方向
    GameLib::AnimeData animePlayer_Down[] = {
        { &sprPlayer_Down0, 10 },
        { &sprPlayer_Down1, 10 },
        { &sprPlayer_Down2, 10 },
        { &sprPlayer_Down1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //左方向
    GameLib::AnimeData animePlayer_Left[] = {
        { &sprPlayer_Left0, 10 },
        { &sprPlayer_Left1, 10 },
        { &sprPlayer_Left2, 10 },
        { &sprPlayer_Left1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
}

void setEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    const VECTOR2 pos = { 100,500 };

    OBJ2D* enemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    enemy->zOrder_ = 3;

    obj2dManager->add(enemy, &normalEnemyBehavior, pos);
}

//******************************************************************************
//
//      BaseEnemyBehavior
//
//******************************************************************************
void BaseEnemyBehavior::init(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = getParam()->ANIME_LEFT;

    obj->collider_->judgeFlag_ = true;
    obj->collider_->isDrawHitRect_ = true;
    obj->collider_->isDrawAttackRect_ = true;

    //TODO 01 eraser
    obj->eraser_ = &eraseEnemy;
}

void BaseEnemyBehavior::moveX(OBJ2D* obj) const
{
    // 直線移動(仮)
    obj->transform_->velocity_.x -= getParam()->ACCEL_X;

    ActorBehavior::moveX(obj);
}

void BaseEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    // プレイヤーのHPを減らす
    dst->actorComponent_->hp_ -= getParam()->ATTACK_POWER;
}

bool BaseEnemyBehavior::isAlive(OBJ2D* obj) const
{
    return obj->actorComponent_->hp_ > 0;
}

void BaseEnemyBehavior::damageProc(OBJ2D* obj) const
{
    // ダメージ処理
    //obj->actorComponent_->damaged();

    // 無敵処理
    //obj->actorComponent_->muteki();
}

void BaseEnemyBehavior::areaCheck(OBJ2D* obj) const
{
    // 左端に進むと右端から出てくる(仮)
    if (obj->transform_->position_.x < -obj->collider_->size_.x)
    {
        obj->transform_->position_.x = obj->collider_->size_.x + BG::WINDOW_W;
    }
}

//******************************************************************************
//
//      NormalEnemyBehavior
//
//******************************************************************************
NormalEnemyBehavior::NormalEnemyBehavior()
{
    // アニメーション
    param_.ANIME_UP = animePlayer_Up;
    param_.ANIME_RIGHT = animePlayer_Right;
    param_.ANIME_DOWN = animePlayer_Down;
    param_.ANIME_LEFT = animePlayer_Left;

    param_.SIZE = VECTOR2(48 / 2, 128 - 16);
    param_.HIT_BOX = { -48, -128, 48, 0 };
    param_.ATTACK_BOX = { -48, -128, 48, 0 };
    param_.HP = 1;

    // 速度関連のパラメータ
    param_.ACCEL_X = 1.0f;
    param_.ACCEL_Y = 1.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void NormalEnemyBehavior::moveY(OBJ2D* obj) const
{
    BaseEnemyBehavior::moveY(obj);
}

void NormalEnemyBehavior::attack(OBJ2D* obj) const
{
}

//******************************************************************************
//
//      ItemEnemyBehavior
//
//******************************************************************************
ItemEnemyBehavior::ItemEnemyBehavior()
{
    // アニメーション
    param_.ANIME_UP = animePlayer_Up;
    param_.ANIME_RIGHT = animePlayer_Right;
    param_.ANIME_DOWN = animePlayer_Down;
    param_.ANIME_LEFT = animePlayer_Left;

    param_.SIZE = VECTOR2(48 / 2, 128 - 16);
    param_.HIT_BOX = { -48, -128, 48, 0 };
    param_.ATTACK_BOX = { -48, -128, 48, 0 };
    param_.HP = 1;

    // 速度関連のパラメータ
    param_.ACCEL_X = 4.0f;
    param_.ACCEL_Y = 4.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void ItemEnemyBehavior::moveY(OBJ2D* obj) const
{
    //// メインの自機のデータ
    static OBJ2D* main = *(Game::instance()->obj2dManager()->getList()->begin());

    VECTOR2 vecPlayer = {
        main->transform_->position_.x - obj->transform_->position_.x,
        main->transform_->position_.y - obj->transform_->position_.y
    };

    float cross = obj->transform_->velocity_.x * vecPlayer.y - obj->transform_->velocity_.y * vecPlayer.x;

    static float rot = 3.14f;

    if (cross > 0) rot += 0.025f;
    if (cross < 0) rot -= 0.025f;

    obj->transform_->velocity_.x = getParam()->ACCEL_X * cosf(rot);
    obj->transform_->velocity_.y = getParam()->ACCEL_Y * sinf(rot);

    BaseEnemyBehavior::moveY(obj);
}

void ItemEnemyBehavior::moveX(OBJ2D* obj) const
{
    ActorBehavior::moveX(obj);
}

void ItemEnemyBehavior::attack(OBJ2D* obj) const
{
}

//--------------------------------------------------------------
//  消去
//--------------------------------------------------------------
void EraseEnemy::erase(OBJ2D* obj) const
{
    if (!obj->actorComponent_->isAlive())
    {
        obj->behavior_ = &itemEnemyBehavior;
        obj->actorComponent_->hp_ = 1;
        obj->eraser_ = &eraseItem;
    }
}

void EraseItem::erase(OBJ2D* obj) const
{
    if (!obj->actorComponent_->isAlive())
    {
        obj->behavior_ = &normalPlayerBehavior;
        obj->eraser_ = &erasePlayer;
    }
}