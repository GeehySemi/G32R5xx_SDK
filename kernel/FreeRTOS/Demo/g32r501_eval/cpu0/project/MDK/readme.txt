G32R501 pyOCD Device Support
============================

This folder provides pyOCD target support and project configuration templates
for the Geehy G32R501 (Cortex-M52) series.

Contents
--------
  target_G32R501xx.py
      Built-in style target module (flash algorithm, DCS hooks, memory map).
      Keep in sync with your local pyOCD tree when developing, for example:
        D:\Desktop\pycod\pyOCD_Geehy_v0.44\pyocd\target\builtin\target_G32R501xx.py

  pyocd.yaml
      Session configuration (single-core / dual-core target_override).

  pyocd_user.py
      User script: DCS key patch table and optional SP/PC helpers.

  readme.txt
      This file.

Supported target names
----------------------
  g32r501xx     Single-core
  g32r501dxx    Dual-core (default in pyocd.yaml)

Requirements
------------
  - pyOCD 0.44 or later
  - Python 3.9 or later
  - CMSIS-DAP compatible probe

Project setup
-------------
1. Copy pyocd.yaml and pyocd_user.py next to your .elf / launch config.
2. Run pyocd from that directory (or pass --config pyocd.yaml).
3. Adjust DCS keys in pyocd_user.py if OTP passwords changed
   (G32R501 CSM ports: 0x50024020 / 0x500240A0 family ¡ª do not use G32R502
   0x400108xx addresses).

Verify
------
  pyocd list -t | findstr g32r501
  pyocd cmd --config pyocd.yaml
  pyocd erase --config pyocd.yaml -c 0x08000000
  pyocd load --config pyocd.yaml build/your_app.elf

NOTE
----
Vector-table linker framework backport is tracked separately and is not
required for basic pyOCD connect/erase/load.
