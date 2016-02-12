/*
 * Newton.h
 *
 *  Created on: 2013/11/28
 *      Author: joe.hsu
 */


#ifndef  _M2C8001_H
#define  _M2C8001_H

/**************************************************************************************************
 *   INCLUDES
 *************************************************************************************************/
#include "platform.h"
#include "typedef.h"

/**************************************************************************************************
 *   MACROS
 *************************************************************************************************/
#ifndef NULL
#define NULL            (0)
#endif

#define TRUE	   	    (1)
#define FALSE   	    (0)

#define ENABLE          (1)
#define DISABLE         (0)

/* interrupt sources */
/*IRQ*/
#define IC_I2C      (1 << IRQ_I2C_INTR)

#define IC_TIMER1   (1 << IRQ_TM1_INTR)
#define IC_TIMER2   (1 << IRQ_TM2_INTR)
#define IC_TIMER3   (1 << IRQ_TM3_INTR)
#define IC_UART0    (1 << IRQ_UART0_INTR)
#define IC_UART1    (1 << IRQ_UART1_INTR)
#define IC_SSP0     (1 << IRQ_SSP0_INTR)
#define IC_SSP1     (1 << IRQ_SSP1_INTR)
#define IC_DMAC          (1 << IRQ_DMAC_INTR)


/*FIQ*/
#define IC_WDT      (1 << FIQ_WDT_INTR)
#define IC_RTC        (1 << FIQ_RTC_INTR)
#define IC_GPIO     (1 << FIQ_GPIO_INTR)

/************************************
 *  Newton MAC MARCOS      *
 ************************************/
//0x00
#define RX_FIFO_REWIND      (1)
#define RX_FIFO_CLR         (1 << 1)
#define RX_FIFO_MCU_READ    (1 << 4)
#define RX_FIFO_MCU_WRITE   (1 << 5)
#define TX_FIFO_REWIND      (1 << 16)
#define TX_FIFO_CLR         (1 << 17)
#define TX_FIFO_MCU_READ    (1 << 20)
#define TX_FIFO_MCU_WRITE   (1 << 21)

//0x14
#define FCS_EN              (1)
#define MAC_RX_EN           (1 << 1)
#define BKN_SADR_CHK_EN     (1 << 2)
#define RX_FRM_RPT_DROP_EN  (1 << 3)
#define PROMISC_MD          (1 << 4)
#define FMT_ZB_SEL          (1 << 5)
#define BBP_BYPASS          (1 << 7)
#define CONNECTION_CONTROL  (0xFF << 8)
#define RX2DMA_AUTO         (1 << 16)

//0x28
#define RX2ACK_DELAY        (0xFFF << 8)
#define TX_BEACON_EN        (1)
#define DAT_RATE_SEL        (0xF << 4)
#define MODE_ED             (1 << 5)
#define MODE_RT             (1 << 6)
#define MODE_AP             (1 << 7)

//0x38
#define BACKOFF_PERIOD      (0x3F)
#define TOTAL_SLOT          (0xFF << 16)

//0x58
#define RX_SLICE            (0xFF)
#define TX_SLICE            (0xFF << 8)

//0x84
#define MAC_TIMER_EN        (1)
#define GEN_SLICE_TICK      (0xFF << 8)
#define GEN_SLOT_TICK       (0xFF << 16)
#define MISS_RXBEACON_NUM   (0xFF << 24)

//0x90
#define SLOT_CNT_RO         (0xFF << 15)

//0x94
#define CCA_REQ_P           (1 << 31)

//0x98
#define MAX_FRAME_RETRIES   (0xF)
#define DMA2TX_AUTO         (1 << 4)
#define MAC_TX_EN_P         (1 << 5)
#define START_BEACON_PERIOD (1 << 6)
#define SLOTTED             (1 << 8)

//0x9C
#define ACK_WAIT_DURATION   (0xFF)
#define MIN_SIFS            (0xFF << 8)
#define MIN_LIFS            (0xFF << 16)
#define MAX_SIFS            (0xFF << 24)

//0xB4
#define RELOAD_SLOT_CNT     (0xFF)
#define RELOAD_TIME_P       (1 << 8)
#define RELOAD_TIME_AUTO    (1 << 12)

//0xCC
#define CCA_REPORT_CLEAR_P  (1 << 3)
#define CCA_STATUS_RO       (1 << 6)
#define CCA_CONFIRM_RO      (1 << 7)





/******************************************************************
        TOP register mapping
 *****************************************************************/


/********************* Bit definition of TOP MISC(0x14) register **********************/
#define MISC_SPI0_CS1    (0x1 << 0)
#define MISC_SPI0_CS2    (0x1 << 1)

#define MISC_SW_FIQ0     (0x1 << 4)
#define MISC_SW_FIQ1     (0x1 << 5)
#define MISC_SW_IRQ0     (0x1 << 6)
#define MISC_SW_IRQ1     (0x1 << 7)



/********************* Bit definition of TOP PADMUX0(0x20) register **********************/
#define PAD_GPIO1_MUX_GPIO1       (0x0 << 2)
#define PAD_GPIO1_MUX_PWM0        (0x1 << 2)
#define PAD_GPIO1_MUX_MASK        (0x3 << 2)

#define PAD_GPIO2_MUX_GPIO2       (0x0 << 4)
#define PAD_GPIO2_MUX_PWM1        (0x1 << 4)
#define PAD_GPIO2_MUX_MASK        (0x3 << 4)

#define PAD_GPIO3_MUX_GPIO3       (0x0 << 6)
#define PAD_GPIO3_MUX_MASK        (0x3 << 6)

#define PAD_GPIO4_MUX_GPIO4       (0x0 << 8)
#define PAD_GPIO4_MUX_SPI0_CS2    (0x1 << 8)
#define PAD_GPIO4_MUX_MASK        (0x3 << 8)

#define PAD_GPIO5_MUX_GPIO5       (0x0 << 10)
#define PAD_GPIO5_MUX_SPI1_MISO   (0x1 << 10)
#define PAD_GPIO5_MUX_MASK        (0x3 << 10)

#define PAD_GPIO6_MUX_GPIO6       (0x0 << 12)
#define PAD_GPIO6_MUX_MASK        (0x3 << 12)

#define PAD_GPIO7_MUX_GPIO7       (0x0 << 14)
#define PAD_GPIO7_MUX_SPI0_CS1    (0x1 << 14)
#define PAD_GPIO7_MUX_MASK        (0x3 << 14)

#define PAD_GPIO8_MUX_GPIO8       (0x0 << 16)
#define PAD_GPIO8_MUX_MASK        (0x3 << 16)

#define PAD_GPIO9_MUX_GPIO9       (0x0 << 18)
#define PAD_GPIO9_MUX_SPI1_MOSI   (0x1 << 18)
#define PAD_GPIO9_MUX_EXT_INT0    (0x2 << 18)
#define PAD_GPIO9_MUX_MASK        (0x3 << 18)

#define PAD_GPIO10_MUX_GPIO10     (0x0 << 20)
#define PAD_GPIO10_MUX_SPI1_CS    (0x1 << 20)
#define PAD_GPIO10_MUX_XO_OUT     (0x2 << 20)
#define PAD_GPIO10_MUX_MASK       (0x3 << 20)

#define PAD_GPIO11_MUX_GPIO11     (0x0 << 22)
#define PAD_GPIO11_MUX_SPI1_CLK   (0x1 << 22)
#define PAD_GPIO11_MUX_MASK       (0x3 << 22)

#define PAD_GPIO12_MUX_GPIO12     (0x0 << 24)
#define PAD_GPIO12_MUX_EXT_INT1   (0x1 << 24)
#define PAD_GPIO12_MUX_MASK       (0x3 << 24)

#define PAD_GPIO13_MUX_GPIO13     (0x0 << 26)
#define PAD_GPIO13_MUX_MASK       (0x3 << 26)

#define PAD_GPIO14_MUX_GPIO14     (0x0 << 28)
#define PAD_GPIO14_MUX_MASK       (0x3 << 28)

#define PAD_GPIO15_MUX_GPIO15     (0x0 << 30)
#define PAD_GPIO15_MUX_EBI_ADDR7  (0x3 << 30)
#define PAD_GPIO15_MUX_MASK       (0x3 << 30)

