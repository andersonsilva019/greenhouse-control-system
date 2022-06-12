#include "clock.h"
#include "drivers.h"
#include "gpio.h"
#include "port.h"

#include <stdbool.h>

static pin_handler_t drv_led_green;
static pin_handler_t drv_led_red;

static pin_handler_t drv_button_sw1;
static pin_handler_t drv_button_sw3;

/*!
 * @brief Inits the clock of the processor at 48 MHz.
 */
void drvCpuClockInit(void) {
	clkEnableClock(clkSOURCE_HIRCLK);
	clkSetMainClock(clkSOURCE_HIRCLK);
}

/*!
 * @brief Inits the two embedded LEDs of the board.
 */
void drvLedInit(void) {
	drv_led_green.port = pinPORT_D;
	drv_led_green.pin = 5;
	gpioPinInit(&drv_led_green, gpioOUTPUT);
	gpioPinWrite(&drv_led_green, DRV_LED_OFF);

	drv_led_red.port = pinPORT_E;
	drv_led_red.pin = 29;
	gpioPinInit(&drv_led_red, gpioOUTPUT);
	gpioPinWrite(&drv_led_red, DRV_LED_OFF);
}

/*!
 * @brief Inits the two embedded buttons of the board.
 */
void drvButtonInit(void) {
	drv_button_sw1.port = pinPORT_C;
	drv_button_sw1.pin = 3;
	gpioPinInit(&drv_button_sw1, gpioINPUT);
	portConfigPullup(&drv_button_sw1);

	drv_button_sw3.port = pinPORT_C;
	drv_button_sw3.pin = 12;
	gpioPinInit(&drv_button_sw3, gpioINPUT);
	portConfigPullup(&drv_button_sw3);
}

/*!
 * @brief Performs a given function with the given LED.
 */
void drvLedSet(drv_led_id led, drv_led_function function) {
	if(led > DRV_LED_RED || led < DRV_LED_GREEN) {
		while(1);
	}
	pin_handler_t *led_handle = (led == DRV_LED_GREEN) ? &drv_led_green : &drv_led_red;
	switch(function) {
		case DRV_LED_SET:
			gpioPinWrite(led_handle, DRV_LED_ON);
			break;
		case DRV_LED_CLEAR:
			gpioPinWrite(led_handle, DRV_LED_OFF);
			break;
		case DRV_LED_TOGGLE:
			gpioPinToggle(led_handle);
			break;
	}
}

drv_button_level drvCheckButtonPressed(drv_button_id button) {
	if(button > DRV_BUTTON_SW3 || button < DRV_BUTTON_SW1) {
		while(1);
	}
	pin_handler_t *button_handle = (button == DRV_BUTTON_SW1) ? &drv_button_sw1 : &drv_button_sw3;
	return gpioPinRead(button_handle);
}
