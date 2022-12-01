#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "stm32l4xx_it.h"
#include "stm32l4xx_hal_conf.h"
#include "shift_register.h"
#include "light_logic.h"
#include "Traffic_Light.h"
#include "tim.h"
#include "interactions.h"
#include "OledDelayBars.h"
#include "potentiometer.h"
#include "math.h"
#include "ssd1306.h"

//In Miliseconds
#define toggleFreq 200 //Pedestrian blue light toggle frequency

//In Seconds
#define pedestrianDelay 5 //Pedestrian on blue blink wait delay
#define walkingDelay 10 //Pedestrian on green walk delay
#define orangeDelay 1 // In Orange/Yellow state delay

typedef enum{   
    PLRed,
    PLGreen,
    PLBlue
} crosswalk;

typedef enum{   
    TLRed,
    TLGreen
} crossing;

static crossing C1, C2, C3, C4;

static crosswalk CW1, CW2;

uint8_t brightness = 0;

uint8_t PLBlueDelay = 0;

uint8_t PLGreenDelay = 0;

uint8_t TLYellowDelay = 0;

bool toggleBrightness = false;

bool toggleBlue = false;

uint16_t msTick = 1;

uint8_t Tick = 1;

uint32_t bits = 0;

void Init_States(){
    C1 = TLRed;
    C2 = TLGreen;
    C3 = TLRed;
    C4 = TLGreen;
    CW1 = PLRed;
    CW2 = PLRed;
}

