/*
 * @Author: jiang chenhui
 * @Date: 2020-01-31 20:42:24
 * @LastEditTime : 2020-02-03 15:07:20
 * @LastEditors  : Please set LastEditors
 * @Description: map information
 * @FilePath: \stm32f407-rushb\applications\map.c
 */
#include "map.h"

/* global parameters of line model */
LINE_POS line;
LINE_POS back_line;

/* global parameters of car model */
Car car;

/* pid parameters for various scence */
int kp_center     = 0     ; int kd_center     = 0;
int kp_leftt      = 0     ; int kd_leftt      = 0;
int kp_rightt     = 0     ; int kd_rightt     = 0;
int kp_centerleft = 0     ; int kd_centerleft = 0;
int kp_upbridge   = 0     ; int kd_upbridge   = 0;
int kp_bridge     = 0     ; int kd_bridge     = 0;
int kp_wave       = 0     ; int kd_wave       = 0;
int kp_seesaw     = 0     ; int kd_seesaw     = 0;
int kp_round      = 0     ; int kd_round      = 0;
int kp_slow       = 0     ; int kd_slow       = 0;
int kp_back       = 0     ; int kd_back       = 0;

FINSH_VAR_EXPORT(kp_center,     finsh_type_int,     kp center)
FINSH_VAR_EXPORT(kp_leftt,      finsh_type_int,     kp leftt)
FINSH_VAR_EXPORT(kp_rightt,     finsh_type_int,     kp rightt)
FINSH_VAR_EXPORT(kp_centerleft, finsh_type_int,     kp centerleft)
FINSH_VAR_EXPORT(kp_upbridge,   finsh_type_int,     kp upbridge)
FINSH_VAR_EXPORT(kp_bridge,     finsh_type_int,     kp bridge)
FINSH_VAR_EXPORT(kp_wave,       finsh_type_int,     kp wave)
FINSH_VAR_EXPORT(kp_seesaw,     finsh_type_int,     kp seesaw)
FINSH_VAR_EXPORT(kp_round,      finsh_type_int,     kp round)
FINSH_VAR_EXPORT(kp_slow,       finsh_type_int,     kp slow)
FINSH_VAR_EXPORT(kp_back,       finsh_type_int,     kp back)
FINSH_VAR_EXPORT(kd_center,     finsh_type_int,     kd center)
FINSH_VAR_EXPORT(kd_leftt,      finsh_type_int,     kd leftt)
FINSH_VAR_EXPORT(kd_rightt,     finsh_type_int,     kd rightt)
FINSH_VAR_EXPORT(kd_centerleft, finsh_type_int,     kd centerleft)
FINSH_VAR_EXPORT(kd_upbridge,   finsh_type_int,     kd upbridge)
FINSH_VAR_EXPORT(kd_bridge,     finsh_type_int,     kd bridge)
FINSH_VAR_EXPORT(kd_wave,       finsh_type_int,     kd wave)
FINSH_VAR_EXPORT(kd_seesaw,     finsh_type_int,     kd seesaw)
FINSH_VAR_EXPORT(kd_round,      finsh_type_int,     kd round)
FINSH_VAR_EXPORT(kd_slow,       finsh_type_int,     kd slow)
FINSH_VAR_EXPORT(kd_back,       finsh_type_int,     kd back)


/**
 * @description: float abs function
 * @param float  
 * @return: float
 */
float fabs(float num)
{
    if (num >= 0)
    {
        return num;
    }
    else
    {
        return (-num);
    }
}

/**
 * @description: map parameter initilaze
 * @param none 
 * @return: status
 */
