#include "stm32f10x.h"
#include "HAL.h"



#define K_SCALE    1000

int16_t PID_Kp = 2000;
int16_t PID_Ki ;
int16_t PID_Kd = 0;

int32_t PID_Pout;
//int32_t PID_Iout;
int32_t PID_Dout;
int16_t PID_Out;


int16_t Error;
int16_t LastError = 0;

int16_t Integral_Limit = 0;
int16_t OutPut_Limit = 99;


int16_t PID_MotorControl(uint16_t PID_Data,int16_t PID_TargetData,int16_t *LastError,int16_t *LastOut,int32_t *PID_Iout)
{
	int16_t PID_DataTran;
	PID_DataTran = (int16_t)PID_Data / 5 ;

	if(APP_Actioncontrol_GetStopLabel() == 1)
	{
		*PID_Iout = 0;
		*LastError = 0;
	}



	if(PID_TargetData>=0)
	{

	}
	else if(PID_TargetData<0)
	{
		PID_DataTran = -PID_DataTran;
	}
	Error = PID_TargetData - PID_DataTran ;




	if(abs(Error)<10)
	{
		PID_Ki =200;
	}
	else if(abs(Error)<40&&abs(Error)>10)
	{
		PID_Ki =100;
	}
	else if(abs(Error)<60&&abs(Error)>40)
	{
		PID_Ki =100;
	}
	else
	{
		PID_Ki =0;
	}



	PID_Pout = PID_Kp * Error/K_SCALE;
	*PID_Iout += PID_Ki * Error/K_SCALE;
	PID_Dout = PID_Kd * (Error - *LastError)/K_SCALE;

	if(*PID_Iout >= Integral_Limit)
	{
		*PID_Iout = Integral_Limit;
	}
	if(*PID_Iout < -Integral_Limit)
	{
		*PID_Iout = -Integral_Limit;
	}


	PID_Out = PID_Pout + *PID_Iout + PID_Dout;

	if(PID_Out-*LastOut>=5)
	{
		PID_Out = *LastOut+5;
	}
	if(PID_Out-*LastOut<=-5)
	{
		PID_Out = *LastOut-5;
	}



	if(PID_TargetData>0)
	{
	if(PID_Out > OutPut_Limit)
	{
		PID_Out = OutPut_Limit;
	}
	}
	if(PID_TargetData<0)
	{
	if(PID_Out < -OutPut_Limit)
	{
		PID_Out = -OutPut_Limit;
	}
	}

	*LastError = Error;
	*LastOut = PID_Out;

	return PID_Out;

}

int16_t Get_PIDOut(void)
{
	return PID_Out;

}
