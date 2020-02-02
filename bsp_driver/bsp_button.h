/*
 * @Author: jiang chenhui
 * @Date: 2020-01-31 19:25:05
 * @LastEditTime : 2020-02-02 21:39:12
 * @LastEditors  : Please set LastEditors
 * @Description: driver for button
 * @FilePath: \stm32f407-rushb\bsp_driver\bsp_button.h
 */

#ifndef __BSP_BUTTON_H__
#define __BSP_BUTTON_H__

#include <car.h>

#define KEY1    GET_PIN(F,11)
#define KEY2    GET_PIN(F,13)
#define KEY3    GET_PIN(F,15)
#define KEY4    GET_PIN(F,10)
#define KEY5    GET_PIN(F,12)
#define KEY6    GET_PIN(F,14)
#define KEY7    GET_PIN(E, 3)
#define KEY8    GET_PIN(E, 0)
#define SURE    GET_PIN(E, 4)
#define EXTI    GET_PIN(E, 1)

/**
 * @description: button initialize
 * @param none 
 * @return: status 
 */
rt_err_t button_init(void);

/**
 * @description: read button
 * @param none
 * @return: key code
 */
rt_uint8_t button_read(void);

#endif
