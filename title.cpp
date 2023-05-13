#include "all.h"

Title Title::instance_;

OBJ2D* setTitleObj(OBJ2DManager* obj2dManager, Behavior* behavior, VECTOR2 pos)
{
    OBJ2D* obj = new OBJ2D(
        new Renderer,
        new Collider,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        new PerformComponent
    );

    return obj2dManager->add(obj, behavior, pos);
}

void Title::init()
{
    Scene::init();

    obj2dManager_ = new OBJ2DManager;
    bg_ = new BG;

    // 変数の初期化
    isStartPerform_ = true;
    oldTimer_ = 0;
    //pushCount_ = 0;

    isDispTextStart_ = false;
    isDispTextExit_  = false;
    textStartColorAlpha_ = 0.0f;
    textExitColorAlpha_  = 0.0f;

    Game::instance()->isStartFirstShrink_ = false;

    //フェード(イン)アウトの初期化
    FADE::clear();

    // 初期背景を白に
    FADE::getInstance2()->SetColorNum(FADE::COLER::WHITE);
    FADE::getInstance2()->SetAlpha(1.0f);

    Audio::titleInit();
}

void Title::deinit()
{
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    player_         = nullptr;
    startCommand_   = nullptr;
    endCommand_     = nullptr;

    // テクスチャの解放
    GameLib::texture::releaseAll();

    // 音楽のクリア
    Audio::clear();
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
        GameLib::texture::load(titleLoadTexture);
        obj2dManager()->init();

        
        player_         = setTitlePlayer(obj2dManager(),bg());
        startCommand_   = setTitleObj(obj2dManager(), &titleStartObjBehavior, { 500,600 } );
        endCommand_     = setTitleObj(obj2dManager(), &titleEndObjBehavior,   { 1420,600 } );
        titleLogo_      = setTitleObj(obj2dManager(), &titleLogoObjBehavior,  { 960.0f,200.0f } );

        bg()->init();

        ++state_;                                   // 初期化処理の終了
        /*fallthrough*/                             // 意図的にbreak;を記述していない
    case 1:
        //////// 通常時の処理 ////////
        obj2dManager()->update();           // オブジェクト更新
        bg()->update();                     // BGの更新
        
        // 演出が終わっていなかったらreturn
        if (!startPerform()) return;

        userHintMove();

        judge();
        changeSceneGame();                  // 画面遷移(Game)
        endGame();                          // ゲーム終了

        ++timer_;                           // タイマーを足す
        break;
    }
}

