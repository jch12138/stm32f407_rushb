/*
 * @Author: jiang chenhui
 * @Date: 2020-01-31 19:25:12
 * @LastEditTime : 2020-02-01 13:13:43
 * @LastEditors  : Please set LastEditors
 * @Description: driver for button
 * @FilePath: \stm32f407-rushb\bsp_driver\bsp_button.c
 */

#include "bsp_button.h"

/**
 * @description: button initialize
 * @param none 
 * @return: status 
 */
rt_err_t button_init(void)
{
    rt_pin_mode(KEY1, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY2, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY3, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY4, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY5, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY6, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY7, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY8, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(SURE, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(EXTI, PIN_MODE_INPUT_PULLUP);

    return RT_EOK;
}

/**
 * @description: read button
 * @param none
 * @return: key code
 */
rt_uint8_t button_read(void)
{
    rt_uint8_t key = 0;

    while (1)
    {
        if (rt_pin_read(KEY1) == PIN_LOW)
        {
            rt_thread_mdelay(20);
            if (rt_pin_read(KEY1) == PIN_LOW)
            {
                key = 1;
            }
        }
        if (rt_pin_read(KEY2) == PIN_LOW)
        {
            rt_thread_mdelay(20);
            if (rt_pin_read(KEY2) == PIN_LOW)
            {
                key = 2;
            }
        }

        if (rt_pin_read(KEY3) == PIN_LOW)
        {
            rt_thread_mdelay(20);
            if (rt_pin_read(KEY3) == PIN_LOW)
            {
                key = 3;
            }
        }

        if (rt_pin_read(KEY4) == PIN_LOW)
        {
            rt_thread_mdelay(20);
            if (rt_pin_read(KEY4) == PIN_LOW)
            {
                key = 4;
            }
        }

        if (rt_pin_read(KEY5) == PIN_LOW)
        {
            rt_thread_mdelay(20);
            if (rt_pin_read(KEY5) == PIN_LOW)
            {
                key = 5;
            }
        }

        if (rt_pin_read(KEY6) == PIN_LOW)
        {
            rt_thread_mdelay(20);
            if (rt_pin_read(KEY6) == PIN_LOW)
            {
                key = 6;
            }
        }

        if (rt_pin_read(KEY7) == PIN_LOW)
        {
            rt_thread_mdelay(20);
            if (rt_pin_read(KEY7) == PIN_LOW)
            {
                key = 7;
            }
        }

        if (rt_pin_read(KEY8) == PIN_LOW)
        {
            rt_thread_mdelay(20);
            if (rt_pin_read(KEY8) == PIN_LOW)
            {
                key = 8;
            }
        }

        if (rt_pin_read(SURE) == PIN_LOW)
        {
            rt_thread_mdelay(20);
            if (rt_pin_read(SURE) == PIN_LOW)
            {
                key = 9;
            }
        }

        if (key != 0)
        {
            break;
        }
    }

    return key;
}