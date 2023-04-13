//******************************************************************************
//
//
//      ゲーム
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< 変数 >----------------------------------------------------------------
Game Game::instance_;

//--------------------------------------------------------------
//  初期化処理
//--------------------------------------------------------------
void Game::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ

    obj2dManager_   = new OBJ2DManager;
    bg_             = new BG;

    isPaused_ = false;   // ポーズフラグの初期化

    isGameOver_ = false;
}

//--------------------------------------------------------------
//  終了処理
//--------------------------------------------------------------
void Game::deinit()
{
    // 各マネージャの解放
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    player_ = nullptr;

    // テクスチャの解放
    GameLib::texture::releaseAll();

    // 音楽のクリア
    GameLib::music::clear();
}

int num = 2;
int shrinkNum = 0;

//--------------------------------------------------------------
//  更新処理
//--------------------------------------------------------------
void Game::update()
{
    // ソフトリセット
    if ((GameLib::input::STATE(0) & GameLib::input::PAD_SELECT) &&  // 0コンのセレクトボタンが押されている状態で
        (GameLib::input::TRG(0) & GameLib::input::PAD_START))       // 0コンのスタートボタンが押された瞬間
    {
        changeScene(Title::instance());   // タイトルシーンに切り替える
        return;
    }

    // ポーズ処理
    //if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
    //    isPaused_ = !isPaused_;       // 0コンのスタートボタンが押されたらポーズ状態が反転
    //if (isPaused_) return;           // この時点でポーズ中ならリターン

    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////
        timer_ = 0;
        num = 2;
        BasePlayerBehavior::plShrinkCount = 0;

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        GameLib::texture::load(loadTexture);

        // プレイヤーマネージャの初期化
        obj2dManager()->init();

        // プレイヤーを追加する
        setPlayer(obj2dManager(), bg(), true); // trueならこのobjをplayer_に代入する

        // カーソル追加(仮)
        setCursor(obj2dManager(), bg());

        // エネミーを追加する
        setEnemy(obj2dManager(), bg());

        bg()->init(player_); // BGの初期化

        ++state_;    // 初期化処理の終了
        /*fallthrough*/
    case 1:
        //////// 通常時の処理 ////////

        // 敵追加4
        if (GameLib::input::STATE(0) & GameLib::input::PAD_TRG2)
        {
            addEnemy(obj2dManager(), bg());
            ++num;
        }

        GameLib::debug::setString("num:%d", num);
        if (player_->transform_) GameLib::debug::setString("playerScale:%f", player_->transform_->scale_.x);
        GameLib::debug::setString("shrinkNum:%d", shrinkNum);
        GameLib::debug::setString("plShrinkCount:%d", BasePlayerBehavior::plShrinkCount);


        if (BasePlayerBehavior::plShrinkCount >= 10)     // プレイヤーの数がShrinkの規定数に達していて
        {
            if (Collider::isAllShrink_  == false &&       // Shrinkが開始されておらず、
                Behavior::isObjShrink() == false)         // すべてのobjがshrink中でなければ
            {
                Collider::isAllShrink_ = true;           // Shrinkを開始
                BasePlayerBehavior::plShrinkCount -= 10; // プレイヤーのカウントをリセット
                ++shrinkNum;
            }
        }

        // オブジェクトの更新
        obj2dManager()->update();

        // オブジェクトの更新後にShrinkの開始を止める
        if (Collider::isAllShrink_) Collider::isAllShrink_ = false; 


        // ゲームオーバーの処理
        if (isGameOver())
        {
            gameOverProc();
            break;
        }

        bg()->update();   // BGの更新

        judge();

        ++timer_;
        break;
    }
}

//--------------------------------------------------------------
//  描画処理
//--------------------------------------------------------------
void Game::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0.6f, 0.4f, 0.3f, 1));

    bg()->drawBack();     // 背景の描画

    // オブジェクトの描画
    obj2dManager()->draw();
}

void Game::judge()
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

void Game::gameOverProc()
{
    gameOverTimer_--;
    if (gameOverTimer_ <= 0)
    {
        changeScene(Title::instance());
    }
}
//******************************************************************************
