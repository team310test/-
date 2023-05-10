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
    ActorComponent* dstA = dst->actorComponent_;

    if (dstA->damageTimer_ > 0) return;


    // プレイヤーのHPを減らす
    dstA->hp_ = std::max(dstA->hp_ - getParam()->ATTACK_POWER, 0);

    // 被弾SEを再生
    Audio::play(SE_DMG, false);

    // 相手がまだ生きている場合
    if (dstA->hp_ > 0)
    {
        // 相手を揺らす
        dstA->isQuake_ = true;
        // 相手を点滅させる無敵時間
        dstA->damageTimer_ = 40;

        // プレイヤーコアなら専用被弾SEを再生
        if (dst == Game::instance()->player_)
        {
            Audio::play(SE_PL_CORE_ALERT, false);
        }
    }
}

bool BaseEnemyBehavior::isAlive(OBJ2D* obj) const
{
    return obj->actorComponent_->hp_ > 0;
}

void BaseEnemyBehavior::damageProc(OBJ2D* obj) const
{
    ActorComponent* a = obj->actorComponent_;

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


    if (!obj->actorComponent_->isQuake_) return;

    // 揺らす
    static Quake quake;
    quake.quakeDamage(obj);
}

void BaseEnemyBehavior::areaCheck(OBJ2D* obj) const
{
    const VECTOR2* size     = &obj->collider_->size_;
    const VECTOR2* pos      = &obj->transform_->position_;
    const float    margin   = 600.0f;

    const float leftLimit   = size->x - margin;
    const float rightLimit  = BG::WINDOW_W + size->x + margin;
    const float topLimit    = size->y - margin;
    const float bottomLimit = BG::WINDOW_H + size->y + margin;

    if (pos->x < leftLimit  ||
        pos->x > rightLimit ||
        pos->y < topLimit   ||
        pos->y > bottomLimit)
    {
        //obj->actorComponent_->hp_ = 0;              // 画面外に行ったら消去(体力を0にする)
        obj->actorComponent_->parent_ = nullptr;    

        // hpが0になったときに死亡SEが鳴ってしまうのでbehaviorの方を消す
        obj->behavior_ = nullptr;
        return;
    }

}



//******************************************************************************
//
//      EnemyCore01
//
//******************************************************************************
EnemyCore01Behavior::EnemyCore01Behavior()
{
    // アニメーション
    param_.ANIME_WAIT    = animeCore01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = { 
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f, 
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f 
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = ENM_CORE01_HP;
    param_.ATTACK_POWER  = ENM_CORE01_ATK;

    // 次のBehaviorなし
    param_.NEXT_BEHAVIOR = nullptr;
    param_.NEXT_ERASER   = nullptr;

    // アニメーションのパラメータ
    param_.OBJ_ANIME     = &rotateAnime;
    param_.ROT_SPEED     = ENM_CORE01_ROT_SPEED;
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
    const VECTOR2 objPos     = obj->transform_->position_;      // objの位置

    const VECTOR2 d    = { coreEnmPos - objPos };               // objから自機本体へ向かうベクトル
    const float   dist = sqrtf((d.x * d.x) + (d.y * d.y));      // objから自機本体までの距離

    float addVelocity = 0.0f;                                   // objのvelocityに足す速度
    float num         = 0.0f;                                   // for分のiみたいな役割
    const float copyDist = (dist >= 0) ? dist : dist * (-1);

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
    param_.ANIME_WAIT    = animeTurret01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = { 
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.25f, 
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.25f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = ENM_TURRET01_HP;
    param_.ATTACK_POWER  = ENM_TURRET01_ATK;

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

    // 弾発射SE再生
    Audio::play(SE_SHOT, false);

    // 攻撃クールタイム設定
    obj->actorComponent_->attackTimer_ = ENM_TURRET01_ATK_TIME;
}


//******************************************************************************
//
//      Buff
//
//******************************************************************************

// Buff01
EnemyBuff01Behavior::EnemyBuff01Behavior()
{
    param_.ANIME_WAIT    = animeBuff01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP           = ENM_BUFF01_HP;
    param_.ATTACK_POWER = ENM_BUFF01_ATK;

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR = &dropBuff01Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}

// 攻撃タイプがENEMYなのでdstは味方(エネミー)になる(代わりに体当たりダメージが与えられない)
void EnemyBuff01Behavior::hit(OBJ2D*, OBJ2D* dst) const
{
    // 攻撃クールタイムを減少（弾速上昇）
    dst->actorComponent_->attackTimer_ += BUFF_SUB_ATK_TIMER;
}


//******************************************************************************
// 
//      Common(効果なしパーツ)
// 
//******************************************************************************

// Common01
EnemyCommon01Behavior::EnemyCommon01Behavior()
{
    param_.ANIME_WAIT       = animeCommon01;

    param_.SIZE             = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]       = {
        -COMMON_HITBOX_64, -COMMON_HITBOX_18,
         COMMON_HITBOX_64,  COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0]    = param_.HIT_BOX[0];

    param_.HP               = ENM_COMMON01_HP;
    param_.ATTACK_POWER     = ENM_COMMON01_ATK;

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR    = &dropCommon01Behavior;
    param_.NEXT_ERASER      = &eraseDropParts;
}

// Common01_2(90度回転)
EnemyCommon01_2Behavior::EnemyCommon01_2Behavior()
{
    param_.ANIME_WAIT       = animeCommon01;

    param_.SIZE             = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]       = {
         -COMMON_HITBOX_18, -COMMON_HITBOX_64,
          COMMON_HITBOX_18,  COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0]    = param_.HIT_BOX[0];
    param_.ROTATION         = ROT_90;

    param_.HP               = ENM_COMMON01_2_HP;
    param_.ATTACK_POWER     = ENM_COMMON01_2_ATK;

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR    = &dropCommon01_2Behavior;
    param_.NEXT_ERASER      = &eraseDropParts;
}

