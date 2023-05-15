#include "all.h"

bool Collider::isAllShrink_ = false;
int ActorComponent::playerNum = 1;

OBJ2D::OBJ2D(
    Renderer* renderer,
    Collider* collider,
    BG* bg,
    ActorComponent* actorComponent,
    ItemComponent* itemComponent, 
    WeaponComponent* weaponComponent,
    PerformComponent* performComponent,
    EffectComponent* effectComponent
)
    :transform_(new Transform)
    , renderer_(renderer)
    , collider_(collider)
    , bg_(bg)
    , actorComponent_(actorComponent)
    , itemComponent_(itemComponent)
    , weaponComponent_(weaponComponent)
    , performComponent_(performComponent)
    , effectComponent_(effectComponent)
{
    if (transform_)         transform_->setOBJ2D(this);
    if (renderer_)          renderer_->setOBJ2D(this);
    if (collider_)          collider_->setOBJ2D(this);
    if (actorComponent_)    actorComponent_->setOBJ2D(this);
    if (itemComponent_)     itemComponent_->setOBJ2D(this);
    if (weaponComponent_)   weaponComponent_->setOBJ2D(this);
    if (effectComponent_)   effectComponent_->setOBJ2D(this);
    if (performComponent_) performComponent_->setOBJ2D(this);
}


OBJ2D::~OBJ2D()
{
    safe_delete(transform_);
    safe_delete(renderer_);
    safe_delete(collider_);

    safe_delete(actorComponent_);
    safe_delete(itemComponent_);
    safe_delete(weaponComponent_);
    safe_delete(performComponent_);
    safe_delete(effectComponent_);
}

//--------------------------------------------------------------
//  �ړ�
//--------------------------------------------------------------
void OBJ2D::move()
{
    if (behavior_) behavior_->move(this);
    if (eraser_) eraser_->erase(this);
}


void Renderer::draw()
{

    VECTOR2 scale = drawXFlip_
        ? VECTOR2{-obj_->renderer_->drawScale_.x, obj_->renderer_->drawScale_.y} 
        : obj_->renderer_->drawScale_;

    if (data_)
    {
        data_->draw(obj_->transform_->position_,
            scale, obj_->transform_->rotation_, color_);  // data��draw���\�b�h�ŃX�v���C�g��`�悷��
    }
}

//--------------------------------------------------------------
//  �A�j���[�V�����X�V
//--------------------------------------------------------------
//  �߂�l�Ftrue  �A�j�����擪�ɖ߂�u��
//        :false ����ȊO
//--------------------------------------------------------------
bool Renderer::animeUpdate()
{
    if (animeData_ == nullptr)
    {
        assert(!"animeUpdate�֐���AnimeData��nullptr");
        return false;
    }

    if (anime_.pPrev != animeData_)         // �A�j���f�[�^���؂�ւ�����Ƃ�
    {
        anime_.pPrev = animeData_;
        anime_.patNum = 0;	                // �擪����Đ�
        anime_.frame = 0;
    }

    animeData_ += anime_.patNum;
    data_ = animeData_->data;               // ���݂̃p�^�[���ԍ��ɊY������摜��ݒ�

    anime_.frame++;
    if (anime_.frame >= animeData_->frame)  // �ݒ�t���[�����\��������
    {
        anime_.frame = 0;
        anime_.patNum++;                    // ���̃p�^�[����
        if ((animeData_ + 1)->frame < 0)    // �I���R�[�h�̂Ƃ�
        {
            anime_.patNum = 0;              // �擪�֖߂�
            return true;
        }
    }

    return false;
}

//******************************************************************************
//
//
//      OBJ2DManager�N���X
//
//
//******************************************************************************

//--------------------------------------------------------------
//  ������
//--------------------------------------------------------------
void OBJ2DManager::init()
{
    //���X�g��OBJ2D��S�ăN���A����
    objList_.clear();
}

