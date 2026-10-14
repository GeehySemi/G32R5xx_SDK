FILE:    readme.txt
TITLE:   G32R502 IAR ICF selection and comment alignment
VERSION: 1.0.0
DATE:    2026-08-10

G32R502 IAR Linker Configuration Files (ICF)
============================================

Location: device_support/g32r502/common/icf/

This refresh aligns the G32R502 common ICF masters with the G32R501 comment shape while keeping all capacities, vector modes, RWZI modes, stack / heap values, and placement rules unchanged.

Script selection
----------------

| File | Code runs in | RAM vector (.bss.ram.intvec) | Typical use |
|------|--------------|------------------------------|-------------|
| g32r502xcx7_cbus_flash.icf | CBUS Flash | Yes (configurable) | Peripherals, eval, boot, mathlib integration |
| g32r502xcx7_itcm_ram.icf | ITCM RAM | Yes (configurable) | Low-latency app code + NVIC |
| g32r502xcx7_cbus_flash_noramvector.icf | CBUS Flash | No | DSP/math library benchmarks |
| g32r502xcx7_itcm_ram_noramvector.icf | ITCM RAM | No | DSP/math library benchmarks |

ICF editor controls
-------------------

- __vector_region__ = 0 / 1 / 2 keeps the existing DTCM / ITCM / None meaning.
- __ICFEDIT_rwzi_bank__ = 0 / 1 / 2 keeps the existing DTCM / ITCM / spill meaning.
- __ICFEDIT_size_cstack__ / __ICFEDIT_size_heap__ remain unchanged.
- __ICFEDIT_boot_status_snapshot_enable__ still reserves the last 0x20 bytes of DTCM.

Layout notes
------------

- General scripts keep the same RAM vector / readonly / readwrite layout.
- The *_noramvector* scripts still omit RAM_VEC_region and use full DTCM for data / stack.
- itcm_ram / itcm_ram_noramvector still require generic readwrite to stay in DTCM.
- This update only revises comments, short notes, and date fields.

Copy into your project
----------------------

Each SDK example keeps a copy under project/IAR/. After updating masters here, run:

  python python_tools/linker_sync/g32r502_sync_linker_copies.py --apply

Stack / heap values and local Wizard edits in each project copy are preserved.

See also: common/sct/readme.txt (MDK), common/ld/readme.txt (Eclipse).
