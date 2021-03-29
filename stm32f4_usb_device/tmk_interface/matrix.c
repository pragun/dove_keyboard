#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"

/*
 * Infinity Pinusage:
 * Column pins are input with internal pull-down. Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 *     col: { PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB12, PB13, PB14, PB15}
 *     row: { PB2, PB10, PC13, PC14, PC15 }
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint32_t debouncing_time = 0;

const GPIO_TypeDef* col_ports[] = {GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB};
const uint16_t col_pins[] = {GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};

const GPIO_TypeDef* row_ports[] = {GPIOB,GPIOB,GPIOC,GPIOC,GPIOC};
const uint16_t row_pins[] = {GPIO_PIN_2, GPIO_PIN_10, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};

void matrix_init(void)
{
	//All of this is done in main.cpp by MX_GPIO_Init
    memset(matrix, 0, sizeof(matrix));
    memset(matrix_debouncing, 0, sizeof(matrix_debouncing));
}

uint8_t matrix_scan(void)
{
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;

        //  strobe row
        HAL_GPIO_WritePin(row_ports[row],row_pins[row],GPIO_PIN_SET);
        wait_us(1); // need wait to settle pin state

        // read column data
        for (int col = 0; col < MATRIX_COLS; col++) {
        	GPIO_PinState ps = HAL_GPIO_ReadPin(col_ports[col],col_pins[col]);
            data |= (ps<<col);
        }

        if (matrix_debouncing[row] != data) {
			matrix_debouncing[row] = data;
			debouncing = true;
			debouncing_time = timer_read32();
       }

       // un-strobe column
        HAL_GPIO_WritePin(row_ports[row],row_pins[row],GPIO_PIN_RESET);
    }

    if (debouncing && timer_elapsed32(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing = false;
    }
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    printf("\nRow data:\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("%02X: ");
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}
