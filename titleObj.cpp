#include "all.h"

// アニメデータ
namespace
{
    // 待機(player)
    GameLib::AnimeData animePlayerCore01[] = {
        { &sprPlayerCore01, 10 },
        { nullptr, -1 },// 終了フラグ
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
        obj->renderer_->data_ = getParam()->SPR_DETA;

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
TitleStateObjBehavior::TitleStateObjBehavior()
{
    param_.SPR_DETA = &sprTitleCore;
    param_.SIZE = {100,100};
    param_.SCALE = {2.0f,2.0f};
    //param_.ATTACK_BOX[0] = { -33, 0,19,53 };
    param_.ATTACK_BOX[0] = { -13, 20,-1,33 };
}

void TitleStateObjBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    static bool wait = false;

    // 画像が切り替わる前のplayerをframeと重なる位置に変更する
    VECTOR2 pos = src->transform_->position_;
    dst->transform_->position_ = { pos.x - 7.0f,pos.y + 28 };

    src->titleComponent_->isTrigger = true;

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
    param_.SPR_DETA = &sprTitleTrash;
    param_.SIZE = { 128,128 };
    param_.ATTACK_BOX[0] = { -30, -30,30,30 };
    //param_.ATTACK_BOX[0] = { -47, 20,18,85 };
}

void TitleEndObjBehavior::hit(OBJ2D* src, OBJ2D* dst) const
{
    // コアのある位置に自機の座標を変更
    //dst->transform_->position_ = src->transform_->position_;

    src->titleComponent_->isTrigger = true;
    src->collider_->judgeFlag_ = false;

    // 自機を操作できなくする
    dst->transform_->velocity_ = { 0.0f,0.0f };
    dst->update_ = nullptr;
}

// タイトルロゴ
TitleLogoObjBehavior::TitleLogoObjBehavior()
{
    param_.SPR_DETA = &sprTitleLogo;
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
    param_.SPR_DETA = &sprTitleUser01;
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
    param_.SPR_DETA = &sprTitleUser02;
}

void TitleHintShotObjBehavior::init(OBJ2D* obj) const
{
    // 描画以外の判定を行わない
    obj->collider_->judgeFlag_ = false;
    obj->collider_->isDrawHitRect_ = false;
    obj->collider_->isDrawAttackRect_ = false;
}
