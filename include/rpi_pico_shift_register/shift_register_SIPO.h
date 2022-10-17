
/**
 * @file shift_register_SIPO.h
 * @brief header for SN74HC595 shift register
 */

#ifndef SHIFT_REGISTER_SIPO_H
#define SHIFT_REGISTER_SIPO_H

#define PIN_DISABLED 0xff   // default value for uninitialized pins

#include <stdint.h>

/**
 * @brief Specifies byte order for serial data
 * 
 */
typedef enum {
    MSBFIRST = 0,   /**< Most significant bit first */
    LSBFIRST        /**< Least significant bit first*/
} ByteOrder;

/**
 * @brief A structure containing pin information for a Serial-In-Parallel-Out shift register
 * 
 */
typedef struct ShiftRegisterSIPO {

    uint8_t serial_pin;
    uint8_t latch_pin;
    uint8_t clock_pin;

    uint8_t enable_pin;
    uint8_t clear_pin;  // Not used

    void (*set_enable_pin)(struct ShiftRegisterSIPO *, uint8_t);
    void (*enable)(struct ShiftRegisterSIPO *, bool);
    void (*latch)(struct ShiftRegisterSIPO *);
    void (*write_bit)(struct ShiftRegisterSIPO *, bool);
    void (*write_byte)(struct ShiftRegisterSIPO *, uint8_t, ByteOrder);
    void (*clear)(struct ShiftRegisterSIPO *);

} ShiftRegisterSIPO;

/**
 * @brief Sets GPIO and initializes shift_register_SIPO structure
 * 
 * @param serial_pin GPIO pin for serial output
 * @param latch_pin GPIO pin for latch output
 * @param clock_pin GPIO pin for clock output
 * @return ShiftRegisterSIPO 
 */
ShiftRegisterSIPO shift_register_SIPO_create (uint8_t serial_pin, uint8_t latch_pin, uint8_t clock_pin);

/**
 * @brief Set GPIO for the enable pin
 * 
 * @param sr shift register
 * @param enable_pin GPIO pin for enable output
 */
void shift_register_SIPO_set_enable_pin (ShiftRegisterSIPO *sr, uint8_t enable_pin);

/**
 * @brief Set output enable
 * 
 * @details The uutput enable pin on the SN74HC595 is active low, so
 * the GPIO will be set to the complement of the
 * boolean entered here; i.e. false will set the GPIO high.
 * The enable pin needs to be set by shift_register_SIPO_set_enable_pin()
 * prior to calling this function
 * 
 * @param sr shift register
 * @param value true enables the output, false disables it
 */
void shift_register_SIPO_enable (ShiftRegisterSIPO *sr, bool value);

/**
 * @brief Latches register output
 * 
 * @param sr shift register
 */
void shift_register_SIPO_latch (ShiftRegisterSIPO *sr);

/**
 * @brief Write a single bit to the shift register
 * 
 * @param sr shift register
 * @param value 0 (false) or 1 (true)
 */
void shift_register_SIPO_write_bit (ShiftRegisterSIPO *sr, bool value);

/**
 * @brief Writes a byte of data to the shift register
 * 
 * @param sr shift register
 * @param byte data to transmit
 * @param ByteOrder byte order, defaults to MSBFIRST on invalid input
 */
void shift_register_SIPO_write_byte (ShiftRegisterSIPO *sr, uint8_t byte, ByteOrder byte_order);

/**
 * @brief Sets output of shift register to all zeros
 * 
 * @param sr shift register
 */
void shift_register_SIPO_clear (ShiftRegisterSIPO *sr);

#endif