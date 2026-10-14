================================================================================

  G32R5xx_AddOn - Geehy G32R5xx IAR EWARM Device Support Installer

================================================================================



Target devices

--------------

  Geehy G32R5xx series Cortex-M MCUs (G32R501, G32R502).



  Supported device variants (v1.0.2):

    G32R501DxCx7

    G32R501DxYx7

    G32R501DxYx8Q

    G32R501xCx7

    G32R501xYx7

    G32R502xCx7



Current release

---------------

  Version    : 1.0.2

  Build date : 2026-05-22

  Binary     : G32R5xx_AddOn_v1.0.2.exe



Purpose

-------

  Install G32R5xx IAR device support into an existing IAR EWARM for Arm.

  Target directory: <IAR root>\arm\config\



IAR version requirement

-----------------------

  IAR Embedded Workbench for ARM (EWARM) 9.70.4 or later.

  Versions older than 9.70.4 are not supported.



  Select the IAR installation root (e.g. C:\iar\ewarm-9.70.4). Do not select

  arm\config, common\bin, or other subfolders.





Installation

------------

  1. Close IAR EWARM.

  2. Run G32R5xx_AddOn_v1.0.2.exe and select the IAR root directory.

  3. Complete installation and restart IAR EWARM.

  4. In Project > Options > General Options > Device, choose a G32R501 or

     G32R502 part from the Geehy device list.





Version history

---------------

  1.0.2 (2026-05-22)

    - Add G32R502xCx7 support. For G32R502, use this package (v1.0.2) with

      IAR 9.70.4 or later; earlier Add-On releases support G32R501 only.



  1.0.1

    - G32R501 device support updates.



  1.0.0

    - Initial release for G32R501 series.





Directory layout

----------------

  G32R5xx_AddOn_v1.0.2.exe    Installer

  readme.txt                  This file





Notes

-----

  - Re-run the installer to update support on the same IAR installation.

  - For other IAR versions, use the matching Add-On package from Geehy.



Product information

-------------------

  Publisher : Geehy Semiconductor

  Web site  : https://www.geehy.com



================================================================================
