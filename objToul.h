#pragma once

// OBJ2D�ɒP���ȓ�����������
class objToul
{
public:
    static objToul& instance() {
        static objToul inst;
        return inst;
    }
    // OBJ2D
    bool FadeOut(OBJ2D*, float = 0.01f);		                    // �t�F�[�h�A�E�g
    bool FadeIn(OBJ2D*, float = 0.01f);			                    // �t�F�[�h�C��
    bool Shrink(OBJ2D*, VECTOR2 = {1.0f,1.0f}, float = 0.01f); 	    // �k��
    bool Enlarge(OBJ2D*, VECTOR2 = { 1.0f,1.0f }, float = 0.01f);   // �g��
    bool ContactPos(OBJ2D*, VECTOR2, float = 1.0f);                 // �w�肵�����W�Ɉړ� 
    
    // OBJ2DManager
    bool isObjType(OBJ2DManager* obj2dManager, OBJ_TYPE objType);    // �w�肵���I�u�W�F�N�g�̃^�C�v�����݂��Ă�����true��Ԃ�
};

// <���̑�>

// �w�肵���t���[�����o�߂����true��Ԃ�
bool wait(int waitTime);
