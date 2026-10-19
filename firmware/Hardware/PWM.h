#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);

void PWM_ChangeCCR1(uint16_t Compare);
void PWM_ChangeCCR2(uint16_t Compare);
void PWM_ChangeCCR3(uint16_t Compare);

#endif
