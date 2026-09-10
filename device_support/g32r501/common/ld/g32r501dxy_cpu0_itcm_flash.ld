/*!
 * @file        g32r501dxy_cpu0_itcm_flash.ld
 *
 * @brief       Linker script for G32R501 series
 *              640Kbytes FLASH, 128KByte RAM
 *
 * @version     V1.0.0
 *
 * @date        2025-01-15
 *
 * @attention
 *
 *  Copyright (C) 2025 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/*
 *-------- <<< Use Configuration Wizard in Context Menu >>> -------------------
 */

/*---------------------- Flash Configuration ----------------------------------
  <h> Flash Configuration
    <o0> Flash Base Address <0x0-0xFFFFFFFF:8>
    <o1> Flash Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
  -----------------------------------------------------------------------------*/
__CPU0_CBUS_ROM_BASE = 0x0;
__CPU0_CBUS_ROM_SIZE = 0x0;
__CPU1_CBUS_ROM_BASE = 0x0;
__CPU1_CBUS_ROM_SIZE = 0x0;
__CPU0_ITCM_ROM_BASE = 0x00100000;
__CPU0_ITCM_ROM_SIZE = 0x00050000;
__CPU1_ITCM_ROM_BASE = 0x00150000;
__CPU1_ITCM_ROM_SIZE = 0x00050000;

/*--------------------- Embedded RAM Configuration ----------------------------
  <h> RAM Configuration
    <o0> RAM Base Address    <0x0-0xFFFFFFFF:8>
    <o1> RAM Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
 -----------------------------------------------------------------------------*/
__CPU0_ITCM_RAM_BASE = 0x00000000;
__CPU0_ITCM_RAM_SIZE = 0x0000C000;
__CPU0_DTCM_RAM_BASE = 0x20000000;
__CPU0_DTCM_RAM_SIZE = 0x00004000;
__CPU1_ITCM_RAM_BASE = 0x00000000;
__CPU1_ITCM_RAM_SIZE = 0x00000000;
__CPU1_DTCM_RAM_BASE = 0x20000000;
__CPU1_DTCM_RAM_SIZE = 0x00000000;

__SRAM1_BASE = 0x20100000;
__SRAM1_SIZE = 0x00002000;
__SRAM2_BASE = 0x20200000;
__SRAM2_SIZE = 0x00002000;
__SRAM3_BASE = 0x20300000;
__SRAM3_SIZE = 0x00008000;


/*--------------------- Stack / Heap Configuration ----------------------------
  <h> Stack / Heap Configuration
    <o0> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
    <o1> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
  </h>
  -----------------------------------------------------------------------------*/
__STACK_SIZE = 0x0001000;
__HEAP_SIZE  = 0x0000000;

/*
 *-------------------- <<< end of configuration section >>> -------------------
 */

/* ARMv8-M stack sealing:
   to use ARMv8-M stack sealing set __STACKSEAL_SIZE to 8 otherwise keep 0
 */
__STACKSEAL_SIZE = 8;


MEMORY
{
  CPU0_FLASH    (rx)  : ORIGIN = __CPU0_ITCM_ROM_BASE, LENGTH = __CPU0_ITCM_ROM_SIZE
  CPU1_FLASH    (rx)  : ORIGIN = __CPU1_ITCM_ROM_BASE, LENGTH = __CPU1_ITCM_ROM_SIZE
  CPU0_ITCM_RAM (rwx) : ORIGIN = __CPU0_ITCM_RAM_BASE, LENGTH = __CPU0_ITCM_RAM_SIZE
  CPU0_DTCM_RAM (rwx) : ORIGIN = __CPU0_DTCM_RAM_BASE, LENGTH = __CPU0_DTCM_RAM_SIZE
  SRAM1         (rwx) : ORIGIN = __SRAM1_BASE, LENGTH = __SRAM1_SIZE
  SRAM2         (rwx) : ORIGIN = __SRAM2_BASE, LENGTH = __SRAM2_SIZE
  SRAM3         (rwx) : ORIGIN = __SRAM3_BASE, LENGTH = __SRAM3_SIZE
}

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext          (deprecated)
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __StackSeal      (only if ARMv8-M stack sealing is used)
 */
