# 原始资料与目录迁移

原始包保存在 [archive/超声波智能避障小车.zip](../archive/超声波智能避障小车.zip)，Git 提交历史保留。

| 原始目录 | 当前目录 |
| --- | --- |
| 超声波智能避障小车程序/Algorithm | `firmware/Algorithm/` |
| 超声波智能避障小车程序/Application | `firmware/Application/` |
| 超声波智能避障小车程序/HAL | `firmware/HAL/` |
| 超声波智能避障小车程序/Hardware | `firmware/Hardware/` |
| 超声波智能避障小车程序/system | `firmware/System/` |
| 超声波智能避障小车程序/user | `firmware/User/` |
| 超声波智能避障小车程序/start | `firmware/Libraries/CMSIS/` |
| 超声波智能避障小车程序/liberary | `firmware/Libraries/STM32F10x_StdPeriph_Driver/` |
| 立创eda | `hardware/` |

- `MototPID.c` 更名为 `MotorPID.c`，同步调整 Keil 引用。
- C、头文件与汇编统一为 UTF-8/LF，保留第三方版权说明。
- 工程使用新目录下的相对路径，并明确配置 `STM32F10X_MD`。
- 排除 Objects/Listings、个人 IDE 配置和旧清理批处理；原样版本仍在压缩包内。
- PDF、BOM 与 Gerber 的文件字节保持不变。
- 原包没有嘉立创 EDA 可编辑工程，没有将 PDF/Gerber 称为设计源文件。

逐文件路径与导入时 SHA256 见 [import-manifest.json](import-manifest.json)。清单是导入记录，后续合法代码修改可以产生不同摘要。