/********************* Bit definition of TOP PADMUX1 register(0x24) **********************/
#define PAD_GPIO16_MUX_GPIO16     (0x0 << 0)
#define PAD_GPIO16_MUX_MASK       (0x3 << 0)

#define PAD_GPIO17_MUX_GPIO17     (0x0 << 2)
#define PAD_GPIO17_MUX_MASK       (0x3 << 2)

#define PAD_GPIO18_MUX_GPIO18     (0x0 << 4)
#define PAD_GPIO18_MUX_MASK       (0x3 << 4)

#define PAD_UART0_TX_MUX_UART0_TX (0x0 << 6)
#define PAD_UART0_TX_MUX_GPIO19   (0x1 << 6)
#define PAD_UART0_TX_MUX_MASK     (0x3 << 6)

#define PAD_UART0_RX_MUX_UART0_RX (0x0 << 8)
#define PAD_UART0_RX_MUX_GPIO20   (0x1 << 8)
#define PAD_UART0_RX_MUX_MASK     (0x3 << 8)

#define PAD_I2C_CLK_MUX_I2C_CLK   (0x0 << 10)
#define PAD_I2C_CLK_MUX_GPIO21    (0x1 << 10)
#define PAD_I2C_CLK_MUX_PWM2    (0x2 << 10)
#define PAD_I2C_CLK_MUX_MASK      (0x3 << 10)

#define PAD_I2C_SDA_MUX_I2C_SDA   (0x0 << 12)
#define PAD_I2C_SDA_MUX_GPIO22    (0x1 << 12)
#define PAD_I2C_SDA_MUX_PWM3      (0x2 << 12)
#define PAD_I2C_SDA_MUX_MASK      (0x3 << 12)

#define PAD_UART1_RX_MUX_UART1_RX (0x0 << 14)
#define PAD_UART1_RX_MUX_GPIO23   (0x1 << 14)
#define PAD_UART1_RX_MUX_MASK     (0x3 << 14)

#define PAD_UART1_TX_MUX_UART1_TX (0x0 << 16)
#define PAD_UART1_TX_MUX_GPIO24   (0x1 << 16)
#define PAD_UART1_TX_MUX_MASK     (0x3 << 16)

#define PAD_SPI0_MOSI_MUX_SPI0_MOSI  (0x0 << 18)
#define PAD_SPI0_MOSI_MUX_GPIO25  (0x1 << 18)
#define PAD_SPI0_MOSI_MUX_MASK    (0x3 << 18)

#define PAD_SPI0_MISO_MUX_SPI0_MISO  (0x0 << 20)
#define PAD_SPI0_MISO_MUX_GPIO26  (0x1 << 20)
#define PAD_SPI0_MISO_MUX_MASK    (0x3 << 20)

#define PAD_SPI0_CLK_MUX_SPIO_CLK (0x0 << 22)
#define PAD_SPI0_CLK_MUX_GPIO27   (0x1 << 22)
#define PAD_SPI0_CLK_MUX_MASK     (0x3 << 22)

#define PAD_SPI0_CSN_MUX_SPI0_CSN (0x0 << 24)
#define PAD_SPI0_CSN_MUX_GPIO28   (0x1 << 24)
#define PAD_SPI0_CSN_MUX_MASK     (0x3 << 24)

#define EBI_EN (0x1 << 31)


/********************* Bit definition of TOP AGPIOCTRL0 register(0x60) **********************/
#define AGPIO_FUNC_ADGPIO1_MUX_ACMPCH7   (0x2 << 0)
#define AGPIO_FUNC_ADGPIO1_MUX_MASK      (0x3 << 0)

#define AGPIO_FUNC_ADGPIO2_MUX_ACMPCH1   (0x2 << 2)
#define AGPIO_FUNC_ADGPIO2_MUX_MASK      (0x3 << 2)

#define AGPIO_FUNC_ADGPIO3_MUX_ACMPCH2   (0x2 << 4)
#define AGPIO_FUNC_ADGPIO3_MUX_MASK      (0x3 << 4)

#define AGPIO_FUNC_ADGPIO4_MUX_ACMPCH3   (0x2 << 6)
#define AGPIO_FUNC_ADGPIO4_MUX_MASK      (0x3 << 6)

#define AGPIO_FUNC_ADGPIO5_MUX_ACMPCH4   (0x2 << 8)
#define AGPIO_FUNC_ADGPIO5_MUX_MASK      (0x3 << 8)

#define AGPIO_FUNC_ADGPIO6_MUX_ACMPCH5   (0x2 << 10)
#define AGPIO_FUNC_ADGPIO6_MUX_MASK      (0x3 << 10)

#define AGPIO_FUNC_ADGPIO7_MUX_ACMPCH6   (0x2 << 12)
#define AGPIO_FUNC_ADGPIO7_MUX_MASK      (0x3 << 12)

#define AGPIO_FUNC_ADGPIO8_MUX_ACMPVSS   (0x2 << 14)
#define AGPIO_FUNC_ADGPIO8_MUX_MASK      (0x3 << 14)


#define AGPIO_AEN_ADGPIO1_2 (0x1 << 24) /* Enable analogue function for ADGPIO1 and 2*/
#define AGPIO_AEN_ADGPIO3_4 (0x1 << 25) /* Enable analogue function for ADGPIO3 and 4*/
#define AGPIO_AEN_ADGPIO5_6 (0x1 << 26) /* Enable analogue function for ADGPIO5 and 6*/
#define AGPIO_AEN_ADGPIO7_8 (0x1 << 27) /* Enable analogue function for ADGPIO7 and 8*/


/************************************
 *  Newton Flash Controller MARCOS      *
 ************************************/
#define FC_INFO_ACCESS_EN       (1<<2)
#define FC_WRITE_PROTECTION_EN  (1<<9)

#define FC_WRITE_MODE_SEL       (0x3)
#define FC_MASS_ERASE_EN        (1)
#define FC_PROGRAM_DONE         (1<<4)
#define FC_ERASE_DONE           (1<<5)
#define FC_ERASE_INFO_DONE      (1<<6)
#define FC_MASS_ERASE_DONE      (1<<7)
#define FC_STATUS               (1)
#define FC_PROGRAM_ADDR         (0x7FFF)

#define FC_ERASE_PAGE           (0x3F)
#define FC_ERASE_INFO_PAGE      (1<<8)











/******************************************************************
        INTC register mapping
 *****************************************************************/
//#define INTC_BASE              0x00F08000  /* Interrupt Controller base address */
#define IRQSRCR_OFFSET         0x00        /* IRQ(HW1) Source Register offset */
#define IRQER_OFFSET           0x04        /* IRQ(HW1) Enable Register offset */
#define IRQICR_OFFSET          0x08        /* IRQ(HW1) Interrupt Clear Register offset */
#define IRQTMR_OFFSET          0x0C        /* IRQ(HW1) Trigger Mode Register offset */
#define IRQTLR_OFFSET          0x10        /* IRQ(HW1) Trigger Level Register offset */
#define IRQSR_OFFSET           0x14        /* IRQ(HW1) Status Register offset */
#define FIQSRCR_OFFSET         0x20        /* FIQ(HW0) Source Register offset */
#define FIQER_OFFSET           0x24        /* FIQ(HW0) Enable Register offset */
#define FIQICR_OFFSET          0x28        /* FIQ(HW0) Interrupt Clear Register offset */
#define FIQTMR_OFFSET          0x2C        /* FIQ(HW0) Trigger Mode Register offset */
#define FIQTLR_OFFSET          0x30        /* FIQ(HW0) Trigger Level Register offset */
#define FIQSR_OFFSET           0x34        /* FIQ(HW0) Status Register offset */
#define INT_ER_INIT            0x00000000  /* values used to disable all interrupts */
#define INT_CLEAR_VALUE        0xFFFFFFFF  /* values used to clear all pending interrupts */
#if 0
/* Constants utilized by interrupt handler for nesting interrupts */

#define FIRST_STACK_OFFSET     40          /* First stack offset FIQ/IRQ interrupt unnset */
#define IRQER_STACK_OFFSET     40          /* INT MASK register */
#define FIQER_STACK_OFFSET     44          /* Interrupt ER OFFSET register value */
#define MASK1_STACK_OFFSET     40          /* INT MASK register */
#define IEROFF_STACK_OFFSET    44          /* Interrupt ER OFFSET register value */
#define NUM_MASK_REGS          2           /* Number of mask register (1 mask register */
                                           /* and base address of interrupt */
                                           /* control register for core module) */
