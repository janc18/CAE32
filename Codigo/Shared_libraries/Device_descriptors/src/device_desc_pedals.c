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
 * .. note::
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


