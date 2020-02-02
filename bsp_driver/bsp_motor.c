/*
 * @Author: jiang chenhui
 * @Date: 2020-01-30 19:13:22
 * @LastEditTime : 2020-01-31 15:16:39
 * @LastEditors  : Please set LastEditors
 * @Description: driver for motor
 * @FilePath: \stm32f407-rushb\bsp_driver\bsp_motor.c
 */

#include "bsp_motor.h"

struct rt_device_pwm *pwm_dev; //pwm device control handler

/**
 * @description: motor device initialize
 * @param none
 * @return: status
 */
rt_err_t motor_init(void)
{
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("cant find pwm device!\n");
        return RT_ERROR;
    }
    /* set duty */
    motor_set(0, 0, 0, 0);

    /* enable output */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL1);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL2);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL3);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL4);

    return RT_EOK;
}

/**
 * @description: set 4 motor's velocity
 * @param 4 motor's duty range in (0,PWM_PERIOD)
 * @return: none
 */
void motor_set(rt_uint32_t pwm1, rt_uint32_t pwm2, rt_uint32_t pwm3, rt_uint32_t pwm4)
{
    if(pwm1>PWM_PERIOD)pwm1=PWM_PERIOD;
    if(pwm2>PWM_PERIOD)pwm2=PWM_PERIOD;
    if(pwm3>PWM_PERIOD)pwm3=PWM_PERIOD;
    if(pwm4>PWM_PERIOD)pwm4=PWM_PERIOD;

    if(pwm1<-PWM_PERIOD)pwm1=-PWM_PERIOD;
    if(pwm2<-PWM_PERIOD)pwm2=-PWM_PERIOD;
    if(pwm3<-PWM_PERIOD)pwm3=-PWM_PERIOD;
    if(pwm4<-PWM_PERIOD)pwm4=-PWM_PERIOD;

    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL1, PWM_PERIOD, pwm1);
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL2, PWM_PERIOD, pwm2);
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL3, PWM_PERIOD, pwm3);
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL4, PWM_PERIOD, pwm4);
}

/**
 * @description: go forward
 * @param right pwm and left pwm
 * @return: none
 */
void car_forward(rt_uint32_t pwm_left, rt_uint32_t pwm_right)
{
    motor_set(pwm_left, pwm_right, 0, 0);
}

/**
 * @description: go backward
 * @param right pwm and left pwm
 * @return: none
 */
void car_backward(rt_uint32_t pwm_left, rt_uint32_t pwm_right)
{
    motor_set(0, 0, -pwm_left, -pwm_right);
}

/**
 * @description: go left
 * @param right pwm and left pwm
 * @return: none
 */
void car_left(rt_uint32_t pwm_left, rt_uint32_t pwm_right)
{
    motor_set(0, pwm_right, -pwm_left, 0);
}

/**
 * @description: go right
 * @param right pwm and left pwm
 * @return: none
 */
void car_right(rt_uint32_t pwm_left, rt_uint32_t pwm_right)
{
    motor_set(pwm_left, 0, 0, -pwm_right);
}

/**
 * @description: stop
 * @param right pwm and left pwm
 * @return: none
 */
void car_stop(void)
{
    motor_set(0, 0, 0, 0);
}

/**
 * @description: Finsh test command
 * @param none
 * @return: none
 */
static void motor_test(void)
{
    car_forward(5000,5000);
    rt_thread_mdelay(1000);
    car_backward(5000,5000);
    rt_thread_mdelay(1000);
    car_left(2000,3000);
    rt_thread_mdelay(1000);
    car_right(3000,2000);
    rt_thread_mdelay(1000);
}
MSH_CMD_EXPORT(motor_test,motor test);