/*
 * @Author: jiang chenhui
 * @Date: 2020-01-30 19:17:23
 * @LastEditTime : 2020-02-02 21:52:44
 * @LastEditors  : Please set LastEditors
 * @Description: driver for oled
 * @FilePath: \stm32f407-rushb\bsp_driver\bsp_oled.h
 */

#ifndef __BSP_OLED_H__
#define __BSP_OLED_H__

#include "car.h"

/* pin define */
#define OLED_SCK_PIN    GET_PIN(F,6)
#define OLED_SDA_PIN    GET_PIN(F,4)
#define OLED_RST_PIN    GET_PIN(F,2)
#define OLED_DC_PIN     GET_PIN(F,1)
#define OLED_CS_PIN     GET_PIN(F,0)

/* pin operation define */
#define OLED_SCK_SET    rt_pin_write(OLED_SCK_PIN, PIN_HIGH)
#define OLED_SCK_RESET  rt_pin_write(OLED_SCK_PIN, PIN_LOW)

#define OLED_SDA_SET    rt_pin_write(OLED_SDA_PIN, PIN_HIGH)
#define OLED_SDA_RESET  rt_pin_write(OLED_SCK_PIN, PIN_LOW)

#define OLED_RST_SET    rt_pin_write(OLED_RST_PIN, PIN_HIGH)
#define OLED_RST_RESET  rt_pin_write(OLED_RST_PIN, PIN_LOW)

#define OLED_DC_SET     rt_pin_write(OLED_DC_PIN, PIN_HIGH)
#define OLED_DC_RESET   rt_pin_write(OLED_DC_PIN, PIN_LOW)

#define OLED_CS_SET     rt_pin_write(OLED_CS_PIN, PIN_HIGH)
#define OLED_CS_RESET   rt_pin_write(OLED_CS_PIN, PIN_LOW)

/* write data kind define */
#define OLED_CMD    0
#define OLED_DATA   1

rt_err_t oled_init(void)
#endif