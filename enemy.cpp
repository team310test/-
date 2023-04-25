#include "all.h"

// アニメデータ
namespace
{   
    //  コア01
    GameLib::AnimeData animeCore01[] = {
        { &sprPartsCore01, 10 },
        { nullptr, -1 },// 終了フラグ
    };

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


OBJ2D* setMainEnemy(OBJ2DManager* obj2dManager, BG* bg, BaseEnemyBehavior* behavior, VECTOR2 pos,OBJ_DATA update,int zOrder = 3)
{
    OBJ2D* enemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    enemy->zOrder_ = zOrder;
    enemy->actorComponent_->parent_ = enemy;

    return obj2dManager->add(enemy, behavior, pos, update);
}
OBJ2D* setSubEnemy(OBJ2DManager* obj2dManager, BG* bg, BaseEnemyBehavior* behavior, OBJ2D* parent, VECTOR2 pos, OBJ_DATA update, int zOrder = 3)
{
    OBJ2D* subEnemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    subEnemy->zOrder_ = zOrder;
    // 親を設定
    subEnemy->actorComponent_->parent_ = parent;

    return obj2dManager->add(subEnemy, behavior, pos, update);
}

void setEnemy01(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos)
{
    OBJ_DATA update = ENEMY_LINE;

    OBJ2D* Parent = setMainEnemy(obj2dManager, bg, &enemyCore01Behavior, pos, update);
    setSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, Parent, { pos.x - 64,pos.y + 96 }, update);
}
void setEnemy02(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos)
{
    OBJ_DATA update = ENEMY_LINE;

    OBJ2D* Parent = setMainEnemy(obj2dManager, bg, &enemyCore01Behavior, pos, update);
    setSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, Parent, { pos.x - 128,pos.y }, update);
}

void setEnemyT(OBJ2DManager* obj2dManager, BG* bg,VECTOR2 pos)
{
    OBJ_DATA update = ENEMY_LINE;

    OBJ2D* Parent = setMainEnemy(obj2dManager, bg, &enemyCore01Behavior, pos, update);

    OBJ2D* subParent01 =
        setSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, Parent, { pos.x,pos.y - 229 }, update);
    setSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, subParent01, { pos.x,pos.y - 429 }, update);
    OBJ2D* subParent02 =
        setSubEnemy(obj2dManager, bg, &enemyBuff01Behavior, Parent, { pos.x,pos.y + 229 }, update);
    setSubEnemy(obj2dManager, bg, &enemyBuff01Behavior, subParent02, { pos.x,pos.y + 429 }, update);
}

void addEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    OBJ2D* Parent = setMainEnemy(obj2dManager, bg, &enemyCore01Behavior, getCursorPoint2(), ENEMY_LINE);
    VECTOR2 pos = Parent->transform_->position_;
    // サブパーツ
    setSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, Parent, { pos.x,pos.y - 229 }, ENEMY_LINE);
    setSubEnemy(obj2dManager, bg, &enemyBuff01Behavior, Parent, { pos.x,pos.y + 229 }, ENEMY_LINE);
}

#if 0
// Turret
void setSubEnemy(OBJ2DManager* obj2dManager, BG* bg, OBJ2D* parent, VECTOR2 pos)
{
    OBJ2D* subEnemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    subEnemy->zOrder_ = 3;
    // 親を設定
    subEnemy->actorComponent_->parent_ = parent;

    obj2dManager->add(subEnemy, &enemyTurret01Behavior, pos);
}
// Buff
void setSubEnemy2(OBJ2DManager* obj2dManager, BG* bg, OBJ2D* parent, VECTOR2 pos)
{
    OBJ2D* subEnemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr
    );

    subEnemy->zOrder_ = 3;
    // 親を設定
    subEnemy->actorComponent_->parent_ = parent;

    obj2dManager->add(subEnemy, &enemyBuff01Behavior, pos);
}

void setEnemy01(OBJ2DManager* obj2dManager, BG* bg)
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

    // サブパーツ
    setSubEnemy(obj2dManager, bg, enemy, { pos.x, pos.y - 429 });
    setSubEnemy(obj2dManager, bg, enemy, { pos.x, pos.y - 229 });
    setSubEnemy2(obj2dManager, bg, enemy, { pos.x, pos.y + 229 });
    setSubEnemy2(obj2dManager, bg, enemy, { pos.x, pos.y + 429 });
<<<<<<< HEAD
}

// カーソルの座標取得
VECTOR2 getCursorPoint2()
{
    static POINT point_;

    GetCursorPos(&point_);
    ScreenToClient(GetActiveWindow(), &point_);

    VECTOR2 pos = { static_cast<float>(point_.x), static_cast<float>(point_.y) };
    return pos;
=======
>>>>>>> maeyama
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

    // サブパーツ
    setSubEnemy(obj2dManager, bg, enemy, { pos.x, pos.y - 229 });
    setSubEnemy(obj2dManager, bg, enemy, { pos.x, pos.y + 229 });
}
#endif



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

    obj->renderer_->flip(); // 反転させる
}

void BaseEnemyBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
{
    // プレイヤーのHPを減らす
    dst->actorComponent_->hp_ -= getParam()->ATTACK_POWER;
}

bool BaseEnemyBehavior::isAlive(OBJ2D* obj) const
{
    return obj->actorComponent_->hp_ > 0;
}

void BaseEnemyBehavior::damageProc(OBJ2D* /*obj*/) const
{
    // ダメージ処理
    //obj->actorComponent_->damaged();

    // 無敵処理
    //obj->actorComponent_->muteki();
}

void BaseEnemyBehavior::areaCheck(OBJ2D* obj) const
{
#if 1
    // 左端に進むと右端から出てくる(仮)
    if (obj->transform_->position_.x < -obj->collider_->size_.x)
    {
        obj->transform_->position_.x = obj->collider_->size_.x + BG::WINDOW_W;
    }

#else
    if (obj->transform_->position_.x < 0) // 画面右に行ったら
    {
        obj->behavior_ = nullptr; // 消去
    }
#endif
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
    param_.HIT_BOX[0] = { -125,-125,125,125 };

    param_.ATTACK_BOX[0] = { -125, -125, 125, 125 };

    // 次のBehaviorなし
    param_.NEXT_BEHAVIOR = nullptr;
    param_.NEXT_ERASER   = nullptr;

    // アニメーションのパラメータ
    param_.OBJ_ANIME = &rotateAnime;
    param_.ROT_SPEED = -0.05f;
}


//******************************************************************************
//
//      Turret
//
//******************************************************************************

// Turret01
EnemyTurret01Behavior::EnemyTurret01Behavior()
{
    param_.ANIME_WAIT = animeTurret01;

    param_.SIZE = { player_size, player_size };

    // 画像サイズ(128*64の半分)
    param_.HIT_BOX[0] = { -64, -32, 64, 32 };    // 下長方形    
    //param_.HIT_BOX[1] = { -10,-95,125,50 };      // ネジ

    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];   // 下長方形
    //param_.ATTACK_BOX[1] = param_.HIT_BOX[1];      // ネジ

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR = &dropTurret01Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}


void EnemyTurret01Behavior::attack(OBJ2D* obj) const
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
            &enmAimShotBehavior,
            pos,
            nullptr
        );
        shot->zOrder_ = 2;
        shot->weaponComponent_->parent_ = obj;
    }

    obj->actorComponent_->attackTimer_ = 120;
}


//******************************************************************************
//
//      Buff
//
//******************************************************************************

// Buff01
EnemyBuff01Behavior::EnemyBuff01Behavior()
{
    param_.ANIME_WAIT = animeBuff01;

    param_.SIZE = { player_size, player_size };
    param_.HIT_BOX[0] = {
        -player_hitBox, -player_hitBox,
         player_hitBox,  player_hitBox,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR = &dropBuff01Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}


//******************************************************************************
//
//      erase（消去）
//
//******************************************************************************
void EraseEnemy::erase(OBJ2D* obj) const
{
    // スケールが0以下になったら消去
    if (obj->transform_->scale_.x <= 0)
    {
        obj->actorComponent_->parent_ = nullptr; // 親情報をリセット
        obj->behavior_ = nullptr;
        return;
    }

    OBJ2D* parent = obj->actorComponent_->parent_; // 長いので省略

    // 親が存在していて、親が消滅するか親の体力が0になるとアイテム化する
    if (parent && (parent->behavior_ == nullptr || !parent->actorComponent_->isAlive()) )
    {
        obj->actorComponent_->parent_ = nullptr; // 親リセット


        // 次のbehavior・eraser（ドロップアイテム）を代入
        obj->behavior_ = obj->nextBehavior_;
        obj->eraser_   = obj->nextEraser_;

        if (obj->behavior_ == nullptr) return;
        obj->behavior_->update = PARTS_UPDATE;  // updateを変更

        obj->actorComponent_->hp_ = 0;  // HPを0にする

        obj->renderer_->flip(); // 反転させる

        return;
    }

    // HPが0以下になると
    if (!obj->actorComponent_->isAlive())
    {
        obj->actorComponent_->parent_ = nullptr; // 親情報をリセット

        // 自分がコアでないならゴミアイテム化する
        if (obj != parent)
        {
            // 次のbehavior・eraser（ドロップアイテム）を代入
            obj->behavior_ = &dropTrash01Behavior;
            obj->eraser_   = &eraseDropParts;
            
            if (obj->behavior_ == nullptr) return;
            obj->behavior_->update = PARTS_UPDATE;  // updateを変更

            return;
        }

        // コアなら消滅する
        obj->behavior_ = nullptr;
        return;
    }

}

//******************************************************************************
//
//      エネミーのupdate
//
//******************************************************************************
void ENEMY_LINE(OBJ2D* obj)
{
    const float speed = -5;
    Transform* t = obj->transform_;
    
    t->velocity_.x = speed;

    t->position_ += t->velocity_;
}
void ENEMY_LINE_SLOW(OBJ2D* obj)
{
    const float speed = -1;
    Transform* t = obj->transform_;

    t->velocity_.x = speed;

    t->position_ += t->velocity_;
}