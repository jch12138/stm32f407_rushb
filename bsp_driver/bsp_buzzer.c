/*
 * @Author: jiang chenhui
 * @Date: 2020-01-31 19:29:16
 * @LastEditTime : 2020-02-02 21:58:34
 * @LastEditors  : Please set LastEditors
 * @Description: driver for buzzer
 * @FilePath: \stm32f407-rushb\bsp_driver\bsp_buzzer.c
 */

#include "bsp_buzzer.h"

/**
 * @description: buzzer initilaze
 * @param none
 * @return: status
 */

rt_err_t buzzer_init(void)
{
    rt_pin_mode(BUZZER_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(BUZZER_PIN, PIN_LOW);

    return RT_EOK;
}

/**
 * @description: buzzer beep
 * @param none 
 * @return: none
 */
void buzzer_beep(void)
{
    rt_pin_write(BUZZER_PIN, PIN_HIGH);
    rt_thread_mdelay(500);
    rt_pin_write(BUZZER_PIN, PIN_LOW);
}

/**
 * @description: Finsh test command
 * @param none 
 * @return: none
 */
static void buzzer_test(void)
{
    buzzer_beep();
}

MSH_CMD_EXPORT(buzzer_test, buzzer test);
