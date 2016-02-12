/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Comm.
 *    This software is the proprietary information of M2C Comm.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file m2c8001_uart.h
 *  \brief M2C8001 Uart functions prototypes
 *  $Date: 2014-04-14 
 *
 *
 * ------------------------------------------------------------------------------------------------
 */


#ifndef M2C8001_UART_H_
#define M2C8001_UART_H_

/**************************************************************************************************
 *   INCLUDES
 *************************************************************************************************/
#include "m2c8001.h"


/***********************************************************************************************
*   MARCOS
************************************************************************************************/
/*UART driver returnn value*/
#define UART_RET_TIMEOUT  (0)
#define UART_RET_SUCCESS  (1)

/***********************Uart Driver define******************************/

#define UART_DRV_BAUDRATE_38400    (38400)
#define UART_DRV_BAUDRATE_57600    (57600) 
#define UART_DRV_BAUDRATE_115200   (115200)  
#define UART_DRV_BAUDRATE_230400   (230400)  
#define UART_DRV_BAUDRATE_460800   (460800)  

#define UART_DRV_DATABITS_5   (0x0)  
#define UART_DRV_DATABITS_6   (0x1)  
#define UART_DRV_DATABITS_7   (0x2)
#define UART_DRV_DATABITS_8   (0x3)

#define UART_DRV_STOPBITS_1     (0x0)
#define UART_DRV_STOPBITS_1_5   (0x1)

#define UART_DRV_PARITY_NONE    (0x0)
#define UART_DRV_PARITY_ODD     (0x1)
#define UART_DRV_PARITY_EVEN    (0x3)
#define UART_DRV_PARITY_ONE     (0x5)
#define UART_DRV_PARITY_ZERO    (0x7)


#define UART_DRV_RDAINT     (0x1)
#define UART_DRV_THREINT    (0x2)
#define UART_DRV_RLSINT     (0x8)
#define UART_DRV_MODEMINT   (0x10)


/*Select UART clock source*/
#define UART_CLK_SRC_32K   (1)
#define UART_CLK_SRC_XO    (2)
#define UART_CLK_SRC_CPULL (3)


/***********************************************************************************************
*   TYPEDEFS
************************************************************************************************/
typedef void (DRVUART_Callback)(u32 u32IntSts);


typedef struct
{
    u32 u32BaudRate;
    u8 u8DataBits;
    u8 u8StopBits;
    u8 u8Parity;
}UART_DATA_t;


/***********************************************************************************************
*   SOC UART definition
************************************************************************************************/

/********************* Bit definition of UART Interrupt Enable Register **********************/
#define UART_IER_RDA        (0x1 << 0)   /*Enable interrupt of Received Data Available*/ 
#define UART_IER_THRE       (0x1 << 1)   /*Enable interrupt of Transmitter Holding Register Empty */
#define UART_IER_RLS        (0x1 << 3)   /*Enable interrupt of Receive Line Status */
#define UART_IER_MODEM      (0x1 << 4)   /*Enable interrupt of modem status*/



/********************* Bit definition of UART Line Control Register(LCR) **********************/
#define UART_LCR_WL0        (0x1 << 0) 
#define UART_LCR_WL1	    (0x1 << 1 )
#define UART_LCR_STOPBITS    (0x1 <<2)
#define UART_LCR_PARITY_EN    (0x1 <<3)
#define UART_LCR_EVEN_PARITY    (0x1 <<4)
#define UART_LCR_STICK_PARITY    (0x1 <<5)
#define UART_LCR_SET_BREAK_PARITY    (0x1 <<6)
#define UART_LCR_DLAB	    (0x1 << 7)


/********************* Bit definition of UART Mode Definition Register(MDR) **********************/
#define UART_MDR_MODE_UART      (0x0) 
#define UART_MDR_MODE_SIR		(0x1 )
#define UART_MDR_MODE_FIR		(0x2)
#define UART_MDR_MODE_MASK	(0x3)


/********************* Bit definition of UART Interrupt Identification Register(IIR,0x8) **********************/
#define UART_IIR_NONE      (0x0) 
#define UART_IIR_RLS       (0x6 )
#define UART_IIR_RDA		(0x4)
#define UART_IIR_CRT		(0xC)
#define UART_IIR_MASK	(0xF)
#define UART_IIR_TX_FULL	(0x1 << 4)


/********************* Bit definition of UART FIFO Control Register **********************/
#define UART_FCR_FIFO_ENABLE      (0x1 << 0) 
#define UART_FCR_RX_FIFO_RESET    (0x1 << 1 )
#define UART_FCR_TX_FIFO_RESET    (0x1 << 2)
#define UART_FCR_DMA_MODE    (0x1 << 3)

#define UART_FCR_RXFIFO_TRGL_1    (0x00)
#define UART_FCR_RXFIFO_TRGL_4    (0x40)
#define UART_FCR_RXFIFO_TRGL_8    (0x60)
#define UART_FCR_RXFIFO_TRGL_14    (0xC0)
#define UART_FCR_RXFIFO_TRGL_MASK    (0xC0)

/********************* Bit definition of UART Line Status Register(LSR,0x14) **********************/
#define UART_LSR_DATA_READY        (0x1 << 0) 
#define UART_LSR_OVER_ERR          (0x1 << 1 )
#define UART_LSR_PARITY_ERR        (0x1 << 2)
#define UART_LSR_FRAMING_ERR       (0x1 << 3)
#define UART_LSR_BREAK_INT         (0x1 << 4)
#define UART_LSR_THR_EMPTY         (0x1 << 5)
#define UART_LSR_DLAB              (0x1 << 7)


/**************************************************************************************************
 *   GLOBAL PROTOTYPES
 *************************************************************************************************/
void UART_IsrInit(UART_TypeDef *tUart);
void UART_Init(UART_TypeDef *tUart,UART_DATA_t * tParam);
void UART_SetConsole(UART_TypeDef *tUart);
void UART_DeInit(UART_TypeDef *tUart);
void UART_WriteByte(UART_TypeDef *tUart,u8 u8Data);
u8 UART_ReadByte(UART_TypeDef *tUart);
u8 UART_Write(UART_TypeDef *tUart,u8 u8Len,const u8 * pu8Data);
u8 UART_Read(UART_TypeDef *tUart,u8 u8Len, u8 * pu8Data);

void UART_EnableInt(UART_TypeDef *tUart,u32 u32IntFlag);
void UART_DisableInt(UART_TypeDef *tUart);
void UART_RegisterCallback(UART_TypeDef *tUart,DRVUART_Callback cb);
void UART_SetRxFIFOTrigger(UART_TypeDef *tUart,u8 u8TrigVal);

void UART_SetClockSrc(UART_TypeDef *tUart, u8 u8ClkSrc);
void UART_SetCpupllDivider(UART_TypeDef *tUart, u8 u8Div);

u8 uartDataCheck(void);
s8 uartReadByte(void);
s8 uartPeekByte(void);
void uartFlush(UART_TypeDef *tUart);

#endif /* M2C8001_UART_H_ */
