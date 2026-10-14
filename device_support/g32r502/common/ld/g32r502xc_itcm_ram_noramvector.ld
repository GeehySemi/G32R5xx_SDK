/*!
 * @file        g32r502xc_itcm_ram_noramvector.ld
 * @brief       G32R502 linker script (Eclipse / llvm-lld)
 * @version     V1.0.0
 * @date        2026-08-10
 *
 * LAYOUT SUMMARY (read this if the filename is unclear)
 * -------------------------------------------------------
 * Template ID : IR-NV-R0
 * Code exec   : ITCM RAM 0x00000000 (16 KB)
 * RAM vector  : None (no .ram.intvec section)
 * Generic RW  : DTCM (.data / .bss / .heap) [ITCM code exec: generic RW fixed in DTCM]
 * ITCM custom : itcm.instruction, itcm.ramfunc (always ITCM)
 * DTCM custom : dtcm.data, dtcm.bss (always DTCM)
 * Stack/heap  : DTCM top (default stack 0x400)
 *
 * MDK/IAR equivalent:
 *   __VECTOR_REGION = 2, __RWZI_BANK = 0
 *   (IAR: __vector_region__ = 2, __ICFEDIT_rwzi_bank__ = 0)
 *
 * Do not edit layout here; pick another _template file or change
 * stack/heap/snapshot Wizard values only.
 */

/*---------------------- Flash Configuration ----------------------------------
  <h> Flash Configuration
    <o0> CBUS Flash Base Address <0x0-0xFFFFFFFF:8>
    <o1> CBUS Flash Size (in Bytes) <0x0-0xFFFFFFFF:8>
    <i> G32R502 has no ITCM Flash interface.
  </h>
  ----------------------------------------------------------------------------*/
__CBUS_FLASH_BASE = 0x08000000;
__CBUS_FLASH_SIZE = 0x00040000;

/*--------------------- Embedded RAM Configuration ----------------------------
  <h> Embedded RAM Configuration
    <o0> ITCM Base Address <0x0-0xFFFFFFFF:8>
    <o1> ITCM Size (in Bytes) <0x0-0xFFFFFFFF:8>
    <o2> DTCM Base Address <0x0-0xFFFFFFFF:8>
    <o3> DTCM Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
  ----------------------------------------------------------------------------*/
__ITCM_RAM_BASE   = 0x00000000;
__ITCM_RAM_SIZE   = 0x00004000;
__DTCM_PHYS_BASE = 0x20000000;
__DTCM_PHYS_SIZE = 0x00006000;

/*--------------------- Stack / Heap Configuration ----------------------------
  <h> Stack / Heap Configuration
    <o0> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
    <o1> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
  -----------------------------------------------------------------------------*/
__STACK_SIZE = 0x00000400;
__HEAP_SIZE  = 0x00000000;

__BOOT_STATUS_SNAPSHOT_ENABLE = 0;
__BOOT_STATUS_SNAPSHOT_SIZE = __BOOT_STATUS_SNAPSHOT_ENABLE * 0x20;

__VECTOR_REGION = 2;
__VECTOR_SIZE = 0x00000400;
__RESERVED_VECTOR_SIZE = 0;

__DTCM_PHYS_TOP = __DTCM_PHYS_BASE + __DTCM_PHYS_SIZE;
__DTCM_RW_SIZE = __DTCM_PHYS_SIZE - __STACK_SIZE - __HEAP_SIZE - __BOOT_STATUS_SNAPSHOT_SIZE;
__STACK_TOP_ADDR = __DTCM_PHYS_TOP - __BOOT_STATUS_SNAPSHOT_SIZE;
__BOOT_STATUS_SNAPSHOT_BASE = __DTCM_PHYS_TOP - __BOOT_STATUS_SNAPSHOT_SIZE;

/* Region summary:
 *   FLASH      : image / loadable readonly
 *   ITCM_RAM   : code / const
 *   DTCM_RAM   : generic RW/ZI and dtcm.*
 *   DTCM_STACK : stack / optional boot snapshot
 */
MEMORY
{
  FLASH    (rx)  : ORIGIN = __CBUS_FLASH_BASE, LENGTH = __CBUS_FLASH_SIZE
  ITCM_RAM (rwx) : ORIGIN = __ITCM_RAM_BASE, LENGTH = __ITCM_RAM_SIZE
  DTCM_RAM (rwx) : ORIGIN = __DTCM_PHYS_BASE, LENGTH = __DTCM_RW_SIZE
  DTCM_STACK (rwx) : ORIGIN = __STACK_TOP_ADDR - __STACK_SIZE, LENGTH = __STACK_SIZE + __BOOT_STATUS_SNAPSHOT_SIZE
}

