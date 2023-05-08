#include "all.h"

OBJ2D* setEnemy
(
    OBJ2DManager* obj2dManager
    , BG* bg
    , VECTOR2 pos
    , Behavior* behavior
    , OBJ_DATA update
    , OBJ2D* parent
    , OBJ2D* orgParent
    , int zOrder
    , VECTOR4 addition
)
{
    OBJ2D* enemy = new OBJ2D(
        new Renderer,
        new Collider,
        bg,
        new ActorComponent,
        nullptr,
        nullptr,
        nullptr
    );

    enemy->zOrder_ = zOrder;
    if (!orgParent) // �R�A�̏ꍇ
    {
        enemy->update_ = update;
        enemy->actorComponent_->parent_ = enemy;
        enemy->actorComponent_->orgParent_ = enemy;
    }
    else // �R�A�ȊO�̏ꍇ
    {
        enemy->update_ = ENEMY_PARTS;
        enemy->actorComponent_->parent_ = parent;
        enemy->actorComponent_->orgParent_ = orgParent;
    }
    return obj2dManager->add(enemy, behavior, pos);
}


// �G�l�~�[01
EnemyData enemy01[] =
{
    CORE(&enemyCore01Behavior,3,PARENT_NO::PARENT0)
    ,{&enemyTurret01Behavior,{-64,96},3,PARENT_NO::NOT,PARENT_NO::PARENT0}
    ,END
};
// �G�l�~�[02
EnemyData enemy02[] =
{
    CORE(&enemyCore01Behavior,3,PARENT_NO::PARENT0)
    ,{&enemyTurret01Behavior,{0,-256},3,PARENT_NO::PARENT1,PARENT_NO::PARENT0}
    ,{&enemyTurret01Behavior,{0,-512},3,PARENT_NO::NOT,PARENT_NO::PARENT1}
    ,END
};