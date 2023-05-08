#pragma once

class EnemyData
{
public:
    Behavior* behavior_;
    VECTOR2 pos_;
    int zOrder_;
    int no_;
    int parentNo_;

    EnemyData(Behavior* behavior, VECTOR2 pos, int zOrder, int no, int parentNo)
        :behavior_(behavior)
        , pos_(pos) 
        , zOrder_(zOrder)
        , no_(no)
        , parentNo_(parentNo)
    {}
};

OBJ2D* setEnemy(
    OBJ2DManager* obj2dManager,
    BG* bg,
    VECTOR2 pos,
    Behavior* behavior,
    OBJ_DATA update,
    OBJ2D* parent,
    OBJ2D* orgParent,
    int zOrder,
    VECTOR4 addition = { 0,0,0,0 }
);

enum PARENT_NO
{
    NOT = -1,
    PARENT0 = 0,
    PARENT1,
    PARENT2,
    PARENT3,
    PARENT4,
    PARENT5,
    PARENT6,
    PARENT7,
    PARENT8,
    PARENT9,
};

#define CORE(behavior,zOrder,no)    {behavior,{0,0},zOrder,no,0}
#define PARTS(behavior,pos,zOrder)  {behavior,pos,zOrder}
#define END                         {nullptr,{0,0},0,0,0}

// エネミー01
extern EnemyData enemy01[];
// エネミー02
extern EnemyData enemy02[];
// エネミー03
extern EnemyData enemy03[];
// エネミー04
extern EnemyData enemy04[];
// エネミー05
extern EnemyData enemy05[];
// エネミー06
extern EnemyData enemy06[];