#define MASK_REG_SPACE         (NUM_MASK_REGS * 4)
#endif

/******************************************************************
        CGU register mapping(0x00F19000)
 *****************************************************************/
/******************************************************************
        Bit definition of CGU Bus clock divider Register (0x0)
 *****************************************************************/
#define BCLK_DIV_CPU     (0xF)
#define BCLK_DIV_GPIO    (0xF0)


/******************************************************************
        Bit definition of CGU Timer clock divider Register (0x4)
 *****************************************************************/
#define TCLK_TIMER1_CPUPLL_DIV             (0xF)
#define TCLK_TIMER2_CPUPLL_DIV             (0xF0)
#define TCLK_TIMER3_CPUPLL_DIV             (0xF00)


/******************************************************************
        Bit definition of CGU Peripheral clock divider Register (0x8)
 *****************************************************************/
#define PCLK_SSP0_CPUPLL_DIV             (0x0000000F)
#define PCLK_SSP1_CPUPLL_DIV             (0x000000F0)
#define PCLK_UART0_CPUPLL_DIV            (0x00000F00)
#define PCLK_UART1_CPUPLL_DIV            (0x0000F000)
#define PCLK_PWM0_CPUPLL_DIV             (0x000F0000)
#define PCLK_PWM1_CPUPLL_DIV             (0x00F00000)
#define PCLK_WDT_RTC_DIV                 (0x0F000000)
#define PCLK_EXT_XO_DIV                  (0xF0000000)

/******************************************************************
        Bit definition of CGU CPUPLLCFG Register(0x10)
 *****************************************************************/
#define CPUPLL_CFG_INDIV2  (0x1)
#define CPUPLL_CFG_CALPLL  (0x2)
#define CPUPLL_CFG_FBDIV (0x03FC)   /*bit2-bit9*/
#define CPUPLL_CFG_PREDIV (0x01C00)  /*bit10-bit12*/
#define CPUPLL_CFG_ODIV (0xE000)  /*bit13-bit15*/


/******************************************************************
        Bit definition of CGU Digital IP clock source selection Register(0x14)
 *****************************************************************/
#define DIP_CLK_SEL_RTC_OSC             (0x0)
#define DIP_CLK_SEL_RTC_XO              (0x1)

#define DIP_CLK_SEL_APB_XO              (0x0 << 2)
#define DIP_CLK_SEL_APB_CPUPLL          (0x1 << 2)
#define DIP_CLK_SEL_APB_HFRC            (0x2 << 2)
#define DIP_CLK_SEL_APB_32K             (0x3 << 2)
#define DIP_CLK_SEL_APB_MASK            (0x3 << 2)

#define DIP_CLK_SEL_SPI0_XO             (0x0 << 6)
#define DIP_CLK_SEL_SPI0_32K            (0x1 << 6)
#define DIP_CLK_SEL_SPI0_CPUPLL         (0x2 << 6)
#define DIP_CLK_SEL_SPI0_MASK           (0x3 << 6)

#define DIP_CLK_SEL_SPI1_XO             (0x0 << 8)
#define DIP_CLK_SEL_SPI1_32K            (0x1 << 8)
#define DIP_CLK_SEL_SPI1_CPUPLL         (0x2 << 8)
#define DIP_CLK_SEL_SPI1_MASK           (0x3 << 8)

#define DIP_CLK_SEL_UART0_XO            (0x0 << 10)
#define DIP_CLK_SEL_UART0_32K           (0x1 << 10)
#define DIP_CLK_SEL_UART0_CPUPLL        (0x2 << 10)
#define DIP_CLK_SEL_UART0_MASK          (0x3 << 10)

#define DIP_CLK_SEL_UART1_XO            (0x0 << 12)
#define DIP_CLK_SEL_UART1_32K           (0x1 << 12)
#define DIP_CLK_SEL_UART1_CPUPLL        (0x2 << 12)
#define DIP_CLK_SEL_UART1_MASK          (0x3 << 12)

#define DIP_CLK_SEL_PWM0_XO             (0x0 << 14)
#define DIP_CLK_SEL_PWM0_32K            (0x1 << 14)
#define DIP_CLK_SEL_PWM0_CPUPLL         (0x2 << 14)
#define DIP_CLK_SEL_PWM0_MASK           (0x3 << 14)

#define DIP_CLK_SEL_PWM1_XO             (0x0 << 16)
#define DIP_CLK_SEL_PWM1_32K            (0x1 << 16)
#define DIP_CLK_SEL_PWM1_CPUPLL         (0x2 << 16)
#define DIP_CLK_SEL_PWM1_MASK           (0x3 << 16)

#define DIP_CLK_SEL_TIMER1_XO           (0x0 << 18)
#define DIP_CLK_SEL_TIMER1_32K          (0x1 << 18)
#define DIP_CLK_SEL_TIMER1_CPUPLL       (0x2 << 18)
#define DIP_CLK_SEL_TIMER1_MASK         (0x3 << 18)

#define DIP_CLK_SEL_TIMER2_XO           (0x0 << 20)
#define DIP_CLK_SEL_TIMER2_32K          (0x1 << 20)
#define DIP_CLK_SEL_TIMER2_CPUPLL       (0x2 << 20)
#define DIP_CLK_SEL_TIMER2_MASK         (0x3 << 20)

#define DIP_CLK_SEL_TIMER3_XO           (0x0 << 22)
#define DIP_CLK_SEL_TIMER3_32K          (0x1 << 22)
#define DIP_CLK_SEL_TIMER3_CPUPLL       (0x2 << 22)
#define DIP_CLK_SEL_TIMER3_MASK         (0x3 << 22)

/******************************************************************
        Bit definition of  CGU Internal IP clock switch  Register(0x18)
 *****************************************************************/
#define IIP_EN_CPU_CLK          (0x1 << 0)
#define IIP_EN_TINY_CLK         (0x1 << 1)
#define IIP_EN_DLM_CLK          (0x1 << 2)
#define IIP_EN_FC_CLK           (0x1 << 3)
#define IIP_EN_CPUPLL_CLK       (0x1 << 4)
#define IIP_EN_BBPLL_CLK        (0x1 << 5)
#define IIP_EN_MAC_CLK          (0x1 << 8)
#define IIP_EN_BBP_CLK          (0x1 << 9)
#define IIP_EN_ANC_CLK          (0x1 << 10)
#define IIP_EN_CCM_CLK          (0x1 << 11)
#define IIP_EN_DMA_APBCLK       (0x1 << 12)
#define IIP_EN_DMA_CLK          (0x1 << 13)
#define IIP_EN_IMC_CLK          (0x1 << 14)
#define IIP_EN_SRAM8KB_CLK      (0x1 << 15)
#define IIP_EN_TIMER_APBCLK     (0x1 << 16)
#define IIP_EN_TIMER1_CLK       (0x1 << 17)
#define IIP_EN_TIMER2_CLK       (0x1 << 18)
#define IIP_EN_TIMER3_CLK       (0x1 << 19)
#define IIP_EN_RTC_EXTCLK       (0x1 << 24)


/******************************************************************
        Bit definition of  CGU Peripheral IP clock switch  Register(0x1C)
 *****************************************************************/
#define PIP_EN_SSP0_APBCLK      (0x1 << 0)
#define PIP_EN_SSP0_CLK         (0x1 << 1)
#define PIP_EN_SSP1_APBCLK      (0x1 << 2)
#define PIP_EN_SSP1_CLK         (0x1 << 3)
#define PIP_EN_UART0_APBCLK     (0x1 << 4)
#define PIP_EN_UART0_CLK        (0x1 << 5)
#define PIP_EN_UART1_APBCLK     (0x1 << 6)
#define PIP_EN_UART1_CLK        (0x1 << 7)
#define PIP_EN_WDT_APBCLK       (0x1 << 8)
#define PIP_EN_WDT_CLK          (0x1 << 9)
#define PIP_EN_PWM0_APBCLK      (0x1 << 10)
#define PIP_EN_PWM0_CLK         (0x1 << 11)
#define PIP_EN_PWM1_APBCLK      (0x1 << 12)
#define PIP_EN_PWM1_CLK         (0x1 << 13)
#define PIP_EN_I2C_CLK          (0x1 << 14)
#define PIP_EN_GPIO_CLK         (0x1 << 15)
#define PIP_EN_EBI_CLK          (0x1 << 16)


