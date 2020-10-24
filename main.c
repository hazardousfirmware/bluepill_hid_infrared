#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/st_usbfs.h>
#include <libopencm3/stm32/exti.h>
#include "hid_functions.h"
#include "nec_infrared.h"
#include "actions.h"

uint32_t timing_delay = 0;
uint32_t clock_counter = 0;

void doNothing(void)
{
    static int led = 0;

    if (led)
    {
        led = 0;
        gpio_clear(GPIOC, GPIO13);
    }
    else
    {
        led = 1;
        gpio_set(GPIOC, GPIO13);
    }
}


const struct nec_infrared_command_t command_list[] = {
    {
        .address = 0x03, //WINFAST REMOTE up button
        .command = 0x0C,
        .action = &action_cursor_up
    },
    {
        .address = 0x03, //WINFAST REMOTE down button
        .command = 0x10,
        .action = &action_cursor_down
    },
    {
        .address = 0x03, //WINFAST REMOTE left button
        .command = 0x08,
        .action = &action_cursor_left
    },
    {
        .address = 0x03, //WINFAST REMOTE up  button
        .command = 0x04,
        .action = &action_cursor_right
    },
    {
        .address = 0x03,
        .command = 0x00,
        .action = &doNothing
    },
    {
        .address = 0x02,
        .command = 0x1d,
        .action = &doNothing
    }

};

void delay_ms(uint32_t milliseconds);

// Hardware functions
static inline void clock_setup(void)
{
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
	//rcc_clock_setup_in_hsi_out_48mhz();

	// enable the systick
    systick_clear();
    systick_set_frequency(1000000, rcc_ahb_frequency); // Interrupt every microsecond
	systick_counter_enable();
	systick_interrupt_enable();
}

static inline void led_setup(void)
{
    /* Enable GPIOG clock for LED. */
	rcc_periph_clock_enable(RCC_GPIOC);

	/* Setup GPIO pin GPIO13 on GPIO port C for LED. */
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

	// LED is low acting on the bluepill board, switch off by default
	gpio_set(GPIOC, GPIO13);
}

static inline void activityLED_on(void)
{
    // turn on the LED when there is activity
    gpio_clear(GPIOC, GPIO13);
}

static inline void activityLED_off(void)
{
    // turn off the LED when there is no activity
    gpio_set(GPIOC, GPIO13);
}

static inline void infraredpin_setup(void)
{
    // For now use PIN B12
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_AFIO);

    gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO12);

    exti_set_trigger(EXTI12, EXTI_TRIGGER_FALLING);
    exti_select_source(EXTI12, GPIOB);
    exti_enable_request(EXTI12);

    //nvic_set_priority(NVIC_EXTI0_IRQ, 0);
    nvic_enable_irq(NVIC_EXTI15_10_IRQ);
}

int main(void)
{
    // BSP initialization
	clock_setup();
	led_setup();
	usbd_setup();
	infraredpin_setup();

	nvic_enable_irq(NVIC_USB_LP_CAN_RX0_IRQ);

	necdecoder_register_button_actions(&command_list[0], sizeof(command_list) / sizeof(struct nec_infrared_command_t));

	//while(1);

    while (1)
    {
        activityLED_on();
        delay_ms(200);
        activityLED_off();
        delay_ms(200);
        activityLED_on();
        delay_ms(200);
        activityLED_off();
        delay_ms(1000);
    }

	return 0;
}

// delay
void delay_ms(uint32_t milliseconds)
{
    timing_delay = milliseconds * 1000;

    while(timing_delay != 0);
}


void sys_tick_handler()
{
    clock_counter++;

    if (timing_delay != 0x00)
    {
        timing_delay--;
    }
}

void usb_lp_can_rx0_isr(void)
{
    const uint16_t usb_istr = *USB_ISTR_REG;
    (void)usb_istr;

    usbpoll();
}

void exti15_10_isr(void)
{
    // Falling edge interrupt, PORT B12

    if (!exti_get_flag_status(EXTI12))
    {
        // ignore interrupts from other ports
        return;
    }

    necdecoder_decode_falling_edge(clock_counter);

    exti_reset_request(EXTI12);
}
