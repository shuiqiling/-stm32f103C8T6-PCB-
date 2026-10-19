#include "stm32f10x.h"                  // Device header
#include "HAL.h"

uint16_t Bubble_Sort_Temp;

void Bubble_Sort(uint16_t *Bubble_Sort_Array,uint16_t Bubble_SortNum)
{
	for(uint16_t j=0;j<Bubble_SortNum;j++)
	{
		for(uint16_t i=0;i<Bubble_SortNum-1-j;i++)
		{
			if(Bubble_Sort_Array[Bubble_SortNum-1-j]<Bubble_Sort_Array[i])
			{
				Bubble_Sort_Temp = Bubble_Sort_Array[Bubble_SortNum-1-j];
				Bubble_Sort_Array[Bubble_SortNum-1-j] = Bubble_Sort_Array[i];
				Bubble_Sort_Array[i] =  Bubble_Sort_Temp;
			}
		}
	}
}
