# pyocd_user.py
# encoding: utf-8

import logging
from pyocd.core.helpers import ConnectHelper

LOG = logging.getLogger(__name__)

# Global variable, for example:
CORE0_SET_ADDR = 0xFFFFFFFF

try:
    from pyocd.target.builtin import target_G32R501xx

    # Custom new decryption keys (address, value)
    NEW_DECRYPT_KEYS = [
       (0x50024020, 0xFFFFFFFF),
       (0x50024024, 0xFFFFFFDC),
       (0x50024028, 0xFFFFFFFF),
       (0x5002402C, 0xFFFFFFFF),
       (0x500240A0, 0xFFFFFFFF),
       (0x500240A4, 0xFFFEDFFF),
       (0x500240A8, 0xFFFFFFFF),
       (0x500240AC, 0xFFFFFFFF),
    ]

    # Overwrite the G32R501xx.DECRYPT_KEYS
    target_G32R501xx.DECRYPT_KEYS[:] = NEW_DECRYPT_KEYS

    # Update DECRYPT_KEY_VALUES (only the values)
    target_G32R501xx.DECRYPT_KEY_VALUES[:] = [pair[1] for pair in NEW_DECRYPT_KEYS]

    # Rebuild the final instructions by combining MAIN_INSTRUCTIONS + DECRYPT_KEY_VALUES
    target_G32R501xx.FLASH_INSTRUCTIONS[:] = (
        target_G32R501xx.MAIN_INSTRUCTIONS + target_G32R501xx.DECRYPT_KEY_VALUES
    )

    # Set the boot address for CORE1 here.
    target_G32R501xx.CORE1_SET_ADDR = 0x08050000

    LOG.info("Patched target_G32R501xx DECRYPT_KEYS via pyocd_user.py!")
except ImportError:
    LOG.warning("Unable to import target_G32R501xx; patch not applied.")
except AttributeError:
    LOG.warning("Target G32R501xx found, but missing expected attributes. Patch not applied.")


@command(name="set_pc_cmd", help="Set MSP and PC from the given memory address.")
def set_pc_cmd(addr: int):
    """
    Reads the first two 32-bit words from 'addr' as MSP and PC,
    then writes them to the CPU registers after halting.  
    Resumes execution afterward.  
    All comments are in English.
    
    Example usage in pyOCD commander:
        set_pc_cmd 0x08000000
    """
    global target

    # Halt the target to safely modify registers
    target.halt()

    # Read two 32-bit values from memory => MSP, PC
    values = target.read_memory_block32(addr, 2)
    sp_temp, pc_temp = values[0], values[1]

    # LOG.info log messages
    LOG.info(f"Reading SP/PC from 0x{addr:08X}:")
    LOG.info(f"  MSP = 0x{sp_temp:08X}")
    LOG.info(f"  PC  = 0x{pc_temp:08X}")

    # Write the MSP and PC registers
    target.write_core_register("msp", sp_temp)
    target.write_core_register("pc", pc_temp)

    # Resume execution
    target.resume()
    LOG.info("set_pc_cmd: Registers updated; target resuming.")


def set_sp_pc_setup():
    """
    Uses the global CORE0_SET_ADDR. If CORE0_SET_ADDR != 0xFFFFFFFF,
    calls set_pc_cmd(CORE0_SET_ADDR). Otherwise, LOG.infos warnings.

    Comments in English.
    """
    global CORE0_SET_ADDR

    if CORE0_SET_ADDR != 0xFFFFFFFF:
        # Directly call the command function with our global address
        set_pc_cmd(CORE0_SET_ADDR)
    else:
        LOG.warning("Warning: SP and PC are not set because CORE0_SET_ADDR is currently 0xFFFFFFFF.")
        LOG.warning("Please define a valid CORE0_SET_ADDR in pyocd_user.py, for example:")
        LOG.warning("  CORE0_SET_ADDR = 0x08000000")


