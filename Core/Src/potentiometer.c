#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "stm32l4xx_it.h"
#include "stm32l4xx_hal_conf.h"
#include "adc.h"
#include "potentiometer.h"

uint8_t getPotiPercent(){
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 1000);
    uint16_t readValue = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    float calc = (readValue/4096.0)*101.0;
    uint8_t i = calc;
    return i;
}

uint16_t getPotiValue(){
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 1000);
    uint16_t readValue = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    return readValue;
}