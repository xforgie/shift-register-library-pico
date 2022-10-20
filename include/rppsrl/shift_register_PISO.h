/**
 * @file shift_register_PISO.h
 * @brief header for CD4021B shift register
*/

#ifndef SHIFT_REGISTER_PISO_H
#define SHIFT_REGISTER_PISO_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief structure containing pin information for a Parallel-In-Serial-Out shift register
 * 
*/
typedef struct ShiftRegisterPISO {

    uint8_t serial_pin;
    uint8_t clock_pin;
    uint8_t latch_pin;

    void (*read_in_byte)(struct ShiftRegisterPISO *, uint8_t *);

} ShiftRegisterPISO;

/**
 * @brief Sets GPIO and initializes ShiftRegisterPISO structure
 * 
 * @param serial_pin GPIO pin for serial input
 * @param clock_pin GPIO pin for clock output
 * @param latch_pin GPIO pin for latch output
 * @return ShiftRegisterPISO
*/
ShiftRegisterPISO shift_register_PISO_create(uint8_t serial_pin, uint8_t clock_pin, uint8_t latch_pin);

/**
 * @brief Reads a byte into the provided buffer from the shift register
 * 
 * @note Uses busy waiting to be within the 3 MHz limit of CD4021BE
 * 
 * @param sr shift register
 * @param buffer data buffer
 */
void shift_register_PISO_read_in_byte(ShiftRegisterPISO *sr, uint8_t *buffer);

#endif