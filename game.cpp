//******************************************************************************
//
//
//      ゲーム
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< 変数 >----------------------------------------------------------------
Game Game::instance_;

//--------------------------------
//  初期化処理
//--------------------------------
void Game::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ

    playerManager_      = new PlayerManager;

    isPaused = false;   // ポーズフラグの初期化
}

//--------------------------------
//  終了処理
//--------------------------------
void Game::deinit()
{
    // 各マネージャの解放
    safe_delete(playerManager_);

    // テクスチャの解放
    texture::releaseAll();

    // 音楽のクリア
    music::clear();
}

//--------------------------------
//  更新処理
//--------------------------------
void Game::update()
{
    using namespace input;

    // ソフトリセット
    if ((STATE(0) & PAD_SELECT) &&  // 0コンのセレクトボタンが押されている状態で
        (TRG(0) & PAD_START))       // 0コンのスタートボタンが押された瞬間
    {
        changeScene(Title::instance());   // タイトルシーンに切り替える
        return;
    }

    // デバッグ文字列表示
    debug::setString("state:%d", state);
    debug::setString("timer:%d", timer);

    // ポーズ処理
    if (TRG(0) & PAD_START)
        isPaused = !isPaused;       // 0コンのスタートボタンが押されたらポーズ状態が反転
    if (isPaused) return;           // この時点でポーズ中ならリターン

    switch (state)
    {
    case 0:
        //////// 初期設定 ////////

        timer = 0;
        GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        texture::load(loadTexture);

        // プレイヤーマネージャの初期化
        playerManager()->init();

        // プレイヤー（自分で操作）を追加する
        playerManager()->add(&player, VECTOR2(window::getWidth() / 2, window::getHeight() / 2));

        state++;    // 初期化処理の終了

        /*fallthrough*/     // case 1:の処理も同時に行う必要があるため、わざとbreak;を記述していない

    case 1:
        //////// 通常時の処理 ////////

        timer++;

        // プレイヤーの更新
        playerManager()->update();

        break;
    }
}

//--------------------------------
//  描画処理
//--------------------------------
void Game::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0, 0, 0, 1));

#if 2
    //******************************************************************************
    // TODO:02 地面の描画
    //------------------------------------------------------------------------------
    /*
    課題）
        地面を描画しなさい

    ヒント）
        0, GROUND_POS_Yから、幅 window::getWidth()、高さ window::getHeight() - GROUND_POS_Yの
        矩形を描画しなさい。色は背景色以外であれば、何色でも良い。
    */
    //******************************************************************************
#endif

    const VECTOR2 pos{ 0,Game::GROUND_POS_Y };
    const VECTOR2 size{ window::getWidth(), window::getHeight() - GROUND_POS_Y };
    const VECTOR2 pivot{ 0.0f,0.0f };
    const VECTOR4 color{ 0.0f, 1.0f, 0.0f, 1.0f };

    //TODO_02 地面の描画
    primitive::rect(pos, size,pivot, 0, color);

    // プレイヤーの描画
    playerManager()->draw();
}

//******************************************************************************