ENTRY(Reset_Handler)

SECTIONS
{
  /* section for storing the cpu1 core image */
  .cpu1_code :
  {
    . = ALIGN(4) ;
    __cpu1_image_start__ = .;

    KEEP (*(cpu1_code))
    *(cpu1_code*)

    . = ALIGN(4) ;
    __cpu1_image_end__ = .;
  } > CPU1_FLASH

  .text :
  {
    KEEP(*(.vectors))
    *(.text*)

    KEEP(*(.init))
    KEEP(*(.fini))

    /* .ctors */
    *crtbegin.o(.ctors)
    *crtbegin?.o(.ctors)
    *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
    *(SORT(.ctors.*))
    *(.ctors)

    /* .dtors */
    *crtbegin.o(.dtors)
    *crtbegin?.o(.dtors)
    *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
    *(SORT(.dtors.*))
    *(.dtors)

    *(.rodata*)

    KEEP(*(.eh_frame*))
  } > CPU0_FLASH

  /*
   * SG veneers:
   * All SG veneers are placed in the special output section .gnu.sgstubs. Its start address
   * must be set, either with the command line option '--section-start' or in a linker script,
   * to indicate where to place these veneers in memory.
   */
/*
  .gnu.sgstubs :
  {
    . = ALIGN(32);
  } > CPU0_FLASH
*/
  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > CPU0_FLASH

  __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } > CPU0_FLASH
  __exidx_end = .;

  .copy.table :
  {
    . = ALIGN(4);
    __copy_table_start__ = .;

    LONG (LOADADDR(.data))
    LONG (ADDR(.data))
    LONG (SIZEOF(.data) / 4)

    LONG (LOADADDR(.itcm_custom_section))
    LONG (ADDR(.itcm_custom_section))
    LONG (SIZEOF(.itcm_custom_section) / 4)

    LONG (LOADADDR(.dtcm.data))
    LONG (ADDR(.dtcm.data))
    LONG (SIZEOF(.dtcm.data) / 4)

    LONG (LOADADDR(.sram1.share_data))
    LONG (ADDR(.sram1.share_data))
    LONG (SIZEOF(.sram1.share_data) / 4)

    LONG (LOADADDR(.sram2.share_data))
    LONG (ADDR(.sram2.share_data))
    LONG (SIZEOF(.sram2.share_data) / 4)

    LONG (LOADADDR(.sram3.share_data))
    LONG (ADDR(.sram3.share_data))
    LONG (SIZEOF(.sram3.share_data) / 4)

    /* Add each additional data section here */
/*
    LONG (LOADADDR(.data2))
    LONG (ADDR(.data2))
    LONG (SIZEOF(.data2) / 4)
*/
    __copy_table_end__ = .;
  } > CPU0_FLASH

  .zero.table :
  {
    . = ALIGN(4);
    __zero_table_start__ = .;

    LONG (ADDR(.bss))
    LONG (SIZEOF(.bss) / 4)

    LONG (ADDR(.dtcm.bss))
    LONG (SIZEOF(.dtcm.bss) / 4)

    /* Add each additional bss section here */
/*
    LONG (ADDR(.bss2))
    LONG (SIZEOF(.bss2) / 4)
*/
    __zero_table_end__ = .;
  } > CPU0_FLASH

  /*
   * This __etext variable is kept for backward compatibility with older,
   * ASM based startup files.
   */
  PROVIDE(__etext = LOADADDR(.data));

  .data : ALIGN(4)
  {
    __data_load__ = LOADADDR(.data);
    __data_start__ = .;
    *(vtable)
    *(.data)
    *(.data.*)

    . = ALIGN(4);
    /* preinit data */
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP(*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);

    . = ALIGN(4);
    /* init data */
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    PROVIDE_HIDDEN (__init_array_end = .);

    . = ALIGN(4);
    /* finit data */
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array))
    PROVIDE_HIDDEN (__fini_array_end = .);

    KEEP(*(.jcr*))
    . = ALIGN(4);
    /* All data end */
    __data_end__ = .;

  } > CPU0_ITCM_RAM AT > CPU0_FLASH

  /*
   * Secondary data section, optional
   *
   * Remember to add each additional data section
   * to the .copy.table above to assure proper
   * initialization during startup.
   */
