#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

void action_cursor_up(void);
void action_cursor_down(void);
void action_cursor_left(void);
void action_cursor_right(void);

void action_mouse_click_l(void);
void action_mouse_click_r(void);
void action_mouse_click_m(void);

void action_button_release(void);

extern void action_complete_callback(void);


// bit flags for each button
#define MOUSE_BUTTON_L 0x01 //001b
#define MOUSE_BUTTON_R 0x02 //010b
#define MOUSE_BUTTON_M 0x04 //100b


#endif // ACTIONS_H_INCLUDED
