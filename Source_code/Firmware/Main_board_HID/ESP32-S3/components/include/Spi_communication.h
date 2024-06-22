#ifndef SPI_H
#define SPI_H

#include "driver/spi_master.h"
#include <string.h>

// spi_device_handle_t spi;
spi_device_handle_t init_spi_device();
void send_spi_data(spi_device_handle_t spi, spi_transaction_t t);
#endif
