/*!
 * @file        g32r501xy_cbus_flash_secure.ld
 * @brief       G32R501 linker script (Eclipse / llvm-lld) - xy CBUS Flash secure
 * @version     V1.0.2
 * @date        2026-08-11
 *
 * LAYOUT SUMMARY (read this if the filename is unclear)
 * -------------------------------------------------------
 * Template ID : CF-V0-R0-SEC
 * Code exec   : Secure CBUS Flash 0x08000000 (320 KB)
 * RAM vector  : DTCM 0x20000000..0x200003FF (.bss.ram.intvec)
 * Generic RW  : bit-mask pool (default all banks)
 * Stack/heap  : DTCM top (stack 0x00001000, heap 0x00000000)
 *
 * Generic RW/ZI: multi-region pool (lld --enable-non-contiguous-regions);
 * Eclipse must pass -Wl,--enable-non-contiguous-regions.
 * MDK/IAR equivalent:
 *   __VECTOR_REGION / __RWZI_BANK match this master defaults
 */

/*---------------------- Flash Configuration ----------------------------------
  <h> Flash Configuration
    <o0> Flash / CBUS / ITCM Flash bases and sizes (family-specific)
  </h>
  ----------------------------------------------------------------------------*/

__CBUS_FLASH_BASE = 0x08000000;
__CBUS_FLASH_SIZE = 0x00050000;
__UNSECURE_FLASH_BASE = 0x08050000;
__UNSECURE_FLASH_SIZE = 0x00050000;
__ITCM_FLASH_BASE = 0x00000000;
__ITCM_FLASH_SIZE = 0x00000000;

/*--------------------- Embedded RAM Configuration ----------------------------
  <h> RAM Configuration
    <o0> ITCM / DTCM physical base and size (family-specific)
  </h>
 ----------------------------------------------------------------------------*/

__CPU0_ITCM_RAM_BASE = 0x00000000;
__CPU0_ITCM_RAM_SIZE = 0x00010000;
__DTCM_PHYS_BASE = 0x20000000;
__DTCM_PHYS_SIZE = 0x00004000;

__SRAM1_BASE = 0x20100000;
__SRAM1_SIZE = 0x00002000;
__SRAM2_BASE = 0x20200000;
__SRAM2_SIZE = 0x00002000;
__SRAM3_BASE = 0x20300000;
__SRAM3_SIZE = 0x00008000;

__SRAM1_ENABLED = 1;
__SRAM2_ENABLED = 1;
__SRAM3_ENABLED = 1;
/*--------------------- Stack / Heap Configuration ----------------------------
  <h> Stack / Heap Configuration
    <o0> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
    <o1> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
  -----------------------------------------------------------------------------*/
__STACK_SIZE = 0x00001000;
__HEAP_SIZE  = 0x00000000;

__BOOT_STATUS_SNAPSHOT_ENABLE = 0;
__BOOT_STATUS_SNAPSHOT_SIZE = __BOOT_STATUS_SNAPSHOT_ENABLE * 0x20;

__VECTOR_REGION = 0;
__VECTOR_SIZE = 0x00000400;
__RESERVED_VECTOR_SIZE = __VECTOR_SIZE;
__RWZI_BANK = 0x0000001F;

ASSERT((__RWZI_BANK & 0x1F) != 0, "__RWZI_BANK must select a bank");
ASSERT(((__RWZI_BANK & 0x04) == 0) || (__SRAM1_ENABLED != 0), "RWZI SRAM1 bit without ENABLE");
ASSERT(((__RWZI_BANK & 0x08) == 0) || (__SRAM2_ENABLED != 0), "RWZI SRAM2 bit without ENABLE");
ASSERT(((__RWZI_BANK & 0x10) == 0) || (__SRAM3_ENABLED != 0), "RWZI SRAM3 bit without ENABLE");
__DTCM_PHYS_TOP = __DTCM_PHYS_BASE + __DTCM_PHYS_SIZE;
__DTCM_RW_SIZE = __DTCM_PHYS_SIZE - __RESERVED_VECTOR_SIZE - __STACK_SIZE - __HEAP_SIZE - __BOOT_STATUS_SNAPSHOT_SIZE;
__STACK_TOP_ADDR = __DTCM_PHYS_TOP - __BOOT_STATUS_SNAPSHOT_SIZE;
__BOOT_STATUS_SNAPSHOT_BASE = __DTCM_PHYS_TOP - __BOOT_STATUS_SNAPSHOT_SIZE;