/********************* Bit definition of RCU SW Reset register **********************/
#define RCU_SW_RST_SYSTEM      (0x1 << 0)
#define RCU_SW_RST_CPU         (0x1 << 1)
#define RCU_SW_RST_TINY        (0x1 << 2)
#define RCU_SW_RST_FMC         (0x1 << 3)
#define RCU_SW_RST_MAC         (0x1 << 4)
#define RCU_SW_RST_BBP         (0x1 << 5)
#define RCU_SW_RST_ANALOG      (0x1 << 6)
#define RCU_SW_RST_CCM         (0x1 << 7)
#define RCU_SW_RST_SPI0        (0x1 << 8)
#define RCU_SW_RST_SPI1        (0x1 << 9)
#define RCU_SW_RST_UART0       (0x1 << 10)
#define RCU_SW_RST_UART1       (0x1 << 11)
#define RCU_SW_RST_DMA         (0x1 << 12)
#define RCU_SW_RST_ACS         (0x1 << 13)
#define RCU_SW_RST_EBI         (0x1 << 14)
#define RCU_SW_RST_SRAM8KB     (0x1 << 15)
#define RCU_SW_RST_TIMER       (0x1 << 16)
#define RCU_SW_RST_WDT         (0x1 << 17)
#define RCU_SW_RST_RTC         (0x1 << 18)
#define RCU_SW_RST_I2C         (0x1 << 20)
#define RCU_SW_RST_PWM0        (0x1 << 21)
#define RCU_SW_RST_PWM1        (0x1 << 22)
#define RCU_SW_RST_GPIO        (0x1 << 23)




/******************************************************************************/
/*                Multi-Function Pin                                          */
/******************************************************************************/

#define MFP_I2C_ENABLE()   (TOP->PADMUX1 = (TOP->PADMUX1 & ~(PAD_I2C_CLK_MUX_MASK | PAD_I2C_SDA_MUX_I2C_SDA)) |(PAD_I2C_CLK_MUX_I2C_CLK  | PAD_I2C_SDA_MUX_I2C_SDA))
#define MFP_UART0_ENABLE() (TOP->PADMUX1 = TOP->PADMUX1 & ~(PAD_UART0_TX_MUX_UART0_TX | PAD_UART0_RX_MUX_UART0_RX) |(PAD_I2C_CLK_MUX_I2C_CLK  | PAD_I2C_SDA_MUX_I2C_SDA))
#define MFP_UART1_ENABLE() (TOP->PADMUX1 = TOP->PADMUX1 & ~(PAD_I2C_CLK_MUX_MASK | PAD_I2C_SDA_MUX_I2C_SDA) |(PAD_I2C_CLK_MUX_I2C_CLK  | PAD_I2C_SDA_MUX_I2C_SDA))

#define MFP_SPI0_ENABLE()   {\
TOP->PADMUX1 = (TOP->PADMUX1 & ~(PAD_SPI0_MOSI_MUX_MASK | PAD_SPI0_MISO_MUX_MASK \
| PAD_SPI0_CLK_MUX_MASK |PAD_SPI0_CSN_MUX_MASK)) \
| PAD_SPI0_MOSI_MUX_SPI0_MOSI |PAD_SPI0_MISO_MUX_SPI0_MISO |PAD_SPI0_CLK_MUX_SPIO_CLK |   PAD_SPI0_CSN_MUX_SPI0_CSN; \
}


#define MFP_SPI1_ENABLE()   {\
TOP->PADMUX0 = (TOP->PADMUX0& ~(PAD_GPIO5_MUX_MASK | PAD_GPIO9_MUX_MASK \
| PAD_GPIO10_MUX_MASK |PAD_GPIO11_MUX_MASK)) \
| PAD_GPIO5_MUX_SPI1_MISO |PAD_GPIO9_MUX_SPI1_MOSI |PAD_GPIO10_MUX_SPI1_CS |   PAD_GPIO11_MUX_SPI1_CLK; \
}

/*PWM*/
#define MFP_PWM0_ENABLE()   {TOP->PADMUX0 = (TOP->PADMUX0 & ~PAD_GPIO1_MUX_MASK) | PAD_GPIO1_MUX_PWM0;}
#define MFP_PWM1_ENABLE()   {TOP->PADMUX0 = (TOP->PADMUX0 & ~PAD_GPIO2_MUX_MASK) | PAD_GPIO2_MUX_PWM1;}
#define MFP_PWM2_ENABLE()   {TOP->PADMUX1 = (TOP->PADMUX1 & ~PAD_I2C_CLK_MUX_MASK) | PAD_I2C_CLK_MUX_PWM2;}
#define MFP_PWM3_ENABLE()   {TOP->PADMUX1 = (TOP->PADMUX1 & ~PAD_I2C_SDA_MUX_I2C_SDA) | PAD_I2C_SDA_MUX_PWM3;}


/*AGPIO*/
#define MFP_AGPIO1_2_ENABLE()   {TOP->AGPIOCTRL0 |= AGPIO_AEN_ADGPIO1_2;}
#define MFP_AGPIO3_4_ENABLE()   {TOP->AGPIOCTRL0 |= AGPIO_AEN_ADGPIO3_4;}
#define MFP_AGPIO5_6_ENABLE()   {TOP->AGPIOCTRL0 |= AGPIO_AEN_ADGPIO5_6;}
#define MFP_AGPIO7_8_ENABLE()   {TOP->AGPIOCTRL0 |= AGPIO_AEN_ADGPIO7_8;}

/*ACMP*/
#define MFP_ACMP_CH7_ENABLE()  {TOP->AGPIOCTRL0 = (TOP->AGPIOCTRL0 & ~AGPIO_FUNC_ADGPIO1_MUX_MASK) | AGPIO_FUNC_ADGPIO1_MUX_ACMPCH7;}  
#define MFP_ACMP_CH1_ENABLE()  {TOP->AGPIOCTRL0 = (TOP->AGPIOCTRL0 & ~AGPIO_FUNC_ADGPIO2_MUX_MASK) | AGPIO_FUNC_ADGPIO2_MUX_ACMPCH1;}  
#define MFP_ACMP_CH2_ENABLE()  {TOP->AGPIOCTRL0 = (TOP->AGPIOCTRL0 & ~AGPIO_FUNC_ADGPIO3_MUX_MASK) | AGPIO_FUNC_ADGPIO3_MUX_ACMPCH2;} 
#define MFP_ACMP_CH3_ENABLE()  {TOP->AGPIOCTRL0 = (TOP->AGPIOCTRL0 & ~AGPIO_FUNC_ADGPIO4_MUX_MASK) | AGPIO_FUNC_ADGPIO4_MUX_ACMPCH3;} 
#define MFP_ACMP_CH4_ENABLE()  {TOP->AGPIOCTRL0 = (TOP->AGPIOCTRL0 & ~AGPIO_FUNC_ADGPIO5_MUX_MASK) | AGPIO_FUNC_ADGPIO5_MUX_ACMPCH4;} 
#define MFP_ACMP_CH5_ENABLE()  {TOP->AGPIOCTRL0 = (TOP->AGPIOCTRL0 & ~AGPIO_FUNC_ADGPIO6_MUX_MASK) | AGPIO_FUNC_ADGPIO6_MUX_ACMPCH5;} 
#define MFP_ACMP_CH6_ENABLE()  {TOP->AGPIOCTRL0 = (TOP->AGPIOCTRL0 & ~AGPIO_FUNC_ADGPIO7_MUX_MASK) | AGPIO_FUNC_ADGPIO7_MUX_ACMPCH6;} 

/******************************************************************
        MAC Control Register (MAC) 0x00E00000
 *****************************************************************/

