# 构建与烧录

## 工程环境

| 项目 | 当前工程配置 |
| --- | --- |
| IDE | Keil MDK/uVision |
| 编译器 | 原工程记录 ARM Compiler 5.06 update 5，build 528 |
| 目标器件 | STM32F103C8，使用中容量启动文件 |
| 器件包 | 原工程记录 `Keil.STM32F1xx_DFP.2.2.0` |
| 标准外设库 | STM32F10x Standard Peripheral Library V3.5.0，已随项目保存 |
| 预处理宏 | `USE_STDPERIPH_DRIVER`、`STM32F10X_MD` |
| 工程入口 | [`firmware/projects.uvprojx`](../firmware/projects.uvprojx) |
| 默认输出 | `firmware/Objects/`，目标文件名 `projects` |

工程路径相对 `firmware/`，不依赖原作者电脑目录。本次显式配置 `STM32F10X_MD`，避免依赖本机或器件包的隐式定义。

## 在 uVision 中构建

1. 准备 Keil MDK 的 ARM 开发环境与 STM32F1 器件支持包。
2. 打开 `firmware/projects.uvprojx`，选中 `Target 1`。
3. 确认使用 ARM Compiler 5。迁移到 ARM Compiler 6 需要处理旧 CMSIS 汇编/内联汇编兼容性。
4. 核对目标器件、实际晶振及下载器，再执行 Rebuild。
5. 原工程未开启 HEX 导出；需要时在 `Options for Target → Output` 勾选 `Create HEX File`。
6. 按实际 ST-Link/J-Link 配置烧录，先验证时钟、显示与测距，再验证电机和避障流程。

仓库不包含个人 `.uvoptx`/`.uvguix.*` 状态，调试器设置需要在当前电脑选择。

## 命令行示例

在已安装 MDK ARM 工具链的 Windows 终端中，按实际安装位置调整：

```powershell
& 'C:\Keil_v5\UV4\UV4.exe' -b '.\firmware\projects.uvprojx' -t 'Target 1' -j0 -o '.\firmware\build.log'
```

仅安装 C51 的 uVision 不代表具备 ARM 编译器。本次整理环境只有 uVision/C51，未安装 ARM Compiler 5，因此未宣称固件重新编译通过。

## 仓库检查

```bash
python scripts/verify_repository.py
```

检查 Keil 引用文件、包含目录、文件名大小写、项目内头文件、硬件资料与 Gerber 压缩包、Markdown 相对链接和意外编译缓存。检查不替代交叉编译或真机测试；代码复测事项见 [known-issues.md](known-issues.md)。
