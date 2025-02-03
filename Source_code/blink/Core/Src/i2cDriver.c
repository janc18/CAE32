#include "i2cDriver.h"

#define ADC128S102_CMD_START_CONVERSION 0x10
#define ADC128S102_CMD_READ_DATA         0x00
#define ADC128S102_CMD_SET_CHANNEL 0x40  

uint8_t spi_tx_buffer[2];
uint8_t spi_rx_buffer[2];

void ADC128S102_StartConversion(SPI_HandleTypeDef *hspi1) {
    spi_tx_buffer[0] = ADC128S102_CMD_START_CONVERSION;
    spi_tx_buffer[1] = 0x00;

    HAL_SPI_Transmit(hspi1, spi_tx_buffer, 2, HAL_MAX_DELAY);
}

uint16_t ADC128S102_ReadChannel(SPI_HandleTypeDef *hspi, uint8_t channel) {
    uint16_t adc_data = 0; 
    if (channel > 7) {
        return 0xFFFF;  
    }
    spi_tx_buffer[0] = ADC128S102_CMD_SET_CHANNEL | (channel & 0x07);
    spi_tx_buffer[1] = 0x00;  
    if (HAL_SPI_Transmit(hspi, spi_tx_buffer, 2, HAL_MAX_DELAY) != HAL_OK) {
        return 0xFFFF;  
    }
    HAL_Delay(1);  
    if (HAL_SPI_Receive(hspi, spi_rx_buffer, 2, HAL_MAX_DELAY) != HAL_OK) {
        return 0xFFFF;  
    }
    adc_data = ((spi_rx_buffer[0] << 8) | spi_rx_buffer[1]) >> 4;
    return adc_data;
}
