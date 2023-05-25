#pragma once

// 関数ポインタ（アニメ処理）
typedef	void(*SET_ENEMY)(OBJ2DManager* obj2dManager, BG* bg, VECTOR2 pos, OBJ_DATA update);

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


#define X BG::WINDOW_W + 256.0f
#define X2 BG::WINDOW_W + 425.0f    // enemy03の出現するX軸
#define SET_ENEMY_LENE(fream,enemyData,posX,posY,accelX)                                        {(fream),(enemyData),{posX,posY},(ENEMY_LINE),{accelX,0.0f}}
#define SET_ENEMY_TARGET_X(fream,enemyData,posX,posY,accelX,accelY,targetX,NexsPosX,NexsPosY)   {(fream),(enemyData),{posX,posY},(ENEMY_TARGET_X),{accelX,accelY},{targetX,NexsPosX,NexsPosY,0.0f}}
#define SET_ENEMY_END                                                                           {(0), (nullptr), { 0,0 }, nullptr, { 0,0 }}

extern STAGE_SCRIPT stageData01[];
extern STAGE_SCRIPT stageData02[];
extern STAGE_SCRIPT stageData03[];
extern STAGE_SCRIPT stageData04[];
extern STAGE_SCRIPT stageData05[];
extern STAGE_SCRIPT stageData06[];
extern STAGE_SCRIPT stageDataBoss[];
