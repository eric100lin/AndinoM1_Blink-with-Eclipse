/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Comm.
 *    This software is the proprietary information of M2C Comm.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file newton_uart.c
 *  \brief NEWTON UART driver
 *  $Date: 2014-04-14
 *
 *
 * ------------------------------------------------------------------------------------------------
 */

/***********************************************************************************************
*   INCLUDES
************************************************************************************************/
#include "m2c8001_uart.h"
#include "m2c8001_sys.h"
#include "m2c8001_int.h"

/***********************************************************************************************
*   MARCOS
************************************************************************************************/
#define CHECK_UART_PORT(port)			((port == UART0) || (port == UART1))
#define CHECK_UART_PARITY(parity)		((parity==UART_DRV_PARITY_NONE) || (parity==UART_DRV_PARITY_ODD) || (parity==UART_DRV_PARITY_EVEN) || (parity==UART_DRV_PARITY_ONE) || (parity==UART_DRV_PARITY_ZERO))
#define CHECK_UART_DATABIT(databit)	((databit==UART_DRV_DATABITS_5) || (databit==UART_DRV_DATABITS_6) || (databit==UART_DRV_DATABITS_7) || (databit==UART_DRV_DATABITS_8))
#define CHECK_UART_STOPBIT(stopbit)	((stopbit==UART_DRV_STOPBITS_1) || (stopbit==UART_DRV_STOPBITS_1_5))

#define CHECK_UART_PSR_IS_OVERFLOW(val)  (val > 31)

#define CHECK_UART_BAUDRATE_IS_UNDER_3(expBr,relBr)  ((expBr>relBr)?(expBr-relBr)*100/relBr <3:(relBr-expBr)*100/expBr<3)


/***********************************************************************************************
*   GLOBAL VARIABLES
************************************************************************************************/
DRVUART_Callback *gUart0Callback;
DRVUART_Callback *gUart1Callback;

#define UART_MAX_RCV_BUF_SIZ	256
UART_TypeDef *gUartConsole = UART0;
char uartRcvBuf[UART_MAX_RCV_BUF_SIZ];
volatile unsigned int uartRcvHead = 0;
volatile unsigned int uartRcvTail = 0;

/***********************************************************************************************
*   LOCAL FUNCTIONS
************************************************************************************************/

void UART0_Isr(int unused)
{
    u32 u32Intsts;

    u32Intsts =  UART0->IIR;
    //UART_DBG("UART0_Isr UART0->IIR:%x\r\n",u32Intsts);
    //if(gUart0Callback)
    //    gUart0Callback(u32Intsts);


    //if(gUartConsole->LSR & UART_LSR_DATA_READY)
	  if(u32Intsts & UART_IIR_RDA)
    {
        uartRcvBuf[uartRcvTail] = gUartConsole->RBR;
        if((uartRcvTail + 1) == UART_MAX_RCV_BUF_SIZ)
            uartRcvTail = 0;
        else
            uartRcvTail++;
    }
}

void UART1_Isr(int unused)
{
    u32 u32Intsts;

    u32Intsts =  UART1->IIR;
    if(gUart1Callback)
        gUart1Callback(u32Intsts);
}

static u32 UART_GetUartClcok(UART_TypeDef *tUart)
{
    u32 clk = 0;
    u8 div =0;
    if((u32)tUart == UART0_BASE){
        switch(CGU->DIPCLKSEL & DIP_CLK_SEL_UART0_MASK){
            case DIP_CLK_SEL_UART0_XO:
                clk = __XTAL;
                break;
            case DIP_CLK_SEL_UART0_32K:
                clk = __RTC_32K;
                break;
            case DIP_CLK_SEL_UART0_CPUPLL:
                clk = SYS_GetCpupllFreq()*MHz;
                div =(CGU->PCLKDIV & PCLK_UART0_CPUPLL_DIV) >> 8;
                break;
        }
    }
    else if((u32)tUart == UART1_BASE){
        switch(CGU->DIPCLKSEL & DIP_CLK_SEL_UART1_MASK){
            case DIP_CLK_SEL_UART1_XO:
                clk = __XTAL;
                break;
            case DIP_CLK_SEL_UART1_32K:
                clk = __RTC_32K;
                break;
            case DIP_CLK_SEL_UART1_CPUPLL:
                clk = SYS_GetCpupllFreq()*MHz;
                div =(CGU->PCLKDIV & PCLK_UART1_CPUPLL_DIV) >> 12;
                break;
        }
    }
    return clk/(div+1);
}

