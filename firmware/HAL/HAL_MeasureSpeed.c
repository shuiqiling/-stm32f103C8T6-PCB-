#include "stm32f10x.h"                  // Device header
#include "HAL.h"




void HAL_MeasureSpeed_Init(void)
{
	MeasureSpeed_Init();
}

uint16_t HAL_MeasureSpeed_MeasureRSpeed(void)
{
	uint16_t HAL_RSpeed;
	MeasureSpeed_MeasureRSpeed();
	HAL_RSpeed = MeasureSpeed_GetRSpeed();
	return HAL_RSpeed;
};

uint16_t HAL_MeasureSpeed_MeasureLSpeed(void)
{
	int16_t HAL_LSpeed;
	MeasureSpeed_MeasureLSpeed();
	HAL_LSpeed = MeasureSpeed_GetLSpeed();
	return HAL_LSpeed;
};

uint16_t HAL_MeasureSpeed_GetRCount(void)
{
	return MeasureSpeed_GetRcount();
}

uint16_t HAL_MeasureSpeed_GetLCount(void)
{
	return MeasureSpeed_GetLcount();
}
