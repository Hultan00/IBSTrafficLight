#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
#define pedestrianDelay 5 //Pedestrian wait after press duration
#define walkingDelay 10 //Pedestrian green duration
#define orangeDelay 1 // TrafficLight Orange/Yellow state duration
#define greenDelay 7 // trafficlight direction change when no active cars duration
#define redDelayMax 7 // trafficlight direction change when atleast 1 car from both directions are active duation

typedef enum{   
    PLRed,
    PLGreen,
    PLBlue
} crosswalk;

typedef enum{   
    TLRed,
    TLGreen
} TLcrossing;

typedef enum{   
    G1,
    G2
} crossingSwitch;

struct crossing
{
    char crossingName[4];
    TLcrossing light;
};

struct crossing C1, C2, C3, C4;

static crosswalk CW1, CW2;

static crossingSwitch NCWaitingState;

uint8_t brightness = 0;

uint8_t PLBlueDelay = 0;

uint8_t PLGreenDelay = 0;

uint8_t TLYellowDelay = 0;

uint8_t TLRedWaitTime = 0;

uint8_t NCWaitingDelay = 0;

uint16_t msTick = 1;

uint16_t TickFlash = 1;

uint8_t Tick = 1;

uint32_t bits = 0;

bool NoCarsWaiting = true;

bool BlueOn = false;

void Init_States(){
    C1.light = TLRed;
    C2.light = TLGreen;
    C3.light = TLRed;
    C4.light = TLGreen;
    strcpy(C1.crossingName, "TL1");
    strcpy(C2.crossingName, "TL2");
    strcpy(C3.crossingName, "TL3");
    strcpy(C4.crossingName, "TL4");
    CW1 = PLRed;
    CW2 = PLRed;
    NCWaitingState = G1;
}

TLcrossing IsIllegalGreenState(struct crossing state){
    if(strcmp(state.crossingName, "TL1") == 0){
        if((C2.light == TLRed) && (C4.light == TLRed) && (CW1 != PLGreen) && (NCWaitingState == G1)){
            if(state.light == TLRed){
                TLYellowDelay = orangeDelay;
                msTick = 1;
                HAL_Delay
            }
            return TLGreen;
        }else{
            if(state.light == TLGreen){
                TLYellowDelay = orangeDelay;
                msTick = 1;
            }
            return TLRed;
        }
    }else if(strcmp(state.crossingName, "TL3") == 0){
        if((C2.light == TLRed) && (C4.light == TLRed) && (CW2 != PLGreen) && (CW1 != PLGreen) && (NCWaitingState == G1)){
            if(state.light == TLRed){
                TLYellowDelay = orangeDelay;
                msTick = 1;
            }
            return TLGreen;
        }else{
            if(state.light == TLGreen){
                TLYellowDelay = orangeDelay;
                msTick = 1;
            }
            return TLRed;
        }
    }else if(strcmp(state.crossingName, "TL2") == 0){
        if((C1.light == TLRed) && (C3.light == TLRed) && (CW2 != PLGreen) && (NCWaitingState == G2)){
            if(state.light == TLRed){
                TLYellowDelay = orangeDelay;
                msTick = 1;
            }
            return TLGreen;
        }else{
            if(state.light == TLGreen){
                TLYellowDelay = orangeDelay;
                msTick = 1;
            }
            return TLRed;
        }
    }else if(strcmp(state.crossingName, "TL4") == 0){
        if((C1.light == TLRed) && (C3.light == TLRed) && (CW1 != PLGreen) && (CW2 != PLGreen) && (NCWaitingState == G2)){
            if(state.light == TLRed){
                TLYellowDelay = orangeDelay;
                msTick = 1;
            }
            return TLGreen;
        }else{
            if(state.light == TLGreen){
                TLYellowDelay = orangeDelay;
                msTick = 1;
            }
            return TLRed;
        }
    }
}

void checkAndChangeTL(){
    C3.light = IsIllegalGreenState(C3);
    C1.light = IsIllegalGreenState(C1);
    C2.light = IsIllegalGreenState(C2);
    C4.light = IsIllegalGreenState(C4);
}

