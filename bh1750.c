#include "bh1750.h"
void delay_ms(uint32_t ms) {
    uint32_t i;
    for(i = 0; i < ms * 8000; i++) {
        __NOP();
    }
}


static void BH1750_WriteCmd(uint8_t cmd) {
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, BH1750_ADDR, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    I2C_SendData(I2C1, cmd);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    I2C_GenerateSTOP(I2C1, ENABLE);
}

void BH1750_Init(void) {
    BH1750_WriteCmd(BH1750_POWER_ON);
    BH1750_WriteCmd(BH1750_RESET);
    BH1750_WriteCmd(BH1750_POWER_DOWN); // v? ch? d? ch?
}

float BH1750_ReadLux_OneTime(void) {
    uint16_t val = 0;

    // b?t ngu?n và g?i l?nh do 1 l?n
    BH1750_WriteCmd(BH1750_POWER_ON);
    BH1750_WriteCmd(ONE_TIME_HIGH_RES_MODE);

    // d?i c?m bi?n do (~180ms)
    delay_ms(180);

    // b?t d?u d?c d? li?u
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, BH1750_ADDR, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    val = I2C_ReceiveData(I2C1) << 8;

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    val |= I2C_ReceiveData(I2C1);

    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);
    I2C_AcknowledgeConfig(I2C1, ENABLE);

    // t?t ngu?n sau khi do
    BH1750_WriteCmd(BH1750_POWER_DOWN);

    return (float)val / 1.2f;
}
