#include "all.h"

STAGE_SCRIPT* STAGE_DATA[] =
{
    //stageData01,
    //stageData02,
    stageData03,
    stageData04,
    //stageData05,
    nullptr
};

int Stage::shrinkNum_ = 0;
Stage::Stage()
    : timer_()
    , pScript_(nullptr)
    , stageNum_()
{
    shrinkNum_ = 0;
    pScript_ = STAGE_DATA[stageNum_];
}
<<<<<<< HEAD
int Stage::shrinkNum_ = 0;
=======
>>>>>>> maeyama
//#define error

void Stage::update(OBJ2DManager* obj2dManager, BG* bg)
{
    // timer表示
    //GameLib::debug::setString("timer:%d", timer_);

    // ステージ遷移
    if (stageNum_ != shrinkNum_)
    {
        timer_ = 0;
        stageNum_ = shrinkNum_;
<<<<<<< HEAD
        if (shrinkNum_ >= 0 && shrinkNum_ < STAGE_MAX)
=======
        if (shrinkNum_ >= 0 && shrinkNum_ < stageMax)
>>>>>>> maeyama
        {
            pScript_ = STAGE_DATA[stageNum_];
        }
        else
        {
#ifdef error
            assert(!"shrinkNumに異常な値が入っています");
#else
            pScript_ = STAGE_DATA[STAGE_MAX - 1];
#endif
        }
    }

    // 敵出現
    while (pScript_ && pScript_->enemyData_ && pScript_->time_ == timer_)
    {
        OBJ2D* orgParent = nullptr;
        OBJ2D* Parent[10] = {};
        while (pScript_->enemyData_ && pScript_->enemyData_->behavior_)
        {
            // 0番目ではなくParentのparentNo番目がnullptrなら
            if(pScript_->enemyData_->no_ != 0 && !Parent[pScript_->enemyData_->parentNo_])
                assert(!"parent[parentNo]はnullptrです");
            // parentNoが0以下だとエラーを吐く
            if(pScript_->enemyData_->parentNo_ < PARENT_NO::PARENT0) 
                assert(!"parentNoが使用できない値です");
            
            VECTOR2 pos = { pScript_->pos_.x + pScript_->enemyData_->pos_.x, pScript_->pos_.y + pScript_->enemyData_->pos_.y };
            
            OBJ2D* hold =
            setEnemy
            (
                obj2dManager
                , bg
                , pos
                , pScript_->enemyData_->behavior_
                , pScript_->update_
                , Parent[pScript_->enemyData_->parentNo_]
                , orgParent
                , pScript_->enemyData_->zOrder_
                , pScript_->addition_
            );
            // 速度・追加パラメータ設定
            hold->actorComponent_->accel_ = pScript_->accel_;
            hold->actorComponent_->addition_ = pScript_->addition_;

            if (!orgParent) orgParent = hold;                           // orgParentがnullptrなら元の親を設定する
            
            // noが-1より大きかったら
            if (pScript_->enemyData_->no_ > -1)
            {
                // Parentのno番目に値が入っていれば
                if (Parent[pScript_->enemyData_->no_])assert(!"parentを上書きしようとしています");

                Parent[pScript_->enemyData_->no_] = hold;                    // no番目のParentを設定
            }

            pScript_->enemyData_++;
        }
        pScript_->DataReset();   // enemyDataを先頭に戻す
        pScript_++;
    }

    ++timer_;

    // 最後の敵が出現するとループする
    if (pScript_ && !pScript_->enemyData_)
    {
        timer_ = 0;
<<<<<<< HEAD
        if (shrinkNum_ >= 0 && shrinkNum_ < STAGE_MAX)
=======
        if (shrinkNum_ >= 0 && shrinkNum_ < stageMax)
>>>>>>> maeyama
        {
            pScript_ = STAGE_DATA[stageNum_];
        }
        else 
        {
#ifdef error
            assert(!"shrinkNumに異常な値が入っています");
#else
            pScript_ = STAGE_DATA[STAGE_MAX - 1];
#endif
        }
    }
}