typedef struct
{
    __RW u32 FIFO_CTRL;                 //0x00
         u32 RESERVED[4];                   /* Offset 0x04 - 0x10*/
    __RW u32 RX_CTRL;                   //0x14
    __RW u32 PAN_ID;                    //0x18
    __RW u32 SHORT_ADDR;                //0x1C
    __RW u32 EXTEND_ADDR_0;             //0x20
    __RW u32 EXTEND_ADDR_1;             //0x24
    __RW u32 MAC_CTRL;                  //0x28
    __RW u32 PRE_SLOT_OFFSET;           //0x2C
    __RW u32 UNIT_SLOT;                 //0x30
    __RW u32 UNIT_BEACON;               //0x34;
    __RW u32 SLOT_CTRL;                 //0x38
    __RW u32 PRE_RXBEACON_OFFSET;       //0x3C
    __RW u32 RXBEACON_OFFSET;           //0x40
    __RW u32 PRE_TXBEACON_OFFSET;       //0x44
    __RW u32 UNIT_GP1;                  //0x48
    __RW u32 UNIT_GP2;                  //0x4C
    __RW u32 UNIT_SLICE;                //0x50
    __RW u32 PRESLICE_OFFSET;           //0x54
    __RW u32 SLICE_CTRL;                //0x58
    __RW u32 SLOT_TR_MODE_0;            //0x5C
    __RW u32 SLOT_TR_MODE_1;            //0x60
    __RW u32 SLOT_TR_MODE_2;            //0x64
    __RW u32 SLOT_TR_MODE_3;            //0x68
    __RW u32 SLOT_TR_MODE_4;            //0x6C
    __RW u32 SLOT_TR_MODE_5;            //0x70
    __RW u32 SLOT_TR_MODE_6;            //0x74
    __RW u32 SLOT_TR_MODE_7;            //0x78
    __RW u32 BKN_SRC_ADDR_0;            //0x7C
    __RW u32 BKN_SRC_ADDR_1;            //0x80
    __RW u32 TIMER_CTRL;                //0x84
    __R  u32 SLOT_SYMBOL_CNT;           //0x88
    __R  u32 BI_SYMBOL_CNT;             //0x8C
    __R  u32 BACKOFF_PERIOD_CNT;        //0x90
    __RW u32 CSMA_CA_0;                 //0x94
    __RW u32 TX_CTRL;                   //0x98
    __RW u32 DURATION_CTRL;             //0x9C
    __RW u32 CHANNEL_CTRL;              //0xA0
    __R  u32 ERR_NUM;                   //0xA4
    __RW u32 FCS_CLEAR;                 //0xA8
    __RW u32 RELOAD_SLOT_SYMBOL_CNT;    //0xAC
    __RW u32 RELOAD_BI_SYMBOL_CNT;      //0xB0
    __RW u32 RELOAD_CNT;                //0xB4
    __RW u32 ADDR_MASK_0;               //0xB8
    __RW u32 ADDR_MASK_1;               //0xBC
    __RW u32 ADDR_MASK_2;               //0xC0
    __RW u32 ADDR_MASK_3;               //0xC4
    __RW u32 INTR_MASK;                 //0xC8
    __RW u32 LBT_CTRL;                  //0xCC
         u32 Reservd2[19];                  //0xD0 - 0x118
    __RW  u32 INTR_STATE_RPT;            //0x11C
    __RW u32 TX_FIFO_WDAT; 	            //0x120
    __R  u32 TX_FIFO_RDAT; 	            //0x124
    __RW u32 RX_FIFO_WDAT;              //0x128
    __R  u32 RX_FIFO_RDAT;              //0x12C

}MAC_TypeDef;

/******************************************************************
        TOP Control Register (TOP)
 *****************************************************************/
typedef struct
{
    __RW u32 SYSBOOT;         /* Offset 0x00 TOP Boot Register */
    __RW u32 TESTBUSCTRL;     /* Offset 0x04 TOP Test Bus Control Register */
    __R  u32 FPGAVER;         /* Offset 0x08 TOP FPGA Version Register*/
    __R  u32 ASIICVER;        /* Offset 0x0C TOP ASIIC Verson Register*/
    __RW u32 TESTBUSMASK;     /* Offset 0x10 TOP Test Bus Mask Register*/
    __RW u32 MISC;       /* Offset 0x14 MISC Register */
         u32 RESERVED[2];     /* Offset 0x18 - 0x1C*/
    __RW u32 PADMUX0;         /* Offset 0x20 TOP PAD MUX0 Register*/
    __RW u32 PADMUX1;         /* Offset 0x24 TOP PAD MUX1 Register*/
         u32 RESERVED2[6];    /* Offset 0x28 - 0x3C*/
    __RW u32 PADDS0;          /* Offset 0x40 PAD DS#0 Register */
    __RW u32 PADDS1;          /* Offset 0x44 PAD DS#1 Register */
         u32 RESERVED3[2];    /* Offset 0x48 - 0x4C*/
    __RW u32 PADPE0;          /* Offset 0x50 PAD PE#0 Register */
    __RW u32 PADPE1;          /* Offset 0x54 PAD PE#1 Register */
    __RW u32 BONDOPTPE;       /* Offset 0x58 BONDOPTPE Register */
         u32 RESERVED4[1];    /* Offset 0x5C*/
    __RW u32 AGPIOCTRL0;      /* Offset 0x60 AGPIOCTRL0 Register */
    __RW u32 AGPIOCTRL1;      /* Offset 0x64 AGPIOCTRL1 Register */    
}TOP_TypeDef;

/******************************************************************
        Timer Control Register (TIMER)
 *****************************************************************/
typedef struct
{
    __RW u32 TM1COUNTER;     /* Offset 0x00 timer1 counter register */
    __RW u32 TM1LOAD;        /* Offset 0x04 timer1 load register  */
    __RW u32 TM1MATCH1;      /* Offset 0x08 timer1 match counter register  */
    __RW u32 TM1MATCH2;      /* Offset 0x0C timer1 match counter register  */
    __RW u32 TM2COUNTER;     /* Offset 0x10 timer2 counter register  */
    __RW u32 TM2LOAD;        /* Offset 0x14 timer2 load register  */
    __RW u32 TM2MATCH1;      /* Offset 0x18 timer2 match counter register  */
    __RW u32 TM2MATCH2;      /* Offset 0x1C timer2 match counter register  */
    __RW u32 TM3COUNTER;     /* Offset 0x20 timer3 counter register  */
    __RW u32 TM3LOAD;        /* Offset 0x24 timer3 load register  */
    __RW u32 TM3MATCH1;      /* Offset 0x28 timer3 match counter register  */
    __RW u32 TM3MATCH2;      /* Offset 0x2C timer3 match counter register  */
    __RW u32 TMCR;           /* Offset 0x30 timer control register  */
    __RW u32 INTRSTATE;      /* Offset 0x34 timer interrupt status register  */
    __RW u32 INTRMASK;       /* Offset 0x38 timer interrupt mask  register  */
    __R  u32 TMREVISION;     /* Offset 0x3C timer revision register  */
    __RW u32 TM1PRSCALER;    /* Offset 0x40 timer1 prescaler register  */
    __RW u32 TM2PRSCALER;    /* Offset 0x44 timer2 prescaler register  */
    __RW u32 TM3PRSCALER;    /* Offset 0x48 timer3 prescaler register  */
}TIMER_TypeDef;

/******************************************************************
        WDT Control Register (WDT)
 *****************************************************************/
typedef struct
{
    __R  u32 CNT;         /* Offset 0x00 WDT Counter Register  */
    __RW u32 LOAD;        /* Offset 0x04 WDT Counter Auto reload Register  */
    __W  u32 RESTART;     /* Offset 0x08 WDT Counter Restart Register  */
    __RW u32 CR;          /* Offset 0x0C WDT Control Register */
    __R  u32 STATUS;      /* Offset 0x10 WDT Status Register  */
    __W  u32 CLEAR;       /* Offset 0x14 WDT Clear status Register */
    __RW u32 INTRLEN;     /* Offset 0x18 WDT Interrupt length Register  */
    __R  u32 REVISION;    /* Offset 0x1C WDT Revision Register  */
    __RW u32 RSTDLY;      /* Offset 0x20 WDT Reset delay Register  */
}WDT_TypeDef;


/******************************************************************
        RTC Control Register (RTC)
 *****************************************************************/
