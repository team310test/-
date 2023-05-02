#pragma once

#include <list>
#include "../GameLib/vector.h"
#include "../GameLib/obj2d_data.h"

// 前方宣言
class OBJ2D;

// 関数ポインタ（アニメ処理）
typedef	void(*OBJ_DATA)(OBJ2D* obj);
typedef	bool(*OBJ_DATA_b)(OBJ2D* obj);


enum class OBJ_TYPE
{
    //TYPE_NULL = -1,
    NONE = -1,
    PLAYER = 0, 
    PARTS, //　パーツ
    ENEMY, 
    SHOT, 
    CURSOR, 
    EFFECT,
    MAX,
};


// 移動アルゴリズムクラス（抽象クラス）
class Behavior
{
public:
    virtual void move(OBJ2D*) const  = 0;
    virtual OBJ_TYPE getType() const = 0;
    virtual OBJ_TYPE getAttackType() const = 0;

    virtual void hit(OBJ2D* /*src*/, OBJ2D* /*dst*/) const {};

    virtual void startAllShrink(OBJ2D*) const;  // すべてのobjのShrinkを開始させる関数
    virtual void shrink(OBJ2D*) const;          // 縮小関数

    static bool isObjShrink(); // shrinkしているobjがいるか調べる関数（shrinkしているobjがいたらtrue, いなければfalse）

    OBJ_DATA update = nullptr;

public:
    static constexpr float SHRINK_DIVIDE_VALUE  = 0.5f;     // scaleを割る値(最終的なscaleの大きさに影響)

public:
    static float shrinkVelocity_; // 縮小する速度
};

// 消去アルゴリズムクラス（抽象クラス）
class Eraser
{
public:
    virtual void erase(OBJ2D* obj) const = 0;
};

//==============================================================================

//==============================================================================
//
//      OBJ2Dクラス
//
//==============================================================================

//----------------------------------------------------------------------
//  Component
//----------------------------------------------------------------------
class Component
{
protected:
    OBJ2D* obj_;

public:
    Component()
        :obj_()
    {
    }
    virtual void draw() {}
    void setOBJ2D(OBJ2D* obj) { obj_ = obj; }
};

//----------------------------------------------------------------------
//  Transform
//----------------------------------------------------------------------
class Transform : public Component
{
public:
    VECTOR2 position_;
    VECTOR2 orgPosition_;
    VECTOR2 scale_;
    float rotation_;
    VECTOR2 velocity_;

    Transform()
        : position_()
        , orgPosition_()
        , scale_(1, 1)
        , rotation_()
        , velocity_()
    {
    }
};

//----------------------------------------------------------------------
//  Renderer
//----------------------------------------------------------------------
class Renderer : public Component
{
public:
    GameLib::SpriteData* data_;
    VECTOR4 color_;
    VECTOR4 targetColor_;
    GameLib::Anime anime_;
    GameLib::AnimeData* animeData_;
    VECTOR2 drawScale_;
    bool drawXFlip_;
    bool isDrawShrink_;
    bool pad_[2];
    Renderer()
        :data_()
        , color_({ 1,1,1,1 })
        , targetColor_({1,1,1,1})
        , anime_()
        , animeData_()
        , drawScale_({1,1})
        , isDrawShrink_()
        , drawXFlip_()
        , pad_()
    {
    }
    void flip() { drawXFlip_ = !drawXFlip_; }
    void draw() override;
    bool animeUpdate();
};

//----------------------------------------------------------------------
//  Collider
//----------------------------------------------------------------------
class Collider : public Component
{
public:
    static int const boxMax = 2;

    VECTOR2 size_;
    GameLib::fRECT hitBox_[boxMax];
    GameLib::fRECT attackBox_[boxMax];
    bool judgeFlag_;
    bool isDrawHitRect_;
    bool isDrawAttackRect_;

    bool isShrink_;
    static bool isAllShrink_;
    VECTOR2 targetScale_;

    Collider()
        :size_()
        , judgeFlag_()
        , isDrawHitRect_()
        , isDrawAttackRect_()
        , hitBox_()
        , attackBox_()

        , isShrink_()
        , targetScale_()
    {
    }
    void draw() override;
    void calcHitBox(const GameLib::fRECT& rc , int i);
    void calcAttackBox(const GameLib::fRECT& rc , int i);

    bool hitCheck(Collider* other);
    bool hitCheck(OBJ2D* obj);
};

