#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "stm32l4xx_it.h"
#include "stm32l4xx_hal_conf.h"
#include "spi.h"
#include "shift_register.h"


void STCP_ON(){
    HAL_Delay(1);
    HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
}

void STCP_OFF(){
    HAL_Delay(1);
    HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}

void STCP_Clock(){
    STCP_ON();
    STCP_OFF();
}

void MR_OFF(){
    HAL_Delay(1);
    HAL_GPIO_WritePin(Reset_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
}

void MR_ON(){
    HAL_Delay(1);
    HAL_GPIO_WritePin(Reset_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}


void EN_OFF(){
    HAL_Delay(1);
    HAL_GPIO_WritePin(Enable_595_GPIO_Port, Enable_595_Pin, GPIO_PIN_SET);
}

void EN_ON(){
    HAL_Delay(1);
    HAL_GPIO_WritePin(Enable_595_GPIO_Port, Enable_595_Pin, GPIO_PIN_RESET);
}

void EN_Toggle(){
    HAL_GPIO_TogglePin(Enable_595_GPIO_Port, Enable_595_Pin);
}


uint32_t SR_bitset(uint32_t bits){
    bits = bits<<8;

    STCP_OFF();

    HAL_SPI_Transmit(&hspi3, &bits, 4, 10);

    STCP_Clock();

    return bits>>8;
}

uint32_t SR_bitadj(uint32_t bits, uint32_t newbits, uint32_t bitmask){
    bits = bits<<8;
    uint32_t cpyBits = bits;
    newbits = newbits<<8;
    bitmask = bitmask<<8;
    bitmask = ~bitmask;

    bits = (bits & bitmask);

    bitmask = ~bitmask;

    bits = bits + (newbits & bitmask);

    if(bits == cpyBits){
        return bits>>8;
    }

    STCP_OFF();

    HAL_SPI_Transmit(&hspi3, &bits, 4, 1);

    STCP_Clock();

    return bits>>8;
}