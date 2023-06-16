#include "Spi_communication.h"

//  	Spi's pin	//
const uint8_t PIN_NUM_MISO = 37;
const uint8_t PIN_NUM_MOSI = 35;
const uint8_t PIN_NUM_CLK = 36;
const uint8_t PIN_NUM_CS = 45;
//----------------------//

//  Pedal's registers	//
const uint8_t FIRMWARE_VERSION = 0x01;
const uint8_t CONFIG_ADC_RESOLUTION = 0x02;
const uint8_t RAW_ACCE_VALUE = 0x03;
const uint8_t RAW_BRAKE_VALUE = 0x04;
const uint8_t RAW_CLUTCH_VALUE = 0x05;
const uint8_t STATUS = 0x06;
//---------------------//

spi_device_handle_t init_spi_device() {
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1000000, // 1 Mhz
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .queue_size = 1,
    };

    spi_device_handle_t spi;

    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0,
    };

    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, 0));
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &spi));

    return spi;
}

void send_spi_data(spi_device_handle_t spi, spi_transaction_t t) {}
/*
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8 * rx_buffer_size;
    t.tx_buffer = (uint8_t *)tx_buffer;
    t.rx_buffer = rx_buffer;
    spi_device_polling_transmit(spi, &t);
    */
