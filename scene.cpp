#include "all.h"

VECTOR2 Scene::takeOverPos_ = { 200.0f,500.0f };
VECTOR2 Scene::takeOverScale_ = { 1.0f,1.0f };
bool Scene::takeOverIsDrawShrink_ = false;

//--------------------------------------------------------------
//  実行
//--------------------------------------------------------------
Scene* Scene::execute()
{
    using namespace GameLib;

    // 初期化処理
    init();

    // ゲームループ
    while (isGameLoop(false))    // falseをtrueにするとタイトルバーにフレームレート表示
    {
        // 入力処理
        input::update();

        // 更新処理
        update();

        // 音楽更新
        Audio::update();

        // ステンシルモード：通常
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // 描画処理
        draw();

        // ステンシルモード：通常
        DepthStencil::instance().set(DepthStencil::MODE::NONE);

        // デバッグ文字列の描画
        debug::display(1, 1, 1, 1, 1);

        // 画面フリップ
        GameLib::present(1, 0);

        // 終了チェック
        if (nextScene_) break;
    }

    // 終了処理
    deinit();

    return nextScene_;	// 次のシーンを返す
}

//******************************************************************************
//
//      SceneManagerクラス
//
//******************************************************************************

//--------------------------------------------------------------
//  実行
//--------------------------------------------------------------
void SceneManager::execute(Scene* scene)
{
    using namespace GameLib;

    bool isFullScreen = true;	// フルスクリーンにするならtrueに変える
                                //（Releaseモードのみ）

    // ゲームライブラリの初期化処理
    GameLib::init(L"Junk Chunk", BG::WINDOW_W, BG::WINDOW_H, isFullScreen);

#ifndef _DEBUG
    ShowCursor(!isFullScreen);	// フルスクリーン時はカーソルを消す
#endif

    // メインループ
    while (scene)
    {
        scene = scene->execute();
    }

    // ゲームライブラリの終了処理
    GameLib::uninit();
}

//******************************************************************************
