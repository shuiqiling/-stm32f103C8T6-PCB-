#include "stm32f10x.h"                  // Device header
#include "HAL.h"

uint16_t ScanModeCounter = 0;
uint16_t APP_Obstacle_Avoidance_State = 0;//空闲状态标志位
uint16_t HAL_Servo_Angle = 0;
uint16_t HAL_Servo_AngleNum = 0;
uint16_t APP_Servo_TurnAngle;

void APP_Obstacle_Avoidance_Init(void)
{
	Timer3_Init(1000,7200);
	HAL_PWM_Init();
	HAL_HC_SR04_Init();
	HAL_Servo_Init();
}

void APP_Obstacle_Avoidance_StraightMode(uint8_t AvoidanceTimeOut)
{
	if(APP_Obstacle_Avoidance_State == 1)//触发定时中断修改标志位，目前是模式一
	{
//		TIM_SetAutoreload(TIM3,5000);
		AvoidanceTimeOut = 3;
		HAL_Servo_Angle = 90;
		HAL_HC_SR04_RequireMeasure();
		HAL_HC_SR04_Measure();
		APP_Obstacle_Avoidance_State = 0;
	}
}

uint16_t APP_Obstacle_Avoidance_Warning(void)
{
	if(APP_Obstacle_Avoidance_State != 3)
	{
		if(HAL_HC_SR04_GetDistance()<50)
		{
			return 1;
		}

	}
	return 0;

}



void APP_Obstacle_Avoidance_ScanMode(void)
{
	if(APP_Obstacle_Avoidance_State == 2)//触发定时中断修改标志位，目前是模式二
	{
		if(APP_Obstacle_Avoidance_Warning()==1)
		{

			TIM_SetAutoreload(TIM3,2500);
			HAL_Servo_Angle = 0+30*HAL_Servo_AngleNum;
			HAL_HC_SR04_RequireMeasure();
			HAL_HC_SR04_Measure();
			HAL_Servo_AngleNum++;
			APP_Obstacle_Avoidance_State = 0;
			if(HAL_Servo_AngleNum>=6)
			{
				APP_Servo_TurnAngle = HAL_Servo_Angle;
				HAL_Servo_AngleNum = 0;
				APP_Obstacle_Avoidance_State = 3;//转弯模式
			}

		}
		else
		{
			APP_Servo_TurnAngle = HAL_Servo_Angle;
			HAL_Servo_AngleNum = 0;
			APP_Obstacle_Avoidance_State = 3;
		}

	}
}

void APP_Obstacle_Avoidance_TurnMode(void)
{
	if(APP_Obstacle_Avoidance_State == 3)
	{

	}
}


void APP_Obstacle_Avoidance_Timer(void)
{
	if(APP_Obstacle_Avoidance_State != 3)
	{


		if(APP_Obstacle_Avoidance_Warning()==0)
		{
			APP_Obstacle_Avoidance_State = 1;
		}


		if(APP_Obstacle_Avoidance_Warning()==1)
		{

			APP_Obstacle_Avoidance_State = 2;

		}
	}
	else if(APP_Obstacle_Avoidance_State == 3)
	{

	}

}



void APP_Obstacle_Avoidance_ServoRun(void)
{
	HAL_Servo_SetAngle(HAL_Servo_Angle);
}

uint16_t APP_Obstacle_Avoidance_GetTurnAngle(void)
{
	return APP_Servo_TurnAngle;
}

uint16_t APP_Obstacle_Avoidance_GetState(void)
{
	return APP_Obstacle_Avoidance_State;
}


void APP_Obstacle_Avoidance_SetState(uint16_t State)
{
	APP_Obstacle_Avoidance_State = State;
}

uint16_t APP_Obstacle_Avoidance_GetDistance(void)
{
	return HAL_HC_SR04_GetDistance();
}
