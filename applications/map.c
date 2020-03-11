/*
 * @Author: jiang chenhui
 * @Date: 2020-01-31 20:42:24
 * @LastEditTime: 2020-03-08 12:13:09
 * @LastEditors: Please set LastEditors
 * @Description: map information
 * @FilePath: \stm32f407-rushb\applications\map.c
 */
#include "map.h"

/* global parameters of line model */
LINE_POS line;
LINE_POS back_line;

/* global parameters of car model */
Car car;

/* mode name & index map */
char track_mode[MODE_NUM][NAME_MAX] = {
    "none",
    "center",
    "stop",
    "leftt",
    "rightt",
    "centerleft",
    "upbridge",
    "bridge",
    "wave",
    "seesaw",
    "round",
    "slow",
    "back"
};

int kd[MODE_NUM];
int kp[MODE_NUM];

/**
 * @description: save pid parameters to on-chip flash
 * @param none 
 * @return: none
 */
void save_parameters(void)
{
    char value_buf[5];
    char name_buf[15];

    for(int i=0;i<MODE_NUM;i++){
        rt_sprintf(value_buf,"%d",kp[i]);
        rt_sprintf(name_buf,"kp_%s",track_mode[i]);
        ef_set_env(name_buf,value_buf);
        rt_memset(value_buf,0,5);
        rt_memset(name_buf,0,15);
    }

    for(int i=0;i<MODE_NUM;i++){
        rt_sprintf(value_buf,"%d",kd[i]);
        rt_sprintf(name_buf,"kd_%s",track_mode[i]);
        ef_set_env(name_buf,value_buf);
        rt_memset(value_buf,0,5);
        rt_memset(name_buf,0,15);
    }

}
MSH_CMD_EXPORT(save_parameters,save para);


/**
 * @description: read pid parameter from flash
 * @param none
 * @return: none
 */
void load_parameter(void)
{
    char value_buf[5];
    char name_buf[15];

    for(int i=0;i<MODE_NUM;i++){
        rt_sprintf(name_buf,"kd_%s",track_mode[i]);
        ef_get_env_blob(name_buf, value_buf, sizeof(value_buf) , NULL);
        kd[i] = atoi(value_buf);
        rt_memset(value_buf,0,5);
    }

    for(int i=0;i<MODE_NUM;i++){
        rt_sprintf(name_buf,"kp_%s",track_mode[i]);
        ef_get_env_blob(name_buf, value_buf, sizeof(value_buf) , NULL);
        kp[i] = atoi(value_buf);
        rt_memset(value_buf,0,5);
    }
}

MSH_CMD_EXPORT(load_parameter,load para);

// /**
//  * @description: float abs function
//  * @param float  
//  * @return: float
//  */
// float fabs(float num)
// {
//     if (num >= 0)
//     {
//         return num;
//     }
//     else
//     {
//         return (-num);
//     }
// }

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
    if(car.trace = STOP){
        car_stop();
         goto exti;
    }else{
        pid_out = (int)(kp[car.trace]*Ek0 + kd[car.trace]*(Ek0-Ek1));
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
    pid_out = (int)(kp[BACK] * Ek0 + kd[BACK] * (Ek0 - Ek1));
    
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
    for(int i=0;i<MODE_NUM;i++){
        rt_kprintf("kp_%-15s:%5d kd_%-15s:%5d\n",track_mode[i],kp[i],track_mode[i],kd[i]);
    }
    //save_parameters();
}
MSH_CMD_EXPORT(show_parameter,show parameters);

int set(int argc,char ** argv){
    if(argc != 4){
        return 0;
    }

    int index = atoi(argv[1]);
    int kp_value = atoi(argv[2]);
    int kd_value = atoi(argv[3]);
    
    kp[index] = kp_value;
    kd[index] = kd_value;
}
MSH_CMD_EXPORT(set,set parameters);


