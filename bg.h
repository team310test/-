#pragma once

class BG
{
public:
    static const int WINDOW_W = 1920;                // �E�C���h�E�̕�
    static const int WINDOW_H = 1080;                // �E�C���h�E�̍���
    static const int CLIENT_W = 1280;                // �N���C�A���g�̈�̕�
    static const int CLIENT_H = 720;                 // �N���C�A���g�̈�̍���

    static constexpr float ADJUST_Y = 0.25f;         // �����蔻��ł̈ʒu�����p�i�c�j
    static constexpr float ADJUST_X = 0.025f;        // �����蔻��ł̈ʒu�����p�i���j

    static constexpr float AREA_LIMIT = 256.0f;      // ���E���炱��ȏ�͂ݏo���������
    
private:
    static const int BG_ARRAY_MAX = 12;                     // �w�i�z��̍ő吔

    static constexpr float DEFAULT_ALPHA_COLOR = 0.2f;      // ���������x

    static constexpr float DISP_BG_SCALE_MIN = 0.011f;      // ���̒l���w�i��scale���������ꍇ�͍X�V�E�`�悵�Ȃ�(�k��5��)
    static constexpr float DISP_BG_SCALE_MAX = 10.0f;       // ���̒l���w�i��scale���傫���ꍇ�͍X�V�E�`�悵�Ȃ�

public:
    static float bgSubScale_;           // scale�̏k�����x

private:
    OBJ2D* bg_[BG_ARRAY_MAX];


    static int   bgSprTableIndex_;      // �w�i�e�[�u���z��̌��݂̗v�f��
    static int   isAddbgSprTableIndex_; // bgSprTableIndex_�����Z���邩���߂�

public:
    BG();
    ~BG();

    // ������
    void init();
    // �X�V
    void update();
    // �w�i�`��
    void drawBack();

    // �w�i�̏k���ݒ�
    void setBGShrink(); 

private:
    // �N���A
    void clear();

    // �w�i�̍X�V����
    void moveBack();
};

//******************************************************************************
