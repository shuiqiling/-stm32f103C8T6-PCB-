#ifndef __HAL_MeasureSpeed_H
#define __HAL_MeasureSpeed_H


void HAL_MeasureSpeed_Init(void);

uint16_t HAL_MeasureSpeed_MeasureRSpeed(void);
uint16_t HAL_MeasureSpeed_MeasureLSpeed(void);

uint16_t HAL_MeasureSpeed_GetRCount(void);
uint16_t HAL_MeasureSpeed_GetLCount(void);

#endif
