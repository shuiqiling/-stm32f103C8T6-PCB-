#include "stm32f10x.h"                  // Device header
#include "Delay.h"


void KEY_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_KEY;
	GPIO_KEY.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_KEY.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_6;
	GPIO_KEY.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_KEY);
}


char KEY_check1()
{
	char check1=0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==0);
		Delay_ms(20);
		check1=1;
	}
	return check1;
}

char KEY_check2()
{
	char check2=0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0);
		Delay_ms(20);
		check2=1;
	}
	return check2;
}
