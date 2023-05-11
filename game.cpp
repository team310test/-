#include "all.h"

Game Game::instance_;

OBJ2D* setGameObj(OBJ2DManager* obj2dManager, Behavior* behavior, VECTOR2 pos)
{
    OBJ2D* obj = new OBJ2D(
        new Renderer,
        new Collider,
        nullptr,
        new ActorComponent,
        nullptr,
        nullptr,
        new PerformComponent
    );

    return obj2dManager->add(obj, behavior, pos);
}

void Game::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ

    obj2dManager_   = new OBJ2DManager;
    bg_             = new BG;
    stage_          = new Stage;

    isPaused_   = false;   // ポーズフラグの初期化

    gameOverState_ = 0;
    isGameOver_ = false;

    //フェード(イン)アウトの初期化
    FADE::clear();
    FADE::getInstance2()->SetColorNum(1);

    Audio::gameInit();
}


void Game::deinit()
{
    // 各マネージャの解放
    safe_delete(stage_);
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    player_ = nullptr;
    playerFrame_ = nullptr;
    playerHeart_ = nullptr;

    // テクスチャの解放
    GameLib::texture::releaseAll();

    // 音楽のクリア
    Audio::clear();
}


void Game::update()
{
    // ソフトリセット
    if ((GameLib::input::STATE(0) & GameLib::input::PAD_SELECT) &&  // 0コンのセレクトボタンが押されている状態で
        (GameLib::input::TRG(0) & GameLib::input::PAD_START))       // 0コンのスタートボタンが押された瞬間
    {
        changeScene(Title::instance());   // タイトルシーンに切り替える
        return;
    }

#ifdef DEBUG_MODE
    // 疑似スローモーション
    static bool isSleep = false;
    if (GetAsyncKeyState('2') < 0) isSleep = (!isSleep) ? true : false;
    if (isSleep) Sleep(60);
#endif

    // ポーズ処理
    //if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
    //    isPaused_ = !isPaused_;       // 0コンのスタートボタンが押されたらポーズ状態が反転
    //if (isPaused_) return;           // この時点でポーズ中ならリターン

    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////
        timer_ = 0;
        BasePlayerBehavior::plShrinkCount_      = 0;
        BasePlayerBehavior::plShrinkCountMax_   = 10;
        Stage::resetShrinkNum();

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        GameLib::texture::load(gameLoadTexture);

        // プレイヤーマネージャの初期化
        obj2dManager()->init();

        // プレイヤーを追加する
        setPlayer(obj2dManager(), bg(),takeOverPos_,takeOverScale_, takeOverIsDrawShrink_, true); // trueならこのobjをplayer_に代入する

        //// カーソル追加(仮)
        //setCursor(obj2dManager(), bg());

        bg()->init(); // BGの初期化

        UI::init();

        // ゲームBGMループ再生
        Audio::play(BGM_GAME, true);

        ++state_;    // 初期化処理の終了
        /*fallthrough*/
    case 1:
        //////// 通常時の処理 ////////

#ifdef DEBUG_MODE
            GameLib::debug::setString("shrinkNum_:%d",stage_->getSrinkNum());               
            GameLib::debug::setString("[1]Key:ShowHitBox");             // 1キーで当たり判定を表示（DEBUG_MODEのみ）
            GameLib::debug::setString("[2]Key:SlowMode");               // 2キーで疑似的なスローモーションにする(少し戻しづらい)（DEBUG_MODEのみ）
            GameLib::debug::setString("[3]Key:AllPlPartsKill");  // 3キーでPLパーツ全破壊（DEBUG_MODEのみ）
#endif

        //if (BasePlayerBehavior::plShrinkCount_ >= BasePlayerBehavior::PL_SHRINK_COUNT_MAX ||
        //    GameLib::input::TRG(0) & GameLib::input::PAD_TRG3)
        if (BasePlayerBehavior::plShrinkCount_ >= BasePlayerBehavior::plShrinkCountMax_)  // プレイヤーの数がShrinkの必要数に達したら
        {
            if (Collider::isAllShrink_ == false &&  // Shrinkが開始されておらず、
                Behavior::isObjShrink() == false)   // すべてのobjが縮小していなければ
            {
                bg()->BG::setBGShrink();            // 背景の縮小設定

                stage_->addSrinkNum();              // shrinkNum加算
                   
                //BasePlayerBehavior::plShrinkCountMax_ += 1; // 縮小するまでのパーツの必要数を増加

                Collider::isAllShrink_ = true;      // Shrinkを開始

                // 縮小SE再生
                Audio::play(SE_SHRINK, false);
            }
        }

        // オブジェクトの更新
        obj2dManager()->update();

        
        if (
            (Behavior::isObjShrink() == false)   // すべてのobjが縮小終了していれば
            && (!isGameOver())                   // ゲームオーバーでなければ  
            )
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
            BG::bgSubScale_                         += (-BG_SHRINK_SPEED) * 0.0225f;
            Behavior::shrinkVelocity_               += (-SHRINK_SPEED)    * 0.015f;
            PlayerPartsBehavior::toCoreVelocity_    += (-TO_CORE_SPEED)   * 0.015f;
            BaseEnemyPartsBehavior::toCoreVelocity_ += (-TO_CORE_SPEED)   * 0.015f;
            UI::letterBox_multiplySizeY_ = std::max(0.75f, UI::letterBox_multiplySizeY_ + LETTER_BOX_SUB_SPEED); // 0.0fより小さければ0.0fに修正
        }
        else // すべてのobjが縮小していなければ
        {
            Behavior::shrinkVelocity_               = SHRINK_SPEED;
            PlayerPartsBehavior::toCoreVelocity_    = TO_CORE_SPEED;
            BaseEnemyPartsBehavior::toCoreVelocity_ = TO_CORE_SPEED;
            UI::letterBox_multiplySizeY_ = std::min(1.0f, UI::letterBox_multiplySizeY_ + LETTER_BOX_ADD_SPEED); // 1.0fより大きければ1.0fに修正

            // 縮小SEフェードアウト
            Audio::fade(SE_SHRINK, 2.0f, 0.0f);
        }

        // 自爆
        if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4)
            player_->actorComponent_->hp_ = 0;


        // ゲームオーバーの処理
        if (isGameOver())
        {
            gameOverProc();
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

    // gameovernの時背景を真っ白に
    FADE::getInstance2()->draw();

    // オブジェクトの描画
    obj2dManager()->draw();

    // ドロップパーツを明滅させる
    drawblink();

    // 縮小カウントメーターの描画(gameoverなら表示しない)
    if(!isGameOver())UI::drawShrinkValueMeter();

    // 映画の黒帯の描画(gameoverなら表示しない)
    if (!isGameOver())UI::drawLetterBox();
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

// 画面中央に移動する
bool MoveToCenter(OBJ2D* obj)
{
    bool contact = objToul::instance().ContactPos(obj, { BG::WINDOW_W_F * 0.5f,BG::WINDOW_H_F * 0.5f },2.0f);
    bool enlarge = objToul::instance().Enlarge(obj, { GAME_OVER_SCALE,GAME_OVER_SCALE },0.04f);

    if (contact && enlarge)return true;

    return false;
}

// 画面外まで落下する
bool objFall(OBJ2D* /*obj*/)
{

    return false;
}

void Game::gameOverProc()
{
    //if (wait(60)) ++gameOverState_;
    switch (gameOverState_)
    {
    case 0:
        //--< 初期設定 >--
        
        // judgeを行わないようにする
        player_->collider_->judgeFlag_ = false;
        // Triggerをtrueに(GameOverのフラグが立つ)
        player_->performComponent_->isTrigger = true;
        // 操作できなくする
        player_->update_ = nullptr;
        player_->transform_->velocity_ = { 0.0f,0.0f };
        // アニメーション終了
        player_->actorComponent_->objAnimeAlways_ = nullptr;

        ++gameOverState_;
        break;
    case 1:
        //--< 爆発エフェクト >--

        if (!player_->actorComponent_->isQuake_) player_->actorComponent_->isQuake_ = true; // 爆破中は振動させる
        if(ChainEffect(player_)) ++gameOverState_;
        break;
    case 2:
        // --< エフェクトの再生終了待ち >--

        if (!objToul::instance().isObjType(obj2dManager(), OBJ_TYPE::EFFECT)) ++gameOverState_;
        break;
    case 3:
        //--< ウェイト >--

        if (wait(10)) ++gameOverState_;
        break;
    case 4:
        //--<player本体以外を削除>--

        for (auto& obj : *obj2dManager_->getList())
        {
            // 自機本体なら飛ばす
            if (obj == player_)continue;

            obj->behavior_ = nullptr;
        }

        // 背景を白にする
        FADE::getInstance2()->SetAlpha(1.0f);
        ++gameOverState_;
        break;
    case 5:
        //--< ウェイト >--

        if (wait(30)) ++gameOverState_;
        break;
    case 6:
        //--<画面中心に移動>--

        if (MoveToCenter(player_)) ++gameOverState_;

        break;
    case 7:
        //--< ウェイト >--

        if (wait(30))++gameOverState_;
        break;
    case 8:
        //--< 自機フレーム・ハートの生成 >--

        playerFrame_ = setGameObj(obj2dManager(), &gamePlayerFrameObjBehavior, player_->transform_->position_);
        playerHeart_ = setGameObj(obj2dManager(), &gamePlayerHheartObjBehavior,
            { player_->transform_->position_.x - 7.0f * GAME_OVER_SCALE,player_->transform_->position_.y + 28.0f * GAME_OVER_SCALE }); 

        ++gameOverState_;
        break;
    case 9:
        //--< ハートの落下後タイトルへ遷移 >--
        if (player_->renderer_->color_.w) player_->renderer_->color_.w = 0.0f;

        if (playerHeart_->performComponent_->isTrigger) changeScene(Title::instance());
        break;
    }
}