#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"
void WaitEvent(I2C_TypeDef* I2Cx,uint32_t I2C_EVENT)
{
	uint16_t TimeOut=10000;
	while(I2C_CheckEvent(I2Cx,I2C_EVENT) != SUCCESS)
	{
			TimeOut--;
			if(TimeOut==0)
			{
				break;
			}
	};
}


void MPU6050_SendByte(uint8_t MPU6050_Address,uint8_t MPU6050_SendByte)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);
	WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) ;

	I2C_SendData(I2C2,MPU6050_Address);
	WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);

	I2C_SendData(I2C2,MPU6050_SendByte);
	WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);

	I2C_GenerateSTOP(I2C2,ENABLE);


}

uint8_t MPU6050_ReadByte(uint8_t MPU6050_Address)
{
	uint8_t MPU6050_ReadByteData;

	I2C_GenerateSTART(I2C2,ENABLE);
	WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);

	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Transmitter);
	WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

	I2C_SendData(I2C2,MPU6050_Address);
	WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);

	I2C_GenerateSTART(I2C2,ENABLE);
	WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);

	I2C_Send7bitAddress(I2C2,0xD0,I2C_Direction_Receiver);
	WaitEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);

	I2C_AcknowledgeConfig(I2C2,DISABLE);
	I2C_GenerateSTOP(I2C2,ENABLE);

	WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED);
	MPU6050_ReadByteData=I2C_ReceiveData(I2C2);

	I2C_AcknowledgeConfig(I2C2,ENABLE);

	return MPU6050_ReadByteData;


}


void MPU6050_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_OD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_SET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,Bit_SET);

	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_Ack=I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed=50000;
	I2C_InitStruct.I2C_DutyCycle=I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Mode=I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1=0x00;
	I2C_Init(I2C2,&I2C_InitStruct);

	I2C_Cmd(I2C2,ENABLE);

	MPU6050_SendByte(MPU6050_PWR_MGMT_1,0x01);
	MPU6050_SendByte(MPU6050_PWR_MGMT_2,0x00);
	MPU6050_SendByte(MPU6050_SMPLRT_DIV,0x09);
	MPU6050_SendByte(MPU6050_CONFIG,0x06);
	MPU6050_SendByte(MPU6050_GYRO_CONFIG,0x18);
	MPU6050_SendByte(MPU6050_ACCEL_CONFIG,0x18);
}

void MPU6050_GetAGValue(int16_t *Ax,int16_t *Ay,int16_t *Az,int16_t *Gx,int16_t *Gy,int16_t *Gz)
{
	*Ax=(MPU6050_ReadByte(MPU6050_ACCEL_XOUT_H)<<8)|MPU6050_ReadByte(MPU6050_ACCEL_XOUT_L);
	*Ay=(MPU6050_ReadByte(MPU6050_ACCEL_YOUT_H)<<8)|MPU6050_ReadByte(MPU6050_ACCEL_YOUT_L);
	*Az=(MPU6050_ReadByte(MPU6050_ACCEL_ZOUT_H)<<8)|MPU6050_ReadByte(MPU6050_ACCEL_ZOUT_L);
	*Gx=(MPU6050_ReadByte(MPU6050_GYRO_XOUT_H)<<8)|MPU6050_ReadByte(MPU6050_GYRO_XOUT_L);
	*Gy=(MPU6050_ReadByte(MPU6050_GYRO_YOUT_H)<<8)|MPU6050_ReadByte(MPU6050_GYRO_YOUT_L);
	*Gz=(MPU6050_ReadByte(MPU6050_GYRO_ZOUT_H)<<8)|MPU6050_ReadByte(MPU6050_GYRO_ZOUT_L);
}
