#include "stm32f10x.h"     // Device header
#include "OLED.h"

uint16_t RCount = 0;
uint16_t LCount = 0;

uint16_t Timer1_CCR1_Current;      //Ringt Tire
uint16_t Timer1_CCR1_Last = 0;

uint16_t Timer1_CCR2_Current;      //Lift Tire
uint16_t Timer1_CCR2_Last = 0;

uint16_t LastRSpeed = 0;
uint16_t LastLSpeed = 0;

uint32_t RSpeed = 0;
uint32_t LSpeed = 0;

void MeasureSpeed_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);


	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0x00;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);

    TIM_ICInitTypeDef TIM_ICInitStruct;

	TIM_ICStructInit(&TIM_ICInitStruct);

	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICFilter=0xf;
	TIM_ICInit(TIM1,&TIM_ICInitStruct);

	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICFilter=0xf;
	TIM_ICInit(TIM1,&TIM_ICInitStruct);


	TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);
	TIM_ITConfig(TIM1,TIM_IT_CC2,ENABLE);

	NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM1_CC_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

	TIM_SetCounter(TIM1,0);
	TIM_Cmd(TIM1,ENABLE);
}

void MeasureSpeed_MeasureRSpeed(void)
{

	if(Timer1_CCR1_Current<Timer1_CCR1_Last)
	{
		RSpeed = ((618 / 20) *60*100)/ (65535 - Timer1_CCR1_Last + Timer1_CCR1_Current+1);
	}

	else
	{
		RSpeed = ((618 / 20) * 60*100)/(Timer1_CCR1_Current - Timer1_CCR1_Last)  ;
	}



}

void MeasureSpeed_MeasureLSpeed(void)
{

	if(Timer1_CCR2_Current<Timer1_CCR2_Last)
	{
		LSpeed = ((618 / 20) *60*100)/ (65535 - Timer1_CCR2_Last + Timer1_CCR2_Current+1);
	}

	else
	{
		LSpeed = ((618 / 20) * 60*100)/(Timer1_CCR2_Current - Timer1_CCR2_Last)  ;
	}


}

uint16_t MeasureSpeed_GetRSpeed(void)
{
	return RSpeed;
}

uint16_t MeasureSpeed_GetLSpeed(void)
{
	return LSpeed;
}

uint16_t MeasureSpeed_GetRcount(void)
{
	return  RCount;
}

uint16_t MeasureSpeed_GetLcount(void)
{
	return LCount;
}









void TIM1_CC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_CC1) == SET)
	{
		Timer1_CCR1_Last = Timer1_CCR1_Current;
		Timer1_CCR1_Current = TIM_GetCapture1(TIM1);
		RCount++;
		TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
	}

	if(TIM_GetITStatus(TIM1,TIM_IT_CC2) == SET)
	{
		Timer1_CCR2_Last = Timer1_CCR2_Current;
		Timer1_CCR2_Current = TIM_GetCapture2(TIM1);
		TIM_ClearITPendingBit(TIM1,TIM_IT_CC2);
		LCount++;
	}

}
