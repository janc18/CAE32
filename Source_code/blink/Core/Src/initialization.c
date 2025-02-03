/*
 * initialization.c
 *
 *  Created on: Jan 5, 2025
 *      Author: jose
 */

#include <stdint.h>
#include "initialization.h"
#include "usb_device.h"
#include "usbd_hid.h"


/*
 * @brief Send data in polling mode to update all the axis values
 *
 *
 */
int executeDemoAxis(USBD_HandleTypeDef hUsbDeviceFS) {
		for (uint8_t i = 0; i < 255; i++) {
		uint8_t report[] = { 1, 0xff, i, i, i, i };
		USBD_HID_SendReport(&hUsbDeviceFS, report, sizeof(report));
		HAL_Delay(50);
	}
	return OK;
}