ENTRY(Reset_Handler)

SECTIONS
{
  .text :
  {
    KEEP(*(.vectors))
    KEEP(*(RESET))
    *(.text*)
    *(itcm.instruction)
    *(itcm.ramfunc)
    KEEP(*(.init))
    KEEP(*(.fini))
    *crtbegin.o(.ctors)
    *crtbegin?.o(.ctors)
    *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
    *(SORT(.ctors.*))
    *(.ctors)
    *crtbegin.o(.dtors)
    *crtbegin?.o(.dtors)
    *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
    *(SORT(.dtors.*))
    *(.dtors)
    *(.rodata*)
    KEEP(*(.eh_frame*))
  } > ITCM_RAM

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > ITCM_RAM

  __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } > ITCM_RAM
  __exidx_end = .;

  .copy.table :
  {
    . = ALIGN(4);
    __copy_table_start__ = .;
    LONG(LOADADDR(.data))
    LONG(ADDR(.data))
    LONG(SIZEOF(.data) / 4)
    LONG(LOADADDR(.dtcm.data))
    LONG(ADDR(.dtcm.data))
    LONG(SIZEOF(.dtcm.data) / 4)
    __copy_table_end__ = .;
  } > ITCM_RAM

  .zero.table :
  {
    . = ALIGN(4);
    __zero_table_start__ = .;
    LONG(ADDR(.bss))
    LONG(SIZEOF(.bss) / 4)
    LONG(ADDR(.dtcm.bss))
    LONG(SIZEOF(.dtcm.bss) / 4)
    __zero_table_end__ = .;
  } > ITCM_RAM

  PROVIDE(__etext = LOADADDR(.data));

  .data : ALIGN(4)
  {
    __data_load__ = LOADADDR(.data);
    __data_start__ = .;
    *(vtable)
    *(.data)
    *(.data.*)
    . = ALIGN(4);
    PROVIDE_HIDDEN(__preinit_array_start = .);
    KEEP(*(.preinit_array))
    PROVIDE_HIDDEN(__preinit_array_end = .);
    . = ALIGN(4);
    PROVIDE_HIDDEN(__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    PROVIDE_HIDDEN(__init_array_end = .);
    . = ALIGN(4);
    PROVIDE_HIDDEN(__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array))
    PROVIDE_HIDDEN(__fini_array_end = .);
    KEEP(*(.jcr*))
    . = ALIGN(4);
    __data_end__ = .;
  } > DTCM_RAM AT > ITCM_RAM

  .bss (NOLOAD) :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > DTCM_RAM

  .dtcm.data : ALIGN(4)
  {
    __dtcm_data_start__ = .;
    *(dtcm.data)
    . = ALIGN(4);
    __dtcm_data_end__ = .;
  } > DTCM_RAM AT > ITCM_RAM

  .dtcm.bss (NOLOAD) :
  {
    . = ALIGN(4);
    __dtcm_bss_start__ = .;
    *(dtcm.bss)
    . = ALIGN(4);
    __dtcm_bss_end__ = .;
  } > DTCM_RAM

  .heap (NOLOAD) :
  {
    . = ALIGN(8);
    __end__ = .;
    PROVIDE(end = .);
    . = . + __HEAP_SIZE;
    . = ALIGN(8);
    __HeapLimit = .;
  } > DTCM_RAM

  .stack (NOLOAD) :
  {
    . = ALIGN(8);
    __StackLimit = .;
    PROVIDE(__stack_limit = .);
    . = . + __STACK_SIZE;
    . = ALIGN(8);
    __StackTop = .;
  } > DTCM_STACK

  .boot_status_snapshot (NOLOAD) :
  {
    . = . + __BOOT_STATUS_SNAPSHOT_SIZE;
  } > DTCM_STACK

  PROVIDE(__stack = __StackTop);
  PROVIDE(__INITIAL_SP = __StackTop);
  PROVIDE(__STACK_LIMIT = __StackLimit);

  ASSERT(__StackTop == __STACK_TOP_ADDR, "region DTCM stack top must match __DTCM_PHYS_TOP - snapshot")
  ASSERT(__BOOT_STATUS_SNAPSHOT_SIZE == 0 || ADDR(.boot_status_snapshot) == __BOOT_STATUS_SNAPSHOT_BASE, "boot status snapshot must anchor at DTCM physical top")
  ASSERT(__StackLimit >= __HeapLimit, "region DTCM_RAM overflowed with stack")
}
