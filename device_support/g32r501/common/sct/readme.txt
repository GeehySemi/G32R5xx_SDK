FILE:    readme.txt
TITLE:   G32R501 MDK scatter file selection and layout
VERSION: 1.0.1
DATE:    2026-08-10

G32R501 MDK Scatter Files (Keil)
================================

Location: device_support/g32r501/common/sct/

G32R501 has multiple memory / core variants (xc/xy/dxc/dxy, cbus/itcm flash,
secure, cpu0/cpu1). Pick the script that matches the device and boot mode.

Hardware sizes
--------------
  xc (single-core packaging / IR matrix):
    ITCM  0x00000000 + 0x10000 (64 KB)
    DTCM  0x20000000 + 0x4000  (16 KB)
    Flash CBUS 0x08000000 + 0x40000 (256 KB)

  dxy CPU0 (Eval examples default family):
    ITCM  0x00000000 + 0xC000 (48 KB)   — NOT xc 64 KB
    DTCM  0x20000000 + 0x4000  (16 KB)
    CPU0 Flash 0x08000000 + 0x50000 (320 KB)
    CPU1 Flash 0x08050000 + 0x50000 (320 KB stub)

  SRAM1/2/3  as Wizard (default 8/8/32 KB)
  Do not copy G32R502 numbers (ITCM 16 KB / DTCM 24 KB).

Script selection (VECTOR / RWZI / Boot masters, 2026-08-10)
----------------------------------------------------------

| File | Code runs in | RAM vector | Typical use |
|------|--------------|------------|-------------|
| g32r501dxy_cpu0_cbus_flash.sct | CBUS Flash | Yes (configurable) | **Eval / product examples default** |
| g32r501dxy_cpu0_itcm_ram.sct | ITCM RAM | Yes (default DTCM) | dxy IR; RWZI forced DTCM |
| g32r501dxy_cpu0_cbus_flash_noramvector.sct | CBUS Flash | No | Lib / no Interrupt_initVectorTable (dxy) |
| g32r501xc_cbus_flash.sct | CBUS Flash | Yes (configurable) | xc packaging / CF matrix gold |
| g32r501xc_cbus_flash_noramvector.sct | CBUS Flash | No | Library / CF noramvector |
| g32r501xc_itcm_ram.sct | ITCM RAM | Yes (default DTCM) | xc IR boot; RWZI forced DTCM |
| g32r501xc_itcm_ram_noramvector.sct | ITCM RAM | No | IR noramvector; define LINKER_VECTOR_REGION_NONE |


Eval examples stay on **dxy_cpu0_cbus_flash** (do not silently retarget to xc_*).

General script: g32r501xc_cbus_flash.sct / g32r501dxy_cpu0_cbus_flash.sct
------------------------------------------------------------------------

Configuration Wizard:

  Vector Execution Region (__VECTOR_REGION)
    0 = DTCM - RAM vector at 0x20000000 (default)
    1 = ITCM - RAM vector at 0x00000000
    2 = None - no LR_VEC; full DTCM for RW (same idea as *_noramvector*)

  Generic RW/ZI Bank (__RWZI_BANK)
    0 = DTCM only (default)
    1 = ITCM only
    2 = DTCM first, spill to ITCM
    dtcm.*/itcm.* custom sections and sram*.share_data are fixed.
    When Code Execution Region is ITCM (itcm_ram masters), keep __RWZI_BANK = 0
    (#error otherwise).

  Boot Status Snapshot (__BOOT_STATUS_SNAPSHOT_ENABLE)
    0 = off (default); 1 = reserve last 0x20 of DTCM; stack top moves down.

  Stack default 0x1000, Heap default 0x1000. SRAM1/2/3 Wizard unchanged.
  DTCM budget reminder: STACK+HEAP + 0x400 vector when REGION=0.

Default layout (__VECTOR_REGION = 0, snapshot = 0) — Flash boot
---------------------------------------------------------------

  Flash       ER_ROM        code + const
  ITCM        RW_RAM_ITCM   itcm.instruction / itcm.ramfunc
  0x20000000  RW_VECTOR_VEC .bss.ram.intvec (LR_VEC, 0x400)
  0x20000400  RW_RAM_DTCM   data / bss / heap
  ...         ARM_LIB_STACK toward DTCM physical top 0x20004000
  SRAM1..3    sram*.share_data only
  (dxy only)  LR_ROM_CPU1   cpu1_code stub

itcm_ram: g32r501xc_itcm_ram.sct / g32r501dxy_cpu0_itcm_ram.sct
--------------------------------------------------------------------

  CODE executes from ITCM (xc 64 KB / dxy 48 KB). VECTOR default 0 (DTCM).
  RWZI forced 0. Product STACK/HEAP = 0x1000 / 0x1000.

noramvector
-----------

  No VECTOR Wizard / no LR_VEC; DTCM starts at 0x20000000.
  Project must define: LINKER_VECTOR_REGION_NONE
  CF noramvector: VTOR stays at Flash/startup table.
  IR noramvector: VTOR stays at ITCM startup table (0x00000000), not Flash.

Copy into your project
----------------------
Each SDK example keeps a copy under project/MDK/. Update masters here first,
then sync project copies when ready. (Example sync is a separate step.)

See also: common/icf/readme.txt (IAR), common/ld/readme.txt (Eclipse/GCC).


File comment convention (V1.0.1)
--------------------------------
English section banners + main-region trailing notes (ARMCM52-like).
Top Flash/RAM capacity uses Configuration Wizard on SCT; ICF editor zone keeps one-line enums only.
No sync-from-502 / pending-vector process notes in product masters.

Vector framework status (2026-08-10)
------------------------------------
W1–W5 common masters backfilled with VECTOR/RWZI/Boot.
CPU1 cbus/itcm_flash product STACK/HEAP default 0x400/0x400.
dxyx8q: ICF only; SCT/LD reuse dxy_*.

[RWZI bit mask - G32R501]
- __RWZI_BANK / __ICFEDIT_rwzi_bank__ is a bit mask: bit0 DTCM, bit1 ITCM,
  bit2 SRAM1, bit3 SRAM2, bit4 SRAM3.
- Default 0x1F (all on); itcm_ram masters default 0x1D (no ITCM bit).
- SRAM bits require matching __SRAM*_ENABLED; otherwise the build errors.
- G32R502 remains enum 0/1/2 (no system SRAM).
