/*
 * initialization.h
 *
 *  Created on: Jan 5, 2025
 *      Author: jose
 */

#ifndef INC_INITIALIZATION_H_
#define INC_INITIALIZATION_H_
#include "usb_device.h"

enum ID_AXIS{
	BRAKE,
	ACCELERATOR,
	CLUTCH
};

enum AXIS_STATUS{
	OK,
	ID_AXIS_ERROR
};
#define MAXNUMBEROFAXIS 3

typedef struct USBReport_t{
	uint8_t Buttons;
	uint8_t **Axis;
}USBReport_t;


int sendAxisValues(USBD_HandleTypeDef hUsbDeviceFS,uint8_t accelerator,uint8_t clutch,uint8_t brake);
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);

#endif /* INC_INITIALIZATION_H_ */
