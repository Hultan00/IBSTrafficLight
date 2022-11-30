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

#define togglefreq 10.0
#define pedestriandelay 5.0

typedef enum{   
    PLRed,
    PLGreen,
    PLBlue
} crosswalk;

typedef enum{   
    TLRed,
    TLYellow,
    TLGreen
} crossing;

static crossing C1, C2, C3, C4;

static crosswalk CW1, CW2;

uint8_t brightness = 0;

uint8_t PLBluedelay = 0;

uint8_t PLGreenDelay = 0;

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

    bits = Init_Task1(bits);
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

        if(is_pl2()){
            CW2 = PLBlue;
            PLBluedelay = togglefreq;
        }

        switch (CW2){
            case PLGreen:
                if(PLGreenDelay == 0){
                    bits = PL2_Green(bits, false);
                    bits = PL2_Red(bits, true);
                    bits = TL4_Green(bits, true);
                    bits = TL4_Red(bits, false);
                    bits = TL4_Yellow(bits, false);
                    CW2 = PLRed;
                }else if(PLGreenDelay == 1){
                    bits = PL2_Green(bits, false);
                    bits = PL2_Red(bits, true);
                    bits = TL4_Green(bits, false);
                    bits = TL4_Red(bits, false);
                    bits = TL4_Yellow(bits, true);
                }else{
                    bits = PL2_Green(bits, true);
                    bits = PL2_Red(bits, false);
                    bits = TL4_Green(bits, false);
                    bits = TL4_Red(bits, true);
                    bits = TL4_Yellow(bits, false);
                }
                break;
            case PLBlue:
                if(PLBluedelay == 0){
                    bits = PL2_Blue(bits, false);
                    CW2 = PLGreen;
                    PLGreenDelay = pedestriandelay;
                }else if(PLBluedelay == 1){
                    bits = TL4_Green(bits, false);
                    bits = TL4_Red(bits, false);
                    bits = TL4_Yellow(bits, true);
                }else{
                    bits = PL2_Blue(bits, true);
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
        if(msTick >= 10000){
            HAL_GPIO_TogglePin(USR_LED1_GPIO_Port, USR_LED1_Pin);
            if(PLBluedelay > 0){
                PLBluedelay--;
                Show_P2Bar(true, (1 - (PLBluedelay/togglefreq))*100.0);
            }else{
                if(PLGreenDelay > 0){
                    PLGreenDelay--;
                    Show_W2Bar(true, (1 - (PLGreenDelay/pedestriandelay))*100.0);
                }else{
                    Show_W2Bar(true, 0);
                }
                Show_P2Bar(true, 0);
            }
            msTick = 1;
        }else{
            msTick++;
        }

        if(Tick >= 100){
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