/***********************************************************************************************
*   GLOBAL FUNCTIONS
************************************************************************************************/

void UART_IsrInit(UART_TypeDef *tUart)
{
    if((u32)tUart == UART0_BASE){
        INT_IrqEn(1 << IRQ_UART0_INTR, 0, 0);
        ISR_InsertCb(INT_TYPE_IRQ,IRQ_UART0_INTR,UART0_Isr);
    }
    else if((u32)tUart == UART1_BASE){
        INT_IrqEn(1 << IRQ_UART1_INTR, 0, 0);
        ISR_InsertCb(INT_TYPE_IRQ,IRQ_UART1_INTR,UART1_Isr);
    }
}


/**********************************************************************************************
@brief:Initialize specified UART port
@para:
        -tUart: Specified UART port UART0/UART1
        -tParam.u32BaudRate : Baud rate(Hz)
            UART_DRV_BAUDRATE_38400
            UART_DRV_BAUDRATE_57600
            UART_DRV_BAUDRATE_115200
            UART_DRV_BAUDRATE_230400
            UART_DRV_BAUDRATE_460800
          tParam.u8DataBits : Data bit setting
            UART_DRV_DATABITS_5
            UART_DRV_DATABITS_6
            UART_DRV_DATABITS_7
            UART_DRV_DATABITS_8
          tParam.u8StopBits : Stop bit setting
            UART_DRV_STOPBITS_1
            UART_DRV_STOPBITS_1_5
          tParam.u8Parity : Parity setting
            UART_DRV_PARITY_NONE
            UART_DRV_PARITY_ODD
            UART_DRV_PARITY_EVEN
            UART_DRV_PARITY_ONE
            UART_DRV_PARITY_ZERO
***********************************************************************************************/
void UART_Init(UART_TypeDef *tUart,UART_DATA_t * tParam)
{
    u8 u8DLLval = 5;/*DLL value*/
    u32 u32PSRval; /* PSR value*/
    u32 u32CalBaudrate = 0;
    u8 u8Divider = 16;
    u32 u32Clk;

    if((u32)tUart == UART0_BASE){
        /*Reset and enable UART0 IP*/
        RCU->CSRSWRSTN &= ~RCU_SW_RST_UART0;
        CGU->PIPCLKSW |= PIP_EN_UART0_CLK;
    }
    else if((u32)tUart == UART1_BASE){
         /*Reset and enable UART1 IP*/
        RCU->CSRSWRSTN &= ~RCU_SW_RST_UART1;
        CGU->PIPCLKSW |= PIP_EN_UART1_CLK;
    }

    /*Set UART mode*/
    tUart->MDR =  (tUart->MDR &~UART_MDR_MODE_MASK) |  UART_MDR_MODE_UART;

    /* Set DLAB to 1 */
    tUart->LCR |= UART_LCR_DLAB;

    /*Get current UART clock source frequency */
    u32Clk = UART_GetUartClcok(tUart);

    do{
        u32PSRval = u32Clk + (tParam->u32BaudRate*u8Divider*u8DLLval)/2;

        u32PSRval = u32PSRval / (tParam->u32BaudRate*u8Divider*u8DLLval);

        u32CalBaudrate = u32Clk/(u8DLLval*u32PSRval*u8Divider);
        if(!CHECK_UART_PSR_IS_OVERFLOW(u32PSRval)){
            if(CHECK_UART_BAUDRATE_IS_UNDER_3(tParam->u32BaudRate,u32CalBaudrate)){
                break;
             }
        }
    }while(--u8DLLval>0);

    tUart->DLL = u8DLLval;
	/* DLM = 0 */
    tUart->DLM = 0x0;

    /* Set prescaler value */
    tUart->PSR = u32PSRval;

    /* LCR: Length 8,  parity,  stop bit. */
    tUart->LCR = tParam->u8DataBits | (tParam->u8StopBits << 2) |(tParam->u8Parity << 3);

    /* FCR: Enable FIFO, reset TX and RX. */
    tUart->FCR = UART_FCR_FIFO_ENABLE |UART_FCR_RX_FIFO_RESET | UART_FCR_TX_FIFO_RESET;

    /* IER: Disable all  Interrupt */
    //tUart->IER = 0;
    tUart->IER = 0x1;
}

