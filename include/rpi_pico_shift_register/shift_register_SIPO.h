
/**
 * @file shift_register_SIPO.h
 * @brief header for shift_register_SIPO library
 */

#ifndef SHIFT_REGISTER_SIPO_H
#define SHIFT_REGISTER_SIPO_H

#include <stdint.h>

/**
 * @brief Specifies byte order for serial data
 * 
 */
typedef enum {
    MSBFIRST = 0,   /** Most significant bit first */
    LSBFIRST        /** Least significant bit first*/
} ByteOrder;

/**
 * @brief A structure containing pin information for a shift register
 * 
 */
typedef struct ShiftRegisterSIPO{

    uint8_t serial_pin;
    uint8_t latch_pin;
    uint8_t clock_pin;

    uint8_t enable_pin;
    uint8_t clear_pin;

    void (*set_enable_pin)(struct ShiftRegisterSIPO *, uint8_t);
    void (*set_enable)(struct ShiftRegisterSIPO *, bool);
    void (*latch)(struct ShiftRegisterSIPO *);
    void (*write_byte)(struct ShiftRegisterSIPO *, uint8_t, ByteOrder);
    void (*write_bit)(struct ShiftRegisterSIPO *, bool);
    void (*clear)(struct ShiftRegisterSIPO *);

} ShiftRegisterSIPO;

/**
 * @brief Sets GPIO and initializes shift_register_SIPO structure
 * 
 * @param serial_pin GPIO pin for serial output
 * @param latch_pin GPIO pin for latch output
 * @param clock_pin GPIO pin for clock output
 * @return shift_register_SIPO*, NULL if there was a failure to allocate memory 
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
 * @discussion The output enable pin is active low, so
 * the GPIO will be set to the complement of the
 * boolean entered here; i.e. false will set the GPIO high
 * 
 * @todo throw an error if enable pin is not set 
 *
 * @param sr shift register
 * @param value true enables the output, false disables it
 */
void shift_register_SIPO_set_enable (ShiftRegisterSIPO *sr, bool value);

/**
 * @brief Latches register output
 * 
 * @param sr shift register
 */
void shift_register_SIPO_latch (ShiftRegisterSIPO *sr);

/**
 * @brief Writes a byte of data to the shift register
 * 
 * @param sr shift register
 * @param byte data to transmit
 * @param ByteOrder byte order
 */
void shift_register_SIPO_write_byte (ShiftRegisterSIPO *sr, uint8_t byte, ByteOrder byte_order);

/**
 * @brief Write a single bit to the shift register
 * 
 * @param sr shift register
 * @param value 0 (false) or 1 (true)
 */
void shift_register_SIPO_write_bit (ShiftRegisterSIPO *sr, bool value);

/**
 * @brief Sets output of shift register to all zeros
 * 
 * @param sr shift register
 */
void shift_register_SIPO_clear (ShiftRegisterSIPO *sr);

/**
 * @brief Free shift_register_SIPO structure
 * 
 * @param sr shift register
 */
void shift_register_SIPO_destroy (ShiftRegisterSIPO *sr);

#endif