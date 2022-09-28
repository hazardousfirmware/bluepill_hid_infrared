#include "hid_functions.h"
#include "mouse_actions.h"

static const int MOVE_PIXELS = 20;

void action_cursor_up(void)
{
    const uint8_t buttons = 0;
    const uint8_t x = 0;
    const uint8_t y = -MOVE_PIXELS;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 3);
}

void action_cursor_down(void)
{
    const uint8_t buttons = 0;
    const uint8_t x = 0;
    const uint8_t y = MOVE_PIXELS;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 3);
}

void action_cursor_left(void)
{
    const uint8_t buttons = 0;
    const uint8_t x = -MOVE_PIXELS;
    const uint8_t y = 0;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 3);
}

void action_cursor_right(void)
{
    const uint8_t buttons = 0;
    const uint8_t x = MOVE_PIXELS;
    const uint8_t y = 0;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 3);
}

void action_mouse_click_l(void)
{
    const uint8_t buttons = MOUSE_BUTTON_L;
    const uint8_t x = 0;
    const uint8_t y = 0;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 3);

    action_complete_callback();
}

void action_mouse_click_m(void)
{
    const uint8_t buttons = MOUSE_BUTTON_M;
    const uint8_t x = 0;
    const uint8_t y = 0;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 3);

    action_complete_callback();
}

void action_mouse_click_r(void)
{
    const uint8_t buttons = MOUSE_BUTTON_R;
    const uint8_t x = 0;
    const uint8_t y = 0;
    const uint8_t wheel = 0;

    const uint8_t buf[4] = {buttons, x, y, wheel};

    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 3);

    action_complete_callback();
}

void action_button_release(void)
{
    const uint8_t buf[4] = {0, 0, 0, 0};
    usb_endpoint_write(EP_ADDRESS_IN_1, buf, 3);
}
