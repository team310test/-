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

    // テクスチャの解放
    GameLib::texture::releaseAll();

    // 音楽のクリア
    GameLib::music::clear();
}

int num = 2;

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

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        GameLib::texture::load(loadTexture);

        // プレイヤーマネージャの初期化
        obj2dManager()->init();

        // プレイヤーを追加する
        setPlayer(obj2dManager(), bg());

        // カーソル追加(仮)
        setCursor(obj2dManager(), bg());

        // エネミーを追加する
        setEnemy(obj2dManager(), bg());

        bg()->init(player_); // BGの初期化

        state_++;    // 初期化処理の終了
        /*fallthrough*/

    case 1:
        //////// 通常時の処理 ////////

        // 敵追加
        if (GameLib::input::STATE(0) & GameLib::input::PAD_START)
        {
            addEnemy(obj2dManager(), bg());
            num++;
        }

        GameLib::debug::setString("num:%d", num);

        
        // オブジェクトの更新
        obj2dManager()->update();

        // ゲームオーバーの処理
        if (isGameOver())
        {
            gameOverProc();
            break;
        }

        bg()->update();   // BGの更新

        judge();

        timer_++;

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
