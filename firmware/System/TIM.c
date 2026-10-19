#include "stm32f10x.h"                  // Device header

void Timer3_Init(uint16_t TIM_Period,uint16_t TIM_Prescaler)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=TIM_Period-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler=TIM_Prescaler-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=1-1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM3,ENABLE);
}

void Timer4_Init(uint16_t TIM_Period,uint16_t TIM_Prescaler)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_InternalClockConfig(TIM4);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=TIM_Period-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler=TIM_Prescaler-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=1-1;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM3,ENABLE);
}

//void TIM3_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
//
//	{
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//
//	}
//}
