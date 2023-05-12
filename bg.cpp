#include "all.h"

float BG::bgSubScale_           = 0.0f; // スケールの縮小速度
int   BG::bgSprTableIndex_      = 0;    // 背景テーブル配列の現在の要素数
int   BG::isAddbgSprTableIndex_ = 1;    // bgSprTableIndex_を加算するか決める


// 背景配列
const int bgSprites[] = {
    GAME_TEXNO::BG01,
    GAME_TEXNO::BG02,
    GAME_TEXNO::BG03,
    GAME_TEXNO::BG04,
    GAME_TEXNO::BG05,
    GAME_TEXNO::BG06,
    GAME_TEXNO::BG07,
    GAME_TEXNO::BG08,
    GAME_TEXNO::BG09,
    GAME_TEXNO::BG_END,
};

BG::BG()
    :bg_()
{
}


BG::~BG()
{
    for (OBJ2D*& bg : bg_) safe_delete(bg);
}


void BG::init()
{
    //new char[1]; // メモリリーク確認
    for (OBJ2D*& bg : bg_)
    {
        bg = new OBJ2D(
            new Renderer,
            new Collider,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr
        );
    }
    //new char[2]; // メモリリーク確認

    bgSubScale_           = BG_SHRINK_SPEED;
    bgSprTableIndex_      = 0;
    isAddbgSprTableIndex_ = 1;

    // BG用データのクリア
    clear();

}


void BG::clear()
{
    // スケールとスプライト画像の設定
    bg_[0]->transform_->scale_   = bg_[1]->transform_->scale_   = { 1, 1 };
    bg_[2]->transform_->scale_   = bg_[3]->transform_->scale_   = { 5, 5 };
    bg_[4]->transform_->scale_   = bg_[5]->transform_->scale_   = { 10, 10 };
    bg_[6]->transform_->scale_   = bg_[7]->transform_->scale_   = { 50, 50 };
    bg_[8]->transform_->scale_   = bg_[9]->transform_->scale_   = { 100, 100 };
    bg_[10]->transform_->scale_  = bg_[11]->transform_->scale_  = { 500, 500 };

    bg_[0]->bgSprNo_   = bg_[1]->bgSprNo_   = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;
    bg_[2]->bgSprNo_   = bg_[3]->bgSprNo_   = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;
    bg_[4]->bgSprNo_   = bg_[5]->bgSprNo_   = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;
    bg_[6]->bgSprNo_   = bg_[7]->bgSprNo_   = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;
    bg_[8]->bgSprNo_   = bg_[9]->bgSprNo_   = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;
    bg_[10]->bgSprNo_  = bg_[11]->bgSprNo_  = bgSprites[bgSprTableIndex_]; ++bgSprTableIndex_;


    int bgSetPosXNum = 1; // スクロールの右左配置設定用

    // 初期設定
    for (OBJ2D*& bg : bg_)
    {
        Transform* t = bg->transform_;
        Collider*  c = bg->collider_;
        Renderer*  r = bg->renderer_;

        c->targetScale_ = t->scale_;         // スケール
        c->size_        = { 3840, 1080 + 256 };    // 画像サイズ

        t->position_.x  = (bgSetPosXNum % 2 == 0) ? c->size_.x : 0.0f; // 2で割れたらスクロールの右側担当にする
        t->position_.y  = bg->bg_->WINDOW_H * 0.5f;             // yだけ真ん中に設定（見栄え）

        t->velocity_.x  = BG_SCROLL_SPEED;                      // スクロール速度

        r->color_       = { 1, 1, 1, 1 };                       // カラー
        r->color_.w     = (t->scale_.x < DISP_BG_SCALE_MAX)     // 不透明度
                        ? DEFAULT_ALPHA_COLOR : 0.0f; 
        r->targetColor_ = r->color_;                            // 目標カラー

        ++bgSetPosXNum;
    }

}


void BG::update()
{
    moveBack();
}