void traffic_lights(){
    HAL_TIM_Base_Start_IT(&htim16);

    Init_States();

    Show_All_DelayBars(true, 0);

    bits = Init_Task2(bits);
    
    while(1){

        brightness = getPotiPercent();

        NoCarsWaiting = true;

       if(is_car3() || is_car1()){
            NoCarsWaiting = false;
            if(!(is_car4() || is_car2())){
                NCWaitingState = G1;
                checkAndChangeTL();
                TLRedWaitTime = 0;
            }
       }

       if(is_car4() || is_car2()){
            NoCarsWaiting = false;
            if(!(is_car1() || is_car3())){
                NCWaitingState = G2;
                checkAndChangeTL();
                TLRedWaitTime = 0;
            }
       }

       if((is_car4() || is_car2()) && (is_car1() || is_car3())){
            checkAndChangeTL();
            if(TLRedWaitTime == 0){
                TLRedWaitTime = redDelayMax;
            }
       }

       if(is_pl1() && (CW2 == PLRed)){
            CW1 = PLBlue;
            PLBlueDelay = pedestrianDelay;
        }

        if(is_pl2() && (CW1 == PLRed)){
            CW2 = PLBlue;
            PLBlueDelay = pedestrianDelay;
        }

       if(NoCarsWaiting){
            checkAndChangeTL();
            if(NCWaitingDelay == 0){
                NCWaitingDelay = greenDelay;
            }
            HAL_GPIO_WritePin(USR_LED2_GPIO_Port, USR_LED2_Pin, GPIO_PIN_SET);
       }else{
            HAL_GPIO_WritePin(USR_LED2_GPIO_Port, USR_LED2_Pin, GPIO_PIN_RESET);
            NCWaitingDelay = 0;
            Show_G1Bar(true, 0);
            Show_G2Bar(true, 0);
       }

        switch (C1.light){
            case TLGreen:
                if((TLYellowDelay > 0) && (!TL1_isGreen(bits))){
                    bits = TL1_Green(bits, false);
                    bits = TL1_Red(bits, true);
                    bits = TL1_Yellow(bits, true);
                }else{
                    bits = TL1_Green(bits, true);
                    bits = TL1_Red(bits, false);
                    bits = TL1_Yellow(bits, false);
                }
                break;
            case TLRed:
                if((TLYellowDelay > 0) && (!TL1_isRed(bits))){
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

        switch (C2.light){
            case TLGreen:
                if((TLYellowDelay > 0) && (!TL2_isGreen(bits))){
                    bits = TL2_Green(bits, false);
                    bits = TL2_Red(bits, true);
                    bits = TL2_Yellow(bits, true);
                }else{
                    bits = TL2_Green(bits, true);
                    bits = TL2_Red(bits, false);
                    bits = TL2_Yellow(bits, false);
                }
                break;
            case TLRed:
                if((TLYellowDelay > 0) && (!TL2_isRed(bits))){
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

        switch (C3.light){
            case TLGreen:
                if((TLYellowDelay > 0) && (!TL3_isGreen(bits))){
                    bits = TL3_Green(bits, false);
                    bits = TL3_Red(bits, true);
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

        switch (C4.light){
            case TLGreen:
                if((TLYellowDelay > 0) && (!TL4_isGreen(bits))){
                    bits = TL4_Green(bits, false);
                    bits = TL4_Red(bits, true);
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
                if((C1.light != TLRed) || (C3.light != TLRed) || (C4.light != TLRed)){
                    checkAndChangeTL();
                    TLYellowDelay = orangeDelay;
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
                    if(BlueOn){
                        bits = PL1_Blue(bits, true);
                    }else{
                        bits = PL1_Blue(bits, false);
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
                if((C4.light != TLRed) || (C2.light != TLRed) || (C3.light != TLRed)){
                    checkAndChangeTL();
                    TLYellowDelay = orangeDelay;
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
                    if(BlueOn){
                        bits = PL2_Blue(bits, true);
                    }else{
                        bits = PL2_Blue(bits, false);
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

            if(NCWaitingDelay > 0){
                if(TLYellowDelay == 0){
                    NCWaitingDelay--;
                }
                if(NCWaitingState == G1){
                    Show_G1Bar(true, (100 - ((NCWaitingDelay*100)/greenDelay)));
                    Show_G2Bar(true, 0);
                }else{
                    Show_G2Bar(true, (100 - ((NCWaitingDelay*100)/greenDelay)));
                    Show_G1Bar(true, 0);
                }
                if(NCWaitingDelay == 0){
                    if(NCWaitingState == G1){
                        NCWaitingState = G2;
                    }else{
                        NCWaitingState = G1;
                    }
                }
            }

            if(TLRedWaitTime > 0){
                if(TLYellowDelay == 0){
                    TLRedWaitTime--;
                }
                if(NCWaitingState == G1){
                    Show_R2Bar(true, (100 - ((TLRedWaitTime*100)/redDelayMax)));
                    Show_R1Bar(true, 0);
                }else{
                    Show_R1Bar(true, (100 - ((TLRedWaitTime*100)/redDelayMax)));
                    Show_R2Bar(true, 0);
                }
                if(TLRedWaitTime == 0){
                    if(NCWaitingState == G1){
                        NCWaitingState = G2;
                    }else{
                        NCWaitingState = G1;
                    }
                }
            }else{
                Show_R1Bar(true, 0);
                Show_R2Bar(true, 0);
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

        if(TickFlash >= (toggleFreq*10)){ //10 ms
            if(BlueOn){
                BlueOn = false;
            }else{
                BlueOn = true;
            }
            TickFlash = 1;
        }else{
            TickFlash++;
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