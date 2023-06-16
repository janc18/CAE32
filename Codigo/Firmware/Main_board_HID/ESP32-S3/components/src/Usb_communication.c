#include "Usb_communication.h"
#include "Wheel_task.h"
#define TUSB_DESC_TOTAL_LEN (TUD_CONFIG_DESC_LEN + CFG_TUD_HID * TUD_HID_DESC_LEN)

uint8_t hid_report_descriptor[] = {
    // TUD_HID_REPORT_DESC_GAMEPAD(HID_REPORT_ID(0x05))

    0x05, 0x01, /* USAGE_PAGE (Generic Desktop) */
    0x09, 0x04, /* USAGE (Joystick) */
    0xa1, 0x01, /* COLLECTION (Physical) */
    0x85, 0x01, /* REPORT_ID (1) */
    0x05, 0x09, /* USAGE_PAGE (Button) */
    0x19, 0x01, /* USAGE_MINIMUM (Button 1) */
    0x29, 0x08, /* USAGE_MAXIMUM (Button 3) */
    0x15, 0x00, /* LOGICAL_MINIMUM (0) */
    0x25, 0x01, /* LOGICAL_MAXIMUM (1) */
    0x95, 0x01, /* REPORT_COUNT (1) */
    0x75, 0x08, /* REPORT_SIZE (8) */
    0x81, 0x02, /* INPUT (Data,Var,Abs) */
    0x05, 0x01, /* USAGE_PAGE (Generic Desktop) */
    0x09, 0x30, /* USAGE (X) */
    0x09, 0x31, /* USAGE (Y) */
    0x09, 0x32, /* USAGE (Z) */
    0x09, 0x33, /* USAGE (Rx)*/
    0x15, 0x81, /* LOGICAL_MINIMUM(-129)*/
    0x25, 0x7f, /* LOGICAL_MAXIMUM(127)*/
    0x35, 0xc9, /* */
    0x45, 0xc8, /* */
    0x75, 0x08, /* REPORT_SIZE  (1)*/
    0x95, 0x04, /* REPORT_COUNT (4)*/
    0x81, 0x02, /* INPUT (Data,Var,Abs)*/
    0xc0        /* */
};

uint8_t hid_configuration_descriptor[] = {
    // Configuration number, interface count, string index, total length,
    // attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, 1, 0, TUSB_DESC_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

    // Interface number, string index, boot protocol, report descriptor len, EP
    // In address, size & polling interval
    TUD_HID_DESCRIPTOR(0, 0, false, sizeof(hid_report_descriptor), 0x81, 16, 10),
};

tinyusb_config_t tusb_cfg = {
    .device_descriptor = NULL,
    .string_descriptor = NULL,
    .external_phy = false,
    .configuration_descriptor = hid_configuration_descriptor,
};

void usb_initialization(void) {
    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));
    if (tud_mounted()) {
        printf("Steering wheel mounted\n");
    } else {
        printf("ERROR mounting wheel\n");
    }
}
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type,
                               uint8_t *buffer, uint16_t reqlen) {
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;

    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type,
                           uint8_t const *buffer, uint16_t bufsize) {}
// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )

uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance) {
    // We use only one interface and one HID report descriptor, so we can ignore
    // parameter 'instance'
    return hid_report_descriptor;
}

void Send_custom_hid(void *Pvparameters) {
    // Typecast Raw_pedals_value struct
    Raw_pedals_value *pedals_values = (Raw_pedals_value *)Pvparameters;
    //----------------------------------

    // struct to save the new pedals_values
    // uint8_t report[5] = {0};
    //--------------------------

    //  report[1] = 50;                                 // Axis X
    // report[2] = 60;                                 // Axis Y
    // report[3] = 70;                                 // Axis Z
    // report[4] = 80;                                 // Axis Rx
    TickType_t xLastWakeTime = xTaskGetTickCount(); // Necesary variable to use vTaskDelayUntil
    while (1) {                                     // Send new values each 200ms
        uint8_t report[5] = {1, pedals_values->Accelerator_value, 0, pedals_values->Brake_value, 0};
        // 0,0,volante,Accelerator_value
        while (tud_hid_ready()) {

            tud_hid_report(0x01, report, sizeof(report));
        }
        // vTaskDelayUntil(&xLastWakeTime, 20 / portTICK_PERIOD_MS);
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}