typedef struct
{
    __R  u32 SEC;         /* Offset 0x00 RTC Second Register for Read */
    __R  u32 MIN;         /* Offset 0x04 RTC Minute Register  for Read  */
    __R  u32 HOUR;        /* Offset 0x08 RTC Hour Register  for Read  */
    __R  u32 DAYS;        /* Offset 0x0C RTC Day Register  for Read  */
    __RW u32 ALMSEC;      /* Offset 0x10 RTC Second Alarm Register for Write  */
    __RW u32 ALMMIN;      /* Offset 0x14 RTC Minute Alarm Register  for Write  */
    __RW u32 ALMHOUR;     /* Offset 0x18 RTC Hour Alarm Register  for Write  */
    __RW u32 RECORD;      /* Offset 0x1C RTC Day Alarm Register  for Write  */
    __RW u32 CR;          /* Offset 0x20 RTC Control Register  for Write  */
    __RW u32 WSEC;        /* Offset 0x24 RTC Second Counter Write Register  */
    __RW u32 WMIN;        /* Offset 0x28 RTC Minute Counter Write Register  */
    __RW u32 WHOUR;       /* Offset 0x2C RTC Hour Counter Write Register  */
    __RW u32 WDAYS;       /* Offset 0x30 RTC Day Counter Write Register */
    __RW u32 INTRSTATE;   /* Offset 0x34 RTC Interrupt Register  */
    __RW u32 DIVIDE;      /* Offset 0x38 RTC Frequency Divider WriteRegister  */
    __R  u32 REVISION;    /* Offset 0x3C RTC Revision Register */
}RTC_TypeDef;


/******************************************************************
        GPIO Control Register (GPIO)
 *****************************************************************/
typedef struct
{
    __RW u32 DOUT;       /* Offset 0x00  GPIO data output register*/
    __R  u32 DIN;        /* Offset 0x04  GPIO data input register */
    __RW u32 DIR;        /* Offset 0x08  GPIO direction register   */
    __RW u32 BYPASS;     /* Offset 0x0C   */
    __W  u32 DSET;       /* Offset 0x10   */
    __W  u32 DCLEAR;     /* Offset 0x14   */
    __RW u32 PUE;        /* Offset 0x18  GPIO pull-up register  */
    __RW u32 PUT;        /* Offset 0x1C  GPIO pull-high/pull-low register  */
    __RW u32 IE;         /* Offset 0x20  GPIO interrupt enable register  */
    __R  u32 IRS;        /* Offset 0x24  GPIO interrupt raw status register  */
    __R  u32 IMS;        /* Offset 0x28  GPIO interrupt masked status register  */
    __RW u32 IM;         /* Offset 0x2C  GPIO interrupt mask register  */
    __W  u32 IC;         /* Offset 0x30  GPIO interrupt clear  register*/
    __RW u32 IT;         /* Offset 0x34  GPIO interrupt trigger method register  */
    __RW u32 IB;         /* Offset 0x38  GPIO edge-trigger interrupt by single or both edges  */
    __RW u32 IR;         /* Offset 0x3C  GPIO interrupt triggered at the rising or falling edger  */
    __RW u32 BE;         /* Offset 0x40  GPIO BounceEnable */
    __RW u32 BPS;        /* Offset 0x44  GPIO BouncePreScale  */
         u32 RESERVED[13];      /* Offset 0x48 -78  */
    __R  u32 REVNUM;       /* Offset 0x7C  GPIO revision number*/
}GPIO_TypeDef;

/******************************************************************
        Interrrupt Controller Control Register (INTC)
 *****************************************************************/
typedef struct
{
    __R  u32 HW1SOURCE;         /* Offset 0x00 IRQ(HW1) Source Register offset */
    __RW u32 HW1ENABLE;         /* Offset 0x04 IRQ(HW1) Enable Register offset */
    __W  u32 HW1INTRCLEAR;      /* Offset 0x08 IRQ(HW1) Interrupt Clear Register offset  */
    __RW u32 HW1TRIGGERMODE;    /* Offset 0x0C IRQ(HW1) Trigger Mode Register offset  */
    __RW u32 HW1TRIGGERLEVEL;   /* Offset 0x10 IRQ(HW1) Trigger Level Register offset  */
    __R  u32 HW1STATE;          /* Offset 0x14 IRQ(HW1) Status Register offset */
         u32 RESERVED[2];       /* Offset 0x18 - 0x1C*/
    __R  u32 HW0SOURCE;         /* Offset 0x20 FIQ(HW0) Source Register offset  */
    __RW u32 HW0ENABLE;         /* Offset 0x24 FIQ(HW0) Enable Register offset  */
    __W  u32 HW0INTRCLEAR;      /* Offset 0x28 FIQ(HW0) Interrupt Clear Register offset */
    __RW u32 HW0TRIGGERMODE;    /* Offset 0x2C FIQ(HW0) Trigger Mode Register offset  */
    __RW u32 HW0TRIGGERLEVEL;   /* Offset 0x30 FIQ(HW0) Trigger Level Register offset */
    __R  u32 HW0STATE;          /* Offset 0x34 FIQ(HW0) Status Register offset  */

}INTC_TypeDef;


/******************************************************************
        DMA Control Register (DMA)
 *****************************************************************/
typedef struct
{
    __RW u32 SSP0RX;            /* Offset 0x00  DMA SSP0 RX Control Register */
    __RW u32 SSP0RXADDR;        /* Offset 0x04  DMA SSP0 RX Addr Register */
    __RW u32 SSP1RX;            /* Offset 0x08  DMA SSP1 RX Control Register*/
    __RW u32 SSP1RXADDR;        /* Offset 0x0C  DMA SSP1 RX Addr Register*/
    __RW u32 UART0RX;           /* Offset 0x10  DMA UART0 RX Control Register*/
    __RW u32 UART0RXADDR;       /* Offset 0x14  DMA UART0 RX Addr Register*/
    __RW u32 UART1RX;           /* Offset 0x18  DMA UART1 RX Control Register*/
    __RW u32 UART1RXADDR;       /* Offset 0x1C  DMA UART1 RX Addr Register*/
    __RW u32 MACRX;             /* Offset 0x20  DMA MAC RX Control Register*/
    __RW u32 SSP0TX;            /* Offset 0x24  DMA SSP0 TX Control Register*/
    __RW u32 SSP0TXADDR;        /* Offset 0x28  DMA SSP0 TX Addr Register*/
    __RW u32 SSP1TX;            /* Offset 0x2C  DMA SSP1 TX Control Register*/
    __RW u32 SSP1TXADDR;        /* Offset 0x30  DMA SSP1 TX Addr Register*/
    __RW u32 UART0TX;           /* Offset 0x34  DMA UART0 TX Control Register*/
    __RW u32 UART0TXADDR;       /* Offset 0x38  DMA UART0 TX Addr Register*/
    __RW u32 UART1TX;           /* Offset 0x3C  DMA UART1 TX Control Register */
    __RW u32 UART1TXADDR;       /* Offset 0x40  DMA UART1 TX Addr Register */
    __RW u32 MACTX;             /* Offset 0x44  DMA MAC TX Control Register */
    __RW u32 MACTXADDR;         /* Offset 0x48  DMA MAC TX Addr Register */
    __RW u32 INTR;              /* Offset 0x4C  DMA Interrupt Control Register */
    __RW u32 MACTARGET0;        /* Offset 0x50  DMA MAC RX Target 0 Register */
    __RW u32 MACTARGET1;        /* Offset 0x54  DMA MAC RX Target 1 Register */
    __RW u32 MACTARGET2;        /* Offset 0x58  DMA MAC RX Target 2 Register */
    __RW u32 MACTARGET3;        /* Offset 0x5C  DMA MAC RX Target 3 Register */
    __RW u32 MACTARGET4;        /* Offset 0x60  DMA MAC RX Target 4 Register */
    __RW u32 EXTENSION;         /* Offset 0x64  DMA extension Register */
    __RW u32 RFCRX;             /* Offset 0x68  DMA RFC RX  Register */
    __RW u32 RFCRXADDR;         /* Offset 0x6C  DMA RFX RX Addr Register */
    __RW u32 SSPCSCTRL;         /* Offset 0x70  DMA SSP chipselect  control  Register */
    __RW u32 UART0RXINFO;       /* Offset 0x74  DMA UART0 RX information Register */
    __RW u32 UART0RXMEMLEN;     /* Offset 0x78  DMA UART0 RX memory length Register */
    __RW u32 UART1RXINFO;       /* Offset 0x7C  DMA UART1 RX information Register */
    __RW u32 UART1RXMEMLEN;     /* Offset 0x80  DMA UART1 RX memory length Register */
}DMA_TypeDef;

