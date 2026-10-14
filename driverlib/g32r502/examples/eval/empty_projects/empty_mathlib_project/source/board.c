//#############################################################################
//
// FILE:    board.c
//
// TITLE:   Board source file (G32R502 eval)
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
void Board_init(void)
{
    WRPRT_DISABLE;

    PinMux_init();
    GPIO_init();

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// PIN MUX Configurations
//
//*****************************************************************************
void PinMux_init(void)
{
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(void)
{
    GPIO_setDrivingCapability(myGPIOOutput_LED1, GPIO_DRIVE_LEVEL_VERY_HIGH);
    GPIO_setDirectionMode(myGPIOOutput_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(myGPIOOutput_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myGPIOOutput_LED1, GPIO_QUAL_SYNC);
}
