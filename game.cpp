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

    gameClearState_ = 0;
    isBossDied_ = false;

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

    boss_ = nullptr;

    // テクスチャの解放
    GameLib::texture::releaseAll();

    // 音楽のクリア
    Audio::clear();
}


void Game::update()
{


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


#ifdef DEBUG_MODE
    GameLib::debug::setString("shrinkNum_:%d", stage_->getSrinkNum());
    GameLib::debug::setString("[1]Key:ShowHitBox");     // 1キーで当たり判定を表示（DEBUG_MODEのみ）
    GameLib::debug::setString("[2]Key:SlowMode");       // 2キーで疑似的なスローモーションにす（(少し戻しづらい)（DEBUG_MODEのみ）
    GameLib::debug::setString("[3]Key:KillPlCore");     // 3キーでプレイヤーコア自爆（DEBUG_MODEのみ）
#endif

    switch (state_)
    {
    case 0:
        //////// 初期設定 ////////
        timer_ = 0;
        BasePlayerBehavior::plShrinkCount_       = 0;
        BasePlayerBehavior::plShrinkCountMax_    = 10;
        BasePlayerBehavior::plPartsCurrentCount_ = 0;
        Stage::resetShrinkNum();

        GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        GameLib::texture::load(gameLoadTexture);

        // プレイヤーマネージャの初期化
        obj2dManager()->init();

        // プレイヤーを追加する
        setPlayer(obj2dManager(), bg(),takeOverPos_, takeOverIsDrawShrink_, true); // trueならこのobjをplayer_に代入する

        //// カーソル追加(仮)
        //setCursor(obj2dManager(), bg());

        bg()->init(); // BGの初期化

        UI::init();

        ++state_;    // 初期化処理の終了
        /*fallthrough*/
    case 1:
        //////// 通常時の処理 ////////
        
        // objが縮小していなくて
        if (!Behavior::isObjShrink() && !isGameOver() && !isGameClear())
        {
            // ソフトリセット
            if ((GameLib::input::STATE(0) & GameLib::input::PAD_SELECT) &&  // 0コンのセレクトボタンが押されている状態で
                (GameLib::input::TRG(0) & GameLib::input::PAD_START))       // 0コンのスタートボタンが押された瞬間
            {
                changeScene(Title::instance());   // タイトルシーンに切り替える
                return;
            }

            // ゲームオーバーでなければステージ更新(エネミー出現)
            stage_->update(obj2dManager_, bg_);
        }

        // 始めの縮小開始
        if (isStartFirstShrink_)
        {
            // オブジェクトの更新
            obj2dManager()->update();

            isStartFirstShrink_ = false; // 一度だけ行うのでこれ以降はfalse

            bg()->BG::setBGShrink();            // 背景の縮小設定
            Collider::isAllShrink_ = true;      // Shrinkを開始

            // 縮小SE再生
            Audio::play(SE_SHRINK, false);

            // ゲームBGMループ再生
            Audio::play(BGM_GAME, true);
            Audio::fade(BGM_GAME, 5.0f, 1.0f);
        }

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

            UI::plPartsCountPos_.y = std::min(0.0f, UI::plPartsCountPos_.y + 5.0f);

            //meterAlphaColor_

            UI::meterPos_.x = std::min(825.0f,  UI::meterPos_.x + 20.0f);
            UI::meterPos_.y = std::max(-450.0f, UI::meterPos_.y - 19.8f);
            // 透かす
            UI::meterAlphaColor_ = std::max(
                0.5f, UI::meterAlphaColor_ += (-0.05f)
            );

            UI::letterBox_multiplySizeY_ = std::max(0.7f, UI::letterBox_multiplySizeY_ + LETTER_BOX_SUB_SPEED); // 0.0fより小さければ0.0fに修正
        }
        else // すべてのobjが縮小していなければ
        {   
            Behavior::shrinkVelocity_               = SHRINK_SPEED;
            PlayerPartsBehavior::toCoreVelocity_    = TO_CORE_SPEED;
            BaseEnemyPartsBehavior::toCoreVelocity_ = TO_CORE_SPEED;

            UI::plPartsCountPos_.y = std::min(0.0f, UI::plPartsCountPos_.y + 5.0f);

            UI::meterPos_.x = std::max(0.0f, UI::meterPos_.x - 50.0f);
            UI::meterPos_.y = std::min(0.0f, UI::meterPos_.y + 28.0f);

            UI::letterBox_multiplySizeY_ = std::min(1.0f, UI::letterBox_multiplySizeY_ + LETTER_BOX_ADD_SPEED); // 1.0fより大きければ1.0fに修正

            // 侵入していたら透かす
            if (UI::isInAreaMeter_)
            {
                UI::meterAlphaColor_ = std::max(
                    UI::UI_ALPHA_COLOR_MIN, UI::meterAlphaColor_ += (-0.05f)
                );
            }
            else // でなければ戻す
            {
                UI::meterAlphaColor_ = std::min(
                    UI::UI_ALPHA_COLOR_MAX, UI::meterAlphaColor_ += 0.05f
                );
            }

            // 縮小SEフェードアウト
            Audio::fade(SE_SHRINK, 0.5f, 0.0f);
        }

#ifdef DEBUG_MODE
        // 3キーでプレイヤーコア自爆
        if (GetAsyncKeyState('3') & 1) player_->actorComponent_->hp_ = 0;
#endif

        bg()->update();   // BGの更新

        UI::update();     // UIの更新

        judge();


        // ゲームオーバーの処理
        if (isGameOver())
        {
            gameOverProc();
            break;
        }

        
        // ゲームクリアの処理
        if (isGameClear())
        {
            gameClearProc();
            break;
        }

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

    // (ゲームオーバー・ゲームクリアならUIを表示しない)
    if (!isGameOver() && !isGameClear())
    {
        // 縮小カウントメーターの描画
        UI::drawShrinkValueMeter();

        // 現在のプレイヤーパーツ数描画
        UI::drawPlPartsCurrentCount();

        // 映画の黒帯の描画
        UI::drawLetterBox();
    }

    // 集めたパーツ・経過時間表示
    if (UI::isSpawnResultJunks_) UI::drawResultJunks();
    if (UI::isSpawnResultTimes_) UI::drawResultTimes();
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
    bool contact = objToul::instance().ContactPos(obj, { BG::WINDOW_W_F * 0.5f, BG::WINDOW_H_F * 0.5f }, 7.0f);
    bool enlarge = objToul::instance().Enlarge(obj, { GAME_OVER_SCALE, GAME_OVER_SCALE }, 0.04f);

    if (contact && enlarge) return true;

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

        // ゲーム・ボス戦BGMフェードアウト
        Audio::fade(BGM_GAME, 2.0f, 0.0f);
        Audio::fade(BGM_BOSS, 2.0f, 0.0f);

        ++gameOverState_;
        break;
    case 1:
        //--< 爆発エフェクト >--

        if (!player_->isQuake_) player_->isQuake_ = true; // 爆破中は振動させる
        if (ChainEffect(player_)) ++gameOverState_;
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
            if (!obj->behavior_) continue;
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
        playerHeart_ = setGameObj(obj2dManager(), &gamePlayerHeartObjBehavior,
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


enum RANK
{
    S, A, B, C,
};

// ランク付けの仕方
// { S+S=S, S+A=A, S+B=A, S+C=B }
// { A+S=A, A+A=A, A+B=B, A+C=B }
// { B+S=A, B+A=B, B+B=B, B+C=C }
// { C+S=B, C+A=B, C+B=C, C+C=C }

// 総合ランクを決める
Behavior* decideRank[][4] = {
    { &gameResult_S, &gameResult_A, &gameResult_A, &gameResult_B },
    { &gameResult_A, &gameResult_A, &gameResult_B, &gameResult_B },
    { &gameResult_A, &gameResult_B, &gameResult_B, &gameResult_C },
    { &gameResult_B, &gameResult_B, &gameResult_C, &gameResult_C },
};
// 一言コメントを決める
Behavior* decideText[][4] = {
    { &gameResult_text_junkie, &gameResult_text_great, &gameResult_text_great, &gameResult_text_nice },
    { &gameResult_text_great,  &gameResult_text_great, &gameResult_text_nice,  &gameResult_text_nice },
    { &gameResult_text_great,  &gameResult_text_nice,  &gameResult_text_nice,  &gameResult_text_soso },
    { &gameResult_text_nice,   &gameResult_text_nice,  &gameResult_text_soso,  &gameResult_text_soso },
};

struct ResultTextData
{
    int       spawnTime; // 生成時間
    Behavior* behavior;  // Behavior
    VECTOR2   pos;       // 生成位置
};


// リザルトテキスト生成
bool spawnResultText(const int& spawnTimer)
{
    // TODO: ランク付けの設定
    
    // パーツのランク付け
    int junkRank  = RANK::S;
    const int partsCount = BasePlayerBehavior::plPartsCurrentCount_;
         if (partsCount >= 50) junkRank = RANK::S; // 50個以上
    else if (partsCount >= 30) junkRank = RANK::A; // 30~49個
    else if (partsCount >= 20) junkRank = RANK::B; // 20~29個
    else                       junkRank = RANK::C; // 20個未満

    // クリア時間のランク付け
    int timesRank = RANK::S;
    const int clearTime = Game::instance()->getTimer();
         if (clearTime <= 60 * 20) timesRank = RANK::S; // 2分以下
    else if (clearTime <= 60 * 40) timesRank = RANK::A; // 2分~4分
    else if (clearTime <= 60 * 60) timesRank = RANK::B; // 4分~6分
    else                           timesRank = RANK::C; // 6分超

    // 総合的なランク付け
    Behavior* gameResultSABC = decideRank[junkRank][timesRank];
    Behavior* gameResultText = decideText[junkRank][timesRank];


    // 順番にテキストを生成
    ResultTextData resultTextData[] = {
        { 60,  &gameResult_junks,   { 390,  400 } }, // JUNK'S
        { 120, &gameResult_times,   { 400,  550 } }, // TIME'S
        { 180, &gameResult_rank,    { 1350, 170 } }, // RANK
        { 210, gameResultSABC,      { 1355, 470 } }, // S・A・B・C
        { 240, gameResultText,      { 1450, 740 } }, // ひと言
        { 300, &gameResult_anyPush, { 575,  800 } }, // ANY PUSH
                                                         
        { 0, nullptr, { 0.0f,0.0f } },
    };
    if (spawnTimer == 90) UI::isSpawnResultJunks_ = true;
    if (spawnTimer == 150) UI::isSpawnResultTimes_ = true;

    static ResultTextData* currentData = nullptr;
    if (!currentData) currentData = resultTextData;


    while (currentData->behavior && currentData->spawnTime == spawnTimer)
    {
        OBJ2D* resultText = setGameObj(
            Game::instance()->obj2dManager(), currentData->behavior, currentData->pos
        );
        resultText->zOrder_  = 100;   // 最前面
        resultText->isQuake_ = true; // 生成時に揺らす
        ++currentData;
    }

    // behaviorがnullptrなら
    if (!currentData->behavior)
    {
        currentData = nullptr;
        return true; // 生成し終わったのでtrue
    }

    return false;
}


void Game::gameClearProc()
{
    if (!boss_) return;

    Transform*      bossT = boss_->transform_;
    ActorComponent* bossA = boss_->actorComponent_;

    static OBJ2D* resultBack = nullptr; // リザルトバック
    static int spawnTimer = 0;

    switch (gameClearState_)
    {
    case 0: // 初期設定
        // judgeを行わないようにする
        player_->collider_->judgeFlag_ = false;

        // 操作できなくする
        boss_->update_ = nullptr;
        bossT->velocity_ = {};
        // アニメーション終了
        bossA->objAnimeAlways_ = nullptr;

        // ゲーム・ボス戦BGMフェードアウト
        Audio::fade(BGM_GAME, 2.0f, 0.0f);
        Audio::fade(BGM_BOSS, 2.0f, 0.0f);

        ++gameClearState_;
        /*fallthrough*/
    case 1: // しばらく爆発
        // 連鎖爆発エフェクト
        if (!boss_->isQuake_) boss_->isQuake_ = true; // 爆破中は振動させる
        ChainEffect(boss_);

        if (wait(120))
        {
            // リザルトバック生成
            resultBack = setGameObj(
                Game::instance()->obj2dManager(), &gameResult_back,
                { BG::WINDOW_W_F * 0.5f, BG::WINDOW_H_F * 0.5f }
            );
            resultBack->zOrder_ = 100;

            ++gameClearState_;
            break;
        }

        break;
    case 2: // リザルト
        // 連鎖爆発エフェクト
        if (!boss_->isQuake_) boss_->isQuake_ = true; // 爆破中は振動させる
        ChainEffect(boss_);

        // リザルトバックのアニメーションが終わってsprDataに切り替わっていなければbreak
        if (!resultBack->renderer_->data_) break;

            // リザルトテキストが生成し終わっていなければbreak
        if (!spawnResultText(spawnTimer))
        {
            ++spawnTimer;
            break;
        }

        spawnTimer = 0;
        ++gameClearState_;
        break;      
    case 3: // ボタンアクション待ち
        // 連鎖爆発エフェクト
        if (!boss_->isQuake_) boss_->isQuake_ = true; // 爆破中は振動させる
        ChainEffect(boss_);

        // 指定のボタンを押したら次に進む
        if ((GameLib::input::TRG(0) & GameLib::input::PAD_TRG1) ||
            (GameLib::input::TRG(0) & GameLib::input::PAD_TRG2) ||
            (GameLib::input::TRG(0) & GameLib::input::PAD_TRG3) ||
            (GameLib::input::TRG(0) & GameLib::input::PAD_TRG4))
        {
            UI::isSpawnResultJunks_ = false;
            UI::isSpawnResultTimes_ = false;

            ++gameClearState_;
            break;
        }

        break;
    case 4: // リザルト画面のバックの不透明度を下げる
        // リザルトバック以外のリザルトUIを消す
        for (auto& obj : *obj2dManager_->getList())
        {
            if (!obj->behavior_) continue;
            if (obj->behavior_->getType() == OBJ_TYPE::PLAYER) continue;
            if (obj->behavior_->getType() == OBJ_TYPE::EFFECT) continue;
            if (obj == boss_)      continue;
            if (obj == resultBack) continue;

            obj->behavior_ = nullptr;
        }

        // 連鎖爆発エフェクト
        if (!boss_->isQuake_) boss_->isQuake_ = true; // 爆破中は振動させる
        ChainEffect(boss_);

        // リザルトバックの不透明度を下げる
        resultBack->renderer_->color_.w = std::max(
            -0.5f, resultBack->renderer_->color_.w - 0.025f
        );

        // リザルトバック不透明度が下がり切ったら
        if (resultBack->renderer_->color_.w == -0.5f)
        {
            ++gameClearState_;
            break;
        }

        break;
    case 5: // エフェクトの再生終了待ち
        if (!objToul::instance().isObjType(obj2dManager(), OBJ_TYPE::EFFECT))
        {
            ++gameClearState_;
            break;
        }

        break;
    case 6: // ウェイト
        if (wait(10))
        {
            ++gameClearState_;
            break;
        }

        break;
    case 7:
        // プレイヤーを透明にする
        player_->renderer_->color_.w = 0.0f;

        // 背景を白にする
        FADE::getInstance2()->SetAlpha(1.0f);

        ++gameClearState_;
        break;
    case 8: // ウェイト
        if (wait(30))
        {
            ++gameClearState_;
            break;
        }

        break;
    case 9: // 画面中心に移動
        if (MoveToCenter(boss_))
        {
            ++gameClearState_;
            break;
        }

        break;
    case 10: // ウェイト
        if (wait(30))
        {
            ++gameClearState_;
            break;
        }

        break;
    case 11: // 自機フレーム・ハートの生成
        playerFrame_ = setGameObj(
            obj2dManager(), &gamePlayerFrameObjBehavior, bossT->position_
        );
        playerFrame_->renderer_->Xflip(); // 反転

        playerHeart_ = setGameObj(
            obj2dManager(), &gamePlayerHeartObjBehavior, 
            { bossT->position_.x + 7.0f  * GAME_OVER_SCALE,
              bossT->position_.y + 28.0f * GAME_OVER_SCALE }
            );           
        playerHeart_->renderer_->Xflip(); // 反転

        ++gameClearState_;
        break;
    case 12: // ハートの落下後タイトルへ遷移
        boss_->renderer_->color_.w = 0.0f;

        if (playerHeart_->performComponent_->isTrigger)
        {
            changeScene(Title::instance());
            return;
        }

        break;
    }
}
