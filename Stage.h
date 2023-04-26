#pragma once

// 関数ポインタ（アニメ処理）
typedef	void(*SET_ENEMY)(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos,OBJ_DATA update);

class STAGE_SCRIPT
{
public:
    int time_;
    EnemyData* enemyData_;
    VECTOR2 pos_;
    OBJ_DATA update_;
    VECTOR2 accel_;
    VECTOR4 addition_;
private:
    EnemyData* begin_;
public:

    STAGE_SCRIPT(int time, EnemyData* enemyData, VECTOR2 pos, OBJ_DATA update, VECTOR2 accel, VECTOR4 addition)
        :time_(time)
        , enemyData_(enemyData)
        , pos_(pos)
        , addition_(addition)
        , update_(update)
        , accel_(accel)
        , begin_(enemyData)
    {}
    STAGE_SCRIPT(int time, EnemyData* enemyData, VECTOR2 pos, OBJ_DATA update, VECTOR2 accel)
        :time_(time)
        , enemyData_(enemyData)
        , pos_(pos)
        , update_(update)
        , accel_(accel)
        , addition_()
        , begin_(enemyData)
    {}

    void DataReset() { enemyData_ = begin_; }
};

#define SET_ENEMY_LENE(fream,enemyData,pos,accelX)              {(fream),(enemyData),{pos},(ENEMY_LINE),{accelX,0.0f}}
#define SET_ENEMY_TARGET_X(fream,enemyData,pos,accel,targetX)   {(fream),(enemyData),{pos},(ENEMY_TARGET_X),{accel},{targetX,0.0f,0.0f,0.0f}}
#define SET_ENEMY_END                     	                    {(0),(nullptr),{0,0},nullptr,{0,0}}

class Stage
{
private:
    int timer;
    STAGE_SCRIPT* pScript;
public:
    Stage();
    void update(OBJ2DManager* obj2dManager, BG* bg);
};