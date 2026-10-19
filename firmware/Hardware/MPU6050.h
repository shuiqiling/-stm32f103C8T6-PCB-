#ifndef __MPU6050_H
#define __MPU6050_H
#include "MPU6050_Reg.h"


void MPU6050_SendByte(uint8_t MPU6050_Address,uint8_t MPU6050_SendByte);
uint8_t MPU6050_ReadByte(uint8_t MPU6050_Address);

void MPU6050_GetAGValue(int16_t *Ax,int16_t *Ay,int16_t *Az,int16_t *Gx,int16_t *Gy,int16_t *Gz);
void MPU6050_Init(void);

#endif
