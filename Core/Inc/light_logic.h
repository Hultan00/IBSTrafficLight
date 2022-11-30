#ifndef LIGHTLOGIC_H_
#define LIGHTLOGIC_H_

#include <stdbool.h>

static const uint32_t LED7 = 1;
static const uint32_t LED8 = 2;
static const uint32_t LED9 = 4;
static const uint32_t LED10 = 8;
static const uint32_t LED11 = 16;
static const uint32_t LED12 = 32;
static const uint32_t LED4 = 256;
static const uint32_t LED5 = 512;
static const uint32_t LED6 = 1024;
static const uint32_t LED1920 = 2048;
static const uint32_t LED2122 = 4096;
static const uint32_t LED2324 = 8192;
static const uint32_t LED1 = 65536;
static const uint32_t LED2 = 131072;
static const uint32_t LED3 = 262144;
static const uint32_t LED1314 = 524288;
static const uint32_t LED1516 = 1048576;
static const uint32_t LED1718 = 2097152;

uint32_t PL1_Green(uint32_t bits, bool activated);

uint32_t PL1_Red(uint32_t bits, bool activated);

uint32_t PL1_Blue(uint32_t bits, bool activated);


uint32_t PL2_Green(uint32_t bits, bool activated);

uint32_t PL2_Red(uint32_t bits, bool activated);

uint32_t PL2_Blue(uint32_t bits, bool activated);


uint32_t TL1_Red(uint32_t bits, bool activated);

uint32_t TL1_Yellow(uint32_t bits, bool activated);

uint32_t TL1_Green(uint32_t bits, bool activated);


uint32_t TL2_Red(uint32_t bits, bool activated);

uint32_t TL2_Yellow(uint32_t bits, bool activated);

uint32_t TL2_Green(uint32_t bits, bool activated);


uint32_t TL3_Red(uint32_t bits, bool activated);

uint32_t TL3_Yellow(uint32_t bits, bool activated);

uint32_t TL3_Green(uint32_t bits, bool activated);


uint32_t TL4_Red(uint32_t bits, bool activated);

uint32_t TL4_Yellow(uint32_t bits, bool activated);

uint32_t TL4_Green(uint32_t bits, bool activated);


uint32_t TL1_R2G(uint32_t bits);

uint32_t TL2_R2G(uint32_t bits);


uint32_t TL3_R2G(uint32_t bits);

uint32_t TL4_R2G(uint32_t bits);


uint32_t TL1_G2R(uint32_t bits);

uint32_t TL2_G2R(uint32_t bits);


uint32_t TL3_G2R(uint32_t bits);

uint32_t TL4_G2R(uint32_t bits);


uint32_t Init_Task1(uint32_t bits);

#endif //LIGHTLOGIC_H_