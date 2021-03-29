#include "hid_device_driver.hpp"


HID_Device_Driver::HID_Device_Driver(){};
HID_Device_Driver::~HID_Device_Driver(){};

std::vector<uint8_t> HID_Device_Driver::hid_interface_list(){
	std::vector<uint8_t> v;
	return v;
};

USBH_StatusTypeDef HID_Device_Driver::prepare_hid_handle(uint8_t interface, HID_HandleTypeDef *hid_handle){ return USBH_OK; };
USBH_StatusTypeDef HID_Device_Driver::process_hid_report(HID_HandleTypeDef *hid_handle, uint8_t *buf, uint8_t len){ return USBH_OK; };
USBH_StatusTypeDef HID_Device_Driver::process_hid_report_descriptor(HID_HandleTypeDef *hid_handle, uint8_t *buf, uint8_t len){ return USBH_OK; };
USBH_StatusTypeDef HID_Device_Driver::hid_handle_deinit(HID_HandleTypeDef *hid_handle){ return USBH_OK; };
USBH_StatusTypeDef HID_Device_Driver::hid_handle_init(HID_HandleTypeDef *hid_handle){ return USBH_OK; };

