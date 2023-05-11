#pragma once

// OBJ2Dに単純な動きをさせる
class objToul
{
public:
    static objToul& instance() {
        static objToul inst;
        return inst;
    }
    // OBJ2D
    bool FadeOut(OBJ2D*, float = 0.01f);		                    // フェードアウト
    bool FadeIn(OBJ2D*, float = 0.01f);			                    // フェードイン
    bool Shrink(OBJ2D*, VECTOR2 = {1.0f,1.0f}, float = 0.01f); 	    // 縮小
    bool Enlarge(OBJ2D*, VECTOR2 = { 1.0f,1.0f }, float = 0.01f);   // 拡大
    bool ContactPos(OBJ2D*, VECTOR2, float = 1.0f);                 // 指定した座標に移動 
    
    // OBJ2DManager
    bool isObjType(OBJ2DManager* obj2dManager, OBJ_TYPE objType);    // 指定したオブジェクトのタイプが存在していたらtrueを返す
};

// <その他>

// 指定したフレームが経過するとtrueを返す
bool wait(int waitTime);
