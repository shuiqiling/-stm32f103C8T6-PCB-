#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"

uint16_t HC_SR04_StartCounter;
uint16_t HC_SR04_StopCounter;
uint32_t HC_SR04_Result;

uint8_t HC_SR04_State = 0;

void HC_SR04_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);


	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0x00;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);

    TIM_ICInitTypeDef TIM_ICInitStruct;

	TIM_ICStructInit(&TIM_ICInitStruct);

	TIM_ICInitStruct.TIM_Channel=TIM_Channel_3;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICFilter=0xf;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInit(TIM1,&TIM_ICInitStruct);

	TIM_ICInitStruct.TIM_Channel=TIM_Channel_4;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_IndirectTI;
	TIM_ICInitStruct.TIM_ICFilter=0xf;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Falling;
	TIM_ICInit(TIM1,&TIM_ICInitStruct);


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);



	TIM_Cmd(TIM1,ENABLE);


}

void HC_SR04_Measure(void)
{

			if(TIM_GetCapture4(TIM1) > TIM_GetCapture3(TIM1))
			{
				HC_SR04_Result = ((TIM_GetCapture4(TIM1) - TIM_GetCapture3(TIM1)  ) * (342.62 / 2) )/ 100;
			}
			else
			{
				HC_SR04_Result = ((65535 - TIM_GetCapture4(TIM1) + TIM_GetCapture3(TIM1) + 1) * (342.62 / 2) )/ 100;
			}
//			if(HC_SR04_Result>700)
//			{
//				HC_SR04_Result = 1314;
//			}

}

void HC_SR04_RequireTest(void)
{

		GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_SET);
		Delay_us(11);
		GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_RESET);

}

uint16_t HC_SR04_GetDistance(void)
{
	return HC_SR04_Result;
}
