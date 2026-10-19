#include "stm32f10x.h"                  // Device header
#include "HAL.h"


void HAL_MPU6050_Init(void)
{
	MPU6050_Init();
}

void HAL_MPU6050_SendByte(uint8_t MPU6050_Address,uint8_t SendByte)
{
	MPU6050_SendByte(SendByte,MPU6050_Address);
}

uint8_t HAL_MPU6050_ReadByte(uint8_t MPU6050_Address)
{
	uint8_t ReadByte;
	ReadByte=MPU6050_ReadByte(MPU6050_Address);
	return ReadByte;
};

void HAL_MPU6050_GetAGValue(int16_t *Ax,int16_t *Ay,int16_t *Az,int16_t *Gx,int16_t *Gy,int16_t *Gz)
{
	MPU6050_GetAGValue(Ax,Ay,Az,Gx,Gy,Gz);
};
