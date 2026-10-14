FILE:    readme.txt
TITLE:   G32R502 GNU linker script selection and comment alignment
VERSION: 1.0.0
DATE:    2026-08-10

G32R502 GNU Linker Scripts (Eclipse / GCC / Clang)
==================================================

Location: device_support/g32r502/common/ld/

This refresh aligns the G32R502 common LD masters and template comments with the G32R501 shape while keeping all 502 layout branches, capacities, VECTOR choices, and RWZI semantics unchanged.

Script selection
----------------

| File | Code runs in | RAM vector (.bss.ram.intvec) | Typical use |
|------|--------------|------------------------------|-------------|
| g32r502xc_cbus_flash.ld | CBUS Flash | Yes (configurable) | Peripherals, eval, boot, mathlib integration |
| g32r502xc_itcm_ram.ld | ITCM RAM | Yes (configurable) | Low-latency app code + NVIC |
| g32r502xc_cbus_flash_noramvector.ld | CBUS Flash | No | DSP/math library benchmarks |
| g32r502xc_itcm_ram_noramvector.ld | ITCM RAM | No | DSP/math library benchmarks |

Template directory
------------------

Quick reference for the 16 fixed-layout Eclipse templates:
  common/ld/_template/readme.txt

The parent directory keeps the 4 product masters listed above. The _template tree keeps the 16 fixed-layout LD variants used by the linker-script board-test matrix.

Layout notes
------------

- G32R502 remains a CBUS Flash + ITCM RAM + DTCM RAM device; no ITCM Flash view is added.
- __VECTOR_REGION values 0 / 1 / 2 keep the existing DTCM / ITCM / None meaning.
- __RWZI_BANK values 0 / 1 / 2 keep the existing DTCM / ITCM / spill meaning.
- itcm_ram / itcm_ram_noramvector still require generic RW/ZI to stay in DTCM.
- This update only revises comments, section notes, header wrappers, and date fields.

Copy into your project
----------------------

Eclipse projects reference ${ProjDirPath}/g32r502xc_*.ld under project/Eclipse/.
After updating masters here, run:

  python python_tools/linker_sync/g32r502_sync_linker_copies.py --apply

Stack / heap values and local Wizard edits in each project copy are preserved.

See also: common/sct/readme.txt (MDK), common/icf/readme.txt (IAR).
