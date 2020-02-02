/*
 * @Author: jiang chenhui
 * @Date: 2020-01-30 19:13:22
 * @LastEditTime : 2020-02-02 21:57:31
 * @LastEditors  : Please set LastEditors
 * @Description: driver for motor
 * @FilePath: \stm32f407-rushb\bsp_driver\bsp_motor.h
 */
#ifndef __BSP_MOTOR_H__
#define __BSP_MOTOR_H__

#include "car.h"

#define PWM_DEV_NAME "pwm1"
#define PWM_DEV_CHANNEL1 1
#define PWM_DEV_CHANNEL2 2
#define PWM_DEV_CHANNEL3 3
#define PWM_DEV_CHANNEL4 4
#define PWM_PERIOD 10000 /* cycle is 10us */

/**
 * @description: motor device initialize 
 * @param none
 * @return: status
 */
rt_err_t motor_init(void);

/**
 * @description: set 4 motor's velocity
 * @param 4 motor's duty range in (0,PWM_PERIOD)
 * @return: none
 */
void motor_set(rt_uint32_t pwm1, rt_uint32_t pwm2, rt_uint32_t pwm3, rt_uint32_t pwm4);

/**
 * @description: go forward
 * @param right pwm and left pwm
 * @return: none
 */
void car_forward(rt_uint32_t pwm_left, rt_uint32_t pwm_right);

/**
 * @description: go backward
 * @param right pwm and left pwm
 * @return: none
 */
void car_backward(rt_uint32_t pwm_left, rt_uint32_t pwm_right);

/**
 * @description: go left
 * @param right pwm and left pwm
 * @return: none
 */
void car_left(rt_uint32_t pwm_left, rt_uint32_t pwm_right);

/**
 * @description: go right
 * @param right pwm and left pwm
 * @return: none
 */
void car_right(rt_uint32_t pwm_left, rt_uint32_t pwm_right);

/**
 * @description: stop
 * @param none
 * @return: none
 */
void car_stop(void);

#endif