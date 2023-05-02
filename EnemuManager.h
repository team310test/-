#pragma once

#include <vector>
#include "Enemy.h"

// �G�l�~�[�}�l�[�W���[
class EnemuManager
{
private:
    EnemuManager(){}
    ~EnemuManager(){}

public:
    // �B��̃C���X�^���X�擾
    static EnemuManager& Instance()
    {
        static EnemuManager instance;
        return instance;
    }

    // �X�V����
    void Update(float elapsedTime);

    // �`�揈��
    void Render(ID3D11DeviceContext* dc, Shader shader);

private:
    std::vector<Enemy*> enemies;
};

