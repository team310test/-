#include "all.h"

#define X BG::WINDOW_W + 256.0f

// addition_(追加変数)は省略できる
STAGE_SCRIPT stageData01[] =
{
    SET_ENEMY_TARGET_X(180,enemy02, X,800.0f, 5.0f,0.0f, 1000.0f, 10.0f,-5.0f),
    SET_ENEMY_LENE(360,enemy01, X,300.0f, 5.0f),
    SET_ENEMY_END
};

Stage::Stage()
    : timer()
    , pScript(nullptr)
{
    pScript = stageData01;
}

void Stage::update(OBJ2DManager* obj2dManager, BG* bg)
{
    while (pScript->enemyData_ && pScript->time_ == timer)
    {
        OBJ2D* orgParent = nullptr;
        OBJ2D* Parent[10] = {};
        while (pScript->enemyData_ && pScript->enemyData_->behavior_)
        {
            // 0番目ではなくParentのparentNo番目がnullptrなら
            if(pScript->enemyData_->no_ != 0 && !Parent[pScript->enemyData_->parentNo_])
                assert(!"parent[parentNo]はnullptrです");
            // parentNoが0以下だとエラーを吐く
            if(pScript->enemyData_->parentNo_ < PARENT_NO::PARENT0) assert(!"parentNoが使用できない値です");
            
            VECTOR2 pos = { pScript->pos_.x + pScript->enemyData_->pos_.x, pScript->pos_.y + pScript->enemyData_->pos_.y };
            
            OBJ2D* hold =
            setEnemy
            (
                obj2dManager
                , bg
                , pos
                , pScript->enemyData_->behavior_
                , pScript->update_
                , Parent[pScript->enemyData_->parentNo_]
                , orgParent
                , pScript->enemyData_->zOrder_
                , pScript->addition_
            );
            // 速度・追加パラメータ設定
            hold->actorComponent_->accel_ = pScript->accel_;
            hold->actorComponent_->addition_ = pScript->addition_;

            if (!orgParent) orgParent = hold;                           // orgParentがnullptrなら元の親を設定する
            
            // noが-1より大きかったら
            if (pScript->enemyData_->no_ > -1)
            {
                // Parentのno番目に値が入っていれば
                if (Parent[pScript->enemyData_->no_])assert(!"parentを上書きしようとしています");

                Parent[pScript->enemyData_->no_] = hold;                    // no番目のParentを設定
            }

            pScript->enemyData_++;
        }
        pScript->DataReset();   // enemyDataを先頭に戻す
        pScript++;
    }

    ++timer;

    // 最後の敵が出現するとループする
    if (!pScript->enemyData_)
    {
        timer = 0;
        pScript = stageData01;
    }
}