/******************************************************************
        I2C Control Register (I2C)
 *****************************************************************/
typedef struct
{
    __RW u32 CR;                /* Offset 0x00  I2C Control Register */
    __R  u32 SR;                /* Offset 0x04  I2C Status Register */
    __RW u32 CDR;               /* Offset 0x08 I2C Clock Division Register*/
    __RW u32 DR;                /* Offset 0x0C I2C Data Register*/
    __RW u32 SAR;               /* Offset 0x10  I2C Slave Address Register*/
    __RW u32 TGSR;              /* Offset 0x14 I2C Setup/Hold Time and Glitch Suppression Setting Register */
    __RW u32 BMR;               /* Offset 0x18 I2C Bus Monitor Register */
         u32 RESERVED[5];       /* Offset 0x1C - 0x2C*/
    __RW u32 I2CREVISION;       /* Offset 0x30  I2C Revision Register*/

}I2C_TypeDef;

/******************************************************************
        SPI  Control Register (SPI)
 *****************************************************************/
typedef struct
{
    __RW u32 CR0;               /* Offset 0x00  SSP Control Register0 */
    __RW u32 CR1;               /* Offset 0x04  SSP Control Register1 */
    __RW u32 CR2;               /* Offset 0x08  SSP Control Register2*/
    __R  u32 SR;                /* Offset 0x0C  SSP Status Register*/
    __RW u32 INTRCR;            /* Offset 0x10  SSP Interrupt Control Register*/
    __R  u32 INTRSR;            /* Offset 0x14  SSP Interrupt Status Register */
    __RW u32 DR;                /* Offset 0x18  SSP Data Register */

}SPI_TypeDef;


/******************************************************************
       Flash Control Register (FC)
 *****************************************************************/
typedef struct
{
	__RW u32 CONFIG;            /* Offset 0x00 Config Register */
	__R  u32 STATUS;            /* Offset 0x04 Config Register */
	__RW u32 PROGRAM_ADDR;      /* Offset 0x08 Config Register */
	__RW u32 PROGRAM_DATA;      /* Offset 0x0C Config Register */
	__RW u32 ERASE_PAGE;        /* Offset 0x10 Config Register */
	__RW u32 MASS_ERASE;	    /* Offset 0x14 Config Register */
	__RW u32 READ_TIMING;       /* Offset 0x18 Config Register */
	__RW u32 PROGRAM_TIMING;    /* Offset 0x1C Config Register */
	__RW u32 PROGRAM_TIMING2;	/* Offset 0x20 Config Register */
	__RW u32 ERASE_TIMING;      /* Offset 0x24 Config Register */
	__RW u32 ERASE_TIMING2;     /* Offset 0x28 Config Register */
	__RW u32 TNVH;	            /* Offset 0x2C Config Register */
	__RW u32 TNVH1;	            /* Offset 0x30 Config Register */
	__RW u32 FPGA_SPEC;         /* Offset 0x34 Config Register */
	__RW u32 TESTBUS_CTRL;      /* Offset 0x38 Config Register */
}FC_TypeDef;


/******************************************************************
        AC Control Register (AC)
 *****************************************************************/
typedef struct
{
	__RW u32 DIN;
	__RW u32 INFO;
	__R  u32 DOUT;
	__R  u32 LOW;
	__R  u32 RANGE;
	__RW u32 VALUE;
}AC_TypeDef;

/******************************************************************
        PWM Control Register (PWM)
 *****************************************************************/
typedef struct
{
    __RW u32 PWM0CR;           /* Offset 0x00 PWM0 Control Register */
    __RW u32 PWM0DUTY;         /* Offset 0x04 PWM0 Duty cycle Register */
    __RW u32 PWM0PER;          /* Offset 0x08 PWM0 Period control Register */
    __RW u32 PWM0CR2;          /* Offset 0x0C PWM0 Control 2 Register */
    __RW u32 PWM1CR;           /* Offset 0x10 PWM1 Control Register */
    __RW u32 PWM1DUTY;         /* Offset 0x14 PWM1 Duty cycle Register  */
    __RW u32 PWM1PER;          /* Offset 0x18 PWM1 Period control Register */
    __RW u32 PWM1CR2;          /* Offset 0x1C PWM1 Control 2 Register */
}PWM_TypeDef;

/******************************************************************
        TINY Control Register (TINY)
 *****************************************************************/
typedef struct
{
    __RW  u32 CTRL;
    __RW  u32 SW_TRIG;
    union{
    	struct{
    		__RW u32 CH0_CTRL;
    		__RW u32 CH0_SRC;

    		__RW u32 CH1_CTRL;
    		__RW u32 CH1_SRC;

    		__RW u32 CH2_CTRL;
    		__RW u32 CH2_SRC;

    		__RW u32 CH3_CTRL;
    		__RW u32 CH3_SRC;
    	};
    	struct{
    		__RW u32 CTRL;
    		__RW u32 SRC;
    	}CH[4];
    };
    __R u32 unused[54];
    union{
    	__RW u32 IM[512];
    	struct{
    		__RW u32 RD_ADDR;
    		__RW u32 WR_ADDR;
    		__RW u32 AND;
    		__RW u32 XOR;
    	} INSN[128];
    };
}TINY_TypeDef;

/******************************************************************
        UART Control Register (UART)
 *****************************************************************/
typedef struct
{
    union{
    __R  u32 RBR;               /* Offset 0x00 UART Receiver Buffer Register for Read */
    __RW u32 THR;               /* Offset 0x00  Transmitter Holding Register for Write */
    __RW u32 DLL;               /* Offset 0x00Baud Rate Divisor Latch Least Significant Byte  when DLAB = 1 */
    };
    union{
    __RW u32 IER;               /* Offset 0x04  UART Interrupt Enable Register */
    __RW u32 DLM;               /* Offset 0x04 Baud Rate Divisor Latch Most Significant Byte when DLAB = 1 */
    };
    union{
    __RW u32 IIR;               /* Offset 0x08 UART Interrupt Identification Register  */
    __RW u32 FCR;               /* Offset 0x08 FIFO Control Register */
    __RW u32 PSR;               /* Offset 0x08  Prescaler Register (PSR, Offset: 0x08 when DLAB =1) */
    };
    __RW u32 LCR;               /* Offset 0x0C UART Line Control Register */
    __RW u32 MCR;               /* Offset 0x10 UART Modem Control Register */
    union{
    __RW u32 LSR;               /* Offset 0x14 UART Line Status Register for Read */
    __RW u32 TST;               /* Offset 0x14Testing Register for Write */
    };
    __R  u32 MSR;               /* Offset 0x18 UART Modem Status Register */
    __RW u32 SPR;               /* Offset 0x1C UART Scratch Pad Register */
    __RW u32 MDR;               /* Offset 0x20 UART Mode Definition Register */
    __RW u32 ADR;               /* Offset 0x24 UART Auxiliary Control Register */
    __RW u32 TXLENL;            /* Offset 0x28 UART Transmitter Frame Length Low Register */
    __RW u32 TXLENH;            /* Offset 0x2C UART Transmitter Frame Length High Register */
    __RW u32 MRXLENL;           /* Offset 0x30 UART Maximum Receiver Frame Length Low Register */
    __RW u32 MRXLENH;           /* Offset 0x34 UART Maximum Receiver Frame Length High Register */
    __RW u32 PLR;               /* Offset 0x38 UART FIR Preamble Length Register */
    union{
    __RW u32 FMIIR_PIO;         /* Offset 0x3C UART FIR Mode Interrupt Identification Register In PIO mode */
    __RW u32 FMIIR_DMA;         /* Offset 0x3C UART FIR Mode Interrupt Identification RegisterIn PIO mode*/
    };
    union{
    __RW u32 FMIIER_PIO;        /* Offset 0x40 UART FIR Mode Interrupt Enable Register In PIO mode */
    __RW u32 FMIIER_DMA;        /* Offset 0x40 UART FIR Mode Interrupt Enable RegisterIn PIO mode*/
    };
    __R  u32 STFF_STS;          /* Offset 0x44 UART Modem Status Register */
    __R  u32 STFF_RXLENL;       /* Offset 0x48 UART Modem Status Register */
    __R  u32 STFF_RXLENH;       /* Offset 0x4C UART Modem Status Register */
    __R  u32 FMLSR;             /* Offset 0x50 UART Modem Status Register */
    __RW  u32 FMLSIER;          /* Offset 0x54 UART FIR Mode Link Status Interrupt Enable Register*/
    __R  u32 RSR;               /* Offset 0x58 UART Resume Register*/
    __R  u32 RXFF_CNTR;         /* Offset 0x5C UART Rx FIFO Count Register*/
    __RW  u32 LSTFMLENL;        /* Offset 0x60 UART Last Frame Length Register Low */
    __RW  u32 LSTFMLENH;        /* Offset 0x64 UART Last Frame Length Register High */
    __RW  u32 FEATURE;          /* Offset 0x68 UART Feature Register */
    __R  u32 REVD1;             /* Offset 0x6C UART Revision Register Digit 1 */
    __R  u32 REVD2;             /* Offset 0x70 UART Revision Register Digit 2 */
    __R  u32 REVD3;             /* Offset 0x74 UART Revision Register Digit 3 */
    __RW  u32 DIV;              /* Offset 0x78 UART Divied 16 Register  */
}UART_TypeDef;

