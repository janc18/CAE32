
/**
 * @file device_descriptor.c
 * @brief Device descriptor definition 
 */

/**
 * @brief Device descriptor Characteristics
 * 
 * A Device descriptor is a set of 8 bits that define the features
 * of a device, this is send constantly through USB bus and is reading
 * by the kernel.
 *
 * The features of this device are the next:
 * Automobile Simulation device
 * 3 Pedals
 * Steering wheel
 * Shifter
 *
 * .. note::
 *    This device descriptor probably isn't correct
 */

#include "device_descriptor.h"

unsigned char rdesc[32] = {
    0x05, 0x02, /* USAGE_PAGE ( Simulation Controls Page) */
    0x09, 0x02, /* USAGE (Automobile Simulation Device) */
                //	0xa1, 0x01,	/* COLLECTION (Application) */
                //	0x09, 0x01,		/* USAGE (Pointer) */
    0xa1, 0x01, /* COLLECTION (Physical) */
    0x85, 0x01, /* REPORT_ID (1) */
                // 0x05, 0x02, /* USAGE (Automobile Simulation Device) */
    0x09, 0xc4, /* USAGE (Accelerator)*/
    0x09, 0xc5, /* USAGE (Brake)*/
    0x09, 0xc6, /* USAGE (Clutch)*/
    0x09, 0xc7, /* USAGE (Shifter)*/
    0x09, 0xc8, /* USAGE (Steering)*/
    0x15, 0x00, /* Logical_minimum (0) */
    0x25, 0xfe, /* Logical_maximum (1) */
    0x95, 0x05, /* report_count (3) */
    0x75, 0x08, /* report_size (1) */
    0x81, 0x02, /* input (data,var,abs) */
    0xc0        /* end_collection */
                //	0xc0,		/* end_collection */
};

