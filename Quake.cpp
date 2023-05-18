#include "all.h"

// ダメージを受けた時の揺れる演出を行う
void Quake::quakeDamage(OBJ2D* obj)
{
    if (!obj->isQuake_) return;

    Transform* t = obj->transform_;

    switch (obj->quakeState_)
    {
    case 0: // 右上
        t->position_.x +=  ADD_QUAKE_POS;
        t->position_.y += -ADD_QUAKE_POS;

        ++obj->quakeState_;
        break;
    case 1: // 右下
        t->position_.y += ADD_QUAKE_POS * 2;

        ++obj->quakeState_;
        break;
    case 2: // 左下
        t->position_.x += -ADD_QUAKE_POS * 2;

        ++obj->quakeState_;
        break;
    case 3: // 左上
        t->position_.y += -ADD_QUAKE_POS * 2;

        ++obj->quakeState_;
        break;
    case 4: // 真ん中
        t->position_.x += ADD_QUAKE_POS;
        t->position_.y += ADD_QUAKE_POS;

        // ループ回数が最大ループ数未満なら最初から繰り返す
        if (obj->quakeLoop_ < LOOP_MAX)
        {
            ++obj->quakeLoop_;
            obj->quakeState_ = 0;
            break;
        }

        // quake終了
        obj->quakeState_ = 0;
        obj->quakeLoop_ = 0;
        obj->isQuake_ = false;
        break;
    }

}