//--------------------------------------------------------------
//  ���X�g�֒ǉ�
//--------------------------------------------------------------
OBJ2D* OBJ2DManager::add(OBJ2D* obj, Behavior* behavior, const VECTOR2& pos)
{
    obj->behavior_ = behavior;           // behavior_�Ɉ�����behavior����
    obj->transform_->position_ = pos;                // position_�Ɉ�����pos����

    objList_.emplace_back(obj);            // ���X�g��obj��ǉ�����
    return obj;       // ���ǉ�����obj�̃A�h���X��Ԃ��i�����Ŏg����悤�Ɂj
}

OBJ2D* OBJ2DManager::insert(std::list<OBJ2D*>::iterator& iter, OBJ2D* obj, Behavior* behavior, const VECTOR2& pos)
{
    obj->behavior_ = behavior;           // behavior_�Ɉ�����behavior����
    obj->transform_->position_ = pos;                // position_�Ɉ�����pos����

    //objList_.emplace_back(obj);            // ���X�g��obj��ǉ�����
    objList_.insert(iter, obj);
    return obj;       // ���ǉ�����obj�̃A�h���X��Ԃ��i�����Ŏg����悤�Ɂj

}

//--------------------------------------------------------------
//  �X�V
//--------------------------------------------------------------
void OBJ2DManager::update()
{
    // �ړ�
    for (auto& obj : objList_)   // objList�̑S�Ă̗v�f�����[�v���Ait�Ƃ������O�Ŋe�v�f�ɃA�N�Z�X
    {
        obj->move();              // it��move���\�b�h���Ă�
    }

    // ��m�[�h�̍폜
    auto iter = objList_.begin();
    while (iter != objList_.end())
    {
        if ((*iter)->behavior_)
        {
            iter++;
        }
        else
        {
            safe_delete(*iter);
            iter = objList_.erase(iter);
        }
    }
}

//--------------------------------------------------------------
//  �`��
//--------------------------------------------------------------
bool predFunc(OBJ2D* obj1, OBJ2D* obj2)
{
    return obj1->zOrder_ < obj2->zOrder_;
}

void OBJ2DManager::draw()
{
    constexpr float LIMIT = 256.0f;

    this->getList()->sort([](OBJ2D* obj1, OBJ2D* obj2)->bool {
        return obj1->zOrder_ < obj2->zOrder_;
        });


    for (auto& obj : objList_)
    {
        const VECTOR2 screenPos = obj->transform_->position_;
        if (screenPos.x < -LIMIT || screenPos.x > GameLib::window::getWidth() + LIMIT ||
            screenPos.y < -LIMIT || screenPos.y > GameLib::window::getHeight() + LIMIT)
        {
            continue;
        }

        // isBlink_��true�Ȃ�}�X�N��K�p
        // �����}�X�N��size��scale��0�������i�}�C�i�X�E���]�j�ƓK�p����Ȃ��Ȃ遦��
        // �iflip()�Ȃǂ̔��]�����ɒ��Ӂj
        if (obj->isBlink_) DepthStencil::instance().set(DepthStencil::MODE::MASK);
        else               DepthStencil::instance().set(DepthStencil::MODE::NONE);

        if (obj->transform_->scale_.x > DRAW_OBJ_SCALE_MIN_LIMIT)
        {
            obj->renderer_->draw();
        }


        DepthStencil::instance().set(DepthStencil::MODE::NONE);

#ifdef DEBUG_MODE
        static bool isDrawHitBox = false; // �q�b�g�{�b�N�X��\�����邩
        // 1�L�[�Ńq�b�g�{�b�N�X�\���E��\��
        if (GetAsyncKeyState('1') & 1)
        {
            isDrawHitBox = (!isDrawHitBox) ? true : false;
        }
        if (isDrawHitBox) obj->collider_->draw();
#endif


    }

}

//--------------------------------------------------------------
//  �f�X�g���N�^
//--------------------------------------------------------------
OBJ2DManager::~OBJ2DManager()
{
    // ���������������
    for (auto& obj : objList_)
    {
        safe_delete(obj);
    }

    // ���X�g��OBJ2D��S�ăN���A����
    objList_.clear();
}

