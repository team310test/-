#include "all.h"

#define X BG::WINDOW_W + 256.0f

// addition_(追加変数)は省略できる
STAGE_SCRIPT stageData01[] =
{
    SET_ENEMY_TARGET_X(180,enemy02, X,800.0f, 5.0f,0.0f, 1000.0f, 10.0f,-5.0f),
    SET_ENEMY_LENE(360,enemy01, X,300.0f, 5.0f),
    SET_ENEMY_END
};
STAGE_SCRIPT stageData02[] =
{
    SET_ENEMY_LENE(520,enemy01, X,300.0f, 10.0f),
    SET_ENEMY_LENE(520,enemy01, X,900.0f, 10.0f),
    SET_ENEMY_LENE(700,enemy01, X,500.0f, 5.0f),
    SET_ENEMY_END
};

STAGE_SCRIPT* STAGE_DATA[] =
{
    stageData01,
    stageData02,
};

Stage::Stage()
    : timer_()
    , pScript_(nullptr)
    , stageNum_()
{
    pScript_ = STAGE_DATA[stageNum_];
}
int Stage::shrinkNum = 0;
//#define error

void Stage::update(OBJ2DManager* obj2dManager, BG* bg)
{
    // timer表示
    GameLib::debug::setString("timer:%d", timer_);

    // ステージ遷移
    if (stageNum_ != shrinkNum)
    {
        if (shrinkNum > 0 && shrinkNum < stageMax)
        {
            timer_ = 0;
            pScript_ = STAGE_DATA[stageNum_];
        }
#ifdef error
        else
        {
            assert(!"shrinkNumに異常な値が入っています");
        }
#endif
        stageNum_ = shrinkNum;
    }

    // 敵出現
    while (pScript_->enemyData_ && pScript_->time_ == timer_)
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
    if (!pScript_->enemyData_)
    {
        timer_ = 0;
        pScript_ = STAGE_DATA[stageNum_];
    }
}