rt_err_t map_init(void)
{
    line.len = 14;
    line.white_num = 0;
    line.green_num = 0;

    line.adc_min = 4095;
    line.adc_max = 0;
    
    line.Green_Value = 100;
    line.White_Value = 3300;

    line.aim = 6.5f;
    line.now_position = 6.5f;

    return RT_EOK;
}

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
void update_speed(void)
{
    static float Ek0=0, Ek1=0;    /* last error and this time error */
    int pid_out;       /* pid output */
    Ek0 = line.aim - line.now_position; /* this time error */

    /* various track mode */
    if(car.trace == NONE)
    {
        pid_out = 0;
    }
    else if(car.trace == CENTER)
    {
        pid_out = (int)(kp_center * Ek0 + kd_center * (Ek0 - Ek1));
    }
    else if(car.trace == STOP)
    {
        car_stop();
        goto exti;
    }
    else if(car.trace == LEFTT || car.trace == CENTERLEFT)
    {
        pid_out = (int)(kp_leftt  * Ek0 + kd_leftt  * (Ek0 - Ek1));
    }
    else if(car.trace == RIGHTT)
    {
        pid_out = (int)(kp_rightt * Ek0 + kd_rightt * (Ek0 - Ek1));
    }
    else if(car.trace == SEESAW)
    {
        pid_out = (int)(kp_seesaw * Ek0 + kd_seesaw * (Ek0 - Ek1));
    }
    else if(car.trace == ROUND)
    {
        pid_out = (int)(kp_round  * Ek0 + kd_round  * (Ek0 - Ek1));
    }
    else if(car.trace == WAVE)
    {
        pid_out = (int)(kp_wave   * Ek0 + kd_wave   * (Ek0 - Ek1));
    }
    else if(car.trace == BRIDGE)
    {
        pid_out = (int)(kp_bridge * Ek0 + kd_bridge * (Ek0 - Ek1));
    }
    else if(car.trace == SLOW)
    {
        pid_out = (int)(kp_slow   * Ek0 + kd_slow   * (Ek0 - Ek1));
    }
    else
    {
        pid_out = 0;
    }

    /* update speed */
    car.left_speed  = car.speed_base_left  - pid_out;
    car.right_speed = car.speed_base_right + pid_out;
    
    /* output speed */
    car_forward(car.left_speed, car.right_speed);

exti:
    /* update error */
    Ek1 = Ek0;
}

/**
 * @description: update speed when car back
 * @param none 
 * @return: none
 */
void update_speed_back(void)
{
    static float Ek0 = 0,Ek1 = 0;
    float pid_out ;
    Ek0  = 3.5f - back_line.now_position; /* why 3.5f? */
    pid_out = (int)(kp_back * Ek0 + kd_back * (Ek0 - Ek1));
    
     /* update speed */
    car.left_speed  = car.speed_base_left  - pid_out;
    car.right_speed = car.speed_base_right + pid_out;
    
    /* output speed */
    car_forward(car.left_speed, car.right_speed);

    /* update error */
    Ek1 = Ek0;
}

/**
 * @description: Finsh show pid parameter command 
 * @param none 
 * @return: none
 */
void show_parameter(void)
{
    rt_kprintf("kp_center     :%5d kd_center     :%5d\n", kp_center, kd_center);
    rt_kprintf("kp_leftt      :%5d kd_leftt      :%5d\n", kp_leftt, kd_leftt);
    rt_kprintf("kp_rightt     :%5d kd_rightt     :%5d\n", kp_rightt, kd_rightt);
    rt_kprintf("kp_centerleft :%5d kd_centerleft :%5d\n", kp_centerleft, kd_centerleft);
    rt_kprintf("kp_upbridge   :%5d kd_upbridge   :%5d\n", kp_upbridge, kd_upbridge);
    rt_kprintf("kp_bridge     :%5d kd_bridge     :%5d\n", kp_bridge, kd_bridge);
    rt_kprintf("kp_wave       :%5d kd_wave       :%5d\n", kp_wave, kd_wave);
    rt_kprintf("kp_seesaw     :%5d kd_seesaw     :%5d\n", kp_seesaw, kd_seesaw);
    rt_kprintf("kp_round      :%5d kd_round      :%5d\n", kp_round, kd_round);
    rt_kprintf("kp_slow       :%5d kd_slow       :%5d\n", kp_slow, kd_slow);
    rt_kprintf("kp_back       :%5d kd_back       :%5d\n", kp_back, kd_back);
}
MSH_CMD_EXPORT(show_parameter,show parameters);
FINSH_FUNCTION_EXPORT(show_parameter,show parameter);
