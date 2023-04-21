#pragma once

//******************************************************************************
//
//
//      OBJ2D�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include <list>
#include "../GameLib/vector.h"
#include "../GameLib/obj2d_data.h"

// �O���錾
class OBJ2D;

enum class OBJ_TYPE
{
    //TYPE_NULL = -1,
    NONE = -1,
    PLAYER = 0, 
    PARTS, //�@�p�[�c
    ENEMY, 
    SHOT, 
    MAX, 
};

//==============================================================================

// �ړ��A���S���Y���N���X�i���ۃN���X�j
class Behavior
{
public:
    virtual void move(OBJ2D*) const = 0;
    virtual OBJ_TYPE getType() const = 0;
    virtual OBJ_TYPE getAttackType() const = 0;

    virtual void hit(OBJ2D* src, OBJ2D* dst) const = 0;

    virtual void startAllShrink(OBJ2D*) const;  // ���ׂĂ�obj��Shrink���J�n������֐�
    virtual void shrink(OBJ2D*) const;          // �k���֐�

    static bool isObjShrink(); // shrink���Ă���obj�����邩���ׂ�֐��ishrink���Ă���obj��������true, ���Ȃ����false�j

};

// �����A���S���Y���N���X�i���ۃN���X�j
class Eraser
{
public:
    virtual void erase(OBJ2D* obj) const = 0;
};

//==============================================================================

//==============================================================================
//
//      OBJ2D�N���X
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
    bool drawXFlip_;
    bool pad_[3];
    Renderer()
        :data_()
        , color_({ 1,1,1,1 })
        , targetColor_({1,1,1,1})
        , anime_()
        , animeData_()
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
    int attackTimer_;
    int damageTimer_;
    int mutekiTimer_;
    int padTrg_;
    int padState_;

    OBJ2D* parent_;
    OBJ2D* obj;

    static int playerNum;
    int No;

    ActorComponent()
        :hp_(1)
        , attackTimer_(0)
        , damageTimer_(0)
        , mutekiTimer_(0)
        , padTrg_(0)
        , padState_(0)

        , obj(nullptr)
        , parent_(nullptr)

        , No(1)
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
    OBJ2D* parent_;  // ���̕���̎�����
public:
    WeaponComponent()
        :parent_(nullptr)
    {
    }
};

class BG;
class OBJ2D
{
public:
    // ��{�I�ȃ����o
    int state_ = 0;
    int act_ = 0;
    int timer_ = 0;
    int zOrder_ = 0;
    Behavior* behavior_     = nullptr;
    Eraser*   eraser_       = nullptr;
    Behavior* nextBehavior_ = nullptr; // ���ɕς��Behavior
    Eraser*   nextEraser_   = nullptr; // ���ɕς��Eraser

    BG* bg_ = nullptr;

    Transform* transform_;
    Renderer* renderer_;
    Collider* collider_;
    ActorComponent* actorComponent_;
    ItemComponent* itemComponent_;
    WeaponComponent* weaponComponent_;

public:
    // �����o�֐�
    OBJ2D(Renderer* renderer,
        Collider* collider,
        BG* bg,
        ActorComponent* actorComponent,
        ItemComponent* itemComponent, 
        WeaponComponent* weaponComponent
    );
    ~OBJ2D();
    void move();    // �ړ�
    void setBG(BG* bg) { bg_ = bg; }
    void remove() { behavior_ = nullptr; }
};

//==============================================================================

// OBJ2DManager�N���X
class OBJ2DManager
{
protected:
    std::list<OBJ2D*> objList_;
public:
    // �f�X�g���N�^
    ~OBJ2DManager();

    void init();    // ������
    void update();  // �X�V
    void draw();    // �`��

    OBJ2D* add(OBJ2D* obj, Behavior* behavior, const VECTOR2& pos);
    OBJ2D* insert(std::list<OBJ2D*>::iterator& iter,OBJ2D* obj, Behavior* behavior, const VECTOR2& pos);
    
    std::list<OBJ2D*>* getList() { return &objList_; }
};

//******************************************************************************
