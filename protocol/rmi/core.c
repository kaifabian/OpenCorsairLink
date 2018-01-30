/*
 * This file is part of OpenCorsairLink.
 * Copyright (C) 2017  Sean Nelson <audiohacked@gmail.com>

 * OpenCorsairLink is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * any later version.

 * OpenCorsairLink is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with OpenCorsairLink.  If not, see <http://www.gnu.org/licenses/>.
 */

/*! \file protocol/rmi/core.c
 *  \brief Core Routines for RMi Series of Power Supplies
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libusb.h>
#include <math.h>

#include "../../lowlevel/hid.h"
#include "../../device.h"
#include "../../driver.h"
#include "core.h"

double convert_bytes_double(uint16_t v16)
{
	int exponent = v16>>11;
	int fraction = (int)(v16&2047);
	if (exponent > 15)
		exponent = -(32 - exponent);

	if (fraction > 1023)
		fraction = -(2048 - fraction);

	if ((fraction & 1) == 1)
		fraction++;

	return (double)fraction * pow(2.0, (double)exponent);
}

int corsairlink_rmi_device_id(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint8_t *device_id)
{
	//memset(device_id, 0x00, 1);
	(*device_id) = 0xFF;
	return 0;
}

int corsairlink_rmi_firmware_id(struct corsair_device_info *dev, struct libusb_device_handle *handle, char *firmware)
{
	sprintf(firmware, "NA");

	return 0;
}

int corsairlink_rmi_name(struct corsair_device_info *dev, struct libusb_device_handle *handle, char *name)
{
	int rr;
	uint8_t response[64];
	uint8_t commands[64];
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0xfe;
	commands[1] = 0x03;

	rr = dev->driver->write(handle, dev->write_endpoint, commands, 64);
	rr = dev->driver->read(handle, dev->read_endpoint, response, 64);

	memcpy(name, response+2, 16);

	return 0;
}

int corsairlink_rmi_vendor(struct corsair_device_info *dev, struct libusb_device_handle *handle, char *name)
{
	int rr;
	uint8_t response[64];
	uint8_t commands[64];
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0x03;
	commands[1] = 0x99;
	commands[2] = 0x00;

	rr = dev->driver->write(handle, dev->write_endpoint, commands, 64);
	rr = dev->driver->read(handle, dev->read_endpoint, response, 64);

	memcpy(name, response+2, 16);

	return 0;
}

int corsairlink_rmi_product(struct corsair_device_info *dev, struct libusb_device_handle *handle, char *name)
{
	int rr;
	uint8_t response[64];
	uint8_t commands[64];
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0x03;
	commands[1] = 0x9a;
	commands[2] = 0x00;

	rr = dev->driver->write(handle, dev->write_endpoint, commands, 64);
	rr = dev->driver->read(handle, dev->read_endpoint, response, 64);

	memcpy(name, response+2, 16);

	return 0;
}

int corsairlink_rmi_select_page(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint8_t page) {
	int rr;
	uint8_t response[64];
	uint8_t commands[64];
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0x02 /* write register */;
	commands[1] = 0x00 /* page selector */;
	commands[2] = page;
	commands[3] = 0x00;

	rr = dev->driver->write(handle, dev->write_endpoint, commands, 64);
	rr = dev->driver->read(handle, dev->read_endpoint, response, 64);

	return (response[2] == page) ? 0 : -1;
}

int corsairlink_rmi_handshake(struct corsair_device_info *dev, struct libusb_device_handle *handle) {
	int rr;
	uint8_t response[64];
	uint8_t commands[64];
	memset(response, 0, sizeof(response));
	memset(commands, 0, sizeof(commands));

	commands[0] = 0xFE /* handshake */;
	commands[1] = 0x03 /* dunno */;
	commands[2] = 0x00;

	rr = dev->driver->write(handle, dev->write_endpoint, commands, 64);
	rr = dev->driver->read(handle, dev->read_endpoint, response, 64);

	return 0;
}
