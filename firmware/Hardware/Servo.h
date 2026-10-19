#ifndef __Servo_H
#define __Servo_H

extern float Angle;
extern uint8_t ServoState;

void Servo_Init(void);

void Servo_SetAngle(float Angle);


#endif
