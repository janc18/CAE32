#include "main.h"
/*
void ADC128S102_StartConversion(SPI_HandleTypeDef *hspi1);
uint16_t ADC128S102_ReadChannel(SPI_HandleTypeDef *hspi, uint8_t channel);
void ADC128S102_ReadAllChannels(SPI_HandleTypeDef *hspi, uint16_t *result);
uint16_t ADC128S102_ReadSingleChannel(SPI_HandleTypeDef *hspi, uint8_t channel);
*/
void SCLK_High(void);
void SCLK_Low(void);
void Send_Bit(uint8_t bit_value);
uint8_t Receive_Bit(void);
uint16_t ADC128S102_ReadSingleChannel(uint8_t channel);

