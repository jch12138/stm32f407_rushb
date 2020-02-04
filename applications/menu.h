/*
 * @Author: jiang chenhui
 * @Date: 2020-02-04 11:16:28
 * @LastEditTime : 2020-02-04 11:23:46
 * @LastEditors  : Please set LastEditors
 * @Description: oled menu
 * @FilePath: \stm32f407-rushb\applications\menu.h
 */

#ifndef __MENU_H__
#define __MENU_H__

# include "car.h"

#define KEY_ON	0
#define KEY_OFF	1
#define PAGE_DISP_NUM 7
#define NULL 0

typedef enum 
{
	KEY_U,
	KEY_D,
	KEY_L,
	KEY_R,
	KEY_B,
	KEY_MAX,
	KEY_NULL
}KEY_e;

typedef struct{
	KEY_e key;
	rt_uint8_t status;
}KEY_MSG;

typedef struct{
	rt_uint8_t x;
	rt_uint8_t y;
}Site_t;

typedef struct{

	rt_uint8_t ExitMark;     

	rt_uint8_t Cursor;       

	rt_uint8_t PageNo;       

	rt_uint8_t Index;       

	rt_uint8_t DispNum;     

	rt_uint8_t MaxPage;     
}MENU_PRMT;     


typedef struct{

	rt_uint8_t *MenuName;		

	void(*ItemHook)(void); 

	rt_uint16_t *DebugParam;		
	
}MENU_TABLE;     


extern KEY_MSG keymsg;


void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,rt_uint16_t GPIO_Pin);

KEY_e wait_KEY(void);

void MainMenu_Set(void);
void Menu_motor(void);

void read_data_from_flash(void);
void save_data_to_flash(void);
	

#endif