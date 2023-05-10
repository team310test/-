#pragma once

class BG
{
public:
    static const int WINDOW_W = 1920;                // �E�C���h�E�̕�
    static const int WINDOW_H = 1080;                // �E�C���h�E�̍���
    static const int CLIENT_W = 1280;                // �N���C�A���g�̈�̕�
    static const int CLIENT_H = 720;                 // �N���C�A���g�̈�̍���
    static constexpr int WINDOW_W_F = static_cast<float>(WINDOW_W);                // �E�C���h�E�̕�(float)
    static constexpr int WINDOW_H_F = static_cast<float>(WINDOW_H);                // �E�C���h�E�̍���(float)

    static constexpr float ADJUST_Y = 0.25f;         // �����蔻��ł̈ʒu�����p�i�c�j
    static constexpr float ADJUST_X = 0.025f;        // �����蔻��ł̈ʒu�����p�i���j

    static constexpr float AREA_LIMIT = 256.0f;      // ���E���炱��ȏ�͂ݏo���������
    
private:
    static const int BG_MAX = 12;                       // �w�i�̍ő吔

    static constexpr float DEFAULT_ALPHA_COLOR = 0.2f;  // ���������x

    static constexpr float DISP_BG_SCALE_MIN = 0.03125f;    // ���̒l���w�i��scale���������ꍇ�͍X�V�E�`�悵�Ȃ�(�k��5��)
    static constexpr float DISP_BG_SCALE_MAX = 2.0f;    // ���̒l���w�i��scale���傫���ꍇ�͍X�V�E�`�悵�Ȃ�

public:
    static float subScale;    // scale�̏k�����x

private:
    OBJ2D* bg_[BG_MAX];

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
