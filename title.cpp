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


        obj2dManager()->update();           // オブジェクト更新
        bg()->update();                     // BGの更新
        
        // 演出が終わっていなかったらreturn
        if (isStatePerform_ && !statePerform()) return;

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
        static bool isAnime = false;
        // キーを押すとアニメーション再生
        if (GameLib::input::TRG(0) & GameLib::input::PAD_TRG3 && !isAnime) 
            isAnime = true;

        // キーが押されアニメーションが再生終わるとカウントを増やす
        if (isAnime && xAxisSclaeAnime(player_))
        {
            ++pushCount_;
            isAnime = false;
        }

        // 一定回数アニメーションするとゲーム画面に遷移
        if (pushCount_ >= 3)
        {

            bool fadeOut = objFadeOut();    // フェードアウト
            bool shrink = objShrink();      // 縮小

            // 両方の処理が完了したら画面を遷移する
            if (fadeOut && shrink)
            {
                takeOverPos_ = player_->transform_->position_;
                takeOverScale_ = player_->renderer_->drawScale_;
                takeOverIsDrawShrink_ = player_->renderer_->isDrawShrink_;
                changeScene(Game::instance());
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
    if (player_->titleComponent_->isTrigger)
    {
        // フェードインしたらtreuを返す
        if (objFadeIn())
        {
            // playerのupdate変更
            if (player_->update_ != PLAYER_CORE_UPDATE) player_->update_ = PLAYER_CORE_UPDATE;
            isStatePerform_ = false;
            return true;
        }
    }

    return false;
}

bool Title::objFadeOut()
{
    const float fadeSpeed = 0.01f;

    if (endCommand_->renderer_->color_.w >= 0)
    {
        endCommand_->renderer_->color_.w -= fadeSpeed;
        // 超過修正
        if(endCommand_->renderer_->color_.w < 0)
            endCommand_->renderer_->color_.w = 0.0f;
    }
    if (titleLoge_->renderer_->color_.w >= 0)
    {
        titleLoge_->renderer_->color_.w -= fadeSpeed;
        // 超過修正
        if (titleLoge_->renderer_->color_.w < 0)
            titleLoge_->renderer_->color_.w = 0.0f;
    }

    // 全て透明になったらtreuを返す
    if (
        (endCommand_->renderer_->color_.w == 0)
        && (titleLoge_->renderer_->color_.w == 0)
        )
    {
        return true;
    }

    return false;
}

bool Title::objFadeIn()
{
    const float fadeSpeed = 0.01f;

    if (stateCommand_->renderer_->color_.w <= 1.0f)
    {
        stateCommand_->renderer_->color_.w += fadeSpeed;
        // 超過修正
        if (stateCommand_->renderer_->color_.w > 1.0f)
            stateCommand_->renderer_->color_.w = 1.0f;
    }
    if (endCommand_->renderer_->color_.w <= 1.0f)
    {
        endCommand_->renderer_->color_.w += fadeSpeed;
        // 超過修正
        if (endCommand_->renderer_->color_.w > 1.0f)
            endCommand_->renderer_->color_.w = 1.0f;
    }
    if (titleLoge_->renderer_->color_.w <= 1.0f)
    {
        titleLoge_->renderer_->color_.w += fadeSpeed;
        // 超過修正
        if (titleLoge_->renderer_->color_.w > 1.0f)
            titleLoge_->renderer_->color_.w = 1.0f;
    }

    // 全てフェードインしたらtreuを返す
    if (
        (endCommand_->renderer_->color_.w == 1.0f)
        && (titleLoge_->renderer_->color_.w == 1.0f)
        )
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
