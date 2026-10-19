#include "stm32f10x.h"                  // Device header
#include "HAL.h"

void HAL_HC_SR04_Init(void)
{
	HC_SR04_Init();
}

void HAL_HC_SR04_Measure(void)
{
	HC_SR04_Measure();

}

void HAL_HC_SR04_RequireMeasure(void)
{
	HC_SR04_RequireTest();
}

uint16_t HAL_HC_SR04_GetDistance(void)
{
	return HC_SR04_GetDistance();
}
