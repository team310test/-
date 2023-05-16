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
    bool FadeIn(OBJ2D*,  const float& fadeInSpeed  =  0.01f);			            // フェードイン
    bool FadeOut(OBJ2D*, const float& fadeOutSpeed = -0.01f);		                // フェードアウト
    //bool Shrink(OBJ2D*, const VECTOR2& = { 1.0f,1.0f }, const float& = 0.01f);    // 縮小
    bool Enlarge(OBJ2D* obj, const VECTOR2& targetScale = { 1.0f,1.0f }, const float& speed = 0.01f);     // 拡大
    bool ContactPos(OBJ2D*, const VECTOR2& targetPos, const float& constactSpeed = 1.0f);   // 指定した座標に移動 
    
    // OBJ2DManager
    bool isObjType(OBJ2DManager* obj2dManager, const OBJ_TYPE& objType);    // 指定したオブジェクトのタイプが存在していたらtrueを返す
};

// <その他>

// 指定したフレームが経過するとtrueを返す
bool wait(const int& waitTime);
