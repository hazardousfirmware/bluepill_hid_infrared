#ifndef HID_FUNCTIONS_H_INCLUDED
#define HID_FUNCTIONS_H_INCLUDED

#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/hid.h>

enum usbd_request_return_codes hid_control_request(usbd_device *dev, struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
			void (**complete)(usbd_device *, struct usb_setup_data *));
void hid_set_config(usbd_device *dev, uint16_t wValue);

void usbd_setup(void);

void usbpoll(void);

void usb_endpoint_write(uint8_t endpoint, const uint8_t *data, uint16_t data_length);

extern bool usb_ready;

#define EP_ADDRESS_IN_1 0x81

#endif // HID_FUNCTIONS_H_INCLUDED
