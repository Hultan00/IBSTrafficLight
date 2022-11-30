#ifndef SHIFTREGISTER_H_
#define SHIFTREGISTER_H_

void STCP_ON();

void STCP_OFF();

void STCP_Clock();

void MR_ON();

void MR_OFF();

void EN_ON();

void EN_OFF();

void EN_Toggle();

uint32_t SR_bitset(uint32_t bits);

uint32_t SR_bitadj(uint32_t bits, uint32_t newbits, uint32_t bitmask);

#endif //SHIFTREGISTER_H_