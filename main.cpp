#include "all.h"


//--------------------------------------------------------------
//  WinMain（エントリポイント）
//--------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
    srand(static_cast<unsigned int>(time(0)));

    SceneManager sceneManager;
    sceneManager.execute(Title::instance());

    return 0;
}

//******************************************************************************