void traffic_lights(){
    HAL_TIM_Base_Start_IT(&htim16);

    Init_States();

    Show_All_DelayBars(true, 0);

    bits = Init_Task2(bits);
    while(1){

        brightness = getPotiPercent();

        /* // Brightness OLED
        char strBri[20] = "Brightness ";
        char strBrValue[3] = "";
        itoa(brightness, strBrValue, 10);
        strcat(strBri, strBrValue);
        strcat(strBri, " ");
        ssd1306_SetCursor(2,0);
        ssd1306_WriteString(strBri, Font_7x10, White);
        ssd1306_UpdateScreen();
        */

       if(is_pl1() && (CW2 == PLRed)){
            CW1 = PLBlue;
            PLBlueDelay = pedestrianDelay;
        }

        if(is_pl2() && (CW1 == PLRed)){
            CW2 = PLBlue;
            PLBlueDelay = pedestrianDelay;
        }

        switch (C1){
            case TLGreen:
                if((TLYellowDelay > 0) && (!TL1_isGreen(bits))){
                    bits = TL1_Green(bits, false);
                    bits = TL1_Red(bits, false);
                    bits = TL1_Yellow(bits, true);
                }else{
                    bits = TL1_Green(bits, false);
                    bits = TL1_Red(bits, true);
                    bits = TL1_Yellow(bits, false);
                }
                break;
            case TLRed:
                if((TLYellowDelay > 0)  && (!TL1_isRed(bits))){
                    bits = TL1_Green(bits, false);
                    bits = TL1_Red(bits, false);
                    bits = TL1_Yellow(bits, true);
                }else{
                    bits = TL1_Green(bits, false);
                    bits = TL1_Red(bits, true);
                    bits = TL1_Yellow(bits, false);
                }
                break;
            default:
                break;
        }

        switch (C2){
            case TLGreen:
                if((TLYellowDelay > 0)  && (!TL2_isGreen(bits))){
                    bits = TL2_Green(bits, false);
                    bits = TL2_Red(bits, false);
                    bits = TL2_Yellow(bits, true);
                }else{
                    bits = TL2_Green(bits, true);
                    bits = TL2_Red(bits, false);
                    bits = TL2_Yellow(bits, false);
                }
                break;
            case TLRed:
                if((TLYellowDelay > 0)  && (!TL2_isRed(bits))){
                    bits = TL2_Green(bits, false);
                    bits = TL2_Red(bits, false);
                    bits = TL2_Yellow(bits, true);
                }else{
                    bits = TL2_Green(bits, false);
                    bits = TL2_Red(bits, true);
                    bits = TL2_Yellow(bits, false);
                }
                break;
            default:
                break;
        }

        switch (C3){
            case TLGreen:
                if((TLYellowDelay > 0)  && (!TL3_isGreen(bits))){
                    bits = TL3_Green(bits, false);
                    bits = TL3_Red(bits, false);
                    bits = TL3_Yellow(bits, true);
                }else{
                    bits = TL3_Green(bits, true);
                    bits = TL3_Red(bits, false);
                    bits = TL3_Yellow(bits, false);
                }
                break;
            case TLRed:
                if((TLYellowDelay > 0) && (!TL3_isRed(bits))){
                    bits = TL3_Green(bits, false);
                    bits = TL3_Red(bits, false);
                    bits = TL3_Yellow(bits, true);
                }else{
                    bits = TL3_Green(bits, false);
                    bits = TL3_Red(bits, true);
                    bits = TL3_Yellow(bits, false);
                }
                break;
            default:
                break;
        }

        switch (C4){
            case TLGreen:
                if((TLYellowDelay > 0) && (!TL4_isGreen(bits))){
                    bits = TL4_Green(bits, false);
                    bits = TL4_Red(bits, false);
                    bits = TL4_Yellow(bits, true);
                }else{
                    bits = TL4_Green(bits, true);
                    bits = TL4_Red(bits, false);
                    bits = TL4_Yellow(bits, false);
                }
                break;
            case TLRed:
                if((TLYellowDelay > 0)  && (!TL4_isRed(bits))){
                    bits = TL4_Green(bits, false);
                    bits = TL4_Red(bits, false);
                    bits = TL4_Yellow(bits, true);
                }else{
                    bits = TL4_Green(bits, false);
                    bits = TL4_Red(bits, true);
                    bits = TL4_Yellow(bits, false);
                }
                break;
            default:
                break;
        }

        switch (CW1){
            case PLGreen:
                if((C1 != TLRed) || (C3 != TLRed) || (C4 != TLRed)){
                    C1 = TLRed;
                    C3 = TLRed;
                    C4 = TLRed;
                    TLYellowDelay = orangeDelay+1;
                }else{
                    if(TLYellowDelay == 0){
                        if(PLGreenDelay > 0){
                            bits = PL1_Green(bits, true);
                            bits = PL1_Red(bits, false);
                        }else{
                            CW1 = PLRed;
                            bits = PL1_Green(bits, false);
                            bits = PL1_Red(bits, true);
                        }
                    }
                }
                break;
            case PLBlue:
                if(PLBlueDelay > 0){
                    if((msTick % (uint16_t)(toggleFreq*10)) == 0){
                        bits = PL1_Blue_Toggle(bits);
                    }
                }else{
                    CW1 = PLGreen;
                    PLGreenDelay = walkingDelay;
                    bits = PL1_Blue(bits, false);
                }
                break;
            case PLRed:
                bits = PL1_Red(bits,true);
                bits = PL1_Green(bits,false);
                break;
            default:
                break;
        }

        switch (CW2){
            case PLGreen:
                if((C4 != TLRed) || (C2 != TLRed) || (C3 != TLRed)){
                    C2 = TLRed;
                    C3 = TLRed;
                    C4 = TLRed;
                    TLYellowDelay = orangeDelay+1;
                }else{
                    if(TLYellowDelay == 0){
                        if(PLGreenDelay > 0){
                            bits = PL2_Green(bits, true);
                            bits = PL2_Red(bits, false);
                        }else{
                            CW2 = PLRed;
                            bits = PL2_Green(bits, false);
                            bits = PL2_Red(bits, true);
                        }
                    }
                }
                break;
            case PLBlue:
                if(PLBlueDelay > 0){
                    if((msTick % (uint16_t)(toggleFreq*10)) == 0){
                        bits = PL2_Blue_Toggle(bits);
                    }
                }else{
                    CW2 = PLGreen;
                    PLGreenDelay = walkingDelay;
                    bits = PL2_Blue(bits, false);
                }
                break;
            case PLRed:
                bits = PL2_Red(bits,true);
                bits = PL2_Green(bits,false);
                break;
            default:
                break;
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim == &htim16){
        if(msTick >= 10000){ //1 second

            HAL_GPIO_TogglePin(USR_LED1_GPIO_Port, USR_LED1_Pin);

            if(TLYellowDelay > 0){
                TLYellowDelay--;
            }

            if(PLBlueDelay > 0){
                PLBlueDelay--;
                if(CW1 == PLBlue){
                    Show_P1Bar(true, (100 - ((PLBlueDelay*100)/pedestrianDelay)));
                }
                if(CW2 == PLBlue){
                    Show_P2Bar(true, (100 - ((PLBlueDelay*100)/pedestrianDelay)));
                }
            }else{
                if(PLGreenDelay > 0){
                    PLGreenDelay--;
                    if(CW1 == PLGreen){
                        Show_W1Bar(true, (100 - ((PLGreenDelay*100)/walkingDelay)));
                    }
                    if(CW2 == PLGreen){
                        Show_W2Bar(true, (100 - ((PLGreenDelay*100)/walkingDelay)));
                    }
                }else{
                    Show_W1Bar(true, 0);
                    Show_W2Bar(true, 0);
                }
                Show_P1Bar(true, 0);
                Show_P2Bar(true, 0);
            }

            msTick = 1;
        }else{
            msTick++;
        }

        if(Tick >= 100){ //10 ms
            Tick = 1;
        }else{
            Tick++;
        }

        if(Tick > brightness){
            HAL_GPIO_WritePin(Enable_595_GPIO_Port, Enable_595_Pin, GPIO_PIN_SET);
        }else{
            HAL_GPIO_WritePin(Enable_595_GPIO_Port, Enable_595_Pin, GPIO_PIN_RESET);
        }

    }
}