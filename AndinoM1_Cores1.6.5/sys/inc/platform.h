/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Comm.
 *    This software is the proprietary information of M2C Comm.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file platform.h
 *  \brief Platform dependent definitions, macros.
 *  $Date: 2014-04-14 
 *
 *
 * ------------------------------------------------------------------------------------------------
 */
#ifndef _PLATFORM_H_
#define _PLATFORM_H_

/**************************************************************************************************
 *   INCLUDES
 *************************************************************************************************/
#include "n801_asm.h"
#include "typedef.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/**************************************************************************************************
 *   MACROS
 *************************************************************************************************/


/**************************************************************************************************
 *   TYPEDEFS
 *************************************************************************************************/

/**************************************************************************************************
 *  Global Prototypes
 *************************************************************************************************/
#define MEMCPY(des, src, n) __builtin_memcpy ((des), (src), (n))
#define MEMSET(s, c, n) __builtin_memset ((s), (c), (n))
#define MEMCMP(s1, s2, n)	 __builtin_memcmp ((s1), (s2), (n))

#define	inw(reg)		(*((volatile unsigned int *) (reg)))
#define	outw(reg, data) 	((*((volatile unsigned int *)(reg)))=(unsigned int)(data))
#define	inh(reg)		(*((volatile unsigned short *) (reg)))
#define	outh(reg, data) 	((*((volatile unsigned short *)(reg)))=(unsigned int)(data))

#ifndef __XTAL
#define __XTAL      (24000000UL)	/* HXT */
#endif
#define __RTC_32K (32768UL)		/* LXT */
#define MHz 1000000


#define ILM_BASE            (0x100000)
#ifdef DLM_8K
#define DLM_BASE            (0x400000)
#define DLM_SIZE            (0x2000)
#else
#define DLM_BASE            (0x400000)
#define DLM_SIZE            (0x4000)
#endif



#define INCR_DIV(_a_,_b_)                   (_a_%_b_)?((_a_/_b_)+1):(_a_/_b_)

#define CYCLE_IN_NS(_clk_)                  (1000/(_clk_/MHz))
#define NS_TO_CYCLE(_clk_, _ns_)            (_ns_ < CYCLE_IN_NS(_clk_)) ? 1 : INCR_DIV(_ns_,CYCLE_IN_NS(_clk_))
#define US_TO_CYCLE(_clk_, _us_)            (_clk_/MHz)*(_us_)
#define MS_TO_CYCLE(_clk_, _ms_)            US_TO_CYCLE(_clk_, _ms_*1000)

#endif /* PLATFORM_H_ */
