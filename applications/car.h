/*
 * @Author: jiang chenhui
 * @Date: 2020-01-31 17:30:34
 * @LastEditTime : 2020-02-02 21:38:10
 * @LastEditors  : Please set LastEditors
 * @Description: information of car , include all needed global parameters and structs.
 * @FilePath: \stm32f407-rushb\applications\car.h
 */

#ifndef __CAR_H__
#define __CAR_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <finsh.h>

#include "bsp_motor.h"
#include "bsp_adc.h"
#include "bsp_infrared.h"
#include "bsp_button.h"
#include "bsp_oled.h"

/* various track mode */
#define NONE        0
#define CENTER      1
#define STOP        2
#define LEFTT       3
#define RIGHTT      4
#define CENTERLEFT  5
#define UPBRIDGE    6
#define BRIDGE      7
#define WAVE        8
#define SEESAW      9
#define ROUND       10
#define SLOW        11


typedef struct 
{
    rt_uint16_t speed_base_left;        /* base speed for pid */
    rt_uint16_t speed_base_right;

    rt_uint16_t left_speed;             /* final output speed after pid */
    rt_uint16_t right_speed;

    rt_uint16_t trace;                  /* track mode */

} Car;

typedef struct
{
    rt_uint8_t len;                     /* number of gray scale sensor channels */
    rt_uint16_t adc_data[12];           /* buffer of adc data */

    rt_uint8_t white_num;               /* number of white lines */
    rt_uint8_t white_buf[12];           /* buffer of white lines */

    rt_uint8_t green_num;	            /* number of green parts */
    rt_uint8_t green_buf[12];           /* buffer of green parts */

    rt_uint8_t left_white;	            /* number of white lines on left */
    rt_uint8_t right_white;             /* number of white lines on right */ 

    rt_uint16_t adc_min;                /* the minimum value of lines's adc value */
    rt_uint16_t adc_max;                /* the maximum value of lines's adc value */

    rt_uint16_t White_Value;            /* threshold of white */
    rt_uint16_t Green_Value;            /* threshold of green */                  
                     
    float now_position;                 /* now position of car */
    float aim;                          /* Target location  */
	
} LINE_POS;

typedef struct 
{
	rt_uint8_t start;                   /* starting point */
	rt_uint8_t door;                    /* door point */
    
	rt_uint8_t left;                    /* is there any obstacle on the left  */
	rt_uint8_t right;                   /* is there any obstacle on the right */
	
	rt_uint8_t front_left;              /* is there any obstacle on the front left */
	rt_uint8_t front_right;             /* is there any obstacle on the front right */
	
	rt_uint8_t up;                      /* ? */
	rt_uint8_t down;                    /* ? */
	
	rt_uint8_t seesaw;             /* ? */

}SINGLE_INFO;

/* global parameter which restore infrared info */
extern SINGLE_INFO infrared_info;

/* global parameters of line model */
extern LINE_POS line;
extern LINE_POS back_line;

/* oled show mode control */
extern rt_uint8_t oled_show_mode;

#endif