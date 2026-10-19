#ifndef __MeasureSpeed_H
#define __MeasureSpeed_H

void MeasureSpeed_Init(void);

void MeasureSpeed_MeasureRSpeed(void);
void MeasureSpeed_MeasureLSpeed(void);

uint16_t MeasureSpeed_GetRcount(void);
uint16_t MeasureSpeed_GetLcount(void);

uint16_t MeasureSpeed_GetRSpeed(void);
uint16_t MeasureSpeed_GetLSpeed(void);



#endif
