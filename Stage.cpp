#include "all.h"

#define X BG::WINDOW_W + 256.0f

STAGE_SCRIPT stageData01[] =
{
    {180,&setEnemy01,{X,300}},
    {360,&setEnemy02,{X,800}},
    SET_ENEMY_DATA_END
};

Stage::Stage()
    : timer()
    , pScript(nullptr)
{
    pScript = stageData01;
}

void Stage::update(OBJ2DManager* obj2dManager, BG* bg)
{
    while (pScript->setEnemy_ && pScript->time_ == timer)
    {
        pScript->setEnemy_(obj2dManager, bg, pScript->pos_);

        pScript++;
    }

    ++timer;

    // ƒ‹[ƒvˆ—(‰¼)
    if (!pScript->setEnemy_)
    {
        pScript = 0;
        timer = 0;
        pScript = stageData01;
    }
}