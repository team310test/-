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

//------< アニメデータ >----------------------------------------------
namespace
{   
    //------< アニメデータ >------------------------------------------
    //上方向
    GameLib::AnimeData animeEnemey_Up[] = {
        { &sprEnemey_test, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // タレット01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
        //{ &sprPlayer_test, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //  コア01
    GameLib::AnimeData animeCore01[] = {
        { &sprPartsCore01, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //  ゴミ01
    GameLib::AnimeData animeTrash01[] = {
        { &sprPartsTrash01, 10 },
        { nullptr, -1 },// 終了フラグ
    };
}

void setSubEnemy(BaseEnemyBehavior* behavior, OBJ2D* parent, VECTOR2 pos)
{
    if (behavior->isCore())
    {
        assert(!"coreがcoreを呼び出しています");
    };

    VECTOR2 POS = { parent->transform_->position_.x + pos.x,parent->transform_->position_.y + pos.y };

    OBJ2D* subEnemy = new OBJ2D(
        new Renderer,
        new Collider,
        Game::instance()->bg(),
        new ActorComponent,
        nullptr,
        nullptr
    );

    subEnemy->zOrder_ = 3;
    // 親を設定
    subEnemy->actorComponent_->parent_ = parent;

    Game::instance()->obj2dManager()->add(subEnemy, behavior, POS);
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
    enemy->actorComponent_->parent_ = enemy;

    obj2dManager->add(enemy, &enemyCore01Behavior, pos);
}

// カーソルの座標取得
VECTOR2 getCursorPoint2()
{
    static POINT point_;

    GetCursorPos(&point_);
    ScreenToClient(GetActiveWindow(), &point_);

    VECTOR2 pos = { static_cast<float>(point_.x), static_cast<float>(point_.y) };
    return pos;
}

void addEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    const VECTOR2 pos = getCursorPoint2();

    OBJ2D* enemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    enemy->zOrder_ = 3;
    enemy->actorComponent_->parent_ = enemy;

    obj2dManager->add(enemy, &enemyCore01Behavior, pos);
}

//******************************************************************************
//
//      BaseEnemyBehavior
//
//******************************************************************************
void BaseEnemyBehavior::init(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = getParam()->ANIME_WAIT;

    obj->collider_->judgeFlag_ = true;
    obj->collider_->isDrawHitRect_ = true;
    obj->collider_->isDrawAttackRect_ = true;

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
    //if (obj->transform_->position_.x < -obj->collider_->size_.x)
    //{
    //    obj->transform_->position_.x = obj->collider_->size_.x + BG::WINDOW_W;
    //}
}

//******************************************************************************
//
//      NormalEnemyBehavior
//
//******************************************************************************
NormalEnemyBehavior::NormalEnemyBehavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeEnemey_Up;

    param_.SIZE    = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -player_hitBox, -player_hitBox, player_hitBox, player_hitBox };
    //param_.ATTACK_BOX = { -250 / 2, -250, 250 / 2, 0 };
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
    param_.ANIME_WAIT = animeEnemey_Up;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.ATTACK_BOX[0] = { -player_hitBox, -player_hitBox, player_hitBox, player_hitBox };
    param_.HIT_BOX[0] = { -player_hitBox, -player_hitBox, player_hitBox, player_hitBox };
    param_.HP = 1;

    // 速度関連のパラメータ
    param_.ACCEL_X = 4.0f;
    param_.ACCEL_Y = 4.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;
}

void ItemEnemyBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    src->actorComponent_->hp_ = 0;
}

void ItemEnemyBehavior::attack(OBJ2D* obj) const
{
}

//******************************************************************************
//
//      EnemyCore01
//
//******************************************************************************
EnemyCore01Behavior::EnemyCore01Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeCore01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -64,-64,64,64 };

    param_.ATTACK_BOX[0] = { -64, -64, 64, 64 };

    // 速度関連のパラメータ
    param_.ACCEL_X = 4.0f;
    param_.ACCEL_Y = 4.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;

    // アニメーションのパラメータ
    param_.obj_ANIME = &rotateAnime;
    param_.ROT_SPEED = -0.05f;
}

void EnemyCore01Behavior::init(OBJ2D* obj) const
{
    // サブパーツ召喚
    setSubEnemy(&enemyTurret01Behavior, obj, { -64,96 });

    BaseEnemyBehavior::init(obj);
}

