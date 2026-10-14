//###########################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file (G32R502 EVAL, CANA).
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules.
// Call this function in your application if you wish to do all module
// initialization.
// If you wish to not use some of the initializations, instead of the
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
    WRPRT_DISABLE;

    PinMux_init();
    CAN_init();

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// PIN MUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANTXA);
}

//*****************************************************************************
//
// CAN Configurations
//
//*****************************************************************************
void CAN_init()
{
    CAN_initModule(myCAN0_BASE);

    //
    // CANA bit clock = APBCLK.
    //
    CAN_selectClockSource(myCAN0_BASE, CAN_CLOCK_SOURCE_APB);

    CAN_setBitTiming(myCAN0_BASE, 7, 0, 15, 7, 3);
    CAN_enableTestMode(myCAN0_BASE, CAN_TEST_EXTLBEN);

    CAN_setupMessageObject(myCAN0_BASE, 1, myCAN0_MessageObj1_ID,
                           CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_RX, 0, 0, 8);

    CAN_setupMessageObject(myCAN0_BASE, 2, myCAN0_MessageObj2_ID,
                           CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_RXTX_REMOTE, 0, 0, 8);

    CAN_setupMessageObject(myCAN0_BASE, 3, myCAN0_MessageObj3_ID,
                           CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_TX_REMOTE, 0, 0, 0);

    CAN_startModule(myCAN0_BASE);
}
