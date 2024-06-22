#include "Wheel_task.h"
#include "Spi_communication.h"
#include "Usb_communication.h"

void print(void *Pvparameters) {

    Raw_pedals_value *pedals_values = NULL;
    pedals_values = (Raw_pedals_value *)Pvparameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        printf("%d\t,%d\t,%d\n", pedals_values->Clutch_value, pedals_values->Brake_value,
               pedals_values->Accelerator_value);
        vTaskDelayUntil(&xLastWakeTime, 20 / portTICK_PERIOD_MS);
    }
}
void Create_tasks(Raw_pedals_value *p_pedals_t) {
    xTaskCreate(Get_raw_pedals_value, "Pedals", 4000, (void *)p_pedals_t, 2, NULL);
    xTaskCreate(Send_custom_hid, "Send HID Report", 3000, (void *)p_pedals_t, 1, NULL);
    xTaskCreate(print, "print", 3000, (void *)p_pedals_t, 1, NULL);
}
void Get_raw_pedals_value(void *Pvparameters) {
    Raw_pedals_value *pedals_values = NULL;
    pedals_values = (Raw_pedals_value *)Pvparameters;
    printf("%p\n", pedals_values);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        uint8_t tx_buffer[1] = {0x11};
        uint8_t rx_buffer[3] = {0};
        spi_transaction_t t;
        memset(&t, 0, sizeof(t));
        t.length = 8 * 4;
        t.tx_buffer = tx_buffer;
        t.rx_buffer = rx_buffer;
        spi_device_polling_transmit(pedals_values->spi, &t);
        pedals_values->Accelerator_value = rx_buffer[0];
        pedals_values->Brake_value = rx_buffer[1];
        pedals_values->Clutch_value = rx_buffer[2];
        // spi_device_transmit(pedals_values->spi, &t);
        vTaskDelayUntil(&xLastWakeTime, 70 / portTICK_PERIOD_MS);
    }

    /*
        TickType_t xLastWakeTime = xTaskGetTickCount();
        while (1) {
            printf("1O1\n");
            vTaskDelayUntil(&xLastWakeTime, 1900 / portTICK_PERIOD_MS);
        }
    */
}
