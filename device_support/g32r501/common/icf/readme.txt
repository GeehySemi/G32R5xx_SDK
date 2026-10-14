FILE:    readme.txt
TITLE:   G32R501 IAR ICF selection and layout
VERSION: 1.0.1
DATE:    2026-08-10

G32R501 IAR Linker Configuration Files (ICF)
============================================

Location: device_support/g32r501/common/icf/

Script names encode package / core / boot mode, for example:
  g32r501dxyx7_cpu0_cbus_flash.icf
| g32r501dxyx7_cpu0_itcm_ram.icf | Yes (default DTCM) | dxy IR; rwzi_bank must stay 0 |
  g32r501dxyx7_cpu0_cbus_flash_noramvector.icf
  g32r501xcx7_cbus_flash.icf
  g32r501xcx7_cbus_flash_noramvector.icf
  g32r501dxyx7_cpu0_itcm_ram.icf
  g32r501xcx7_itcm_ram.icf
  g32r501xcx7_itcm_ram_noramvector.icf

Hardware sizes
--------------
  xc:
    ITCM  0x00000000..0x0000FFFF (64 KB)
    DTCM  0x20000000..0x20003FFF (16 KB)
    Flash 0x08000000..0x0803FFFF (256 KB)

  dxy CPU0 (Eval examples default):
    ITCM  0x00000000..0x0000BFFF (48 KB)
    DTCM  0x20000000..0x20003FFF (16 KB)
    CPU0 Flash 0x08000000..0x0804FFFF (320 KB)
    CPU1 Flash stub 0x08050000..0x0809FFFF

  Stack / Heap default 0x1000 / 0x1000 (sct/icf product masters)
  Do not copy G32R502 numbers.

VECTOR / RWZI / Boot masters (2026-08-10)
----------------------------------------

| File | RAM vector | Notes |
|------|------------|-------|
| g32r501dxyx7_cpu0_cbus_flash.icf | Yes (__vector_region__) | **Eval examples default** |
| g32r501dxyx7_cpu0_cbus_flash_noramvector.icf | No (fixed region=2) | Define LINKER_VECTOR_REGION_NONE |
| g32r501xcx7_cbus_flash.icf | Yes | xc CF packaging / matrix gold |
| g32r501xcx7_cbus_flash_noramvector.icf | No | CF noramvector |
| g32r501xcx7_itcm_ram.icf | Yes (default DTCM) | IR boot; rwzi_bank must stay 0 |
| g32r501xcx7_itcm_ram_noramvector.icf | No | IR noramvector; LINKER_VECTOR_REGION_NONE |

Symbols (general Flash / IR masters)
------------------------------------
  __vector_region__     0=DTCM, 1=ITCM, 2=None
  __ICFEDIT_intvec_size__  0x400
  __ICFEDIT_rwzi_bank__    0=DTCM, 1=ITCM, 2=DTCM then ITCM spill
  __ICFEDIT_boot_status_snapshot_enable__  0/1 (last 0x20 of DTCM)
  itcm_ram: rwzi_bank != 0 forces a link-time failure path

Regions
-------
  RAM_VEC_region / DTCM_DATA_region / DTCM_STACK_region
  sram1/2/3.share_data stay in SRAM1/2/3.
  dxy masters keep CPU1_region { section __cpu1_image }.

Default (__vector_region__ = 0)
-------------------------------
  0x20000000..0x200003FF  .bss.ram.intvec
  0x20000400..             DTCM data / RW / HEAP
  top of DTCM              CSTACK (minus optional boot snapshot)
  DTCM budget: STACK+HEAP + 0x400 vector

noramvector
-----------
  No RAM vector slot; DTCM data from 0x20000000.
  Project Define: LINKER_VECTOR_REGION_NONE
  IR noramvector: startup/.intvec at ITCM 0x00000000 (not Flash).

Copy into your project
----------------------
Examples keep copies under project/IAR/. Update masters here first.
Example sync is a separate step (not part of common-only landing).

See also: common/sct/readme.txt (MDK), common/ld/readme.txt (Eclipse).


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
