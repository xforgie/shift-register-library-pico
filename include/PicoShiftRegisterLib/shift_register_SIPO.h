
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
} byte_order_t;

/**
 * @brief A structure containing pin information for a shift register
 * 
 */
typedef struct {

    uint8_t serial_pin;
    uint8_t latch_pin;
    uint8_t clock_pin;

    uint8_t enable_pin;
    uint8_t clear_pin;

    uint32_t num_connected; /** How many registers are connected to eachother */

} shift_register_SIPO;

/**
 * @brief Allocate memory and assign pins for shift_register_SIPO structure
 * 
 * @param num_connected How many shift registers are chained serially
 * @param serial_pin GPIO pin for serial output
 * @param latch_pin GPIO pin for latch output
 * @param clock_pin GPIO pin for clock output
 * @return shift_register_SIPO*, NULL if there was a failure to allocate memory 
 */
shift_register_SIPO* shift_register_SIPO_create (uint32_t num_connected, uint8_t serial_pin, uint8_t latch_pin, uint8_t clock_pin);

/**
 * @brief Set GPIO for the enable pin
 * 
 * @param sr shift register
 * @param enable_pin GPIO pin for enable output
 */
void shift_register_SIPO_set_enable_pin (shift_register_SIPO *sr, uint8_t enable_pin);

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
void shift_register_SIPO_set_enable (shift_register_SIPO *sr, bool value);

/**
 * @brief Latches register output
 * 
 * @param sr shift register
 */
void shift_register_SIPO_latch (shift_register_SIPO *sr);

/**
 * @brief Writes a byte of data to the shift register
 * 
 * @param sr shift register
 * @param byte data to transmit
 * @param byte_order byte order
 */
void shift_register_SIPO_write_byte (shift_register_SIPO *sr, uint8_t byte, byte_order_t byte_order);

/**
 * @brief Write a single bit to the shift register
 * 
 * @param sr shift register
 * @param value 0 (false) or 1 (true)
 */
void shift_register_SIPO_write_bit (shift_register_SIPO *sr, bool value);

/**
 * @brief Sets output of shift register to all zeros
 * 
 * @param sr shift register
 */
void shift_register_SIPO_clear (shift_register_SIPO *sr);

/**
 * @brief Free shift_register_SIPO structure
 * 
 * @param sr shift register
 */
void shift_register_SIPO_destroy (shift_register_SIPO *sr);

#endif