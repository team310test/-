#include "all.h"

// ダメージを受けた時の揺れる演出を行う
void Quake::quakeDamage(OBJ2D* obj)
{
    if (!obj->isQuake_) return;

    Transform* t = obj->transform_;

    switch (state_)
    {
    case 0: // 右上
        t->position_.x +=  ADD_QUAKE_POS;
        t->position_.y += -ADD_QUAKE_POS;

        ++state_;
        break;
    case 1: // 右下
        t->position_.y += ADD_QUAKE_POS * 2;

        ++state_;
        break;
    case 2: // 左下
        t->position_.x += -ADD_QUAKE_POS * 2;

        ++state_;
        break;
    case 3: // 左上
        t->position_.y += -ADD_QUAKE_POS * 2;

        ++state_;
        break;
    case 4: // 真ん中
        t->position_.x += ADD_QUAKE_POS;
        t->position_.y += ADD_QUAKE_POS;

        // ループ回数が最大ループ数未満なら最初から繰り返す
        if (loop_ < LOOP_MAX)
        {
            ++loop_;
            state_ = 0;
            break;
        }

        // quake終了
        state_ = 0;
        loop_  = 0;
        obj->isQuake_ = false;
        break;
    }

}
