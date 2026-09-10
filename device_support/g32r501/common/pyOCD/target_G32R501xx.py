#!/usr/bin/env python3
# target_G32R501xx.py
#
# Geehy G32R501xx Dual-core Target Script
# This script defines two target classes for G32R501xx MCU:
#   - g32r501Dxx_core0: Main core (core0) that handles flash programming (using AP port 0)
#   - g32r501Dxx_core1: Secondary core (core1) that is released by core0 (using AP port 1)
#
# Note: Adjust RELEASE_CPU1_ADDR and other register addresses as per the device manual.

import time
import logging

from ...coresight.coresight_target import CoreSightTarget
from ...core.memory_map import (FlashRegion, RamRegion, MemoryMap)
from ...coresight.cortex_m import CortexM
from ...coresight.minimal_mem_ap import MinimalMemAP as MiniAP
from ...coresight.ap import AccessPort, APv1Address
from ...debug.svd.loader import SVDFile

LOG = logging.getLogger(__name__)

# 1) Define the main body of instructions (excluding the final 8 key constants).
MAIN_INSTRUCTIONS = [
    0xe7fdbe00,
    0x4178f100, 0x1280f5a0, 0x2f20f5b1, 0x0385f244, 0x912fea5f, 0x2f20f5b2, 0x922fea5f, 0x3f50ebb3,
    0x0002ea41, 0x911fea5f, 0x47704308, 0x0004f240, 0x0220f244, 0x0000f2c0, 0x1000f859, 0x0202f2c5,
    0x60114448, 0x60516841, 0x60916881, 0x60d168c1, 0xf8c26901, 0x69411080, 0x1084f8c2, 0xf8c26981,
    0x69c01088, 0x008cf8c2, 0xbf004770, 0xf240b580, 0xf2440104, 0xf2c00320, 0xf8590100, 0xf2c52001,
    0x44490302, 0x684a601a, 0x688a605a, 0x68ca609a, 0x690a60da, 0x2080f8c3, 0xf8c3694a, 0x698a2084,
    0x2088f8c3, 0xf8c369c9, 0xf64e108c, 0xf2ce5188, 0x680a0100, 0x020cf042, 0x2101600a, 0x111cee00,
    0x4152f246, 0x0102f2c5, 0xf042880a, 0x800a0268, 0x0285f244, 0xebb22100, 0xee003f50, 0xd00b111c,
    0x4178f100, 0x2f20f5b1, 0xf5a0d306, 0x0c401080, 0xd9012804, 0xbd802000, 0x21322000, 0x0001f2c5,
    0xf8a6f000, 0x2000b920, 0xf8a7f000, 0xd0f12800, 0xbd802001, 0x47702000, 0xb085b5f0, 0x77fff64d,
    0x6400f04f, 0xf6c0ad01, 0xbf000709, 0x46212006, 0xf898f000, 0xbf004606, 0xf899f000, 0xd1fb2802,
    0xf000b986, 0xb968f899, 0xf44f4620, 0x462a6100, 0xf897f000, 0x42bcb930, 0x5400f504, 0x2000d9e6,
    0xbdf0b005, 0xb0052001, 0xbf00bdf0, 0xb084b5b0, 0xf2444604, 0xebb00085, 0xd00c3f54, 0x4078f104,
    0x2f20f5b0, 0xf5a4d307, 0x0c401080, 0xd9022804, 0xb0042000, 0x2006bdb0, 0xf0004621, 0x4605f863,
    0xf865f000, 0xd1fb2802, 0xf000b955, 0xb938f865, 0x466a4620, 0x6100f44f, 0xf863f000, 0xd0e72800,
    0xb0042001, 0xbf00bdb0, 0x45f0e92d, 0x4606b083, 0xf0004248, 0xf04f0007, 0x18440800, 0x4615d034,
    0x0a85f244, 0xbf00e00a, 0x60306828, 0x60706868, 0xf1063c08, 0xf1050608, 0xd0230508, 0x3f56ebba,
    0xf106d009, 0xf5b04078, 0xd3042f20, 0x1080f5a6, 0x28040c40, 0x4630d8e8, 0x22024629, 0xf8cd2300,
    0xf8cd8000, 0xf0008004, 0x4607f831, 0xf81ff000, 0xd1fb2802, 0xf000b91f, 0x2800f81f, 0xf04fd0d8,
    0xe0010801, 0x0800f04f, 0xb0034640, 0x85f0e8bd, 0x0c01f244, 0x0c00f2c1, 0xf2444760, 0xf2c10c31,
    0x47600c00, 0x1ce1f244, 0x0c00f2c1, 0xf2444760, 0xf2c10c1d, 0x47600c00, 0x0c11f244, 0x0c00f2c1,
    0xf6444760, 0xf2c16c41, 0x47600c00, 0x4c79f244, 0x0c00f2c1, 0x00004760, 0x00000000,
]

