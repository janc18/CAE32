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
int executeDemoAxis(USBD_HandleTypeDef hUsbDeviceFS,uint8_t axisX,uint8_t axisY) {
	uint8_t report[6] = { 1, 0xff, axisX, axisY, 12, 45};
	USBD_HID_SendReport(&hUsbDeviceFS, report, sizeof(report));
	HAL_Delay(10);
	return OK;
}
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

