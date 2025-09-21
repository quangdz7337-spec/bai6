#ifndef __BH1750_H
#define __BH1750_H

#include "stm32f10x.h"

#define BH1750_ADDR         0x46   // d?a ch? I2C (ADDR n?i GND)

#define BH1750_POWER_DOWN   0x00
#define BH1750_POWER_ON     0x01
#define BH1750_RESET        0x07

// One-time measurement mode
#define ONE_TIME_HIGH_RES_MODE  0x20

void BH1750_Init(void);
float BH1750_ReadLux_OneTime(void);
void delay_ms(uint32_t ms);

#endif
