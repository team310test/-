#pragma once

class BG
{
public:
    static const int WINDOW_W = 1920;                // ウインドウの幅
    static const int WINDOW_H = 1080;                // ウインドウの高さ
    static const int CLIENT_W = 1280;                // クライアント領域の幅
    static const int CLIENT_H = 720;                 // クライアント領域の高さ

    static constexpr float ADJUST_Y = 0.25f;         // あたり判定での位置調整用（縦）
    static constexpr float ADJUST_X = 0.025f;        // あたり判定での位置調整用（横）

    static constexpr float AREA_LIMIT = 256.0f;      // 世界からこれ以上はみ出たら消えるS
    
private:
    static const int BG_MAX = 10;                        // 背景の最大数

    static constexpr float DEFAULT_ALPHA_COLOR = 0.2f;  // 初期透明度

    static constexpr float DISP_BG_SCALE_MIN = 0.0f;    // この値より背景のscaleが小さい場合は更新・描画しない
    static constexpr float DISP_BG_SCALE_MAX = 2.0f;    // この値より背景のscaleが大きい場合は更新・描画しない

private:
    OBJ2D* player_;
    std::unique_ptr<OBJ2D> bg_[BG_MAX];

    int bgSprNo_; // スプライト画像TEXNO

public:
    BG();
    ~BG();

    // 初期化
    void init(OBJ2D* player);
    // 更新
    void update();
    // 背景描画
    void drawBack();

    // 背景の縮小設定
    void setBGShrink(); 

private:
    // クリア
    void clear();

    // 背景の更新処理
    void moveBack() const;
};

//******************************************************************************