/*
  .data2 : ALIGN(4)
  {
    . = ALIGN(4);
    __data2_start__ = .;
    *(.data2)
    *(.data2.*)
    . = ALIGN(4);
    __data2_end__ = .;

  } > CPU0_DTCM_RAM AT > CPU0_FLASH
*/

  .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > CPU0_ITCM_RAM AT > CPU0_ITCM_RAM

  /*
   * Secondary bss section, optional
   *
   * Remember to add each additional bss section
   * to the .zero.table above to assure proper
   * initialization during startup.
   */
/*
  .bss2 :
  {
    . = ALIGN(4);
    __bss2_start__ = .;
    *(.bss2)
    *(.bss2.*)
    . = ALIGN(4);
    __bss2_end__ = .;
  } > CPU0_DTCM_RAM AT > CPU0_DTCM_RAM
*/

  .itcm_custom_section :
  {
    . = ALIGN(4);
    __itcm_custom_section_start__ = .;
    *(itcm.instruction)
    *(itcm.ramfunc)
    . = ALIGN(4);
    __itcm_custom_section_end__ = .;
  } > CPU0_ITCM_RAM AT > CPU0_FLASH

  .dtcm.data :
  {
    . = ALIGN(4);
    __dtcm_data_start__ = .;
    *(dtcm.data)
    . = ALIGN(4);
    __dtcm_data_end__ = .;
  } > CPU0_DTCM_RAM AT > CPU0_FLASH

  .dtcm.bss (NOLOAD) :
  {
    . = ALIGN(4);
    __dtcm_bss_start__ = .;
    *(dtcm.bss)
    . = ALIGN(4);
    __dtcm_bss_end__ = .;
  } > CPU0_DTCM_RAM AT > CPU0_DTCM_RAM

  .sram1.share_data :
  {
    . = ALIGN(4);
    __sram1_share_data_start__ = .;
    *(sram1.share_data)
    . = ALIGN(4);
    __sram1_share_data_end__ = .;
  } > SRAM1 AT > CPU0_FLASH

  .sram2.share_data :
  {
    . = ALIGN(4);
    __sram2_share_data_start__ = .;
    *(sram2.share_data)
    . = ALIGN(4);
    __sram2_share_data_end__ = .;
  } > SRAM2 AT > CPU0_FLASH

  .sram3.share_data :
  {
    . = ALIGN(4);
    __sram3_share_data_start__ = .;
    *(sram3.share_data)
    . = ALIGN(4);
    __sram3_share_data_end__ = .;
  } > SRAM3 AT > CPU0_FLASH

  .heap (NOLOAD) :
  {
    . = ALIGN(8);
    __end__ = .;
    PROVIDE(end = .);
    . = . + __HEAP_SIZE;
    . = ALIGN(8);
    __HeapLimit = .;
  } > CPU0_DTCM_RAM

  .stack (ORIGIN(CPU0_DTCM_RAM) + LENGTH(CPU0_DTCM_RAM) - __STACK_SIZE - __STACKSEAL_SIZE) (NOLOAD) :
  {
    . = ALIGN(8);
    __StackLimit = .;
    PROVIDE(__stack_limit = .);
    . = . + __STACK_SIZE;
    . = ALIGN(8);
    __StackTop = .;
  } > CPU0_DTCM_RAM
  PROVIDE(__stack = __StackTop);

  /* ARMv8-M stack sealing:
     to use ARMv8-M stack sealing uncomment '.stackseal' section
   */
/*
  .stackseal (ORIGIN(CPU0_DTCM_RAM) + LENGTH(CPU0_DTCM_RAM) - __STACKSEAL_SIZE) (NOLOAD) :
  {
    . = ALIGN(8);
    __StackSeal = .;
    PROVIDE(__stack_seal = .);
    . = . + 8;
    . = ALIGN(8);
  } > CPU0_DTCM_RAM
*/

  /* Check if data + heap + stack exceeds RAM limit */
  ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
}
