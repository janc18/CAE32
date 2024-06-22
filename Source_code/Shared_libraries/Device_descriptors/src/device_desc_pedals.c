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

unsigned char Pedals_descriptor[49] = {
    0x05, 0x01,                         /* USAGE_PAGE (Generic Desktop) */
    0x09, 0x04,                         /* USAGE (Joystick) */
    0xa1, 0x01,                         /* COLLECTION (Physical) */
    0x85, 0x01,                         /* REPORT_ID (1) */
    0x05, 0x09,                         /* USAGE_PAGE (Button) */
    0x19, 0x01,                         /* USAGE_MINIMUM (Button 1) */
    0x29, 0x08,                         /* USAGE_MAXIMUM (Button 3) */
    0x15, 0x00,                         /* LOGICAL_MINIMUM (0) */
    0x25, 0x01,                         /* LOGICAL_MAXIMUM (1) */
    0x95, 0x08,                         /* REPORT_COUNT (3) */
    0x75, 0x01,                         /* REPORT_SIZE (1) */
    0x81, 0x02,                         /* INPUT (Data,Var,Abs) */
    0x05, 0x01,                         /* USAGE_PAGE (Generic Desktop) */
    0x09, 0x30,                         /* USAGE (X) */
    0x09, 0x31,                         /* USAGE (Y) */
    0x09, 0x32,                         /* USAGE (Z) */
    0x09, 0x33,                         /* USAGE (WHEEL) */
    0x15, 0x00,                         /* LOGICAL_MINIMUM (0) */
    0x25, 0xFF,                         /* LOGICAL_MAXIMUM (255) */
    0x35, 0xc9,                         /* PHYSICAL_MINIMUM ()*/
    0x45, 0xc8,                         /* PHYSICAL_MAXIMUM ()*/
    0x75, 0x08,                         /* REPORT_SIZE (8) */
    0x95, 0x04,                         /* REPORT_COUNT (4) */
    0x81, 0x02,                         /* INPUT (Data,Var,Rel) */
    0xc0                                /* END_COLLECTION */
};
