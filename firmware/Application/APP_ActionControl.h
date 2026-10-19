#ifndef _APP_ActionControl_H
#define _APP_ActionControl_H


void APP_ActionControl_Init(void);

void APP_ActionControl_StraightGoBack(int8_t APP_Speed);

void APP_Actioncontrol_TurnRight(int8_t APP_TurnSpeed);

void APP_Actioncontrol_TurnLeft(int8_t APP_TurnSpeed);

void APP_Actioncontrol_Stop(void);

uint16_t  APP_Actioncontrol_GetStopLabel(void);

uint16_t APP_Actioncontrol_GetRSpeed(void);

uint16_t APP_Actioncontrol_GetLSpeed(void);

void APP_Actioncontrol_SetStopLabel(uint16_t StopState);

void APP_Actioncontrol_UpdateSpeed(void);

extern int16_t test;

void APP_Actioncontrol_TurnRight(int8_t APP_TurnAngle);

void APP_Actioncontrol_TurnLeft(int8_t APP_TurnAngle);

void APP_Actioncontrol_Turn(int8_t APP_TurnAngle);


#endif
