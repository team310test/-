#include "all.h"

// アニメデータ
namespace
{
    // タイトル用のplayer
    GameLib::AnimeData animeTitlePlayerCore[] = {
        { &sprTitlePlayerCore, 10 },
        { nullptr, -1 },// 終了フラグ
    };

    // コア(ハートのみ)
    GameLib::AnimeData animeTitleCoreHeart[] =
    {
        {&sprTitleCoreHeart,10},
        {nullptr,-1},// 終了フラグ
    };
}

//******************************************************************************
//
//      BaseTitleObjBehavior
//
//******************************************************************************
void BaseTitleObjBehavior::move(OBJ2D* obj) const
{
    obj->renderer_->animeData_ = nullptr;
    switch (obj->state_)
    {
    case 0:
        //////// 初期設定 ////////
        // アニメの初期設定
        obj->transform_->scale_ = getParam()->SCALE;
        obj->renderer_->drawScale_ = getParam()->SCALE;
        obj->collider_->size_ = {
            getParam()->SIZE.x,
            getParam()->SIZE.y
        };
        obj->renderer_->color_ = getParam()->COLOR;
        obj->renderer_->data_ = getParam()->SPR_DATA;

        init(obj);

        obj->state_++;
        break;

    case 1:
        //////// 通常時 ////////

        break;
    }

    for (int i = 0; i < Collider::boxMax; ++i)
        obj->collider_->calcHitBox(getParam()->HIT_BOX[i], i);

    for (int i = 0; i < Collider::boxMax; ++i)
        obj->collider_->calcAttackBox(getParam()->ATTACK_BOX[i], i);
}

void BaseTitleObjBehavior::init(OBJ2D* obj) const
{
    obj->collider_->judgeFlag_ = true;
    obj->collider_->isDrawHitRect_ = true;
    obj->collider_->isDrawAttackRect_ = true;
}

//******************************************************************************
//
//      BaseTitleObjBehavior
//
//******************************************************************************
// スタート
TitleStartObjBehavior::TitleStartObjBehavior()
{
    param_.SPR_DATA = &sprTitleCoreFrame;
    param_.SIZE = {100,100};
    param_.SCALE = {2.0f,2.0f};
    //param_.ATTACK_BOX[0] = { -33, 0,19,53 };
    param_.ATTACK_BOX[0] = { -13, 20,-1,33 };
}

void TitleStartObjBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    static bool wait = false;

    // 画像が切り替わる前のplayerをframeと重なる位置に変更する
    VECTOR2 pos = src->transform_->position_;
    dst->transform_->position_ = { pos.x - 7.0f,pos.y + 28 };

    src->performComponent_->isTrigger = true;

    // 1フレーム処理を遅らせる
    if (wait)
    {
        // 画像が切り替わったplayerをframeの合った位置に変更する
        dst->transform_->position_ = src->transform_->position_;
        src->collider_->judgeFlag_ = false; // 判定を取らないようにする
        src->renderer_->color_.w = 0.0f;    // 透明にする
        src->zOrder_ = 4;                   // 処理の順番を変更
        wait = false;                       // 変数初期化

        return;
    }

    wait = true;
    dst->update_ = nullptr;                 // 自機を変更　操作できなくする
    dst->behavior_ = &titlePlayerCoreBehavior;   // 画像(Behavior)変更
    dst->transform_->velocity_ = { 0.0f,0.0f };
}

// エンド
TitleEndObjBehavior::TitleEndObjBehavior()
{
    param_.SPR_DATA = &sprTitleTrashBox;
    param_.SIZE = { 128,128 };
    param_.ATTACK_BOX[0] = { -30, -30,30,30 };
    //param_.ATTACK_BOX[0] = { -47, 20,18,85 };
}

void TitleEndObjBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    // コアのある位置に自機の座標を変更
    //dst->transform_->position_ = src->transform_->position_;

    src->performComponent_->isTrigger = true;
    src->collider_->judgeFlag_ = false;

    // 自機を操作できなくする
    dst->transform_->velocity_ = { 0.0f,0.0f };
    dst->update_ = nullptr;
}

