//******************************************************************************
//
//
//      プレイヤークラス
//
//
//******************************************************************************

//------< インクルード >--------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//******************************************************************************
//
//      プレイヤー移動処理
//
//******************************************************************************

//------< プレイヤーのアニメデータ >--------------------------------------------
namespace
{   // ※このデータは長いので、Visual Studioの機能で閉じられるようにnamespaceを分けている

    //------< プレイヤーのアニメデータ >------------------------------------------
    //上方向
    AnimeData animePlayer_Up[] = {
        { &sprPlayer_Up0, 10 },
        { &sprPlayer_Up1, 10 },
        { &sprPlayer_Up2, 10 },
        { &sprPlayer_Up1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //右方向
    AnimeData animePlayer_Right[] = {
        { &sprPlayer_Right0, 10 },
        { &sprPlayer_Right1, 10 },
        { &sprPlayer_Right2, 10 },
        { &sprPlayer_Right1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //下方向
    AnimeData animePlayer_Down[] = {
        { &sprPlayer_Down0, 10 },
        { &sprPlayer_Down1, 10 },
        { &sprPlayer_Down2, 10 },
        { &sprPlayer_Down1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
    //左方向
    AnimeData animePlayer_Left[] = {
        { &sprPlayer_Left0, 10 },
        { &sprPlayer_Left1, 10 },
        { &sprPlayer_Left2, 10 },
        { &sprPlayer_Left1, 10 },
        { nullptr, -1 },// 終了フラグ
    };
}

//--------------------------------
//  直接操作
//--------------------------------
void Player::move(OBJ2D *obj)
{
    using namespace input;  // 関数内で入力処理を行うときに記述する

    // 定数（これらはこの関数内でしか使用しないため、ここで定義している）
    const float KASOKU          =  1.0f;    // 横方向・縦方向の加速度
    const float GENSOKU = KASOKU * 0.5f;    // 横方向・縦方向の減速度
    const float SPEED_MAX_X     =  8.0f;    // 横方向の最大速度
    const float SPEED_MAX_Y     =  16.0f;   // 最大の落下速度
    const float SPEED_JUMP_Y    = -12.0f;   // ジャンプ中の上昇スピード

    // 変数
    AnimeData* animeData = nullptr;
    bool onGround = false;          // 地上フラグ

    switch (obj->state)
    {
    case 0:
        //////// 初期設定 ////////

        //アニメの初期設定
        animeData = animePlayer_Down;   // 初期値として下向きのアニメを設定する

        // サイズ設定（足元が中心であるため、幅はあたりとして使用する半分・縦はそのままが扱いやすい）
        obj->size = VECTOR2(96 / 2, 128 - 2);

        obj->state++;

        break;

    case 1:
        //////// 通常時 ////////

        // 毎フレーム毎の初期設定
        onGround = false;   // 地面フラグは毎フレームの最初にfalseにしておき、地面に接していたらtrueを設定する
#if 1
//******************************************************************************
// TODO:01 プレイヤーの移動（Y方向）
//------------------------------------------------------------------------------
/*
課題）
    プレイヤーの縦方向の動作を実装しなさい

仕様）
    位置はobj->positionである
    速度はobj->speedである
    縦方向の加速度は KASOKUである

    落下速度は SPEED_MAX_Y を超えない
    地面の高さは Game::GROUND_POS_Y

ヒント）
    下記の手順で行うとよい（この設問の上下の部分も確認してから取り組むこと）

    □ 速度に加速度を加える
    □ 最大速度チェック
    □ Y方向の位置更新（Y方向の位置にY方向の速度を加える）
    □ Y方向地形あたり判定

解説）
    上の条件とヒントをよく読み理解して、じっくり取り組もう。
    Y方向地形あたり判定については、obj->position.yが Game::GROUND_POS_Y を超えたら
    obj->position.yに Game::GROUND_POS_Y を代入する
*/
//******************************************************************************
#endif
        //速度に加速度を加える
        obj->speed.y += KASOKU;

        //最高速度チェック
        obj->speed.y=(std::min)(obj->speed.y, SPEED_MAX_Y);
        //if (obj->speed.y > SPEED_MAX_Y) {
        //    obj->speed.y = SPEED_MAX_Y;
        //}

        //Y軸方向の位置
        obj->position.y += obj->speed.y;

        //地面との当たり判定
        if (obj->position.y > Game::GROUND_POS_Y) {
            obj->position.y = Game::GROUND_POS_Y;
            onGround = true;
        }

#if 3
//******************************************************************************
// TODO:03 プレイヤーの移動（X方向）
//------------------------------------------------------------------------------
/*
課題）
    プレイヤーの横方向の動作を実装しなさい

仕様）
    左右同時にキーを押しても、どちらにも進まない（入力取り出し部分は既に組んであるので意味を考えなさい）
    キーを押した瞬間に最高速度で動くのではなく、横方向にも加速度が働くように組む
    横方向の加速度はKASOKU
    速度はSPEED_MAX_Xを超えない
    入力がない場合、左右で相殺している場合は速度から加速度の半分を減らし、止まろうとする
    左右のアニメを設定する

ヒント）
    下記の手順で行うとよい（この設問の上下の部分も確認してから取り組むこと）

    □ 左右入力の取り出し
        □ 左だけが押されている場合
            □ 速度に左方向の加速度を加える（加速度を引く）
            □ 左向きのアニメを設定する
        □ 右だけが押されている場合
            □ 速度に右方向の加速度を加える（加速度を足す）
            □ 右向きのアニメを設定する
        □ どちらも押されていないか相殺されている場合
            □ 速度が0より大きい場合
                □ 速度から加速度の半分を引く（止まろうとする）
                □ 速度が負になったら0にする
            □ 速度が0より小さい場合
                □ 速度に加速度の半分を足す（止まろうとする）
                □ 速度が正になったら0にする
    □ 最大速度チェック
    □ 位置更新（位置に速度を加える）

解説）
    左右入力の取り出しのswitch文の変数にSTATE(0) & (PAD_LEFT | PAD_RIGHT)とあるので
    意味をよく考えてみよう。下の2行をコピーして直下に貼り、実行してみなさい

    debug::setString("STATE(0) ALL:%s", strBit16(STATE(0)).c_str());
    debug::setString("STATE(0) LR :%s", strBit16(STATE(0) & (PAD_LEFT | PAD_RIGHT)).c_str());

    STATE(0)が0コンの入力状況を表している。STATE(0)は0コンの状態を返す関数で、戻り値は
    int型、つまり32ビットの変数であるが、16ビットしか使用していない。
    PAD_UPなどは、input_manager.hの先頭で定義してあるが、(1 << 0)から(1 << 15)までの
    16ビット分のみ使用していることがわかる。

    strBit16はuser.hに定義しているインライン関数で、整数を2進数（16bit）のstringへと
    変換する。debug::setStringの引数はconst char*なので、c_str()メソッドでstring型から
    char *に変換している。
*/
//******************************************************************************
#endif
        debug::setString("STATE(0) ALL:%s", strBit16(STATE(0)).c_str());
        debug::setString("STATE(0) LR :%s", strBit16(STATE(0) & (PAD_LEFT | PAD_RIGHT)).c_str());

        //TODO_03 左右入力の取り出し
        switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
        {
        case PAD_LEFT:  // 左だけが押されている場合
            //速度に加速度を加える
            obj->speed.x -= KASOKU;
            //アニメを設定    
            animeData = animePlayer_Left;
            break;
        case PAD_RIGHT: // 右だけが押されている場合
            obj->speed.x += KASOKU;
            animeData = animePlayer_Right;
            break;
        default:        // どちらも押されていないか相殺されている場合
            //X方向の速度が0より大きい場合
            if (obj->speed.x > 0) {
                //X方向の速度から加速度の半分を引く（止まろうとする）
                obj->speed.x -= GENSOKU;
                //0より小さくなったら 
                obj->speed.x = (std::max)(obj->speed.x, 0.0f);
                //0より小さくなったら
                //if (obj->speed.x < 0) {
                //    //速度を0に戻す
                //    obj->speed.x = 0;
                //}
            }
            //X方向の速度が0より小さいとき   
            if (obj->speed.x < 0) {
                //X方向の速度から加速度の半分を引く（止まろうとする）
                obj->speed.x += GENSOKU;
                //0より小さくなったら 
                obj->speed.x = (std::min)(obj->speed.x, 0.0f);
                //0より大きくなったら
                //if (obj->speed.x > 0) {
                //    //速度を0に戻す
                //    obj->speed.x = 0;
                //}
            }


            break;
        }

        //TODO_03 最大速度チェック
        obj->speed.x = clanp(obj->speed.x, SPEED_MAX_X ,-SPEED_MAX_X);
        //if (obj->speed.x > SPEED_MAX_X) {
        //    //超えたら最大値に戻す
        //    obj->speed.x = SPEED_MAX_X;
        //}
        //if (obj->speed.x < -SPEED_MAX_X) {
        //    //超えたら最大値に戻す
        //    obj->speed.x = -SPEED_MAX_X;
        //}

        //TODO_03 X方向移動
        obj->position.x += obj->speed.x;

#if 4
//******************************************************************************
// TODO:04 ジャンプ処理
//------------------------------------------------------------------------------
/*
課題）
    プレイヤーのジャンプ処理を実装しなさい

仕様）
    obj->jumpTimer：ジャンプタイマー（あとどれぐらい上昇し続けられるか、0より大きい数値が入っている時はジャンプ上昇中である）
    onGround      ：地面フラグ（地面の上にいる場合：true、ジャンプ中の場合：false）

    地面にいてPAD_TRG1が押された瞬間、ジャンプタイマーに数値を設定する（20）
    ジャンプ中、PAD_TRG1が押され（続け）ていれば、y方向の速度にSPEED_JUMP_Yを設定し、ジャンプタイマーを減らす
    PAD_TRG1が押されていなければ、ジャンプタイマーを0にする（離したらそれ以上上昇できない）

    ※TODO_01のY方向地形当たりで、地面にめり込んでいて座標を変更した部分でonGroundをtrueにしておくこと（重要）

手順）
    □ プレイヤーが地面にいて、0コンのPAD_TRG1が押された瞬間なら
        □ ジャンプタイマーに数値を設定する（20）
    □ ジャンプタイマーの数値が0より大きければ
        □ 0コンのPAD_TRG1が押されている状態なら
            □ y方向の速度はSPEED_JUMP_Y
            □ ジャンプタイマーを1減らす
        □ そうでないなら
            □ ジャンプタイマーを0にする

ヒント）
    下記をコピーしてソースに貼り、動作を確認すること
    debug::setString("onGround:%d", onGround);
    debug::setString("jumpTimer:%d", obj->jumpTimer);
*/
//******************************************************************************
#endif
        //TODO_04 ジャンプチェック
        
        //デバッグ
        debug::setString("onGround:%d", onGround);
        debug::setString("jumpTimer:%d", obj->jumpTimer);

        //プレイヤーが地上にいてキーが押されたとき
        if (onGround && TRG(0) & PAD_TRG1) {
            obj->jumpTimer = 20;
        }

        //TODO_04 ジャンプ中
         
        //ジャンプタイマーが0以上の時
        if (obj->jumpTimer > 0) {
            //キーが押されていると
            if (STATE(0) & PAD_TRG1) {
                //Y方向の速度をSPEED_JUMP_Yに
                obj->speed.y = SPEED_JUMP_Y;
                //jumpTimerを1減らす
                obj->jumpTimer--;
            }
            //そうでないなら
            else {
                obj->jumpTimer = 0;
            }
        }

#if 5
//******************************************************************************
// TODO:05 エリアチェック（左右方向）
//------------------------------------------------------------------------------
/*
課題）
    プレイヤーが画面から左右にはみ出さないようにしなさい。

ヒント）
    プレイヤーが画面の一番左にいる時の座標は？
    プレイヤーが画面の一番右にいる時の座標は？
    obj->position.xがそれらを超えたら、その値を代入する
    それは壁に当たったということなので、obj->speed.xを0にする

解説）
    プレイヤーが画面の一番左にいる時の座標は、0 + obj->size.x
    プレイヤーが画面の一番右にいる時の座標は、window::getWidth() - obj->size.x
*/
//******************************************************************************
#endif
        //TODO_05 エリアチェック

        const float LEFT_END = window::getWidth() - obj->size.x;
        const float RIGHT_END = 0 + obj->size.x;
        
        //プレイヤーが左端
        if (obj->position.x < RIGHT_END) {
            //0に戻す
            obj->position.x = RIGHT_END;
            //速度も0に戻す
            obj->speed.x = 0;
        }
        //プレイヤーが左端
        if (obj->position.x > LEFT_END) {
            obj->position.x = LEFT_END;
            //速度も0に戻す
            obj->speed.x = 0;
        }

        break;
    }

    // アニメーション更新
    if (animeData)
    {
        // animeDataに値が入っていれば、obj->animeUpdateメソッドを呼ぶ
        obj->animeUpdate(animeData);
    }
}

//--------------------------------
//  消去
//--------------------------------
void ErasePlayer::erase(OBJ2D* obj)
{
    obj->clear();           // OBJ2Dを消去する
}
