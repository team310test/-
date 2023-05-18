#include "all.h"

// �_���[�W���󂯂����̗h��鉉�o���s��
void Quake::quakeDamage(OBJ2D* obj)
{
    if (!obj->isQuake_) return;

    Transform* t = obj->transform_;

    switch (obj->quakeState_)
    {
    case 0: // �E��
        t->position_.x +=  ADD_QUAKE_POS;
        t->position_.y += -ADD_QUAKE_POS;

        ++obj->quakeState_;
        break;
    case 1: // �E��
        t->position_.y += ADD_QUAKE_POS * 2;

        ++obj->quakeState_;
        break;
    case 2: // ����
        t->position_.x += -ADD_QUAKE_POS * 2;

        ++obj->quakeState_;
        break;
    case 3: // ����
        t->position_.y += -ADD_QUAKE_POS * 2;

        ++obj->quakeState_;
        break;
    case 4: // �^��
        t->position_.x += ADD_QUAKE_POS;
        t->position_.y += ADD_QUAKE_POS;

        // ���[�v�񐔂��ő僋�[�v�������Ȃ�ŏ�����J��Ԃ�
        if (obj->quakeLoop_ < LOOP_MAX)
        {
            ++obj->quakeLoop_;
            obj->quakeState_ = 0;
            break;
        }

        // quake�I��
        obj->quakeState_ = 0;
        obj->quakeLoop_ = 0;
        obj->isQuake_ = false;
        break;
    }

}
