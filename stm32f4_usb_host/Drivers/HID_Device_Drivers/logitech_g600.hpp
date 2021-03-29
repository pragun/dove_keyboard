/*
 * hid_device_drivers.h
 *
 *  Created on: Jan 4, 2020
 *      Author: Pragun Goyal
 */

#include <mmo_mouse_hid_driver.hpp>
#include "usbh_hid.hpp"


class Logitech_G600_Mouse_Driver: public MMO_Mouse_HID_Driver{
public:
	Logitech_G600_Mouse_Driver();
	~Logitech_G600_Mouse_Driver();
	USBH_StatusTypeDef hid_handle_init(HID_HandleTypeDef *hid_handle);

private:
	USBH_StatusTypeDef process_hid_report_descriptor_mouse(uint8_t *buff, uint8_t len);
	USBH_StatusTypeDef process_hid_report_descriptor_keyboard(uint8_t *buff, uint8_t len);
	USBH_StatusTypeDef process_hid_report_mouse (uint8_t *buff, uint8_t len);
	USBH_StatusTypeDef process_hid_report_keyboard (uint8_t *buff, uint8_t len);
};
