#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "OLED.h"
#include <stdlib.h>
void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);


	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_RESET);

	GPIO_WriteBit(GPIOA,GPIO_Pin_6,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_RESET);
}



void Motor_LSpeed(int8_t speed)
{
	int16_t Temp;
	Temp =  abs(speed) * 200;
		if(speed>0)
		{
			GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_SET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_RESET);
		}
		if(speed<0)
		{
			GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_SET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);
		}
	TIM_SetCompare3(TIM2,Temp);
}

void Motor_RSpeed(int8_t speed)
{
	int16_t Temp;
	Temp =  abs(speed) * 200;
		if(speed>0)
		{
			GPIO_WriteBit(GPIOA,GPIO_Pin_6,Bit_SET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_RESET);
		}
		if(speed<0)
		{
			GPIO_WriteBit(GPIOA,GPIO_Pin_6,Bit_RESET);
			GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_SET);
		}

	TIM_SetCompare2(TIM2,Temp);
}
