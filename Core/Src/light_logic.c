#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "stm32l4xx_it.h"
#include "stm32l4xx_hal_conf.h"
#include "shift_register.h"
#include "spi.h"
#include "light_logic.h"

uint32_t PL1_Green(uint32_t bits, bool activated){
    if(activated){
        bits = SR_bitadj(bits, LED1516, LED1516);
    }else{
        bits = SR_bitadj(bits, 0, LED1516);
    }
    return bits;
}

uint32_t PL1_Red(uint32_t bits, bool activated){
    if(activated){
        bits = SR_bitadj(bits, LED1314, LED1314);
    }else{
        bits = SR_bitadj(bits, 0, LED1314);
    }
    return bits;
}

uint32_t PL1_Blue(uint32_t bits, bool activated){
    if(activated){
        bits = SR_bitadj(bits, LED1718, LED1718);
    }else{
        bits = SR_bitadj(bits, 0, LED1718);
    }
    return bits;
}

uint32_t PL1_Blue_Toggle(uint32_t bits){
    if((bits&LED1718) == 0){
        bits = SR_bitadj(bits, LED1718, LED1718);
    }else{
        bits = SR_bitadj(bits, 0, LED1718);
    }
    return bits;
}

uint32_t PL2_Green(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED2122, LED2122);
    }else{
        bits = SR_bitadj(bits, 0, LED2122);
    }
    return bits;
}

uint32_t PL2_Red(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED1920, LED1920);
    }else{
        bits = SR_bitadj(bits, 0, LED1920);
    }
    return bits;
}

uint32_t PL2_Blue(uint32_t bits, bool activated){
    if(activated){
        bits = SR_bitadj(bits, LED2324, LED2324);
    }else{
        bits = SR_bitadj(bits, 0, LED2324);
    }
    return bits;
}

uint32_t PL2_Blue_Toggle(uint32_t bits){
    if((bits&LED2324) == 0){
        bits = SR_bitadj(bits, LED2324, LED2324);
    }else{
        bits = SR_bitadj(bits, 0, LED2324);
    }
    return bits;
}

uint32_t TL1_Red(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED1, LED1);
    }else{
        bits = SR_bitadj(bits, 0, LED1);
    }
    return bits;
}

uint32_t TL1_Yellow(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED2, LED2);
    }else{
        bits = SR_bitadj(bits, 0, LED2);
    }
    return bits;
}

uint32_t TL1_Green(uint32_t bits,bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED3, LED3);
    }else{
        bits = SR_bitadj(bits, 0, LED3);
    }
    return bits;
}

uint32_t TL4_Red(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED10, LED10);
    }else{
        bits = SR_bitadj(bits, 0, LED10);
    }
    return bits;
}

uint32_t TL4_Yellow(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED11, LED11);
    }else{
        bits = SR_bitadj(bits, 0, LED11);
    }
    return bits;
}

uint32_t TL4_Green(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED12, LED12);
    }else{
        bits = SR_bitadj(bits, 0, LED12);
    }
    return bits;
}

uint32_t TL2_Red(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED4, LED4);
    }else{
        bits = SR_bitadj(bits, 0, LED4);
    }
    return bits;
}

uint32_t TL2_Yellow(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED5, LED5);
    }else{
        bits = SR_bitadj(bits, 0, LED5);
    }
    return bits;
}

uint32_t TL2_Green(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED6, LED6);
    }else{
        bits = SR_bitadj(bits, 0, LED6);
    }
    return bits;
}

uint32_t TL3_Red(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED7, LED7);
    }else{
        bits = SR_bitadj(bits, 0, LED7);
    }
    return bits;
}

uint32_t TL3_Yellow(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED8, LED8);
    }else{
        bits = SR_bitadj(bits, 0, LED8);
    }
    return bits;
}

uint32_t TL3_Green(uint32_t bits, bool activated){ 
    if(activated){
        bits = SR_bitadj(bits, LED9, LED9);
    }else{
        bits = SR_bitadj(bits, 0, LED9);
    }
    return bits;
}

