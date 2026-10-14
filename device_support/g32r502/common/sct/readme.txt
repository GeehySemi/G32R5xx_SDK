FILE:    readme.txt
TITLE:   G32R502 MDK scatter file selection and comment alignment
VERSION: 1.0.0
DATE:    2026-08-10

G32R502 MDK Scatter Files (Keil)
================================

Location: device_support/g32r502/common/sct/

This refresh aligns the G32R502 common scatter masters with the G32R501
comment / Configuration Wizard shape while keeping all 502 capacities,
VECTOR / RWZI options, stack / heap defaults, and layout branches unchanged.

Script selection
----------------

| File | Code runs in | RAM vector (.bss.ram.intvec) | Typical use |
|------|--------------|------------------------------|-------------|
| g32r502xc_cbus_flash.sct | CBUS Flash | Yes (configurable) | Peripherals, eval, boot, mathlib integration |
| g32r502xc_itcm_ram.sct | ITCM RAM | Yes (configurable) | Low-latency app code + NVIC |
| g32r502xc_cbus_flash_noramvector.sct | CBUS Flash | No | DSP/math library benchmarks |
| g32r502xc_itcm_ram_noramvector.sct | ITCM RAM | No | DSP/math library benchmarks |

Configuration Wizard shape
--------------------------

The common masters now expose:

  ITCM / DTCM RAM Configuration
    <o0> ITCM base, <o1> ITCM size, <o2> DTCM base, <o3> DTCM size

  CBUS Flash Configuration
    <o0> CBUS Flash base, <o1> CBUS Flash size
    <i> G32R502 has no ITCM Flash interface.

Existing Stack / Heap, Boot Status Snapshot, Generic RW/ZI Placement,
Vector Execution Region, and Code Execution Region controls remain unchanged.

Layout notes
------------

- G32R502 capacities remain fixed: 256 KB CBUS Flash, 16 KB ITCM RAM, 24 KB DTCM RAM.
- Generic RW/ZI values 0 / 1 / 2 keep their existing semantics.
- __VECTOR_REGION values 0 / 1 / 2 keep their existing semantics.
- The *_noramvector* masters remain the recommended choice for library / benchmark projects that do not use a RAM vector table.
- itcm_ram / itcm_ram_noramvector still require generic RW/ZI to stay in DTCM.

Copy into your project
----------------------

Each SDK example keeps its own copy under project/MDK|IAR|Eclipse/. Update the masters in this directory first, then run:

  python python_tools/linker_sync/g32r502_sync_linker_copies.py --apply

The sync tool updates matching project copies while preserving each project's stack / heap values and local Wizard edits.

See also: common/icf/readme.txt (IAR), common/ld/readme.txt (Eclipse).
