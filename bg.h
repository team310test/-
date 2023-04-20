#pragma once

class BG
{
public:
    static const int WINDOW_W = 1920;                   // �E�C���h�E�̕�
    static const int WINDOW_H = 1080;                    // �E�C���h�E�̍���
    static const int CLIENT_W = 1280;                   // �N���C�A���g�̈�̕�
    static const int CLIENT_H = 720;                    // �N���C�A���g�̈�̍���

    static constexpr float ADJUST_Y = 0.25f;            // �����蔻��ł̈ʒu�����p�i�c�j
    static constexpr float ADJUST_X = 0.025f;           // �����蔻��ł̈ʒu�����p�i���j

    static constexpr float AREA_LIMIT = 256.0f;         // ���E���炱��ȏ�͂ݏo���������S
    
private:
    OBJ2D* player_;
    std::unique_ptr<OBJ2D> bg_[4];

public:
    int bgSprNo_;

public:
    BG();

    // ������
    void init(OBJ2D* player);
    // �X�V
    void update();
    // �w�i�`��
    void drawBack();

    // �w�i��targetScale(�k���ڕW�l)��ݒ�
    void setBGTargetScale(); 

private:
    // �N���A
    void clear();

    // �w�i�̍X�V����
    void moveBack() const;
};

//******************************************************************************