uint32_t TL1_R2G(uint32_t bits){
    bits = TL1_Green(bits, false);
    bits = TL1_Red(bits, true);
    bits = TL1_Yellow(bits, false);

    HAL_Delay(1000);

    bits = TL1_Green(bits, false);
    bits = TL1_Red(bits, true);
    bits = TL1_Yellow(bits, true);

    HAL_Delay(1000);

    bits = TL1_Green(bits, true);
    bits = TL1_Red(bits, false);
    bits = TL1_Yellow(bits, false);
    return bits;
}

uint32_t TL1_G2R(uint32_t bits){
    bits = TL1_Green(bits, true);
    bits = TL1_Red(bits, false);
    bits = TL1_Yellow(bits, false);

    HAL_Delay(1000);

    bits = TL1_Green(bits, false);
    bits = TL1_Red(bits, false);
    bits = TL1_Yellow(bits, true);

    HAL_Delay(1000);

    bits = TL1_Green(bits, false);
    bits = TL1_Red(bits, true);
    bits = TL1_Yellow(bits, false);
    return bits;
}

uint32_t TL4_R2G(uint32_t bits){
    bits = TL2_Green(bits, false);
    bits = TL2_Red(bits, true);
    bits = TL2_Yellow(bits, false);

    HAL_Delay(1000);

    bits = TL2_Green(bits, false);
    bits = TL2_Red(bits, true);
    bits = TL2_Yellow(bits, true);

    HAL_Delay(1000);

    bits = TL2_Green(bits, true);
    bits = TL2_Red(bits, false);
    bits = TL2_Yellow(bits, false);
    return bits;
}

uint32_t TL4_G2R(uint32_t bits){
    bits = TL2_Green(bits, true);
    bits = TL2_Red(bits, false);
    bits = TL2_Yellow(bits, false);

    HAL_Delay(1000);

    bits = TL2_Green(bits, false);
    bits = TL2_Red(bits, false);
    bits = TL2_Yellow(bits, true);

    HAL_Delay(1000);

    bits = TL2_Green(bits, false);
    bits = TL2_Red(bits, true);
    bits = TL2_Yellow(bits, false);
    return bits;
}

uint32_t TL2_R2G(uint32_t bits){
    bits = TL3_Green(bits, false);
    bits = TL3_Red(bits, true);
    bits = TL3_Yellow(bits, false);

    HAL_Delay(1000);

    bits = TL3_Green(bits, false);
    bits = TL3_Red(bits, true);
    bits = TL3_Yellow(bits, true);

    HAL_Delay(1000);

    bits = TL3_Green(bits, true);
    bits = TL3_Red(bits, false);
    bits = TL3_Yellow(bits, false);
    return bits;
}

uint32_t TL2_G2R(uint32_t bits){
    bits = TL3_Green(bits, true);
    bits = TL3_Red(bits, false);
    bits = TL3_Yellow(bits, false);

    HAL_Delay(1000);

    bits = TL3_Green(bits, false);
    bits = TL3_Red(bits, false);
    bits = TL3_Yellow(bits, true);

    HAL_Delay(1000);

    bits = TL3_Green(bits, false);
    bits = TL3_Red(bits, true);
    bits = TL3_Yellow(bits, false);
    return bits;
}

uint32_t TL3_R2G(uint32_t bits){
    bits = TL4_Green(bits, false);
    bits = TL4_Red(bits, true);
    bits = TL4_Yellow(bits, false);

    HAL_Delay(1000);

    bits = TL4_Green(bits, false);
    bits = TL4_Red(bits, true);
    bits = TL4_Yellow(bits, true);

    HAL_Delay(1000);

    bits = TL4_Green(bits, true);
    bits = TL4_Red(bits, false);
    bits = TL4_Yellow(bits, false);
    return bits;
}

uint32_t TL3_G2R(uint32_t bits){
    bits = TL4_Green(bits, true);
    bits = TL4_Red(bits, false);
    bits = TL4_Yellow(bits, false);

    HAL_Delay(1000);

    bits = TL4_Green(bits, false);
    bits = TL4_Red(bits, false);
    bits = TL4_Yellow(bits, true);

    HAL_Delay(1000);

    bits = TL4_Green(bits, false);
    bits = TL4_Red(bits, true);
    bits = TL4_Yellow(bits, false);
    return bits;
}

uint32_t Init_Task1(uint32_t bits){
    bits = SR_bitset(0);

    bits = TL2_Green(bits, true);

    bits = TL4_Green(bits, true);

    bits = PL2_Red(bits, true);

    return bits;
}