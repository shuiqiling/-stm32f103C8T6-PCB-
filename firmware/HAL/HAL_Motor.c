#include "stm32f10x.h"                  // Device header
#include "HAL.h"
void HAL_Motor_Init(void)
{
	Motor_Init();
}

void HAL_Motor_RSpeed(int8_t Rspeed)
{
	Motor_RSpeed(Rspeed);
}

void HAL_Motor_LSpeed(int8_t Lspeed)
{
	Motor_LSpeed(Lspeed);
}
