#include "main.h"

void ADC128S102_StartConversion(SPI_HandleTypeDef *hspi1);
uint16_t ADC128S102_ReadChannel(SPI_HandleTypeDef *hspi, uint8_t channel);
