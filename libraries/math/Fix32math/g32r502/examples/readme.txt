FILE:    readme.txt
TITLE:   Fix32math examples - code region and linker notes
VERSION: 1.0.0
DATE:    2026-06-30

Fix32math Examples - Code Execution Region
============================================================

Overview
------------------------------------------------------------
Application code for every example below is linked to CBUS Flash
(0x08000000) on MDK, IAR, and Eclipse.
Linker scripts: g32r502xc_cbus_flash_noramvector.sct /
g32r502xcx7_cbus_flash_noramvector.icf / g32r502xc_cbus_flash_noramvector.ld.

Interrupt / RAM vector table
------------------------------------------------------------
These examples use *_noramvector.* scripts. They do NOT reserve RAM for
.bss.ram.intvec and do not use Interrupt_initVectorTable().

Examples are for benchmark and library validation only. For product
firmware with NVIC interrupts, use general linker templates and follow:

  driverlib/g32r502/examples/eval/empty_projects/empty_mathlib_project

See device_support/g32r502/common/{sct,icf,ld}/readme.txt.

Examples
------------------------------------------------------------
No.  Example                                 
------------------------------------------------------------
1    Fix32math_sample                        
------------------------------------------------------------
