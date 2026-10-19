# 引脚与硬件核对

下表按当前固件驱动实现整理。原 `main.c` 的左右电机注释与 `Motor.c` 实现存在顺序差异，这里以实际调用为准。

| 功能 | 当前代码引脚 | 依据 |
| --- | --- | --- |
| 舵机 PWM | PA0 / TIM2_CH1 | `Servo.c`、`PWM.c` |
| 右轮 PWM | PA1 / TIM2_CH2 | `Motor_RSpeed()` |
| 左轮 PWM | PA2 / TIM2_CH3 | `Motor_LSpeed()` |
| 左轮方向控制 | PA4、PA5 | `Motor_LSpeed()` |
| 右轮方向控制 | PA6、PA7 | `Motor_RSpeed()` |
| 右轮测速 | PA8 / TIM1_CH1 | `MeasureSpeed.c` |
| 左轮测速 | PA9 / TIM1_CH2 | `MeasureSpeed.c` |
| HC-SR04 触发 | PB13 | `HC_SR04_RequireTest()` |
| HC-SR04 回波 | PA10 / TIM1_CH3，配合 CH4 间接捕获 | `HC_SR04_Init()` |
| OLED 软件时钟/数据 | PB8、PB9 | `OLED.c` |

相关源码：[驱动目录](../firmware/Hardware)、[PWM](../firmware/Hardware/PWM.c)、[超声波](../firmware/Hardware/HC_SR04.c)、[测速](../firmware/Hardware/MeasureSpeed.c)。

## 复测顺序

1. 按 [原理图](../hardware/schematic/schematic.pdf) 和实物确认供电、地线、晶振、复位及 SWD。
2. 对照源码检查接口；PDF/PCB 与软件可能来自不同迭代，需要分别核对。
3. 分别测试 OLED、舵机、HC-SR04，再验证轮速反馈与电机方向。
4. 核实测速/测距共用 TIM1 的配置及时序，再做避障联调。

硬件导出文件名标记为 2026-06-04。完整资料见 [hardware/README.md](../hardware/README.md)。