// 背景更新処理(private)
static constexpr float ADD_ALPHA_COLOR     =  0.001f;  // 不透明度の増加速度
static constexpr float SUBJECT_ALPHA_COLOR = -0.0025f; // 不透明度の減少速度
void BG::moveBack()
{
    // 最初と最後の背景のスケール確認
    //GameLib::debug::setString("bg[0]Scale:%f", bg_[0]->transform_->scale_.x);
    //GameLib::debug::setString("bg[11]Scale:%f", bg_[11]->transform_->scale_.x);

    for (OBJ2D*& bg : bg_)
    {
        Transform* t = bg->transform_;
        Renderer*  r = bg->renderer_;
        Collider*  c = bg->collider_;

        // 値確認
        {
            //GameLib::debug::setString("position + size:%f", (t->position_.x + c->size_.x)); // 画像の右端の値
            //GameLib::debug::setString("scale:%f", t->scale_.x); // スケール
            //GameLib::debug::setString("color.z:%f", r->color_.w); // 不透明度
        }

/////////////// スケール更新 //////////////////////////////////////////////

        if (t->scale_.x > c->targetScale_.x)
        {
            // scale減少
            t->scale_ += (bgSubScale_ * t->scale_); // scaleの大きさで縮小速度を調整更新

            // 目標より小さくなったら修正
            if (t->scale_.x < c->targetScale_.x) t->scale_ = c->targetScale_;
        }

/////////////// カラー不透明度更新 /////////////////////////////////////////

        if (r->color_.w > r->targetColor_.w) // 目標値より大きい場合
        {
            // 不透明度減少
            r->color_.w += (SUBJECT_ALPHA_COLOR * r->color_.w);

            // 超過分を修正
            if (r->color_.w < r->targetColor_.w) r->color_.w = r->targetColor_.w;
        }
        else if (r->color_.w < r->targetColor_.w) // 目標値より小さい場合
        {
            // 不透明度増加
            r->color_.w += ADD_ALPHA_COLOR;

            // 超過分を修正
            if (r->color_.w > r->targetColor_.w) r->color_.w = r->targetColor_.w;
        }


/////////////// 位置更新 ///////////////////////////////////////////////////

        if (t->scale_.x > DISP_BG_SCALE_MAX) continue;  // scaleが最大表示より大きければ位置を更新しない
        
        // 位置に速度を足す
        if (t->scale_.x == c->targetScale_.x) t->position_.x += (t->velocity_.x * t->scale_.x); // scaleの大きさでスクロール速度を調整（小さい（遠い）ほどゆっくりになる）

        // 画像の右端が画面左端を超えたら画像サイズ2つ分右に移動
        if ( (t->position_.x + c->size_.x) < 0) t->position_.x += (c->size_.x * 2.0f);  
        
    }

}


void BG::drawBack()
{
    // 背景描画する
    for (OBJ2D*& bg : bg_)
    {
        Transform* t = bg->transform_;
        Collider*  c = bg->collider_;
        Renderer*  r = bg->renderer_;

        GameLib::texture::begin(bg->bgSprNo_);
        GameLib::texture::draw(
            bg->bgSprNo_,
            t->position_, t->scale_,
            { 0, 0 }, c->size_,
            { 0.0f,  (c->size_.y * 0.5f) }, 
            0,
            r->color_
        );
        GameLib::texture::end(bg->bgSprNo_);
    }

}


void BG::setBGShrink()
{
    for (OBJ2D*& bg : bg_)
    {
        Transform* t = bg->transform_;
        Collider*  c = bg->collider_;
        Renderer*  r = bg->renderer_;

        // 画像更新(targetScaleを決める必要があるのでここで処理を行う)
        if( (t->scale_.x >= 0.01f && t->scale_.x <= 0.011f) || t->scale_.x == 0.05f)
        {
            // 背景が最後の背景ならそのまま、そうでなければ次の背景にする
            bg->bgSprNo_ = (bgSprites[bgSprTableIndex_] < BG_END)
                         ? bgSprites[bgSprTableIndex_]
                         : bg->bgSprNo_;
            if (isAddbgSprTableIndex_ % 2 == 0) ++bgSprTableIndex_;
            ++isAddbgSprTableIndex_;

            if (t->scale_.x >= 0.01f && t->scale_.x <= 0.011f) t->scale_ = { 10,10 };
            if (t->scale_.x == 0.05f) t->scale_ = { 50, 50 };

            r->color_ = { 1,1,1,0 };
            r->targetColor_ = r->color_;
        }

        t->velocity_ *= 1.15f;

        // scaleの?を目標値に設定
        c->targetScale_ = t->scale_ * 0.1f;

        bgSubScale_ = BG_SHRINK_SPEED; // 縮小速度をリセット

        // 不透明度はデフォルトのscaleの値の1.0f以下なら減らし、最大表示より小さければ増やす
        if (t->scale_.x <= 1.0f) r->targetColor_.w = r->color_.w * 0.25f;
        else if (t->scale_.x <= DISP_BG_SCALE_MAX) r->targetColor_.w = DEFAULT_ALPHA_COLOR;

    }

}