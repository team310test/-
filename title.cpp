#include "all.h"

Title Title::instance_;

OBJ2D* setTitleObj(OBJ2DManager* obj2dManager, Behavior* behavior,VECTOR2 pos)
{
    OBJ2D* obj = new OBJ2D(
        new Renderer,
        new Collider,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        new TitleComponent
    );

    return obj2dManager->add(obj, behavior, pos);
}

void Title::init()
{
    Scene::init();

    obj2dManager_ = new OBJ2DManager;
    bg_ = new BG;

    // 変数の初期化
    isStatePerform_ = true;
    oldTImer_ = 0;
    pushCount_ = 0;

    // //フェード(イン)アウトの初期化
    FADE::clear();
}

void Title::deinit()
{
    safe_delete(bg_);
    safe_delete(obj2dManager_);

    player_ = nullptr;
    stateCommand_ = nullptr;
    endCommand_ = nullptr;

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

        
        player_ = setTitlePlayer(obj2dManager(),bg());
        stateCommand_ = setTitleObj(obj2dManager(), &titleStateObjBehavior, { 500,500 });
        endCommand_ = setTitleObj(obj2dManager(), &titleEndObjBehavior, { 1420,500 });
        titleLoge_ = setTitleObj(obj2dManager(), &titleLogoObjBehavior, { 960.0f,200.0f });

        bg()->init();

        state_++;                                    // 初期化処理の終了
        /*fallthrough*/                             // 意図的にbreak;を記述していない

    case 1:
        //////// 通常時の処理 ////////
        GameLib::debug::setString("time:%d", timer_);

        obj2dManager()->update();           // オブジェクト更新
        bg()->update();                     // BGの更新
        
        // 演出が終わっていなかったらreturn
        if (!statePerform()) return;

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
    GameLib::clear(VECTOR4(0.75f, 0.45f, 0.3f, 1));

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
    // 自機が接触したら
    if (stateCommand_ && stateCommand_->titleComponent_->isTrigger)
    {
        // 時間経過でヒント描画
        userHintShot();

        static bool isAnime = false;
        
        // 一定回数アニメーションするとゲーム画面に遷移
        if (pushCount_ >= 3)
        {
            const float fadeSpeed = 0.01f;

            // フェードアウト
            const bool endFadeOut = objFadeOut(endCommand_, fadeSpeed);    
            const bool logoFadeOut = objFadeOut(titleLoge_, fadeSpeed);


            const bool shrink = objShrink();      // 縮小

            // 両方の処理が完了したら画面を遷移する
            if (endFadeOut && logoFadeOut && shrink)
            {
                takeOverPos_ = player_->transform_->position_;
                takeOverScale_ = player_->renderer_->drawScale_;
                takeOverIsDrawShrink_ = player_->renderer_->isDrawShrink_;
                changeScene(Game::instance());
            }
        }
        else
        {
            // キーを押すとアニメーション再生
            if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG3 && !isAnime)
                isAnime = true;

            // キーが押されアニメーションが再生終わるとカウントを増やす
            if (isAnime && xAxisSclaeAnime(player_))
            {
                ++pushCount_;
                isAnime = false;
            }
        }
    }
}

void Title::endGame()
{
    // 自機が接触したら
    if (endCommand_ && endCommand_->titleComponent_->isTrigger)
    {
        // 画面が暗転したらゲーム終了
        if (FADE::getInstance()->fadeOut(0.01f))
        {
            exit(0);
        }
    }
}

bool Title::statePerform()
{
    // 演出が終わっていたらtrueを返す
    if (!isStatePerform_) return true;

    if (player_->titleComponent_->isTrigger)
    {
        const float fadeSpeed = 0.01f;

        const bool state = objFadeIn(stateCommand_, fadeSpeed);
        const bool end = objFadeIn(endCommand_, fadeSpeed);
        const bool logo = objFadeIn(titleLoge_, fadeSpeed);

        // フェードインが完了したら
        if (state && end && logo)
        {
            // playerのupdate変更
            if (player_->update_ != PLAYER_CORE_UPDATE) player_->update_ = PLAYER_CORE_UPDATE;
            isStatePerform_ = false;
            return true;
        }
    }

    return false;
}

