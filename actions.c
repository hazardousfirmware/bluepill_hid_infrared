#include "hid_functions.h"
#include "actions.h"

static const int MOVE_PIXELS = 50;

void action_cursor_up(void)
{
    const uint8_t buttons = 0;
    const uint8_t x = 0;
    const uint8_t y = -MOVE_PIXELS;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 4);
}

void action_cursor_down(void)
{
    const uint8_t buttons = 0;
    const uint8_t x = 0;
    const uint8_t y = MOVE_PIXELS;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 4);
}

void action_cursor_left(void)
{
    const uint8_t buttons = 0;
    const uint8_t x = -MOVE_PIXELS;
    const uint8_t y = 0;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 4);
}

void action_cursor_right(void)
{
    const uint8_t buttons = 0;
    const uint8_t x = MOVE_PIXELS;
    const uint8_t y = 0;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 4);
}

void action_mouse_click(void)
{
    const uint8_t buttons = 0x01;
    const uint8_t x = 0;
    const uint8_t y = 0;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 4);
}
