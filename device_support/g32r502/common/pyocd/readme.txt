G32R502 pyOCD Device Support
============================

This folder provides pyOCD target support and project configuration templates
for the Geehy G32R502 (Cortex-M52) series. After installing the target into
your pyOCD build and copying the project files below, you can erase, program,
and debug G32R502 boards with a CMSIS-DAP compatible probe.

Contents
--------
  target_G32R502xx.py
      Built-in style target module (flash algorithm, DCS hooks, memory map).

  pyocd.yaml
      Example session configuration (target override, user script, timeouts).

  pyocd_user.py
      User script: DCS key table and startup hooks (will_connect / did_connect).

  readme.txt
      This file.

Supported target name
---------------------
  g32r502xx

  Select this name with pyocd --target g32r502xx or target_override in pyocd.yaml.

Requirements
------------
  - pyOCD 0.44 or later.
  - Python 3.9 or later.
  - CMSIS-DAP compatible debug probe (e.g. on-board DAPLink or standalone adapter).

Obtain pyOCD
------------
  Install pyOCD 0.44 or later from your pyOCD source tree in editable mode:

    cd <path-to>/pyocd
    pip install -e .

  Use the same Python environment when running pyocd from the command line or IDE.

Add G32R502 support to pyOCD
----------------------------
1. Copy target_G32R502xx.py from this folder into your pyOCD install:

     pyocd/target/builtin/target_G32R502xx.py

2. Register the target in pyocd/target/builtin/__init__.py:

   - Add import:
       from . import target_G32R502xx

   - Add to BUILTIN_TARGETS dict:
       'g32r502xx': target_G32R502xx.G32R502xx,

3. Reinstall or ensure your editable install picks up the changes (pip install -e .).

4. Confirm the target is registered:

     pyocd list -t | findstr g32r502          (Windows)
     pyocd list -t | grep g32r502             (Linux / macOS)

   You should see g32r502xx in the output. Alternatively:

     pyocd list -t -n g32r502

Project setup
-------------
1. Copy into your project directory (same folder as your .elf / launch config):

     pyocd.yaml
     pyocd_user.py

2. Run pyocd from that directory (or pass --config pyocd.yaml) so user_script
   and target_override are applied.

3. Adjust DCS keys in pyocd_user.py if Zone1/Zone2 OTP passwords were changed
   (see Custom DCS keys below).

Verify
------
After project files are in place and the board is connected:

1. List probes:

     pyocd list -p

2. Interactive commander (halt, reset, memory read/write, erase, load, etc.):

     pyocd cmd --config pyocd.yaml

   Or run a single command:

     pyocd cmd -t g32r502xx -c "status"
     pyocd cmd -t g32r502xx -c "erase 0x08000000 1"

3. Erase flash (example: full chip):

     pyocd erase --config pyocd.yaml -c 0x08000000

4. Load firmware:

     pyocd load --config pyocd.yaml build/your_app.elf

5. Start GDB server for IDE attach:

     pyocd gdbserver --config pyocd.yaml

   Confirm connect, reset, and flash operations complete without DCS or timeout errors.

IDE usage notes
---------------
Eclipse (GNU MCU Eclipse / Embedded CDT + pyOCD)
  - Copy pyocd.yaml and pyocd_user.py into the project (Eclipse project folder).
  - Debug launch: pyOCD as the debugger, target g32r502xx, config file pyocd.yaml.
  - Working directory should be the project folder so user_script resolves.
  - Initial SP/PC may be taken from the vector table at 0x08000000 for CBUS flash builds.

Custom DCS keys
---------------
If Zone1/Zone2 CSM passwords were changed in OTP, edit the DCS_KEYS list at the
top of pyocd_user.py (register/value pairs) before copying into your project.

References
----------
  pyOCD documentation: https://pyocd.io/docs/
  pyOCD installation: pip install -e . from your pyOCD source tree

