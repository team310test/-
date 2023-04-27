#include "all.h"


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
            nullptr
        );
    }
    //new char[2]; // メモリリーク確認

    // BG用データのクリア
    clear();

}


void BG::clear()
{
    // スケールとスプライト画像の設定
    bg_[0]->transform_->scale_ = bg_[1]->transform_->scale_ = { 1, 1 };
    bg_[2]->transform_->scale_ = bg_[3]->transform_->scale_ = { 2, 2 };
    bg_[4]->transform_->scale_ = bg_[5]->transform_->scale_ = { 4, 4 };
    bg_[6]->transform_->scale_ = bg_[7]->transform_->scale_ = { 8, 8 };
    bg_[8]->transform_->scale_ = bg_[9]->transform_->scale_ = { 16, 16 };

    bg_[0]->bgSprNo_ = bg_[1]->bgSprNo_ = BACK01;
    bg_[2]->bgSprNo_ = bg_[3]->bgSprNo_ = BACK02;
    bg_[4]->bgSprNo_ = bg_[5]->bgSprNo_ = BACK01;
    bg_[6]->bgSprNo_ = bg_[7]->bgSprNo_ = BACK02;
    bg_[8]->bgSprNo_ = bg_[9]->bgSprNo_ = BACK01;


    int bgNum = 1; // スクロールの右左配置設定用

    // 初期設定
    for (OBJ2D*& bg : bg_)
    {
        Transform* t = bg->transform_;
        Collider*  c = bg->collider_;
        Renderer*  r = bg->renderer_;

        c->targetScale_ = t->scale_;         // スケール
        c->size_        = { 3840, 1080 };    // 画像サイズ

        t->position_.x  = (bgNum % 2 == 0) ? c->size_.x : 0.0f; // 2で割れたらスクロールの右側担当にする
        t->position_.y  = bg->bg_->WINDOW_H * 0.5f;             // yだけ真ん中に設定（見栄え）

        t->velocity_.x  = -5.0f;             // スクロール速度

        r->color_   = { 1, 1, 1, 1 };        // カラー
        r->color_.w = (t->scale_.x < DISP_BG_SCALE_MAX) // 不透明度
                    ? DEFAULT_ALPHA_COLOR : 0.0f; 
        r->targetColor_ = r->color_;         // 目標カラー

        ++bgNum;
    }

}


void BG::update()
{
    moveBack();
}


// 背景更新処理(private)
float BG::subScale = -0.0035f;    // scaleの縮小速度
static constexpr float ADD_ALPHA_COLOR     =  0.001f;  // 不透明度の増加速度
static constexpr float SUBJECT_ALPHA_COLOR = -0.0025f; // 不透明度の減少速度
void BG::moveBack()
{
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

        if (t->scale_.x < DISP_BG_SCALE_MIN) continue;  // scaleが最小表示より小さければcontinue


/////////////// スケール更新 //////////////////////////
        if (t->scale_.x > c->targetScale_.x)
        {
            // scale減少
            t->scale_ += (subScale * t->scale_); // scaleの大きさで縮小速度を調整更新

            // 目標より小さくなったら修正
            if (t->scale_.x < c->targetScale_.x) t->scale_ = c->targetScale_;
        }


/////////////// カラー不透明度更新 /////////////////////
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


/////////////// 位置更新 /////////////////////////////
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

        if (t->scale_.x < DISP_BG_SCALE_MIN) continue; // scaleが最小表示より小さければcontinue
        if (t->scale_.x > DISP_BG_SCALE_MAX) continue; // scaleが最大表示より大きければcontinue


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

        if (t->scale_.x < DISP_BG_SCALE_MIN) continue; // scaleが最小表示より小さければcontinue

        t->velocity_ *= 1.25f;

        // scaleの半分を目標値に設定
        c->targetScale_ = t->scale_ * 0.5f;

        // 不透明度はデフォルトのscaleの値の1.0f以下なら減らし、最大表示より小さければ増やす
        if (t->scale_.x <= 1.0f) r->targetColor_.w = r->color_.w * 0.75f;
        else if (t->scale_.x <= DISP_BG_SCALE_MAX) r->targetColor_.w = DEFAULT_ALPHA_COLOR;
    }

}