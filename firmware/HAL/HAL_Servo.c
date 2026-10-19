#include "stm32f10x.h"                  // Device header
#include "HAL.h"

void HAL_Servo_Init(void)
{
	Servo_Init();
}

void HAL_Servo_SetAngle(float Angle)
{
	Servo_SetAngle(Angle);
};