# 2) Define the addresses and values for the decryption keys as a list of (address, value).
#    You only need to edit this list if the keys or addresses change.
DECRYPT_KEYS = [
    (0x50024020, 0xFFFFFFFF),
    (0x50024024, 0xFFFFFFDC),
    (0x50024028, 0xFFFFFFFF),
    (0x5002402C, 0xFFFFFFFF),
    (0x500240A0, 0xFFFFFFFF),
    (0x500240A4, 0xFFFEDFFF),
    (0x500240A8, 0xFFFFFFFF),
    (0x500240AC, 0xFFFFFFFF)
]

CORE1_SET_ADDR = 0x08050000

# 3) Extract just the key values to append to the instructions array.
DECRYPT_KEY_VALUES = [val for (_, val) in DECRYPT_KEYS]

# 4) Combine MAIN_INSTRUCTIONS with DECRYPT_KEY_VALUES, 
#    ensuring the final compiled flash algo includes the 8 key constants at the end.
FLASH_INSTRUCTIONS = MAIN_INSTRUCTIONS + DECRYPT_KEY_VALUES

FLASH_ALGO = {
    'load_address': 0x00000000,

    # Use FLASH_INSTRUCTIONS as the final instructions array.
    'instructions': FLASH_INSTRUCTIONS,

    # Adjust these if code size or layout changes significantly.
    'pc_init': 0x00000071,
    'pc_unInit': 0x00000119,
    'pc_program_page': 0x000001cd,
    'pc_erase_sector': 0x00000171,
    'pc_eraseAll': 0x0000011d,

    'static_base': 0x00000000 + 0x00000004 + 0x00000298,
    'begin_stack': 0x000082c0,
    'end_stack': 0x000042c0,
    'begin_data': 0x00000000 + 0x1000,
    'page_size': 0x2000,
    'analyzer_supported': False,
    'analyzer_address': 0x00000000,
    # Enable double buffering
    'page_buffers': [
        0x000002c0,
        0x000022c0
    ],
    'min_program_length': 0x2000,

    'ro_start': 0x4,
    'ro_size': 0x298,
    'rw_start': 0x29c,
    'rw_size': 0x24,
    'zi_start': 0x2c0,
    'zi_size': 0x0,

    'flash_start': 0x0,
    'flash_size': 0x20308000,
    'sector_sizes': (
        (0x0, 0x2000),
    )
}

# Define memory map for core0 (Main Core)
MEMORY_MAP_G32R501xx = MemoryMap(
    FlashRegion(
        start=0x08000000,
        length=0xA0000,
        sector_size=0x2000,
        page_size=0x1000,
        is_boot_memory=True,
        algo=FLASH_ALGO
    ),
    # TCMRAM and DTCMRAM
    RamRegion(start=0x00000000, length=0xC000, access="rwx", is_cachable=False),
    RamRegion(start=0x20000000, length=0x4000, access="rwx", is_cachable=False),

    # Shared SRAM regions
    RamRegion(start=0x20100000, length=0x2000, access="rwx", init="0"),
    RamRegion(start=0x20200000, length=0x2000, access="rwx", init="0"),
    RamRegion(start=0x20300000, length=0x8000, access="rwx", init="0"),

)

# Define memory map for core0 (Main Core)
MEMORY_MAP_G32R501Dxx = MemoryMap(
    FlashRegion(
        start=0x08000000,
        length=0xA0000,
        sector_size=0x2000,
        page_size=0x1000,
        is_boot_memory=True,
        algo=FLASH_ALGO
    ),
    # core0-specific memory: ITCMRAM and DTCMRAM
    RamRegion(start=0x00000000, length=0xC000, access="rwx", is_cachable=False),
    RamRegion(start=0x20000000, length=0x4000, access="rwx", is_cachable=False),

    # Shared SRAM regions
    RamRegion(start=0x20100000, length=0x2000, access="rwx", init="0"),
    RamRegion(start=0x20200000, length=0x2000, access="rwx", init="0"),
    RamRegion(start=0x20300000, length=0x8000, access="rwx", init="0"),
)