/***********************************************************************************************
@brief:Disable UART clock
@para:
        -tUart: Specified UART port UART0/UART1
***********************************************************************************************/
void UART_DeInit(UART_TypeDef *tUart)
{
    if((u32)tUart == UART0_BASE){
        CGU->PIPCLKSW &= ~PIP_EN_UART0_CLK;
        disableIntr(1 << IRQ_UART0_INTR);
    }
    else if((u32)tUart == UART1_BASE){
        CGU->PIPCLKSW &= ~PIP_EN_UART1_CLK;
        disableIntr(1 << IRQ_UART1_INTR);
    }
}

/***********************************************************************************************
@brief:Write one byte data to Tx FIFO and transmit data by specified UART
@para:
        -tUart: Specified UART port UART0/UART1
        -u8Data: wirte data
***********************************************************************************************/
void UART_WriteByte(UART_TypeDef *tUart,u8 u8Data)
{
    u32 u32Delay = 0;
    while((tUart->IIR & UART_IIR_TX_FULL) && (u32Delay++ < 0x1000000));    /*Check  tx fifo full */
    tUart->THR = u8Data;
}

/***********************************************************************************************
@brief:Read one byte data from Rx FIFO of specified UART
@para:
        -tUart: Specified UART port UART0/UART1
@ret:
***********************************************************************************************/
u8 UART_ReadByte(UART_TypeDef *tUart)
{
    return tUart->RBR;
}


/***********************************************************************************************
@brief:Write number of  bytes data to Tx FIFO and transmit data by specified UART
@para:
        -tUart: Specified UART port UART0/UART1
        -u8Len: write data number bytes
        -pu8Data:Specify the buffer to transmit the data to UART
@ret: UART_RET_TIMEOUT /UART_RET_SUCCESS
***********************************************************************************************/
u8 UART_Write(UART_TypeDef *tUart,u8 u8Len,const u8 * pu8Data)
{
    u32 u32Delay = 0;
    int i;
    for(i=0;i<u8Len;i++){
            u32Delay = 0;
        while(tUart->IIR & UART_IIR_TX_FULL){
            if(u32Delay++ >= 0x100000)
                return UART_RET_TIMEOUT;
        }
        tUart->THR = *pu8Data++;

    }
    return UART_RET_SUCCESS;
}


/***********************************************************************************************
@brief:Read number of  bytes data from Tx FIFO and transmit data by specified UART
@para:
        -tUart: Specified UART port UART0/UART1
        -u8Len: read data number bytes
        -pu8Data:Specify the buffer to receive the data of UART rx buffer
@ret: UART_RET_TIMEOUT /UART_RET_SUCCESS
***********************************************************************************************/
u8 UART_Read(UART_TypeDef *tUart,u8 u8Len, u8 * pu8Data)
{
    u32 u32Delay = 0;
    int i;
    for(i=0;i<u8Len;i++){
        u32Delay = 0;
        while((tUart->LSR & UART_LSR_DATA_READY) == 0x0){
            if(u32Delay++ >= 0x100000)
                return UART_RET_TIMEOUT;
        }
        *pu8Data++ =  tUart->RBR;

    }
    return UART_RET_SUCCESS;
}

/***********************************************************************************************
@brief:Register UART interrupt callback function
@para:
        -tUart: Specified UART port UART0/UART1
        -cb : UART callback function
***********************************************************************************************/
void UART_RegisterCallback(UART_TypeDef *tUart,DRVUART_Callback cb)
{
    if((u32)tUart == UART0_BASE)
        gUart0Callback = cb;
    else if((u32)tUart == UART1_BASE)
        gUart1Callback = cb;
}

/***********************************************************************************************
@brief:Enable interrupt of  specified UART
@para:
        -tUart: Specified UART port UART0/UART1
        -u32IntFlag: UART enable interrupt flag
            UART_DRV_RDAINT
            UART_DRV_THREINT
            UART_DRV_RLSINT
            UART_DRV_MODEMINT
***********************************************************************************************/
void UART_EnableInt(UART_TypeDef *tUart,u32 u32IntFlag)
{
    tUart->IER = u32IntFlag;
}

