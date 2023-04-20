#include "all.h"

//bool isDebugDraw;

BG::BG()
    :player_(nullptr)
    , bgSprNo_(0)
{
    for (auto& bg : bg_)
    {
        bg = std::unique_ptr<OBJ2D>(
                new OBJ2D(
                    new Renderer,
                    new Collider,
                    this,
                    nullptr,
                    nullptr,
                    nullptr)
            );
    }
}


void BG::init(OBJ2D* player)
{
    player_ = player;

    // BG用データのクリア
    clear();

    //isDebugDraw = false;
}


void BG::clear()
{
    bg_[0]->transform_->scale_ = bg_[1]->transform_->scale_ = { 1, 1 };
    //bg_[2]->transform_->scale_ = bg_[3]->transform_->scale_ = { 2, 2 };

    bg_[0]->bg_->bgSprNo_ = BACK01;
    bg_[1]->bg_->bgSprNo_ = BACK01;
    //bg_[2]->bg_->bgSprNo_ = BACK01;
    //bg_[3]->bg_->bgSprNo_ = BACK01;


    int num = 1;

    for (auto& bg : bg_)
    {
        bg->collider_->size_        = { 3840, 1080 };
        bg->transform_->position_.x = (num % 2 == 0) // 2で割れたら
                                    ? 3840.0f + bg->collider_->size_.x * 0.5f // 位置を右側にする
                                    : 0.0f    + bg->collider_->size_.x * 0.5f;
        bg->transform_->position_.y = bg->bg_->WINDOW_H * 0.5f;
        bg->collider_->targetScale_ = bg->transform_->scale_;
        bg->renderer_->color_       = { 1, 1, 1, 0.1f };

        bg->transform_->velocity_.x = -5.0f;

        ++num;
    }



}


void BG::update()
{
    moveBack();
}


// 背景更新処理(private)
static constexpr float subScaleValue = -0.0025f; // scaleの縮小速度
void BG::moveBack() const
{
    for (auto& bg : bg_)
    {
        Transform* t = bg->transform_;
        Collider*  c = bg->collider_;

        if (t->scale_.x <= 0.0f) continue; // scaleが0以下ならcontinue

        // 位置に速度を足す
        t->position_.x += (t->velocity_.x * t->scale_.x); // scaleの大きさでスクロール速度を調整

        // position更新
        if (t->position_.x + (c->size_.x * 0.5f) < 0.0f)
        {
            t->position_.x += (c->size_.x * 2.0f); // 画像サイズ2つ分右に移動
        }

        // scale更新
        if (t->scale_.x > c->targetScale_.x)
        {
            // scale減少
            t->scale_ += (subScaleValue * t->scale_); // scaleの大きさで縮小速度を調整

            if (t->scale_.x < c->targetScale_.x)
            {
                // 目標より小さくなったら修正
                t->scale_ = c->targetScale_;
            }        
        }
    }

}


void BG::drawBack()
{
    // 背景描画する
    for (auto& bg : bg_)
    {
        if (bg->transform_->scale_.x <= 0.0f) continue;
        //if (bg->transform_->scale_.x >= 2.0f) continue;

        GameLib::texture::begin(bg->bg_->bgSprNo_);
        GameLib::texture::draw(
            bg->bg_->bgSprNo_,
            bg->transform_->position_, bg->transform_->scale_,
            { 0,0 }, bg->collider_->size_,
            {bg->collider_->size_.x * 0.5f, bg->collider_->size_.y * 0.5f, }, 
            0,
            bg->renderer_->color_
        );
        GameLib::texture::end(bg->bg_->bgSprNo_);
    }

}

void BG::setBGTargetScale()
{
    for (auto& bg : bg_)
    {
        if (bg->transform_->scale_.x <= 0) continue;

        // scaleの半分を目標値に設定
        bg->collider_->targetScale_ = bg->transform_->scale_ * 0.5f;
    }
}