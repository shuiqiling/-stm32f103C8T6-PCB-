#ifndef __APP_Obstacle_Avoidance_H
#define __APP_Obstacle_Avoidance_H


void APP_Obstacle_Avoidance_Init(void);

void APP_Obstacle_Avoidance_StraightMode(uint8_t AvoidanceTimeOut);

uint16_t APP_Obstacle_Avoidance_Warning(void);
void APP_Obstacle_Avoidance_ScanMode(void);
void APP_Obstacle_Avoidance_TurnMode(void);
void APP_Obstacle_Avoidance_Timer(void);


uint16_t APP_Obstacle_Avoidance_GetState(void);

void APP_Obstacle_Avoidance_SetState(uint16_t State);

uint16_t APP_Obstacle_Avoidance_GetDistance(void);


void APP_Obstacle_Avoidance_ServoRun(void);

uint16_t APP_Obstacle_Avoidance_GetTurnAngle(void);


#endif
