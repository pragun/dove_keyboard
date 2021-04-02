/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"

/*
 * scan matrix
 */
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif

static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

stm32_gpio_t* row_ports1[] = {GPIOC,GPIOC,GPIOC,GPIOC,GPIOC};
uint16_t row_pins1[] = {GPIOC_PIN0,GPIOC_PIN1,GPIOC_PIN3,GPIOC_PIN2,GPIOC_PIN4};

stm32_gpio_t* row_ports2[] = {GPIOD,GPIOD,GPIOD,GPIOD,GPIOD};
uint16_t row_pins2[] = {GPIOD_PIN1,GPIOD_PIN0,GPIOD_PIN2,GPIOD_PIN3,GPIOD_PIN4};

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

/* generic STM32F103C8T6 board */
#ifdef BOARD_GENERIC_STM32_F103
#define LED_ON()    do { palClearPad(GPIOC, GPIOC_LED) ;} while (0)
#define LED_OFF()   do { palSetPad(GPIOC, GPIOC_LED); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOC, GPIOC_LED); } while (0)
#endif

/* Maple Mini */
#ifdef BOARD_MAPLEMINI_STM32_F103
#define LED_ON()    do { palSetPad(GPIOB, 1) ;} while (0)
#define LED_OFF()   do { palClearPad(GPIOB, 1); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOB, 1); } while (0)
#endif

void matrix_init(void)
{
    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    //debug
    debug_matrix = true;
    LED_ON();
    wait_ms(500);
    LED_OFF();
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        wait_us(5);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            wait_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("   %d: %08x|", row, matrix_get_row(row));
    }
    print("\n");
}

/* Column pin configuration
 */
static void  init_cols(void)
{
#ifdef BOARD_MAPLEMINI_STM32_F103
    // don't need pullup/down, since it's pulled down in hardware
    palSetPadMode(GPIOB, 8, PAL_MODE_INPUT);
#else
    palSetPadMode(GPIOB, 8, PAL_MODE_INPUT_PULLDOWN);
#endif
}

/* Returns status of switches(1:on, 0:off) */
static matrix_row_t read_cols(void)
{
  uint16_t cols1 = palReadPort(GPIOE);
  uint16_t cols2 = palReadPort(GPIOD);

  cols1 = ~cols1;
  cols2 = ~cols2;

  return ((cols1 >> 2) << 11)|(cols2 >> 5);
}

/* Row pin configuration
 */
static void unselect_rows(void)
{
    // palSetPadMode(GPIOA, GPIOA_PIN10, PAL_MODE_INPUT); // hi-Z
  for(uint8_t i=0; i<MATRIX_ROWS; i++){
    palSetPad(row_ports1[i],row_pins1[i]);
    palSetPad(row_ports2[i],row_pins2[i]);
  }
}

static void select_row(uint8_t row)
{
    //(void)row;
    palClearPad(row_ports1[row],row_pins1[row]);
    palClearPad(row_ports2[row],row_pins2[row]);
    // Output low to select
    // switch (row) {
    //     case 0:
    //         palSetPadMode(GPIOA, GPIOA_PIN10, PAL_MODE_OUTPUT_PUSHPULL);
    //         palSetPad(GPIOA, GPIOA_PIN10, PAL_LOW);
    //         break;
    // }
}
