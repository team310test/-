#pragma once

class BG
{
public:
    static const int WINDOW_W = 1920;                   // ウインドウの幅
    static const int WINDOW_H = 1080;                    // ウインドウの高さ
    static const int CLIENT_W = 1280;                   // クライアント領域の幅
    static const int CLIENT_H = 720;                    // クライアント領域の高さ

    static constexpr float ADJUST_Y = 0.25f;            // あたり判定での位置調整用（縦）
    static constexpr float ADJUST_X = 0.025f;           // あたり判定での位置調整用（横）

    static constexpr float AREA_LIMIT = 256.0f;         // 世界からこれ以上はみ出たら消えるS
    
private:
    OBJ2D* player_;
    std::unique_ptr<OBJ2D> bg_[4];

public:
    int bgSprNo_;

public:
    BG();

    // 初期化
    void init(OBJ2D* player);
    // 更新
    void update();
    // 背景描画
    void drawBack();

    // 背景のtargetScale(縮小目標値)を設定
    void setBGTargetScale(); 

private:
    // クリア
    void clear();

    // 背景の更新処理
    void moveBack() const;
};

//******************************************************************************
