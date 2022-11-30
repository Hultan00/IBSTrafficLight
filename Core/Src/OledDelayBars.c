#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "stm32l4xx_it.h"
#include "stm32l4xx_hal_conf.h"
#include "spi.h"
#include "ssd1306.h"
#include "OledDelayBars.h"

void Show_P1Bar(bool state, uint8_t percent){
    if(state){
        ssd1306_DrawRectangle(2,10,12,50,White);
        ssd1306_SetCursor(2,53);
        ssd1306_WriteString("P1", Font_7x10, White);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(2+1,50-y,12-1,50-y,Black);
        }
        float fpercent = percent;
        float calc = ((1.0/40.0)*100.0);
        for(float y = 1.0;(calc < fpercent);y++){
            calc = ((y/40.0)*100.0);
            ssd1306_Line(2+1,50-y,12-1,50-y,White);
        }
        ssd1306_UpdateScreen();
    }else{
        ssd1306_DrawRectangle(2,10,12,50,Black);
        ssd1306_SetCursor(2,53);
        ssd1306_WriteString("P1", Font_7x10, Black);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(2+1,50-y,12-1,50-y,Black);
        }
        ssd1306_UpdateScreen();
    }
}

void Show_W1Bar(bool state, uint8_t percent){
    if(state){
        ssd1306_DrawRectangle(18,10,28,50,White);
        ssd1306_SetCursor(18,53);
        ssd1306_WriteString("W1", Font_7x10, White);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(18+1,50-y,28-1,50-y,Black);
        }
        float fpercent = percent;
        float calc = ((1.0/40.0)*100.0);
        for(float y = 1.0;(calc < fpercent);y++){
            calc = ((y/40.0)*100.0);
            ssd1306_Line(18+1,50-y,28-1,50-y,White);
        }
        ssd1306_UpdateScreen();
    }else{
        ssd1306_DrawRectangle(18,10,28,50,Black);
        ssd1306_SetCursor(18,53);
        ssd1306_WriteString("W1", Font_7x10, Black);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(18+1,50-y,28-1,50-y,Black);
        }
        ssd1306_UpdateScreen();
    }
}

void Show_P2Bar(bool state, uint8_t percent){
    if(state){
        ssd1306_DrawRectangle(34,10,44,50,White);
        ssd1306_SetCursor(34,53);
        ssd1306_WriteString("P2", Font_7x10, White);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(34+1,50-y,44-1,50-y,Black);
        }
        float fpercent = percent;
        float calc = ((1.0/40.0)*100.0);
        for(float y = 1.0;(calc < fpercent);y++){
            calc = ((y/40.0)*100.0);
            ssd1306_Line(34+1,50-y,44-1,50-y,White);
        }
        ssd1306_UpdateScreen();
    }else{
        ssd1306_DrawRectangle(34,10,44,50,Black);
        ssd1306_SetCursor(34,53);
        ssd1306_WriteString("P2", Font_7x10, Black);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(34+1,50-y,44-1,50-y,Black);
        }
        ssd1306_UpdateScreen();
    }
}

void Show_W2Bar(bool state, uint8_t percent){
    if(state){
        ssd1306_DrawRectangle(50,10,60,50,White);
        ssd1306_SetCursor(50,53);
        ssd1306_WriteString("W2", Font_7x10, White);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(50+1,50-y,60-1,50-y,Black);
        }
        float fpercent = percent;
        float calc = ((1.0/40.0)*100.0);
        for(float y = 1.0;(calc < fpercent);y++){
            calc = ((y/40.0)*100.0);
            ssd1306_Line(50+1,50-y,60-1,50-y,White);
        }
        ssd1306_UpdateScreen();
    }else{
        ssd1306_DrawRectangle(50,10,60,50,Black);
        ssd1306_SetCursor(50,53);
        ssd1306_WriteString("W2", Font_7x10, Black);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(50+1,50-y,60-1,50-y,Black);
        }
        ssd1306_UpdateScreen();
    }
}

