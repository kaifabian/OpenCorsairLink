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

/*! \file protocol/rmi/core.h
 *  \brief Core Routines for RMi Series of Power Supplies
 */
#ifndef _PROTOCOL_RMI_H
#define _PROTOCOL_RMI_H

#include "../../common.h"

double convert_bytes_double(uint16_t v16);

int corsairlink_rmi_device_id(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint8_t *device_id);
int corsairlink_rmi_firmware_id(struct corsair_device_info *dev, struct libusb_device_handle *handle, char *firmware);
int corsairlink_rmi_channel_id(struct corsair_device_info *dev);
int corsairlink_rmi_product_id(struct corsair_device_info *dev);

int corsairlink_rmi_select_page(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint8_t page);
int corsairlink_rmi_handshake(struct corsair_device_info *dev, struct libusb_device_handle *handle);

int corsairlink_rmi_output_select(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint8_t select);
int corsairlink_rmi_output_volts(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint16_t *volts);
int corsairlink_rmi_output_amps(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint16_t *amps);
int corsairlink_rmi_output_watts(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint16_t *watts);

int corsairlink_rmi_power_total_wattage(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint16_t *watts);
int corsairlink_rmi_power_supply_voltage(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint16_t *volts);

int corsairlink_rmi_temperature(struct corsair_device_info *dev, struct libusb_device_handle *handle, 	 		uint8_t select, uint16_t *temp);

int corsairlink_rmi_fan_mode(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint16_t *mode);
int corsairlink_rmi_fan_pwm(struct corsair_device_info *dev, struct libusb_device_handle *handle, 
			uint16_t *pwm);
int corsairlink_rmi_fan_pwm_percent(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint16_t *pwm_percent);
int corsairlink_rmi_fan_status(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint16_t *status);

int corsairlink_rmi_time_powered(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint32_t *v32);
int corsairlink_rmi_time_uptime(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint32_t *v32);

int corsairlink_rmi_name(struct corsair_device_info *dev, struct libusb_device_handle *handle, char *name);
int corsairlink_rmi_vendor(struct corsair_device_info *dev, struct libusb_device_handle *handle, char *name);
int corsairlink_rmi_product(struct corsair_device_info *dev, struct libusb_device_handle *handle, char *name);

int corsairlink_rmi_set_rail_state(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint8_t rail_state, uint8_t *rail_state_out);
int corsairlink_rmi_get_rail_state(struct corsair_device_info *dev, struct libusb_device_handle *handle, uint8_t *rail_state_out);
#endif