//******************************************************************************
//
//      Turret01
//
//******************************************************************************
// エネミー
EnemyTurret01Behavior::EnemyTurret01Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] =  { -64,-64,64,64 };

    param_.ATTACK_BOX[0] =  { -64,-64,64,64 };

    // 速度関連のパラメータ
    param_.ACCEL_X = 4.0f;
    param_.ACCEL_Y = 4.0f;
    param_.SPEED_X_MAX = 4.0f;
    param_.SPEED_Y_MAX = 4.0f;
    param_.JUMP_POWER_Y = -12.0f;

    // 次のBehavior・Eraser
    param_.NEXT_BEHAVIOR = &playerTurret01Behavior;

    // アニメーションのパラメータ
    param_.obj_ANIME = &scaleAnime;
}

void EnemyTurret01Behavior::attack(OBJ2D* obj) const
{
    obj->actorComponent_->attackTimer_--;

    if (obj->actorComponent_->attackTimer_ >= 0)return;

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
        &enemyNormalShotBehavior,
        pos
    );
    shot->zOrder_ = 2;
    shot->weaponComponent_->parent_ = obj;
    obj->actorComponent_->attackTimer_ = 180;

}

// アイテム
ItemTurret01Behavior::ItemTurret01Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -64,-64,64,64 };

    param_.ATTACK_BOX[0] = { -64,-64,64,64 };

    // 速度関連のパラメータ
    param_.ACCEL_X = 2.0f;
    param_.ACCEL_Y = 2.0f;
    param_.SPEED_X_MAX = 2.0f;
    param_.SPEED_Y_MAX = 2.0f;
    param_.JUMP_POWER_Y = -12.0f;
}


//******************************************************************************
//      EnemyTrash01
//******************************************************************************
// アイテム
ItemTrash01Behavior::ItemTrash01Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeTrash01;

    param_.SIZE = VECTOR2(player_size, player_size);
    param_.HIT_BOX[0] = { -64,-64,64,64 };

    param_.ATTACK_BOX[0] = { -64,-64,64,64 };

    // 速度関連のパラメータ
    param_.ACCEL_X = 2.0f;
    param_.ACCEL_Y = 2.0f;
    param_.SPEED_X_MAX = 2.0f;
    param_.SPEED_Y_MAX = 2.0f;
    param_.JUMP_POWER_Y = -12.0f;
}


//--------------------------------------------------------------
//  消去
//--------------------------------------------------------------
void EraseEnemy::erase(OBJ2D* obj) const
{
    // 親が消滅するとアイテム化する
    if (obj->actorComponent_->parent_->actorComponent_->parent_ == nullptr)
    {
        obj->actorComponent_->parent_ = nullptr;
        obj->behavior_ = &itemTurret01Behavior;
        obj->actorComponent_->hp_ = 1;
        obj->eraser_ = &eraseItem;

        // 反転させる
        obj->renderer_->flip();
    }

    // HPが0以下になるとTrashアイテム化する
    if (!obj->actorComponent_->isAlive())
    {
        obj->actorComponent_->parent_ = nullptr;
        obj->behavior_ = &itemTrash01Behavior;
        obj->actorComponent_->hp_ = 1;
        obj->eraser_ = &eraseItem;
        // アニメーション停止
        obj->actorComponent_->objAnime_ = nullptr;
        // nextBehavior_変更
        obj->actorComponent_->nextBehavior_ = &playerTrash01Behavior;

        // 反転させる
        obj->renderer_->flip();
    }

    // 画面外へ行くと消滅
    if (obj->transform_->position_.x < -obj->collider_->size_.x)
    {
        obj->actorComponent_->parent_ = nullptr;
        obj->behavior_ = nullptr;
        return;
    }
}

void EraseItem::erase(OBJ2D* obj) const
{
    if (!obj->actorComponent_->isAlive())
    {
        obj->behavior_ = obj->actorComponent_->nextBehavior_;
        
        obj->eraser_ = &erasePlayer;
        
        obj->actorComponent_->hp_ = obj->behavior_->getParam_HP();

        ++BasePlayerBehavior::plShrinkCount;
    }

    //画面外へ行くと 消滅
    if (obj->transform_->position_.x < -obj->collider_->size_.x)
    {
        obj->actorComponent_->parent_ = nullptr;
        obj->behavior_ = nullptr;
        return;
    }
}