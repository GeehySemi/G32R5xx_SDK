================================================================================

  keil_dbg_tool - G32R5xx MDK Debug INI (r5xx_dbg.ini) SP/PC Updater

================================================================================

Target devices
--------------

  For Geehy G32R5xx series Cortex-M MCUs (e.g. G32R501, G32R502, and other
  R5xx parts using the same MDK debug flow).

  In this SDK, the debugger initialization file is named r502_dbg.ini; the same
  tool and INI layout apply to other G32R5xx SDK packages that ship this file.

Current release
---------------

  Version    : 1.1.2
  Build date : 2026-06-25
  Binary     : keil_dbg_tool.exe (standalone, no Python install required)

Purpose
-------

  After each MDK build, read MSP and PC from the linked AXF/ELF vector table
  and update r502_dbg.ini for Keil Debugger CPU setup (Set_SP_PC_Setup).

  Applies to standard ARM Cortex-M vector layout (offset 0 = MSP, offset 4 = PC)
  used across G32R5xx devices.

  - TOOL mode (default): this tool updates SP/PC literals in the INI after build.
  - Custom mode: user sets CUSTOM_VECTOR_ADDR in INI; tool skips file update.

Version history
---------------

  1.1.2 (2026-06-25)
    - TOOL mode with -r: apply INI SP/PC update before Compare report so
      post-build console reflects values after write (MATCH when update succeeds).

  1.1.1 (2026-06-08)
    - Default console output reduced to three lines: Firmware, INI, Compare.
    - Extended diagnostics available via optional verbose flag (see -h).

  1.1.0 (2026-06-08)
    - Read SP_PC_UPDATE_SOURCE from r502_dbg.ini (default: TOOL if missing).
    - Custom mode: no INI write; only mode detection (no address validation).
    - TOOL mode: skip INI update when MSP/PC already match firmware.
    - TOOL mode without -r: comment SP/PC; skip if already commented.
    - SDK r502_dbg.ini: PC/MSP Wizard + CUSTOM_VECTOR_ADDR (_RDWORD read).
    - Standalone keil_dbg_tool.exe via PyInstaller.

  1.0.0 beta 0.5 (2025-03-24)
    - Initial release: extract SP/PC from ELF, update or comment r502_dbg.ini.

MDK integration (After Make)
----------------------------

  Typical command in project.uvprojx UserProg2:

    ...\utilities\keil_dbg_tool\keil_dbg_tool -r -a "#L" -d .\r502_dbg.ini

  #L  = linker output (project.axf)
  -r  = update SP/PC when TOOL mode and values differ

Manual usage
------------

  Run keil_dbg_tool.exe -h for all options and descriptions.

  keil_dbg_tool.exe -v
      Show version and build date.

  keil_dbg_tool.exe -r -a <path\to\project.axf> -d <path\to\r502_dbg.ini>
      TOOL mode: compare and update INI if needed.

Example console output (TOOL, mismatch)
---------------------------------------

  [keil_dbg_tool] Firmware: MSP=0x20006000 PC=0x08001240
  [keil_dbg_tool] INI: MSP=0x20006000 PC=0x080010F0
  [keil_dbg_tool] Compare: MISMATCH (PC ini=0x080010F0 firmware=0x08001240)

Example console output (TOOL, match)
------------------------------------

  [keil_dbg_tool] Firmware: MSP=0x20006000 PC=0x08001264
  [keil_dbg_tool] INI: MSP=0x20006000 PC=0x08001264
  [keil_dbg_tool] Compare: MATCH

r502_dbg.ini modes (Configuration Wizard)
-----------------------------------------

  SP_PC_UPDATE_SOURCE = 0  (Tool)
      keil_dbg_tool maintains SP= / PC= in the if (SP_PC_UPDATE_SOURCE == 0) block.

  SP_PC_UPDATE_SOURCE = 1  (Custom vector address)
      Debugger reads:
        SP = _RDWORD(CUSTOM_VECTOR_ADDR);
        PC = _RDWORD(CUSTOM_VECTOR_ADDR + 4) - 1;
      Typical CUSTOM_VECTOR_ADDR (G32R5xx, part-dependent):
        0x08000000 (CBUS Flash), 0x00000000 (ITCM RAM).
      Set the address according to your part linker map / scatter file.

r502_dbg.ini template (published SDK)
-------------------------------------

  Published G32R502 SDK packages do NOT ship r502_dbg.ini under each
  example project/MDK folder. MDK projects still reference .\r502_dbg.ini
  (Initialization File / After Make). Users must copy the template once
  per project:

    copy utilities\keil_dbg_tool\r502_dbg.ini.template
         <example>\project\MDK\r502_dbg.ini

  Then build once so keil_dbg_tool updates SP/PC. Full steps:
  docs\getting_started\sdk_getting_started_zh.md (Section 5.1)
  docs\getting_started\sdk_getting_started_en.md (Section 5.1)

Directory layout
----------------

  keil_dbg_tool.exe         Release binary (use this from MDK)
  r502_dbg.ini.template     Template for user-local r502_dbg.ini
  readme.txt                This file
  build_exe.bat             Rebuild exe from source
  src\                      Python source, spec, developer README.md
  build\                    PyInstaller cache (optional cleanup)

Rebuild exe (developers)
------------------------

  1. pip install -r src\requirements.txt
  2. Run build_exe.bat
  3. See src\README.md for details and design doc path.

Design document
---------------

  docs\develop\keil_dbg_tool\keil_dbg_tool_pc_msp_design.md
  (G32R502 SDK reference; concepts apply to other G32R5xx packages.)

================================================================================
