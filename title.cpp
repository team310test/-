#include "all.h"

Title Title::instance_;
bool Title::isFallPerform_ = false;

void Title::init()
{
    Scene::init();
    isFallPerform_ = false;

    obj2dManager_ = new OBJ2DManager;
    bg_ = new BG;
}

void Title::deinit()
{
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    // テクスチャの解放
    GameLib::texture::releaseAll();

    // 音楽のクリア
    GameLib::music::clear();
}

void Title::update()
{
    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////

        timer_ = 0;
        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        GameLib::texture::load(loadTexture);
        obj2dManager()->init();

        //setPlayer(obj2dManager(), bg(), true); // trueならこのobjをplayer_に代入する
        setTitlePlayer(obj2dManager(),bg(),true);
        
        bg()->init();

        state_++;                                    // 初期化処理の終了
        /*fallthrough*/                             // 意図的にbreak;を記述していない

    case 1:
        //////// 通常時の処理 ////////

        if (GameLib::input::TRG(0) & GameLib::input::PAD_START)             // PAD_TRG1が押されたら
            changeScene(Game::instance());  // ゲームシーンに切り替え

        // 落下演出をしていなかったら
        if (isFallPerform_);

        obj2dManager()->update();           // オブジェクト更新
        bg()->update();                     // BGの更新

        ++timer_;                           // タイマーを足す
        break;
    }
}

void Title::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0.0f, 1.0f, 0.0f, 1));

    // オブジェクトの描画
    obj2dManager()->draw();
}

void Title::judge()
{
    for (auto& src : *obj2dManager_->getList())
    {
        if (src->behavior_ == nullptr) continue;
        if (src->collider_->judgeFlag_ == false) continue;

        for (auto& dst : *obj2dManager_->getList())
        {
            if (src == dst) continue;
            if (src->behavior_ == nullptr) break;
            if (src->collider_->judgeFlag_ == false) break;
            if (dst->behavior_ == nullptr) continue;
            if (dst->collider_->judgeFlag_ == false) continue;

            // srcの攻撃タイプとdstのタイプが一致しなければcontinue;
            if (src->behavior_->getAttackType() != dst->behavior_->getType())
                continue;

            // あたり判定を行う
            if (src->collider_->hitCheck(dst))
            {
                // あたった場合の処理
                src->behavior_->hit(src, dst);
            }
        }
    }
}