bool Title::objFadeOut(OBJ2D* obj, float fadeSpeed)
{
    //const float fadeSpeed = 0.01f;

    // 透明度0未満の場合
    if (obj->renderer_->color_.w < 0.0f)
    {
        obj->renderer_->color_.w = 0.0f;
        return true;
    }

    // 透明度0.0を超えているなら減少
    if (obj->renderer_->color_.w >= 0)
    {
        obj->renderer_->color_.w -= fadeSpeed;
        // 超過修正
        if(obj->renderer_->color_.w < 0)
            obj->renderer_->color_.w = 0.0f;
    }

    // 全て透明になったらtreuを返す
    if (obj->renderer_->color_.w == 0)
    {
        return true;
    }

    return false;
}

bool Title::objFadeIn(OBJ2D* obj, float fadeSpeed)
{
    // 透明度1.0を超えていた場合
    if (obj->renderer_->color_.w > 1.0f)
    {
        obj->renderer_->color_.w = 1.0f;
        return true;
    }

    // 透明度1.0未満なら増加
    if (obj->renderer_->color_.w <= 1.0f)
    {
        obj->renderer_->color_.w += fadeSpeed;
        // 超過修正
        if (obj->renderer_->color_.w > 1.0f)
            obj->renderer_->color_.w = 1.0f;
    }

    // 透明度1.0になったらtrueを返す
    if (obj->renderer_->color_.w == 1.0f)
    {
        return true;
    }

    return false;
}

bool Title::objShrink()
{
    const float fadeSpeed = 0.01f;

    // Y軸
    if (player_->renderer_->drawScale_.y >= 1.0f)
    {
        player_->renderer_->drawScale_.y -= fadeSpeed;
        // 超過修正
        if (player_->renderer_->drawScale_.y < 1.0f)
            player_->renderer_->drawScale_.y = 1.0f;
    }

    // X軸
    if (player_->renderer_->drawScale_.x >= 1.0f)
    {
        player_->renderer_->drawScale_.x -= fadeSpeed;
        // 超過修正
        if (player_->renderer_->drawScale_.x < 1.0f)
            player_->renderer_->drawScale_.x = 1.0f;
    }

    // 両方ともscaleが1.0fになったらtrueえお返す
    if (
        (player_->renderer_->drawScale_.y == 1.0f)
        && (player_->renderer_->drawScale_.x == 1.0f)
        )
    {
        return true;
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
        if (objFadeOut(userHintMove_, 0.05f))
        {
            userHintMove_->behavior_ = nullptr;
            userHintMove_ = nullptr;
        }
        return;
    }

    // oldTImer_が0ならtimerの値を代入
    if (!oldTImer_) oldTImer_ = timer_;

    // PLの移動入力チェック
    if (GameLib::input::TRG(0) & (GameLib::input::PAD_UP | GameLib::input::PAD_DOWN | GameLib::input::PAD_LEFT | GameLib::input::PAD_RIGHT))
    {
        isPlayerMove_ = true;
        oldTImer_ = 0;
        return;
    }

    // 一定時間立つとヒントを描画
    if (timer_ - oldTImer_ > 200)
    {
        if (!userHintMove_)
        {
            VECTOR2 pos = player_->transform_->position_;
            pos += {0.0f, -100.0f};
            userHintMove_ = setTitleObj(obj2dManager(), &titleHintMoveObjBehavior, pos);
        }
        objFadeIn(userHintMove_, 0.01f);
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
        if (objFadeOut(userHintShot_, 0.05f))
        {
            userHintShot_->behavior_ = nullptr;
            userHintShot_ = nullptr;
        }
        return;
    }

    // oldTImer_が0ならtimerの値を代入
    if (!oldTImer_) oldTImer_ = timer_;

    // PLの攻撃入力チェック
    if (GameLib::input::TRG(0) & (GameLib::input::PAD_TRG3))
    {
        isPlayerShot_ = true;
        oldTImer_ = 0;
        return;
    }

    // 一定時間立つとヒントを描画
    if (timer_ - oldTImer_ > 200)
    {
        if (!userHintShot_)
        {
            VECTOR2 pos = player_->transform_->position_;
            pos += {0.0f, -200.0f};
            userHintShot_ = setTitleObj(obj2dManager(), &titleHintShotObjBehavior, pos);
        }
        objFadeIn(userHintShot_, 0.01f);
    }
}