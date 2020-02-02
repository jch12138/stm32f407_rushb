/*
 * @Author: jiang chenhui
 * @Date: 2020-01-31 19:30:11
 * @LastEditTime : 2020-02-01 14:45:51
 * @LastEditors  : Please set LastEditors
 * @Description: driver for infrared
 * @FilePath: \stm32f407-rushb\bsp_driver\bsp_infrared.c
 */

#include "bsp_infrared.h"

/* global parameter which restore infrared info */
SINGLE_INFO infrared_info;

/**
 * @description: infrared initilaze
 * @param none
 * @return: status
 */
rt_err_t infrared_init(void)
{
    rt_pin_mode(START_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(UP_PIN,PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(DOWN_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(LEFT_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(RIGHT_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(FRONT_LEFT_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(FRONT_RIGHT_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(SEESAW_PIN, PIN_MODE_INPUT_PULLUP);
}

/**
 * @description: read infrared info
 * @param none 
 * @return: none
 */
void get_infrared_info(void)
{
    infrared_info.start         = rt_pin_read(START_PIN);
    infrared_info.up            = rt_pin_read(UP_PIN);
    infrared_info.down          = rt_pin_read(DOWN_PIN);
    infrared_info.left          = rt_pin_read(LEFT_PIN);
    infrared_info.right         = rt_pin_read(RIGHT_PIN);
    infrared_info.front_left    = rt_pin_read(FRONT_LEFT_PIN);
    infrared_info.front_right   = rt_pin_read(FRONT_RIGHT_PIN);
    infrared_info.seesaw        = rt_pin_read(SEESAW_PIN);
}

/**
 * @description: wait infrared signal of start
 * @param none
 * @return: none
 */
void wait_infrared_start_signal(void)
{
    while (1)
    {
        if(infrared_info.start == PIN_LOW)
        break;
    }
    while (1)
    {
        if(infrared_info.start == PIN_HIGH)
        break;
    }
}