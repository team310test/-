#include "all.h"

// アニメデータ
namespace
{   
    //  コア01
    GameLib::AnimeData animeCore01[] = {
        { &sprEnemyCore01, 10 },
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

    param_.SIZE = VECTOR2(PARTS_OBJ_SIZE, PARTS_OBJ_SIZE);

    param_.HIT_BOX[0]    = { -64, -64, 64, 64 };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    // 次のBehaviorなし
    param_.NEXT_BEHAVIOR = nullptr;
    param_.NEXT_ERASER   = nullptr;

    // アニメーションのパラメータ
    param_.OBJ_ANIME = &rotateAnime;
    param_.ROT_SPEED = -0.05f;
}



//******************************************************************************
// 
//      BaseEnemyPartsBehavior（エネミーのパーツのベース）
// 
//******************************************************************************

void BaseEnemyPartsBehavior::shrink(OBJ2D* obj) const
{
    Behavior::shrink(obj);

    if (!obj->actorComponent_->orgParent_) return;
    if (!obj->actorComponent_->orgParent_->behavior_) return;

    contactToEnmCore(obj, obj->actorComponent_->orgParent_);
}


// オリジナル自機の方に向かって移動する関数
//static const float toCoreVelocity = 0.085f; // 元になる速度(オリジナル自機へ向かう速さに影響)
float BaseEnemyPartsBehavior::toCoreVelocity_ = TO_CORE_SPEED;
// オリジナル自機へ向かう速度
void BaseEnemyPartsBehavior::contactToEnmCore(OBJ2D* obj, OBJ2D* coreEnm) const
{
    if (!obj->collider_->isShrink_) return; // 縮小していなければreturn

    const VECTOR2 coreEnmPos = coreEnm->transform_->position_;  // 自機本体の位置
    const VECTOR2 objPos = obj->transform_->position_;  // objの位置

    const VECTOR2 d = { coreEnmPos - objPos };               // objから自機本体へ向かうベクトル
    const float dist = sqrtf((d.x * d.x) + (d.y * d.y));  // objから自機本体までの距離

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
        if ((copyDist >= (50.0f * num) && copyDist <= 50.0f * (num + 1.0f)))  // ±0から±50、±50から±100、±100から±150...
        {
            addVelocity = (num != 0.0f) ? (toCoreVelocity_ * num) : toCoreVelocity_; // ±0から±50までの距離はnumが0なのでデフォルトの値を代入

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


    //// 最大速度チェックを行う
    //obj->transform_->velocity_.y = clamp(
    //    obj->transform_->velocity_.y, -PL_SPEED_MAX, PL_SPEED_MAX
    //);
    //obj->transform_->velocity_.x = clamp(
    //    obj->transform_->velocity_.x, -PL_SPEED_MAX, PL_SPEED_MAX
    //);
    // 位置更新
    obj->transform_->position_ += obj->transform_->velocity_;
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

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

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

    // 弾を追加
    AddObj::addShot(obj, &enmAimShotBehavior, obj->transform_->position_);

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

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.HIT_BOX[0] = {
        -PL_CORE_HITBOX, -PL_CORE_HITBOX,
         PL_CORE_HITBOX,  PL_CORE_HITBOX,
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
    // parentを省略すると正常に動作しないので撤廃
    //OBJ2D* parent    = obj->actorComponent_->parent_;
    //OBJ2D* orgParent = obj->actorComponent_->orgParent_;

    ActorComponent* a = obj->actorComponent_;


    // スケールが一定以下になったら消去
    if (obj->transform_->scale_.x <= UPDATE_OBJ_SCALE_MIN_LIMIT)
    {
        a->parent_      = nullptr; // 親をリセット
        a->orgParent_   = nullptr; // 元の親をリセット
        obj->behavior_  = nullptr; // 自分を消去

        // 爆発エフェクト
        AddObj::addEffect(obj, &efcBombBehavior);

        return;
    }


    // 親を持っていて、自分が親ではなく、親が消滅するとアイテム化する
    if (a->parent_ && obj != a->parent_ && a->parent_->behavior_ == nullptr)
    {
        a->parent_      = nullptr; // 親をリセット
        a->orgParent_   = nullptr; // 元の親をリセット

        // 次のbehavior・eraser（ドロップアイテム）を代入
        obj->behavior_ = obj->nextBehavior_;
        obj->eraser_   = obj->nextEraser_;

        // 爆発エフェクト
        AddObj::addEffect(obj, &efcBombBehavior);

        if (obj->behavior_ == nullptr) return;

        obj->update_ = DROP_PARTS_UPDATE;  // updateを変更

        a->hp_ = 0;             // HPを0にする
        obj->renderer_->flip(); // 反転させる

        return;
    }


    // HPが0以下になると
    if (!a->isAlive())
    {
        a->parent_ = nullptr; // 親をリセット

        // 爆発エフェクト
        AddObj::addEffect(obj, &efcBombBehavior);


        // 自分がコアでないならゴミアイテム化する
        if (obj != a->orgParent_)
        {
            a->orgParent_ = nullptr; // 元の親をリセット

            // 次のbehavior・eraser（ドロップごみアイテム）を代入
            obj->behavior_ = &dropTrash01Behavior;
            obj->eraser_   = &eraseDropParts;         
            obj->update_   = DROP_PARTS_UPDATE;  // updateを変更

            return;
        }

        a->orgParent_ = nullptr; // 元の親をリセット

        // コアなので消滅する
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