MEMORY
{
  FLASH    (rx)  : ORIGIN = __CBUS_FLASH_BASE, LENGTH = __CBUS_FLASH_SIZE /* secure code/const */
  UNSECURE_FLASH (rx) : ORIGIN = __UNSECURE_FLASH_BASE, LENGTH = __UNSECURE_FLASH_SIZE /* unsecure window */
  ITCM_RAM (rwx) : ORIGIN = __CPU0_ITCM_RAM_BASE, LENGTH = __CPU0_ITCM_RAM_SIZE /* custom itcm.* */
  VECTOR_RAM (rwx) : ORIGIN = __DTCM_PHYS_BASE, LENGTH = __RESERVED_VECTOR_SIZE /* .bss.ram.intvec */
  DTCM_RAM (rwx) : ORIGIN = __DTCM_PHYS_BASE + __RESERVED_VECTOR_SIZE, LENGTH = __DTCM_RW_SIZE /* RW/ZI after vector */
  DTCM_STACK (rwx) : ORIGIN = __STACK_TOP_ADDR - __STACK_SIZE, LENGTH = __STACK_SIZE + __BOOT_STATUS_SNAPSHOT_SIZE /* stack at DTCM top */
  SRAM1      (rwx) : ORIGIN = __SRAM1_BASE, LENGTH = __SRAM1_SIZE /* sram1.share_data */
  SRAM2      (rwx) : ORIGIN = __SRAM2_BASE, LENGTH = __SRAM2_SIZE /* sram2.share_data */
  SRAM3      (rwx) : ORIGIN = __SRAM3_BASE, LENGTH = __SRAM3_SIZE /* sram3.share_data */
}


/*
 * It defines following symbols (CMSIS-style), usable without definition:
 *   __exidx_start / __exidx_end
 *   __copy_table_start__ / __copy_table_end__
 *   __zero_table_start__ / __zero_table_end__
 *   __data_start__ / __data_end__ / __bss_start__ / __bss_end__
 *   __HeapLimit / __StackLimit / __StackTop / __stack
 *   __cpu1_image_start__ / __cpu1_image_end__ (when CPU1 stub present)
 */
ENTRY(Reset_Handler)

