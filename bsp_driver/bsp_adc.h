/*
 * @Author: jiang chenhui
 * @Date: 2020-01-30 19:13:06
 * @LastEditTime : 2020-02-02 21:39:03
 * @LastEditors  : Please set LastEditors
 * @Description: drivers for gray scale sensor
 * @FilePath: \stm32f407-rushb\bsp_driver\adc\bsp_adc.h
 */
#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include <car.h>

#define ADC_DEV1_NAME "adc1"   /* adc device1 name */
#define ADC_DEV2_NAME "adc3"   /* adc device2 name */
#define CONVERT_BITS (1 << 12) /* convert   bits   */

/**
 * @description: gray scale sensor initialize
 * @param void 
 * @return: status
 */
rt_err_t adc_init(void);

/**
 * @description: read the data of gray scale
 * @param uint16_t none 
 * @return: none
 */
static void adc_read(void);

/**
 * @description: start thread of data transfer
 * @param void
 * @return: status
 */
rt_err_t adc_start(void);

/**
 * @description: return adc value 
 * @param array pointer 
 * @return: status
 */
rt_err_t get_adc_value(rt_uint16_t *array);

#endif