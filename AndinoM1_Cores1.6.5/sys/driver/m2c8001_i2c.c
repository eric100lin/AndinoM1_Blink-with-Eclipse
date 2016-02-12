#include "m2c8001_i2c.h"

#define I2C_RETRY_CNT   (1000000)


/*Check I2C Master Write status*/
#define I2C_WRITE_START_OK(status)	((status & (I2C_STAS_DT | I2C_STAS_ACK |I2C_STAS_RW |I2C_STAS_AL)) == I2C_STAS_DT )
#define I2C_WRITE_DATA_OK(status)	((status & (I2C_STAS_DT | I2C_STAS_ACK |I2C_STAS_RW | I2C_STAS_AL )) == I2C_STAS_DT )
#define I2C_WRITE_STOP_OK(status)	((status & (I2C_STAS_DT | I2C_STAS_ACK |I2C_STAS_RW  | I2C_STAS_AL )) == (I2C_STAS_DT) )


/*Check I2C Master Read status*/
#define I2C_READ_START_OK(status)	((status & (I2C_STAS_DT | I2C_STAS_ACK |I2C_STAS_RW |I2C_STAS_AL)) == (I2C_STAS_DT  |I2C_STAS_RW))
#define I2C_READ_DATA_OK(status)	((status & (I2C_STAS_DR | I2C_STAS_ACK |I2C_STAS_RW )) == (I2C_STAS_DR |I2C_STAS_RW))
#define I2C_READ_STOP_OK(status)	((status & (I2C_STAS_DR | I2C_STAS_ACK |I2C_STAS_RW)) == (I2C_STAS_DR | I2C_STAS_ACK |I2C_STAS_RW))

/*
#define I2C_DBG_EN  (0)

#if I2C_DBG_EN
#define I2C_DBG(...)    DBG_PRINT(__VA_ARGS__);
#else
#define I2C_DBG(...)
#endif
*/

void I2C_Init(u8 u8Mode,u8 u8Div)
{
    /*Enable I2C clock*/
    CGU->PIPCLKSW |= PIP_EN_I2C_CLK;

    /*Reset I2C IP*/
    RCU->CSRSWRSTN &= ~RCU_SW_RST_I2C;

    if(u8Mode == I2C_MODE_MASTER){
        I2C->CDR = u8Div;
        I2C->CR |= (I2C_CTRL_ENABLE|I2C_CTRL_SCL_EN);
    }
    else
        I2C->CR = I2C_CTRL_ENABLE;

}

void I2C_DeInit(void)
{
    CGU->PIPCLKSW &= ~PIP_EN_I2C_CLK;
    //I2C_IsrDeInit();
}

void I2C_SetPCLK(u32 div)
{
    I2C->CDR = div;
}

u8 I2C_Readbyte(void)
{
    return I2C->DR ;
}

void I2C_Writebyte(u8 u8Data)
{
    I2C->DR = u8Data;
}

u8 I2C_Write(u8 u8Addr, u8 * pu8Data, u8 u8Len)
{
    u32 retryCnt = 0;
    u32 status = 0;

    u8 i;
    //I2C_DBG("I2C_M Write Start \r\n");
    /*Write slave addr to Data Reg*/
    I2C->DR =((u8Addr << 1) & 0xFE);

    /*START*/
    I2C->CR |= (I2C_CTRL_START |I2C_CTRL_TB_EN) ;

    do{
        if(retryCnt++ > I2C_RETRY_CNT){
            //I2C_DBG("I2C_Write Start Error sts:%x\n\r",status);
            return I2C_RET_TIMEOUT;
        }
        status = I2C->SR;
    }while(!I2C_WRITE_START_OK(status));

    I2C->CR &= ~(I2C_CTRL_START);

    /*Transmit data 0~N-1 byte*/
    for(i=0;i<u8Len-1;i++,pu8Data++){
        I2C->DR = *pu8Data;
        retryCnt = 0;
        /*Send Data*/
        //I2C_DBG("I2C_M Write Data \r\n");
        I2C->CR  |= I2C_CTRL_TB_EN ;
        do{
            if(retryCnt++ >I2C_RETRY_CNT){
                //I2C_DBG("I2C_Write Tx  Error sts:%x\n\r",status);
                return I2C_RET_TIMEOUT;
            }
            status = I2C->SR;
        }while(!I2C_WRITE_DATA_OK(status));
    }

    /*Last byte and STOP*/
    I2C->DR = *pu8Data;
    retryCnt = 0;
    //I2C_DBG("I2C_M Write Stop \r\n");
    I2C->CR  |= (I2C_CTRL_TB_EN | I2C_CTRL_STOP) ;
    do{
        if(retryCnt++ >I2C_RETRY_CNT){
            //I2C_DBG("I2C_Write Stop Error sts:%x\n\r",status);
            return I2C_RET_TIMEOUT;
        }
        status = I2C->SR;
    }while(!I2C_WRITE_STOP_OK(status));
    /*Recover to default state*/
    I2C->CR &= ~(I2C_CTRL_STOP) ;
    
    //I2C_DBG("I2C_M Write End \r\n");
    return I2C_RET_SUCCESS;
}

u8 I2C_Read(u8 u8Addr, u8 * pu8Data, u8 u8Len)
{
    u32 retryCnt = 0;
    u32 status = 0;
    u8 i;
    //I2C_DBG("I2C_M Read Start \r\n");
    /*Write slave addr to Data Reg*/
    I2C->DR =(u8Addr <<1)  | 0x1;

    /*START*/
    I2C->CR |= (I2C_CTRL_START |I2C_CTRL_TB_EN);
    do{
        if(retryCnt++ > I2C_RETRY_CNT){
            //I2C_DBG("I2C_Read Start Error sts:%x \r\n",status);
            return I2C_RET_TIMEOUT;
        }
        status = I2C->SR;
    }while(!I2C_READ_START_OK(status));
    I2C->CR &= ~(I2C_CTRL_START);

    /*Receive data 0~N-1 byte*/
    for(i=0;i<u8Len-1;i++,pu8Data++){
        retryCnt = 0;
        /*Send Data*/
        I2C->CR |= I2C_CTRL_TB_EN ;
        do{
            if(retryCnt++ >I2C_RETRY_CNT){
                //I2C_DBG("I2C_Read Tx  Error sts:%x\n\r",status);
                return I2C_RET_TIMEOUT;
            }
            status = I2C->SR;
        }while(!I2C_READ_DATA_OK(status));
        *pu8Data = I2C->DR;
    }

    /*Last byte and STOP*/
    retryCnt = 0;
    I2C->CR |= (I2C_CTRL_STOP |I2C_CTRL_TB_EN | I2C_CTRL_NACK) ;
    do{
        if(retryCnt++ >I2C_RETRY_CNT){
            //I2C_DBG("I2C_Read End  Error sts:%x\n\r",status);
            return I2C_RET_TIMEOUT;
        }
        status = I2C->SR;
    }while(!I2C_READ_STOP_OK(status));
    *pu8Data = I2C->DR;
    /*Recover to default state*/
    I2C->CR &= ~(I2C_CTRL_STOP  | I2C_CTRL_NACK) ;

    //I2C_DBG("I2C_M Read End \r\n");
    return I2C_RET_SUCCESS;
}
