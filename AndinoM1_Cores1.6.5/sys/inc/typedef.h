/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Comm.
 *    This software is the proprietary information of M2C Comm.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file platform.h
 *  \brief Platform dependent definitions, macros.
 *  $Revision:  $
 *  $Date:  $
 *  \details  all self defined types goes here
 *
 *
 * ------------------------------------------------------------------------------------------------
 */

#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

/**************************************************************************************************
 *   INCLUDES
 *************************************************************************************************/

/**************************************************************************************************
 *   MACROS
 *************************************************************************************************/

/**************************************************************************************************
 *   TYPEDEFS
 *************************************************************************************************/

/**
 * Integers' type re-definitions, to be move to types.h if necessary
 */
typedef   unsigned char     u8;
typedef   unsigned short     u16;
typedef   unsigned int     u32;
typedef   unsigned long long int u64;

typedef   char              s8;
typedef   short             s16;
typedef   int               s32;
typedef   long long int     s64;

#ifndef NULL
#define NULL        (0)
#endif

#ifndef INLINE
#define INLINE  inline
#endif


#define   __R   volatile const      /* Read only  */
#define   __W   volatile            /* Write only    */
#define   __RW  volatile            /* Read/Write  */



#endif /* _TYPEDEF_H_ */
