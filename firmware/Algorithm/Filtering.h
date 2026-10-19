#ifndef __Filtering_H
#define __Filtering_H


uint16_t First_order(uint16_t First_order_Data,uint8_t Alpha);

uint16_t Continue_Filter(uint16_t Continue_Filter_Data);

void Weighted_Filter(uint16_t Weighted_Filter_Data,uint16_t *Weighted_Filter_Rusult,uint16_t *Weighted_FilterArray);




#endif
