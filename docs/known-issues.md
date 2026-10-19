# 后续复测与改进事项

本次整理工程结构和资料，保留原始应用控制逻辑。以下来自静态阅读，尚未在实物上重新验证；仓库路径检查通过不代表这些事项已经解决。

| 事项 | 代码位置 | 后续方向 |
| --- | --- | --- |
| PID 积分状态使用未指向存储空间的全局指针 | [APP_ActionControl.c](../firmware/Application/APP_ActionControl.c)、[MotorPID.c](../firmware/Algorithm/MotorPID.c) | 为左右轮提供有效积分状态存储，验证停止/重启状态清零 |
| 首次或相同捕获值可能导致测速分母为 0 | [MeasureSpeed.c](../firmware/Hardware/MeasureSpeed.c) | 处理首帧、停止与溢出，确认速度单位 |
| `AvoidanceTimeOut` 按值传入，赋值不更新主程序同名变量 | [APP_Obstacle_Avoidance.c](../firmware/Application/APP_Obstacle_Avoidance.c)、[main.c](../firmware/User/main.c) | 统一超时计数的归属和更新方式 |
| `Timer4_Init()` 最后启用 TIM3 | [TIM.c](../firmware/System/TIM.c) | 确认该函数用途，再修正验证 |
| 左右轮注释和驱动实现不完全一致 | [Motor.c](../firmware/Hardware/Motor.c) | 按实物转向统一命名 |
| 旧 CMSIS、ARM Compiler 5 与器件包依赖 | [构建说明](build.md) | 在对应工具链上记录完整构建结果后再讨论迁移 |

本次没有调整 PID 参数或改写避障状态机；上述清单用于后续带硬件复测。