SECTIONS
{
  .text :
  {
    KEEP(*(.vectors))
    KEEP(*(RESET))
    *(.text*)
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
  } > FLASH

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > FLASH

  __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } > FLASH
  __exidx_end = .;

  .copy.table :
  {
    . = ALIGN(4);
    __copy_table_start__ = .;
    LONG(LOADADDR(.data))
    LONG(ADDR(.data))
    LONG(SIZEOF(.data) / 4)
    LONG(LOADADDR(.data_itcm))
    LONG(ADDR(.data_itcm))
    LONG(SIZEOF(.data_itcm) / 4)
    LONG(LOADADDR(.data_sram1))
    LONG(ADDR(.data_sram1))
    LONG(SIZEOF(.data_sram1) / 4)
    LONG(LOADADDR(.data_sram2))
    LONG(ADDR(.data_sram2))
    LONG(SIZEOF(.data_sram2) / 4)
    LONG(LOADADDR(.data_sram3))
    LONG(ADDR(.data_sram3))
    LONG(SIZEOF(.data_sram3) / 4)
    LONG(LOADADDR(.itcm_custom_section))
    LONG(ADDR(.itcm_custom_section))
    LONG(SIZEOF(.itcm_custom_section) / 4)
    LONG(LOADADDR(.dtcm.data))
    LONG(ADDR(.dtcm.data))
    LONG(SIZEOF(.dtcm.data) / 4)
    LONG(LOADADDR(.sram1.share_data))
    LONG(ADDR(.sram1.share_data))
    LONG(SIZEOF(.sram1.share_data) / 4)
    LONG(LOADADDR(.sram2.share_data))
    LONG(ADDR(.sram2.share_data))
    LONG(SIZEOF(.sram2.share_data) / 4)
    LONG(LOADADDR(.sram3.share_data))
    LONG(ADDR(.sram3.share_data))
    LONG(SIZEOF(.sram3.share_data) / 4)
    __copy_table_end__ = .;
  } > FLASH

  .zero.table :
  {
    . = ALIGN(4);
    __zero_table_start__ = .;
    LONG(ADDR(.bss))
    LONG(SIZEOF(.bss) / 4)
    LONG(ADDR(.bss_itcm))
    LONG(SIZEOF(.bss_itcm) / 4)
    LONG(ADDR(.bss_sram1))
    LONG(SIZEOF(.bss_sram1) / 4)
    LONG(ADDR(.bss_sram2))
    LONG(SIZEOF(.bss_sram2) / 4)
    LONG(ADDR(.bss_sram3))
    LONG(SIZEOF(.bss_sram3) / 4)
    LONG(ADDR(.dtcm.bss))
    LONG(SIZEOF(.dtcm.bss) / 4)
    __zero_table_end__ = .;
  } > FLASH

  PROVIDE(__etext = LOADADDR(.data));

  /* RAM vector table (NOLOAD); VTOR target when REGION=0/1 */
  .ram.intvec (NOLOAD) :
  {
    . = ALIGN(__VECTOR_SIZE);
    __ram_intvec_start__ = .;
    KEEP(*(.bss.ram.intvec))
    KEEP(*(ram.intvec))
    . = ALIGN(4);
    __ram_intvec_end__ = .;
  } > VECTOR_RAM


  .itcm_custom_section : ALIGN(4)
  {
    __itcm_custom_section_start__ = .;
    *(itcm.instruction)
    *(itcm.ramfunc)
    . = ALIGN(4);
    __itcm_custom_section_end__ = .;
  } > ITCM_RAM AT > FLASH

  .dtcm.data : ALIGN(4)
  {
    __dtcm_data_start__ = .;
    *(dtcm.data)
    . = ALIGN(4);
    __dtcm_data_end__ = .;
  } > DTCM_RAM AT > FLASH

  .dtcm.bss (NOLOAD) :
  {
    . = ALIGN(4);
    __dtcm_bss_start__ = .;
    *(dtcm.bss)
    . = ALIGN(4);
    __dtcm_bss_end__ = .;
  } > DTCM_RAM

  .sram1.share_data : ALIGN(4)
  {
    __sram1_share_data_start__ = .;
    *(sram1.share_data)
    . = ALIGN(4);
    __sram1_share_data_end__ = .;
  } > SRAM1 AT > FLASH

  .sram2.share_data : ALIGN(4)
  {
    __sram2_share_data_start__ = .;
    *(sram2.share_data)
    . = ALIGN(4);
    __sram2_share_data_end__ = .;
  } > SRAM2 AT > FLASH

  .sram3.share_data : ALIGN(4)
  {
    __sram3_share_data_start__ = .;
    *(sram3.share_data)
    . = ALIGN(4);
    __sram3_share_data_end__ = .;
  } > SRAM3 AT > FLASH
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
  } > DTCM_RAM AT > FLASH

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

  .data_itcm : ALIGN(4)
  {
    __data_itcm_start__ = .;
    *(.data)
    *(.data.*)
    . = ALIGN(4);
    __data_itcm_end__ = .;
  } > ITCM_RAM AT > FLASH

  .data_sram1 : ALIGN(4)
  {
    __data_sram1_start__ = .;
    *(.data)
    *(.data.*)
    . = ALIGN(4);
    __data_sram1_end__ = .;
  } > SRAM1 AT > FLASH

  .data_sram2 : ALIGN(4)
  {
    __data_sram2_start__ = .;
    *(.data)
    *(.data.*)
    . = ALIGN(4);
    __data_sram2_end__ = .;
  } > SRAM2 AT > FLASH

  .data_sram3 : ALIGN(4)
  {
    __data_sram3_start__ = .;
    *(.data)
    *(.data.*)
    . = ALIGN(4);
    __data_sram3_end__ = .;
  } > SRAM3 AT > FLASH

  .bss_itcm (NOLOAD) :
  {
    . = ALIGN(4);
    __bss_itcm_start__ = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_itcm_end__ = .;
  } > ITCM_RAM

  .bss_sram1 (NOLOAD) :
  {
    . = ALIGN(4);
    __bss_sram1_start__ = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_sram1_end__ = .;
  } > SRAM1

  .bss_sram2 (NOLOAD) :
  {
    . = ALIGN(4);
    __bss_sram2_start__ = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_sram2_end__ = .;
  } > SRAM2

  .bss_sram3 (NOLOAD) :
  {
    . = ALIGN(4);
    __bss_sram3_start__ = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_sram3_end__ = .;
  } > SRAM3


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
  ASSERT((__StackLimit - __HeapLimit) >= 0, "region DTCM_RAM overflowed with stack")
}
