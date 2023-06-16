#ifndef WHEEL_TASKS
#define WHEEL_TASKS
#include "FreeRTOS.h"
#include "Spi_communication.h"
#include "freertos/task.h"
typedef struct {
    uint8_t Accelerator_value;
    uint8_t Brake_value;
    uint8_t Clutch_value;
    spi_device_handle_t spi;
} Raw_pedals_value;

typedef struct {
    Raw_pedals_value Pedals_values;
    uint8_t Shifter;
} Raw_values;

void Create_tasks(Raw_pedals_value *p_pedals_t);

// Tasks
void Get_raw_pedals_value();
void Get_raw_shifter_value(void *pvParameters);
// void Send_HID_report(void *pvParameters);

#endif