void Show_G1Bar(bool state, uint8_t percent){
    if(state){
        ssd1306_DrawRectangle(66,10,76,50,White);
        ssd1306_SetCursor(66,53);
        ssd1306_WriteString("G1", Font_7x10, White);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(66+1,50-y,76-1,50-y,Black);
        }
        float fpercent = percent;
        float calc = ((1.0/40.0)*100.0);
        for(float y = 1.0;(calc < fpercent);y++){
            calc = ((y/40.0)*100.0);
            ssd1306_Line(66+1,50-y,76-1,50-y,White);
        }
        ssd1306_UpdateScreen();
    }else{
        ssd1306_DrawRectangle(66,10,76,50,Black);
        ssd1306_SetCursor(66,53);
        ssd1306_WriteString("G1", Font_7x10, Black);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(66+1,50-y,76-1,50-y,Black);
        }
        ssd1306_UpdateScreen();
    }
}

void Show_R1Bar(bool state, uint8_t percent){
    if(state){
        ssd1306_DrawRectangle(82,10,92,50,White);
        ssd1306_SetCursor(82,53);
        ssd1306_WriteString("R1", Font_7x10, White);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(82+1,50-y,92-1,50-y,Black);
        }
        float fpercent = percent;
        float calc = ((1.0/40.0)*100.0);
        for(float y = 1.0;(calc < fpercent);y++){
            calc = ((y/40.0)*100.0);
            ssd1306_Line(82+1,50-y,92-1,50-y,White);
        }
        ssd1306_UpdateScreen();
    }else{
        ssd1306_DrawRectangle(82,10,92,50,Black);
        ssd1306_SetCursor(82,53);
        ssd1306_WriteString("R1", Font_7x10, Black);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(82+1,50-y,92-1,50-y,Black);
        }
        ssd1306_UpdateScreen();
    }
}

void Show_G2Bar(bool state, uint8_t percent){
    if(state){
        ssd1306_DrawRectangle(98,10,108,50,White);
        ssd1306_SetCursor(98,53);
        ssd1306_WriteString("G2", Font_7x10, White);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(98+1,50-y,108-1,50-y,Black);
        }
        float fpercent = percent;
        float calc = ((1.0/40.0)*100.0);
        for(float y = 1.0;(calc < fpercent);y++){
            calc = ((y/40.0)*100.0);
            ssd1306_Line(98+1,50-y,108-1,50-y,White);
        }
        ssd1306_UpdateScreen();
    }else{
        ssd1306_DrawRectangle(98,10,108,50,Black);
        ssd1306_SetCursor(98,53);
        ssd1306_WriteString("G2", Font_7x10, Black);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(98+1,50-y,108-1,50-y,Black);
        }
        ssd1306_UpdateScreen();
    }
}

void Show_R2Bar(bool state, uint8_t percent){
    if(state){
        ssd1306_DrawRectangle(114,10,124,50,White);
        ssd1306_SetCursor(114,53);
        ssd1306_WriteString("R2", Font_7x10, White);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(114+1,50-y,124-1,50-y,Black);
        }
        float fpercent = percent;
        float calc = ((1.0/40.0)*100.0);
        for(float y = 1.0;(calc < fpercent);y++){
            calc = ((y/40.0)*100.0);
            ssd1306_Line(114+1,50-y,124-1,50-y,White);
        }
        ssd1306_UpdateScreen();
    }else{
        ssd1306_DrawRectangle(114,10,124,50,Black);
        ssd1306_SetCursor(114,53);
        ssd1306_WriteString("R2", Font_7x10, Black);
        for(float y = 1.0;y < 40;y++){
            ssd1306_Line(114+1,50-y,124-1,50-y,Black);
        }
        ssd1306_UpdateScreen();
    }
}

void Show_All_DelayBars(bool state, uint8_t percent){
    if(state){
        Show_G1Bar(true, percent);
        Show_G2Bar(true, percent);
        Show_P1Bar(true, percent);
        Show_P2Bar(true, percent);
        Show_R1Bar(true, percent);
        Show_R2Bar(true, percent);
        Show_W1Bar(true, percent);
        Show_W2Bar(true, percent);
    }else{
        Show_G1Bar(false, 0);
        Show_G2Bar(false, 0);
        Show_P1Bar(false, 0);
        Show_P2Bar(false, 0);
        Show_R1Bar(false, 0);
        Show_R2Bar(false, 0);
        Show_W1Bar(false, 0);
        Show_W2Bar(false, 0);
    }
}