/*
 * @Author: jiang chenhui
 * @Date: 2020-01-31 19:29:16
 * @LastEditTime : 2020-02-02 21:39:22
 * @LastEditors  : Please set LastEditors
 * @Description: driver for buzzer
 * @FilePath: \stm32f407-rushb\bsp_driver\bsp_beep.h
 */

#ifndef __BSP_BUZZER_H__
#define __BSP_BUZZER_H__

#include <car.h>

#define BUZZER_PIN  GET_PIN(C, 15)

/**
 * @description: buzzer initilaze
 * @param none
 * @return: status
 */

rt_err_t buzzer_init(void);

/**
 * @description: buzzer beep
 * @param none 
 * @return: none
 */
void buzzer_beep(void);

#endif