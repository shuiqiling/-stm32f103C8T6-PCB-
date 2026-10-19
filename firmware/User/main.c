#include "stm32f10x.h"                  // Device heade
#include "HAL.h"




/*
Motor： in1：A4(A),A6(B)；
		in2：A5(A),A7(B);
		PWMA:A2(右)
		PWMB:A1(左)

measurespeed:A8(右)
			 A9(左)

Servo:		 A0(D0)

HC_SR04:	 B13(send)
			 A10(measure)



*/
uint16_t UpdateSpeedTimeOut = 0;
uint16_t AvoidanceTimeOut = 0;

uint8_t Timer3_Counter = 0;

int16_t Acc_X,Acc_Y,Acc_Z,Gyro_X,Gyro_Y,Gyro_Z;
int16_t TestData;

int main(void)
{
	OLED_Init();
	APP_ActionControl_Init();
	APP_Obstacle_Avoidance_Init();
	while(1)
	{
		OLED_ShowSignedNum(1,1,Get_PIDOut(),6);
		OLED_ShowNum(2,1,APP_Actioncontrol_GetRSpeed(),6);
		OLED_ShowNum(3,1,HAL_HC_SR04_GetDistance(),6);
		if(APP_Obstacle_Avoidance_GetState()==1)
		{
			APP_ActionControl_StraightGoBack(90);
			APP_Obstacle_Avoidance_StraightMode(AvoidanceTimeOut);
		}
		else if(APP_Obstacle_Avoidance_GetState()==2)
		{
			APP_Actioncontrol_Stop();//停止
			APP_Obstacle_Avoidance_ScanMode();
		}
		else if(APP_Obstacle_Avoidance_GetState()==3)
		{
			APP_Obstacle_Avoidance_TurnMode();
			APP_Actioncontrol_Turn(APP_Obstacle_Avoidance_GetTurnAngle());//转弯
		}

		APP_Obstacle_Avoidance_ServoRun();
	};
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		if(UpdateSpeedTimeOut-- == 0)
		{
			APP_Actioncontrol_UpdateSpeed();
		}
		if(AvoidanceTimeOut-- == 0)
		{
			APP_Obstacle_Avoidance_Timer();
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }

}
