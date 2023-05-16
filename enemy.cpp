#include "all.h"

// アニメデータ
namespace
{   
    //  コア01
    GameLib::AnimeData animeCore01[] = {
        { &sprEnemyCore01, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    //  コア02(ボス)
    GameLib::AnimeData animeCore02[] = {
        { &sprEnemyCore02, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // タレット01
    GameLib::AnimeData animeTurret01[] = {
        { &sprPartsTurret01, 10 },
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

    obj->renderer_->Xflip(); // 反転させる
}

void BaseEnemyBehavior::hit(OBJ2D* /*src*/, OBJ2D* dst) const
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


    if (!obj->isQuake_) return;

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
//      EnemyCore02(ボス)
//
//******************************************************************************
EnemyCore02Behavior::EnemyCore02Behavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeCore02;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };
    param_.SCALE = { 2.0f,2.0f };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP = ENM_CORE02_HP;
    param_.ATTACK_POWER = ENM_CORE02_ATK;

    // 次のBehaviorなし
    param_.NEXT_BEHAVIOR = nullptr;
    param_.NEXT_ERASER = nullptr;

    // アニメーションのパラメータ
    param_.OBJ_ANIME = &scaleAnime;
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

// Turret01(AimShot)
EnemyTurret01Behavior::EnemyTurret01Behavior()
{
    param_.ANIME_WAIT    = animeTurret01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = { 
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f, 
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
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

// Turret01Flip
EnemyTurret01FlipBehavior::EnemyTurret01FlipBehavior()
{
    param_.ANIME_WAIT = animeTurret01Flip;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0] = {
        -PARTS_OBJ_SIZE * 0.5f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.5f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP = ENM_TURRET01_HP;
    param_.ATTACK_POWER = ENM_TURRET01_ATK;

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR = &dropTurret01FlipBehavior;
    param_.NEXT_ERASER = &eraseDropParts;
}

void EnemyTurret01FlipBehavior::attack(OBJ2D* obj) const
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

// Turret02(CurveShot)
EnemyTurret02Behavior::EnemyTurret02Behavior()
{
    param_.ANIME_WAIT = animeTurret02;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    // 画像サイズ(128*64の半分)
    param_.HIT_BOX[0] = { -64, -32, 64, 32 };   // 下長方形    
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];   // 下長方形

    param_.ROTATION = ToRadian(ENM_TURRET02_ANGLE);

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR = &dropTurret02Behavior;
    param_.NEXT_ERASER = &eraseDropParts;
}

void EnemyTurret02Behavior::attack(OBJ2D* obj) const
{
    // 攻撃クールタイム減少
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // 攻撃クールタイムが終わっていなければreturn
    if (obj->actorComponent_->attackTimer_ > 0) return;

    // 弾を追加
    const float radius = obj->collider_->size_.x * 0.5f;
    const float angle = obj->transform_->rotation_;
    VECTOR2 pos = obj->transform_->position_;
    pos.x -= cosf(angle) * radius;
    pos.y -= sinf(angle) * radius;

    AddObj::addShot(obj, &enmCurveShotBehavior, pos);

    obj->actorComponent_->attackTimer_ = 120;
}

// Turret02Flip
EnemyTurret02FlipBehavior::EnemyTurret02FlipBehavior()
{
    param_.ANIME_WAIT = animeTurret02Flip;

    param_.SIZE = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    // 画像サイズ(128*64の半分)
    param_.HIT_BOX[0] = { -64, -32, 64, 32 };   // 下長方形    
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];   // 下長方形

    param_.ROTATION = ToRadian(-ENM_TURRET02_ANGLE);

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR = &dropTurret02FlipBehavior;
    param_.NEXT_ERASER = &eraseDropParts;
}

void EnemyTurret02FlipBehavior::attack(OBJ2D* obj) const
{
    // 攻撃クールタイム減少
    if (obj->actorComponent_->attackTimer_ > 0) --obj->actorComponent_->attackTimer_;

    // 攻撃クールタイムが終わっていなければreturn
    if (obj->actorComponent_->attackTimer_ > 0) return;

    // 弾を追加
    const float radius = obj->collider_->size_.x * 0.5f;
    const float angle = obj->transform_->rotation_;
    VECTOR2 pos = obj->transform_->position_;
    pos.x -= cosf(angle) * radius;
    pos.y -= sinf(angle) * radius;

    AddObj::addShot(obj, &enmCurveShotFlipBehavior, pos);

    obj->actorComponent_->attackTimer_ = 120;
}


//******************************************************************************
//
//      Shield（防御パーツ）
//
//******************************************************************************

// Shield01
EnemyShield01Behavior::EnemyShield01Behavior()
{
    param_.ANIME_WAIT    = animeShield01;

    param_.SIZE          = { PARTS_OBJ_SIZE, PARTS_OBJ_SIZE };

    param_.HIT_BOX[0]    = {
        -PARTS_OBJ_SIZE * 0.25f, -PARTS_OBJ_SIZE * 0.5f,
         PARTS_OBJ_SIZE * 0.25f,  PARTS_OBJ_SIZE * 0.5f
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.HP            = ENM_SHIELD01_HP;
    param_.ATTACK_POWER  = ENM_SHIELD01_ATK;

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR = &dropShield01Behavior;
    param_.NEXT_ERASER   = &eraseDropParts;
}


//******************************************************************************
//
//      Buff（バフパーツ）
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
    dst->actorComponent_->attackTimer_ -= BUFF_SUB_ATK_TIMER;
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
// Common04([01]の90度回転)
EnemyCommon04Behavior::EnemyCommon04Behavior()
{
    param_.ANIME_WAIT       = animeCommon01;

    param_.SIZE             = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]       = {
         -COMMON_HITBOX_18, -COMMON_HITBOX_64,
          COMMON_HITBOX_18,  COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0]    = param_.HIT_BOX[0];
    param_.ROTATION         = ROT_90;

    param_.HP               = ENM_COMMON04_HP;
    param_.ATTACK_POWER     = ENM_COMMON04_ATK;

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
// Common05([02]の90度回転)
EnemyCommon05Behavior::EnemyCommon05Behavior()
{
    param_.ANIME_WAIT    = animeCommon02;
                         
    param_.SIZE          = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };
    param_.HIT_BOX[0]    = {
         -COMMON_HITBOX_18, -COMMON_HITBOX_64,
          COMMON_HITBOX_18,  COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];

    param_.ROTATION      = ROT_90;

    param_.HP            = ENM_COMMON05_HP;
    param_.ATTACK_POWER  = ENM_COMMON05_ATK;

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
// Common06([03]の90度回転)
EnemyCommon06Behavior::EnemyCommon06Behavior()
{
    param_.ANIME_WAIT     = animeCommon03;

    param_.SIZE           = { PARTS_OBJ_SIZE, COMMON_SIZE_36 };

    param_.HIT_BOX[0]     = {
         -COMMON_HITBOX_18, -COMMON_HITBOX_64,
          COMMON_HITBOX_18,  COMMON_HITBOX_64,
    };
    param_.ATTACK_BOX[0]  = param_.HIT_BOX[0];
    param_.ROTATION       = ROT_90;

    param_.HP             = ENM_COMMON06_HP;
    param_.ATTACK_POWER   = ENM_COMMON06_ATK;

    // 次のBehavior・Eraser（ドロップアイテム）
    param_.NEXT_BEHAVIOR  = &dropCommon03_2Behavior;
    param_.NEXT_ERASER    = &eraseDropParts;
}

//******************************************************************************
//
//      erase（消去）
//
//******************************************************************************
Behavior* trashbahavior[] = {
    &dropTrash01Behavior,
    &dropTrash02Behavior,
    //&dropTrash03Behavior,
};

void EraseEnemy::erase(OBJ2D* obj) const
{
    // behaviorがなければreturn
    if (!obj->behavior_) return;

    // parentを省略すると正常に動作しないので撤廃
    //OBJ2D* parent    = obj->actorComponent_->parent_;
    //OBJ2D* orgParent = obj->actorComponent_->orgParent_;

    ActorComponent* a = obj->actorComponent_;

    // TODO: ボスが死んでいたら残っているエネミーを消去
    // ボスが死んでいて自分がボスでなければ
    if (Game::instance()->isBossDied_ && obj->behavior_ != &enemyCore02Behavior)
    {
        // 爆発エフェクト
        AddObj::addEffect(obj, &efcBombBehavior);

        // 死亡SE
        Audio::play(SE_DEATH, false);

        // 消去
        a->parent_      =  nullptr;
        a->orgParent_   = nullptr;
        obj->behavior_  = nullptr;

        return;
    }
    // TODO: ボスが死んでいてボスならreturnだけ行う
    else if (Game::instance()->isBossDied_ && obj->behavior_ == &enemyCore02Behavior)
    { 
        return; 
    } 


    // スケールが一定以下になったら消去
    //if (obj->transform_->scale_.x <= UPDATE_OBJ_SCALE_MIN_LIMIT)
    if (obj->transform_->scale_.x < 1.0f && !obj->collider_->isShrink_) // 1回でも縮小したら消す
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

        // TODO: ボスが死んだらボス死亡フラグを立たせる
        // 自分がボスなら
        if (obj->behavior_ == &enemyCore02Behavior)
        {
            a->orgParent_ = nullptr;  // 元の親をリセット

            // ボス死亡フラグをtrue
            Game::instance()->isBossDied_ = true;

            return;
        }


        // 自分がコアでないならゴミアイテム化する
        if (obj != a->orgParent_)
        {
            // 死亡SE
            Audio::play(SE_DEATH, false);

            a->orgParent_  = nullptr;           // 元の親をリセット

            // 次のbehavior・eraser（ドロップごみアイテム）を代入
            obj->behavior_ = trashbahavior[rand() % 2];
            obj->eraser_   = &eraseDropParts;         
            obj->update_   = DROP_PARTS_UPDATE; // updateを変更

            a->hp_ = 0;                         // HPを0にする
            obj->renderer_->Xflip();            // 反転させる（マスク処理に重要）

            obj->isBlink_  = true;              // 明滅させる

            return;
        }

        // エネミーコア死亡SE
        Audio::play(SE_ENM_CORE_DEATH, false);

        a->orgParent_  = nullptr;               // 元の親をリセット

        obj->behavior_ = nullptr;               // 自分(コア)を消去
        return;
    }

        
    // 親が存在しなければ
    if (!a->parent_)
    {
        ++a->deathDelayTimer_;   // 死亡ディレイタイマーを加算する
    }
    else // 親が存在していて
    {
        // まだ生きていてエネミーパーツであればreturn
        if (a->parent_->behavior_)
        {
            if (a->parent_->behavior_->getType() == OBJ_TYPE::ENEMY) return;
        }

        // 死んでいたら
        a->parent_    = nullptr; // 親をリセット
        a->orgParent_ = nullptr; // 元の親をリセット
        return;
    }


    if (a->deathDelayTimer_ < PARTS_DEATH_DELAY_TIME) return;

    // 死亡ディレイタイマーが一定時間たったらドロップパーツ化処理を行う
    //（親が死んだときのパーツの連鎖爆散に遅延をつくりだす）
    
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
    obj->renderer_->Xflip();                // 反転させる
    obj->transform_->rotation_ *= -1;       // 角度反転

    obj->isBlink_ = true;                   // 明滅させる

    return;
    
    
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
    default:
        break;
    }
}
// パーツのアップデート
void ENEMY_PARTS(OBJ2D* obj)
{
    Transform*      t = obj->transform_;
    ActorComponent* a = obj->actorComponent_;

    if (!a->parent_)            return; // 親が存在しなければreturn
    if (!a->parent_->behavior_) return;


    t->velocity_ = a->parent_->transform_->velocity_;
}