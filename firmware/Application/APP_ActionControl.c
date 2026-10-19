#include "stm32f10x.h"                  // Device header
#include "HAL.h"

uint16_t APP_ActionControl_RSpeed;
uint16_t APP_ActionControl_LSpeed;

uint16_t APP_ActionControl_RSpeedArray[10];
uint16_t APP_ActionControl_LSpeedArray[10];

uint16_t LastGetLCount = 0;
uint16_t LastGetRCount = 0;

uint16_t APP_ActionControl_RCount = 0;
uint16_t APP_ActionControl_LCount = 0;


uint16_t EmergencyStopLabel = 0;
int16_t LastRError;
int16_t LastLError;

int16_t LastROut;
int16_t LastLOut;

int32_t *PID_R_Iout;
int32_t *PID_L_Iout;

void APP_ActionControl_Init(void)
{
	Timer3_Init(1000,7200);
	HAL_PWM_Init();
	HAL_Motor_Init();
	HAL_MeasureSpeed_Init();
}

void APP_ActionControl_StraightGoBack(int8_t APP_Speed)
{
	EmergencyStopLabel = 0;
	HAL_Motor_RSpeed(PID_MotorControl(APP_ActionControl_RSpeed,APP_Speed,&LastRError,&LastROut,PID_R_Iout));
	HAL_Motor_LSpeed(PID_MotorControl(APP_ActionControl_LSpeed,APP_Speed,&LastLError,&LastLOut,PID_L_Iout));
}

void APP_Actioncontrol_TurnRight(int8_t APP_TurnAngle)
{
	EmergencyStopLabel = 0;
	if(APP_TurnAngle>APP_ActionControl_RCount)
	{
		if(HAL_MeasureSpeed_GetRCount()-LastGetRCount>0)
		{
			LastGetRCount = HAL_MeasureSpeed_GetRCount();
			APP_ActionControl_RCount++;
		}
		HAL_Motor_LSpeed(PID_MotorControl(APP_ActionControl_LSpeed,80,&LastLError,&LastLOut,PID_L_Iout));
		HAL_Motor_RSpeed(0);
	}
	else
	{
		APP_ActionControl_RCount = 0;
		APP_Obstacle_Avoidance_SetState(0);
	}
}

void APP_Actioncontrol_TurnLeft(int8_t APP_TurnAngle)
{
	EmergencyStopLabel = 0;
	if(APP_TurnAngle>APP_ActionControl_LCount)
	{
		if(HAL_MeasureSpeed_GetLCount()-LastGetLCount>0)
		{
			LastGetLCount = HAL_MeasureSpeed_GetLCount();
			APP_ActionControl_LCount++;
		}
		HAL_Motor_RSpeed(PID_MotorControl(APP_ActionControl_RSpeed,80,&LastRError,&LastROut,PID_R_Iout));
		HAL_Motor_LSpeed(0);
	}
	else
	{
		APP_ActionControl_LCount = 0;
		APP_Obstacle_Avoidance_SetState(0);
	}

}

void APP_Actioncontrol_Turn(int8_t APP_TurnAngle)
{
	if(APP_TurnAngle-90<0)
	{
		APP_Actioncontrol_TurnLeft(90-APP_TurnAngle);
	}
	if(APP_TurnAngle-90>=0)
	{
		APP_Actioncontrol_TurnRight(APP_TurnAngle-90);
	}
}


void APP_Actioncontrol_Stop(void)
{
	EmergencyStopLabel = 1;
	HAL_Motor_RSpeed(0);
	HAL_Motor_LSpeed(0);
}

uint16_t  APP_Actioncontrol_GetStopLabel(void)
{
	return EmergencyStopLabel;
}

uint16_t APP_Actioncontrol_GetRSpeed(void)
{

	return APP_ActionControl_RSpeed;

}

uint16_t APP_Actioncontrol_GetLSpeed(void)
{
	return APP_ActionControl_LSpeed;
}

void APP_Actioncontrol_SetStopLabel(uint16_t StopState)
{
	EmergencyStopLabel = StopState;
}


void APP_Actioncontrol_UpdateSpeed(void) 			//采样频率有多快，如果远快于传感器采样频率则加权滤波快速移位采集的是同一个数，加权滤波失效
{
	Weighted_Filter(HAL_MeasureSpeed_MeasureRSpeed(),&APP_ActionControl_RSpeed,APP_ActionControl_RSpeedArray);
	Weighted_Filter(HAL_MeasureSpeed_MeasureLSpeed(),&APP_ActionControl_LSpeed,APP_ActionControl_LSpeedArray);
}
