# pyocd_user.py
# encoding: utf-8
#
# G32R501 common pyOCD user script: DCS keys and core vector bases.
# CSM key window uses the G32R501 map (0x500240xx).
# Hardware startup (DCS / bootmode / init_cpu / vector apply) lives in target_G32R501xx.

import logging

LOG = logging.getLogger(__name__)

DCS_KEYS = [
    (0x50024020, 0xFFFFFFFF),
    (0x50024024, 0xFFFFFFDC),
    (0x50024028, 0xFFFFFFFF),
    (0x5002402C, 0xFFFFFFFF),
    (0x500240A0, 0xFFFFFFFF),
    (0x500240A4, 0xFFFEDFFF),
    (0x500240A8, 0xFFFFFFFF),
    (0x500240AC, 0xFFFFFFFF),
]

# Core0 vector table base for VTOR / MSP / Reset.
#   0x08000000 - Flash (default)
#   0x00000000 - ITCM / RAM vector table
CORE0_SET_ADDR = 0x08000000
CORE1_SET_ADDR = 0x08050000


def will_connect(board):
    """Apply DCS keys and vector bases on the target instance before init."""
    target = board.target
    if hasattr(target, "configure_startup"):
        target.configure_startup(
            decrypt_keys=DCS_KEYS,
            core0_vector_address=CORE0_SET_ADDR,
            core1_vector_address=CORE1_SET_ADDR,
        )
        LOG.info(
            "will_connect: core0=0x%08X core1=0x%08X",
            CORE0_SET_ADDR,
            CORE1_SET_ADDR,
        )


def did_connect(board):
    target = board.target
    if hasattr(target, "set_decrypt_keys"):
        target.set_decrypt_keys(DCS_KEYS)
    if hasattr(target, "r501_dcs_setup"):
        target.r501_dcs_setup()


def did_reset(core, reset_type):
    """Re-apply vector table after IDE/GDB reset."""
    t = core.session.board.target if hasattr(core, "session") else None
    if t is None:
        return
    if hasattr(t, "configure_startup"):
        t.configure_startup(
            core0_vector_address=CORE0_SET_ADDR,
            core1_vector_address=CORE1_SET_ADDR,
        )
    if hasattr(t, "set_core_vector_table"):
        LOG.info("did_reset: re-apply vector from 0x%08X", CORE0_SET_ADDR)
        t.set_core_vector_table(0)
        if getattr(t, "HAS_CORE1", False) and getattr(t, "BRINGUP_CORE1_VECTOR", False):
            t.set_core_vector_table(1)
