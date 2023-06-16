#ifndef USB_H
#define USB_H

#include "class/hid/hid_device.h"
#include "tinyusb.h"

#define TUSB_DESC_TOTAL_LEN                                                    \
    (TUD_CONFIG_DESC_LEN + CFG_TUD_HID * TUD_HID_DESC_LEN)

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id,
                               hid_report_type_t report_type, uint8_t *buffer,
                               uint16_t reqlen);

uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance);
void usb_initialization(void);
void Send_custom_hid();
#endif
