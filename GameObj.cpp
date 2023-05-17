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

    // リザルトバック
    GameLib::AnimeData animResult_back[] = {
        { &sprResult_back01, 5 },
        { &sprResult_back02, 5 },
        { &sprResult_back03, 5 },
        { &sprResult_back04, 5 },
        { nullptr, -1 }, // 終了フラグ
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
    //obj->renderer_->animeData_ = nullptr;
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
        obj->renderer_->animeData_ = getParam()->ANIME_DATA;
        if (!obj->renderer_->animeData_) obj->renderer_->data_ = getParam()->SPR_DATA;

        init(obj);

        obj->state_++;
        break;

    case 1:
        //////// 通常時 ////////
        // 更新処理（任意で設定）
        update(obj);

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

    obj->transform_->velocity_ = { GAME_OVER_Initial_SPEED_X, GAME_OVER_Initial_SPEED_Y };
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


void BaseGameResult::update(OBJ2D* obj) const
{
    if (!obj->isQuake_) return;

    static Quake quake;
    quake.quakeDamage(obj);
}



GameResult_Back::GameResult_Back()
{
    param_.SPR_DATA   = &sprResult_back04;
    param_.ANIME_DATA = animResult_back;
    param_.COLOR      = { 0,0,0, 0.6f };
}

void GameResult_Back::update(OBJ2D* obj) const
{
    Renderer* r = obj->renderer_;

    if (!r->animeData_) return;    // アニメがなければreturn
    if (!r->animeUpdate()) return; // アニメが回り切っていなければreturn

    // アニメを回しきったらsprDataに切り替える
    r->animeData_ = nullptr;
    r->data_      = param_.SPR_DATA;
}

GameResult_Junks::GameResult_Junks()
{
    param_.SPR_DATA = &sprResult_junks;
    param_.SCALE    = { 0.75f, 0.75f };
}

GameResult_Times::GameResult_Times()
{
    param_.SPR_DATA = &sprResult_times;
    param_.SCALE    = { 0.75f, 0.75f };
}

GameResult_Rank::GameResult_Rank()
{
    param_.SPR_DATA = &sprResult_rank;
    param_.SCALE = { 1.0f, 1.0f };
}


static const float RESULT_TEXT_ANGLE = ToRadian(-10.0f);

GameResult_Text_Junkie::GameResult_Text_Junkie()
{
    param_.SPR_DATA = &sprResult_textJunkie;
    param_.SCALE = { 1.5f, 1.5f };
}

void GameResult_Text_Junkie::init(OBJ2D* obj) const
{
    obj->transform_->rotation_ = RESULT_TEXT_ANGLE;
}

GameResult_Text_Great::GameResult_Text_Great()
{
    param_.SPR_DATA = &sprResult_textGreat;
    param_.SCALE = { 1.25f, 1.25f };
}

void GameResult_Text_Great::init(OBJ2D* obj) const
{
    obj->transform_->rotation_ = RESULT_TEXT_ANGLE;
}

GameResult_Text_Nice::GameResult_Text_Nice()
{
    param_.SPR_DATA = &sprResult_textNice;
    param_.SCALE = { 1.25f, 1.25f };
}

void GameResult_Text_Nice::init(OBJ2D* obj) const
{
    obj->transform_->rotation_ = RESULT_TEXT_ANGLE;
}

GameResult_Text_Soso::GameResult_Text_Soso()
{
    param_.SPR_DATA = &sprResult_textSoso;
    param_.SCALE = { 1.25f, 1.25f };
}

void GameResult_Text_Soso::init(OBJ2D* obj) const
{
    obj->transform_->rotation_ = RESULT_TEXT_ANGLE;
}


GameResult_AnyPush::GameResult_AnyPush()
{
    param_.SPR_DATA = &sprResult_anyPush;
    param_.SCALE = { 0.75f, 0.75f };
}

void GameResult_AnyPush::init(OBJ2D* obj) const
{
    BaseGameObjBehavior::init(obj);

    obj->timer_ = -20;
}

void GameResult_AnyPush::update(OBJ2D* obj) const
{
    obj->renderer_->color_.w = (obj->timer_ & 0x20) ? 1.0f : 0.0f;
    ++obj->timer_;
}


GameResult_S::GameResult_S()
{
    param_.SPR_DATA = &sprResult_S;
}

GameResult_A::GameResult_A()
{
    param_.SPR_DATA = &sprResult_A;
}

GameResult_B::GameResult_B()
{
    param_.SPR_DATA = &sprResult_B;
}

GameResult_C::GameResult_C()
{
    param_.SPR_DATA = &sprResult_C;
}
