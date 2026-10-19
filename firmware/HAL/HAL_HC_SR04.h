#ifndef HAL_HC_SR04
#define HAL_HC_SR04

void HAL_HC_SR04_Init(void);
void HAL_HC_SR04_Measure(void);
void HAL_HC_SR04_RequireMeasure(void);
uint16_t HAL_HC_SR04_GetDistance(void);

#endif