/******************************************************************
        PMU Control Register (PMU)
 *****************************************************************/
typedef struct
{
    __RW u32 SWCFG;             /* Offset 0x00  PMU SW config Register */
    __RW u32 TESTMODE;          /* Offset 0x04  PMU Test Mode Register */
    __RW u32 PWRMODE;           /* Offset 0x08  PMU Power Mode Register*/
    __RW u32 MISC;              /* Offset 0x0C  PMU MISC Register*/
    __RW u32 TMCR;              /* Offset 0x10  Timer Control Register*/
    __RW u32 TM1LOAD;           /* Offset 0x14  Timer1 Load Register*/
    __RW u32 TM2LOAD;           /* Offset 0x18  Timer2 Load Register*/
    __RW u32 TM3LOAD;           /* Offset 0x1C  Timer3 Load Register*/
    __R u32 TM1CNT;             /* Offset 0x20  Timer1 Counter Register*/
    __R u32 TM2CNT;             /* Offset 0x24  Timer2 Counter Register*/
    __R u32 TM3CNT;             /* Offset 0x28  Timer3 Counter Register*/
        u32 RESERVED[1];        /* Offset 0x2C*/
    __R u32 IRQSRC;             /* Offset 0x30  IRQ Source Register*/
    __RW u32 IRQEN;             /* Offset 0x34  IRQ Enable Register*/
    __R u32 IRQSTATE;           /* Offset 0x38  IRQ State Register*/
        u32 RESERVED2[1];       /* Offset 0x3C*/
    __R u32 TM1LOADCAL;         /* Offset 0x40  Timer1 Load Calibration Register*/
    __R u32 TM2LOADCAL;         /* Offset 0x44  Timer2 Load Calibration Register*/
    __R u32 TM3LOADCAL;         /* Offset 0x48  Timer3 Load Calibration Register*/
    __RW u32 ACMPCR;            /* Offset 0x50  ACMP Control Register*/
    __RW u32 ACMPSET;           /* Offset 0x54  ACMP Set Register*/
}PMU_TypeDef;

/******************************************************************
        CGU Control Register (CGU)
 *****************************************************************/
typedef struct
{
    __RW u32 BUSCLKDIV;         /* Offset 0x00  Bus clock divider Register */
    __RW u32 TMRCLKDIV;         /* Offset 0x04  Timer clock divider Register */
    __RW u32 PCLKDIV;           /* Offset 0x08  Peripheral clock divider Register */
    __RW u32 CPUPLLCFGLCY;      /* Offset 0x0C  CPUPLL configure latency Register*/
    __RW u32 CPUPLLCFG;         /* Offset 0x10  CPUPLL configure Register*/
    __RW u32 DIPCLKSEL;         /* Offset 0x14  Digital IP clock source Register*/
    __RW u32 IIPCLKSW;          /* Offset 0x18  Internal IP clock switch Register*/
    __RW u32 PIPCLKSW;          /* Offset 0x1C  Peripheral IP clock switch Register*/
    __RW u32 CGUCTRL;           /* Offset 0x20  CGU control Register*/
    __RW u32 CGUTESTBUS;        /* Offset 0x24  CGU test busRegister*/
}CGU_TypeDef;


/******************************************************************
        RCU Control Register (RCU)
 *****************************************************************/
typedef struct
{
    __RW u32 CSRSWRSTN;         /* Offset 0x00  RCU Register */
}RCU_TypeDef;




/******************************************************************
        EBI Control Register (EBI)
 *****************************************************************/
typedef struct
{
    __RW u32 EBICFG;         /* Offset 0x00  EBI configuation Register */
    __RW u32 TIMING;         /* Offset 0x04  Timing parameter  Register */
}EBI_TypeDef;


/******************************************************************
        Memory Map
 *****************************************************************/

#define NEWTON_MAX_BASE     (0x00FFFFFF)//(0x00F1AFFF)
#define NEWTON_MIN_BASE     (0x00000000)

#define MAC_BASE            (0x00E00000)
#define BBP_BASE            (0x00E40000)	

#define TOP_BASE            (0x00F02000)
#define TIMER0_BASE         (0x00F03000)
#define EBI_BASE            (0x00F04000)
#define WDT_BASE            (0x00F05000)
#define RTC_BASE            (0x00F06000)
#define GPIO_BASE           (0x00F07000)
#define INTC_BASE           (0x00F08000)
#define DMA_BASE            (0x00F09000)
#define I2C_BASE            (0x00F0A000)
#define SPI0_BASE           (0x00F0B000)
#define SPI1_BASE           (0x00F0C000)
//#define TCON_BASE   (0x00F0D000)
#define FLASH_CTRL_BASE     (0x00F0E000)
#define AC_BASE             (0x00F0F000)
#define PWM0_BASE           (0x00F10000)
#define PWM1_BASE           (0x00F11000)
#define TINY_BASE           (0x00F12000)
#define TINY_IM_BASE        (0x00F12100)
#define UART0_BASE          (0x00F16000)
#define UART1_BASE          (0x00F17000)
#define PMU_BASE            (0x00F18000)
#define CGU_BASE            (0x00F19000) /* Clock generate unit */
#define RCU_BASE            (0x00F1A000) /* Reset controller unit  */


#define MAC     ((MAC_TypeDef*)MAC_BASE)
#define TIMER   ((TIMER_TypeDef*)TIMER0_BASE)
#define WDT     ((WDT_TypeDef*)WDT_BASE)
#define RTC     ((RTC_TypeDef*)RTC_BASE)
#define GPIO    ((GPIO_TypeDef*)GPIO_BASE)
#define INTC    ((INTC_TypeDef*)INTC_BASE)
#define DMA     ((DMA_TypeDef*)DMA_BASE)
#define I2C     ((I2C_TypeDef*)I2C_BASE)
#define SPI0    ((SPI_TypeDef*)SPI0_BASE)
#define SPI1    ((SPI_TypeDef*)SPI1_BASE)
#define FC      ((FC_TypeDef*)FLASH_CTRL_BASE)
#define AC      ((AC_TypeDef*)AC_BASE)
#define PWM0    ((PWM_TypeDef*)PWM0_BASE)
#define PWM1    ((PWM_TypeDef*)PWM1_BASE)
#define TINY    ((TINY_TypeDef*)TINY_BASE)
#define TINY_IM ((volatile u32*)TINY_IM_BASE)
#define UART0   ((UART_TypeDef*)UART0_BASE)
#define UART1   ((UART_TypeDef*)UART1_BASE)
#define PMU     ((PMU_TypeDef*)PMU_BASE)
#define CGU     ((CGU_TypeDef*)CGU_BASE)
#define RCU     ((RCU_TypeDef*)RCU_BASE)
#define TOP     ((TOP_TypeDef*)TOP_BASE)
#define EBI     ((EBI_TypeDef *)EBI_BASE)



#endif  /* _M2C8001_H */

