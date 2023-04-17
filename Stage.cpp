//******************************************************************************
//
//
//		Stage.h
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

Stage::Stage()
    :timer(0)
    , pScript(stageData)
{
}

void Stage::update()
{
    while (pScript->behavior_ && pScript->time_ == timer)
    {
        OBJ2D* enemy = new OBJ2D(
            new Renderer,
            new Collider,
            Game::instance()->bg(),
            new ActorComponent,
            nullptr,
            nullptr
        );

        enemy->zOrder_ = 3;
        enemy->actorComponent_->parent_ = enemy;

        Game::instance()->obj2dManager()->add(enemy, pScript->behavior_, pScript->pos_);
        pScript++;
    }
    ++timer;

    if (pScript->behavior_ == nullptr)
    {
        pScript = stageData;
        timer = 0;
    }
}
