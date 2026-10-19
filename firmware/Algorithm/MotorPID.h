#ifndef __MotoePID_H
#define __MotoePID_H

int16_t PID_MotorControl(uint16_t PID_Data,int16_t PID_TargetData,int16_t *LastError,int16_t *LastOut,int32_t *PID_IOut);
int16_t Get_PIDOut(void);

#endif
