/*
 * hid_device_drivers.h
 *
 * Created on: Jan 4, 2020
 * Author: Pragun Goyal
 */

#include <mmo_mouse_hid_driver.hpp>
#include "usbh_hid.hpp"
#include "logitech_g600.hpp"
#include "msgs.h"

#define KEYBOARD_INTERFACE 1
#define MOUSE_INTERFACE 0

//The following are not used (for now)
#define KEYBOARD_REPORT_DESCRIPTOR_BUFFER_SIZE 135
#define MOUSE_REPORT_DESCRIPTOR_BUFFER_SIZE 67
#define KEYBOARD_REPORT_BUFFER 32
#define MOUSE_REPORT_BUFFER 9

Logitech_G600_Mouse_Driver::Logitech_G600_Mouse_Driver(): MMO_Mouse_HID_Driver(
		(uint8_t) KEYBOARD_INTERFACE,
		(uint8_t) MOUSE_INTERFACE)
{
	info_msg("Constructing Logitech G600 Driver Object\r\n");
}

Logitech_G600_Mouse_Driver::~Logitech_G600_Mouse_Driver(){};

USBH_StatusTypeDef Logitech_G600_Mouse_Driver::hid_handle_init(HID_HandleTypeDef *hid_handle){
	hid_handle->report_buffer = (uint8_t*) malloc(hid_handle->length);
	info_msg("Logitech G600 Mouse Initialized.\r\n");
	return USBH_OK;
}

USBH_StatusTypeDef Logitech_G600_Mouse_Driver::process_hid_report_descriptor_mouse(uint8_t *buff, uint8_t len){
	info_msg("Mouse received report descriptor: %d bytes\r\n", len);
	PrintHexBuf(buff, len, VERBOSE_MSG);
	return USBH_OK;
}

USBH_StatusTypeDef Logitech_G600_Mouse_Driver::process_hid_report_descriptor_keyboard(uint8_t *buff, uint8_t len){
	info_msg("Keyboard received report descriptor: %d bytes\r\n", len);
	PrintHexBuf(buff, len, VERBOSE_MSG);
	return USBH_OK;
}

USBH_StatusTypeDef Logitech_G600_Mouse_Driver::process_hid_report_mouse (uint8_t *buff, uint8_t len){
	verbose_msg("Mouse received report: %d bytes\r\n", len);
	PrintHexBuf(buff, len, DEBUG_MSG);

	input_state.dx = buff[2] | (buff[3] << 8);
	input_state.dy = buff[4] | (buff[5] << 8);
	input_state.dz = buff[6];
	return USBH_OK;
}

USBH_StatusTypeDef Logitech_G600_Mouse_Driver::process_hid_report_keyboard (uint8_t *buff, uint8_t len){
	verbose_msg("Keyboard received report: %d bytes\r\n", len);
	PrintHexBuf(buff, len, DEBUG_MSG);
	if(buff[0] == 0x80){
		input_state.buttons = buff[1] | (buff[2] << 8) | (buff[3] << 16);

		//this is kind of a hack to reset the counters for position
		//under the assumption that by the time we receive a keyboard report
		//most likely all the location data would already have been transferred

		input_state.dx = 0;
		input_state.dy = 0;
		input_state.dz = 0;

		return USBH_OK;
	}
	return USBH_NOT_SUPPORTED;
}