void Title::draw()
{
    // 画面クリア
    //GameLib::clear(VECTOR4(1.0f, 1.0f, 1.0f, 1));
    GameLib::clear(VECTOR4(0.75f, 0.45f, 0.3f, 1));

    FADE::getInstance2()->draw();


    static int     texNo  = 0;
    static VECTOR2 pos    = {};
    static VECTOR2 scale  = {};
    static VECTOR2 texPos = {};
    static VECTOR2 size   = {};
    static VECTOR2 center = {};
    static float   angle  = 0.0f;
    static VECTOR4 color  = {};

    static constexpr float ADD_TEXT_COLOR_ALPHA =  0.04f;
    static constexpr float SUB_TEXT_COLOR_ALPHA = -0.075f;

    // Startテキスト描画
    {
        texNo   = TITLE_TEXT_START;
        pos     = { 500, 400 };
        scale   = { 0.75f, 0.75f };
        size    = { 384, 128 };
        center  = size * 0.5f;
        color   = { 1,1,1, textStartColorAlpha_ };

        // 不透明度増減
        if (isDispTextStart_) textStartColorAlpha_ = std::min(1.0f, textStartColorAlpha_ + ADD_TEXT_COLOR_ALPHA);
        else                  textStartColorAlpha_ = std::max(0.0f, textStartColorAlpha_ + SUB_TEXT_COLOR_ALPHA);

        GameLib::texture::begin(texNo);
        GameLib::texture::draw(texNo, pos, scale, texPos, size, center, angle, color);
        GameLib::texture::end(texNo);
    }

    // Exitテキスト描画
    {
        texNo   = TITLE_TEXT_EXIT;
        pos     = { 1420, 400 };
        //scale  = { 1.0f, 1.0f };
        color.w = textExitColorAlpha_;

        // 不透明度増減
        if (isDispTextExit_) textExitColorAlpha_ = std::min(1.0f, textExitColorAlpha_ + ADD_TEXT_COLOR_ALPHA);
        else                 textExitColorAlpha_ = std::max(0.0f, textExitColorAlpha_ + SUB_TEXT_COLOR_ALPHA);

        GameLib::texture::begin(texNo);
        GameLib::texture::draw(texNo, pos, scale, texPos, size, center, angle, color);
        GameLib::texture::end(texNo);
    }

    // オブジェクトの描画
    obj2dManager()->draw();

    //フェード(イン)アウト
    FADE::getInstance()->draw();
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

void Title::changeSceneGame()
{
    if (!startCommand_ || !startCommand_->performComponent_->isTrigger) return;

    // 自機が接触したら

    // 時間経過で射撃ヒント描画
    userHintShot();

    static bool isAnime = false;
    const  int  pushMax = 4;
    static int  shotCoolTimer   = 0;  // 射撃クールタイマー
    const  int  setShotCoolTime = 30; // 射撃クールタイム設定
    static bool  isAutoAddAlpha  = false;
    static float addAlpha        = 1.0f;

    if (pushCount_ >= pushMax - 1)
    {
        // タイトルBGMフェードアウト
        Audio::fade(BGM_TITLE, 2.0f, 0.0f);
    }

    // 一定回数アニメーションするとゲーム画面に遷移
    if (pushCount_ >= pushMax && !isAnime)
    {
        // フェードアウト
        const bool endFadeOut  = objToul::instance().FadeOut(endCommand_, 0.03f);
        const bool logoFadeOut = objToul::instance().FadeOut(titleLogo_,  0.03f);
        //const bool shrink      = objToul::instance().Shrink(player_);      // 縮小
        Game::instance()->isStartFirstShrink_ = true; // 縮小

        //　2回目以降は自動で透明度を設定
        if (isAutoAddAlpha)
        {
            addAlpha -= 0.03f;
            FADE::getInstance2()->SetAlpha(addAlpha);
        }

        // 両方の処理が完了したら画面を遷移する
        if (endFadeOut && logoFadeOut/* && shrink*/)
        {
            isAutoAddAlpha = true;
            addAlpha       = 1.0f;

            // パラメータを引き継ぐ
            takeOverPos_          = player_->transform_->position_;
            takeOverIsDrawShrink_ = player_->renderer_->isDrawShrink_;
            changeScene(Game::instance());
            return;
        }
    }
    else
    {
        // 指定キー(Space,A,B,X,Y)を押すとアニメーション再生
        if ( (GameLib::input::STATE(0) & GameLib::input::PAD_TRG1 ||
              GameLib::input::STATE(0) & GameLib::input::PAD_TRG2 ||
              GameLib::input::STATE(0) & GameLib::input::PAD_TRG3 ||
              GameLib::input::STATE(0) & GameLib::input::PAD_TRG4) &&
              !isAnime && shotCoolTimer <= 0)
        {
            isAnime = true;
            shotCoolTimer = setShotCoolTime; // 射撃クールタイム設定

            // 鼓動エフェクト生成
            AddObj::addEffect(player_, Title::instance()->obj2dManager(), &efcBeatBehavior);

            // 鼓動SE再生
            Audio::play(SE_HEART_BEAT, false);
        }

        // キーが押されアニメーションが再生終わるとカウントを増やす
        if (isAnime && xAxisSclaeAnime(player_))
        {
            ++pushCount_;
            isAnime = false;

            FADE::getInstance2()->SetAlpha(1.0f - 1.0f / pushMax * pushCount_);
        }

        // 射撃クールタイム減少
        shotCoolTimer = (shotCoolTimer > 0) ? --shotCoolTimer : 0;
    }
    
}

// falseを返すbool型(引数bool)関数
bool returnFalse(bool) { return false; }

void Title::endGame()
{
    // 自機が接触したら
    if (endCommand_ && endCommand_->performComponent_->isTrigger)
    {
        // タイトルBGMフェードアウト
        Audio::fade(BGM_TITLE, 2.0f, 0.0f);

        // 画面が暗転したらゲーム終了
        if (FADE::getInstance()->fadeOut(0.025f))
        {
            isGameLoop = returnFalse; // ゲームループ終了
            return;
        }
    }
}

bool Title::startPerform()
{
    // 演出が終わっていたらtrueを返す
    if (!isStartPerform_) return true;

    if (player_->performComponent_->isTrigger)
    {
        const bool state = objToul::instance().FadeIn(startCommand_);
        const bool end = objToul::instance().FadeIn(endCommand_);
        const bool logo = objToul::instance().FadeIn(titleLogo_);

        // フェードインが完了したら
        if (state && end && logo)
        {
            // playerのupdate変更
            if (player_->update_ != PLAYER_CORE_UPDATE) player_->update_ = PLAYER_CORE_UPDATE;
            isStartPerform_ = false;

            // タイトルBGMループ再生
            Audio::play(BGM_TITLE, true);
            
            return true;
        }
    }

    return false;
}

void Title::userHintMove()
{
    // PLが移動したら
    if (isPlayerMove_)
    {
        // userHintMove_がnullpyrならreturn
        if (!userHintMove_) return;

        // userHintMove_がnullptrでないならフェードアウトした後nullptrにする
        if (objToul::instance().FadeOut(userHintMove_, 0.05f))
        {
            userHintMove_->behavior_ = nullptr;
            userHintMove_ = nullptr;
        }
        return;
    }

    // oldTImer_が0ならtimerの値を代入
    if (!oldTimer_) oldTimer_ = timer_;

    // PLの移動入力チェック
    if ((GameLib::input::STATE(0) & (GameLib::input::PAD_UP | GameLib::input::PAD_DOWN | GameLib::input::PAD_LEFT | GameLib::input::PAD_RIGHT)) ||
         GameLib::input::getPadState(0)->leftX != 0.0f || GameLib::input::getPadState(0)->leftY != 0.0f)
    {
        isPlayerMove_ = true;
        oldTimer_ = 0;
        return;
    }

    // 一定時間立つとヒントを描画
    if (timer_ - oldTimer_ >= 60)
    {
        if (!userHintMove_)
        {
            VECTOR2 pos = player_->transform_->position_;
            pos += {0.0f, -100.0f};
            userHintMove_ = setTitleObj(obj2dManager(), &titleHintMoveObjBehavior, pos);
        }
        objToul::instance().FadeIn(userHintMove_, 0.025f);
    }
}

void Title::userHintShot()
{
    // PLが攻撃したら
    if (isPlayerShot_)
    {
        // userHintMove_がnullpyrならreturn
        if (!userHintShot_) return;

        // userHintMove_がnullptrでないならフェードアウトした後nullptrにする
        if (objToul::instance().FadeOut(userHintShot_, 0.05f))
        {
            userHintShot_->behavior_ = nullptr;
            userHintShot_ = nullptr;
        }
        return;
    }

    // oldTImer_が0ならtimerの値を代入
    if (!oldTimer_) oldTimer_ = timer_;

    // PLの攻撃入力チェック
    if ((GameLib::input::TRG(0) & GameLib::input::PAD_TRG1 ||
         GameLib::input::TRG(0) & GameLib::input::PAD_TRG2 ||
         GameLib::input::TRG(0) & GameLib::input::PAD_TRG3 ||
         GameLib::input::TRG(0) & GameLib::input::PAD_TRG4) )
    {
        isPlayerShot_ = true;
        oldTimer_ = 0;
        return;
    }

    // 一定時間立つとヒントを描画
    if (timer_ - oldTimer_ > 60)
    {
        if (!userHintShot_)
        {
            VECTOR2 pos = player_->transform_->position_;
            pos += {0.0f, -200.0f};
            userHintShot_ = setTitleObj(obj2dManager(), &titleHintShotObjBehavior, pos);
        }
        objToul::instance().FadeIn(userHintShot_, 0.025f);
    }
}