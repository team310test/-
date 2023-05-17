#include "all.h"

// �_���[�W���󂯂����̗h��鉉�o���s��
void Quake::quakeDamage(OBJ2D* obj)
{
    if (!obj->isQuake_) return;

    Transform* t = obj->transform_;

    switch (state_)
    {
    case 0: // �E��
        t->position_.x +=  ADD_QUAKE_POS;
        t->position_.y += -ADD_QUAKE_POS;

        ++state_;
        break;
    case 1: // �E��
        t->position_.y += ADD_QUAKE_POS * 2;

        ++state_;
        break;
    case 2: // ����
        t->position_.x += -ADD_QUAKE_POS * 2;

        ++state_;
        break;
    case 3: // ����
        t->position_.y += -ADD_QUAKE_POS * 2;

        ++state_;
        break;
    case 4: // �^��
        t->position_.x += ADD_QUAKE_POS;
        t->position_.y += ADD_QUAKE_POS;

        // ���[�v�񐔂��ő僋�[�v�������Ȃ�ŏ�����J��Ԃ�
        if (loop_ < LOOP_MAX)
        {
            ++loop_;
            state_ = 0;
            break;
        }

        // quake�I��
        state_ = 0;
        loop_  = 0;
        obj->isQuake_ = false;
        break;
    }

}