// Common02
EnemyCommon02Behavior::EnemyCommon02Behavior()
{
    param_.ANIME_WAIT    = animeCommon02;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]    = {
        -COMMON_HITBOX_64, -COMMON_HITBOX_18,
         COMMON_HITBOX_64,  COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = ENM_COMMON02_HP;
    param_.ATTACK_POWER  = ENM_COMMON02_ATK;

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR = &dropCommon02Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}

// Common02_2(90度回転)
EnemyCommon02_2Behavior::EnemyCommon02_2Behavior()
{
    param_.ANIME_WAIT    = animeCommon02;
                         
    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18, -COMMON_HITBOX_64,
          COMMON_HITBOX_18,  COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ROTATION      = ROT_90;

    param_.HP            = ENM_COMMON02_2_HP;
    param_.ATTACK_POWER  = ENM_COMMON02_2_ATK;

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR = &dropCommon02_2Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}

// Common03
EnemyCommon03Behavior::EnemyCommon03Behavior()
{
    param_.ANIME_WAIT    = animeCommon03;

    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]    = {
        -COMMON_HITBOX_64, -COMMON_HITBOX_18,
         COMMON_HITBOX_64,  COMMON_HITBOX_18,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = ENM_COMMON03_HP;
    param_.ATTACK_POWER  = ENM_COMMON03_ATK;

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR = &dropCommon03Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}

// Common03_2(90度回転)
EnemyCommon03_2Behavior::EnemyCommon03_2Behavior()
{
    param_.ANIME_WAIT     = animeCommon03;

    param_.SIZE           = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]     = {
         -COMMON_HITBOX_18, -COMMON_HITBOX_64,
          COMMON_HITBOX_18,  COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0]  = param_.HIT_BOX[0];
    param_.ROTATION       = ROT_90;

    param_.HP             = ENM_COMMON03_2_HP;
    param_.ATTACK_POWER   = ENM_COMMON03_2_ATK;

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR  = &dropCommon03_2Behavior;
    param_.NEXT_ERASER    = &eraseDropParts;
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
        // 爆発エフェクト
        AddObj::addEffect(obj, &efcBombBehavior);

        // 死亡SE
        Audio::play(SE_DEATH, false);

        a->parent_      = nullptr; // 親をリセット
        a->orgParent_   = nullptr; // 元の親をリセット
        obj->behavior_  = nullptr; // 自分を消去

        return;
    }


    // HPが0以下になると
    if (!a->isAlive())
    {
        // 爆発エフェクト
        AddObj::addEffect(obj, &efcBombBehavior);

        a->parent_ = nullptr; // 親をリセット

        // 自分がコアでないならゴミアイテム化する
        if (obj != a->orgParent_)
        {
            // 死亡SE
            Audio::play(SE_DEATH, false);

            a->orgParent_  = nullptr;           // 元の親をリセット

            // 次のbehavior・eraser（ドロップごみアイテム）を代入
            obj->behavior_ = &dropTrash01Behavior;
            obj->eraser_   = &eraseDropParts;         
            obj->update_   = DROP_PARTS_UPDATE; // updateを変更

            a->hp_ = 0;                         // HPを0にする
            obj->renderer_->flip();             // 反転させる（マスク処理に重要）

            obj->isBlink_  = true;              // 明滅させる

            return;
        }

        // エネミーコア死亡SE
        Audio::play(SE_ENM_CORE_DEATH, false);

        a->orgParent_  = nullptr;               // 元の親をリセット

        obj->behavior_ = nullptr;
        return;
    }

        
    // 死亡ディレイタイマーが一定時間たったらドロップパーツ化処理を行う（親が死んだときのパーツの連鎖死亡に遅延をつくりだす）
    if (a->deathDelayTimer_ >= PARTS_DEATH_DELAY_TIME)
    {
        // 爆発エフェクト
        AddObj::addEffect(obj, &efcBombBehavior);

        // 死亡SE
        Audio::play(SE_DEATH, false);

        // 次のbehavior・eraser（ドロップアイテム）を代入
        obj->behavior_ = obj->nextBehavior_;
        obj->eraser_   = obj->nextEraser_;


        if (obj->behavior_ == nullptr) return;  // 次のBehaviorがなければreturn


        obj->update_ = DROP_PARTS_UPDATE;       // updateを変更

        a->hp_ = 0;                             // HPを0にする
        obj->renderer_->flip();                 // 反転させる

        obj->isBlink_ = true;                   // 明滅させる

        return;
    }


    // 親または大元の親が存在しなければ
    if (!a->parent_ || !a->orgParent_)
    {
        ++a->deathDelayTimer_;   // 死亡ディレイタイマーを加算する
    }
    else // 親と大元の親が存在していれば
    {
        // どちらもまだ生きていたらreturn
        if (a->parent_->behavior_ && a->orgParent_->behavior_) return;

        // どちらかが死んでいたら
        a->parent_    = nullptr; // 親をリセット
        a->orgParent_ = nullptr; // 元の親をリセット
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
    ActorComponent* a = obj->actorComponent_;

    if (!a->orgParent_) return; // 親が消えていたらreturn

    Transform* t = obj->transform_;
    Transform* parent = a->orgParent_->transform_;

    t->velocity_ = parent->velocity_;
}