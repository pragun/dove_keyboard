/*
 * hid_device_drivers.h
 *
 *  Created on: Jan 4, 2020
 *      Author: Pragun Goyal
 */

#ifndef HID_DEVICE_DRIVERS_MMO_MOUSE_HID_DRIVER_HPP_
#define HID_DEVICE_DRIVERS_MMO_MOUSE_HID_DRIVER_HPP_

#include <vector>
#include "usbh_hid.hpp"
#include "hid_device_driver.hpp"

#pragma pack(1)
typedef struct
{
	int16_t dx;
	int16_t dy;
	int8_t dz;
	uint32_t buttons;
}
MMO_Mouse_State_TypeDef;

class MMO_Mouse_HID_Driver : public HID_Device_Driver{
	public:
	MMO_Mouse_State_TypeDef input_state;
	std::vector<uint8_t> hid_interface_list();
	virtual USBH_StatusTypeDef prepare_hid_handle(uint8_t interface, HID_HandleTypeDef *hid_handle);
	virtual USBH_StatusTypeDef process_hid_report(HID_HandleTypeDef *hid_handle, uint8_t *buf, uint8_t len);
	virtual USBH_StatusTypeDef process_hid_report_descriptor(HID_HandleTypeDef *hid_handle, uint8_t *buf, uint8_t len);
	virtual USBH_StatusTypeDef hid_handle_init(HID_HandleTypeDef *hid_handle);
	virtual USBH_StatusTypeDef hid_handle_deinit(HID_HandleTypeDef *hid_handle);


	MMO_Mouse_HID_Driver(uint8_t keyboard_iface,
			uint8_t mouse_iface);
	virtual ~MMO_Mouse_HID_Driver();


	private:

	uint8_t mouse_interface;
	uint8_t keyboard_interface;
	uint8_t keyboard_report_descriptor_buffer_size;
	uint8_t mouse_report_descriptor_buffer_size;
	uint8_t keyboard_report_buffer_size;
	uint8_t mouse_report_buffer_size;

	uint8_t (*new_report_callback)(const MMO_Mouse_State_TypeDef& input_state);
	virtual USBH_StatusTypeDef process_hid_report_descriptor_mouse(uint8_t *buf, uint8_t len);
	virtual USBH_StatusTypeDef process_hid_report_descriptor_keyboard(uint8_t *buf, uint8_t len);
	virtual USBH_StatusTypeDef process_hid_report_mouse (uint8_t *buf, uint8_t len);
	virtual USBH_StatusTypeDef process_hid_report_keyboard (uint8_t *buf, uint8_t len);

};

#endif /* HID_DEVICE_DRIVERS_MMO_MOUSE_HID_DRIVER_HPP_ */
