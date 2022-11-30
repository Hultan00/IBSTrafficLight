#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "stm32l4xx_it.h"
#include "stm32l4xx_hal_conf.h"
#include "interactions.h"

bool is_car1(){
    if(HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin) == GPIO_PIN_RESET){
        return true;
    }
    return false;
}

bool is_car2(){
    if(HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == GPIO_PIN_RESET){
        return true;
    }
    return false;
}

bool is_car3(){
    if(HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin) == GPIO_PIN_RESET){
        return true;
    }
    return false;
}

bool is_car4(){
    if(HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin) == GPIO_PIN_RESET){
        return true;
    }
    return false;
}

bool is_pl1(){
    if(HAL_GPIO_ReadPin(PL1_Switch_GPIO_Port, PL1_Switch_Pin) == GPIO_PIN_RESET){
        return true;
    }
    return false;
}

bool is_pl2(){
    if(HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == GPIO_PIN_RESET){
        return true;
    }
    return false;
}

bool is_jcenter(){
    if(HAL_GPIO_ReadPin(button3_center_GPIO_Port, button3_center_Pin) == GPIO_PIN_RESET){
        return true;
    }
    return false;
}

bool is_jright(){
    if(HAL_GPIO_ReadPin(button3_D_GPIO_Port, button3_D_Pin) == GPIO_PIN_RESET){
        return true;
    }
    return false;
}

bool is_jdown(){
    if(HAL_GPIO_ReadPin(button3_C_GPIO_Port, button3_C_Pin) == GPIO_PIN_RESET){
        return true;
    }
    return false;
}

bool is_jup(){
    if(HAL_GPIO_ReadPin(button3_B_GPIO_Port, button3_B_Pin) == GPIO_PIN_RESET){
        return true;
    }
    return false;
}

bool is_jleft(){
    if(HAL_GPIO_ReadPin(button3_A_GPIO_Port, button3_A_Pin) == GPIO_PIN_RESET){
        return true;
    }
    return false;
}