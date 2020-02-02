/*
 * @Author: jiang chenhui
 * @Date: 2020-01-31 19:30:11
 * @LastEditTime : 2020-02-01 14:44:35
 * @LastEditors  : Please set LastEditors
 * @Description: driver for light sensor like rgb led and infrared
 * @FilePath: \stm32f407-rushb\bsp_driver\bsp_light_sensor.h
 */

#ifndef __BSP_INFRARED_H__
#define __BSP_INFRARED_H__

#include "car.h"

#define START_PIN           GET_PIN(G,  2)
#define UP_PIN              GET_PIN(C, 14)
#define DOWN_PIN            GET_PIN(E,  5)
#define LEFT_PIN            GET_PIN(G,  5)
#define RIGHT_PIN           GET_PIN(G,  5)
#define FRONT_LEFT_PIN      GET_PIN(C, 13)
#define FRONT_RIGHT_PIN     GET_PIN(E,  6)
#define SEESAW_PIN          GET_PIN(G,  3)

/**
 * @description: infrared initilaze
 * @param none
 * @return: status
 */
rt_err_t infrared_init(void);

/**
 * @description: read infrared info
 * @param none 
 * @return: none
 */
void get_infrared_info(void);

/**
 * @description: wait infrared signal of start
 * @param none
 * @return: none
 */
void wait_infrared_start_signal(void);

#endif
