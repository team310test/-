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
    while (pScript->enemyData_ && pScript->time_ == timer)
    {
        OBJ2D* PARENT = nullptr;

        while (pScript->enemyData_->behavior_)
        {
            VECTOR2 pos =
            {
                pScript->pos_.x + pScript->enemyData_->pos_.x,
                pScript->pos_.y + pScript->enemyData_->pos_.y
            };

            PARENT = setEnemy(pScript->enemyData_->behavior_, PARENT, pos, pScript->enemyData_->zOrder_);
            pScript->enemyData_++;
        }
        pScript++;
    }
    ++timer;

    if (!pScript->enemyData_)
    {
        pScript = stageData;
        timer = 0;
    }
}