class G32R501xxBase(CoreSightTarget):
    """Base class for G32R501Dxx dual-core device."""
    VENDOR = "Geehy"

    def __init__(self, session, memory_map):
        """Initialize the base class with session and memory map."""
        super().__init__(session, memory_map)

    def r501_dcs_setup(self):
        """Initialize device security / decryption keys (via AP0)."""
        ap = MiniAP(self.dp)
        ap.init()

        # 1) Enter Standalone Boot Mode
        ap.write32(0x50020000, 0x5AFFFFFF)
        ap.write32(0x50020004, 0xFFFFFF03)
        ap.write32(0x50020008, 0xFFFFFFFF)

        LOG.info("R501 DCS Key Set ...")
        # 2) Write all DCS keys from DECRYPT_KEYS
        for (addr, val) in DECRYPT_KEYS:
            ap.write32(addr, val)
            LOG.info(" 0x%08X -> [0x%08X]", addr, val)

        # 3) Check the ITCM RAM size after DCS unlock
        itcm_size = ap.read32(0x50020064)
        if itcm_size not in (3, 8):
            LOG.error("Insufficient ITCM RAM size for FLM algorithm. Please check CFGSMS configuration.")
            return

        LOG.info("R501 setup completed successfully.")

    def reset_and_halt(self, reset_type=None, map_to_user=True):
        """Reset and halt the core, then set up DCS keys."""
        super().reset_and_halt(reset_type or self.ResetType.SW)
        self.halt()
        self.r501_dcs_setup()
        LOG.info("Reset & Halt completed, DCS setup done.")

    def create_init_sequence(self):
        seq = super().create_init_sequence()
        seq.wrap_task('discovery',
            lambda seq: seq.replace_task('find_aps', self.find_aps)
                .replace_task('create_cores', self.create_cores)
        )
        return seq

    def find_aps(self):
        """Discover available APs manually (AP0, AP1, etc)."""
        if self.dp.valid_aps is not None:
            return
        self.dp.read_ap(0xFC)
        self.dp.valid_aps = [0,1,2]  # Example
        ap0 = AccessPort.create(self.dp, APv1Address(0))
        # This call ensures AP0 is recognized.

    def create_cores(self):
        """Create core and core1 in a single session."""
        # Create core
        core = CortexM(self.session, self.aps[0], self.memory_map, 0)
        core.default_reset_type = self.ResetType.SW_CORE
        self.aps[0].core = core
        core.init()
        self.add_core(core)
        LOG.info("core is created and initialized.")

class G32R501Dxx(G32R501xxBase):
    MEMORY_MAP = MEMORY_MAP_G32R501Dxx

    def __init__(self, session):
        super().__init__(session, self.MEMORY_MAP)

    def create_cores(self):
        """Create core0 and core1 in a single session."""
        # Create core0
        core0 = CortexM(self.session, self.aps[0], self.memory_map, 0)
        core0.default_reset_type = self.ResetType.SW_CORE
        self.aps[0].core = core0
        core0.init()
        self.add_core(core0)
        LOG.info("core0 is created and initialized.")

        # Release core1 using AP0
        LOG.info("Enabling clock and setting startup address for core1 via AP0...")
        ap0 = self.dp.aps[0]
        ap0.init()
        # For example, set core1 startup to CORE1_SET_ADDR
        ap0.write32(0x50020054, CORE1_SET_ADDR)
        val = ap0.read32(0x50020058)
        val |= 0x2
        ap0.write32(0x50020058, val)

        # Create core1
        core1 = CortexM(self.session, self.aps[1], self.memory_map, 1)
        core1.default_reset_type = self.ResetType.SW_CORE
        self.aps[1].core = core1
        core1.init()
        self.add_core(core1)
        LOG.info("core1 is created and initialized.")

class G32R501xx(G32R501xxBase):
    MEMORY_MAP = MEMORY_MAP_G32R501xx

    def __init__(self, session):
        super().__init__(session, self.MEMORY_MAP)