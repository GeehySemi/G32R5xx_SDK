# pyocd_user.py
# encoding: utf-8
#
# G32R502 common pyOCD user script: DCS keys and vector table base.
# CSM key window uses the G32R502 map (0x400108xx).

import logging

LOG = logging.getLogger(__name__)

DCS_KEYS = [
    (0x40010820, 0xFFFFFFFF),
    (0x40010824, 0xFFFFFFDC),
    (0x40010828, 0xFFFFFFFF),
    (0x4001082C, 0xFFFFFFFF),
    (0x400108A0, 0xFFFFFFFF),
    (0x400108A4, 0xFFFEDFFF),
    (0x400108A8, 0xFFFFFFFF),
    (0x400108AC, 0xFFFFFFFF),
]

# Vector table base for VTOR / MSP / Reset.
#   0x08000000 - Flash (default)
#   0x00000000 - ITCM / RAM vector table
VECTOR_TABLE_ADDRESS = 0x08000000


def will_connect(board):
    """Apply DCS keys and vector base on the target instance before init."""
    target = board.target
    if hasattr(target, "configure_startup"):
        target.configure_startup(
            decrypt_keys=DCS_KEYS,
            vector_table_address=VECTOR_TABLE_ADDRESS,
        )
        LOG.info("will_connect: vector base = 0x%08X", VECTOR_TABLE_ADDRESS)


def did_connect(board):
    target = board.target
    if hasattr(target, "set_decrypt_keys"):
        target.set_decrypt_keys(DCS_KEYS)
    if hasattr(target, "r502_dcs_setup"):
        target.r502_dcs_setup()


def did_reset(core, reset_type):
    """Re-apply vector table after IDE/GDB reset."""
    t = core.session.board.target if hasattr(core, "session") else None
    if t is None:
        return
    if hasattr(t, "set_vector_table_address"):
        t.set_vector_table_address(VECTOR_TABLE_ADDRESS)
    if hasattr(t, "set_core_vector_table"):
        LOG.info("did_reset: re-apply vector from 0x%08X", VECTOR_TABLE_ADDRESS)
        t.set_core_vector_table()
