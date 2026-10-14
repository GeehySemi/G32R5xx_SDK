FILE:    readme.txt
TITLE:   G32R501 GNU linker script selection and layout
VERSION: 1.0.1
DATE:    2026-08-10

G32R501 GNU Linker Scripts (Eclipse / GCC / Clang)
==================================================

Location: device_support/g32r501/common/ld/

Typical scripts:
  g32r501dxy_cpu0_cbus_flash.ld
| g32r501dxy_cpu0_itcm_ram.ld | IR-V0-R0 (dxy) | DTCM 0x400 | CODE in ITCM 48KB; RWZI=0 |
  g32r501dxy_cpu0_cbus_flash_noramvector.ld
  g32r501xc_cbus_flash.ld
  g32r501xc_cbus_flash_noramvector.ld
  g32r501dxy_cpu0_itcm_ram.ld
  g32r501xc_itcm_ram.ld
  g32r501xc_itcm_ram_noramvector.ld
  g32r501xxx_peripheral_memory.ld
  g32r501xxx_dcs_memory.ld

Dual-core / secure / itcm_flash variants use matching prefixes
(g32r501dxy_*, g32r501dxc_*, *_secure, *_itcm_flash).

Hardware sizes
--------------
  xc masters:
    ITCM  64 KB @ 0x00000000
    DTCM  16 KB @ 0x20000000
    Flash 256 KB @ 0x08000000

  dxy CPU0 (Eval examples default):
    ITCM  48 KB @ 0x00000000
    DTCM  16 KB @ 0x20000000
    CPU0 Flash 320 KB @ 0x08000000
    CPU1 Flash stub 320 KB @ 0x08050000

  SRAM1/2/3  8/8/32 KB (share_data)
  Stack default 0x1000; Heap default 0 (matches prior xc ld style)
  Do not copy G32R502 numbers (ITCM 16 KB / DTCM 24 KB).

VECTOR / RWZI / Boot masters (2026-08-10)
----------------------------------------

| File | Template ID | RAM vector | Notes |
|------|-------------|------------|-------|
| g32r501dxy_cpu0_cbus_flash.ld | CF-V0-R0 (dxy) | DTCM 0x400 | **Eval examples default** |
| g32r501dxy_cpu0_cbus_flash_noramvector.ld | CF-NV-R0 (dxy) | None | LINKER_VECTOR_REGION_NONE |
| g32r501xc_cbus_flash.ld | CF-V0-R0 | DTCM 0x400 | xc CF gold |
| g32r501xc_cbus_flash_noramvector.ld | CF-NV-R0 | None | CF noramvector |
| g32r501xc_itcm_ram.ld | IR-V0-R0 | DTCM 0x400 | CODE in ITCM; RWZI=0 |
| g32r501xc_itcm_ram_noramvector.ld | IR-NV-R0 | None | IR noramvector |

Symbols / MEMORY split
----------------------
  __VECTOR_REGION / __VECTOR_SIZE / __RWZI_BANK / __BOOT_STATUS_SNAPSHOT_*
  VECTOR_RAM + DTCM_RAM + DTCM_STACK (general master)
  noramvector: no VECTOR_RAM; DTCM_RAM from DTCM base
  dxy: CPU1_FLASH + .cpu1_code
  Copy/zero tables keep itcm / dtcm / sram1..3 share_data entries as applicable
  DTCM budget: STACK (+ HEAP if non-zero) + 0x400 vector when REGION=0

Default layout (Flash boot, general master)
-------------------------------------------
  0x20000000  VECTOR_RAM   .bss.ram.intvec / ram.intvec
  0x20000400  DTCM_RAM     .data / .bss / dtcm.* / .heap
  DTCM top    DTCM_STACK   .stack (+ optional boot snapshot)

itcm_ram layout
---------------
  .text / tables execute from ITCM_RAM; RW AT> FLASH for init images.
  IR noramvector: startup table / VTOR at ITCM 0x00000000 (not Flash).

noramvector
-----------
  Project must define: LINKER_VECTOR_REGION_NONE

Copy into your project
----------------------
Eclipse projects reference ${ProjDirPath}/g32r501*.ld under project/Eclipse/.
Update masters here first, then sync project copies when ready.

See also: common/sct/readme.txt (MDK), common/icf/readme.txt (IAR).


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