//----------------------------------------------------------------------
//  ActorComponent
//----------------------------------------------------------------------
class ActorComponent : public Component
{
public:
    int hp_;
    int nextHp_;
    int attackTimer_;
    int damageTimer_;
    int mutekiTimer_;
    int padTrg_;
    int padState_;

    OBJ2D* parent_;
    OBJ2D* orgParent_;
    OBJ2D* obj;

    static int playerNum;
    int No;

    // 速度関連パラメータ
    VECTOR2 accel_;
    VECTOR4 addition_;

    // アニメ用データ
    OBJ_DATA objAnimeAlways_;
    OBJ_DATA_b objAnimeTemporary_;
    float rotSpeed_;

    ActorComponent()
        :hp_(1)
        , nextHp_(0)
        , attackTimer_(0)
        , damageTimer_(0)
        , mutekiTimer_(0)
        , padTrg_(0)
        , padState_(0)

        , parent_(nullptr)
        , orgParent_(nullptr)
        , obj(nullptr)

        , No(1)

        // 速度関連パラメータ
        , accel_()
        , addition_()

        // アニメ用データ
        , objAnimeAlways_(nullptr)
        , objAnimeTemporary_(nullptr)
        , rotSpeed_(0)
    {
    }
    bool isAlive() const { return hp_ > 0; }
    void damaged();
    void muteki();
    bool isAliveParent()const;
};

//----------------------------------------------------------------------
//  ItemComponent
//----------------------------------------------------------------------
class ItemComponent : public Component
{
public:
    VECTOR2 origin_;
    float angle_;

    ItemComponent()
        :origin_()
        , angle_()
    {
    }
};

//----------------------------------------------------------------------
//  WeaponComponent
//----------------------------------------------------------------------
class WeaponComponent : public Component
{
public:
    OBJ2D* parent_;  // この武器の持ち主
public:
    WeaponComponent()
        :parent_(nullptr)
    {
    }
};

//----------------------------------------------------------------------
//  TitleComponent
//----------------------------------------------------------------------
class TitleComponent : public Component
{
public:
    OBJ2D* parent_;  // この武器の持ち主
    bool isTrigger;
    bool isDraw;
public:
    TitleComponent()
        :parent_(nullptr)
        , isDraw(false)
        , isTrigger(false)
    {}
};


class EffectComponent : public Component
{
public:
    float animeX_;
    int   animeTimer_;

public:
    EffectComponent()
        :animeX_(0.0f)
        , animeTimer_(0)
    {
    }

};

class BG;
class OBJ2D
{
public:
    // 基本的なメンバ
    int state_ = 0;
    int act_ = 0;
    int timer_ = 0;
    int zOrder_ = 0;
    Behavior* behavior_     = nullptr;
    Eraser*   eraser_       = nullptr;
    Behavior* nextBehavior_ = nullptr; // 次に変わるBehavior
    Eraser*   nextEraser_   = nullptr; // 次に変わるEraser
    OBJ_DATA  update_       = nullptr;

    int bgSprNo_ = 0; // 背景スプライト画像TEXNO

    BG* bg_ = nullptr;

    Transform* transform_;
    Renderer* renderer_;
    Collider* collider_;
    ActorComponent* actorComponent_;
    ItemComponent* itemComponent_;
    WeaponComponent* weaponComponent_;
    TitleComponent* titleComponent_;
    EffectComponent* effectComponent_;

public:
    // メンバ関数
    OBJ2D(Renderer* renderer,
        Collider* collider,
        BG* bg,
        ActorComponent* actorComponent,
        ItemComponent* itemComponent, 
        WeaponComponent* weaponComponent,
        TitleComponent* titleComponent = nullptr,
        EffectComponent* effectComponent = nullptr  // 引数を書く手間を省く
    );
    ~OBJ2D();
    void move();    // 移動
    void setBG(BG* bg) { bg_ = bg; }
    void remove() { behavior_ = nullptr; }
};

//==============================================================================

// OBJ2DManagerクラス
class OBJ2DManager
{
protected:
    std::list<OBJ2D*> objList_;
public:
    // デストラクタ
    ~OBJ2DManager();

    void init();    // 初期化
    void update();  // 更新
    void draw();    // 描画

    OBJ2D* add(OBJ2D* obj, Behavior* behavior, const VECTOR2& pos);
    OBJ2D* insert(std::list<OBJ2D*>::iterator& iter,OBJ2D* obj, Behavior* behavior, const VECTOR2& pos);
    
    std::list<OBJ2D*>* getList() { return &objList_; }
};

//******************************************************************************
