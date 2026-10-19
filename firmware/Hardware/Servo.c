#include "stm32f10x.h"                  // Device header
#include "PWM.h"

float Angle;
uint8_t ServoState = 0;

void Servo_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}


void Servo_SetAngle(float Angle)
{
	PWM_ChangeCCR1(Angle*2000/180+500);
}
