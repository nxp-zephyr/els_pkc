/*
 *     Copyright 2022 NXP
 *     All rights reserved.
 *
 *     SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcux_pkc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief PKC Init after power down.
 *
 * This function enables RAM interleave, clocks, zeroize the PKC RAM and reset PKC peripheral.
 * Normally all of these actions are done automatically by boot ROM, but if an application uses Power Down mode
 * this function must be called before using PKC after wake-up.
 *
 * param base PKC peripheral address.
 *
 * return kStatus_Success upon success, kStatus_Fail otherwise
 */
status_t PKC_PowerDownWakeupInit(PKC_Type *base)
{
    /* set PKC RAM to interleave mode */
    SYSCON->RAM_INTERLEAVE = SYSCON_RAM_INTERLEAVE_INTERLEAVE_MASK;

    /* Reset PKC */
    RESET_PeripheralReset(kPKC_RST_SHIFT_RSTn);
    /* enable PKC clock */
    CLOCK_EnableClock(kCLOCK_Pkc);

    /* Zeroize the PKC RAM */
    for (int i = 0; i < PKC_RAM_SIZE / sizeof(uint32_t); i++)
    {
        ((uint32_t *)PKC_RAM_ADDR)[i] = 0x0;
    }

    return kStatus_Success;
}

/*!
 * brief PKC Init after power down.
 *
 * This function enables RAM interleave, clocks and reset PKC peripheral.
 *
 * param base PKC peripheral address.
 *
 * return kStatus_Success upon success, kStatus_Fail otherwise
 */
status_t PKC_InitNoZeroize(PKC_Type *base)
{
    /*Not applicable for RW610, should be in a pre-processor TODO*/
    /* set PKC RAM to interleave mode */
    SYSCON->RAM_INTERLEAVE = SYSCON_RAM_INTERLEAVE_INTERLEAVE_MASK;

    /* Reset PKC */
    RESET_PeripheralReset(kPKC_RST_SHIFT_RSTn);
    /* enable PKC clock */
    CLOCK_EnableClock(kCLOCK_Pkc);

    return kStatus_Success;
}