/***********************************************************************************************
@brief:Disable interrupt of specified UART
@para:
        -tUart: Specified UART port UART0/UART1
***********************************************************************************************/
void UART_DisableInt(UART_TypeDef *tUart)
{
    tUart->IER = 0x0;
}


/***********************************************************************************************
@brief:Set the trigger level of the RX FIFO interrupt of specified UART
@para:
        -tUart: Specified UART port UART0/UART1
        -u8TrigVal: trigger level value
***********************************************************************************************/
 void UART_SetRxFIFOTrigger(UART_TypeDef *tUart,u8 u8TrigVal)
{
    tUart->FCR = (tUart->FCR &~UART_FCR_RXFIFO_TRGL_MASK) |  u8TrigVal;
}


/***********************************************************************************************
@brief:Set specified UART port clock source
@para:
        -tUart: Specified UART port UART0/UART1
        -u8ClkSrc:UART_CLK_SRC_XO/UART_CLK_SRC_CPULL
************************************************************************************************/
void UART_SetClockSrc(UART_TypeDef *tUart, u8 u8ClkSrc)
{
    /*UART0*/
    if((u32)tUart == UART0_BASE){
        if(u8ClkSrc == UART_CLK_SRC_XO)
            CGU->DIPCLKSEL = (CGU->DIPCLKSEL & ~DIP_CLK_SEL_UART0_MASK) |DIP_CLK_SEL_UART0_XO; //clock source XO
        else if (u8ClkSrc == UART_CLK_SRC_CPULL)
            CGU->DIPCLKSEL = (CGU->DIPCLKSEL & ~DIP_CLK_SEL_UART0_MASK) |DIP_CLK_SEL_UART0_CPUPLL; //clock source CPUPLL
    }
    else{
        if(u8ClkSrc == UART_CLK_SRC_XO)
            CGU->DIPCLKSEL = (CGU->DIPCLKSEL & ~DIP_CLK_SEL_UART1_MASK) |DIP_CLK_SEL_UART1_XO; //clock source XO
        else if (u8ClkSrc == UART_CLK_SRC_CPULL)
            CGU->DIPCLKSEL = (CGU->DIPCLKSEL & ~DIP_CLK_SEL_UART1_MASK) |DIP_CLK_SEL_UART1_CPUPLL; //clock source CPUPLL
    }

}

/***********************************************************************************************
@brief:Set specified UART port CPUPLL divider
@para:
        -tUart: Specified UART port UART0/UART1
        -u8Div:divider value 1~16
************************************************************************************************/
void UART_SetCpupllDivider(UART_TypeDef *tUart, u8 u8Div)
{
    if((u32)tUart == UART0_BASE){
        CGU->PCLKDIV = (CGU->PCLKDIV &~PCLK_UART0_CPUPLL_DIV) |(u8Div << 8);
    }
    else{
        CGU->PCLKDIV = (CGU->PCLKDIV &~PCLK_UART1_CPUPLL_DIV) |(u8Div << 12);
    }
}

u8 uartDataCheck(void)
{
    if(uartRcvTail != uartRcvHead)
        return 1;
    else
        return 0;
}

s8 uartReadByte(void)
{
    volatile char ch = ' ';

    ch = uartRcvBuf[uartRcvHead++];
    if(uartRcvHead >= UART_MAX_RCV_BUF_SIZ)
        uartRcvHead = 0;

    return ch;
}

s8 uartPeekByte(void)
{
    return uartRcvBuf[uartRcvHead];
}

void uartFlush(UART_TypeDef *tUart)
{
    tUart->IER = 0x0;

    while(1)
    {
	      if(uartDataCheck())
	      {
	    	    uartReadByte();
	    	}
	    	else
	    	    break;
    }

	  tUart->FCR = UART_FCR_FIFO_ENABLE |UART_FCR_RX_FIFO_RESET | UART_FCR_TX_FIFO_RESET;
    uartRcvHead = 0;
    uartRcvTail = 0;
    tUart->IER = 0x1;
}
