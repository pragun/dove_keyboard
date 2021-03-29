/*
 * generic_hid_driver.hpp
 *
 *  Created on: Jan 9, 2020
 *      Author: Pragun
 */

#ifndef HID_DEVICE_DRIVERS_GENERIC_HID_DRIVER_HPP_
#define HID_DEVICE_DRIVERS_GENERIC_HID_DRIVER_HPP_

#include <vector>
#include "usbh_hid.hpp"
#include "hid_device_driver.hpp"

class Generic_HID_Driver : public HID_Device_Driver{
	public:
	std::vector<uint8_t> hid_interface_list();
	virtual USBH_StatusTypeDef prepare_hid_handle(uint8_t interface, HID_HandleTypeDef *hid_handle);
	virtual USBH_StatusTypeDef process_hid_report(HID_HandleTypeDef *hid_handle, uint8_t *buf, uint8_t len);
	virtual USBH_StatusTypeDef process_hid_report_descriptor(HID_HandleTypeDef *hid_handle, uint8_t *buf, uint8_t len);
	virtual USBH_StatusTypeDef hid_handle_init(HID_HandleTypeDef *hid_handle);
	virtual USBH_StatusTypeDef hid_handle_deinit(HID_HandleTypeDef *hid_handle);
	Generic_HID_Driver();
	~Generic_HID_Driver();
};


#endif /* HID_DEVICE_DRIVERS_GENERIC_HID_DRIVER_HPP_ */
