/*
 * generic_hid_driver.cpp
 *
 *  Created on: Jan 9, 2020
 *      Author: Pragun
 */

#include <generic_hid_driver.hpp>
#include <vector>
#include "msgs.h"


Generic_HID_Driver::Generic_HID_Driver(){};

Generic_HID_Driver::~Generic_HID_Driver(){}

std::vector<uint8_t> Generic_HID_Driver::hid_interface_list(){
	std::vector<uint8_t> vect{};
	return vect;
}

USBH_StatusTypeDef Generic_HID_Driver::prepare_hid_handle(uint8_t interface, HID_HandleTypeDef *hid_handle){
	return USBH_OK;
}

USBH_StatusTypeDef Generic_HID_Driver::hid_handle_deinit(HID_HandleTypeDef *hid_handle){
	free(hid_handle->report_descriptor_buffer);
	free(hid_handle->report_buffer);
	return USBH_OK;
}

USBH_StatusTypeDef Generic_HID_Driver::hid_handle_init(HID_HandleTypeDef *hid_handle){
	hid_handle->report_buffer = (uint8_t*) malloc(hid_handle->length);
	return USBH_OK;
}

USBH_StatusTypeDef Generic_HID_Driver::process_hid_report(HID_HandleTypeDef *hid_handle, uint8_t *buf, uint8_t len){
	printf("HID Interface:%d Received report: %d bytes\r\n", hid_handle->interface, len);
	PrintHexBuf(buf, len);
	return USBH_OK;
}

USBH_StatusTypeDef Generic_HID_Driver::process_hid_report_descriptor(HID_HandleTypeDef *hid_handle, uint8_t *buf, uint8_t len){
	hid_handle->report_descriptor_buffer = (uint8_t*) malloc(len);
	memcpy(hid_handle->report_descriptor_buffer, buf, len);
	printf("HID Interface:%d Received report descriptor: %d bytes\r\n", hid_handle->interface, len);
	PrintHexBuf(buf, len);
	return USBH_OK;
}