void Collider::draw()
{
    if (isDrawHitRect_)
    {
        for (int i = 0; i < boxMax; ++i)
        {
            VECTOR2 pos = VECTOR2(hitBox_[i].left, hitBox_[i].top);
            VECTOR2 size = { hitBox_[i].right - hitBox_[i].left, hitBox_[i].bottom - hitBox_[i].top };
            VECTOR2 center{ 0, 0 };
            VECTOR4 blue{ 0,0,1,0.5f };
            GameLib::primitive::rect(pos, size, center, 0, blue);
        }
    }

    if (isDrawAttackRect_)
    {
        for (int i = 0; i < boxMax; ++i)
        {
            VECTOR2 pos = VECTOR2(attackBox_[i].left, attackBox_[i].top);
            VECTOR2 size = { attackBox_[i].right - attackBox_[i].left, attackBox_[i].bottom - attackBox_[i].top };
            VECTOR2 center{ 0, 0 };
            VECTOR4 red{ 1,0,0,0.5f };
            GameLib::primitive::rect(pos, size, center, 0, red);
        }
    }
}

void Collider::calcHitBox(const GameLib::fRECT& rc,int i)
{
    hitBox_[i] = {
        //obj_->transform_->position_.x + rc.left, 
        //obj_->transform_->position_.y + rc.top, 
        //obj_->transform_->position_.x + rc.right, 
        //obj_->transform_->position_.y + rc.bottom 
        obj_->transform_->position_.x + (rc.left   * obj_->transform_->scale_.x),
        obj_->transform_->position_.y + (rc.top    * obj_->transform_->scale_.y),
        obj_->transform_->position_.x + (rc.right  * obj_->transform_->scale_.x),
        obj_->transform_->position_.y + (rc.bottom * obj_->transform_->scale_.y),
    };
}

void Collider::calcAttackBox(const GameLib::fRECT& rc, int i)
{
    attackBox_[i] = {
        //obj_->transform_->position_.x + rc.left, 
        //obj_->transform_->position_.y + rc.top, 
        //obj_->transform_->position_.x + rc.right, 
        //obj_->transform_->position_.y + rc.bottom
        obj_->transform_->position_.x + (rc.left   * obj_->transform_->scale_.x),
        obj_->transform_->position_.y + (rc.top    * obj_->transform_->scale_.y),
        obj_->transform_->position_.x + (rc.right  * obj_->transform_->scale_.x),
        obj_->transform_->position_.y + (rc.bottom * obj_->transform_->scale_.y),
    };
}

bool Collider::hitCheck(Collider* other)
{
    for (auto& This : this->attackBox_)
    {
        for (auto& Other : other->hitBox_)
        {
            if (This.right  > Other.left  &&
                This.left   < Other.right &&
                This.bottom > Other.top   &&
                This.top    < Other.bottom) return true;
        }      
    }

    return false;
}

bool Collider::hitCheck(OBJ2D* obj)
{
    return hitCheck(obj->collider_);
}

void ActorComponent::damaged()
{
    // �_���[�W�^�C�}�[��1�ȏ�Ȃ� return
    if (damageTimer_ <= 0) return;

    padTrg_ = 0;
    padState_ = 0;
    --damageTimer_;
}

void ActorComponent::muteki()
{
    if (mutekiTimer_ <= 0) return;

    //VECTOR4 color = obj_->renderer_->color_;
    //color.w = mutekiTimer_ & 0x01 ? 1.0f : 0.0f;
    //obj_->renderer_->color_ = color;

    VECTOR4 color = obj->renderer_->color_;
    color.w = mutekiTimer_ & 0x01 ? 1.0f : 0.0f;
    obj->renderer_->color_ = color;

    --mutekiTimer_;
}

bool ActorComponent::isAliveParent() const
{
    if (parent_ == nullptr) return false;
    return (parent_->actorComponent_->isAlive());
}
