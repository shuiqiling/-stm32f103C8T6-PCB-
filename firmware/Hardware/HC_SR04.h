#ifndef __HC_SR04_H
#define __HC_SR04_H
uint16_t HC_SR04_GetDistance(void);


void HC_SR04_Init(void);
void HC_SR04_Measure(void);

void HC_SR04_RequireTest(void);



#endif
