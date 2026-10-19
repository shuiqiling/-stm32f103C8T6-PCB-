#include "stm32f10x.h"                  // Device header
#include "HAL.h"



uint16_t First_order_LastData = 0;


uint16_t Continue_FilterArray[5];
uint16_t Weighted_FilterTempArray[10];

uint16_t First_order(uint16_t First_order_Data,uint8_t Alpha)
{
	uint16_t First_order_Rusult;

	First_order_Rusult = (Alpha * First_order_Data + (100 - Alpha) * First_order_LastData) / 100;

	First_order_LastData = First_order_Rusult;

	return First_order_Rusult;

}
uint16_t Continue_Filter(uint16_t Continue_Filter_Data)
{
	uint16_t Continue_Filter_Rusult;
	for(uint16_t i=0;i<4;i++)
	{
		Continue_FilterArray[4-i] = Continue_FilterArray[4-i-1];
	}
		Continue_FilterArray[0] = Continue_Filter_Data;

	Continue_Filter_Rusult = (Continue_FilterArray[4] + Continue_FilterArray[3] + Continue_FilterArray[2] + Continue_FilterArray[1] + Continue_FilterArray[1]) / 5;

	return Continue_Filter_Rusult;
}

void Weighted_Filter(uint16_t Weighted_Filter_Data,uint16_t *Weighted_Filter_Rusult,uint16_t *Weighted_FilterArray)
{

	if(Weighted_Filter_Data<1000)
	{
	if(Weighted_Filter_Data>10)
	{

		uint16_t i;
		uint16_t j;
		*Weighted_Filter_Rusult = 0;
		for(i = 0; i < 9; i++)
		{
			Weighted_FilterArray[i] = Weighted_FilterArray[i+1];
		}
		Weighted_FilterArray[9] = Weighted_Filter_Data;
		for(j = 0; j < 10 ; j++)
		{
			Weighted_FilterTempArray[j] = Weighted_FilterArray[j];
		}
		Bubble_Sort(Weighted_FilterTempArray,10);

		for(uint16_t p=0;p<3;p++)
		{
			*Weighted_Filter_Rusult += 2*Weighted_FilterTempArray[p];
		}
		for(uint16_t p=4;p<7;p++)
		{
			*Weighted_Filter_Rusult += 28*Weighted_FilterTempArray[p];
		}
		*Weighted_Filter_Rusult += 4*Weighted_FilterTempArray[7];
		for(uint16_t p=8;p<10;p++)
		{
			*Weighted_Filter_Rusult += 2*Weighted_FilterTempArray[p];
		}

		*Weighted_Filter_Rusult = *Weighted_Filter_Rusult/100;

	}
	}

}
