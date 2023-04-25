#pragma once

// 関数ポインタ（アニメ処理）
typedef	void(*SET_ENEMY)(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos,OBJ_DATA update);

class STAGE_SCRIPT
{
public:
    int time_;
    SET_ENEMY setEnemy_;
    VECTOR2 pos_;
    OBJ_DATA update_;

    STAGE_SCRIPT(int time, SET_ENEMY setEnemy, VECTOR2 pos, OBJ_DATA update)
        :time_(time)
        , setEnemy_(setEnemy)
        , pos_(pos)
        , update_(update)
    {}
};

#define SET_ENEMY_DATA(time,enemyData,pos,update)		{(time),(enemyData),(pos),(update)}
#define SET_ENEMY_DATA_END                     	        {(0),(nullptr),{0,0},nullptr}

class Stage
{
private:
    int timer;
    STAGE_SCRIPT* pScript;
public:
    Stage();
    void update(OBJ2DManager* obj2dManager, BG* bg);
};