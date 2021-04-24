/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/01     Bernard      The first version
 */

#include <rthw.h>

#include <board.h>
#include <RV32M1_ri5cy.h>

typedef void (*irq_handler_t)(void);
extern const irq_handler_t isrTable[];

void SystemIrqHandler(uint32_t mcause)
{
    uint32_t intNum;

    if (mcause & 0x80000000) /* For external interrupt. get the value of the 31st bit*/
    {
        intNum = mcause & 0x1FUL; // get the values of the 0th~4th bits

        /* Clear pending flag in EVENT unit .*/
        // I will rewrite this line, remember include event.h
        EVENT_UNIT->INTPTPENDCLEAR = (1U << intNum);

        /* Now call the real irq handler for intNum */
        isrTable[intNum]();
    }
}
