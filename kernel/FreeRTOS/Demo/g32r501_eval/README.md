# g32r501_eval — 双核 FreeRTOS + 共享 RAM IPC + Zidian

G32R501xD eval Demo：CPU0 / CPU1 各跑独立 FreeRTOS；共享 SRAM 双缓冲；IPC 轮询门铃；CPU1 Zidian **仅 `sinf`**；CPU0 **64 点/周波、10 ms/点** 连续相位 + UART **ref/abs_err**。

## 结构

```text
g32r501_eval/
├── common/ipc_shm_msg.h
├── cpu0/   # LED1 + UART + 相位 REQ + RSP + 打印
│   └── project/{MDK,IAR,Eclipse}/
└── cpu1/   # LED2 + Zidian sinf worker
    └── project/{MDK,IAR,Eclipse}/
```

## 编译顺序（三平台通用）

1. 编译 **cpu1**
2. 更新 CPU1 镜像至 `cpu0/source/cpu1_image.bin`（IAR OBJCOPY 可自动写入；MDK 从 `cpu1/.../g32r501_eval_cpu1.bin` 复制）
3. 编译 **cpu0**

### MDK

```text
cpu1/project/MDK/cpu1.uvprojx  →  copy bin →  cpu0/source/cpu1_image.bin
cpu0/project/MDK/cpu0.uvprojx
```

### IAR / Eclipse

Target 名 **G32R501**；IAR 使用 `portable/IAR/ARM_CM52_NTZ/non_secure/portasm.s`。

```powershell
python python_tools/project_compiler/project_compiler.py build -t iar -p kernel/FreeRTOS/Demo/g32r501_eval/cpu1/project/IAR/cpu1.ewp --targets G32R501 --sdk-root .
# 复制 cpu1_image 后
python python_tools/project_compiler/project_compiler.py build -t iar -p kernel/FreeRTOS/Demo/g32r501_eval/cpu0/project/IAR/cpu0.ewp --targets G32R501 --sdk-root .
```

Eclipse 将 `-t iar` 改为 `-t eclipse`，路径改为各 `project/Eclipse/.cproject`。

## 烧录 / 串口

- pyOCD：在 `cpu0/project/MDK` 下，`target=g32r501dxx`，加载 `g32r501_eval_cpu0.axf`
- UART：115200 8N1；Geehy CMSIS-DAP WinUSB 对应 VCP（按探针 SN 查 COM）
- 期望输出示例：
  `IPC seq=64 phase=6.283185rad result=0.000000 ref=0.000000 abs_err=0.00e+00 err=0`

## LED

| 核 | LED | GPIO |
|---|---|---|
| CPU0 | LED1 | 23 |
| CPU1 | LED2 | 34 |
