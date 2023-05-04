#include "all.h"

Game Game::instance_;

void Game::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ

    obj2dManager_   = new OBJ2DManager;
    bg_             = new BG;
    stage_          = new Stage;

    isPaused_ = false;   // ポーズフラグの初期化

    isGameOver_ = false;
}


void Game::deinit()
{
    // 各マネージャの解放
    safe_delete(stage_);
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    player_ = nullptr;

    // テクスチャの解放
    GameLib::texture::releaseAll();

    // 音楽のクリア
    GameLib::music::clear();
}

int num = 2;

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
        BasePlayerBehavior::plShrinkCount_ = 0;
        Stage::resetShrinkNum();

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        GameLib::texture::load(loadTexture);

        // プレイヤーマネージャの初期化
        obj2dManager()->init();

        // プレイヤーを追加する
        setPlayer(obj2dManager(), bg(),takeOverPos_,takeOverScale_, takeOverIsDrawShrink_, true); // trueならこのobjをplayer_に代入する

        //// カーソル追加(仮)
        //setCursor(obj2dManager(), bg());

        bg()->init(); // BGの初期化

        UI::init();

        ++state_;    // 初期化処理の終了
        /*fallthrough*/
    case 1:
        //////// 通常時の処理 ////////

        // 敵追加4
        //if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG2)
        //{
        //    addEnemy(obj2dManager(), bg());
        //    ++num;
        //}

        // debug::setString
        {
            //GameLib::debug::setString("num:%d", num);
            //if (player_->transform_) GameLib::debug::setString("playerScale:%f", player_->transform_->scale_.x);
            GameLib::debug::setString("shrinkNum_:%d",stage_->getSrinkNum());
            //GameLib::debug::setString("plShrinkCount_:%d", BasePlayerBehavior::plShrinkCount_);
        }


        if (BasePlayerBehavior::plShrinkCount_ >= BasePlayerBehavior::PL_SHRINK_COUNT_MAX)  // プレイヤーの数がShrinkの規定数に達したら
        {
            if (Collider::isAllShrink_  == false && // Shrinkが開始されておらず、
                Behavior::isObjShrink() == false)   // すべてのobjが縮小していなければ
            {
                Collider::isAllShrink_ = true;      // Shrinkを開始

                bg()->BG::setBGShrink();       // 背景の縮小設定

                stage_->addSrinkNum();

            }
        }

        // オブジェクトの更新
        obj2dManager()->update();

        
        if (Behavior::isObjShrink() == false) // すべてのobjが縮小終了していれば
        {
            // ステージ更新(エネミー出現)
            stage_->update(obj2dManager_, bg_);
        }


        // オブジェクトの更新後にShrinkの開始を止める
        if (Collider::isAllShrink_)
        {
            Collider::isAllShrink_ = false;
            BasePlayerBehavior::plShrinkCount_ = 0; // プレイヤーのカウントをリセット
        }

        //// 縮小とパーツプレイヤーへ向かう速度いじり
        if (Behavior::isObjShrink()) // ひとつでもobjが縮小していれば
        {
            Behavior::shrinkVelocity_               += (-SHRINK_SPEED)  * 0.015f;
            PlayerPartsBehavior::toCoreVelocity_    += (-TO_CORE_SPEED) * 0.015f;
            BaseEnemyPartsBehavior::toCoreVelocity_ += (-TO_CORE_SPEED) * 0.015f;
            UI::letterBox_multiplySizeY_ = std::max(0.75f, UI::letterBox_multiplySizeY_ + LETTER_BOX_SUB_SPEED); // 0.0fより小さければ0.0fに修正
        }
        else // すべてのobjが縮小していなければ
        {
            Behavior::shrinkVelocity_               = SHRINK_SPEED;
            PlayerPartsBehavior::toCoreVelocity_    = TO_CORE_SPEED;
            BaseEnemyPartsBehavior::toCoreVelocity_ = TO_CORE_SPEED;
            UI::letterBox_multiplySizeY_ = std::min(1.0f, UI::letterBox_multiplySizeY_ + LETTER_BOX_ADD_SPEED); // 1.0fより大きければ1.0fに修正
        }

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


// ドロップパーツを明滅させる関数
void drawblink()
{
    static float blinkColor       = 0.0f;   // 明滅カラー
    static bool  isBlinkColorFlip = false;  // カラーの増減を決める(falseなら加算、trueなら減算)

    blinkColor += (!isBlinkColorFlip) ? ADD_BLINK_COLOR : -ADD_BLINK_COLOR;

    // カラーが規定値を超えたら増減を反転させる
         if (blinkColor >= BLINK_COLOR_MAX) isBlinkColorFlip = true;
    else if (blinkColor <= BLINK_COLOR_MIN) isBlinkColorFlip = false;


    // マスクに描画
    DepthStencil::instance().set(DepthStencil::MODE::APPLY_MASK);
    GameLib::primitive::rect(
        { 0,0 }, { BG::WINDOW_W, BG::WINDOW_H },
        { 0,0 }, 0, { blinkColor,blinkColor,blinkColor,1 }
    );
    // ステンシルリセット
    DepthStencil::instance().clear();
    DepthStencil::instance().set(DepthStencil::MODE::NONE);
}

//--------------------------------------------------------------
//  描画処理
//--------------------------------------------------------------
void Game::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0.75f, 0.45f, 0.3f, 1));
    //GameLib::clear(VECTOR4(1,1,1,1));

    // 背景の描画
    bg()->drawBack();     


    // オブジェクトの描画
    obj2dManager()->draw();

    // ドロップパーツを明滅させる
    drawblink();


    // 縮小カウントメーターの描画
    UI::drawShrinkValueMeter();

    // 映画の黒帯の描画
    UI::drawLetterBox();
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
