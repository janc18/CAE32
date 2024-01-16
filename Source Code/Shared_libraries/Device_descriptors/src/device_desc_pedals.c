/**
 * @file device_desc_pedals.c
 * @brief Pedals Device Descriptor
 *
 * @brief Characteristics of the Pedals Device
 *
 * The features of this device include the following:
 *
 * - A minimum of 3 channels with an 8-bit resolution, which is the
 *   standard configuration. However, it supports 8 ADC channels with
 *   a 12-bit resolution and 3 load cell channels, providing significant
 *   flexibility in the simracing setup.
 * 
 * - Terminal console for real-time configuration changes or command transmission.
 * 
 * .. note:
 *    Due to the PCB's high flexibility in configuration, the device descriptor
 *    may vary for each specific case.
 *    For this particular device descriptor, the standard configuration will be
 *    applied (3 channels of 8 bits).
 *  
 * - Related documents
 *   https://www.usb.org/sites/default/files/documents/hid1_11.pdf
 *   https://usb.org/sites/default/files/hut1_4.pdf
 */

#include "device_desc_pedals.h"

char Pedals_descriptor [25]={
    0x05, 0x01, /* USAGE_PAGE (Generic Desktop Page) */
    0x09, 0x04, /* USAGE (Joystick) */
    0xA1, 0x01, /* COLLECTION (Physical) */
    0x85, 0x01, /* REPORT_ID (1) */
    0x09, 0x30, /* USAGE (Accelerator)*/
    0x09, 0x31, /* USAGE (Brake)*/
    0x09, 0x32, /* USAGE (Clutch)*/
    0x15, 0x00, /* Logical_minimum (0) */
    0x25, 0xFE, /* Logical_maximum (255) */
    0x95, 0x03, /* report_count (3) */
    0x75, 0x03, /* report_size (1) */
    0x81, 0x02, /* input (data,var,abs) */
    0xc0        /* end_collection */
};
