#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f005_config.h"		
#include "include/ca51f005sfr.h"
#include "include/ca51f005xsfr.h"
#include "include/gpiodef_f005.h"
#include "include/system_clock.h"
#include "include/uart.h"
#include "include/i2c.h"
#include "include/delay.h"
#include <intrins.h>
#include "aries_sdk.h"	
/*********************************************************************************************************************/
#define LED_ON                						1
#define LED_OFF               						0
#define LED_PIN										P05
#define	BUTTON_PIN									P04

#define LED(X)										LED_PIN = X
#define BUTTON()									BUTTON_PIN == 0

#define INT_TIME									1000
#define	TH_VAL										(uint8_t)((0x10000 - (INT_TIME * (FOSC / 1000)) / 12000) >> 8)
#define	TL_VAL										(uint8_t)(0x10000 - (INT_TIME * (FOSC / 1000)) / 12000)
#define HAL_GetTick()								sysTick					

#define MIN(X,Y)									X > Y ? Y : X

volatile uint32_t data sysTick = 0;

#ifdef DEBUG
#define printf_BUFF_LEN       64
volatile uint8_t xdata buff_tx[printf_BUFF_LEN];
volatile uint32_t count = 0;
char putchar(char ch)
{
    buff_tx[count++] = ch;
	if(count >= printf_BUFF_LEN || ch == '\n')
	{
		aries_sdk_cdc_write(buff_tx, count);
		count = 0;
	}
    return ch;
}

char _getkey(void)
{
	char c;
	while (aries_sdk_cdc_get_length() == 0);
	aries_sdk_cdc_read(&c, 1);
	return c;
}
#endif



void timer0_isr (void) interrupt 1 
{
	TH0 = TH_VAL;
	TL0 = TL_VAL;
	sysTick++;
}

void systick_init(void)
{
	TMOD = (TMOD & 0xFC) | 0x01;
	TH0 = TH_VAL;
	TL0 = TL_VAL;
	TR0 = 1;
	ET0 = 1;
	PT0 = 0;
}

static void APP_GpioConfig(void)
{
	//LED
	P05F = OUTPUT;
	LED(LED_OFF);
	//BUTTON	
	P04F = INPUT | PU_EN;
}

void main(void)
{
	uint32_t ledTick = 0;
	//char input_string[32];
	Sys_Clk_Set_IRCH();	
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE3;					//设置LVD复位电压为2V
#endif
	systick_init();
	APP_GpioConfig();
	aries_sdk_init();
	EA = 1;
	printf("CA51F005 Application Startup...\r\n");

	while(1)
	{
		if((HAL_GetTick() - ledTick) > 500)
		{
			LED_PIN = ~LED_PIN;
			printf("LED Changed ...\r\n");
			ledTick = HAL_GetTick();
		}
		if(BUTTON() == 1)
		{
			printf("Button press down ...\r\n");
			//printf("Please tell me what you want?\r\n");
			//scanf("%s", input_string);
			//printf("You entered: %s\r\n", input_string);
		}	
	}
}
#endif
