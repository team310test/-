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
    bool FadeIn(OBJ2D*,  const float& fadeInSpeed  =  0.01f);			            // �t�F�[�h�C��
    bool FadeOut(OBJ2D*, const float& fadeOutSpeed = -0.01f);		                // �t�F�[�h�A�E�g
    //bool Shrink(OBJ2D*, const VECTOR2& = { 1.0f,1.0f }, const float& = 0.01f);    // �k��
    bool Enlarge(OBJ2D* obj, const VECTOR2& targetScale = { 1.0f,1.0f }, const float& speed = 0.01f);     // �g��
    bool ContactPos(OBJ2D*, const VECTOR2& targetPos, const float& constactSpeed = 1.0f);   // �w�肵�����W�Ɉړ� 
    
    // OBJ2DManager
    bool isObjType(OBJ2DManager* obj2dManager, const OBJ_TYPE& objType);    // �w�肵���I�u�W�F�N�g�̃^�C�v�����݂��Ă�����true��Ԃ�
};

// <���̑�>

// �w�肵���t���[�����o�߂����true��Ԃ�
bool wait(const int& waitTime);
