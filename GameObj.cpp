#include "all.h"

// アニメデータ
namespace
{
    // コア(ハートのみ)
    GameLib::AnimeData animeGameCoreHeart[] =
    {
        {&sprGamePlayerHeart,10},
        {nullptr,-1},// 終了フラグ
    };
}

//******************************************************************************
// 
//      ゲーム用のobj
// 
//******************************************************************************
// BaseGameObjBehavior
void BaseGameObjBehavior::move(OBJ2D* obj) const
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

void BaseGameObjBehavior::init(OBJ2D* obj) const
{
    obj->collider_->judgeFlag_ = false;
    obj->collider_->isDrawHitRect_ = false;
    obj->collider_->isDrawAttackRect_ = false;
}

// playerの枠
GamePlayerFrameObjBehavior::GamePlayerFrameObjBehavior()
{
    param_.SPR_DATA = &sprGamePlayerFrame;
    param_.SIZE = { 100,100 };
    param_.SCALE = { GAME_OVER_SCALE,GAME_OVER_SCALE };
    param_.ATTACK_BOX[0] = { -13, 20,-1,33 };
}
//******************************************************************************
// 
//      Game(Over)Player（タイトル用の自機)
// 
//******************************************************************************

// playerのハート
GamePlayerHheartObjBehavior::GamePlayerHheartObjBehavior()
{
    param_.ANIME_WAIT = animeGameCoreHeart;
    
    param_.SIZE = VECTOR2(42.0f, 37.0f);
    param_.SCALE = { GAME_OVER_SCALE,GAME_OVER_SCALE };
    param_.HIT_BOX[0] = { -10, -10, 10, 10 };
    param_.ATTACK_BOX[0] = param_.HIT_BOX[0];
    param_.HP = 1;  // 消滅防止
    param_.OBJ_ANIME = GAME_OVER_PLAYER_UPDATE;
}

void GamePlayerHheartObjBehavior::init(OBJ2D* obj) const
{
    obj->collider_->judgeFlag_ = false;
    obj->collider_->isDrawHitRect_ = false;
    obj->collider_->isDrawAttackRect_ = false;

    obj->transform_->velocity_ = { GAME_OVER_Initial_SPEED_X,GAME_OVER_Initial_SPEED_Y };
}

void GamePlayerHheartObjBehavior::areaCheck(OBJ2D* obj) const
{
    const VECTOR2* size = &obj->collider_->size_;
    const VECTOR2* pos = &obj->transform_->position_;

    const float leftLimit = size->x;
    const float rightLimit = BG::WINDOW_W + size->x;
    const float topLimit = size->y;
    const float bottomLimit = BG::WINDOW_H + size->y;

    if (pos->x < leftLimit ||
        pos->x > rightLimit ||
        pos->y < topLimit ||
        pos->y > bottomLimit)
    {
        obj->performComponent_->isTrigger = true; // 画面外に行ったらTriggerをtrue(タイトル画面へ遷移)
        return;
    }
}
