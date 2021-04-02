/*
 * (c) 2015 flabberast <s3+flabbergast@sdfeu.org>
 *
 * Based on the following work:
 *  - Guillaume Duc's raw hid example (MIT License)
 *    https://github.com/guiduc/usb-hid-chibios-example
 *  - PJRC Teensy examples (MIT License)
 *    https://www.pjrc.com/teensy/usb_keyboard.html
 *  - hasu's TMK keyboard code (GPL v2 and some code Modified BSD)
 *    https://github.com/tmk/tmk_keyboard/
 *  - ChibiOS demo code (Apache 2.0 License)
 *    http://www.chibios.org
 *
 * Since some GPL'd code is used, this work is licensed under
 * GPL v2 or later.
 */

#include "ch.h"
#include "hal.h"
#include "board.h"

#include "usb_main.h"

/* TMK includes */
#include "report.h"
#include "host.h"
#include "host_driver.h"
#include "keyboard.h"
#include "action.h"
#include "action_util.h"
#include "mousekey.h"
#include "led.h"
#include "sendchar.h"
#include "debug.h"
#ifdef SLEEP_LED_ENABLE
#include "sleep_led.h"
#endif
#include "suspend.h"
#include "hook.h"
#include "printf.h"

/* -------------------------
 *   TMK host driver defs
 * -------------------------
 */

/* declarations */
uint8_t keyboard_leds(void);
void send_keyboard(report_keyboard_t *report);
void send_mouse(report_mouse_t *report);
void send_system(uint16_t data);
void send_consumer(uint16_t data);

/* host struct */
host_driver_t chibios_driver = {
  keyboard_leds,
  send_keyboard,
  send_mouse,
  send_system,
  send_consumer
};

/* Default hooks definitions. */
__attribute__((weak))
void hook_early_init(void) {}

__attribute__((weak))
void hook_late_init(void) {}

__attribute__((weak))
void hook_usb_suspend_loop(void) {
  /* Do this in the suspended state */
  suspend_power_down(); // on AVR this deep sleeps for 15ms
  /* Remote wakeup */
  if((USB_DRIVER.status & 2) && suspend_wakeup_condition()) {
    usbWakeupHost(&USB_DRIVER);
  }
}

/* TESTING
 * Amber LED blinker thread, times are in milliseconds.
 */
/* set this variable to non-zero anywhere to blink once */
//uint8_t blinkLed = 0;
//static THD_WORKING_AREA(waBlinkerThread, 128);
//static THD_FUNCTION(blinkerThread, arg) {
//  (void)arg;
//  chRegSetThreadName("blinkOrange");
//  while(true) {
//    if(blinkLed) {
//      blinkLed = 0;
//      palSetPad(GPIOA, GPIOA_LED);       /* Orange.  */
//      chThdSleepMilliseconds(100);
//      palClearPad(GPIOA, GPIOA_LED);       /* Orange.  */
//    }
//    chThdSleepMilliseconds(100);
//  }
//}

uint8_t blinkLed = 0;
static THD_WORKING_AREA(waBlinkerThread, 128);
static THD_FUNCTION(blinkerThread, arg) {
  (void)arg;
  chRegSetThreadName("blinkLED");
  while(true) {
    {
      sdWrite(&SD2, (int8_t*)"USART2 Initialized.\n", 20);
      printf("Check printf.\n");
      palSetPad(GPIOA, GPIOA_LED);       /* Orange.  */
      chThdSleepMilliseconds(300);
      palClearPad(GPIOA, GPIOA_LED);       /* Orange.  */
      chThdSleepMilliseconds(400);
    }
  }
}

void sendchar_uart(void *p, char c) {
	sdWrite(&SD2, (int8_t*) &c, 1);
};


void _delay_us(uint16_t us){
    gptStartOneShotI(&GPTD8, 100);
}

void _delay_ms(uint16_t ms){
  chThdSleepMilliseconds(1);
}


/* Main thread
 */
int main(void) {
  /* ChibiOS/RT init */
  halInit();
  chSysInit();

  sdStart(&SD2, NULL);
  palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
  palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));

  sdWrite(&SD2, (int8_t*)"USART2 Initialized.\n", 20);
  chThdSleepMilliseconds(10);
  init_printf(NULL,sendchar_uart);


  static const GPTConfig gpt8cfg = {
    100000, // 1 MHz timer clock.
    NULL, // No callback
    0, 0
  };

  gptStart(&GPTD8, &gpt8cfg);
  gptPolledDelay(&GPTD8, 10); // 10 us delay

  // TESTING
  chThdCreateStatic(waBlinkerThread, sizeof(waBlinkerThread), NORMALPRIO, blinkerThread, NULL);

  hook_early_init();

  /* Init USB */
  init_usb_driver(&USB_DRIVER);

  /* init printf */

  /* Wait until the USB is active */
  while(USB_DRIVER.state != USB_ACTIVE)
    chThdSleepMilliseconds(50);

  /* Do need to wait here!
   * Otherwise the next print might start a transfer on console EP
   * before the USB is completely ready, which sometimes causes
   * HardFaults.
   */
  chThdSleepMilliseconds(50);

  printf("USB configured.\n");

  /* init TMK modules */
  keyboard_init();
  host_set_driver(&chibios_driver);

#ifdef SLEEP_LED_ENABLE
  sleep_led_init();
#endif

  print("Keyboard start.\n");

  hook_late_init();

  /* Main loop */
  while(true) {

    if(USB_DRIVER.state == USB_SUSPENDED) {
      print("[s]");
      while(USB_DRIVER.state == USB_SUSPENDED) {
        hook_usb_suspend_loop();
      }
      /* Woken up */
      // variables have been already cleared
      send_keyboard_report();
#ifdef MOUSEKEY_ENABLE
      mousekey_send();
#endif /* MOUSEKEY_ENABLE */
    }

    keyboard_task();
  }
}
