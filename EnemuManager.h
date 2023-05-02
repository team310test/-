#pragma once

#include <vector>
#include "Enemy.h"

// エネミーマネージャー
class EnemuManager
{
private:
    EnemuManager(){}
    ~EnemuManager(){}

public:
    // 唯一のインスタンス取得
    static EnemuManager& Instance()
    {
        static EnemuManager instance;
        return instance;
    }

    // 更新処理
    void Update(float elapsedTime);

    // 描画処理
    void Render(ID3D11DeviceContext* dc, Shader shader);

private:
    std::vector<Enemy*> enemies;
};

