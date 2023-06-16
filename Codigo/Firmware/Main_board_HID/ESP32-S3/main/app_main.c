#include "Spi_communication.h"
#include "Usb_communication.h"
#include "Wheel_task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/task.h"
#include <stdio.h>

Raw_pedals_value pedals_t = {0};

void app_main() {
    Raw_pedals_value *p_pedals_t = malloc(sizeof(pedals_t));
    p_pedals_t = &pedals_t;

    p_pedals_t->spi = init_spi_device();
    printf("%p\n", p_pedals_t);
    usb_initialization();
    Create_tasks(p_pedals_t);
}
// https://github.com/hathach/tinyusb/blob/c0d79457f61cc4ee27336f430a6f96403bd8b289/src/class/hid/hid_device.h
/*
            static bool send_hid_data = true;
            if (send_hid_data) {
                for (int i = 0; i < 100; i++) {

            send_hid_data = !gpio_get_level(APP_BUTTON);
            */
