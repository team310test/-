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

// クリックで敵出現させる(削除予定)
OBJ2D* TsetMainEnemy(OBJ2DManager* obj2dManager, BG* bg, BaseEnemyBehavior* behavior, VECTOR2 pos,OBJ_DATA update,float accelX,int zOrder = 3)
{
    OBJ2D* enemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr,
        nullptr
    );

    enemy->zOrder_ = zOrder;
    enemy->actorComponent_->parent_ = enemy;
    enemy->actorComponent_->orgParent_ = enemy;
    enemy->update_ = update;
    enemy->actorComponent_->accel_.x = accelX;

    return obj2dManager->add(enemy, behavior, pos);
}
OBJ2D* TsetSubEnemy(OBJ2DManager* obj2dManager, BG* bg, BaseEnemyBehavior* behavior, OBJ2D* parent,OBJ2D* orgParent, VECTOR2 pos, OBJ_DATA update, int zOrder = 3)
{
    OBJ2D* subEnemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr,
        nullptr
    );

    subEnemy->zOrder_ = zOrder;
    // 親を設定
    subEnemy->actorComponent_->parent_ = parent;
    subEnemy->actorComponent_->orgParent_ = orgParent;
    subEnemy->update_ = update;

    return obj2dManager->add(subEnemy, behavior, pos);
}
void addEnemy(OBJ2DManager* obj2dManager, BG* bg)
{
    OBJ2D* Parent = TsetMainEnemy(obj2dManager, bg, &enemyCore01Behavior, getCursorPoint2(),ENEMY_LINE, 5.0f);
    VECTOR2 pos = Parent->transform_->position_;
    // サブパーツ
    TsetSubEnemy(obj2dManager, bg, &enemyTurret01Behavior, Parent, Parent,{ pos.x,pos.y - 229 }, ENEMY_PARTS);
    TsetSubEnemy(obj2dManager, bg, &enemyBuff01Behavior, Parent, Parent,{ pos.x,pos.y + 229 }, ENEMY_PARTS);
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
#if 0
    // 左端に進むと右端から出てくる(仮)
    if (obj->transform_->position_.x < -obj->collider_->size_.x)
    {
        //obj->behavior_ = nullptr; // 画面外に行ったら消去
    }

#else

    const VECTOR2* size = &obj->collider_->size_;
    const VECTOR2* pos = &obj->transform_->position_;
    const float margin = 600.0f;

    const float leftLimit = size->x - margin;
    const float rightLimit = BG::WINDOW_W + size->x + margin;
    const float topLimit = size->y - margin;
    const float bottomLimit = BG::WINDOW_H + size->y + margin;

    if (pos->x < leftLimit ||
        pos->x > rightLimit ||
        pos->y < topLimit ||
        pos->y > bottomLimit)
    {
        obj->actorComponent_->hp_ = 0;              // 画面外に行ったら消去(体力を0にする)
        obj->actorComponent_->parent_ = nullptr;    
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
                new WeaponComponent,
                nullptr
            ),
            &enmAimShotBehavior,
            pos
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

    // 親が存在していて、親が自分でなく、親が消滅するか親の体力が0になるとアイテム化する
    if (parent && (parent->behavior_ == nullptr || !parent->actorComponent_->isAlive()) )
    {
        obj->actorComponent_->parent_ = nullptr; // 親リセット
        obj->actorComponent_->orgParent_ = nullptr; // 元の親をリセット

        // 次のbehavior・eraser（ドロップアイテム）を代入
        obj->behavior_ = obj->nextBehavior_;
        obj->eraser_   = obj->nextEraser_;

        if (obj->behavior_ == nullptr) return;
        obj->update_ = PARTS_UPDATE;  // updateを変更

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
            obj->update_ = PARTS_UPDATE;  // updateを変更

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
// コアの直線移動
void ENEMY_LINE(OBJ2D* obj)
{
    Transform* t = obj->transform_;
    const float speedX = obj->actorComponent_->accel_.x;

    t->velocity_ = { -speedX, 0.0f };
}
// x軸の目標地点に達すると別の方向へ移動する(仮)
void ENEMY_TARGET_X(OBJ2D* obj)
{
    Transform* t = obj->transform_;
    ActorComponent* a = obj->actorComponent_;
    const float targetPosX = a->addition_.x;

    switch (obj->act_)
    {
    case 0:
        if (t->position_.x < targetPosX) obj->act_++;

        t->velocity_ = { -a->accel_.x, a->accel_.y };
        break;
    case 1:
        t->velocity_ = { -a->addition_.y,a->addition_.z };

        break;
    default:break;
    }
}
// パーツのアップデート
void ENEMY_PARTS(OBJ2D* obj)
{
    Transform* t = obj->transform_;
    Transform* parent = obj->actorComponent_->orgParent_->transform_;

    t->velocity_ = parent->velocity_;
}