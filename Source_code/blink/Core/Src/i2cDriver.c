#include "i2cDriver.h"


void SCLK_High(void) {
    HAL_GPIO_WritePin(GPIOA, SCLK_Pin, GPIO_PIN_SET);
}

void SCLK_Low(void) {
    HAL_GPIO_WritePin(GPIOA, SCLK_Pin, GPIO_PIN_RESET);
}

void Send_Bit(uint8_t bit_value) {
    if (bit_value) {
        HAL_GPIO_WritePin(GPIOA, MOSI_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(GPIOA, MOSI_Pin, GPIO_PIN_RESET);
    }
    SCLK_High();
    SCLK_Low();
}

uint8_t Receive_Bit(void) {
    uint8_t bit_value = HAL_GPIO_ReadPin(GPIOA, MISO_Pin);
    SCLK_High();
    SCLK_Low();
    return bit_value;
}


uint16_t ADC128S102_ReadSingleChannel(uint8_t channel) {
    uint16_t adc_data = 0;
    if (channel > 7) {
        return 0xFFFF;
    }
    HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_RESET);
    Send_Bit(1);
    for (int i = 2; i >= 0; i--) {
        Send_Bit((channel >> i) & 0x01);
    }
    for (int i = 11; i >= 0; i--) {
        adc_data |= (Receive_Bit() << i);
    }
    HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_SET);
    return adc_data;
}
