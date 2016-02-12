/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Communication.
 *    This software is the proprietary information of M2C Company.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file m2c8001_int.c
 *  \brief
 *  $Revision$
 *  $Date$
 *  \details
 *
 * ------------------------------------------------------------------------------------------------
 */

/**************************************************************************************************
 *   INCLUDES
 *************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "typedef.h"
#include "m2c8001.h"
#include <platform.h>
#include "m2c8001_int.h"

/**************************************************************************************************
 *   MACROS
 *************************************************************************************************/

/**************************************************************************************************
 *   CONSTANTS AND DEFINES
 *************************************************************************************************/

/**************************************************************************************************
 *   TYPEDEFS
 *************************************************************************************************/

/**************************************************************************************************
 *   GLOBAL VARIABLES
 *************************************************************************************************/

/**************************************************************************************************
 *   GLOBAL FUNCTIONS
 *************************************************************************************************/


void INT_IrqEn(unsigned int mask, int edge, int neg)//void enableIntr(unsigned int mask, int edge, int neg)
{
    if(edge)
        INTC->HW1TRIGGERMODE |= mask;
    else
        INTC->HW1TRIGGERMODE &= ~mask;

    if(neg)
        INTC->HW1TRIGGERLEVEL |= mask;
    else
        INTC->HW1TRIGGERLEVEL &= ~mask;

    INTC->HW1ENABLE |= mask;

#if 0
	if (edge)
		outw(INTC_BASE + IRQTMR_OFFSET, inw(INTC_BASE + IRQTMR_OFFSET) | mask);     //Trigger Mode , edge
	else
		outw(INTC_BASE + IRQTMR_OFFSET, inw(INTC_BASE + IRQTMR_OFFSET) & ~mask);    //Trigger Mode, level

	if (neg)
		outw(INTC_BASE + IRQTLR_OFFSET, inw(INTC_BASE + IRQTLR_OFFSET) | mask);     //Trigger Level, active low
	else
		outw(INTC_BASE + IRQTLR_OFFSET, inw(INTC_BASE + IRQTLR_OFFSET) & ~mask);    //Trigger Level, active high /* Joe updated */

	outw(INTC_BASE + IRQER_OFFSET, inw(INTC_BASE + IRQER_OFFSET) | mask);           //Enable Register
#endif

}

void INT_IrqDis(unsigned int mask)
{
    INTC->HW1ENABLE &= ~mask;
    //outw(INTC_BASE + IRQER_OFFSET, inw(INTC_BASE + IRQER_OFFSET) & ~mask);
}

void INT_IrqStsClr(unsigned int mask)
{
    INTC->HW1INTRCLEAR = (1 << mask);
    //outw(INTC_BASE + IRQICR_OFFSET, 1 << mask);
}


void INT_FiqEn(unsigned int mask, int edge, int neg)
{

    if(edge)
    INTC->HW0TRIGGERMODE |= mask;
    else
    INTC->HW0TRIGGERMODE &= ~mask;

    if(neg)
    INTC->HW0TRIGGERLEVEL |= mask;
    else
    INTC->HW0TRIGGERLEVEL &= ~mask;

    INTC->HW0ENABLE |= mask;

#if 0
	if (edge)
		outw(INTC_BASE + FIQTMR_OFFSET, inw(INTC_BASE + FIQTMR_OFFSET) | mask);     //Trigger Mode , edge
	else
		outw(INTC_BASE + FIQTMR_OFFSET, inw(INTC_BASE + FIQTMR_OFFSET) & ~mask);    //Trigger Mode, level

	if (neg)
		outw(INTC_BASE + FIQTLR_OFFSET, inw(INTC_BASE + FIQTLR_OFFSET) | mask);     //Trigger Level, active high
	else
		outw(INTC_BASE + FIQTLR_OFFSET, inw(INTC_BASE + FIQTLR_OFFSET) & ~mask);    //Trigger Level, active low

	outw(INTC_BASE + FIQER_OFFSET, inw(INTC_BASE + FIQER_OFFSET) | mask);           //Enable Register
#endif

}

void INT_FiqDis(unsigned int mask)
{
    INTC->HW0ENABLE &= ~mask;
    //outw(INTC_BASE + FIQER_OFFSET, inw(INTC_BASE + FIQER_OFFSET) & ~mask);
}

void INT_FiqStsClr(unsigned int mask)
{
    INTC->HW0INTRCLEAR = (1<<mask);
    //outw(INTC_BASE + FIQICR_OFFSET, 1 << mask);
}

void INT_GblIsrEn(void)
{
    GIE_ENABLE();
}

void INT_GblIsrDis(void)
{
    GIE_DISABLE();
}


void INT_IntReset(void)
{
    INTC->HW1ENABLE = INT_ER_INIT;
    INTC->HW1INTRCLEAR = INT_CLEAR_VALUE;

    INTC->HW0ENABLE = INT_ER_INIT;
    INTC->HW0INTRCLEAR = INT_CLEAR_VALUE;
}


