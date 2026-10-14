G32R501 J-Link Device Support
=============================

VERSION: 1.0.0

DATE:    2026-08-30

This folder provides SEGGER J-Link device definitions for the Geehy G32R501
(Cortex-M52) series. After installation, J-Link tools can select G32R501
parts without manually specifying a .jlinkscript in each project.

Contents
--------
  G32R501.xml
      Device database (chip list, flash banks, work RAM, script binding).

  Geehy_G32R501_ConnectCore.jlinkscript
      Connect/reset script (DCS unlock, CPU/peripheral init after reset).

  readme.txt
      This file.

Supported device names (subset aligned with G32R5xx DFP)
--------------------------------------------------------
  Single-core: G32R501VY / MY / RY / NY / RC
  Dual-core:   G32R501DVY / DMY / DRY / DNY

  G32R501RC is retained for special-order use. Other 256 KB catalog names
  are no longer listed.

Flash (G32R501.xml):
  CBUS @ 0x08000000 — 640 KB on catalog *Y / D*Y parts; 256 KB on G32R501RC
  ITCM @ 0x00100000 — optional bank on catalog *Y / D*Y parts (640 KB max)
Flash algorithm RAM (WorkRAM in G32R501.xml): 0x20300000, size 0x4000
FLM: G32R5xx_Program_Algorithm.FLM from DFP Flash\G32R5xx_Program_Algorithm.FLM

Requirements
------------
  - SEGGER J-Link software that supports Cortex-M52
    (reference: J-Link V7.94g or later; newer versions recommended).
  - J-Link probe V12 or later is recommended for M52.
    The script presets Cortex-M55 for J-Link AP scan compatibility.

Install (Windows)
-----------------
1. Copy the following files into one folder:

     %APPDATA%\SEGGER\JLinkDevices\Geehy\G32R501\

   Example full path:

     C:\Users\<YourUserName>\AppData\Roaming\SEGGER\JLinkDevices\Geehy\G32R501\

   Files to copy:
     - G32R501.xml
     - Geehy_G32R501_ConnectCore.jlinkscript
     - G32R5xx_Program_Algorithm.FLM   (from DFP: Flash\G32R5xx_Program_Algorithm.FLM)

2. Restart J-Link tools (J-Flash, Ozone, IDE debug session, JLink.exe) so the
   new device database is reloaded.

Install (Linux / macOS)
-----------------------
Copy the same three files to:

  $HOME/.config/SEGGER/JLinkDevices/Geehy/G32R501/

(or the JLinkDevices path shown in SEGGER documentation for your OS).

Verify
------
1. Open J-Link Commander (JLink.exe) or J-Flash.
2. Enter:  device ?
3. Confirm G32R501RC (and inherited *Y / D*Y parts) appear under vendor Geehy.
4. Connect to the target board and run program/erase once to confirm DCS
   unlock and flash programming work.

IDE usage notes
---------------
MDK (Keil)
  - Select device G32R501VY / DVY (or matching part); use G32R501RC only when
    required.
  - Debugger: J-Link / Cortex-M.
  - No need to copy .jlinkscript into the project folder if this package is
    installed; G32R501.xml binds the script automatically.
  - Use r501_dbg.ini in the project for Keil-specific debug init (MSP/PC,
    DCS keys via Configuration Wizard). That file is separate from this pack.

IAR
  - Select the G32R501 device and J-Link as the probe.
  - Disable "Use flash loader(s)" when using this J-Link flash algorithm
    (same approach as G32R502 J-Link integration).

J-Flash / J-Link Commander / Ozone
  - Select the matching G32R501 device name.
  - Script and flash loader are picked up from the installed folder.

Eclipse (GNU MCU Eclipse / Embedded CDT + J-Link GDB Server)
  - Select J-Link and the G32R501 device in the debug launch configuration.
  - DCS/init is handled by the .jlinkscript on connect/reset.
  - Set initial MSP/PC in GDB startup commands if needed (read from the
    vector table at 0x08000000 for CBUS flash builds).

Custom DCS keys
---------------
If Zone1/Zone2 CSM passwords were changed in OTP, edit the Z1_CSM_Buff and
Z2_CSM_Buff arrays at the top of Geehy_G32R501_ConnectCore.jlinkscript
before copying to JLinkDevices.

References
----------
  SEGGER: J-Link script files
    https://kb.segger.com/J-Link_script_file
  SEGGER: J-Link Device Support Kit (device .xml format)
    https://kb.segger.com/J-Link_Device_Support_Kit
  Sibling package (G32R502): device_support/g32r502/common/jlink/readme.txt
