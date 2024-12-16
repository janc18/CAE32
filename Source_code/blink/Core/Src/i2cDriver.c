#include "i2cDriver.h"

#define ADC128S102_CMD_START_CONVERSION 0x10
#define ADC128S102_CMD_READ_DATA         0x00

uint8_t spi_tx_buffer[2];
uint8_t spi_rx_buffer[2];

void ADC128S102_StartConversion(SPI_HandleTypeDef *hspi1) {
    spi_tx_buffer[0] = ADC128S102_CMD_START_CONVERSION;
    spi_tx_buffer[1] = 0x00;

    HAL_SPI_Transmit(hspi1, spi_tx_buffer, 2, HAL_MAX_DELAY);
}

uint16_t ADC128S102_ReadData(SPI_HandleTypeDef *hspi) {
    uint16_t adc_data = 0;

    uint8_t spi_tx_buffer[2] = {ADC128S102_CMD_READ_DATA, 0x00};
    uint8_t spi_rx_buffer[2];

    if (HAL_SPI_Transmit(hspi, spi_tx_buffer, 2, 125) != HAL_OK) {
        return 111;
    }

    if (HAL_SPI_Receive(hspi, spi_rx_buffer, 2, 125) != HAL_OK) {
        return 119;
    }

    adc_data = (spi_rx_buffer[0] << 8) | spi_rx_buffer[1];

    return adc_data;
}