def init_cpu():
    """
    This function configures the CPU and peripherals.
    Comments are in English.
    """
    target.write32(0xE000ED08, 0x10000000)

    val = target.read32(0xE000ED88)
    val |= 0x0C
    target.write32(0xE000ED88, val)

    val8 = target.read8(0x50010600)
    val8 |= 0xF0
    target.write8(0x50010600, val8)

    val16 = target.read16(0x50026452)
    val16 |= 0x68
    target.write16(0x50026452, val16)

    val = target.read32(0xE0059040)
    val |= 0x01
    target.write32(0xE0059040, val)

    val = target.read32(0xE0059044)
    val |= 0x01
    target.write32(0xE0059044, val)

    target.write32(0x50020074, 0x01)
    target.write16(0x500264C0, 0x0001)

    if (target.read32(0x50020B00) & 0x01) == 0x01:
        val = target.read32(0x50010830)
        val |= 0xFFFF
        target.write32(0x50010830, val)

    # Startup configuration
    if (target.read32(0x50020B00) & 0x03) == 0x03:
        target.write32(0x50010000, 0x00000900)
        target.write32(0x50020844, 0x00000000)

        val = target.read32(0x0810B910)
        if ((val & 0xFF000000) >> 24) != 0x5A:
            target.write32(0x50020828, 18)
        if ((val & 0xFF000000) >> 24) == 0x5A:
            target.write32(0x50020828, (val >> 0x08) & 0xFF)

        temp_val = target.read32(0x0810B878)
        if (temp_val & 0xFF03) == 0x5A00:
            v = target.read32(0x500280D4)
            v |= 0x8000
            target.write32(0x500280D4, v)

        temp_val = target.read32(0x0810B894)
        if (temp_val & 0xFFFF) == 0x5A5A:
            target.write32(0x50028024, target.read32(0x0810B884))
            target.write32(0x50028028, target.read32(0x0810B888))
            target.write32(0x5002801C, target.read32(0x0810B88C))
            target.write32(0x50028020, target.read32(0x0810B890))

        if ((val & 0xFF000000) >> 24) == 0x5A:
            mask = val & 0xF0000
            target.write32(0x50021100, mask)
            target.write32(0x50021104, mask)
            target.write32(0x50020844, val & 0xFC)

        val2 = target.read32(0x0810B910)
        if ((val2 & 0xFF000003) == 0x5A000003) and (target.read32(0x5002082C) & 0x01):
            reg_val = target.read32(0x5002081C)
            reg_val |= 0x02
            target.write32(0x5002081C, reg_val)

    target.write32(0x50010000, 0x00000F00)

    # Device configuration
    temp = target.read32(0x0810B800)
    target.write32(0x50020510, temp)
    temp = target.read32(0x0810B804)
    target.write32(0x50020514, temp)
    temp = target.read32(0x0810B80C)
    target.write32(0x50020524, temp)
    temp = target.read32(0x0810B814)
    target.write32(0x5002052C, temp)
    temp = target.read32(0x0810B818)
    target.write32(0x50020530, temp)
    temp = target.read32(0x0810B81C)
    target.write32(0x50020534, temp)
    temp = target.read32(0x0810B824)
    target.write32(0x5002053C, temp)
    temp = target.read32(0x0810B828)
    target.write32(0x50020540, temp)
    temp = target.read32(0x0810B82C)
    target.write32(0x50020544, temp)
    temp = target.read32(0x0810B830)
    target.write32(0x50020548, temp)
    temp = target.read32(0x0810B834)
    target.write32(0x5002054C, temp)
    temp = target.read32(0x0810B840)
    target.write32(0x50020558, temp)
    temp = target.read32(0x0810B844)
    target.write32(0x5002055C, temp)
    temp = target.read32(0x0810B84C)
    target.write32(0x50020564, temp)
    temp = target.read32(0x0810B850)
    target.write32(0x50020568, temp)
    temp = target.read32(0x0810B858)
    target.write32(0x50020570, temp)
    temp = target.read32(0x0810B860)
    target.write32(0x50020574, temp)
    temp = target.read32(0x0810B864)
    target.write32(0x50020578, temp)
    temp = target.read32(0x0810B868)
    target.write32(0x5002057C, temp)
    temp = target.read32(0x0810B86C)
    target.write32(0x50020580, temp)
    temp = target.read32(0x0810B870)
    target.write32(0x50020584, temp)

    val = target.read32(0x0810B914)
    if ((val & 0xFF000000) >> 24) == 0x5A:
        target.write32(0x5002075C, val)

    # System init
    tmp = target.read32(0x50010604)
    target.write32(0x20307F30, tmp)
    tmp = target.read32(0x50010650)
    target.write32(0x20307F34, tmp)
    tmp = target.read32(0x50010608)
    target.write32(0x20307F28, tmp)
    tmp = target.read32(0x50010654)
    target.write32(0x20307F2C, tmp)

    errorStatus = target.read32(0x50024014)
    if ((errorStatus & 0xFF000000) >> 24) == 0x5A:
        if ((errorStatus & 0x00000030) >> 4) == 0x0:
            gpamux2 = target.read32(0x40030010)
            gpamux2 = (gpamux2 & ~(0x03 << 16)) | (0x01 << 16)
            target.write32(0x40030010, gpamux2)

            gpagmux2 = target.read32(0x40030044)
            gpagmux2 = (gpagmux2 & ~(0x03 << 16)) | (0x03 << 16)
            target.write32(0x40030044, gpagmux2)

            lock = target.read32(0x40030078)
            lock |= (0x01 << 24)
            target.write32(0x40030078, lock)
        elif ((errorStatus & 0x00000030) >> 4) == 0x1:
            gpamux2 = target.read32(0x40030010)
            gpamux2 = (gpamux2 & ~(0x03 << 24)) | (0x01 << 24)
            target.write32(0x40030010, gpamux2)

            gpagmux2 = target.read32(0x40030044)
            gpagmux2 = (gpagmux2 & ~(0x03 << 24)) | (0x03 << 24)
            target.write32(0x40030044, gpagmux2)

            lock = target.read32(0x40030078)
            lock |= (0x01 << 28)
            target.write32(0x40030078, lock)
        elif ((errorStatus & 0x00000030) >> 4) == 0x2:
            gpamux2 = target.read32(0x40030010)
            gpamux2 = (gpamux2 & ~(0x03 << 26)) | (0x01 << 26)
            target.write32(0x40030010, gpamux2)

            gpagmux2 = target.read32(0x40030044)
            gpagmux2 = (gpagmux2 & ~(0x03 << 26)) | (0x03 << 26)
            target.write32(0x40030044, gpagmux2)

            lock = target.read32(0x40030078)
            lock |= (0x01 << 29)
            target.write32(0x40030078, lock)

    config_val = target.read32(0x0810B914) & 0xFF
    if config_val == 0x00:
        target.write32(0x40030018, 0xFFCFFFFF)
        target.write32(0x40030098, 0x0F6001FF)
    elif config_val == 0x01:
        target.write32(0x40030018, 0xFFCFFFFF)
        target.write32(0x40030098, 0x00607FFF)
    elif config_val == 0x02:
        target.write32(0x40030018, 0x31CF3FFF)
        target.write32(0x40030098, 0x0000007B)
    elif config_val == 0x03:
        target.write32(0x40030018, 0x31CF3BFF)
        target.write32(0x40030098, 0x0000007B)
    elif config_val == 0x04:
        target.write32(0x40030018, 0x310D30FF)
        target.write32(0x40030098, 0x0000007B)

    if (target.read32(0x0810BA00) & 0xFFFF) == 0xA5A5:
        if (target.read32(0x50020B00) & 0x03) == 0x03:
            target.write32(0x5002800C, target.read32(0x0810BA04))
            target.write32(0x50028000, target.read32(0x0810BA08))
            target.write32(0x50028004, target.read32(0x0810BA0C))

    val = target.read32(0x50020A78)
    val |= 0x0F
    target.write32(0x50020A78, val)

    target.write32(0x50028010, target.read32(0x0810BA5C))
    target.write32(0x50028014, target.read32(0x0810BA60))
    target.write32(0x50028018, target.read32(0x0810BA64))
    target.write32(0x50028068, target.read32(0x0810BA68))
    target.write32(0x5002806C, target.read32(0x0810BA6C))
    target.write32(0x50028070, target.read32(0x0810BA70))

    target.write32(0x4002007C, target.read32(0x0810BA10))
    target.write32(0x4002047C, target.read32(0x0810BA14))
    target.write32(0x4002087C, target.read32(0x0810BA18))

    target.write16(0x40020076, target.read32(0x0810BA1C))
    target.write16(0x40020476, target.read32(0x0810BA20))
    target.write16(0x40020876, target.read32(0x0810BA24))

    target.write32(0x400200E0, target.read32(0x0810BA28))
    target.write32(0x400200E4, target.read32(0x0810BA2C))
    target.write32(0x400200E8, target.read32(0x0810BA30))
    target.write32(0x400204E0, target.read32(0x0810BA34))
    target.write32(0x400204E4, target.read32(0x0810BA38))
    target.write32(0x400204E8, target.read32(0x0810BA3C))
    target.write32(0x400208E0, target.read32(0x0810BA40))
    target.write32(0x400208E4, target.read32(0x0810BA44))

    val = target.read32(0x50020A84)
    val |= 0x00030000
    target.write32(0x50020A84, val)

    target.write32(0x5000180C, target.read32(0x0810BA50))
    target.write32(0x50001C0C, target.read32(0x0810BA54))

    val = target.read32(0x50020B00)
    val &= ~(0x03)
    target.write32(0x50020B00, val)

    # Disable and clear all NVIC interrupts
    for addr in range(0xE000E180, 0xE000E1C0, 4):
        target.write32(addr, 0xFFFFFFFF)
    for addr in range(0xE000E280, 0xE000E2C0, 4):
        target.write32(addr, 0xFFFFFFFF)

    LOG.info("CPU and peripheral initialization completed")


def bootmode_setup():
    """
    Enter Standalone Boot Mode.
    Comments are in English.
    """
    target.write32(0x50020000, 0xA5FFFFFF)

    LOG.info("Entering Standalone Boot Mode")


def dcs_key_setup():
    """
    Use the NEW_DECRYPT_KEYS list to write all DCSM registers automatically.
    """
    for (addr, val) in NEW_DECRYPT_KEYS:
        target.write32(addr, val)

    LOG.info("Using NEW_DECRYPT_KEYS to automatically write all DCSM registers")

def did_connect(board) -> None:
    """
    This hook is called by pyOCD once the board is connected.
    Comments are in English.
    """
    LOG.info("r501 connected (did_connect)")
    # Uncomment as needed
    dcs_key_setup()
    bootmode_setup()
    init_cpu()
    set_sp_pc_setup()