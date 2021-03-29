#include <mmo_mouse_hid_driver.hpp>
#include <vector>
#include "msgs.h"

__weak void MMO_Mouse_Driver_New_State_Callback(const MMO_Mouse_State_TypeDef &mmo_mouse_state)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(mmo_mouse_state);
  /* NOTE: This function should not be modified, when the callback is needed,
           the MMO_Mouse_Driver_New_State_Callback should be implemented in the user file
   */
}

MMO_Mouse_HID_Driver::MMO_Mouse_HID_Driver(	uint8_t keyboard_iface,
											uint8_t mouse_iface)
{
	input_state.buttons = 0;
	input_state.dx = 0;
	input_state.dy = 0;
	input_state.dz = 0;

	mouse_interface = mouse_iface;
	keyboard_interface = keyboard_iface;
}


std::vector<uint8_t> MMO_Mouse_HID_Driver::hid_interface_list(){
	std::vector<uint8_t> vect{ mouse_interface, keyboard_interface };
	return vect;
}

MMO_Mouse_HID_Driver::~MMO_Mouse_HID_Driver(){};


USBH_StatusTypeDef MMO_Mouse_HID_Driver::hid_handle_init(HID_HandleTypeDef *hid_handle){
	hid_handle->report_buffer = (uint8_t*) malloc(hid_handle->length);
	return USBH_OK;
}

USBH_StatusTypeDef MMO_Mouse_HID_Driver::hid_handle_deinit(HID_HandleTypeDef *hid_handle){
	free(hid_handle->report_descriptor_buffer);
	free(hid_handle->report_buffer);
	return USBH_OK;
}


USBH_StatusTypeDef MMO_Mouse_HID_Driver::prepare_hid_handle(uint8_t interface, HID_HandleTypeDef *hid_handle){
	return USBH_OK;
}

USBH_StatusTypeDef MMO_Mouse_HID_Driver::process_hid_report(HID_HandleTypeDef *hid_handle, uint8_t *buf, uint8_t len)
{
	USBH_StatusTypeDef ret_val = USBH_FAIL;
	if (hid_handle->interface == mouse_interface){
		ret_val = process_hid_report_mouse(buf,len);
	}
	if (hid_handle->interface == keyboard_interface){
		ret_val =  process_hid_report_keyboard(buf,len);
	}
	if (ret_val == USBH_OK){
		MMO_Mouse_Driver_New_State_Callback(input_state);
	}
	return ret_val;
}

USBH_StatusTypeDef MMO_Mouse_HID_Driver::process_hid_report_descriptor(HID_HandleTypeDef *hid_handle, uint8_t *buf, uint8_t len)
{
	hid_handle->report_descriptor_buffer = (uint8_t*) malloc(len);
	memcpy(hid_handle->report_descriptor_buffer, buf, len);
	if (hid_handle->interface == mouse_interface){
		return process_hid_report_descriptor_mouse(hid_handle->report_descriptor_buffer,len);
	}
	if (hid_handle->interface == keyboard_interface){
		return process_hid_report_descriptor_keyboard(hid_handle->report_descriptor_buffer,len);
	}
	return USBH_FAIL;
}

USBH_StatusTypeDef MMO_Mouse_HID_Driver::process_hid_report_descriptor_mouse(uint8_t *buf, uint8_t len){ return USBH_OK; };
USBH_StatusTypeDef MMO_Mouse_HID_Driver::process_hid_report_descriptor_keyboard(uint8_t *buf, uint8_t len){ return USBH_OK;};
USBH_StatusTypeDef MMO_Mouse_HID_Driver::process_hid_report_mouse (uint8_t *buf, uint8_t len){ return USBH_OK; };
USBH_StatusTypeDef MMO_Mouse_HID_Driver::process_hid_report_keyboard (uint8_t *buf, uint8_t len){ return USBH_OK; };
