/*
 * @Author: jiang chenhui
 * @Date: 2020-01-31 20:42:19
 * @LastEditTime : 2020-02-02 19:38:05
 * @LastEditors  : Please set LastEditors
 * @Description: map information 
 * @FilePath: \stm32f407-rushb\applications\map.h
 */

#ifndef __MAP_H__
#define __MAP_H__

#include <car.h>

/**
 * @description: map parameter initilaze
 * @param none 
 * @return: status
 */
rt_err_t map_init(void);

/**
 * @description: caculate the position of car
 * @param none 
 * @return: none
 */
void caculate_position(void);

/**
 * @description: caculate the position of car when car back
 * @param none 
 * @return: none
 */
void caculate_position_back(void);

/**
 * @description: update speed
 * @param none 
 * @return: none
 */
void update_speed(void);

/**
 * @description: update speed when car back
 * @param none 
 * @return: none
 */
void update_speed_back(void);

#endif