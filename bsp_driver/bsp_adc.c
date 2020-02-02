/*
 * @Author: jiang chenhui
 * @Date: 2020-01-30 19:13:06
 * @LastEditTime : 2020-02-02 21:22:16
 * @LastEditors  : Please set LastEditors
 * @Description: drivers for gray scale sensor
 * @FilePath: \stm32f407-rushb\bsp_driver\adc\bsp_adc.c
 */

#include "bsp_adc.h"

rt_adc_device_t adc_dev1;  //device control handler
rt_adc_device_t adc_dev2;  //device control handler
rt_uint32_t adc_value[14]; //adc value array

rt_uint32_t index_map[14] = {6, 7, 8, 9, 0, 1, 2, 3, 10, 11, 4, 12, 13};

/**
 * @description: gray scale sensor initialize
 * @param void 
 * @return: status
 */
rt_err_t adc_init(void)
{
    rt_err_t ret = RT_NULL;

    adc_dev1 = (rt_adc_device_t)rt_device_find(ADC_DEV1_NAME);
    adc_dev2 = (rt_adc_device_t)rt_device_find(ADC_DEV2_NAME);

    if (adc_dev1 == RT_NULL || adc_dev2 == RT_NULL)
    {
        rt_kprintf("cant find gray scale sensor!\n");
        return RT_ERROR;
    }

    ret = adc_start();
    if (ret != RT_NULL)
    {
        return RT_EOK;
    }
    else
    {
        return RT_ERROR;
    }
}
//INIT_BOARD_EXPORT(adc_init);

/**
 * @description: read the data of gray scale
 * @param uint16_t pointer 
 * @return: none
 */
static void adc_read(void)
{
    while (1)
    {
        for (int i = 0; i < 12; i++)
        {
            /* enable device */
            rt_adc_enable(adc_dev1, 4 + i);

            /* read data */
            adc_value[index_map[i]] = rt_adc_read(adc_dev1, 4 + i);

            /* close device */
            rt_adc_disable(adc_dev1, 4 + i);
        }

        /* enable device */
        rt_adc_enable(adc_dev2, 5);

        /* read data */
        adc_value[index_map[12]] = rt_adc_read(adc_dev2, 5);

        /* close device */
        rt_adc_disable(adc_dev2, 5);

        /* enable device */
        rt_adc_enable(adc_dev2, 15);

        /* read data */
        adc_value[index_map[13]] = rt_adc_read(adc_dev2, 15);

        /* close device */
        rt_adc_disable(adc_dev2, 15);

        rt_thread_mdelay(50);
    }
}

/**
 * @description: start thread of data transfer
 * @param void
 * @return: status
 */
rt_err_t adc_start(void)
{
    /* create thread*/
    rt_thread_t tid1 = rt_thread_create("adc read", adc_read, RT_NULL, 512, 1, 10);

    if (tid1 != RT_NULL)
    {
        /* start up thread */
        rt_thread_startup(tid1);
        return RT_EOK;
    }
    else
    {
        return RT_ERROR;
    }
}

/**
 * @description: return adc value 
 * @param array pointer 
 * @return: status
 */
rt_err_t get_adc_value(rt_uint16_t *array)
{
    rt_memcpy(array, adc_value, 14);
    return RT_EOK;
}

/**
 * @description: Finsh test command 
 * @param none
 * @return: none
 */
static void gray_scale_sensor_test(void)
{
    rt_uint16_t adc_value[14];

    get_adc_value(adc_value);

    rt_kprintf("%d %d %d %d %d %d %d %d %d %d %d %d\n", adc_value[0], adc_value[1], adc_value[2], adc_value[3], adc_value[4], adc_value[5], adc_value[6], adc_value[7], adc_value[8], adc_value[9], adc_value[10], adc_value[11], adc_value[12], adc_value[13]);
}

MSH_CMD_EXPORT(gray_scale_sensor_test, gray scale sensor test);
FINSH_FUNCTION_EXPORT(gray_scale_sensor_test, gray scale sensor test);