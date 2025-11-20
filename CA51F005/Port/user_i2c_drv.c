#include "defines.h"
#include "port_def.h"
#include "user_i2c_drv.h"

#include "include/ca51f005_config.h"		
#include "include/ca51f005sfr.h"
#include "include/ca51f005xsfr.h"
#include "include/gpiodef_f005.h"
#include "include/i2c.h"
#include "include/delay.h"

#define I2C_ADDRESS           				0xA0               /* Local address 0xA0 */
#define I2C_SPEEDCLOCK        				400000//400000             /* Communication speed 400K */


#define CPU_FREQ							24000000
#define I2C_OK 								0
#define I2C_ERROR 							1

uint8_t I2C_Wait_Flag_Set(uint32_t Timeout) 
{
    uint32_t counter = 0;
    while (!(I2CFLG & I2CF)) 
	{
        if (counter++ > Timeout) 
		{
            return I2C_ERROR;
        }
        Delay_50us(1); // 微小延时，可根据平台调整
    }
    return I2C_OK;
}

void I2C_Start(void) 
{
    I2CCON |= STA(1);
    I2CFLG |= I2CF;
}

void I2C_Stop(void) 
{
    I2CCON |= STP(1);
    I2CFLG |= I2CF;
}

uint8_t I2C_Write_Byte(uint8_t byte, uint32_t Timeout) 
{
    I2CDAT = byte;
    I2CFLG |= I2CF;
    if (I2C_Wait_Flag_Set(Timeout) == I2C_ERROR) 
	{
        return I2C_ERROR;
    }
    if (I2CSTA != 0x18 && I2CSTA != 0x28 && I2CSTA != 0x40 && I2CSTA != 0x30) 
	{
        return I2C_ERROR;
    }
    return I2C_OK;
}

uint8_t I2C_Read_Byte(uint8_t* pBuffer, uint8_t ack, uint32_t Timeout) 
{
    if (ack)
    {
        I2CCON |= AAK(1);        
    }
    else
    {
        I2CCON &= ~AAK(1);
    }    
    I2CFLG |= I2CF;
    if (I2C_Wait_Flag_Set(Timeout) == I2C_ERROR) 
	{
        return I2C_ERROR;
    }
    *pBuffer = I2CDAT;
    return I2C_OK;
}

uint8_t I2C_Mem_Read(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pBuffer, uint16_t Size, uint32_t Timeout) 
{
    uint16_t i;
    I2C_Start();
    if (I2C_Wait_Flag_Set(Timeout) == I2C_ERROR || I2CSTA != 0x08 || I2C_Write_Byte((DevAddress << 1) | 0, Timeout) == I2C_ERROR) 
	{
        I2C_Stop();
        return I2C_ERROR;
    }

    if (MemAddSize == 2) 
	{
        if (I2C_Write_Byte((MemAddress >> 8) & 0xFF, Timeout) == I2C_ERROR) 
		{
            I2C_Stop();
            return I2C_ERROR;
        }
    }
    if (I2C_Write_Byte(MemAddress & 0xFF, Timeout) == I2C_ERROR) 
	{
        I2C_Stop();
        return I2C_ERROR;
    }


    I2C_Start();
    if (I2C_Wait_Flag_Set(Timeout) == I2C_ERROR || I2CSTA != 0x08 || I2C_Write_Byte((DevAddress << 1) | 1, Timeout) == I2C_ERROR) 
	{
        I2C_Stop();
        return I2C_ERROR;
    }
    

    for (i = 0; i < Size; i++) 
	{
        uint8_t ack = (i < (Size - 1)) ? 1 : 0;
        if (I2C_Read_Byte(&pBuffer[i], ack, Timeout) == I2C_ERROR) 
		{
            I2C_Stop();
            return I2C_ERROR;
        }
    }
    I2C_Stop();
    return I2C_OK;
}

uint8_t I2C_Mem_Write(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pBuffer, uint16_t Size, uint32_t Timeout) 
{
    uint16_t i;
    I2C_Start();
    if (I2C_Wait_Flag_Set(Timeout) == I2C_ERROR || I2CSTA != 0x08 || I2C_Write_Byte((DevAddress << 1) | 0, Timeout) == I2C_ERROR) 
    {
        I2C_Stop();
        return I2C_ERROR;
    }

    if (MemAddSize == 2) 
    {
        if (I2C_Write_Byte((MemAddress >> 8) & 0xFF, Timeout) == I2C_ERROR) 
        {
            I2C_Stop();
            return I2C_ERROR;
        }
    }
    if (I2C_Write_Byte(MemAddress & 0xFF, Timeout) == I2C_ERROR) 
    {
        I2C_Stop();
        return I2C_ERROR;
    }

    for (i = 0; i < Size; i++) 
    {
        if (I2C_Write_Byte(pBuffer[i], Timeout) == I2C_ERROR) 
        {
            I2C_Stop();
            return I2C_ERROR;
        }
    }

    I2C_Stop();
    return I2C_OK;
}

void user_i2c_init(void)
{
#if 1	// P06 SDA, P07 SCL
	I2CIOS = 0;
	P06F = P06_I2C_SDA_SETTING | PU_EN;
	P07F = P07_I2C_SCL_SETTING | PU_EN;	
#else	// P13 SCL, P14 SDA
	I2CIOS = 2;
	P14F = P14_I2C_SDA_SETTING | PU_EN;
	P13F = P13_I2C_SCL_SETTING | PU_EN;	
#endif
	I2CCON = I2CE(1) | I2CIE(0) | STA(0) | STP(0)| CKHD(1) | AAK(1)| CBSE(0) | STFE(1);		
	I2CADR = GCE(0);
#if I2C_SPEEDCLOCK == 400000    
	I2CCCR = 0x4C;							//设置I2C时钟 400KHZ时钟
#else    
	I2CCCR = 0x8C;                          //设置I2C 100KHZ时钟
#endif   
}

uint32_t user_i2c_read(TwoWireParams *params)
{	
	uint32_t cnt = 0;
	if (I2C_Mem_Read(params->slaveAddr & 0xFF, params->reg, 1, (uint8_t *)params->pData, params->size, 1000) == I2C_OK)
	{
		cnt = params->size;					
	}
	return cnt;
}

uint32_t user_i2c_write(TwoWireParams *params)
{
	uint32_t cnt = 0;
	if (I2C_Mem_Write(params->slaveAddr & 0xFF, params->reg, 1, (uint8_t *)params->pData, params->size, 1000) == I2C_OK)
	{
		cnt = params->size;
	}
  	return cnt;
}
