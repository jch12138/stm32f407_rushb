/*
 * @Author: jiang chenhui
 * @Date: 2020-01-30 19:17:29
 * @LastEditTime : 2020-02-03 20:33:13
 * @LastEditors  : Please set LastEditors
 * @Description: driver for oled
 * @FilePath: \stm32f407-rushb\bsp_driver\bsp_oled.c
 */
#include "bsp_oled.h"

/* oled show mode control */
extern rt_uint8_t oled_show_mode;

/* oled low level api */
void OLED_WR_Byte(rt_uint8_t dat, rt_uint8_t cmd)
{
    rt_uint8_t i;
    if (cmd)
        OLED_DC_Set();
    else
        OLED_DC_Clr();
    OLED_CS_Clr();
    for (i = 0; i < 8; i++)
    {
        OLED_SCLK_Clr();
        if (dat & 0x80)
            OLED_SDIN_Set();
        else
            OLED_SDIN_Clr();
        OLED_SCLK_Set();
        dat <<= 1;
    }
    OLED_CS_Set();
    OLED_DC_Set();
}

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}

    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X14,OLED_CMD);  
	OLED_WR_Byte(0XAF,OLED_CMD);  
}
   
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X10,OLED_CMD);  
	OLED_WR_Byte(0XAE,OLED_CMD);  
}		   			 
	  
void OLED_Clear(void)  
{  
	rt_uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    
		OLED_WR_Byte (0x00,OLED_CMD);     
		OLED_WR_Byte (0x10,OLED_CMD);        
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} 
}

/**
 * @description: oled initilaze
 * @param none
 * @return: status
 */
rt_err_t oled_init(void)
{
    rt_pin_mode(OLED_SCK_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(OLED_SCK_PIN, PIN_MODE_OUTPUT);

    rt_pin_mode(OLED_SDA_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(OLED_SCK_PIN, PIN_MODE_OUTPUT);

    rt_pin_mode(OLED_RST_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(OLED_RST_PIN, PIN_MODE_OUTPUT);

    rt_pin_mode(OLED_DC_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(OLED_DC_PIN, PIN_MODE_OUTPUT);

    rt_pin_mode(OLED_CS_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(OLED_CS_PIN, PIN_MODE_OUTPUT);

    OLED_RST_Set();
	rt_thread_mdelay(200);
	OLED_RST_Clr();
	rt_thread_mdelay(200);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
}

/**
 * @description: show a character on oled
 * @param x,y coordinate and char
 * @return: none
 */
void oled_showchar(rt_uint8_t x,rt_uint8_t y,char ch)
{
    unsigned char c=0,i=0;	
	unsigned char mode_char;	
	
	c=ch-' ';			
	if(x>Max_Column-1)
	{ 
		x=0;
		y=y+1;
	}
	OLED_Set_Pos(x,y);
	for(i=0;i<6;i++)
	{
		mode_char = ~F6x8[c][i];
		OLED_WR_Byte(mode_char,OLED_DATA);
	}
}

/**
 * @description: show string on oled
 * @param x x coordinate 
 * @param y y coordinate
 * @param p string pointer
 * @return: none
 */
void oled_showstring(rt_int8_t x, rt_int8_t y, char *p)
{
    unsigned char j = 0;
    while (p[j] != '\0')
    {
        oled_showchar(x, y, chr[j]);
        x += 6;
        if (x > 120)
        {
            x = 0;
            y += 1;
        }
        j++;
    }
}

/**
 * @description: show gray scale infomation on oled
 * @param none 
 * @return: none
 */
void oled_show_gray(void);

/**
 * @description: show infrared information on oled
 * @param none
 * @return: none
 */
void oled_show_infrared(void);