// タイトルロゴ
TitleLogoObjBehavior::TitleLogoObjBehavior()
{
    param_.SPR_DATA = &sprTitleLogo;
}

void TitleLogoObjBehavior::init(OBJ2D* obj) const
{
    // 描画以外の判定を行わない
    obj->collider_->judgeFlag_ = false;
    obj->collider_->isDrawHitRect_ = false;
    obj->collider_->isDrawAttackRect_ = false;
}
// 操作説明[移動]
TitleHintMoveObjBehavior::TitleHintMoveObjBehavior()
{
    param_.SPR_DATA = &sprTitleUser01;
}

void TitleHintMoveObjBehavior::init(OBJ2D* obj) const
{
    // 描画以外の判定を行わない
    obj->collider_->judgeFlag_ = false;
    obj->collider_->isDrawHitRect_ = false;
    obj->collider_->isDrawAttackRect_ = false;
}
// 操作説明[攻撃]
TitleHintShotObjBehavior::TitleHintShotObjBehavior()
{
    param_.SPR_DATA = &sprTitleUser02;
}

void TitleHintShotObjBehavior::init(OBJ2D* obj) const
{
    // 描画以外の判定を行わない
    obj->collider_->judgeFlag_ = false;
    obj->collider_->isDrawHitRect_ = false;
    obj->collider_->isDrawAttackRect_ = false;
}


//******************************************************************************
// 
//      TitlePlayer（タイトル用の自機)
// 
//******************************************************************************
OBJ2D* setTitlePlayer(OBJ2DManager* obj2dManager, BG* bg)
{
    const VECTOR2 pos = { BG::WINDOW_W * 0.5f,-250.0f };

    OBJ2D* player = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr,
        new PerformComponent
    );

    player->zOrder_ = 3;
    player->actorComponent_->parent_ = player;

    player->actorComponent_->No = ActorComponent::playerNum;
    player->update_ = TITLE_PLAYER_UPDATE;

    return obj2dManager->add(player, &titlePlayerHeartBehavior, pos);
}

// ハートのみ
TitlePlayerCoreHeartBehavior::TitlePlayerCoreHeartBehavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeTitleCoreHeart;

    param_.SIZE = VECTOR2(42.0f, 37.0f);
    param_.SCALE = { 2.0f,2.0f };
    param_.HIT_BOX[0] = { -10, -10, 10, 10 };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];
}

void TitlePlayerCoreHeartBehavior::areaCheck(OBJ2D* obj) const
{
    Transform* t = obj->transform_;
    Collider* c = obj->collider_;

    const float leftSize = 42.0f;
    const float rightSize = 42.0f;
    const float topSize = 30.0f;
    const float bottomSize = 44.0f;

    const float leftLimit = leftSize;
    const float rightLimit = BG::WINDOW_W - rightSize;
    const float topLimit = topSize;
    const float bottomLimit = BG::WINDOW_H - bottomSize;

    if (t->position_.x >= rightLimit)
    {
        t->position_.x = rightLimit;
        if (t->velocity_.x > 0) t->velocity_.x = 0;
    }
    if (t->position_.x <= leftLimit)
    {
        t->position_.x = leftLimit;
        if (t->velocity_.x < 0) t->velocity_.x = 0;
    }
    if (t->position_.y >= bottomLimit)
    {
        t->position_.y = bottomLimit;
        if (t->velocity_.y > 0) t->velocity_.y = 0;
    }
    if (t->position_.y <= topLimit)
    {
        t->position_.y = topLimit;
        if (t->velocity_.y < 0) t->velocity_.y = 0;
    }
}

// コア
TitlePlayerCoreBehavior::TitlePlayerCoreBehavior()
{
    // アニメーション
    param_.ANIME_WAIT = animeTitlePlayerCore;

    param_.SIZE = VECTOR2(PARTS_OBJ_SIZE, PARTS_OBJ_SIZE);
    param_.SCALE = { 2.0f,2.0f };
    param_.HIT_BOX[0] = { -10, -10, 10, 10 };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];
}